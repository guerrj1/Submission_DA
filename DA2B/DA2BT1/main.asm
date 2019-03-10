; DA2BT1.asm

.INCLUDE "M328PDEF.INC"

.org 0                 ;location reset
jmp main

.org 0x02              ;location for external interrupt 0
jmp ex0_isr            ;external interrupt label

main:
ldi r20, high(ramend)  ;loads the upper ram address
out sph, r20 
ldi r20, low(ramend)   ;loads lower ram address
out spl, r20           ;initialize the stack
sts eicra, r20         ;external interrupt control register
sbi portd, 2           ;pull-up activated
sbi ddrb, 2            ;set portb2 as output
cbi portb, 2           ;clears portb2
sbi ddrb, 5            ;sets pb5 as output
sbi portb, 5           ;turns off pb5
ldi r20, (1<<int0)     ;enable INT0
out eimsk, r20         ;store EIMSK
LDI R20,5              ;set clock prescaler to 1024
STS TCCR1B, R20             
sei                    ;enable interrupts

ex0_isr:               ;interrupt label
in r21, portb          ;portb value stored into r21
ldi r22, (1<<2)        ;sets a one in bit 2
eor r21, r22           ;toggles the led
out portb, r21         ;outputs the led
STS TCNT1H, R20     
STS TCNT1L, R20
rcall delay_on         ;calls the delay to keep led on
reti 

delay_on:
 LDS R29, TCNT1H       ;loading upper bit of counter to R29
 LDS R28, TCNT1L       ;loading lower bit of counter to R28
 CPI R28,0x4A          ;comparing if lower 8 bits of timer is 0x08
 BRSH body_on          ;if lower bits of timer have reached desired amount, check the upper bits
 RJMP delay_on         ;otherwise, keep checking lower bits

body_on:
 CPI R29,0x4C          ;check to see if upper timer bits have reached the desired value
 BRLT delay_on         ;if not, recheck the lower bits
 RET                   ;once the timer reached the desired value, toggle the LED