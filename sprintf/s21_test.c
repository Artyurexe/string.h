#include "s21_sprintf_tests.h"

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

START_TEST(e_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%e, %Le";
  double var1 = 0;
  long double var2 = 0;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = DBL_MAX;
  var2 = LDBL_MAX;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = DBL_MAX * 1e20;
  var2 = LDBL_MAX * 1e20;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = DBL_MIN / 2;
  var2 = LDBL_MIN / 2;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, var2, var1),
                   sprintf(str2, format, var2, var1));
  ck_assert_str_eq(str1, str2);

  var1 = 1 / 3;
  var2 = 1 / 6;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_inf) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%10E, %Le";
  double var1 = DBL_MAX * 1e20;
  long double var2 = LDBL_MAX * 1e20;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%+e, %+LE";

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "% E, % Le";

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%e, %LE";
  var1 = -DBL_MAX * 1e20;
  var2 = -LDBL_MAX * 1e20;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = NAN;
  var2 = NAN;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 50E";
  double var = DBL_MAX / 3;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+40e";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%040E";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%-40e";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+-40E";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%e% -40E";
  ck_assert_int_eq(s21_sprintf(str1, format, var, var),
                   sprintf(str2, format, var, var));
  ck_assert_str_eq(str1, str2);

  format = "%-040e";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+ 40e";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "% -+040e";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%#+-40E";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %40e";
  double var = -DBL_MIN;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*E";
  ck_assert_int_eq(s21_sprintf(str1, format, 40, var),
                   sprintf(str2, format, 40, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -40, var),
                   sprintf(str2, format, -40, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*E";
  ck_assert_int_eq(s21_sprintf(str1, format, 40, var),
                   sprintf(str2, format, 40, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+-*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 41, var),
                   sprintf(str2, format, 41, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*E";
  ck_assert_int_eq(s21_sprintf(str1, format, 42, var),
                   sprintf(str2, format, 42, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(e_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.18e";
  double var = 42.1;
  long double lvar = 4;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "%#.*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "%.*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "%0.*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "%+.*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "% .*e";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  var = -3;
  format = "%.10e";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 15.35;
  format = "%.17Le";
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.0Le";
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.Le";
  lvar = 12.000002121;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.15e";
  var = 0.000000000000000111;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.17Le";
  lvar = -14.4224422424422449999;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(f_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%f, %Lf";
  double var1 = 0;
  long double var2 = 0;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = 1 / 3;
  var2 = 1 / 6;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%Lf";
  var2 = 513515.131513515151351;
  ck_assert_int_eq(s21_sprintf(str1, format, var2),
                   sprintf(str2, format, var2));
  ck_assert_str_eq(str1, str2);

  format = "%10Lf";
  var2 = 15.35;
  ck_assert_int_eq(s21_sprintf(str1, format, var2),
                   sprintf(str2, format, var2));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, "%f", 0.0001),
                   sprintf(str2, "%f", 0.0001));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(f_inf) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%f, %Lf";
  double var1 = DBL_MAX * 1e20;
  long double var2 = LDBL_MAX * 1e20;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%+f, %+Lf";

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "% f, % Lf";

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%f, %Lf";
  var1 = -DBL_MAX * 1e20;
  var2 = -LDBL_MAX * 1e20;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = NAN;
  var2 = NAN;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(f_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% f";
  double var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "% 20f";
  var = 99.9999999;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+40f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%040f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = -99.9999999;
  format = "%-40f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+-40f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%f% -40f";
  ck_assert_int_eq(s21_sprintf(str1, format, -var, var),
                   sprintf(str2, format, -var, var));
  ck_assert_str_eq(str1, str2);

  format = "%-040f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+ 40f";
  ck_assert_int_eq(s21_sprintf(str1, format, -var),
                   sprintf(str2, format, -var));
  ck_assert_str_eq(str1, str2);

  format = "% -+040f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(f_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %40f";
  double var = -DBL_MIN;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 40, var),
                   sprintf(str2, format, 40, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -40, var),
                   sprintf(str2, format, -40, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 40, var),
                   sprintf(str2, format, 40, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+-*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 41, var),
                   sprintf(str2, format, 41, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 42, var),
                   sprintf(str2, format, 42, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(f_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.20f";
  double var = 42;
  long double lvar = 4;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -10, var),
                   sprintf(str2, format, -10, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "%.*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "%0.*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "%+.*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "%#+.*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 13, var),
                   sprintf(str2, format, 13, var));
  ck_assert_str_eq(str1, str2);

  format = "% .*f";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  var = -3;
  format = "%.10f";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 15.35;
  format = "%.17Lf";
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.0Lf";
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.Lf";
  lvar = 12.000002121;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.15f";
  var = 0.000000000000000111;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.17Lf";
  lvar = -14.4224422424422449999;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.10Lf";
  lvar = -99.99999999999999;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_len) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%g, %LG";
  double var1 = 0;
  long double var2 = 0;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = DBL_MAX;
  var2 = LDBL_MAX;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = DBL_MAX * 1e20;
  var2 = LDBL_MAX * 1e20;
  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = DBL_MIN / 2;
  var2 = LDBL_MIN / 2;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, var2, var1),
                   sprintf(str2, format, var2, var1));
  ck_assert_str_eq(str1, str2);

  var1 = 1 / 3;
  var2 = 1 / 6;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%LG";
  var2 = 0.000005;
  ck_assert_int_eq(s21_sprintf(str1, format, var2),
                   sprintf(str2, format, var2));
  ck_assert_str_eq(str1, str2);

  format = "%g";
  var1 = 0.005;
  ck_assert_int_eq(s21_sprintf(str1, format, var1),
                   sprintf(str2, format, var1));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_inf) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%G, %Lg";
  double var1 = DBL_MAX * 1e20;
  long double var2 = LDBL_MAX * 1e20;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%+g, %+Lg";

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "% G, % LG";

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  format = "%g, %Lg";
  var1 = -DBL_MAX * 1e20;
  var2 = -LDBL_MAX * 1e20;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);

  var1 = NAN;
  var2 = NAN;

  ck_assert_int_eq(s21_sprintf(str1, format, var1, var2),
                   sprintf(str2, format, var1, var2));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "% 50G";
  double var = DBL_MAX / 3;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+40g";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%040G";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%-40g";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+-40G";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%e% -40G";
  ck_assert_int_eq(s21_sprintf(str1, format, var, var),
                   sprintf(str2, format, var, var));
  ck_assert_str_eq(str1, str2);

  format = "%-040g";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%+ 40g";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "% -+040G";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%g";
  var = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_width) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "Min field width %40g";
  double var = -DBL_MIN;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %*G";
  ck_assert_int_eq(s21_sprintf(str1, format, 40, var),
                   sprintf(str2, format, 40, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -40, var),
                   sprintf(str2, format, -40, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %-*g";
  ck_assert_int_eq(s21_sprintf(str1, format, 40, var),
                   sprintf(str2, format, 40, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %+-*G";
  ck_assert_int_eq(s21_sprintf(str1, format, 41, var),
                   sprintf(str2, format, 41, var));
  ck_assert_str_eq(str1, str2);

  format = "Min field width %0*g";
  ck_assert_int_eq(s21_sprintf(str1, format, 42, var),
                   sprintf(str2, format, 42, var));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_precision) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];

  char *format = "%.18G";
  double var = 42.1;
  long double lvar = 4;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.5g";
  var = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.g";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 0.0004;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = -0.0004;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.*g";
  var = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  ck_assert_int_eq(s21_sprintf(str1, format, -18, var),
                   sprintf(str2, format, -18, var));
  ck_assert_str_eq(str1, str2);

  var = 0;
  ck_assert_int_eq(s21_sprintf(str1, format, 0, var),
                   sprintf(str2, format, 0, var));
  ck_assert_str_eq(str1, str2);

  format = "%.*G";
  ck_assert_int_eq(s21_sprintf(str1, format, 10, var),
                   sprintf(str2, format, 10, var));
  ck_assert_str_eq(str1, str2);

  format = "%0.*g";
  ck_assert_int_eq(s21_sprintf(str1, format, 11, var),
                   sprintf(str2, format, 11, var));
  ck_assert_str_eq(str1, str2);

  format = "%+.*G";
  ck_assert_int_eq(s21_sprintf(str1, format, 12, var),
                   sprintf(str2, format, 12, var));
  ck_assert_str_eq(str1, str2);

  format = "% .*g";
  ck_assert_int_eq(s21_sprintf(str1, format, 18, var),
                   sprintf(str2, format, 18, var));
  ck_assert_str_eq(str1, str2);

  var = -3;
  format = "%.10G";
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  var = 15.35;
  format = "%.17Lg";
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.0LG";
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.Lg";
  lvar = 12.000002121;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);

  format = "%.15G";
  var = 0.000000000000000111;
  ck_assert_int_eq(s21_sprintf(str1, format, var), sprintf(str2, format, var));
  ck_assert_str_eq(str1, str2);

  format = "%.17Lg";
  lvar = -14.4224422424422449999;
  ck_assert_int_eq(s21_sprintf(str1, format, lvar),
                   sprintf(str2, format, lvar));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_trailing_zero) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.50300;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_large) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 5131.43141;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_small) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%g";
  double hex = 0.123000;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(g_mantiss_flags) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char format[] = "%5.8g";
  double hex = 0.0000005;
  ck_assert_int_eq(s21_sprintf(str1, format, hex), sprintf(str2, format, hex));
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(pointer) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int val = 90;
  double val2 =  123.120000;
  float val3 = 321.8778;
  char ch = 'u';
  char str[10] = "Hello";
  char format[] = "Pointer:%p double:%p float:%p char: %p string:%p";
  s21_sprintf(str1, format, &val, &val2, &val3, &ch, str),
  sprintf(str2, format,  &val, &val2, &val3, &ch, str);

  ck_assert_str_eq(str1,  str2);
}
END_TEST

START_TEST(width_pointer_on_number_1) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int val = 0;
  double val2 =  123.120000;
  char format[] = "int:%7p double:%17p";
  s21_sprintf(str1, format, &val, &val2),
  sprintf(str2, format,&val, &val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_pointer_on_number_2) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  float val1 = 3214.77;
  int val2 = 3;
  char format[] = "float:%7p %10p";
  s21_sprintf(str1, format, &val1, &val2);
  sprintf(str2, format,&val1, &val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_pointer_on_mix) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  double val =  123.12;
  char str[6] = "Hello";
  char format[] = "double:%7p string:%2p";
  s21_sprintf(str1, format, &val, str),
  sprintf(str2, format,&val, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_pointer_on_strchar) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  char str[6] = "Hello";
  char format[] = "char:%16p string:%7p";
  s21_sprintf(str1, format, &ch, str),
  sprintf(str2, format, &ch, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(alignment_pointer_on_number) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int val = INT32_MAX;
  double val2 =  123.120000;
  char format[] = "int:%-p double:%-p";
  s21_sprintf(str1, format, &val, &val2),
  sprintf(str2, format,&val, &val2);
  ck_assert_str_eq(str1, str2);
  
  float val3 = 3214.77;
  val = 3;
  char format1[] = "float:%7p%10p";
  s21_sprintf(str1, format1, &val3, &val);
  sprintf(str2, format1,&val3, &val);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(alignment_pointer_on_mix) {
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  double val =  123.12;
  char str[6] = "Hello";
  char format[] = "int:%-p string:%-p char:%-p";
  s21_sprintf(str1, format, &val, str, &ch),
  sprintf(str2, format,&val, str, &ch);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(null_pointer_on_mix_1){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  double val =  123.12;
  char str[6] = "Hello";
  char format[] = "int:%0p string:%0p char:%0p";
  s21_sprintf(str1, format, &val, str, &ch),
  sprintf(str2, format,&val, str, &ch);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(null_pointer_on_mix_2){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  int val =  INT32_MAX;
  char str[6] = "Hello";
  char format[] = "int:%0p string:%0p char:%0p";
  s21_sprintf(str1, format, &val, str, &ch),
  sprintf(str2, format,&val, str, &ch);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_and_alignment_pointer_on_mix){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  int val =  INT32_MAX;
  double val2 = 0.0;
  char str[6] = "Hello";
  char *format = "int:%-20p string:%-20p char:%-5p double:%-20p";
  s21_sprintf(str1, format, &val, str, &ch, &val2);
  sprintf(str2, format,&val, str, &ch, &val2);

  format = "int:%-4p string:%-5p char:%-1p double:%-2p";
  s21_sprintf(str1, format, &val, str, &ch,&val2);
  sprintf(str2, format,&val, str, &ch, &val2);
  ck_assert_str_eq(str1, str2);

  format = "int:%-17p string:%-5p char:%-4p double:%-8p";
  s21_sprintf(str1, format, &val, str, &ch, &val2);
  sprintf(str2, format,&val, str, &ch, &val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_and_null_pointer_on_mix){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  int val =  INT32_MAX;
  double val2 = 0.0;
  char str[6] = "Hello";
  char *format = "int:%020p string:%020p char:%05p double:%020p";
  s21_sprintf(str1, format, &val, str, &ch, &val2);
  sprintf(str2, format,&val, str, &ch, &val2);

  format = "int:%04p string:%05p char:%01p double:%02p";
  s21_sprintf(str1, format, &val, str, &ch,&val2);
  sprintf(str2, format,&val, str, &ch, &val2);
  ck_assert_str_eq(str1, str2);

  format = "int:%017p string:%05p char:%04p double:%08p";
  s21_sprintf(str1, format, &val, str, &ch, &val2);
  sprintf(str2, format,&val, str, &ch, &val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(mix_pointer_on_mix_1){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  int val =  INT32_MAX;
  double val2 = -0.01;
  char *format = "int:%0-20p char:%0-5p double:%-020p";
  s21_sprintf(str1, format, &val, &ch, &val2);
  sprintf(str2, format,&val, &ch, &val2);
}
END_TEST

START_TEST(mix_pointer_on_mix_2){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  int val =  INT32_MAX;
  double val2 = -0.01;
  char *format = "int:%-04p char:%-01p double:%-2p";
  s21_sprintf(str1, format, &val, &ch,&val2);
  sprintf(str2, format,&val, &ch, &val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(mix_pointer_on_mix_3){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  char ch  = 'p';
  int val =  INT32_MAX;
  double val2 = -0;
  char *format = "int:%017p char:%04p double:%-08p";
  s21_sprintf(str1, format, &val, &ch, &val2);
  sprintf(str2, format,&val, &ch, &val2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(spec_n_1){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int val =  INT32_MAX;
  int n  = 0;
  int n1 = 0;
  char *format = "int:%17p %n";
  s21_sprintf(str1, format, &val, &n);
  sprintf(str2, format,&val, &n1);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n, n1);
}
END_TEST

START_TEST(spec_n_2){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int val =  INT32_MAX;
  int n  = 0;
  int n1 = 0;
  int n2  = 0;
  int n3 = 0;
  char ch = 'r';
  char *format = "int:%-20p %n char:%3p%n";
  s21_sprintf(str1, format, &val, &n, &ch, &n2);
  sprintf(str2, format,&val, &n1, &ch, &n3);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(n2, n3);
}
END_TEST

START_TEST(spec_n_with_tab){
  char str1[BUFF_SIZE];
  char str2[BUFF_SIZE];
  int val =  INT32_MAX;
  int n  = 0;
  int n1 = 0;
  int n2  = 0;
  int n3 = 0;
  char *format = "int:%-20p %n \t%n";
  s21_sprintf(str1, format, &val, &n, &n2);
  sprintf(str2, format,&val, &n1, &n3);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n, n1);
  ck_assert_int_eq(n2, n3);
}
END_TEST

START_TEST(sprintf_wchar_NULL) {
  char str1[100];
  char str2[100];
  char *format = "%lc";
  wchar_t *stringLong = S21_NULL;
  s21_sprintf(str1, format, stringLong);
  sprintf(str2, format, stringLong);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wstr) {
  char str1[1000];
  char str2[1000];
  wchar_t s = 0xC9;
  wchar_t str[10] = {0};
  str[0] = s;
  str[1] = s;
  char *format = "%-10ls";
  s21_sprintf(str1, format, str);
  sprintf(str2, format, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_wchar) {
  char str1[1000];
  char str2[1000];

  char *format = "%3lc";
  wchar_t longChar = 0xC9;
  s21_sprintf(str1, format, longChar);
  sprintf(str2, format, longChar);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_string) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%*sba";
  char str[] = "ooooooo";
  s21_sprintf(str1, format, 5, str);
  sprintf(str2, format, 5, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_char) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is a simple b%cba";
  char c = 'c';
  s21_sprintf(str1, format, c);
  sprintf(str2, format, c);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(sprintf_char_spec_both) {
  char str1[1000];
  char str2[1000];
  char format[] = "This is %4c simple %-1s in %2c %*s";
  char c = 'a';
  char str[] = "booba";
  s21_sprintf(str1, format, c, str, c, 9, str);
  sprintf(str2, format, c, str, c, 9, str);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_sprintf_test(void) {
  Suite *s = suite_create("s21_sprintf tests");
  TCase *tc = tcase_create("SPRINTF TESTS");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, pointer);
  tcase_add_test(tc, width_pointer_on_number_1);
  tcase_add_test(tc, width_pointer_on_number_2);
  tcase_add_test(tc, width_pointer_on_mix);
  tcase_add_test(tc, width_pointer_on_strchar);
  tcase_add_test(tc, alignment_pointer_on_number);
  tcase_add_test(tc, alignment_pointer_on_mix);
  tcase_add_test(tc, null_pointer_on_mix_1);
  tcase_add_test(tc, null_pointer_on_mix_2);
  tcase_add_test(tc, width_and_alignment_pointer_on_mix);
  tcase_add_test(tc, width_and_null_pointer_on_mix);
  tcase_add_test(tc, mix_pointer_on_mix_1);
  tcase_add_test(tc, mix_pointer_on_mix_2);
  tcase_add_test(tc, mix_pointer_on_mix_3);
  
  tcase_add_test(tc, spec_n_1);
  tcase_add_test(tc, spec_n_2);
  tcase_add_test(tc, spec_n_with_tab);

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

  tcase_add_test(tc, e_len);
  tcase_add_test(tc, e_inf);
  tcase_add_test(tc, e_flags);
  tcase_add_test(tc, e_width);
  tcase_add_test(tc, e_precision);

  tcase_add_test(tc, f_len);
  tcase_add_test(tc, f_inf);
  tcase_add_test(tc, f_flags);
  tcase_add_test(tc, f_width);
  tcase_add_test(tc, f_precision);

  tcase_add_test(tc, g_len);
  tcase_add_test(tc, g_inf);
  tcase_add_test(tc, g_flags);
  tcase_add_test(tc, g_width);
  tcase_add_test(tc, g_precision);
  tcase_add_test(tc, g_trailing_zero);
  tcase_add_test(tc, g_large);
  tcase_add_test(tc, g_small);
  tcase_add_test(tc, g_mantiss_flags);

  tcase_add_test(tc, sprintf_char);
  tcase_add_test(tc, sprintf_string);
  tcase_add_test(tc, sprintf_wstr);
  tcase_add_test(tc, sprintf_wchar);
  tcase_add_test(tc, sprintf_wchar_NULL);
  tcase_add_test(tc, sprintf_char_spec_both);
  return s;
}
