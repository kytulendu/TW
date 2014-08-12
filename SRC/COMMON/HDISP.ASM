;****************************************************************************;
; DISP.ASM  3 JAN 89      /**** MODIFIED ****/                               ;
; FOR HERCULES GRAPHIC CARD
; Updated: Kraisorn Liansee                                                  ;
; Updated: Suttipong Kanakakorn                                              ;
;          Sun  07-30-1989  18:01:20                                         ;
;          Suttipong Kanakakorn                                              ;
;          Mon  11-06-1989  20:47:39   modify leveltable to receive BALI     ;
;****************************************************************************;

PUBLIC    _hprchar
PUBLIC    _hprblank
PUBLIC    _hsetcurpos
PUBLIC    _hplot
PUBLIC    _hsetgraph
PUBLIC    _hsettext
PUBLIC    _hsavepic
PUBLIC    _hretpic

PUBLIC    _hclsall
PUBLIC    _hclsgraph
PUBLIC    _hclrline

PUBLIC    _hprakeaw

PUBLIC    _hrdchardot
PUBLIC    _hwrchardot
PUBLIC    _hgetwind
PUBLIC    _hputwind

PUBLIC    _herc_align
INCLUDE cwfnthm.asm

DGROUP           GROUP     _DATA,_BSS
_DATA            SEGMENT   WORD PUBLIC 'DATA'

EXTRN curfont:BYTE,enlargefont:BYTE,offsetfont:WORD
EXTRN chulalogo1:WORD,chulalogo2:WORD,_chardot:BYTE
extrn _dfont:byte,_ditalicfont:byte
extrn _screen_buffptr:dword

_herc_align      dw   5
graphic_table    db   35h,2dh,2eh,07h
                 db   5bh,02h,57h,57h
                 db   02h,03h,00h,00h

screenoffset     dw   90      ;row 0
                 dw   540     ;row 1
                 dw   990     ;row 2
                 dw   1440    ;row 3
                 dw   1890    ;row 4
                 dw   2340    ;row 5
                 dw   2790    ;row 6
                 dw   3240    ;row 7
                 dw   3690    ;row 8
                 dw   4140    ;row 9
                 dw   4590    ;row 10
                 dw   5040    ;row 11
                 dw   5490    ;row 12
                 dw   5940    ;row 13
                 dw   6390    ;row 14
                 dw   6840    ;row 15
                 dw   7290    ;row 16

_DATA            ENDS
_BSS             SEGMENT  WORD PUBLIC 'BSS'
_BSS             ENDS

HDISP_TEXT  SEGMENT   BYTE PUBLIC 'CODE'
           ASSUME    CS:HDISP_TEXT,DS:DGROUP
;=============================================================================;
; prchar                                                                      ;
;     print character at specified cursor position                            ;
;          ( don't forward cursor position )                                  ;
;     USAGE : prchar(unsigned c,unsigned attr,unsigned x,unsigned y)          ;
;             Attribute : bit 0 -> single underline                           ;
;                         bit 1 -> reverse                                    ;
;                         bit 2 -> bold                                       ;
;                         bit 3 -> superscript                                ;
;                         bit 4 -> subscript                                  ;
;                         bit 5 -> italic                                     ;
;                         bit 6 -> enlarge                                    ;
;                         bit 7 -> double underline                           ;
;=============================================================================;
_hprchar proc     far
        push     bp
        mov      bp,sp
        push     si
        push     di
        push     es
        mov      ax,0b000h   ; display at page 0
        mov      es,ax
; ascii value * 20 is offset in font
; we will set DS:[BX+SI] point at font
        mov      si,[bp+6]   ; get character
        and      si,00ffh    ; clear high byte
        add      si,si       ; add for word offset
        add      si,offset DGROUP:offsetfont
        mov      si,ds:[si]  ; get offset from table
        mov      al,[bp+8]   ; get attribute
        or       al,al       ; Has it attribute ?
        jnz      haveattribute
        mov      bx,offset DGROUP:_dfont
        jmp      nochangefont
; if it's attribute -> change font
haveattribute:
        test     al,020h     ; italic ?
        jz       normalfont
        mov      bx,offset DGROUP:_ditalicfont
        jmp      findnextattr
normalfont:
        mov      bx,offset DGROUP:_dfont
findnextattr:
        mov      di,offset DGROUP:curfont
        test     al,008h     ; superscript ?
        jz       testsub
        mov      word ptr ds:[di+16],0  ; clear old font
        mov      word ptr ds:[di+18],0
        sub      di,3
testsub:
        test     al,010h     ; subscript ?
        jz       transferfont
        mov      word ptr ds:[di],0     ; clear old font
        mov      word ptr ds:[di+2],0
        add      di,3
transferfont:
        mov      ax,ds:[bx+si]          ; transfer font
        mov      ds:[di],ax             ; Looping not required,
        mov      ax,ds:[bx+si+2]        ; because of speed.
        mov      ds:[di+2],ax
        mov      ax,ds:[bx+si+4]
        mov      ds:[di+4],ax
        mov      ax,ds:[bx+si+6]
        mov      ds:[di+6],ax
        mov      ax,ds:[bx+si+8]
        mov      ds:[di+8],ax
        mov      ax,ds:[bx+si+10]
        mov      ds:[di+10],ax
        mov      ax,ds:[bx+si+12]
        mov      ds:[di+12],ax
        mov      ax,ds:[bx+si+14]
        mov      ds:[di+14],ax
        mov      ax,ds:[bx+si+16]
        mov      ds:[di+16],ax
        mov      ax,ds:[bx+si+18]
        mov      ds:[di+18],ax
        mov      bx,offset DGROUP:curfont ; base table is in BX
        xor      si,si         ; ds:[bx+si] now point at font
        mov      al,[bp+8]     ; get attribute
        test     al,004h       ; bold ?
        jz       chkunderline
        mov      cx,20
loopbold:
        mov      dl,ds:[bx+si]
        shr      dl,1
        or       ds:[bx+si],dl
        inc      si
        loop     loopbold
        xor      si,si
chkunderline:
        test     al,001h     ; single underline ?
        jz       chkdoubleunderline
        mov      byte ptr ds:[bx+17],0ffh
chkdoubleunderline:
        test     al,080h     ; double underline ?
        jz       chkreverse
        mov      byte ptr ds:[bx+16],0ffh
        mov      byte ptr ds:[bx+18],0ffh
chkreverse:
        test     al,002h     ; reverse ?
        jz       chkenlarge
        mov      al,[bp+6]   ; get char
        cmp      al,0d0h
        jbe      changerev
        cmp      al,0d1h
        jbe      chkenlarge
        cmp      al,0d3h
        jbe      changerev
        cmp      al,0dah
        jbe      chkenlarge
        cmp      al,0e7h
        jb       changerev
        cmp      al,0eeh
        jbe      chkenlarge
changerev:
        mov      dx,0ffffh
        xor      ds:[bx],dx
        xor      ds:[bx+2],dx
        xor      ds:[bx+4],dx
        xor      ds:[bx+6],dx
        xor      ds:[bx+8],dx
        xor      ds:[bx+10],dx
        xor      ds:[bx+12],dx
        xor      ds:[bx+14],dx
        xor      ds:[bx+16],dx
        xor      ds:[bx+18],dx
chkenlarge:
        test     byte ptr [bp+8],040h  ;enlarge ?
        jz       nochangefont
        mov      di,offset enlargefont
        mov      cx,20
twentybyte:
        mov      dx,0
        test     byte ptr ds:[bx+si],080h
        jz       testbit6
        or       dx,0000000011000000b
testbit6:
        test     byte ptr ds:[bx+si],040h
        jz       testbit5
        or       dx,0000000000110000b
testbit5:
        test     byte ptr ds:[bx+si],020h
        jz       testbit4
        or       dx,0000000000001100b
testbit4:
        test     byte ptr ds:[bx+si],010h
        jz       testbit3
        or       dx,0000000000000011b
testbit3:
        test     byte ptr ds:[bx+si],008h
        jz       testbit2
        or       dx,1100000000000000b
testbit2:
        test     byte ptr ds:[bx+si],004h
        jz       testbit1
        or       dx,0011000000000000b
testbit1:
        test     byte ptr ds:[bx+si],002h
        jz       testbit0
        or       dx,0000110000000000b
testbit0:
        test     byte ptr ds:[bx+si],001h
        jz       nomoretest
        or       dx,0000001100000000b
nomoretest:
        mov      ds:[di],dx
        inc      si
        add      di,2
        loop     twentybyte
        mov      bx,offset DGROUP:enlargefont
        xor      si,si
nochangefont:
; we will set ES:[DI] point at screen
         mov      di,[bp+12]  ; get row
         add      di,di       ; add for word offset
         add      di,offset DGROUP:screenoffset
         mov      di,ds:[di]
         add      di,[bp+10]  ; add column
         add      di,_herc_align
; we will write character now ! (using standard code)
         mov      al,[bp+6]   ; get character
         cmp      al,0d0h
         jbe      middle_level
         cmp      al,0d1h
         jbe      abvlevel
         cmp      al,0d3h
         jbe      middle_level
         cmp      al,0d7h
         jbe      abvlevel
         cmp      al,0dah
         jbe      below_level
         cmp      al,0e6h
         jbe      middle_level
         cmp      al,0eeh
         jbe      abvlevel
         jmp      middle_level
abvlevel:
         jmp      above_level
; write below level character
; we will write last-four font only
below_level:
         test     byte ptr [bp+8],040h    ;enlarge ?
         jz       noenlargebelow
         mov      ax,ds:[bx+si+32]
         xor      es:[di+360],ax
         mov      ax,ds:[bx+si+34]
         xor      es:[di+360+2000h],ax
         mov      ax,ds:[bx+si+36]
         xor      es:[di+360+4000h],ax
         mov      ax,ds:[bx+si+38]
         xor      es:[di+360+6000h],ax
         jmp      out_write
noenlargebelow:
         mov      al,ds:[bx+si+16]
         xor      es:[di+360],al
         mov      al,ds:[bx+si+17]
         xor      es:[di+360+2000h],al
         mov      al,ds:[bx+si+18]
         xor      es:[di+360+4000h],al
         mov      al,ds:[bx+si+19]
         xor      es:[di+360+6000h],al
         jmp      out_write
; write middle level character
; we will write 12 byte only by ignore first-four & last-four font
noenlarge1:
         jmp      noenlarge
middle_level:
         test     byte ptr [bp+8],040h    ;enlarge ?
         jz       noenlarge1
         mov      ax,ds:[bx+si]
         mov      es:[di],ax
         mov      ax,ds:[bx+si+2]
         mov      es:[di+2000h],ax
         mov      ax,ds:[bx+si+4]
         mov      es:[di+4000h],ax
         mov      ax,ds:[bx+si+6]
         mov      es:[di+6000h],ax
         mov      ax,ds:[bx+si+8]
         mov      es:[di+90],ax
         mov      ax,ds:[bx+si+10]
         mov      es:[di+90+2000h],ax
         mov      ax,ds:[bx+si+12]
         mov      es:[di+90+4000h],ax
         mov      ax,ds:[bx+si+14]
         mov      es:[di+90+6000h],ax
         mov      ax,ds:[bx+si+16]
         mov      es:[di+180],ax
         mov      ax,ds:[bx+si+18]
         mov      es:[di+180+2000h],ax
         mov      ax,ds:[bx+si+20]
         mov      es:[di+180+4000h],ax
         mov      ax,ds:[bx+si+22]
         mov      es:[di+180+6000h],ax
         mov      ax,ds:[bx+si+24]
         mov      es:[di+270],ax
         mov      ax,ds:[bx+si+26]
         mov      es:[di+270+2000h],ax
         mov      ax,ds:[bx+si+28]
         mov      es:[di+270+4000h],ax
         mov      ax,ds:[bx+si+30]
         mov      es:[di+270+6000h],ax
         mov      ax,ds:[bx+si+32]
         mov      es:[di+360],ax
         mov      ax,ds:[bx+si+34]
         mov      es:[di+360+2000h],ax
         mov      ax,ds:[bx+si+36]
         mov      es:[di+360+4000h],ax
         mov      ax,ds:[bx+si+38]
         mov      es:[di+360+6000h],ax
         jmp      out_write
noenlarge:
         mov      al,ds:[bx+si]
         mov      es:[di],al
         mov      al,ds:[bx+si+1]
         mov      es:[di+2000h],al
         mov      al,ds:[bx+si+2]
         mov      es:[di+4000h],al
         mov      al,ds:[bx+si+3]
         mov      es:[di+6000h],al
         mov      al,ds:[bx+si+4]
         mov      es:[di+90],al
         mov      al,ds:[bx+si+5]
         mov      es:[di+90+2000h],al
         mov      al,ds:[bx+si+6]
         mov      es:[di+90+4000h],al
         mov      al,ds:[bx+si+7]
         mov      es:[di+90+6000h],al
         mov      al,ds:[bx+si+8]
         mov      es:[di+180],al
         mov      al,ds:[bx+si+9]
         mov      es:[di+180+2000h],al
         mov      al,ds:[bx+si+10]
         mov      es:[di+180+4000h],al
         mov      al,ds:[bx+si+11]
         mov      es:[di+180+6000h],al
         mov      al,ds:[bx+si+12]
         mov      es:[di+270],al
         mov      al,ds:[bx+si+13]
         mov      es:[di+270+2000h],al
         mov      al,ds:[bx+si+14]
         mov      es:[di+270+4000h],al
         mov      al,ds:[bx+si+15]
         mov      es:[di+270+6000h],al
         mov      al,ds:[bx+si+16]
         mov      es:[di+360],al
         mov      al,ds:[bx+si+17]
         mov      es:[di+360+2000h],al
         mov      al,ds:[bx+si+18]
         mov      es:[di+360+4000h],al
         mov      al,ds:[bx+si+19]
         mov      es:[di+360+6000h],al
         jmp      out_write
; above level has 2 level ,above-middle & topest
; above-middle level has ascii code < 0e4h
; topest level has ascii code >= 0e4h
above_level:
         cmp      al,0e6h
         jb       above_middle
         cmp      al,0edh
         jae      above_middle
         test     byte ptr [bp+8],040h    ;enlarge ?
         jz       noenlargetop
         mov      ax,ds:[bx+si]
         xor      es:[di],ax
         mov      ax,ds:[bx+si+2]
         xor      es:[di+2000h],ax
         mov      ax,ds:[bx+si+4]
         xor      es:[di+4000h],ax
         mov      ax,ds:[bx+si+6]
         xor      es:[di+6000h],ax
         jmp      out_write
noenlargetop:
         mov      al,ds:[bx+si]
         xor      es:[di],al
         mov      al,ds:[bx+si+1]
         xor      es:[di+2000h],al
         mov      al,ds:[bx+si+2]
         xor      es:[di+4000h],al
         mov      al,ds:[bx+si+3]
         xor      es:[di+6000h],al
         jmp      out_write
above_middle:
         test     byte ptr [bp+8],040h    ;enlarge ?
         jz       noenlargeabove
         mov      ax,ds:[bx+si+8]
         xor      es:[di+90],ax
         mov      ax,ds:[bx+si+10]
         xor      es:[di+90+2000h],ax
         mov      ax,ds:[bx+si+12]
         xor      es:[di+90+4000h],ax
         mov      ax,ds:[bx+si+14]
         xor      es:[di+90+6000h],ax
         jmp      out_write
noenlargeabove:
         mov      al,ds:[bx+si+4]
         xor      es:[di+90],al
         mov      al,ds:[bx+si+5]
         xor      es:[di+90+2000h],al
         mov      al,ds:[bx+si+6]
         xor      es:[di+90+4000h],al
         mov      al,ds:[bx+si+7]
         xor      es:[di+90+6000h],al
out_write:
         pop      es
         pop      di
         pop      si
         pop      bp
         ret
_hprchar  endp
;=============================================================================;
; prblank                                                                     ;
;     print blank character at specified cursor position                      ;
;          ( don't forward cursor position )                                  ;
;     USAGE : prblank(unsigned x,unsigned y)                                  ;
;=============================================================================;
_hprblank proc     far
         push     bp
         mov      bp,sp
         push     di
         push     es
         mov      ax,0b000h   ; display at page 1
         mov      es,ax
; we will set ES:[DI] point at screen
         mov      di,[bp+8]  ; get row
         add      di,di      ; add for word offset
         add      di,offset DGROUP:screenoffset
         mov      di,ds:[di]
         add      di,[bp+6]  ; add column
         add      di,_herc_align
         xor      al,al
         mov      es:[di],al
         mov      es:[di+2000h],al
         mov      es:[di+4000h],al
         mov      es:[di+6000h],al
         mov      es:[di+90],al
         mov      es:[di+90+2000h],al
         mov      es:[di+90+4000h],al
         mov      es:[di+90+6000h],al
         mov      es:[di+180],al
         mov      es:[di+180+2000h],al
         mov      es:[di+180+4000h],al
         mov      es:[di+180+6000h],al
         mov      es:[di+270],al
         mov      es:[di+270+2000h],al
         mov      es:[di+270+4000h],al
         mov      es:[di+270+6000h],al
         mov      es:[di+360],al
         mov      es:[di+360+2000h],al
         mov      es:[di+360+4000h],al
         mov      es:[di+360+6000h],al
         pop      es
         pop      di
         pop      bp
         ret
_hprblank endp
;=============================================================================;
; setcurpos                                                                   ;
;    xor cursor at specified cursor position                                  ;
;    USAGE : setcurpos(unsigned x,unsigned y,int thaimode)                    ;
;=============================================================================;
_hsetcurpos proc     far
           push     bp
           mov      bp,sp
           push     di
           push     es
           mov      di,0b000h
           mov      es,di
; we will set ES:[DI] point at screen
           mov      di,[bp+8]  ; get row
           add      di,di      ; add for word offset
           add      di,offset DGROUP:screenoffset
           mov      di,ds:[di] ; get offset of row from table
           add      di,[bp+6]  ; add column
           add      di,_herc_align
; xor 12 byte only by ignore first-four & last-four byte
           cmp      byte ptr [bp+10],1      ; thai mode ?
           jne      englishmode
           xor      byte ptr es:[di+90],0ffh
           xor      byte ptr es:[di+90+2000h],0ffh
           xor      byte ptr es:[di+90+4000h],0ffh
           xor      byte ptr es:[di+90+6000h],0ffh
           xor      byte ptr es:[di+180],0ffh
           xor      byte ptr es:[di+180+2000h],0ffh
           xor      byte ptr es:[di+180+4000h],0ffh
           xor      byte ptr es:[di+180+6000h],0ffh
           xor      byte ptr es:[di+270],0ffh
           xor      byte ptr es:[di+270+2000h],0ffh
           xor      byte ptr es:[di+270+4000h],0ffh
           xor      byte ptr es:[di+270+6000h],0ffh
           jmp      outsetcurpos
englishmode:
           xor      byte ptr es:[di+360],0ffh
           xor      byte ptr es:[di+360+2000h],0ffh
outsetcurpos:
           pop      es
           pop      di
           pop      bp
           ret
_hsetcurpos endp
;=============================================================================;
; plot                                                                        ;
;     plot dot by find position as follow                                     ;
;     find byte position from formula                                         ;
;          2000h*(Y mod 4) + 90*integer(Y/4) + integer(X/8)                   ;
;     find bit position in byte from formula                                  ;
;          7 - (x mod 8)                                                      ;
;     USAGE : plot(unsigned x,unsigned y)                                     ;
;=============================================================================;
_hplot proc     far
      push     bp
      mov      bp,sp
      push     di
      push     es
;
      mov      cl,2       ; divide by 4
      mov      ax,[bp+8]  ; get dot y
      shr      ax,cl      ; ax = integer(y/4)
      mov      bx,ax
      mov      cl,5       ; multiplied by 32
      shl      bx,cl
      sub      bx,ax      ; multiplied by 31
      sub      bx,ax      ; multiplied by 30
      sub      bx,ax      ; multiplied by 29
      sub      bx,ax      ; multiplied by 28
      sub      bx,ax      ; multiplied by 27
      sub      bx,ax      ; now multiplied by 26
      mov      cl,6       ; multiply by 64
      shl      ax,cl
      add      ax,bx      ; multiplied by 90 ( 64 + 26 )
      mov      di,ax
; Find 2000h * (y mod 4).
; Possible value is 0,2000h,4000h,6000h only.
; So we will not calculate but using comparing for speed.
      mov      al,[bp+8]  ; get dot y (low byte only)
      and      al,03h     ; al = y mod 4 (see from two last bit only)
      or       al,al
      jz       plotnext
      test     al,01h
      jz       testbit1next
      add      di,2000h
testbit1next:
      test     al,02h
      jz       plotnext
      add      di,4000h
plotnext:
      mov      ax,[bp+6]  ; get dot x
      mov      cl,3       ; divide by 8
      shr      ax,cl      ; AL = integer(x/8)
      add      di,ax      ; now DI point at byte wanted
      add      di,_herc_align
      mov      al,[bp+6]  ; get dot x
      and      al,007h    ; now , al = x mod 8
      mov      cl,7
      sub      cl,al      ; BL = 7 - (x mod 8)
      mov      bl,1
      shl      bl,cl
;
      mov      ax,0b000h
      mov      es,ax
      or       byte ptr es:[di],bl
;
      pop      es
      pop      di
      pop      bp
      ret
_hplot endp
;=============================================================================;
; set_graphic                                                                 ;
;      init 6845 CRT Controller to graphic mode                               ;
;=============================================================================;
_hsetgraph proc  far
          push  si
          push  ds
          push  es
;
          mov   dx,03bfh
          mov   al,1
          out   dx,al
;
          mov   al,002h
          mov   dx,03b8h
          out   dx,al
;
          mov   ax,DGROUP
          mov   si,offset DGROUP:graphic_table
          mov   dx,03b4h
          mov   cx,12
          xor   ah,ah
parms:
          mov   al,ah
          out   dx,al
          inc   dx
          lodsb
          out   dx,al
          inc   ah
          dec   dx
          loop  parms
;
          mov   al,00ah
          mov   dx,03b8h
          out   dx,al
;
;
; Add By Suttipong Kanakakorn (Noom)
; Set 0:465 to 0Ah as set to port 3b8h
; Very valuable for Many programs Such as DesqView, Turbo Debugger
;
          xor   si,si
          mov   ds,si
          mov   ds:[465h],00Ah
;
          pop   es
          pop   ds
          pop   si
          ret
_hsetgraph endp
;=============================================================================;
; set_text                                                                    ;
;      init 6845 CRT Controller to text mode by call BIOS routine INT 10h     ;
;=============================================================================;
_hsettext  proc  far
          mov   ax,7   ; set text mode function
          int   10h    ; vdo bios routine
          ret
_hsettext  endp
;=============================================================================;
; savepic                                                                     ;
;     save picture from screen memory page 1 to page 0                        ;
;=============================================================================;
_hsavepic   proc far
           push si
           push di
           push ds
           push es

           les  di,_screen_buffptr

           mov  ax,0b000h

           mov  ds,ax
           xor  si,si

           cld
           mov  cx,4000H
           rep  movsw

           pop  es
           pop  ds
           pop  di
           pop  si
           ret
_hsavepic   endp
;=============================================================================;
; retpic                                                                      ;
;     return picture from screen memory page 0 to page 1                      ;
;=============================================================================;
_hretpic proc far
        push si
        push di
        push ds
        push es

        mov  ax,0b000h
        mov  es,ax
        xor  di,di

        lds  si,_screen_buffptr

        cld
        mov  cx,4000H
        rep  movsw

        pop  es
        pop  ds
        pop  di
        pop  si
        ret
_hretpic endp

;=============================================================================;
; clsall                                                                      ;
;       clear screen memory page 1 to blank                                   ;
;=============================================================================;
_hclsall proc  far
        push  di
        push  es
        mov   ax,0b000h
        mov   es,ax
        xor   di,di
        mov   cx,4000h
        mov   ax,00
        cld
        rep   stosw
        pop   es
        pop   di
        ret
_hclsall endp
;=============================================================================;
; clsgraph                                                                    ;
;     clear graphic screen for window specified                               ;
; USAGE : clsgraph(int x1,int y1,int x2,int y2)                               ;
;=============================================================================;
_hclsgraph  proc  far
           push  bp
           mov   bp,sp
           push  di
           push  es
           mov   ax,0b000h
           mov   es,ax
; we will set ES:[DI] point at screen
           mov   di,[bp+8]  ; get y1
           add   di,di      ; add for word offset
           add   di,offset DGROUP:screenoffset
           mov   di,ds:[di] ; get row offset from table
           add   di,[bp+6]  ; add x1
           add   di,_herc_align
           mov   cx,[bp+12] ; get y2
           sub   cx,[bp+8]  ; sub with y1
           inc   cx         ; CX = no. of row to clear
           mov   ax,0
           mov   bx,[bp+10] ; get x2
           sub   bx,[bp+6]  ; sub with x1
           inc   bx         ; BX = no. of column to clear
clearrow:
           push  cx
           mov   cx,5
           push  di
     loopfive:
               push  cx
               push  di
               mov   cx,bx
               cld
               rep   stosb
               pop   di
;
               push  di
               add   di,2000h
               mov   cx,bx
               cld
               rep   stosb
               pop   di
;
               push  di
               add   di,4000h
               mov   cx,bx
               cld
               rep   stosb
               pop   di
;
               push  di
               add   di,6000h
               mov   cx,bx
               cld
               rep   stosb
               pop   di
;
               add   di,90
               pop   cx
               loop  loopfive
           pop  di
           add  di,450
           pop  cx
           loop clearrow
;
           pop  es
           pop  di
           pop  bp
           ret
_hclsgraph  endp
;=============================================================================;
; clrline                                                                     ;
;     clear line y1 from x1 to x2                                             ;
; USAGE : clrline(int x1,int y1,int x2)                                       ;
;=============================================================================;
_hclrline   proc  far
           push  bp
           mov   bp,sp
           push  di
           push  es
           mov   ax,0b000h
           mov   es,ax
; we will set ES:[DI] point at screen
           mov   di,[bp+8]  ; get y1
           add   di,di
           add   di,offset DGROUP:screenoffset
           mov   di,ds:[di]
           add   di,[bp+6]  ; add x1
           add   di,_herc_align
           mov   ax,0
           mov   bx,[bp+10]  ; get x2
           sub   bx,[bp+6]   ; sub with x1
           inc   bx
           mov   cx,5
           fiveloop:
                     push      cx
                     push      di
                     mov       cx,bx
                     cld
                     rep       stosb
                     pop       di
;
                     push      di
                     add       di,2000h
                     mov       cx,bx
                     cld
                     rep       stosb
                     pop       di
;
                     push      di
                     add       di,4000h
                     mov       cx,bx
                     cld
                     rep       stosb
                     pop       di
;
                     push      di
                     add       di,6000h
                     mov       cx,bx
                     cld
                     rep       stosb
                     pop       di
;
                     add       di,90
                     pop       cx
                     loop      fiveloop
           pop   es
           pop   di
           pop   bp
           ret
_hclrline   endp
;=============================================================================;
; prakeaw                                                                     ;
;       write parkeaw at upper left cornor                                    ;
;=============================================================================;
_hprakeaw proc  far
         push  si
         push  di
         push  es
         mov   si,0b000h
         mov   es,si
         mov   si,offset DS:chulalogo1
         mov   di,_herc_align
         inc   di
         mov   ax,ds:[si]
         mov   es:[di+4000h],ax
         mov   ax,ds:[si+2]
         mov   es:[di+6000h],ax
;
         mov   ax,ds:[si+4]
         mov   es:[di+90],ax
         mov   ax,ds:[si+6]
         mov   es:[di+90+2000h],ax
         mov   ax,ds:[si+8]
         mov   es:[di+90+4000h],ax
         mov   ax,ds:[si+10]
         mov   es:[di+90+6000h],ax
;
         mov   ax,ds:[si+12]
         mov   es:[di+180],ax
         mov   ax,ds:[si+14]
         mov   es:[di+180+2000h],ax
         mov   ax,ds:[si+16]
         mov   es:[di+180+4000h],ax
         mov   ax,ds:[si+18]
         mov   es:[di+180+6000h],ax
;
         mov   ax,ds:[si+20]
         mov   es:[di+270],ax
         mov   ax,ds:[si+22]
         mov   es:[di+270+2000h],ax
         mov   ax,ds:[si+24]
         mov   es:[di+270+4000h],ax
         mov   ax,ds:[si+26]
         mov   es:[di+270+6000h],ax
;
         mov   ax,ds:[si+28]
         mov   es:[di+360],ax
         mov   ax,ds:[si+30]
         mov   es:[di+360+2000h],ax
         mov   ax,ds:[si+32]
         mov   es:[di+360+4000h],ax
         mov   ax,ds:[si+34]
         mov   es:[di+360+6000h],ax
;
         mov   ax,ds:[si+36]
         mov   es:[di+450],ax
         mov   ax,ds:[si+38]
         mov   es:[di+450+2000h],ax
;
         mov   si,offset DS:chulalogo2
         mov   di,3
         add   di,_herc_align
         mov   ax,ds:[si]
         mov   es:[di+4000h],ax
         mov   ax,ds:[si+2]
         mov   es:[di+6000h],ax
;
         mov   ax,ds:[si+4]
         mov   es:[di+90],ax
         mov   ax,ds:[si+6]
         mov   es:[di+90+2000h],ax
         mov   ax,ds:[si+8]
         mov   es:[di+90+4000h],ax
         mov   ax,ds:[si+10]
         mov   es:[di+90+6000h],ax
;
         mov   ax,ds:[si+12]
         mov   es:[di+180],ax
         mov   ax,ds:[si+14]
         mov   es:[di+180+2000h],ax
         mov   ax,ds:[si+16]
         mov   es:[di+180+4000h],ax
         mov   ax,ds:[si+18]
         mov   es:[di+180+6000h],ax
;
         mov   ax,ds:[si+20]
         mov   es:[di+270],ax
         mov   ax,ds:[si+22]
         mov   es:[di+270+2000h],ax
         mov   ax,ds:[si+24]
         mov   es:[di+270+4000h],ax
         mov   ax,ds:[si+26]
         mov   es:[di+270+6000h],ax
;
         mov   ax,ds:[si+28]
         mov   es:[di+360],ax
         mov   ax,ds:[si+30]
         mov   es:[di+360+2000h],ax
         mov   ax,ds:[si+32]
         mov   es:[di+360+4000h],ax
         mov   ax,ds:[si+34]
         mov   es:[di+360+6000h],ax
;
         mov   ax,ds:[si+36]
         mov   es:[di+450],ax
         mov   ax,ds:[si+38]
         mov   es:[di+450+2000h],ax
         pop   es
         pop   di
         pop   si
         ret
_hprakeaw endp


_hrdchardot proc     far
           push     bp
           mov      bp,sp
           push     si
           push     di
           push     es
           mov      ax,0b000h   ; display at page 1
           mov      es,ax
; we will set ES:[DI] point at screen
           mov      di,[bp+8]  ; get row
           add      di,di       ; add for word offset
           add      di,offset DGROUP:screenoffset
           mov      di,ds:[di]
           add      di,_herc_align
           add      di,[bp+6]  ; add column
           mov      si,offset DGROUP:_chardot
           mov      al,es:[di]
           mov      ds:[si],al
           mov      al,es:[di+2000h]
           mov      ds:[si+1],al
           mov      al,es:[di+4000h]
           mov      ds:[si+2],al
           mov      al,es:[di+6000h]
           mov      ds:[si+3],al
           mov      al,es:[di+90]
           mov      ds:[si+4],al
           mov      al,es:[di+90+2000h]
           mov      ds:[si+5],al
           mov      al,es:[di+90+4000h]
           mov      ds:[si+6],al
           mov      al,es:[di+90+6000h]
           mov      ds:[si+7],al
           mov      al,es:[di+180]
           mov      ds:[si+8],al
           mov      al,es:[di+180+2000h]
           mov      ds:[si+9],al
           mov      al,es:[di+180+4000h]
           mov      ds:[si+10],al
           mov      al,es:[di+180+6000h]
           mov      ds:[si+11],al
           mov      al,es:[di+270]
           mov      ds:[si+12],al
           mov      al,es:[di+270+2000h]
           mov      ds:[si+13],al
           mov      al,es:[di+270+4000h]
           mov      ds:[si+14],al
           mov      al,es:[di+270+6000h]
           mov      ds:[si+15],al
           mov      al,es:[di+360]
           mov      ds:[si+16],al
           mov      al,es:[di+360+2000h]
           mov      ds:[si+17],al
           mov      al,es:[di+360+4000h]
           mov      ds:[si+18],al
           mov      al,es:[di+360+6000h]
           mov      ds:[si+19],al
           pop      es
           pop      di
           pop      si
           pop      bp
           ret
_hrdchardot endp

_hwrchardot proc     far
           push     bp
           mov      bp,sp
           push     si
           push     di
           push     es
           mov      ax,0b000h   ; display at page 1
           mov      es,ax
; we will set ES:[DI] point at screen
           mov      di,[bp+8]  ; get row
           add      di,di       ; add for word offset
           add      di,offset DGROUP:screenoffset
           mov      di,ds:[di]
           add      di,_herc_align
           add      di,[bp+6]  ; add column
           mov      si,offset DGROUP:_chardot
           mov      al,ds:[si]
           mov      es:[di],al
           mov      al,ds:[si+1]
           mov      es:[di+2000h],al
           mov      al,ds:[si+2]
           mov      es:[di+4000h],al
           mov      al,ds:[si+3]
           mov      es:[di+6000h],al
           mov      al,ds:[si+4]
           mov      es:[di+90],al
           mov      al,ds:[si+5]
           mov      es:[di+90+2000h],al
           mov      al,ds:[si+6]
           mov      es:[di+90+4000h],al
           mov      al,ds:[si+7]
           mov      es:[di+90+6000h],al
           mov      al,ds:[si+8]
           mov      es:[di+180],al
           mov      al,ds:[si+9]
           mov      es:[di+180+2000h],al
           mov      al,ds:[si+10]
           mov      es:[di+180+4000h],al
           mov      al,ds:[si+11]
           mov      es:[di+180+6000h],al
           mov      al,ds:[si+12]
           mov      es:[di+270],al
           mov      al,ds:[si+13]
           mov      es:[di+270+2000h],al
           mov      al,ds:[si+14]
           mov      es:[di+270+4000h],al
           mov      al,ds:[si+15]
           mov      es:[di+270+6000h],al
           mov      al,ds:[si+16]
           mov      es:[di+360],al
           mov      al,ds:[si+17]
           mov      es:[di+360+2000h],al
           mov      al,ds:[si+18]
           mov      es:[di+360+4000h],al
           mov      al,ds:[si+19]
           mov      es:[di+360+6000h],al
           pop      es
           pop      di
           pop      si
           pop      bp
           ret
_hwrchardot endp


;------------------------------------------------------
;  Fic_getwind routine
;
;      fic_getwind (x1,y1,linecount,bytecount,buffptr);
;
;
;        copy window area at x1,y1 (left-top)
;             size = linecount * bytecount
;        to buffer area
;------------------------------------------------------



     fic_getwind_stack    struc

                          dw    5 dup (?)    ;five regs saved
                          dd    ?            ;return address

     x1_9                 dw    ?
     y1_9                 dw    ?
     linecount_9          dw    ?
     bytecount_9          dw    ?
     buffptr_9            dd    ?

     fic_getwind_stack    ends


   _hgetwind              proc far
                          push bp
                          push ds
                          push es
                          push si
                          push di
                          mov bp,sp

                          mov   di,[bp].y1_9
                          add   di,di
                          add   di,offset DGROUP:screenoffset
                          mov   ax,ds:[di]
                          add   ax,[bp].x1_9
                          add   ax,_herc_align

                          mov bx,ax
                          mov ax,0b000H
                          mov ds,ax
                          les di,[bp].buffptr_9

                          cld
   scanline_loop9:        dec [bp].linecount_9
                          js end_getwind9
                          mov si,bx
                          mov cx,[bp].bytecount_9
                          rep movsb
			  shift_down bx
                          jmp short scanline_loop9
   end_getwind9:          pop di
                          pop si
                          pop es
                          pop ds
                          pop bp
                          ret
   _hgetwind              endp


;------------------------------------------------------
;  Fic_putwind routine
;
;      fic_putwind (x1,y1,linecount,bytecount,buffptr);
;
;
;        copy window area at x1,y1 (left-top)
;             size = linecount * bytecount
;        from buffer area
;------------------------------------------------------



     fic_putwind_stack    struc

                          dw    5 dup (?)    ;five regs saved
                          dd    ?            ;return address

     x1_10                dw    ?
     y1_10                dw    ?
     linecount_10         dw    ?
     bytecount_10         dw    ?
     buffptr_10           dd    ?

     fic_putwind_stack    ends


   _hputwind              proc far
                          push bp
                          push ds
                          push es
                          push si
                          push di
                          mov bp,sp

                          mov   di,[bp].y1_10
                          add   di,di
                          add   di,offset DGROUP:screenoffset
                          mov   ax,ds:[di]
                          add   ax,[bp].x1_10
                          add   ax,_herc_align

                          mov bx,ax
                          mov ax,0b000h
                          mov es,ax
                          lds si,[bp].buffptr_10

                          cld
   scanline_loop10:       dec [bp].linecount_10
                          js end_putwind10
                          mov di,bx
                          mov cx,[bp].bytecount_10
                          rep movsb
			  shift_down bx
                          jmp short scanline_loop10
   end_putwind10:         pop di
                          pop si
                          pop es
                          pop ds
                          pop bp
                          ret
   _hputwind              endp

HDISP_TEXT ENDS
          END
