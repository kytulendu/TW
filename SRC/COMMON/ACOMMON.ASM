;=============================================================================;
;                                 Thai Driver                                 ;
;=============================================================================;

	DGROUP		GROUP	_DATA,_BSS
	_DATA		SEGMENT	WORD PUBLIC 'DATA'

; Kedmanee keyboard table
kedmanee_table	db   000h,001h,002h,003h,004h,005h,006h,007h
				db   008h,009h,00ah,00bh,00ch,00dh,00eh,00fh
				db   010h,011h,012h,013h,014h,015h,016h,017h
				db   018h,019h,01ah,01bh,01ch,01dh,01eh,01fh
				db   020h,023h,02eh,0f2h,0f3h,0f4h,0dbh,0a7h
				db   0f6h,0f7h,0f5h,0f9h,0c1h,0a2h,0e3h,0bdh
				db   0a8h,0c5h,02fh,05fh,0c0h,0b6h,0d8h,0d6h
				db   0a4h,0b5h,0abh,0c7h,0b2h,0aah,0cch,0c6h
				db   0f1h,0c4h,0dah,0a9h,0afh,0aeh,0e2h,0ach
				db   0e7h,0b3h,0ebh,0c9h,0c8h,0eeh,0ech,0cfh
				db   0adh,0f0h,0b1h,0a6h,0b8h,0eah,0ceh,022h
				db   029h,0edh,028h,0bah,05ch,0c5h,0d9h,0f8h
				db   000h,0bfh,0d4h,0e1h,0a1h,0d3h,0b4h,0e0h
				db   0e9h,0c3h,0e8h,0d2h,0cah,0b7h,0d7h,0b9h
				db   0c2h,0e6h,0beh,0cbh,0d0h,0d5h,0cdh,0e4h
				db   0bbh,0d1h,0bch,0b0h,07ch,02ch,025h,07fh

	PUBLIC curfont
curfont			db   20 dup (0)
				db   4 dup (0)

	PUBLIC enlargefont
enlargefont      db   40 dup (0)

	PUBLIC offsetfont
offsetfont		dw   0,20,40,60,80,100,120,140,160,180,200
				dw   220,240,260,280,300,320,340,360,380,400
				dw   420,440,460,480,500,520,540,560,580,600
				dw   620,640,660,680,700,720,740,760,780,800
				dw   820,840,860,880,900,920,940,960,980,1000
				dw   1020,1040,1060,1080,1100,1120,1140,1160,1180,1200
				dw   1220,1240,1260,1280,1300,1320,1340,1360,1380,1400
				dw   1420,1440,1460,1480,1500,1520,1540,1560,1580,1600
				dw   1620,1640,1660,1680,1700,1720,1740,1760,1780,1800
				dw   1820,1840,1860,1880,1900,1920,1940,1960,1980,2000
				dw   2020,2040,2060,2080,2100,2120,2140,2160,2180,2200
				dw   2220,2240,2260,2280,2300,2320,2340,2360,2380,2400
				dw   2420,2440,2460,2480,2500,2520,2540,2560,2580,2600
				dw   2620,2640,2660,2680,2700,2720,2740,2760,2780,2800
				dw   2820,2840,2860,2880,2900,2920,2940,2960,2980,3000
				dw   3020,3040,3060,3080,3100,3120,3140,3160,3180,3200
				dw   3220,3240,3260,3280,3300,3320,3340,3360,3380,3400
				dw   3420,3440,3460,3480,3500,3520,3540,3560,3580,3600
				dw   3620,3640,3660,3680,3700,3720,3740,3760,3780,3800
				dw   3820,3840,3860,3880,3900,3920,3940,3960,3980,4000
				dw   4020,4040,4060,4080,4100,4120,4140,4160,4180,4200
				dw   4220,4240,4260,4280,4300,4320,4340,4360,4380,4400
				dw   4420,4440,4460,4480,4500,4520,4540,4560,4580,4600
				dw   4620,4640,4660,4680,4700,4720,4740,4760,4780,4800
				dw   4820,4840,4860,4880,4900,4920,4940,4960,4980,5000
				dw   5020,5040,5060,5080,5100

;========================================================================;
;                               Logo image                               ;
;========================================================================;
;--------------------------------------------------------------------;

; HEX
;  R | L
; 0xx xxh

; Binary
;       Left             Right
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 1
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 2
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 3
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 4
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 5
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 6
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 7
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 8
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 9
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 10
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 11
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 12
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 13
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 14
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 15
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 16
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 17
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 18
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 19
; xxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxx 20

; Left
	PUBLIC chulalogo1
chulalogo1		dw   00200h,03200h,00d00h,0fb03h
				dw   01d00h,0e500h,09b03h,0320ch
				dw   0e400h,0df01h,0b507h,01f0eh
				dw   00c00h,03f00h,0e001h,00027h
				dw   0ff5fh,00027h,0e051h,03f00h

; Right
	PUBLIC chulalogo2
chulalogo2		dw   00040h,0004ch,000b0h,0c0dfh
				dw   000b8h,000a7h,0c0d9h,0304ch
				dw   00027h,080fbh,0e0adh,070f8h
				dw   00030h,000fch,08007h,0e400h
				dw   0faffh,0e400h,08a07h,000fch

;--------------------------------------------------------------------;

	PUBLIC _chardot
_chardot		db   20 dup (0)

	_DATA		ENDS

	_BSS		SEGMENT WORD PUBLIC 'BSS'
	_BSS		ENDS

	ACOMMON_TEXT	SEGMENT BYTE PUBLIC 'CODE'
				ASSUME  CS:ACOMMON_TEXT, DS:DGROUP
				
;=============================================================================;
; _thaikey -  Change ascii value of key from english to thai                  ;
;                                                                             ;
;     USAGE : thaikey(unsigned key)                                           ;
;=============================================================================;
; thaikey(unsigned key){
;     return (kedmanee_table[key]); ?
;}
    PUBLIC _thaikey
_thaikey PROC FAR
    PUSH    BP
    MOV     BP,SP

    MOV     BX,OFFSET DGROUP:kedmanee_table
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
