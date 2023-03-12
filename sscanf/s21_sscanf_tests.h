#include "../standard_functions/s21_string.h"
#include "s21_sscanf.h"

#include <check.h>
#include <string.h>

#define BUFFERSIZE 1024
#define BUFF_SIZE 100
#define EPS 0.000001f

Suite *s21_sscanf_test(void);