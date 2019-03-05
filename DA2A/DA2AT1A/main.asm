;DA2AT1A

.INCLUDE "M328pDEF.INC"
.CSEG
.org 0x0000
	
 SBI DDRB, 5          ;makes PB5 an output
 SBI PORTB,5          ;turns off LED for PB5
 SBI DDRB, 2          ;makes PB2 an output
 LDI R20,5            ;set clock prescaler to 1024
 STS TCCR1B,R20

begin:
 LDI R20,0x00         ;resetting the counter to 0
 ;ON
 SBI PORTB, 2         ;sets LED PB2 on
 STS TCNT1H,R20        
 STS TCNT1L,R20
 RCALL delay_on       ;calling timer to wait for 0.435 sec

 ;OFF
 CBI PORTB, 2         ;clears LED PB2 off
 STS TCNT1H,R20       
 STS TCNT1L,R20
 RCALL delay_off      ;calling timer to wait for 0.29 sec
 RJMP begin           ;repeat main loop

;Delay for LED on-----------
delay_on:
 LDS R29, TCNT1H      ;loading upper bit of counter to R29
 LDS R28, TCNT1L      ;loading lower bit of counter to R28
 CPI R28,0x8C         ;comparing if lower 8 bits of timer is 0x8c - lower bits of 1A8C
 BRSH body_on         ;if lower bits of timer have reached desired amount, check the upper bits
 RJMP delay_on        ;otherwise, keep checking lower bits

body_on:
 CPI R29,0x1A         ;check to see if upper timer bits have reached the desired value
 BRLT delay_on        ;if not, recheck the lower bits
 RET                  ;once the timer reached the desired value, toggle the LED


;Delay for LED off------------
delay_off:
 LDS R29, TCNT1H      ;loading upper bit of counter to R29
 LDS R28, TCNT1L      ;loading lower bit of counter to R28
 CPI R28,0xB2         ;comparing if lower 8 bits of timer is 0xB2 - lower bits of 11B2
 BRSH body_off        ;if lower bits of timer have reached desired amount, check the upper bits
 RJMP delay_off       ;otherwise, keep checking lower bits

body_off:
 CPI R29,0x11         ;check to see if upper timer bits have reached the desired value
 BRLT delay_off       ;if not, recheck the lower bits
 RET                  ;once the timer reached the desired value, toggle the LED

