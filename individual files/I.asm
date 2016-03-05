;*********************************************************************
;		AUTHOR VAMSIKRISHNAD
;		ROLL NO.CS09B006
;		GetChar stimulator
;		DATE:31-MAR-11
;********************************************************************** 

%include"io.mac"
%include"keyboard.asm"


.DATA
 out_fn_prompt db "enter the output file name: ",0
 out_file_err_msg db "Output file error",0
 prompt_term_char db "enter the terminating character:",0
 
.UDATA
 in_file_name resb 30
 out_file_name resb 30
 fd_in       resd 1
 fd_out      resd 1
 in_buf      resb 1
 term_char  resb 1
.CODE
 .STARTUP
 
 PutStr prompt_term_char   	  ;GETTING TERMINATING CHARECTER......
 GetCh [term_char]


 PutStr out_fn_prompt             ;GETTING OUTPUT FILE NAME......
 GetStr out_file_name,30
 
 
 call canonical_off               ;DISABLING CANONICAL MODULE

create_file:                      ;CREATING AND OPENING THE OUTPUT FILE........ 
 mov EAX,8
 mov EBX,out_file_name
 mov ECX,0777
 
 int 0x80                         ;..........USING SYSTEM CALL

 mov [fd_out],EAX
 cmp EAX,0                        ;CHECKING FOR ERROR IN CREATING AND OPENING 
 jge do_this
 PutStr out_file_err_msg          ;.........THE FILE
 nwln
 jmp done

do_this:                          ;LOOP TO WRITE TO OUTPUT FILE.............
  mov ECX,80
  repeat_read:
  push ECX
  mov EAX,3                           ;READING FROM STDIN FILE....
  mov EBX,0
  mov ECX,in_buf
  mov EDX,1
  int 0x80                            ;........USING SYSTEM CALL 3
  mov EDX,EAX
    			
  mov AL,[term_char]              ;CHECKING FOR TERMINATING CHARECTER   
  cmp AL,[in_buf]
  je length			  ; IF IT IS EQUAL THEN EXIT
  
  mov EAX,4                       ; WRITING  TO FILE
  mov EBX,[fd_out]
  mov ECX,in_buf	
  
  int 0x80                        ;....................

  pop ECX
  
loop repeat_read                  ;.............................................

call canonical_on
length_80:                        ;PRINTING LENGTH ON TO OUTPUTFILE
	mov byte[in_buf],8
	mov EAX,4
	mov EBX,[fd_out]
	mov ECX,in_buf
	int 0x80
	mov byte[in_buf],0
	int 0x80
jmp closing
length:
	pop ECX
	mov EAX,ECX
	mov ECX,80
	sub ECX,EAX
	mov EAX,ECX
	PutLInt EAX
	mov CL,10
	div CL
	add AL,48
	add AH,48
	mov byte[in_buf],AH
	mov EAX,4
	mov EBX,[fd_out]
	mov ECX,in_buf
	int 0x80
	mov byte[in_buf],AL
	int 0x80

closing:
  
  mov EAX,6
  mov EBX,[fd_out]

done:
  call canonical_on
 
  .EXIT
