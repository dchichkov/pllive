@@      equ     word ptr
@       equ     byte ptr
.MODEL LARGE
.DATA      
EXTRN _SEG_BUF:WORD
EXTRN _OFF_BUF:WORD


.CODE

PUBLIC _ALLPP

       _ALLPP    PROC  FAR
        push    bp
        mov     bp,sp
        push    ds
        push    es
        push    ax
        push    bx
        push    cx
        push    dx
        push    di
        push    si
        pushf
        ;
        mov     bx,_OFF_BUF
        mov     ax,_SEG_BUF           ;es:bx - адрес полученного буфера
        mov     es,ax

        call    far ptr cklor         ;разрешить зап. во все битовые плоскости
        mov     ax,0a000h             ;ds:si-адрес видеобуфера
        mov     ds,ax
        mov     si,0
        mov     di,0          ;индекс читаемогоого массива

mt30:   mov     ah,10000000b  ;маска=10000000
        mov     cx,8          ;8 бит в байте

mt35:   mov     dl,@ es:[bx+di]
        cmp     dl,2
        jne     m10                 
        jmp     mt40

m10:    mov     al,@ ds:[si]
        cmp     dl,3
        jne     m20
        or      @ ds:[si],ah
        jmp     mt40
m20:    not     ah
        and     @ ds:[si],ah
        not     ah
mt40:   shr     ah,1
        mov     @ es:[bx+di],0
        inc     di
        loop    mt35


        inc     si
        cmp     si,8000
        jb      mt30


        popf
        pop     si
        pop     di
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        pop     es
        pop     ds
        pop     bp
        ret
        _ALLPP ENDP
        
        cklor   proc far  ;аl-1 битовая плоскость
        push    dx
        push    ax
        mov     dx,3ceh
        mov     al,5
        out     dx,al
        inc     dx
        mov     al,0
        out     dx,al

        mov     dx,3ceh
        mov     al,8
        out     dx,al
        inc     dx
        mov     al,11111111b  ;маска
        out     dx,al

        mov     dx,3c4h
        mov     al,2
        out     dx,al
        inc     dx
        mov     al,00001101b   ;цвет
        out     dx,al
        pop     ax
        pop     dx
        ret
        cklor   endp



END
