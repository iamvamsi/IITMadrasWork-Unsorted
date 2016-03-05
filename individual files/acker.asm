;*********************************************************************
;		AUTHOR VAMSIKRISHNAD
;		ROLL NO.CS09B006
;		Ackermann Function
;		DATE:17-MAR-11
;**********************************************************************  
%include"io.mac"
.DATA
    msg1 db "Enter the value of m :",0
    msg2 db "Enter the value of n :",0
    msg3 db "The value of Ackermann function is A(m,n) : ",0
.UDATA
    
.CODE
    .STARTUP
    sub eax,eax
    sub ebx,ebx
    PutStr msg1       ;prompting user for value of m.....
    nwln
    GetInt ax
    PutStr msg2       ;prompting user for value of n.........
    nwln
    GetInt bx
    sub edx,edx
    call Acek         ;calling ackermann function recusivley
    PutStr msg3
    nwln
    PutLInt edx       ;printing the final result 
    nwln
    .EXIT
    Acek:
        
        cmp eax,0        ;comparing eax with 0...............
        je rec1           ;............if equal goto rec1
        jmp level
        rec1:
            mov edx,ebx
            add edx,1        ;return  ebx+1(n+1) 
            ret
  level:
        cmp ebx,0        ;comparing ebx with 0...............
        je rec2              ;..........if equal goto rec2
        jmp rec3
        rec2:
            sub eax,1
            mov ebx,1
            call Acek         ;return acek(m-1,1)
            ret
        rec3:
            sub ebx,1   ;if both m,n are greater than 0
            push eax
            call Acek      ;acker(m,n-1)
            pop eax
            sub eax,1
            mov ebx,edx
            call Acek      ;acker(m-1,acker(m,n-1))
            ret
