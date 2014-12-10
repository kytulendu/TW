;                   Font macro definition module for TURBO C
;                           Hercules  Adaptor
;
;                           Kraisorn Liansee
;               Date    :     12/01/88
;               Updated :     12/01/88

shift_down MACRO REG
    LOCAL BR1
    ADD     &REG&,2000h
    JNS     br1
    ADD     &REG&,8000h+5Ah

br1:
    ENDM

shift_up MACRO REG
    LOCAL BR1
    SUB     &REG&,2000h
    JNS     br1
    ADD     &REG&,8000h-5Ah

br1:
    ENDM