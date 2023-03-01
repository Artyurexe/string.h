#define BUFF_SIZE 200
#include <check.h>
#include "s21_sprintf.h"
#include <limits.h>

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

Suite *s21_suite_sprintf(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_sprintf tests");
  tc = tcase_create("SPRINTF TESTS");
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

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  Suite *s = suite_create("s21_sprintf tests");
  TCase *tc = tcase_create("SPRINTF TESTS");
  SRunner *sr = srunner_create(s);
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

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);
  return 0;
}