;****************************************************************************;
; HERC.ASM                                                                   ;
;                                                                            ;
; 3 JAN 1989                                                                 ;
; Hercules Graphic Card Driver                                               ;
; Updated: Kraisorn Liansee                                                  ;
; Updated: Suttipong Kanakakorn                                              ;
;          Sun  07-30-1989  18:01:20                                         ;
;          Suttipong Kanakakorn                                              ;
;          Mon  11-06-1989  20:47:39   modify leveltable to receive BALI     ;
;****************************************************************************;

INCLUDE cwfnthm.asm

	DGROUP		GROUP _DATA, _BSS

	_DATA		SEGMENT WORD PUBLIC 'DATA'

EXTRN curfont:BYTE, enlargefont:BYTE, offsetfont:WORD
EXTRN chulalogo1:WORD, chulalogo2:WORD
EXTRN _dfont:BYTE, _ditalicfont:BYTE
EXTRN _screen_buffptr:DWORD

	PUBLIC _herc_align
_herc_align		dw   5

HGC_Address		dw   0B000h				; Beginning of HGC frame buffer

; Hercules port address
herc_index		equ  03B4h				; 6845 index register
;herc_data		equ  03B5h				; 6845 data register
herc_cntrl		equ  03B8h				; Display mode control port
;herc_status	equ  03BAh				; Display status port
herc_config		equ  03BFh				; Display configuration port

; Hercules control/configuration register settings
scrn_on        	equ	 08h				;
graph			equ  02h				; Graphic mode
text			equ  20h				; Text mode

; 6845 values for text and graphics modes.
graphic_table	db   35h, 2dh, 2eh, 07h
				db   5bh, 02h, 57h, 57h
				db   02h, 03h, 00h, 00h

text_table      db   61h, 50h, 52h, 0Fh
                db   19h, 06h, 19h, 19h
                db   02h, 0Dh, 0Bh, 0Ch

screenoffset	dw   90      ;row 0
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

	_DATA		ENDS

	_BSS		SEGMENT WORD PUBLIC 'BSS'
	_BSS		ENDS

HERC_TEXT  SEGMENT   BYTE PUBLIC 'CODE'
		   ASSUME    CS:HERC_TEXT,DS:DGROUP

;=============================================================================;
; _hprchar -  print character at specified cursor position                    ;
;         ( don't forward cursor position )                                   ;
;                                                                             ;
;     USAGE : hprchar(unsigned c, unsigned attr, unsigned x, unsigned y)      ;
;             Attribute : bit 0 -> single underline                           ;
;                         bit 1 -> reverse                                    ;
;                         bit 2 -> bold                                       ;
;                         bit 3 -> superscript                                ;
;                         bit 4 -> subscript                                  ;
;                         bit 5 -> italic                                     ;
;                         bit 6 -> enlarge                                    ;
;                         bit 7 -> double underline                           ;
;=============================================================================;
    PUBLIC _hprchar
_hprchar PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    SI
    PUSH    DI
    PUSH    ES

    MOV     ES,HGC_Address

; ASCII value * 20 is offset in font
; we will set DS:[BX+SI] point at font
    MOV     SI,[BP+6]                   ; get character
    AND     SI,00FFh                    ; clear high byte
    ADD     SI,SI                       ; add for word offset
    ADD     SI,OFFSET DGROUP:offsetfont
    MOV     SI,DS:[SI]                  ; get offset from table
    MOV     AL,[BP+8]                   ; get attribute
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
    MOV     AL,[BP+8]                   ; get attribute
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
    TEST    AL,001h                     ; single underline ?
    JZ      chkdoubleunderline
    MOV     BYTE PTR DS:[BX+17],0FFh

chkdoubleunderline:
    TEST    AL,080h                     ; double underline ?
    JZ      chkreverse
    MOV     BYTE PTR DS:[BX+16],0FFh
    MOV     BYTE PTR DS:[BX+18],0FFh

chkreverse:
    TEST    AL,002h                     ; reverse ?
    JZ      chkenlarge
    MOV     AL,[BP+6]                   ; get char
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
    TEST    BYTE PTR [BP+8],040h        ; enlarge ?
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
    MOV     DI,[BP+12]                  ; get row
    ADD     DI,DI                       ; add for word offset
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     DI,DS:[DI]
    ADD     DI,[BP+10]                  ; add column
    ADD     DI,_herc_align

; we will write character now (using standard code)
    MOV     AL,[BP+6]                   ; get character
    CMP     AL,0D0h
    JBE     middle_level
    CMP     AL,0D1h
    JBE     abvlevel
    CMP     AL,0D3h
    JBE     middle_level
    CMP     AL,0D7h
    JBE     abvlevel
    CMP     AL,0DAh
    JBE     below_level
    CMP     AL,0E6h
    JBE     middle_level
    CMP     AL,0EEh
    JBE     abvlevel
    JMP     middle_level

abvlevel:
    JMP     above_level

; write below level character
; we will write last-four font only
below_level:
    TEST    BYTE PTR [BP+8],040h        ; enlarge ?
    JZ      noenlargebelow
    MOV     AX,DS:[BX+SI+32]
    XOR     ES:[DI+360],AX
    MOV     AX,DS:[BX+SI+34]
    XOR     ES:[DI+360+2000h],AX
    MOV     AX,DS:[BX+SI+36]
    XOR     ES:[DI+360+4000h],AX
    MOV     AX,DS:[BX+SI+38]
    XOR     ES:[DI+360+6000h],AX
    JMP     out_write

noenlargebelow:
    MOV     AL,DS:[BX+SI+16]
    XOR     ES:[DI+360],AL
    MOV     AL,DS:[BX+SI+17]
    XOR     ES:[DI+360+2000h],AL
    MOV     AL,DS:[BX+SI+18]
    XOR     ES:[DI+360+4000h],AL
    MOV     AL,DS:[BX+SI+19]
    XOR     ES:[DI+360+6000h],AL
    JMP     out_write

	noenlarge1:
    JMP     noenlarge

; write middle level character
; we will write 12 byte only by ignore first-four & last-four font
middle_level:
    TEST    BYTE PTR [BP+8],040h        ; enlarge ?
    JZ      noenlarge1
    MOV     AX,DS:[BX+SI]
    MOV     ES:[DI],AX
    MOV     AX,DS:[BX+SI+2]
    MOV     ES:[DI+2000h],AX
    MOV     AX,DS:[BX+SI+4]
    MOV     ES:[DI+4000h],AX
    MOV     AX,DS:[BX+SI+6]
    MOV     ES:[DI+6000h],AX
    MOV     AX,DS:[BX+SI+8]
    MOV     ES:[DI+90],AX
    MOV     AX,DS:[BX+SI+10]
    MOV     ES:[DI+90+2000h],AX
    MOV     AX,DS:[BX+SI+12]
    MOV     ES:[DI+90+4000h],AX
    MOV     AX,DS:[BX+SI+14]
    MOV     ES:[DI+90+6000h],AX
    MOV     AX,DS:[BX+SI+16]
    MOV     ES:[DI+180],AX
    MOV     AX,DS:[BX+SI+18]
    MOV     ES:[DI+180+2000h],AX
    MOV     AX,DS:[BX+SI+20]
    MOV     ES:[DI+180+4000h],AX
    MOV     AX,DS:[BX+SI+22]
    MOV     ES:[DI+180+6000h],AX
    MOV     AX,DS:[BX+SI+24]
    MOV     ES:[DI+270],AX
    MOV     AX,DS:[BX+SI+26]
    MOV     ES:[DI+270+2000h],AX
    MOV     AX,DS:[BX+SI+28]
    MOV     ES:[DI+270+4000h],AX
    MOV     AX,DS:[BX+SI+30]
    MOV     ES:[DI+270+6000h],AX
    MOV     AX,DS:[BX+SI+32]
    MOV     ES:[DI+360],AX
    MOV     AX,DS:[BX+SI+34]
    MOV     ES:[DI+360+2000h],AX
    MOV     AX,DS:[BX+SI+36]
    MOV     ES:[DI+360+4000h],AX
    MOV     AX,DS:[BX+SI+38]
    MOV     ES:[DI+360+6000h],AX
    JMP     out_write

noenlarge:
    MOV     AL,DS:[BX+SI]
    MOV     ES:[DI],AL
    MOV     AL,DS:[BX+SI+1]
    MOV     ES:[DI+2000h],AL
    MOV     AL,DS:[BX+SI+2]
    MOV     ES:[DI+4000h],AL
    MOV     AL,DS:[BX+SI+3]
    MOV     ES:[DI+6000h],AL
    MOV     AL,DS:[BX+SI+4]
    MOV     ES:[DI+90],AL
    MOV     AL,DS:[BX+SI+5]
    MOV     ES:[DI+90+2000h],AL
    MOV     AL,DS:[BX+SI+6]
    MOV     ES:[DI+90+4000h],AL
    MOV     AL,DS:[BX+SI+7]
    MOV     ES:[DI+90+6000h],AL
    MOV     AL,DS:[BX+SI+8]
    MOV     ES:[DI+180],AL
    MOV     AL,DS:[BX+SI+9]
    MOV     ES:[DI+180+2000h],AL
    MOV     AL,DS:[BX+SI+10]
    MOV     ES:[DI+180+4000h],AL
    MOV     AL,DS:[BX+SI+11]
    MOV     ES:[DI+180+6000h],AL
    MOV     AL,DS:[BX+SI+12]
    MOV     ES:[DI+270],AL
    MOV     AL,DS:[BX+SI+13]
    MOV     ES:[DI+270+2000h],AL
    MOV     AL,DS:[BX+SI+14]
    MOV     ES:[DI+270+4000h],AL
    MOV     AL,DS:[BX+SI+15]
    MOV     ES:[DI+270+6000h],AL
    MOV     AL,DS:[BX+SI+16]
    MOV     ES:[DI+360],AL
    MOV     AL,DS:[BX+SI+17]
    MOV     ES:[DI+360+2000h],AL
    MOV     AL,DS:[BX+SI+18]
    MOV     ES:[DI+360+4000h],AL
    MOV     AL,DS:[BX+SI+19]
    MOV     ES:[DI+360+6000h],AL
    JMP     out_write

; above level has 2 level, above-middle & topest
; above-middle level has ASCII code < 0E4h
; topest level has ASCII code >= 0E4h
above_level:
    CMP     AL,0E6h
    JB      above_middle
    CMP     AL,0EDh
    JAE     above_middle
    TEST    BYTE PTR [BP+8],040h        ; enlarge ?
    JZ      noenlargetop
    MOV     AX,DS:[BX+SI]
    XOR     ES:[DI],AX
    MOV     AX,DS:[BX+SI+2]
    XOR     ES:[DI+2000h],AX
    MOV     AX,DS:[BX+SI+4]
    XOR     ES:[DI+4000h],AX
    MOV     AX,DS:[BX+SI+6]
    XOR     ES:[DI+6000h],AX
    JMP     out_write

noenlargetop:
    MOV     AL,DS:[BX+SI]
    XOR     ES:[DI],AL
    MOV     AL,DS:[BX+SI+1]
    XOR     ES:[DI+2000h],AL
    MOV     AL,DS:[BX+SI+2]
    XOR     ES:[DI+4000h],AL
    MOV     AL,DS:[BX+SI+3]
    XOR     ES:[DI+6000h],AL
    JMP     out_write

above_middle:
    TEST    BYTE PTR [BP+8],040h        ; enlarge ?
    JZ      noenlargeabove
    MOV     AX,DS:[BX+SI+8]
    XOR     ES:[DI+90],AX
    MOV     AX,DS:[BX+SI+10]
    XOR     ES:[DI+90+2000h],AX
    MOV     AX,DS:[BX+SI+12]
    XOR     ES:[DI+90+4000h],AX
    MOV     AX,DS:[BX+SI+14]
    XOR     ES:[DI+90+6000h],AX
    JMP     out_write

noenlargeabove:
    MOV     AL,DS:[BX+SI+4]
    XOR     ES:[DI+90],AL
    MOV     AL,DS:[BX+SI+5]
    XOR     ES:[DI+90+2000h],AL
    MOV     AL,DS:[BX+SI+6]
    XOR     ES:[DI+90+4000h],AL
    MOV     AL,DS:[BX+SI+7]
    XOR     ES:[DI+90+6000h],AL

out_write:
    POP     ES
    POP     DI
    POP     SI
    POP     BP
    RET

_hprchar  ENDP

;=============================================================================;
; _hprblank -  print blank character at specified cursor position             ;
;         ( don't forward cursor position )                                   ;
;                                                                             ;
;     USAGE : hprblank(unsigned x, unsigned y)                                ;
;=============================================================================;
    PUBLIC _hprblank
_hprblank PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    DI
    PUSH    ES

    MOV     ES,HGC_Address

; we will set ES:[DI] point at screen
    MOV     DI,[BP+8]                   ; get row
    ADD     DI,DI                       ; add for word offset
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     DI,DS:[DI]
    ADD     DI,[BP+6]                   ; add column
    ADD     DI,_herc_align
    XOR     AL,AL
    MOV     ES:[DI],AL
    MOV     ES:[DI+2000h],AL
    MOV     ES:[DI+4000h],AL
    MOV     ES:[DI+6000h],AL
    MOV     ES:[DI+90],AL
    MOV     ES:[DI+90+2000h],AL
    MOV     ES:[DI+90+4000h],AL
    MOV     ES:[DI+90+6000h],AL
    MOV     ES:[DI+180],AL
    MOV     ES:[DI+180+2000h],AL
    MOV     ES:[DI+180+4000h],AL
    MOV     ES:[DI+180+6000h],AL
    MOV     ES:[DI+270],AL
    MOV     ES:[DI+270+2000h],AL
    MOV     ES:[DI+270+4000h],AL
    MOV     ES:[DI+270+6000h],AL
    MOV     ES:[DI+360],AL
    MOV     ES:[DI+360+2000h],AL
    MOV     ES:[DI+360+4000h],AL
    MOV     ES:[DI+360+6000h],AL

    POP     ES
    POP     DI
    POP     BP
    RET

_hprblank ENDP

;=============================================================================;
; _hsetcurpos -  xor cursor at specified cursor position                      ;
;                                                                             ;
;     USAGE : hsetcurpos(unsigned x, unsigned y, int thaimode)                ;
;=============================================================================;
    PUBLIC _hsetcurpos
_hsetcurpos PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    DI
    PUSH    ES

    MOV     ES,HGC_Address

; we will set ES:[DI] point at screen
    MOV     DI,[BP+8]                   ; get row
    ADD     DI,DI                       ; add for word offset
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     DI,DS:[DI]                  ; get offset of row from table
    ADD     DI,[BP+6]                   ; add column
    ADD     DI,_herc_align

; xor 12 byte only by ignore first-four & last-four byte
    CMP     BYTE PTR [BP+10],1          ; thai mode ?
    JNE     englishmode
    XOR     BYTE PTR ES:[DI+90],0FFh
    XOR     BYTE PTR ES:[DI+90+2000h],0FFh
    XOR     BYTE PTR ES:[DI+90+4000h],0FFh
    XOR     BYTE PTR ES:[DI+90+6000h],0FFh
    XOR     BYTE PTR ES:[DI+180],0FFh
    XOR     BYTE PTR ES:[DI+180+2000h],0FFh
    XOR     BYTE PTR ES:[DI+180+4000h],0FFh
    XOR     BYTE PTR ES:[DI+180+6000h],0FFh
    XOR     BYTE PTR ES:[DI+270],0FFh
    XOR     BYTE PTR ES:[DI+270+2000h],0FFh
    XOR     BYTE PTR ES:[DI+270+4000h],0FFh
    XOR     BYTE PTR ES:[DI+270+6000h],0FFh
    JMP     outsetcurpos

englishmode:
    XOR     BYTE PTR ES:[DI+360],0FFh
    XOR     BYTE PTR ES:[DI+360+2000h],0FFh

outsetcurpos:
    POP     ES
    POP     DI
    POP     BP
    RET

_hsetcurpos ENDP

;=============================================================================;
; plot                                                                        ;
;     plot dot by find position as follow                                     ;
;     find byte position from formula                                         ;
;          2000h*(Y mod 4) + 90*integer(Y/4) + integer(X/8)                   ;
;     find bit position in byte from formula                                  ;
;          7 - (x mod 8)                                                      ;
;     USAGE : plot(unsigned x,unsigned y)                                     ;
;=============================================================================;
    PUBLIC _hplot
_hplot PROC FAR
	PUSH     BP
	MOV      BP,SP
	PUSH     DI
	PUSH     ES

; calculate offset
	MOV     AX,[BP+8]					; get dot y
	MOV     CL,2						; divide by 4
	SHR     AX,CL						; ax = integer(y/4)
	MOV     BX,AX
	MOV     CL,5						; multiplied by 32
	SHL     BX,CL
	SUB     BX,AX						; multiplied by 31
	SUB     BX,AX						; multiplied by 30
	SUB     BX,AX						; multiplied by 29
	SUB     BX,AX						; multiplied by 28
	SUB     BX,AX						; multiplied by 27
	SUB     BX,AX						; multiplied by 26
	MOV     CL,6						; multiply by 64
	SHL     AX,CL
	ADD     AX,BX						; multiplied by 90 ( 64 + 26 )
	MOV     DI,AX
; Find 2000h * (y mod 4).
; Possible value is 0,2000h,4000h,6000h only.
; So we will not calculate but using comparing for speed.
	MOV     AL,[BP+8]					; get dot y (low byte only)
	AND     AL,03h						; al = y mod 4 (see from two last bit only)
	OR      AL,AL
	JZ      plotnext
	TEST    AL,01H
	JZ      testbit1next
	ADD     DI,2000h
testbit1next:
	TEST    AL,02H
	JZ      plotnext
	ADD     DI,4000H
plotnext:
	MOV     AX,[BP+6]					; get dot x
	MOV     CL,3						; divide by 8
	SHR     AX,CL						; AL = integer(x/8)
	ADD     DI,AX						; now DI point at byte wanted
	ADD     DI,_herc_align
	MOV     AL,[BP+6]					; get dot x
	AND     AL,007h						; now , al = x mod 8
	MOV     CL,7
	SUB     CL,AL						; BL = 7 - (x mod 8)
	MOV     BL,1
	SHL     BL,CL

; write dot
	MOV     ES,HGC_Address
	OR      BYTE PTR ES:[DI],BL

	POP     ES
	POP     DI
	POP     BP

	RET

_hplot ENDP

;=============================================================================;
; _hsetgraph                                                                  ;
;         Programs the 6845 CRT controller for the 720 x 348 graphics mode.   ;
;=============================================================================;
	PUBLIC _hsetgraph
_hsetgraph PROC FAR
	PUSH    SI
	PUSH    DS
	PUSH    ES

; NOTE: Be sure that the Configuration Port (03BF) is set to your
; requirements (03BF = 1 for HALF, 03BF = 3 for FULL) before
; attempting to set graphics mode.
	MOV     AL,1
	MOV     DX,herc_config
	OUT     DX,AL

; set graphic mode
	MOV     AL,graph
	MOV     DX,herc_cntrl
	OUT     DX,AL

; initialize the 6845
	MOV     AX,DGROUP
	MOV     SI,OFFSET DGROUP:graphic_table	; address of graphic parameters
	MOV     DX,herc_index
	MOV     CX,12						; 12 parameters to be output
	XOR     AH,AH						; starting from register 0

parms:
	MOV     AL,AH						; first output register number
	OUT     DX,AL

    INC     DX							; get data register address
    LODSB								; get next byte from param. table
    OUT     DX,AL						; output parameter data

    INC     AH							; increment register number
    DEC     DX							; restore index register address
    LOOP    parms						; go do another one

;
	MOV     AL,00Ah
	MOV     DX,herc_cntrl
	OUT     DX,AL

; clear the buffer
	MOV     ES,HGC_Address				; address of video buffer
	XOR     DI,DI						; start at offset 0
	MOV     CX,4000h					; number of words to clear
	MOV     AX,0						; blank value
	CLD									; set auto increment
	REP     STOSW						; repeat store string

; turn screen on with page 0 active
	;MOV     DX,herc_cntrl				; get control register address
	;POP     AX							; get the mode byte
	;ADD     AL,scrn_on					; set the screen-on bit
	;OUT     DX,AL

; Add By Suttipong Kanakakorn (Noom)
; Set 0:465 to 0Ah as set to port 3b8h
; Very valuable for Many programs Such as DesqView, Turbo Debugger
	XOR     SI,SI
	MOV     DS,SI
	MOV     BYTE PTR DS:[465h],00Ah

	POP     ES
	POP     DS
	POP     SI
	RET

_hsetgraph ENDP

;=============================================================================;
; _hsettext                                                                   ;
;         Programs the 6845 CRT controller for text mode.                     ;
;=============================================================================;
	PUBLIC _hsettext
_hsettext PROC FAR
	PUSH    SI
	PUSH    DS
	PUSH    ES

; set text mode
	MOV     AL,text
	MOV     DX,herc_cntrl
	OUT     DX,AL

; initialize the 6845
	MOV     AX,DGROUP
	MOV     SI,OFFSET DGROUP:text_table	; address of text parameters
	MOV     DX,herc_index
	MOV     CX,12						; 12 parameters to be output
	XOR     AH,AH						; starting from register 0

parms1:
	MOV     AL,AH						; first output register number
	OUT     DX,AL

    INC     DX							; get data register address
    LODSB								; get next byte from param. table
    OUT     DX,AL						; output parameter data

    INC     AH							; increment register number
    DEC     DX							; restore index register address
    LOOP    parms1						; go do another one

; clear the buffer
	MOV     ES,HGC_Address				; address of video buffer
	XOR     DI,DI						; start at offset 0
	MOV     CX,2000h					; number of words to clear
	MOV     AX,720h						; blank value
	CLD									; set auto increment
	REP     STOSW						; repeat store string

; turn screen on with page 0 active
	;MOV     DX,herc_cntrl				; get control register address
	;POP     AX							; get the mode byte
	;ADD     AL,scrn_on					; set the screen-on bit
	;OUT     DX,AL

	POP     ES
	POP     DS
	POP     SI
	RET

_hsettext ENDP

;=============================================================================;
; _hsavepic -  save picture from screen memory page 1 to page 0               ;
;=============================================================================;
    PUBLIC _hsavepic
_hsavepic PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    SI
    PUSH    DI
    PUSH    DS

    LES     DI,_screen_buffptr

    MOV     DS,HGC_Address
    XOR     SI,SI

    CLD
    MOV     CX,4000h
    REP     MOVSW

    POP     DS
    POP     DI
    POP     SI
    POP     BP
    RET

_hsavepic ENDP

;=============================================================================;
; _hretpic -  return picture from screen memory page 0 to page 1              ;
;=============================================================================;
    PUBLIC _hretpic
_hretpic PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    SI
    PUSH    DI
    PUSH    DS
    PUSH    ES

    MOV     ES,HGC_Address
    XOR     DI,DI

    LDS     SI,_screen_buffptr

    CLD
    MOV     CX,4000h
    REP     MOVSW

    POP     ES
    POP     DS
    POP     DI
    POP     SI
    POP     BP
    RET

_hretpic ENDP

;=============================================================================;
; _hclsall -  clear screen memory page 1 to blank                             ;
;=============================================================================;
    PUBLIC _hclsall
_hclsall PROC  FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    DI
    PUSH    ES

	MOV     ES,HGC_Address				; address of video buffer
	XOR     DI,DI						; start at offset 0
	MOV     CX,4000h					; number of words to clear
	MOV     AX,0						; blank value
	CLD									; set auto increment
	REP     STOSW						; repeat store string

    POP     ES
    POP     DI
    POP     BP
    RET

_hclsall ENDP

;=============================================================================;
; _hclsgraph -  clear graphic screen for window specified                     ;
;                                                                             ;
;     USAGE : hclsgraph(int x1, int y1, int x2, int y2)                       ;
;=============================================================================;
    PUBLIC _hclsgraph
_hclsgraph PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    DI
    PUSH    ES

    MOV     ES,HGC_Address

; we will set ES:[DI] point at screen
    MOV     DI,[BP+8]                   ; get y1
    ADD     DI,DI                       ; add for word offset
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     DI,DS:[DI]                  ; get row offset from table
    ADD     DI,[BP+6]                   ; add x1
    ADD     DI,_herc_align
    MOV     CX,[BP+12]                  ; get y2
    SUB     CX,[BP+8]                   ; sub with y1
    INC     CX                          ; CX = no. of row to clear
    MOV     AX,0
    MOV     BX,[BP+10]                  ; get x2
    SUB     BX,[BP+6]                   ; sub with x1
    INC     BX                          ; BX = no. of column to clear

clearrow:
    PUSH    CX
    MOV     CX,5
    PUSH    DI

loopfive:
    PUSH    CX
    PUSH    DI
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    PUSH    DI
    ADD     DI,2000h
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    PUSH    DI
    ADD     DI,4000h
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    PUSH    DI
    ADD     DI,6000h
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    ADD     DI,90
    POP     CX
    LOOP    loopfive

    POP     DI
    ADD     DI,450
    POP     CX
    LOOP    clearrow

    POP     ES
    POP     DI
    POP     BP
    RET

_hclsgraph ENDP

;=============================================================================;
; _hclrline -  clear line y1 from x1 to x2                                    ;
;                                                                             ;
;     USAGE : hclrline(int x1, int y1, int x2)                                ;
;=============================================================================;
    PUBLIC _hclrline
_hclrline PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    DI
    PUSH    ES

    MOV     ES,HGC_Address

; we will set ES:[DI] point at screen
    MOV     DI,[BP+8]                   ; get y1
    ADD     DI,DI
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     DI,DS:[DI]
    ADD     DI,[BP+6]                   ; add x1
    ADD     DI,_herc_align
    MOV     AX,0
    MOV     BX,[BP+10]                  ; get x2
    SUB     BX,[BP+6]                   ; sub with x1
    INC     BX
    MOV     CX,5

fiveloop:
    PUSH    CX
    PUSH    DI
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    PUSH    DI
    ADD     DI,2000h
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    PUSH    DI
    ADD     DI,4000h
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    PUSH    DI
    ADD     DI,6000h
    MOV     CX,BX
    CLD
    REP     STOSB
    POP     DI

    ADD     DI,90
    POP     CX
    LOOP    fiveloop

    POP     ES
    POP     DI
    POP     BP
    RET

_hclrline ENDP

;=============================================================================;
; prakeaw                                                                     ;
;       write parkeaw at upper left cornor                                    ;
;=============================================================================;
	PUBLIC _hprakeaw
_hprakeaw PROC FAR
    PUSH    BP
    MOV     BP,SP
    PUSH    SI
    PUSH    DI
    PUSH    ES

    MOV     ES,HGC_Address

    MOV     SI,OFFSET DS:chulalogo1
    MOV     DI,_herc_align
    INC     DI

    MOV     AX,DS:[SI]
    MOV     ES:[DI+4000h],AX
    MOV     AX,DS:[SI+2]
    MOV     ES:[DI+6000h],AX

    MOV     AX,DS:[SI+4]
    MOV     ES:[DI+90],AX
    MOV     AX,DS:[SI+6]
    MOV     ES:[DI+90+2000h],AX
    MOV     AX,DS:[SI+8]
    MOV     ES:[DI+90+4000h],AX
    MOV     AX,DS:[SI+10]
    MOV     ES:[DI+90+6000h],AX

    MOV     AX,DS:[SI+12]
    MOV     ES:[DI+180],AX
    MOV     AX,DS:[SI+14]
    MOV     ES:[DI+180+2000h],AX
    MOV     AX,DS:[SI+16]
    MOV     ES:[DI+180+4000h],AX
    MOV     AX,DS:[SI+18]
    MOV     ES:[DI+180+6000h],AX

    MOV     AX,DS:[SI+20]
    MOV     ES:[DI+270],AX
    MOV     AX,DS:[SI+22]
    MOV     ES:[DI+270+2000h],AX
    MOV     AX,DS:[SI+24]
    MOV     ES:[DI+270+4000h],AX
    MOV     AX,DS:[SI+26]
    MOV     ES:[DI+270+6000h],AX

    MOV     AX,DS:[SI+28]
    MOV     ES:[DI+360],AX
    MOV     AX,DS:[SI+30]
    MOV     ES:[DI+360+2000h],AX
    MOV     AX,DS:[SI+32]
    MOV     ES:[DI+360+4000h],AX
    MOV     AX,DS:[SI+34]
    MOV     ES:[DI+360+6000h],AX

    MOV     AX,DS:[SI+36]
    MOV     ES:[DI+450],AX
    MOV     AX,DS:[SI+38]
    MOV     ES:[DI+450+2000h],AX

    MOV     SI,OFFSET DS:chulalogo2
    MOV     DI,3
    ADD     DI,_herc_align

    MOV     AX,DS:[SI]
    MOV     ES:[DI+4000h],AX
    MOV     AX,DS:[SI+2]
    MOV     ES:[DI+6000h],AX

    MOV     AX,DS:[SI+4]
    MOV     ES:[DI+90],AX
    MOV     AX,DS:[SI+6]
    MOV     ES:[DI+90+2000h],AX
    MOV     AX,DS:[SI+8]
    MOV     ES:[DI+90+4000h],AX
    MOV     AX,DS:[SI+10]
    MOV     ES:[DI+90+6000h],AX

    MOV     AX,DS:[SI+12]
    MOV     ES:[DI+180],AX
    MOV     AX,DS:[SI+14]
    MOV     ES:[DI+180+2000h],AX
    MOV     AX,DS:[SI+16]
    MOV     ES:[DI+180+4000h],AX
    MOV     AX,DS:[SI+18]
    MOV     ES:[DI+180+6000h],AX

    MOV     AX,DS:[SI+20]
    MOV     ES:[DI+270],AX
    MOV     AX,DS:[SI+22]
    MOV     ES:[DI+270+2000h],AX
    MOV     AX,DS:[SI+24]
    MOV     ES:[DI+270+4000h],AX
    MOV     AX,DS:[SI+26]
    MOV     ES:[DI+270+6000h],AX

    MOV     AX,DS:[SI+28]
    MOV     ES:[DI+360],AX
    MOV     AX,DS:[SI+30]
    MOV     ES:[DI+360+2000h],AX
    MOV     AX,DS:[SI+32]
    MOV     ES:[DI+360+4000h],AX
    MOV     AX,DS:[SI+34]
    MOV     ES:[DI+360+6000h],AX

    MOV     AX,DS:[SI+36]
    MOV     ES:[DI+450],AX
    MOV     AX,DS:[SI+38]
    MOV     ES:[DI+450+2000h],AX

    POP     ES
    POP     DI
    POP     SI
    POP     BP
    RET

_hprakeaw ENDP

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

    PUBLIC _hgetwind
_hgetwind PROC FAR
    PUSH    BP
    PUSH    DS
    PUSH    ES
    PUSH    SI
    PUSH    DI
    MOV     BP,SP

    MOV     DI,[BP].y1_9
    ADD     DI,DI
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     AX,DS:[DI]
    ADD     AX,[BP].x1_9
    ADD     AX,_herc_align

    MOV     DS,HGC_Address
    LES     DI,[BP].buffptr_9

    CLD

scanline_loop9:
    DEC     [BP].linecount_9
    JS      end_getwind9
    MOV     SI,AX
    MOV     CX,[BP].bytecount_9
    REP     MOVSB
    shift_down AX
    JMP     scanline_loop9

end_getwind9:
    POP     DI
    POP     SI
    POP     ES
    POP     DS
    POP     BP
    RET

_hgetwind ENDP

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

	x1_10			dw    ?
	y1_10			dw    ?
	linecount_10	dw    ?
	bytecount_10	dw    ?
	buffptr_10		dd    ?

fic_putwind_stack ENDS

    PUBLIC _hputwind
_hputwind PROC FAR
    PUSH    BP
    PUSH    DS
    PUSH    ES
    PUSH    SI
    PUSH    DI
    MOV     BP,SP

    MOV     DI,[BP].y1_10
    ADD     DI,DI
    ADD     DI,OFFSET DGROUP:screenoffset
    MOV     AX,DS:[DI]
    ADD     AX,[BP].x1_10
    ADD     AX,_herc_align

    MOV     ES,HGC_Address
    LDS     SI,[BP].buffptr_10

    CLD

scanline_loop10:
    DEC     [BP].linecount_10
    JS      end_putwind10
    MOV     DI,AX
    MOV     CX,[BP].bytecount_10
    REP     MOVSB
    shift_down AX
    JMP     scanline_loop10

end_putwind10:
    POP     DI
    POP     SI
    POP     ES
    POP     DS
    POP     BP
    RET

_hputwind ENDP

HERC_TEXT ENDS

END
