;*********************************************************************
;		AUTHOR VAMSIKRISHNAD
;		ROLL NO.CS09B006
;		DIVISON USING NON_RESTOIRNG METHOD
;		DATE:09-MAR-11
;**********************************************************************  
%include "io.mac"
.DATA
    msg1 db "Enter the dividend",0
    msg2 db "Enter the divisor",0
    msg3 db "The quotient is : ",0
    msg4 db "The remainder is: ",0
    msg5 db "The value of divisor is not valid ",0

.UDATA
.CODE
    .STARTUP
    sub EAX,EAX             ;MAKING VALUES IN ALL GEN. PUR. REG. ............ 
    sub EBX,EBX          
    sub ECX,ECX
    sub EDX,EDX             ;................IS EQUAL TO ZERO
    PutStr msg1
    nwln
    GetInt AX               ;STORING DIVIDEND IN EAX REG.
    PutStr msg2
    nwln
    GetInt BX               ;STORING DIVISOR IN EBX REG.
    bsf CX,BX
    jz invalid              ;CHECKING FOR VALIDITY OF DIVISOR
    bsr DX,BX
    cmp CX,DX               ;CHECKING WHETHER DIVISOR IS A POWER OF 2..........
    je diff_pro             ;............IF SO THEN GOING FOR A DIFF. PROCEDURE
    bsr CX,AX               
    add CX,1
    push CX
    do_shl:
	 shl BX,1
	 loop do_shl        ;..........IF MSB IN EAX IS 0 THEN MAKE ITS LSB 1
    pop CX
    push CX
    non_res:                ;MODULE FOR NON RESTORING DIVISON
	push DX
	bsr EDX,EAX         ;CHECKING WHETHER MSB IS 1 OR 0
	cmp EDX,31
	pop DX
	jne go_sub          ;IF IT IS 1 ADD DIVISOR .............
	je go_add           ;.........IF IT IS 0 SUB DIVISOR FROM "A"
	go_add:
  		shl EAX,1
                 add EAX,EBX       ;SHIFT LEFT VALUE IN EAX REG.................
                 push DX            
        	 bsr EDX,EAX       ;......IF MSB IN EAX IS 1 THEN MAKE ITS LSB 0
        	 cmp DX,31         
        	 pop DX
		 jne put1_1
		 dec CX
		 cmp CX,0          ;......IF MSB IN EAX IS 0 THEN MAKE ITS LSB 1
                 jg non_res
		 cmp CX,0
		 jg put1_1
		 jmp printer
                 put1_1:
                         bts AX,0
                sub CX,1 
		cmp CX,0
		 jg non_res
		 je printer

	go_sub:
		shl EAX,1            ;SHIFT LEFT VALUE IN EAX REG...............
		push EBX
		neg EBX              ;FINDING 2'S COMPLEMENT USING NEG CALL
		add EAX,EBX
		pop EBX              
		push DX
	        bsr EDX,EAX
        	cmp DX,31
        	pop DX
		jne put2_1
		dec CX
		cmp CX,0             ;....IF MSB IN EAX IS 1 THEN MAKE ITS LSB 0
		jg non_res
		cmp CX,0 
		jg put2_1
		jmp printer
		put2_1:              ;...... MSB IN EAX IS 0 THEN MAKE ITS LSB 1
			bts AX,0
		
		sub CX,1             ;METHOD FOR GETTING REMIANDER IN EAX REG
		cmp CX,0
		jg non_res
   	
	printer:
	pop CX       ;NOW SINCE THE BOTH REMAINDER AND QUOTIENT IS IN EAX REG .
	push DX
        bsr EDX,EAX
        cmp DX,31  ;IF MSB OF EAX IS 1 THEN ADD EBX(DIVISOR)TO GET CRT REMAINDER
        pop DX
	je adder_r
	jmp next
	adder_r:
		add EAX,EBX
		jmp next
	next:
		push EAX
		push CX
		mov DX,CX
		mov CX,8
		sub CX,DX
		push CX                  
		final_l:            ;METHOD FOR PRINTING QUOTIENT IN EAX REG.
			shl AX,1
			dec CX
			cmp CX,0
			jg final_l
		sub AH,AH
		pop CX
		final_r:            
			shr AX,1
			dec CX
			cmp CX,0
			jg final_r
		pop CX
		PutStr msg3
		nwln
		PutInt AX
		nwln
		pop EAX
		final_rem:
			shr AX,1
			dec CX
			cmp CX,0
			jg final_rem

		PutStr msg4
		nwln
		PutInt AX
		nwln
		jmp go	
	result_1:
	PutStr msg3
	nwln
	PutInt AX               ;METHOD FOR PRINTING REMIANDER IN EAX REG
	nwln
	PutStr msg4
	nwln
	PutInt CX
	nwln
	jmp go
    diff_pro:                   ;PROCEDURE FOR DIVISON WHEN DIVISOR IS A POWER OF 2
	mov DX,CX
	cmp CX,0                 ;SHIFTING RIGHT BY THE POWER OF 2 TO GET QUOTIENT 
        je result_1
        push AX
	do_shr:            ;METHOD FOR PRINTING REMIANDER IN EAX REG
        shr AX,1
        loop do_shr
        PutStr msg3
	nwln
        PutInt AX
        nwln
	pop AX
        PutStr msg4
        nwln
	mov CX,8
	sub CX,DX          ;DOING THE REVERSE PROCEDURE TO GET REMIANDER
	push CX
	loop_l:
	shl AX,1
	loop loop_l
	sub AH,AH
	pop CX
	loop_r:            ;METHOD FOR PRINTING REMIANDER IN EAX REG
	shr AX,1
	loop loop_r
	PutInt AX
	nwln
        jmp go
	invalid:
        PutStr msg5       ;CHECKING FOR VALIDITY OF DIVISOR         
        nwln
        jmp go

    go:

    .EXIT
