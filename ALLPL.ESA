@@      equ     word ptr
@       equ     byte ptr
HIGTH   equ     64000-700
LOWT    equ     700
.MODEL LARGE
.DATA
EXTRN _SEG_BUF:WORD
EXTRN _OFF_BUF:WORD


.CODE

PUBLIC _ALLPL

       _ALLPL    PROC  FAR
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
        mov     ax,_SEG_BUF
        mov     es,ax

        call    far ptr cklor         ;разрешить доступ к 1-ой битовой плоскости
        mov     ax,0a000h     ;ds:si-адрес видеобуфера
        mov     ds,ax
        mov     si,0
        mov     di,0          ;индекс записываемого массива

ap80:   cld
        lodsb                ;al-байт из видеобуфера 
        ;mov     al,@ ds:[si]
        ;inc     si
        mov     dl,10000000b  ;dl-маска
        mov     cx,8          ;8 бит в байте
ap90:
        test    al,dl
        jz      ap100         ;ничего не делаем
        cmp     di,LOWT        ;выход за нижнюю границу?
        jb      ap95          ;-да
        inc     @ es:[bx+di-1]
        inc     @ es:[bx+di-320]
        inc     @ es:[bx+di-321]
        inc     @ es:[bx+di-319]
ap95:   cmp     di,HIGTH      ;выход за верхнюю границу?
        ja      ap100         ;-да
        inc     @ es:[bx+di+1]
        inc     @ es:[bx+di+320]
        inc     @ es:[bx+di+321]
        inc     @ es:[bx+di+319]
ap100:  shr     dl,1          ;берем следующий бит
        inc     di            ;переход к след записыв байту
        loop    ap90
        cmp     si,8000
        jb      ap80

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
        _ALLPL ENDP
        
        cklor   proc far  ;аl-1 битовая плоскость
        push    dx
        push    ax
        mov     dx,3ceh
        mov     al,5
        out     dx,al
        inc     dx
        mov     al,0
        out     dx,al

        dec     dx
        mov     al,4
        out     dx,al
        inc     dx
        mov     al,0
        out     dx,al
        pop     ax
        pop     dx
        ret
        cklor   endp



END
