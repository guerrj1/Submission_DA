;Jett Guerrero
;2/16/19
;DA1A_Mul

.EQU multiplicand = 0xFFFF    ;equates variable name multiplicand with hex value 0xFFFF
.EQU multiplier = 0xFF        ;equates variable name multiplier with hex value 0xFF

ldi r24, low(multiplicand)    ;loads the lower bits of the 16 bit multiplicand in r24 
ldi r25, high(multiplicand)   ;loads the higher bits of the 16 bit multiplicand in r25
ldi r22, multiplier           ;loads the hex value in multiplier into r22 
ldi r16, 0x00                 ;loads 0 in r16

mul r24, r22                  ;multiplies the 8 bit value in r22 with 8 bit value in r24
movw r18:r19,r1:r0            ;moves the 16 bit result that is stored in r1 and r2 into r18 and r19
mul r25, r22                  ;multiplies the 8 bit value in r22 with 8 bit value in r25
add r20, r1                   ;adds/moves the 8 bit value in r1 into r20
add r19, r0                   ;adds/moves the 8 but value in r0 into r19

end: jmp end                  ;end label



