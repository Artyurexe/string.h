#include <check.h>
#include <string.h>
#include "s21_sscanf.h"

#define BUFFERSIZE 1024
#define BUFF_SIZE 100
#define EPS 0.000001f

//empty
START_TEST(test_empty) {
  char fstr[] = "";
  char str[] = "";
  int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

//%s
START_TEST(test_s_single) {
    char str1[30];
    char str2[30];
    int res1 = s21_sscanf("string", "%s", str1);
    int res2 = sscanf("string", "%s", str2);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s_two_normal) {
    char str1[30];
    char str2[30];
    char str3[30];
    char str4[30];
    int res1 = s21_sscanf("string s", "%s%s", str1, str2);
    int res2 = sscanf("string s", "%s%s", str3, str4);
    ck_assert_pstr_eq(str1, str3);
    ck_assert_pstr_eq(str2, str4);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s_two_bad) {
    char str1[30];
    char str2[30];
    char str3[30];
    char str4[30];
    s21_sscanf("string \0", "%s%s", str1, str2);
    sscanf("string \0", "%s%s", str3, str4);
    ck_assert_pstr_eq(str1, str3);
    ck_assert_pstr_eq(str2, str4);
}
END_TEST

START_TEST(test_s_two_with_extra_spaces) {
    char str1[30];
    char str2[30];
    char str3[30];
    char str4[30];
    int res1 = s21_sscanf("string    str    ", "%s%s", str1, str2);
    int res2 = sscanf("string    str    ", "%s%s", str3, str4);
    ck_assert_pstr_eq(str1, str3);
    ck_assert_pstr_eq(str2, str4);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s_int) {
    char str1[30];
    char str2[30];
    int res1 = s21_sscanf("    1", "%s", str1);
    int res2 = sscanf("    1", "%s", str2);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
}
END_TEST

//%c
START_TEST(test_c_single) {
    char c1;
    char c2;
    int res1 = s21_sscanf("a", "%c", &c1);
    int res2 = sscanf("a", "%c", &c2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_c_null_terminator) {
    char c1;
    char c2;
    int res1 = s21_sscanf("\0", "%c", &c1);
    int res2 = sscanf("\0", "%c", &c2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_c_empty_string) {
    char c1;
    char c2;
    int res1 = s21_sscanf("", "%c", &c1);
    int res2 = sscanf("", "%c", &c2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_c_two_normal) {
    char c1;
    char c2;
    char c3;
    char c4;
    int res1 = s21_sscanf("a a", "%c%c", &c1, &c2);
    int res2 = sscanf("a a", "%c%c", &c3, &c4);
    ck_assert_int_eq(c1, c3);
    ck_assert_int_eq(c2, c4);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_c_two_special) {
    char c1;
    char c2;
    char c3;
    char c4;
    int res1 = s21_sscanf("\n \0", "%c%c", &c1, &c2);
    int res2 = sscanf("\n \0", "%c%c", &c3, &c4);
    ck_assert_int_eq(c1, c3);
    ck_assert_int_eq(c2, c4);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_c_two_bad) {
    char c1;
    char c2;
    char c3;
    char c4;
    int res1 = s21_sscanf("c ", "%c%c", &c1, &c2);
    int res2 = sscanf("c ", "%c%c", &c3, &c4);
    ck_assert_int_eq(c1, c3);
    ck_assert_int_eq(c2, c4);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_spec_c_2) {
    char format[] = "%c";
    char str[] = "\t\n\n  1 \n  \t";
    char c1, c2;

    int16_t res1 = s21_sscanf(str, format, &c1);
    int16_t res2 = sscanf(str, format, &c2);
    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_spec_c_4) {
    char format[] = "%c";
    char str[] = "\t\n\n   \n  \ta";
    char c1, c2;
    int16_t res1 = s21_sscanf(str, format, &c1);
    int16_t res2 = sscanf(str, format, &c2);
    ck_assert_int_eq(res1, res2);
    ck_assert_int_eq(c1, c2);
}
END_TEST

// %d
START_TEST(test_s21_sscanf_test_d_1) {
  char fstr[] = "%d";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_2) {
  char fstr[] = "%d %d";
  char str[] = "  12321  -111";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST
START_TEST(test_s21_sscanf_test_d_3) {
  char fstr[] = "%d%d";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_4) {
  char fstr[] = "%d.%d %*d%d";
  char str[] = "  12321.999  -111   \n 77777";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_5) {
  char fstr[] = "%d%d%%%d%d";
  char str[] = "11111 22222 % 33333";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_6) {
  char fstr[] = "%d%d%d%d";
  char str[] = "12345 0xF 6 7";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_7) {
  char fstr[] = "%d";
  char str[] = "";
  int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_8) {
  char fstr[] = "%d";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_d_9) {
  char fstr[] = "                 %d%d   %d%d";
  char str[] = "-1 -6 -7 -";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

//%hd
START_TEST(test_s21_sscanf_test_hd_1) {
  char fstr[] = "%hd";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  short int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_2) {
  char fstr[] = "%hd %hd";
  char str[] = "  12321  -111";
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_3) {
  char fstr[] = "%hd%hd";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_4) {
  char fstr[] = "%hd.%hd %hd%hd";
  char str[] = "  123219999.999999999  -999999111   \n 99977777";
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_5) {
  char fstr[] = "%hd%hd%hd%hd";
  char str[] = "11111 22222 33333";
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_6) {
  char fstr[] = "%hd%hd%hd%hd";
  char str[] = "12345 0xFF 6 7";
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_7) {
  char fstr[] = "%hd";
  char str[] = "";
  short int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_8) {
  char fstr[] = "%hd";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  short int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hd_9) {
  char fstr[] = "                 %hd%hd%hd%hd";
  char str[] = "-1 -6 -7 -";
  short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

//%ld
START_TEST(test_s21_sscanf_test_ld_1) {
  char fstr[] = "%ld";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_2) {
  char fstr[] = "%ld %ld";
  char str[] = "  12321  -111";
  long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_3) {
  char fstr[] = "%ld%ld";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_4) {
  char fstr[] = "%ld.%ld %ld%ld";
  char str[] = "  12321.999  -111   \n 77777";
  long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_5) {
  char fstr[] = "%ld%ld%ld%ld";
  char str[] = "11111 22222 33333";
  long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_6) {
  char fstr[] = "%ld%ld%ld%ld";
  char str[] = "12345 0xFF 6 7";
  long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_7) {
  char fstr[] = "%ld";
  char str[] = "";
  long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_8) {
  char fstr[] = "%ld";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_ld_9) {
  char fstr[] = "                 %ld%ld%ld%ld";
  char str[] = "-1 -6 -7 -";
  long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

//%lld
START_TEST(test_s21_sscanf_test_lld_1) {
  char fstr[] = "%lld";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  long long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_2) {
  char fstr[] = "%lld %lld";
  char str[] = "  12321  -111";
  long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_3) {
  char fstr[] = "%lld%lld";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_4) {
  char fstr[] = "%lld.%lld %lld%lld";
  char str[] = "  1232199999.99999999999  -1199999999991   \n 7777777777";
  long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_5) {
  char fstr[] = "%lld%lld%lld%lld";
  char str[] = "111111111111111 222222222222222 333333333333333";
  long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_6) {
  char fstr[] = "%lld%lld%lld%lld";
  char str[] = "12345123451234512345 0xFF 6 7";
  long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_7) {
  char fstr[] = "%lld";
  char str[] = "";
  long long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_8) {
  char fstr[] = "%lld";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  long long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lld_9) {
  char fstr[] = "                 %lld%lld%lld%lld";
  char str[] = "-1 -6 -7 -9";
  long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

//%u
START_TEST(test_s21_sscanf_test_u_1) {
  char fstr[] = "%u";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  unsigned int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_2) {
  char fstr[] = "%u %u";
  char str[] = "  12321  -111";
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_3) {
  char fstr[] = "%u%u";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_4) {
  char fstr[] = "%u.%u %u%u";
  char str[] = "  12321.999  -111   \n 77777";
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_5) {
  char fstr[] = "%u%u%u%u";
  char str[] = "11111 22222 33333 -44444444444444";
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_6) {
  char fstr[] = "%u%u%u%u";
  char str[] = "12345 0 -6 7";
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_7) {
  char fstr[] = "%u";
  char str[] = "";
  unsigned int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_8) {
  char fstr[] = "%u";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  unsigned int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_u_9) {
  char fstr[] = "                 %u%u%u%u";
  char str[] = "-1 -6 -7 -9999999999999999999999999";
  unsigned int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

//%hu
START_TEST(test_s21_sscanf_test_hu_1) {
  char fstr[] = "%hu";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  unsigned short int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_2) {
  char fstr[] = "%hu %hu";
  char str[] = "  12321  -111";
  unsigned short int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_3) {
  char fstr[] = "%hu%hu";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  unsigned short int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_4) {
  char fstr[] = "%hu.%hu %hu%%%hu";
  char str[] = "  12321.999  -111%   \n 77777";
  unsigned short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned short int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_5) {
  char fstr[] = "%hu%hu%hu%hu";
  char str[] = "11111 22222 33333 -44444444444444";
  unsigned short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned short int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_6) {
  char fstr[] = "%hu%hu%hu%hu";
  char str[] = "12345 0 -6 7";
  unsigned short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned short int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_7) {
  char fstr[] = "%hu";
  char str[] = "";
  unsigned short int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_8) {
  char fstr[] = "%hu";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  unsigned short int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_hu_9) {
  char fstr[] = "                 %hu%hu%hu%hu";
  char str[] = "-1 -6 -7 -9999999999999999999999999";
  unsigned short int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned short int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

//%lu
START_TEST(test_s21_sscanf_test_lu_1) {
  char fstr[] = "%lu";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  unsigned long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_2) {
  char fstr[] = "%lu %lu";
  char str[] = "  12321  -111";
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_3) {
  char fstr[] = "%lu%lu";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_4) {
  char fstr[] = "%lu.%lu %lu%lu";
  char str[] = "  12321.999  -111   \n 77777";
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_5) {
  char fstr[] = "%lu%lu%lu%lu";
  char str[] = "11111 22222 33333";
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_6) {
  char fstr[] = "%lu%lu%lu%lu";
  char str[] = "12345 0xFF 6 7";
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_7) {
  char fstr[] = "%lu";
  char str[] = "";
  unsigned long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_8) {
  char fstr[] = "%lu";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  unsigned long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lu_9) {
  char fstr[] = "                 %lu%lu%lu%lu";
  char str[] = "-1 -6 -7 -";
  unsigned long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

//%llu
START_TEST(test_s21_sscanf_test_llu_1) {
  char fstr[] = "%llu";
  char str[] = "fdgsdgsdfgdgdfgdgfghvnvcnhg";
  unsigned long long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_2) {
  char fstr[] = "%llu %llu";
  char str[] = "  12321  -111";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_3) {
  char fstr[] = "%llu%llu";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_4) {
  char fstr[] = "%llu.%llu %llu%llu";
  char str[] = "  1232199999.99999999999  -1199999999991   \n 7777777777";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_5) {
  char fstr[] = "%llu%llu%llu%llu";
  char str[] = "999111111111111111 999222222222222222 999333333333333333";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_6) {
  char fstr[] = "%llu%llu%llu%llu";
  char str[] = "12345123451234512345 9xFF 6 7";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long long d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_7) {
  char fstr[] = "%llu";
  char str[] = "";
  unsigned long long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_8) {
  char fstr[] = "%llu";
  char str[] = "\n\n\n\n   \t\t\t\n\n\n";
  unsigned long long int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llu_9) {
  char fstr[] = "                 %llu%llu%llu%llu";
  char str[] = "-1 -6 -7 -9";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long long d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

//%i
START_TEST(test_s21_sscanf_test_i_1) {
  char fstr[] = "%i%i%i%i%i";
  char str[] = "0 0 0 0 00000000000000 0 0 ";
  int a1 = 1, a2 = 1, b1 = 1, b2 = 1, c1 = 1, c2 = 1, d1 = 1, d2 = 1;
  int e1 = 1, e2 = 1;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_2) {
  char fstr[] = "%i %i";
  char str[] = "11111 -11111 -011111 011111 0x11111 -0x11111";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int e1 = 0, e2 = 0, f1 = 0, f2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(e1, e2);
  ck_assert_int_eq(f1, f2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_3) {
  char fstr[] = "%i%i";
  char str[] = "  789789789789789789878678678 \t\n -8987897897888978978978978 ";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_4) {
  char fstr[] = "%i.%i %i%i";
  char str[] = "  012321.0x999999  -01199999   \n -0x77777";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long long int d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_5) {
  char fstr[] = "%i%i%i%i";
  char str[] = "0999111111111111111 0x999222222222222222 999333333333333333";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_6) {
  char fstr[] = "%i%i%i%i";
  char str[] = "     12345123451234512345 0xFF -6 -07ty";
  int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_7) {
  char fstr[] = "%i";
  char str[] = "";
  int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_8) {
  char fstr[] = "%i";
  char str[] = "\n\n\n\n\t\t\t\n\n\n";
  int a1 = 0, a2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1);
  int res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_s21_sscanf_test_i_9) {
  char fstr[] = "                 %i  %i  %i  %i";
  char str[] = "-1 -6 -0X7 -9";
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  unsigned long long d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

//%f
START_TEST(test_s21_sscanf_test_f_1) {
  char fstr[] = "%f%f%f%f%f";
  char str[] = "0 0.0 0000.0000 0.0000000000001 100000000.0000000001";
  float a1 = 1, a2 = 1, b1 = 1, b2 = 1, c1 = 1, c2 = 1, d1 = 1, d2 = 1;
  float e1 = 1, e2 = 1;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_f_2) {
  char fstr[] = "%f%f%f%*f%f";
  char str[] = "1.111 nan inF 0 3333.3333";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_nan(b1);
  ck_assert_float_infinite(c1);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_f_3) {
  char fstr[] = "%f%f";
  char str[] = "999999999999999.9999999999999999 -9999999999999.99999999999999";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_f_4) {
  char fstr[] = "%f%f%f%f%f";
  char str[] = "1. .1 .  .  .  777.777 00000000.0000001 100000000000.000000001";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  float e1 = 0, e2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_f_5) {
  char fstr[] = "   \n\n %4f  \n\n\n \t %9f     %9f %*f         %f";
  char str[] = "0.123456789 -123456789.987654321 +999.999      \n    1.1";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_f_6) {
  char fstr[] = "   \n\n %f  \n\n\n \t %f     %f   =    %f";
  char str[] = "1243.567e-2 -1243.567e+20 +777e-5   =  \n    1e+1";
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

//%lf
START_TEST(test_s21_sscanf_test_lf_1) {
  char fstr[] = "%lf%lf%lf%lf%lf";
  char str[] = "0 0.0 0000.0000 0.0000000000001 100000000.0000000001";
  double a1 = 1, a2 = 1, b1 = 1, b2 = 1, c1 = 1, c2 = 1, d1 = 1, d2 = 1;
  double e1 = 1, e2 = 1;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lf_2) {
  char fstr[] = "%lf%lf%lf%*lf%lf";
  char str[] = "1.111 nan inF 0 3333.3333";
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_nan(b1);
  ck_assert_double_infinite(c1);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lf_3) {
  char fstr[] = "%lf%lf";
  char str[] = "999999999999999.9999999999999999 -9999999999999.99999999999999";
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lf_4) {
  char fstr[] = "%lf%lf%lf%lf%lf";
  char str[] = "1. .1 .  .  .  777.777 00000000.0000001 100000000000.000000001";
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  double e1 = 0, e2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
  ck_assert_double_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lf_5) {
  char fstr[] = "   \n\n %4lf  \n\n\n \t %9lf     %9lf %*lf         %lf";
  char str[] = "321.123456789 -123456789.987654321 +999.999      \n    0.1";
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_lf_6) {
  char fstr[] = "   \n\n %lf  \n\n\n \t %lf     %lf   =    %lf";
  char str[] = "1243.567e-2 -1243.567e+20 +777e-5   =  \n    1e+1";
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

//%llf
START_TEST(test_s21_sscanf_test_llf_1) {
  char fstr[] = "%Lf%Lf%Lf%Lf%Lf";
  char str[] = "1 0.0 0000.0000 0.0000000000001 100000000.0000000001";
  long double a1 = 1, a2 = 1, b1 = 1, b2 = 1, c1 = 1, c2 = 1, d1 = 1, d2 = 1;
  long double e1 = 1, e2 = 1;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq_tol(d1, d2, EPS);
  ck_assert_ldouble_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llf_2) {
  char fstr[] = "%Lf%Lf%Lf%*Lf%Lf";
  char str[] = "1.111 nan inF 0 3333.3333";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq_tol(a1, a2, EPS);
  ck_assert_ldouble_nan(b1);
  ck_assert_ldouble_infinite(c1);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llf_3) {
  char fstr[] = "%Lf%Lf";
  char str[] = "999999999999999.9999999999999999 -9999999999999.99999999999999";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1);
  int res2 = sscanf(str, fstr, &a2, &b2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq_tol(a1, a2, 1e+11);
  ck_assert_ldouble_eq_tol(b1, b2, 1e+11);
}
END_TEST

START_TEST(test_s21_sscanf_test_llf_4) {
  char fstr[] = "%Lf%Lf%Lf%Lf%Lf";
  char str[] = "1. .1 .  .  .  777.777 00000000.0000001 100000000000.000000001";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long double d1 = 0, d2 = 0, e1 = 0, e2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_ldouble_eq_tol(b1, b2, EPS);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
  ck_assert_ldouble_eq(e1, e2);
}
END_TEST

START_TEST(test_s21_sscanf_test_llf_5) {
  char fstr[] = "   \n\n %4Lf  \n\n\n \t %9Lf     %9Lf %*Lf         %Lf";
  char str[] = "321.123456789 -123456789.987654321 +999.999      \n    0.1";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq_tol(d1, d2, EPS);
}
END_TEST

START_TEST(test_s21_sscanf_test_llf_6) {
  char fstr[] = "   \n\n %Lf  \n\n\n \t %Lf     %Lf   =    %Lf";
  char str[] = "1243.567e-2 -1243.567e+10 +777e-5   =  \n    1e+1";
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq_tol(b1, b2, EPS);
  ck_assert_ldouble_eq_tol(c1, c2, EPS);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST
int main() {
    Suite *s1 = suite_create("Tests_for_sscanf");

    TCase *tc_s = tcase_create("Test_string");
    TCase *tc_c = tcase_create("test_char");
    TCase *tc_empty = tcase_create("test_empty");
    TCase *tc_d = tcase_create("test_digit");
    TCase *tc_hd = tcase_create("test_hd");
    TCase *tc_ld = tcase_create("test_ld");
    TCase *tc_lld = tcase_create("test_lld");
    TCase *tc_u = tcase_create("test_u");
    TCase *tc_hu = tcase_create("test_hu");
    TCase *tc_lu = tcase_create("test_lu");
    TCase *tc_llu = tcase_create("test_llu");
    TCase *tc_i = tcase_create("test_i");
    TCase *tc_f = tcase_create("test_f");;
    TCase *tc_lf = tcase_create("test_lf");
    TCase *tc_llf = tcase_create("test_llf");

    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, tc_empty);
    suite_add_tcase(s1, tc_s);
    suite_add_tcase(s1, tc_c);
    suite_add_tcase(s1, tc_d);
    suite_add_tcase(s1, tc_hd);
    suite_add_tcase(s1, tc_ld);
    suite_add_tcase(s1, tc_lld);
    suite_add_tcase(s1, tc_u);
    suite_add_tcase(s1, tc_hu);
    suite_add_tcase(s1, tc_lu);
    suite_add_tcase(s1, tc_llu);
    suite_add_tcase(s1, tc_i);

    //empty
   tcase_add_test(tc_empty, test_empty);
    //%s
    tcase_add_test(tc_s, test_s_single);
    tcase_add_test(tc_s, test_s_two_normal);
    tcase_add_test(tc_s, test_s_two_bad);
    tcase_add_test(tc_s, test_s_two_with_extra_spaces);
    tcase_add_test(tc_s, test_s_int);

    //%c
    tcase_add_test(tc_c, test_c_single);
    tcase_add_test(tc_c, test_c_null_terminator);
    tcase_add_test(tc_c, test_c_empty_string);
    tcase_add_test(tc_c, test_c_two_normal);
    tcase_add_test(tc_c, test_c_two_special);
    tcase_add_test(tc_c, test_c_two_bad);
    tcase_add_test(tc_c, sscanf_spec_c_2);
    tcase_add_test(tc_c, sscanf_spec_c_4);

    //%d
    tcase_add_test(tc_d, test_s21_sscanf_test_d_1);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_2);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_3);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_4);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_5);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_6);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_7);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_8);
    tcase_add_test(tc_d, test_s21_sscanf_test_d_9);

    //%hd
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_1);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_2);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_3);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_4);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_5);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_6);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_7);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_8);
    tcase_add_test(tc_hd, test_s21_sscanf_test_hd_9);
    //%ld
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_1);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_2);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_3);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_4);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_5);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_6);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_7);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_8);
    tcase_add_test(tc_ld, test_s21_sscanf_test_ld_9);
    //%lld
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_1);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_2);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_3);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_4);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_5);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_6);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_7);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_8);
    tcase_add_test(tc_lld, test_s21_sscanf_test_lld_9);

    //%u
    tcase_add_test(tc_u, test_s21_sscanf_test_u_1);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_2);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_3);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_4);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_5);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_6);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_7);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_8);
    tcase_add_test(tc_u, test_s21_sscanf_test_u_9);

    //%hu
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_1);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_2);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_3);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_4);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_5);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_6);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_7);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_8);
    tcase_add_test(tc_hu, test_s21_sscanf_test_hu_9);
    //%lu
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_1);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_2);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_3);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_4);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_5);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_6);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_7);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_8);
    tcase_add_test(tc_lu, test_s21_sscanf_test_lu_9);
    //%llu
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_1);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_2);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_3);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_4);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_5);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_6);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_7);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_8);
    tcase_add_test(tc_llu, test_s21_sscanf_test_llu_9);

    //%i
    tcase_add_test(tc_i, test_s21_sscanf_test_i_1);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_2);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_3);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_4);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_5);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_6);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_7);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_8);
    tcase_add_test(tc_i, test_s21_sscanf_test_i_9);
    //%f
    tcase_add_test(tc_f, test_s21_sscanf_test_f_1);
    tcase_add_test(tc_f, test_s21_sscanf_test_f_2);
    tcase_add_test(tc_f, test_s21_sscanf_test_f_3);
    tcase_add_test(tc_f, test_s21_sscanf_test_f_4);
    tcase_add_test(tc_f, test_s21_sscanf_test_f_5);
    tcase_add_test(tc_f, test_s21_sscanf_test_f_6);

    //%lf
    tcase_add_test(tc_lf, test_s21_sscanf_test_lf_1);
    tcase_add_test(tc_lf, test_s21_sscanf_test_lf_2);
    tcase_add_test(tc_lf, test_s21_sscanf_test_lf_3);
    tcase_add_test(tc_lf, test_s21_sscanf_test_lf_4);
    tcase_add_test(tc_lf, test_s21_sscanf_test_lf_5);
    tcase_add_test(tc_lf, test_s21_sscanf_test_lf_6);

    //%llf
    tcase_add_test(tc_llf, test_s21_sscanf_test_llf_1);
    tcase_add_test(tc_llf, test_s21_sscanf_test_llf_2);
    tcase_add_test(tc_llf, test_s21_sscanf_test_llf_3);
    tcase_add_test(tc_llf, test_s21_sscanf_test_llf_4);
    tcase_add_test(tc_llf, test_s21_sscanf_test_llf_5);
    tcase_add_test(tc_llf, test_s21_sscanf_test_llf_6);


    srunner_run_all(sr, CK_ENV);
    int a = srunner_ntests_failed(sr);
    srunner_free(sr);

    return a == 0 ? 0 : 1;
}