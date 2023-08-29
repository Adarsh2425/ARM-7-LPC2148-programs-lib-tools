;Author: Abhinav Pawar
;Date: 03-5-2023

;TOLLGATE ,based on the state from which vehicle is coming particular charge is set
;1-karnatak (amount Rs 40)
;2-maharashtra (amount Rs 60)
;3-kerala(amount Rs 90)
;at the end of the day the total amount will be deducted from the owner of the vehicle

 AREA xx,CODE,readonly
 ENTRY
	LDR R1,=7	;Number of vehicles coming from Karnataka
	LDR R2,=5	;Number of vehicles coming from Maharashtra
	LDR R3,=2	;Number of vehicles coming from Kerala
	
	LDR R11,=40	;Charge for each vehicle from Karnataka
	LDR R12,=60	;Charge for each vehicle from Maharashtra
	LDR R13,=90	;Charge for each vehicle from Kerala
	
	MUL R1,R11,R1	;total amount deducted from vehicles of Karnataka
	MUL R2,R12,R2	;total amount deducted from vehicles of Maharashtra
	MUL R3,R13,R3	;total amount deducted from vehicles of Kerala
	ADD R0,R1,R2
	ADD R0,R3,R0	;total tollgate collection 
stop b stop
 END