#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include "s21_string.h"

typedef enum specifier {
    NONE_SPEC,
    CHAR,
    DECIMAL,
    INT,
    SCI_e,
    SCI_E,
    FLOAT,
    SHORT_FLOAT_g,
    SHORT_FLOAT_G,
    UNSIGNED_OCT,
    STR,
    UNSIGNED_DEC_INT,
    UNSIGNED_HEX_x,
    UNSIGNED_HEX_X,
    POINTER_ADDR,
    N_OF_SCANNED_CHARS_UNTIL_N_OCCURS,
    PERCENT_CHAR
} specifier;


#endif
