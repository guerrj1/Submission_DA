;Jett Guerrero
;2/23/2019
;DA1B

.equ STARTADDS = 0x0200             ;starting location address for X pointer
.equ count = 98                     ;counter for 99 numbers - 1-98

.org 0x00                           ;starting program at 0x00

clr r0                              ;clearing r0
ldi XL, low(STARTADDS)              ;loading the lower bits of STARTADDS into XL
ldi XH, high(STARTADDS)             ;loading the higher bits of STARTADDS into XH
ldi YL, low(0x400)                  ;loading the lower bits of 0x400 into YL
ldi YH, high(0x400)                 ;loading the higher bits of 0x400 into YH
ldi ZL, low(0x600)                  ;loading the lower bits of 0x600 into ZL
ldi ZH, high(0x600)                 ;loading the higher bits of 0x600 into ZH

ldi r20, 3                          ;loading decimal value 3 into r20 for divisible by 3 
ldi r21, count                      ;loading value of count which is 98 into r21
ldi r23, 11                         ;loading decimal value 11 into r23 for comparing        

;clear registers
clr r16                             ;clearing r16 - Y SUM
clr r17                             ;clearing r17 - Y SUM
clr r18                             ;clearing r18 - Z SUM
clr r19                             ;clearing r19 - Z SUM

;adding the lower and upper bits and storing it to a register
start:
mov r1, XL                          ;moving the value from XL into r1
add r1, XH                          ;adding the value in XH into r1

inc2eleven:                         ;loop for increasing value to greater than 10 => 11
cp r1, r23                          ;compares the value in r1 with 11
brsh isgreaterthanten               ;if the value in r1 is same or higher than 11 then branch to "isgreaterthanten" label
inc r1                              ;if r1 is lower than 11, increment value in r1
jmp inc2eleven                      ;jump back to inc2eleven label and repeat until r1 is 11

;value is greater than 10
isgreaterthanten:                   
mov r3, r1                          ;moves the value from r1 into r3
st X+, r3                           ;stores the value in r3 into X and increments the X pointer
jmp dividebythree                   ;jumps to dividebythree label to check for divisibility

loop_greaterthanten:                ;when value increments and is greater than 10, jump here
st X+, r3                           ;stores the value in r3 into X and increments the X pointer
mov r1, r3                          ;moves value from r3 into r1

dividebythree:                      ;checks the value if it's divisible by three 
cp r1, r20                          ;compares value in r1 to 3
brlo notdivbythree                  ;if r1 is lower than 3 then branch to "notdivbythree"
sub r1, r20                         ;subtract the value in r1 by 3
cp r1, r20                          ;compare the value in r1 with 3
breq isdivbythree                   ;if the value in r1 equals 3 then branch to "isdivbythree"
rjmp dividebythree                  ;relative jump to "dividebythree" if r1 is not equal to 3 yet

isdivbythree:                       ;value is divisible by 3
st Y+, r3                           ;store the value in r3 into Y and increment the Y pointer   [Y] = XL + XH
add r16, r3                         ;add the value in r3 into r16 for SUM
adc r17, r0                         ;add 0 into r17 plus any carry
rjmp counter_check                  ;relative jump to "counter_check" 

notdivbythree:                      ;value is not divisible by 3
st Z+, r3                           ;stores value in r3 into Z and increments the Z pointer   [Z] = XL + XH
add r18, r3                         ;adds the value in r3 into r18 for SUM
adc r19, r0                         ;add 0 into r19 plus any carry
rjmp counter_check                  ;relative jump to "counter_check"

counter_check:                      ;checks to see if program ran for 99 values 
cp r21, r0                          ;compare r21 which is 98 to 0 
breq end                            ;if r21 equals 0 then branch to 
dec r21                             ;else decrement value in r21
inc r3                              ;increment value in r3 and continue populating X
jmp loop_greaterthanten             ;relative jump to "loop_greaterthanten"

end: jmp end                        ;end label and keep jumping to this label when finished