;=============================================================================;
;                                 Thai Driver                                 ;
;=============================================================================;

	DGROUP		GROUP	_DATA,_BSS
	_DATA		SEGMENT	WORD PUBLIC 'DATA'

EXTRN _kedmanee_table:BYTE

	_DATA		ENDS

	_BSS		SEGMENT WORD PUBLIC 'BSS'
	_BSS		ENDS

	ACOMMON_TEXT	SEGMENT BYTE PUBLIC 'CODE'
				ASSUME  CS:ACOMMON_TEXT, DS:DGROUP
				
;=============================================================================;
; _thaikey -  Change ascii value of key from english to thai                  ;
;                                                                             ;
;     USAGE : thaikey( int key )                                              ;
;=============================================================================;
	PUBLIC _thaikey
_thaikey PROC FAR
	PUSH    BP
	MOV     BP,SP

	MOV     BX,OFFSET DGROUP:_kedmanee_table
	MOV     AX,[BP+6]                   ; get ascii code & scan code
	XLAT                                ; look up table for changing ascii code only

	POP     BP
	RET

_thaikey ENDP

;=============================================================================;
; asm_keypressed -  check keyboard status                                     ;
;                                                                             ;
;     USAGE : int asm_keypressed(void)                                        ;
;         return 0 : no keypressed                                            ;
;                keyboard scan code of the keypressed                         ;
;=============================================================================;

	PUBLIC _asm_keypressed
_asm_keypressed PROC FAR
	PUSHF

	MOV     AH,1
	INT     16h
	JZ      notpress
	JMP     nextpress

notpress:
	XOR      AX,AX

nextpress:
	POPF
	RET

_asm_keypressed ENDP

	ACOMMON_TEXT	ENDS

END
