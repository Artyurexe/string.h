#define BUFF_SIZE 100
#include <check.h>
#include "s21_sprintf.h"
#include <limits.h>

START_TEST(d_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char format[] = "Decimal %hd, %d, %ld of different sizes.";
  short var1 = 0;
  int var2 = 0;
  long int var3 = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2, var3),
                   sprintf(str2, format, var1, var2, var3));
  ck_assert_str_eq(str1, str2);

  var1 = (short)INT32_MAX;
  var2 = INT32_MAX;
  var3 = INT64_MAX;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2, var3),
                   sprintf(str2, format, var1, var2, var3));
  ck_assert_str_eq(str1, str2);

  var1 = (short)INT32_MIN;
  var2 = INT32_MIN;
  var3 = INT64_MIN;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2, var3),
                   sprintf(str2, format, var1, var2, var3));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, var3, var3, var3),
                   sprintf(str2, format, var3, var3, var3));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(d_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Let's test flag combinations %+-0 40d.";
  int var = 21;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Let's test flag combinations %+-040d.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Let's test flag combinations %+040d.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Let's test flag combinations %040d.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Let's test flag combinations %-40d.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Let's test flag combinations %+d.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(d_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %20d";
  int var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -20, var),
                   sprintf(str2, format, -20, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % *d";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % *d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  var = -3;
  format = "Min field width %10d";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-10d";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(d_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Integer precicion %.20d";
  int var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Integer precicion %.*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -20, var),
                   sprintf(str2, format, -20, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Integer precicion %.*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Integer precicion %0.*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Integer precicion %+.*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Integer precicion % .*d";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  var = -3;
  format = "Integer precicion %.10d";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(ld_hd_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%+0.*ld";
  long val1 = 999999999999;
  ck_assert_int_eq(s21_sprintf(str1, format, 10, val1),
                   sprintf(str2, format, 10, val1));

  ck_assert_str_eq(str1, str2);

  format = "%010hd";
  short val2 = -999;
  ck_assert_int_eq(s21_sprintf(str1, format, 10, val2),
                   sprintf(str2, format, 10, val2));

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(i_random) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Integer precicion %.20i";
  int var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Here is long %+0.*li (same as d)";
  long var1 = 999999999999;
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var1),
                   sprintf(str2, format, 10, var1));
  ck_assert_str_eq(str1, str2);

  format = "Everythind at once %+-*.*i, %i";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, 10, var, var),
                   sprintf(str2, format, 20, 10, var, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(u_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lu, %u, %hu";
  long unsigned val1 = ULONG_MAX;
  unsigned val2 = 42211224;
  short unsigned val3 = USHRT_MAX;

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  val2 = UINT32_MAX;
  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val2),
                   sprintf(str2, format, val1, val2, val2));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val1, val1),
                   sprintf(str2, format, val1, val1, val1));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val3, val3, val3),
                   sprintf(str2, format, val3, val3, val3));
  ck_assert_str_eq(str1, str2);

  val1 = 0;
  val2 = 0;
  val3 = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(u_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Flags %+u unsigned.";
  unsigned var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 32;
  format = "Flags % u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Flags %+-0 40u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Flags %+-040u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Flags %+040u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Flags %040u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Flags %-40u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Flags %+u unsigned.";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(u_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %20u";
  unsigned var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % *u";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(u_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Unsigned precicion %.20u";
  unsigned var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Unsigned precicion %.*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Unsigned precicion %.*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Unsigned precicion %0.*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Unsigned precicion %+.*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Unsigned precicion % .*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Unsigned precicion %*.*u";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, 10, var),
                   sprintf(str2, format, 20, 10, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(o_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lo, %o, %ho";
  long int val1 = LONG_MAX;
  int val2 = INT_MAX;
  short int val3 = SHRT_MAX;

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val1, val1),
                   sprintf(str2, format, val1, val1, val1));
  ck_assert_str_eq(str1, str2);

  val1 = LONG_MIN;
  val2 = INT_MIN;
  val3 = SHRT_MIN;

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val1, val1),
                   sprintf(str2, format, val1, val1, val1));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val3, val3, val3),
                   sprintf(str2, format, val3, val3, val3));
  ck_assert_str_eq(str1, str2);

  val1 = 0;
  val2 = 0;
  val3 = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  long unsigned uval1 = ULONG_MAX;
  unsigned uval2 = UINT_MAX;
  short unsigned uval3 = USHRT_MAX;

  ck_assert_int_eq(s21_sprintf(str1, format, uval1, uval2, uval3),
                   sprintf(str2, format, uval1, uval2, uval3));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, uval1, uval1, uval1),
                   sprintf(str2, format, uval1, uval1, uval1));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(o_width_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %20o";
  int var = INT_MAX;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-o";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % *o";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+#*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 13, var),
                   sprintf(str2, format, 13, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % #*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 14, var),
                   sprintf(str2, format, 14, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %- #*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 15, var),
                   sprintf(str2, format, 15, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %- #0o";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 0;

  format = "Min field width %*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 16, var),
                   sprintf(str2, format, 16, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 17, var),
                   sprintf(str2, format, 17, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0#*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+#*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 19, var),
                   sprintf(str2, format, 19, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % #*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %- #*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 21, var),
                   sprintf(str2, format, 21, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(o_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Octal precicion %.20o";
  unsigned var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %0.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %#.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  var = UINT_MAX;
  format = "Octal precicion %0.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %+.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion % .*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 13, var),
                   sprintf(str2, format, 13, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %# .*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 14, var),
                   sprintf(str2, format, 14, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %#+.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 15, var),
                   sprintf(str2, format, 15, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %*.*o";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, 10, var),
                   sprintf(str2, format, 20, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %20.10o";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Octal precicion %-#20.10o";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(x_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%lx, %x, %hx";
  long int val1 = LONG_MAX;
  int val2 = INT_MAX;
  short int val3 = SHRT_MAX;

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  format = "%lX, %X, %hx";

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val1, val1),
                   sprintf(str2, format, val1, val1, val1));
  ck_assert_str_eq(str1, str2);

  val1 = LONG_MIN;
  val2 = INT_MIN;
  val3 = SHRT_MIN;

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val1, val1, val1),
                   sprintf(str2, format, val1, val1, val1));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, val3, val3, val3),
                   sprintf(str2, format, val3, val3, val3));
  ck_assert_str_eq(str1, str2);

  val1 = 0;
  val2 = 0;
  val3 = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, val1, val2, val3),
                   sprintf(str2, format, val1, val2, val3));
  ck_assert_str_eq(str1, str2);

  long unsigned uval1 = ULONG_MAX;
  unsigned uval2 = UINT_MAX;
  short unsigned uval3 = USHRT_MAX;

  ck_assert_int_eq(s21_sprintf(str1, format, uval1, uval2, uval3),
                   sprintf(str2, format, uval1, uval2, uval3));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, uval1, uval1, uval1),
                   sprintf(str2, format, uval1, uval1, uval1));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(x_width_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %20x";
  int var = INT_MAX;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-x";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % *X";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+#*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 13, var),
                   sprintf(str2, format, 13, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % #*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 14, var),
                   sprintf(str2, format, 14, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %- #*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 15, var),
                   sprintf(str2, format, 15, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %- #0X";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 0;

  format = "Min field width %*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 16, var),
                   sprintf(str2, format, 16, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 17, var),
                   sprintf(str2, format, 17, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0#*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+#*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 19, var),
                   sprintf(str2, format, 19, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width % #*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %- #*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 21, var),
                   sprintf(str2, format, 21, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(x_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Hexadecimal precicion %.20x";
  unsigned var = 42;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %.*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, var),
                   sprintf(str2, format, 20, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %0.*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %#.*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %.*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  var = UINT_MAX;
  format = "Hexadecimal precicion %0.*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %+.*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion % .*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 13, var),
                   sprintf(str2, format, 13, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %# .*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 14, var),
                   sprintf(str2, format, 14, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %#+.*X";
  ck_assert_int_eq(s21_sprintf(str1, format, 15, var),
                   sprintf(str2, format, 15, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %*.*x";
  ck_assert_int_eq(s21_sprintf(str1, format, 20, 10, var),
                   sprintf(str2, format, 20, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %20.10x";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Hexadecimal precicion %-#20.10X";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_suite_sprintf(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf tests");
  tc = tcase_create("SPRINTF TESTS");
  tcase_add_test(tc, d_len);
  tcase_add_test(tc, d_flags);
  tcase_add_test(tc, d_width);
  tcase_add_test(tc, d_precision);
  tcase_add_test(tc, ld_hd_flags);

  tcase_add_test(tc, i_random);

  tcase_add_test(tc, u_len);
  tcase_add_test(tc, u_flags);
  tcase_add_test(tc, u_width);
  tcase_add_test(tc, u_precision);

  tcase_add_test(tc, o_len);
  tcase_add_test(tc, o_width_flags);
  tcase_add_test(tc, o_precision);

  tcase_add_test(tc, x_len);
  tcase_add_test(tc, x_width_flags);
  tcase_add_test(tc, x_precision);

  suite_add_tcase(s, tc);

  return s;
}


int main() {
  Suite *s = suite_create("s21_sprintf tests");
  TCase *tc = tcase_create("SPRINTF TESTS");
  SRunner *sr = srunner_create(s);
  suite_add_tcase(s, tc);
  tcase_add_test(tc, d_len);
  tcase_add_test(tc, d_flags);
  tcase_add_test(tc, d_width);
  tcase_add_test(tc, d_precision);
  tcase_add_test(tc, ld_hd_flags);

  tcase_add_test(tc, i_random);

  tcase_add_test(tc, u_len);
  tcase_add_test(tc, u_flags);
  tcase_add_test(tc, u_width);
  tcase_add_test(tc, u_precision);

  tcase_add_test(tc, o_len);
  tcase_add_test(tc, o_width_flags);
  tcase_add_test(tc, o_precision);

  tcase_add_test(tc, x_len);
  tcase_add_test(tc, x_width_flags);
  tcase_add_test(tc, x_precision);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);
  return 0;
}