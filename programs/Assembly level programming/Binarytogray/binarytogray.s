;Author: Abhinav Pawar
;Date: 03-5-2023

;Binary to gray for the halfwords in the list
 AREA xx,CODE,readonly
 ENTRY
	LDR R4,=0x40000000			;Load 16bit binary number in 0x40000000
	LDR R3,=0x40000028			;Load pointer to store gray array from location 0x40000028
	LDR R7,=array				;Load pointer of array in R7
	MOV R1,#4					;Loop counter variable - initialize to number of binary numbers in array
loop
	LDR R11,[R7],#4				;Load array element in R11
	LDR R12,=0x0000ffff;		;Masking Higher significant halfword
	AND R0,R11,R12				;halfword binary stored in R0
	STR R10,[R4],#4				;Store halfword binary number in memory location 40000000
	LSR R10,R0,#1;				;Shift right binary num by 1bit 
	EOR R10,R0,R10				;gray stored in R10
	STR R10,[R3,#4]!			;Preindex store the gray num in mem location 40000028
	SUB R1,R1,#1				;decrement loop counter variable
	CMP R1,#0					;run loop for 4 times
	BNE loop
stop b stop;
array DCD 0xabcd2143,0x12345678,0xa0032c51,0xf2b1d3a7
 END