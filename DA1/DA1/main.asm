;Jett Guerrero
;2/16/19
;DA1A

.EQU multiplicand = 0xFFFF      ;equates variable name multiplicand with hex value 0xFFFF
.EQU multiplier = 0xFF         ;equates variable name multiplier with hex value 0xFF

ldi r24, low(multiplicand)     ;loads the lower bits of the 16 bit multiplicand in r24
ldi r25, high(multiplicand)    ;loads the higher bits of the 16 bit multiplicand in r25
ldi r22, multiplier            ;loads the hex value in multiplier into r22
ldi r16, 0x00                  ;loads 0 in r16

add_loop:                      ;label for looping
add r18, r24                   ;add hex value that is in r24 into r18
adc r19, r25                   ;add hex value that is in r25 into r19 including any carry
adc r20, r16                   ;add any carry if any into r20
dec r22                        ;decrement value in r22 to count the number of times addition operation needed
cp r22, r16                    ;compares if value in r22 is equal to 0 which is stored in r16
brne add_loop                  ;if r22 is not 0 then branch to add_loop until r22 is 0

end: jmp end                   ;end label 



