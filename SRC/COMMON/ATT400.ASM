;****************************************************************************;
; ATT400.ASM                                                                 ;
;                                                                            ;
; 3 JAN 1989                                                                 ;
; AT&T 6300 Graphic Card Driver                                              ;
;****************************************************************************;

INCLUDE   cwfntam.asm

	DGROUP		GROUP _DATA, _BSS

	_DATA		SEGMENT WORD PUBLIC 'DATA'

EXTRN _dfont:byte, _ditalicfont:byte
EXTRN curfont:byte, enlargefont:byte, offsetfont:word
EXTRN chulalogo1:word, chulalogo2:word
EXTRN _screen_buffptr:dword

ATT_Address		dw   0B800h           ; Beginning of AT&T400 frame buffer

	_DATA		ENDS

	_BSS		SEGMENT WORD PUBLIC 'BSS'
	_BSS		ENDS

ATT400_TEXT		SEGMENT BYTE PUBLIC 'CODE'
				ASSUME CS:ATT400_TEXT, DS:DGROUP

EXTRN _aoffset:far

;=============================================================================;
; _aprchar -  print character at specified cursor position                    ;
;         ( don't forward cursor position )                                   ;
;                                                                             ;
;     USAGE : aprchar(unsigned c, unsigned attr, unsigned x, unsigned y)      ;
;             Attribute : bit 0 -> single underline                           ;
;                         bit 1 -> reverse                                    ;
;                         bit 2 -> bold                                       ;
;                         bit 3 -> superscript                                ;
;                         bit 4 -> subscript                                  ;
;                         bit 5 -> italic                                     ;
;                         bit 6 -> enlarge                                    ;
;                         bit 7 -> double underline                           ;
;=============================================================================;
	PUBLIC _aprchar
_aprchar PROC FAR
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
	ADD     SI,OFFSET DGROUP:offsetfont
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
	MOV     DI,OFFSET DGROUP:curfont
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
	MOV     BX,OFFSET DGROUP:curfont    ; base table is in BX
	XOR     SI,SI                       ; DS:[BX+SI] now point at font
	MOV     AL,[BP+14]                  ; get attribute
	TEST    AL,004H                     ; bold ?
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
	MOV     DI,OFFSET enlargefont
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
	MOV     BX,OFFSET DGROUP:enlargefont
	XOR     SI,SI

nochangefont:

; we will set ES:[DI] point at screen
; we will write character now (using standard code)
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
	CMP     AL,0Dah
	JBE     below_level
	CMP     AL,0e6h
	JA      cont3
	JMP     middle_level
cont3:
	CMP     al,0eeh
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column
	MOV     ES,ATT_Address

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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column
	MOV     ES,ATT_Address

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
	JAE     cont4
	JMP     above_middle
cont4:
	CMP     AL,0EDh
	JB      cont5
	JMP     above_middle
cont5:
	MOV     AX,[BP+18]
	MOV     CL,20                       ; 20 lines per row
	MUL     CL
	ADD     AX,4
	PUSH    AX
	XOR     AX,AX
	PUSH    AX
	MOV     DI,BX                       ; save in register variable

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                  ; add column
	MOV     ES,ATT_Address

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
	MOV     CL,20                        ; 20 lines per row
	MUL     CL
	ADD     AX,4+4                       ; down 4 lines
	PUSH    AX
	XOR     AX,AX
	PUSH    AX
	MOV     DI,BX                        ; save in register variable

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     BX,DI
	MOV     DI,AX
	ADD     DI,[BP+16]                   ; add column
	MOV     ES,ATT_Address

	TEST    BYTE PTR [BP+14],040h        ; enlarge ?
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

_aprchar ENDP

;=============================================================================;
; _aprblank -  print blank character at specified cursor position             ;
;         ( don't forward cursor position )                                   ;
;                                                                             ;
;     USAGE : aprblank(unsigned x, unsigned y)                                ;
;=============================================================================;
   PUBLIC _aprblank
_aprblank PROC FAR
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	ADD     DI,[BP+10]                  ; add column
	MOV     ES,ATT_Address

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

_aprblank ENDP

;=============================================================================;
; _asetcurpos -  xor cursor at specified cursor position                      ;
;                                                                             ;
;     USAGE : asetcurpos(unsigned x, unsigned y, int thaimode)                ;
;=============================================================================;
	PUBLIC _asetcurpos
_asetcurpos PROC FAR
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
	CALL    _aoffset                    ; get offset in AX
	MOV     SP,BP
	MOV     DI,AX
	ADD     DI,[BP+10]                  ; add column
	MOV     ES,ATT_Address

	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     byte PTR ES:[DI],0FFh
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	ADD     DI,[BP+10]                  ; add column
	MOV     ES,ATT_Address

	XOR     BYTE PTR ES:[DI],0FFh
	shift_down DI
	XOR     BYTE PTR ES:[DI],0FFh

outsetcurpos:
	POP     ES
	POP     DI
	POP     BP
	RET

_asetcurpos ENDP

;=============================================================================;
; _aplot -  plot dot by find byte position from formula                       ;
;         2000h * (Y mod 4) + 80 * integer(Y / 4) + integer(X / 8)            ;
;         find bit position in byte from formula 7 - (x mod 8)                ;
;                                                                             ;
;     USAGE : aplot(unsigned x, unsigned y)                                   ;
;=============================================================================;
	PUBLIC _aplot
_aplot PROC FAR
	PUSH    BP
	PUSH    DI
	PUSH    ES
	MOV     BP,SP

	PUSH    [BP+12]
	MOV     DI,[BP+10]
	PUSH    DI

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     CX,DI
	MOV     DI,AX
	MOV     ES,ATT_Address

	AND     CL,7
	MOV     AL,80h
	SHR     AL,CL

	OR      BYTE PTR ES:[DI],AL

	POP     ES
	POP     DI
	POP     BP
	RET

_aplot ENDP
;=============================================================================;
; _asavepic -  save picture from screen memory page 1 to page 0               ;
;=============================================================================;
	PUBLIC _asavepic
_asavepic PROC FAR
	PUSH    SI
	PUSH    DI
	PUSH    DS
	PUSH    ES

	LES     DI,_screen_buffptr

	MOV     DS,ATT_Address
	XOR     SI,SI

	MOV     DX,348
	CLD

loop1:
	MOV     BX,SI
	MOV     CX,40
	REP     MOVSW
	MOV     SI,BX
	shift_down SI
	DEC     DX
	JNZ     loop1

	POP     ES
	POP     DS
	POP     DI
	POP     SI
	RET

_asavepic ENDP

;=============================================================================;
; _aretpic -  return picture from screen memory page 0 to page 1              ;
;=============================================================================;
	PUBLIC _aretpic
_aretpic PROC FAR
	PUSH    SI
	PUSH    DI
	PUSH    DS
	PUSH    ES

	MOV     ES,ATT_Address
	XOR     DI,DI

	LDS     SI,_screen_buffptr

	MOV     DX,348
	CLD

loop2:
	MOV     BX,DI
	MOV     CX,40
	REP     MOVSW
	MOV     DI,BX
	shift_down DI
	DEC     DX
	JNZ     loop2

	POP     ES
	POP     DS
	POP     DI
	POP     SI
	RET

_aretpic ENDP

;=============================================================================;
; _aclsall -  clear screen memory page 1 to blank                             ;
;=============================================================================;
	PUBLIC _aclsall
_aclsall PROC FAR
	PUSH    DI
	PUSH    ES

	MOV     ES,ATT_Address
	XOR     DI,DI
	MOV     CX,4000h
	MOV     AX,00
	CLD
	REP     STOSW

	POP     ES
	POP     DI
	RET

_aclsall ENDP

;=============================================================================;
; _aclsgraph -  clear graphic screen for window specified                     ;
;                                                                             ;
;     USAGE : aclsgraph(int x1, int y1, int x2, int y2)                       ;
;=============================================================================;
	PUBLIC _aclsgraph
_aclsgraph PROC FAR
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	MOV     ES,ATT_Address


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
	JMP     SHORT clearrow;

endclsgraph:
	POP     ES
	POP     DI
	POP     BP
	RET

_aclsgraph  ENDP

;=============================================================================;
; _aclrline -  clear line y1 from x1 to x2                                    ;
;                                                                             ;
;     USAGE : aclrline(int x1, int y1, int x2)                                ;
;=============================================================================;
	PUBLIC _aclrline
_aclrline PROC FAR
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	MOV     DI,AX
	MOV     ES,ATT_Address

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

_aclrline ENDP

;=============================================================================;
; _aprakeaw -  write logo at upper left cornor                                ;
;=============================================================================;
	PUBLIC _aprakeaw
_aprakeaw PROC FAR
	PUSH    SI
	PUSH    DI
	PUSH    ES

	MOV     ES,ATT_Address

	MOV     SI,OFFSET DS:chulalogo1
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

	MOV     SI,OFFSET DS:chulalogo2
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
	RET

_aprakeaw ENDP

;------------------------------------------------------
;  fic_getwind(x1, y1, linecount, bytecount, buffptr)
;
;      copy window area at x1, y1 (left-top)
;    size = linecount * bytecount
;    to buffer area
;------------------------------------------------------

fic_getwind_stack STRUC

					DW    5 DUP (?)     ; five regs saved
					DD    ?             ; return address

	x1_9            DW    ?
	y1_9            DW    ?
	linecount_9     DW    ?
	bytecount_9     DW    ?
	buffptr_9       DD    ?

fic_getwind_stack ENDS

	PUBLIC _agetwind

_agetwind PROC FAR
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	ADD     AX,[BP].x1_9
	MOV     BX,AX
	MOV     DS,ATT_Address
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

_agetwind ENDP

;------------------------------------------------------
;  fic_putwind(x1, y1, linecount, bytecount, buffptr)
;
;      copy window area at x1, y1 (left-top)
;    size = linecount * bytecount
;    from buffer area
;------------------------------------------------------
fic_putwind_stack STRUC

					DW    5 DUP (?)     ; five regs saved
					DD    ?             ; return address

	x1_10           DW    ?
	y1_10           DW    ?
	linecount_10    DW    ?
	bytecount_10    DW    ?
	buffptr_10      DD    ?

fic_putwind_stack ENDS

	PUBLIC _aputwind

_aputwind PROC FAR
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

	CALL    _aoffset                    ; get offset in AX

	MOV     SP,BP
	ADD     AX,[BP].x1_10
	MOV     BX,AX
	MOV     ES,ATT_Address
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

_aputwind ENDP

ATT400_TEXT ENDS

END
