#ifndef SCUP_CUPTYPE_H_INCLUDED
#define SCUP_CUPTYPE_H_INCLUDED

typedef enum Set_linespace_mode {
    INTERACTIVE,
    BATCH
} set_linespace_mode;

typedef enum Ctrl_char {
    LF = 10,        /* line feed */
    VT = 11,        /* vertical tab */
    FF = 12,        /* form feed */
    CR = 13,        /* carriage return */
    ESC = 27        /* escape code */
} ctrl_char;

#endif /* SCUP_CUPTYPE_H_INCLUDED */
