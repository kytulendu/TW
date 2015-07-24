;****************************************************************************;
; EGAVGA.ASM                                                                 ;
;                                                                            ;
; 3 JAN 1989                                                                 ;
; EGA/VGA/MCGA Graphic Card Driver                                           ;
;****************************************************************************;

INCLUDE cwfntm.asm

	DGROUP		GROUP _DATA, _BSS

	_DATA		SEGMENT WORD PUBLIC 'DATA'

EXTRN _dfont:byte, _ditalicfont:byte
EXTRN _curfont:BYTE, _enlargefont:BYTE, _fontoffset:WORD
EXTRN _chulalogo1:WORD, _chulalogo2:WORD
EXTRN _screen_buffptr:dword

EGA_Address     dw   0A000h           ; Beginning of EGA/VGA/MCGA frame buffer

	_DATA		ENDS

	_BSS		SEGMENT WORD PUBLIC 'BSS'
	_BSS		ENDS

EGAVGA_TEXT		SEGMENT BYTE PUBLIC 'CODE'
				ASSUME CS:EGAVGA_TEXT, DS:DGROUP

EXTRN _ega_offset:far

;=============================================================================;
; _ega_prchar                                                                 ;
;     Put a character with attribute at given position.                       ;
; Usage :                                                                     ;
; ega_prchar( unsigned char p_char, int p_attr, int p_x, int p_y )            ;
;  \param[in]  p_char			Character.                                    ;
;  \param[in]  p_attr			Attribute.                                    ;
;                                   bit 0 -> single underline                 ;
;                                   bit 1 -> reverse                          ;
;                                   bit 2 -> bold                             ;
;                                   bit 3 -> superscript                      ;
;                                   bit 4 -> subscript                        ;
;                                   bit 5 -> italic                           ;
;                                   bit 6 -> enlarge                          ;
;                                   bit 7 -> double underline                 ;
;  \param[in]  p_x				Horizontal position.                          ;
;  \param[in]  p_y				Vertical position.                            ;
;=============================================================================;
	PUBLIC _ega_prchar
_ega_prchar PROC FAR
	PUSH    BP
	PUSH    SI
	PUSH    DI
	PUSH    ES
	MOV     BP,SP

; ASCII value * 20 is offset in font
; we will set DS:[BX+SI] point at font
	MOV     SI,[BP+12]                  ; get character
	AND     SI,00FFh                    ; clear high byte
	ADD     SI,SI                       ; add for word offset
	ADD     SI,OFFSET DGROUP:_fontoffset
	MOV     SI,DS:[SI]                  ; get offset from table
	MOV     AL,[BP+14]                  ; get attribute
	OR      AL,AL                       ; Has it have attribute ?
	JNZ     haveattribute
	MOV     BX,OFFSET DGROUP:_dfont
	JMP     nochangefont

; if it's attribute -> change font
haveattribute:
	TEST    AL,020h                     ; italic ?
	JZ      normalfont
	MOV     BX,OFFSET DGROUP:_ditalicfont
	JMP     findnextattr

normalfont:
	MOV     BX,OFFSET DGROUP:_dfont

findnextattr:
	MOV     DI,OFFSET DGROUP:_curfont
	TEST    AL,008h                     ; superscript ?
	JZ      testsub
	MOV     WORD PTR DS:[DI+16],0       ; clear old font
	MOV     WORD PTR DS:[DI+18],0
	SUB     DI,3

testsub:
	TEST    AL,010h                     ; subscript ?
	JZ      transferfont
	MOV     WORD PTR DS:[DI],0          ; clear old font
	MOV     WORD PTR DS:[DI+2],0
	ADD     DI,3

transferfont:
	MOV     AX,DS:[BX+SI]               ; transfer font
	MOV     DS:[DI],AX                  ; Looping not required,
	MOV     AX,DS:[BX+SI+2]             ; because of speed.
	MOV     DS:[DI+2],AX
	MOV     AX,DS:[BX+SI+4]
	MOV     DS:[DI+4],AX
	MOV     AX,DS:[BX+SI+6]
	MOV     DS:[DI+6],AX
	MOV     AX,DS:[BX+SI+8]
	MOV     DS:[DI+8],AX
	MOV     AX,DS:[BX+SI+10]
	MOV     DS:[DI+10],AX
	MOV     AX,DS:[BX+SI+12]
	MOV     DS:[DI+12],AX
	MOV     AX,DS:[BX+SI+14]
	MOV     DS:[DI+14],AX
	MOV     AX,DS:[BX+SI+16]
	MOV     DS:[DI+16],AX
	MOV     AX,DS:[BX+SI+18]
	MOV     DS:[DI+18],AX
	MOV     BX,OFFSET DGROUP:_curfont   ; base table is in BX
	XOR     SI,SI                       ; DS:[BX+SI] now point at font
	MOV     AL,[BP+14]                  ; get attribute
	TEST    AL,004h                     ; bold ?
	JZ      chkunderline
	MOV     CX,20

loopbold:
	MOV     DL,DS:[BX+SI]
	SHR     DL,1
	OR      DS:[BX+SI],DL
	INC     SI
	LOOP    loopbold
	XOR     SI,SI

chkunderline:
	TEST    AL,001H                     ; single underline ?
	JZ      chkdoubleunderline
	MOV     BYTE PTR DS:[BX+17],0FFh

chkdoubleunderline:
	TEST    AL,080H                     ; double underline ?
	JZ      chkreverse
	MOV     BYTE PTR DS:[BX+16],0FFh
	MOV     BYTE PTR DS:[BX+18],0FFh

chkreverse:
	TEST    AL,002h                     ; reverse ?
	JZ      chkenlarge
	MOV     AL,[BP+12]                  ; get char
	CMP     AL,0D0h
	JBE     changerev
	CMP     AL,0D1h
	JBE     chkenlarge
	CMP     AL,0D3h
	JBE     changerev
	CMP     AL,0DAh
	JBE     chkenlarge
	CMP     AL,0E7h
	JB      changerev
	CMP     AL,0EEh
	JBE     chkenlarge

changerev:
	MOV     DX,0FFFFh
	XOR     DS:[BX],DX
	XOR     DS:[BX+2],DX
	XOR     DS:[BX+4],DX
	XOR     DS:[BX+6],DX
	XOR     DS:[BX+8],DX
	XOR     DS:[BX+10],DX
	XOR     DS:[BX+12],DX
	XOR     DS:[BX+14],DX
	XOR     DS:[BX+16],DX
	XOR     DS:[BX+18],DX

chkenlarge:
	TEST    BYTE PTR [BP+14],040h       ; enlarge ?
	JZ      nochangefont
	MOV     DI,OFFSET _enlargefont
	MOV     CX,20

twentybyte:
	MOV     DX,0
	TEST    BYTE PTR DS:[BX+SI],080h
	JZ      testbit6
	OR      DX,0000000011000000b

testbit6:
	TEST    BYTE PTR DS:[BX+SI],040h
	JZ      testbit5
	OR      DX,0000000000110000b

testbit5:
	TEST    BYTE PTR DS:[BX+SI],020h
	JZ      testbit4
	OR      DX,0000000000001100b

testbit4:
	TEST    BYTE PTR DS:[BX+SI],010h
	JZ      testbit3
	OR      DX,0000000000000011b

testbit3:
	TEST    BYTE PTR DS:[BX+SI],008h
	JZ      testbit2
	OR      DX,1100000000000000b

testbit2:
	TEST    BYTE PTR DS:[BX+SI],004h
	JZ      testbit1
	OR      DX,0011000000000000b

testbit1:
	TEST    BYTE PTR DS:[BX+SI],002h
	JZ      testbit0
	OR      DX,0000110000000000b

testbit0:
	TEST    BYTE PTR DS:[BX+SI],001h
	JZ      nomoretest
	OR      DX,0000001100000000b

nomoretest:
	MOV     DS:[DI],DX
	INC     SI
	ADD     DI,2
	LOOP    twentybyte
	MOV     BX,OFFSET DGROUP:_enlargefont
	XOR     SI,SI

nochangefont:
; we will set ES:[DI] point at screen
; we will write character now ! (using standard code)
	MOV     AL,[BP+12]                  ; get character
	CMP     AL,0D0h
	JA      cont1
	JMP     middle_level
cont1:
	CMP     AL,0D1h
	JBE     abvlevel
	CMP     AL,0D3h
	JA      cont2
	jmp     middle_level
cont2:
	CMP     AL,0D7h
	JBE     abvlevel
	CMP     AL,0DAh
	JBE     below_level
	CMP     AL,0E6h
	JA      cont3
	JMP     middle_level
cont3:
	CMP     al,0EEh
	JBE     abvlevel
	JMP     middle_level

abvlevel:
	JMP     above_level

; write below level character
; we will write last-four font only
below_level:
	MOV     AX,[BP+18]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,16+4                     ; down 16 lines
	PUSH    AX
	XOR     AX,AX
	PUSH    AX
	MOV     DI,BX                       ; save in register variable

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column

	MOV     ES,EGA_Address

	TEST    BYTE PTR [BP+14],040h       ; enlarge ?
	JZ      noenlargebelow

	MOV     AX,DS:[BX+SI+32]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+34]
	XOR     ES:[DI],AX
	MOV     AX,DS:[BX+SI+36]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+38]
	XOR     ES:[DI],AX

	JMP     out_write

noenlargebelow:
	MOV     AL,DS:[BX+SI+16]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+17]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+18]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+19]
	XOR     ES:[DI],AL
	JMP     out_write

; write middle level character
; we will write 12 byte only by ignore first-four & last-four font
noenlarge1:
	JMP     noenlarge

middle_level:
	MOV     AX,[BP+18]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX
	MOV     DI,BX                       ; save in register variable

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column

	MOV     ES,EGA_Address

	TEST    BYTE PTR [BP+14],040h       ; enlarge ?
	JZ      noenlarge1

	MOV     AX,DS:[BX+SI]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+2]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+4]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+6]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+8]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+10]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+12]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+14]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+16]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+18]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+20]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+22]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+24]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+26]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+28]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+30]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+32]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+34]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+36]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+38]
	MOV     ES:[DI],AX

	JMP     out_write
noenlarge:
	MOV     AL,DS:[BX+SI]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+1]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+2]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+3]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+4]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+5]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+6]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+7]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+8]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+9]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+10]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+11]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+12]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+13]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+14]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+15]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+16]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+17]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+18]
	MOV     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+19]
	MOV     ES:[DI],AL

	JMP     out_write

; above level has 2 level, above-middle & topest
; above-middle level has ASCII code < 0E4h
; topest level has ASCII code >= 0E4h
above_level:
	CMP     AL,0E6h
	JB      above_middle
	CMP     AL,0EDh
	JAE     above_middle

	MOV     AX,[BP+18]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX
	MOV     DI,BX                       ; save in register variable

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column

	MOV     ES,EGA_Address

	TEST    BYTE PTR [BP+14],040h       ; enlarge ?
	JZ      noenlargetop

	MOV     AX,DS:[BX+SI]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+2]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+4]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+6]
	XOR     ES:[DI],AX

	JMP     out_write

noenlargetop:
	MOV     AL,DS:[BX+SI]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+1]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+2]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+3]
	XOR     ES:[DI],AL

	JMP     out_write

above_middle:
	MOV     AX,[BP+18]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4+4                      ; down 4 lines
	PUSH    AX
	XOR     AX,AX
	PUSH    AX
	MOV     DI,BX                       ; save in register variable

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column

	MOV     ES,EGA_Address

	TEST    BYTE PTR [BP+14],040h       ; enlarge ?
	JZ      noenlargeabove

	MOV     AX,DS:[BX+SI+8]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+10]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+12]
	XOR     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[BX+SI+14]
	XOR     ES:[DI],AX
	JMP     out_write

noenlargeabove:
	MOV     AL,DS:[BX+SI+4]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+5]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+6]
	XOR     ES:[DI],AL
	shift_down DI
	MOV     AL,DS:[BX+SI+7]
	XOR     ES:[DI],AL

out_write:
	POP     ES
	POP     DI
	POP     SI
	POP     BP
	RET

_ega_prchar ENDP

;=============================================================================;
; _ega_prblank                                                                ;
;     Put a blank character at given position.                                ;
; Usage :                                                                     ;
; _ega_prblank( int p_x, int p_y )                                            ;
;  \param[in]  p_x				Horizontal position.                          ;
;  \param[in]  p_y				Vertical position.                            ;
;=============================================================================;
	PUBLIC _ega_blank
_ega_blank PROC FAR
	PUSH    BP
	PUSH    DI
	PUSH    ES
	MOV     BP,SP

; we will set ES:[DI] point at screen
	MOV     AX,[BP+12]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	ADD     DI,[BP+10]                  ; add column
	MOV     ES,EGA_Address

	XOR     AL,AL
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL
	shift_down DI
	MOV     ES:[DI],AL

	POP     ES
	POP     DI
	POP     BP
	RET

_ega_blank ENDP

;=============================================================================;
; _ega_setcurpos                                                              ;
;     XOR cursor at specified cursor position.                                ;
; Usage :                                                                     ;
; _ega_setcurpos( int p_x, int p_y, int p_thaimode )                          ;
;  \param[in]  p_x				Horizontal position.                          ;
;  \param[in]  p_y				Vertical position.                            ;
;  \param[in]  p_thaimode		Thai/English mode.                            ;
;=============================================================================;
	PUBLIC _ega_setcurpos
_ega_setcurpos PROC FAR
	PUSH    BP
	PUSH    DI
	PUSH    ES
	MOV     BP,SP

; we will set ES:[DI] point at screen
; xor 12 byte only by ignore first-four & last-four byte
	CMP     BYTE PTR [BP+14],1          ; thai mode ?
	JE      thaimode
	JMP     englishmode

thaimode:
	MOV     AX,[BP+12]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4+4                      ; down 4 lines
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	ADD     DI,[BP+10]                  ; add column
	MOV     ES,EGA_Address

	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	JMP     outsetcurpos

englishmode:
	MOV     AX,[BP+12]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,16+4                     ; down 16 lines + 4 align for factor
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	ADD     DI,[BP+10]                  ; add column
	MOV     ES,EGA_Address

	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh

outsetcurpos:
	POP     ES
	POP     DI
	POP     BP
	RET

_ega_setcurpos ENDP

;=============================================================================;
; _ega_clsgraph                                                               ;
;     Clear graphic screen for window specified.                              ;
; Usage :                                                                     ;
; _ega_clsgraph( int p_xStart, int p_yStart, int p_xEnd, int p_yEnd )         ;
;  \param[in]  p_xStart			Vertical position of start point.             ;
;  \param[in]  p_yStart			Horizontal position of start point.           ;
;  \param[in]  p_xEnd			Vertical position of end point.               ;
;  \param[in]  p_yEnd			Horizontal position of end point.             ;
;=============================================================================;
	PUBLIC _ega_clsgraph
_ega_clsgraph PROC FAR
	PUSH    BP
	PUSH    DI
	PUSH    ES
	MOV     BP,SP

; we will set ES:[DI] point at screen
	MOV     AX,[BP+12]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	MOV     ES,EGA_Address


	ADD     DI,[BP+10]                  ; ADD x1
	MOV     CX,[BP+16]                  ; get y2
	SUB     CX,[BP+12]                  ; SUB with y1
	INC     CX                          ; CX = no. of row to clear
	MOV     AX,CX
	MOV     CL,20
	MUL     CL
	MOV     CX,AX
	XOR     AX,AX

	MOV     BX,[BP+14]                  ; get x2
	SUB     BX,[BP+10]                  ; sub with x1
	INC     BX                          ; BX = no. of column to clear
	MOV     DX,CX                       ; DX = no of lines
	CLD

clearrow:
	DEC     DX
	JS      endclsgraph

	PUSH    DI
	MOV     CX,BX
	REP     STOSB
	POP     DI
	shift_down DI
	JMP     clearrow

endclsgraph:
	POP     ES
	POP     DI
	POP     BP
	RET

_ega_clsgraph  ENDP

;=============================================================================;
; _ega_clrline                                                                ;
;     Clear graphic screen for window specified.                              ;
; Usage :                                                                     ;
; _ega_clrline( int p_x1, int p_y1, int p_x2 )                                ;
;=============================================================================;
	PUBLIC _ega_clrline
_ega_clrline PROC FAR
	PUSH    BP
	PUSH    DI
	PUSH    ES
	MOV     BP,SP

; we will set ES:[DI] point at screen
	MOV     AX,[BP+12]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	MOV     ES,EGA_Address

	ADD     DI,[BP+10]                  ; ADD x1
	MOV     AX,0
	MOV     BX,[BP+14]                  ; get x2
	SUB     BX,[BP+10]                  ; SUB with x1
	INC     BX                          ; BX = number of bytes

	MOV     DX,20
	CLD

clearline:
	DEC     DX
	JS      endclearline

	PUSH    DI
	MOV     CX,BX
	REP     STOSB
	POP     DI
	shift_down DI
	JMP     clearline

endclearline:
	POP     ES
	POP     DI
	POP     BP
	RET

_ega_clrline ENDP

;=============================================================================;
; _ega_prakeaw                                                                ;
;     Display Prakeaw ( Chula University logo ) at top-left of screen.        ;
; Usage :                                                                     ;
; _ega_prakeaw( )                                                             ;
;=============================================================================;
	PUBLIC _ega_prakeaw
_ega_prakeaw PROC FAR
	PUSH    BP
	MOV     BP,SP
	PUSH    SI
	PUSH    DI
	PUSH    ES

	MOV     ES,EGA_Address

	MOV     SI,OFFSET DS:_chulalogo1
	MOV     DI,1
	shift_down DI
	shift_down DI
	MOV     AX,DS:[SI]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+2]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+4]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+6]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+8]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+10]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+12]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+14]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+16]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+18]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+20]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+22]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+24]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+26]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+28]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+30]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+32]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+34]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+36]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+38]
	MOV     ES:[DI],AX

	MOV     SI,OFFSET DS:_chulalogo2
	MOV     DI,3
	shift_down DI
	shift_down DI
	MOV     AX,DS:[SI]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+2]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+4]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+6]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+8]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+10]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+12]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+14]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+16]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+18]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+20]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+22]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+24]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+26]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+28]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+30]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+32]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+34]
	MOV     ES:[DI],AX
	shift_down DI

	MOV     AX,DS:[SI+36]
	MOV     ES:[DI],AX
	shift_down DI
	MOV     AX,DS:[SI+38]
	MOV     ES:[DI],AX

	POP     ES
	POP     DI
	POP     SI
	POP     BP
	RET

_ega_prakeaw ENDP

;------------------------------------------------------
; fic_getwind(x1, y1, linecount, bytecount, buffptr)
;
;      copy window area at x1, y1 (left-top)
;    size = linecount * bytecount
;    to buffer area
;------------------------------------------------------

fic_getwind_stack STRUC

					dw    5 dup (?)     ; five regs saved
					dd    ?             ; return address

	x1_9            dw    ?
	y1_9            dw    ?
	linecount_9     dw    ?
	bytecount_9     dw    ?
	buffptr_9       dd    ?

fic_getwind_stack ENDS

	PUBLIC _ega_getwind
_ega_getwind PROC FAR
	PUSH    BP
	PUSH    DS
	PUSH    ES
	PUSH    SI
	PUSH    DI
	MOV     BP,SP

	MOV     AX,[BP].y1_9                ; offset of source window
	MOV     BL,20
	MUL     BL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	ADD     AX,[BP].x1_9
	MOV     BX,AX
	MOV     DS,EGA_Address
	LES     DI,[BP].buffptr_9

	CLD

scanline_loop9:
	DEC     [BP].linecount_9
	JS      end_getwind9
	MOV     SI,BX
	MOV     CX,[BP].bytecount_9
	REP     MOVSB
	shift_down BX
	JMP     scanline_loop9

end_getwind9:
	POP     DI
	POP     SI
	POP     ES
	POP     DS
	POP     BP
	RET

_ega_getwind ENDP

;------------------------------------------------------
; fic_putwind(x1, y1, linecount, bytecount, buffptr)
;
;      copy window area at x1, y1 (left-top)
;    size = linecount * bytecount
;    from buffer area
;------------------------------------------------------
fic_putwind_stack STRUC

					dw    5 dup (?)     ; five regs saved
					dd    ?             ; return address

	x1_10           dw    ?
	y1_10           dw    ?
	linecount_10    dw    ?
	bytecount_10    dw    ?
	buffptr_10      dd    ?

fic_putwind_stack ENDS

	PUBLIC _ega_putwind
_ega_putwind PROC FAR
	PUSH    BP
	PUSH    DS
	PUSH    ES
	PUSH    SI
	PUSH    DI
	MOV     BP,SP

	MOV     AX,[BP].y1_10               ; offset of source window
	MOV     BL,20
	MUL     BL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX

	CALL    _ega_offset                 ; get offset in AX

	MOV     SP,BP
	ADD     AX,[BP].x1_10
	MOV     BX,AX
	MOV     ES,EGA_Address
	LDS     SI,[BP].buffptr_10

	CLD

scanline_loop10:
	DEC     [BP].linecount_10
	JS      end_putwind10
	MOV     DI,BX
	MOV     CX,[BP].bytecount_10
	REP     MOVSB
	shift_down BX
	JMP     scanline_loop10

end_putwind10:
	POP     DI
	POP     SI
	POP     ES
	POP     DS
	POP     BP
	RET

_ega_putwind ENDP

EGAVGA_TEXT ENDS

END
