;Author: Abhinav Pawar
;Date: 03-5-2023

;Alp to Evaluate 9x2+7y -34 only if x>y
; Else compute 9y2-7x+5

AREA xx,CODE,readonly
 ENTRY
	LDR R7,=0x00000005		;x
	LDR R8,=0x00000008		;y
	CMP R7,R8
	BCS compute_greater		;branch if C=1 (R7>R8)
	LDR R2,=9				;coefficients of 9y2-9x+5
	LDR R1,=-7
	LDR R0,=5
	
	MUL R12,R8,R8	;y^2
	MUL R12,R2,R12	;9y2
	MUL R11,R1,R7	;-7x
	ADD R10,R12,R11	;9y2-7x
	ADD R10,R10,R0	;9y2-7x+5
	b stop
	
compute_greater
	LDR R2,=9				;coefficients of 9x2+7y-34
	LDR R1,=7
	LDR R0,=-34
	MUL R12,R7,R7	;x^2
	MUL R12,R2,R12	;9x^2
	MUL R11,R1,R8	;7y
	ADD R10,R11,R12	;9x^2+7y
	ADD R10,R10,R0	;9x^2+7y-34
stop b stop
end