; DA2AT2A.asm

.CSEG
.org	0x0000
 
 SBI DDRB, 5             ;makes PB5 an output
 SBI PORTB,5             ;turns of LED for PB5
 CBI DDRC, 2             ;makes PC2 an input
 LDI R17,0               ;used to set or reset PB5
 SBI DDRB, 2             ;makes PB2 an output 
 LDI R20,5               ;set clock prescaler to 1024
 STS TCCR1B, R20 
     
check:
 SBIC PINC, 2            ;skip next instruction if PC2 is clear
 RJMP waiting            ;jumps to waiting label for waiting for a pressed input
 CBI PORTB, 2            ;clears PB2
 STS TCNT1H, R20     
 STS TCNT1L, R20
 RCALL delay_on          ;jumping for LED on delay
 RJMP check              ;jump back to check

;waiting for input from pushbutton
waiting:         
 SBI PORTB, 2            ;sets PB2 on
 RJMP check              ;relative jump back to check label 

;delay for LED on
delay_on:
 LDS R29, TCNT1H         ;loading upper bit of counter to R29
 LDS R28, TCNT1L         ;loading lower bit of counter to R28
 CPI R28,0x4A            ;comparing if lower 8 bits of timer is 0x08
 BRSH body_on            ;if lower bits of timer have reached desired amount, check the upper bits
 RJMP delay_on           ;otherwise, keep checking lower bits

body_on:
 CPI R29,0x4C            ;check to see if upper timer bits have reached the desired value
 BRLT delay_on           ;if not, recheck the lower bits
 RET                     ;once the timer reached the desired value, toggle the LED
