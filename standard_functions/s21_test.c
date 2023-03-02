#include <check.h>
#include <string.h>

#include "s21_string.h"

//memchr
START_TEST(test_for_memchr) {
    char str[30] = "123qwer143";
    ck_assert_pstr_eq(s21_memchr(str, '3', 13), memchr(str, '3', 13));
    ck_assert_pstr_eq(s21_memchr(str, 'e', 13), memchr(str, 'e', 13));
  }
END_TEST

START_TEST(test_for_memchr_not_symbol){
  char str[30] = "123qwer143";
  ck_assert_pstr_eq(s21_memchr(str, 'c', 29), memchr(str, 'c', 29));
}
END_TEST

START_TEST(test_for_memchr_special_symbol){
  char str[30] = "@\\%^&  ";
  ck_assert_pstr_eq(s21_memchr(str, '@', 5), memchr(str, '@', 5));
  ck_assert_pstr_eq(s21_memchr(str, 92, 5), memchr(str, 92, 5));
  ck_assert_pstr_eq(s21_memchr(str, ' ', 5), memchr(str, ' ', 5));
}
END_TEST

START_TEST(test_for_memchr_not_enough_memory){
  char str[30] = "123qwer143";
  ck_assert_pstr_eq(s21_memchr(str, 'r', 5), memchr(str, 'r', 5));
   ck_assert_pstr_eq(s21_memchr(str, 4, 5), memchr(str, 4, 5));
}
END_TEST

START_TEST(test_for_memchr_empty_line){
  char str[30] = "\0";
  ck_assert_pstr_eq(s21_memchr(str, '\0', 5), memchr(str, '\0', 5));
}
END_TEST


//memcmp
START_TEST(test_for_memcmp_output_zero) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    ck_assert_int_eq(s21_memcmp(str, str1, 5), memcmp(str, str1, 5));
    char str4[30] = "zxcd";
    char str5[30] = "zxcd";
    ck_assert_int_eq(s21_memcmp(str4, str5, 5), memcmp(str4, str5, 5));
    char str2[30] = "zxcd";
    char str3[30] = "ZXCD";
    ck_assert_int_eq(s21_memcmp(str2, str3, 0), memcmp(str2, str3, 0));
  }
END_TEST

START_TEST(test_for_memcmp_more_memory) {
   char str2[30] = "123Qwer143";
    char str3[30] = "123Q";
    ck_assert_int_eq(s21_memcmp(str2, str3, 7), memcmp(str2, str3, 7));
    char str4[30] = "123Q";
    char str5[30] = "123Qwer143";
    ck_assert_int_eq(s21_memcmp(str4, str5, 7), memcmp(str4, str5, 7));
}
END_TEST

START_TEST(test_for_memcmp_for_different_register) {
   char str2[30] = "123Qwer143";
    char str3[30] = "123q";
    ck_assert_int_eq(s21_memcmp(str2, str3, 4), memcmp(str2, str3, 4));
    char str4[30] = "123qwer143";
    char str5[30] = "123Q";
    ck_assert_int_eq(s21_memcmp(str4, str5, 4), memcmp(str4, str5, 4));
    char str7[30] = "123qwer143";
    char str8[30] = "123q";
    ck_assert_int_eq(s21_memcmp(str7, str8, 4), memcmp(str7, str8, 4));
    char str9[30] = "123Qwer143";
    char str10[30] = "123Q";
    ck_assert_int_eq(s21_memcmp(str9, str10, 4), memcmp(str9, str10, 4));
}
END_TEST



//memcpy
START_TEST(test_for_memcpy) {
    char str[30] = "123qwer143";
    char str1[30] = "";
    char str2[30] = "";
    s21_memcpy(str1, str, 5);
    memcpy(str2, str, 5);
    ck_assert_pstr_eq(str1, str2);
    char str3[30] = "123qwer143";
    char str4[30] = "";
    char str5[30] = "";
    s21_memcpy(str4, &str3[4], 5);
    memcpy(str5, &str3[4], 5);
    ck_assert_pstr_eq(str4, str5);
    char str6[30] = "123qwer144";
    char str7[30] = "";
    char str8[30] = "";
    s21_memcpy(str7, &str6[4], 10);
    memcpy(str8, &str6[4], 10);
    ck_assert_pstr_eq(str7, str8);
  }
END_TEST

START_TEST(test_for_memcpy_copy_zero_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "";
    char str2[30] = "";
    s21_memcpy(str1, str, 0);
    memcpy(str2, str, 0);
    ck_assert_pstr_eq(str1, str2);
  }
END_TEST

START_TEST(test_for_memcpy_more_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "";
    char str2[30] = "";
    s21_memcpy(str1, str, 15);
    memcpy(str2, str, 15);
    ck_assert_pstr_eq(str1, str2);
  }
END_TEST

//memmove
START_TEST(test_for_memmove_in_own_string) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memmove(&str[5], &str[3], 4);
    memmove(&str1[5], &str1[3], 4);
    ck_assert_pstr_eq(str1, str);

  }
END_TEST

START_TEST(test_for_memmove_in_own_string_more_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memmove(&str[5], &str[9], 4);
    memmove(&str1[5], &str1[9], 4);
    ck_assert_pstr_eq(str1, str);

  }
END_TEST

START_TEST(test_for_memmove_for_null_string) {
    char str[30] = "\0";
    char str1[30] = "\0";
    s21_memmove(str, str, 4);
    memmove(str1, str1, 4);
    ck_assert_pstr_eq(str1, str);

  }
END_TEST

START_TEST(test_for_memmove_for_null_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memmove(str, str, 0);
    memmove(str1, str1, 0);
    ck_assert_pstr_eq(str1, str);

  }
END_TEST

START_TEST(test_for_memmove_more_memory) {
    char str[30] = "234ef";
    char str1[30] = "234ef";
    s21_memmove(str, str, 8);
    memmove(str1, str1, 8);
    ck_assert_pstr_eq(str1, str);

  }
END_TEST

START_TEST(test_for_memmove_in_other_string) {
    char str[30] = "123qwer143";
    char str1[30] = "";
    char str2[30] = "";
    s21_memcpy(str1, str, 5);
    memcpy(str2, str, 5);
    ck_assert_pstr_eq(str1, str2);
    char str3[30] = "123qwer143";
    char str4[30] = "";
    char str5[30] = "";
    s21_memcpy(str4, &str3[4], 5);
    memcpy(str5, &str3[4], 5);
    ck_assert_pstr_eq(str4, str5);
    char str6[30] = "123qwer144";
    char str7[30] = "";
    char str8[30] = "";
    s21_memcpy(str7, &str6[4], 10);
    memcpy(str8, &str6[4], 10);
    ck_assert_pstr_eq(str7, str8);
  }
END_TEST

START_TEST(test_for_memmove_in_other_string_copy_zero_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "";
    char str2[30] = "";
    s21_memcpy(str1, str, 0);
    memcpy(str2, str, 0);
    ck_assert_pstr_eq(str1, str2);
  }
END_TEST

START_TEST(test_for_memmove_in_other_string_more_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "";
    char str2[30] = "";
    s21_memcpy(str1, str, 15);
    memcpy(str2, str, 15);
    ck_assert_pstr_eq(str1, str2);
  }
END_TEST

// memset
START_TEST(test_for_memset) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memset(str, 't', 4);
    memset(str1, 't', 4);
    ck_assert_pstr_eq(str, str1);
  }
END_TEST

START_TEST(test_for_memset_full_change) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memset(str, 't', 10);
    memset(str1, 't', 10);
    ck_assert_pstr_eq(str, str1);
  }
END_TEST

START_TEST(test_for_memset_empty_null) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memset(str, '\0', 4);
    memset(str1, '\0', 4);
    ck_assert_pstr_eq(str, str1);

  }
END_TEST

START_TEST(test_for_memset_more_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "123qwer143";
    s21_memset(str, 67, 15);
    memset(str1, 67, 15);
    ck_assert_pstr_eq(str, str1);

  }
END_TEST

// strcat
START_TEST(test_for_strcat) {
    char str[30] = "123qwer143";
    char str1[30] = "qwer143";
    ck_assert_pstr_eq(s21_strcat(str, str1), strcat(str, str1));
  }
END_TEST

START_TEST(test_for_strcat_with_empty_line) {
    char str[30] = "123qwer143";
    char str1[30] = "\0";
    ck_assert_pstr_eq(s21_strcat(str, str1), strcat(str, str1));
    char str2[30] = "  ";
    char str3[30] = "\0";
    ck_assert_pstr_eq(s21_strcat(str2, str3), strcat(str2, str3));
    char str4[30] = "\0";
    char str5[30] = "\0";
    ck_assert_pstr_eq(s21_strcat(str4, str5), strcat(str4, str5));
  }
END_TEST

//strncat
START_TEST(test_for_strncat) {
    char str[30] = "123qwer143";
    char str1[30] = "qwer143";
    ck_assert_pstr_eq(s21_strncat(str, str1, 7), strncat(str, str1, 7));
    char str2[30] = "123qwer143";
    char str3[30] = "\0";
    ck_assert_pstr_eq(s21_strncat(str2, str3, 1), strncat(str2, str3, 1));
  }
END_TEST

START_TEST(test_for_strncat_with_zero_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "qwer143";
    ck_assert_pstr_eq(s21_strncat(str, str1, 0), strncat(str, str1, 0));
  }
END_TEST

START_TEST(test_for_strncat_more_bytes) {
    char str[30] = "123qwer143";
    char str1[30] = "qwer143";
    ck_assert_pstr_eq(s21_strncat(str, str1, 29), strncat(str, str1, 29));
  }
END_TEST

//


int main() {
  Suite *s1 = suite_create("Tests_for_string");

  TCase *tc_memchr = tcase_create("Tests_for_memchr ");
  TCase *tc_memcmp = tcase_create("Tests_for_memcmp ");
  TCase *tc_memcpy = tcase_create("Tests_for_memcpy ");
  TCase *tc_memmove = tcase_create("Tests_for_memmove ");
  TCase *tc_memset = tcase_create("Tests_for_memset ");
  TCase *tc_strcat = tcase_create("Tests_for_strcat ");
  TCase *tc_strncat = tcase_create("Tests_for_strcat ");

  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc_memchr);
  suite_add_tcase(s1, tc_memcmp);
  suite_add_tcase(s1, tc_memcpy);
  suite_add_tcase(s1, tc_memmove);
  suite_add_tcase(s1, tc_memset);
  suite_add_tcase(s1, tc_strcat);
  suite_add_tcase(s1, tc_strncat);
  
  // memchr
  tcase_add_test(tc_memchr, test_for_memchr);
  tcase_add_test(tc_memchr, test_for_memchr_not_symbol);
  tcase_add_test(tc_memchr, test_for_memchr_special_symbol);
  tcase_add_test(tc_memchr, test_for_memchr_not_enough_memory);
  tcase_add_test(tc_memchr, test_for_memchr_empty_line);

  // memcmp
  tcase_add_test(tc_memcmp, test_for_memcmp_output_zero);
  tcase_add_test(tc_memcmp, test_for_memcmp_for_different_register);
  tcase_add_test(tc_memcmp, test_for_memcmp_more_memory);

  // memcpy
  tcase_add_test(tc_memcpy, test_for_memcpy);
  tcase_add_test(tc_memcpy, test_for_memcpy_copy_zero_bytes);
  tcase_add_test(tc_memcpy, test_for_memcpy_more_bytes);

  // memmove
  tcase_add_test(tc_memmove, test_for_memmove_in_own_string);
  tcase_add_test(tc_memmove, test_for_memmove_in_own_string_more_bytes);
  tcase_add_test(tc_memmove, test_for_memmove_for_null_string);
  tcase_add_test(tc_memmove, test_for_memmove_for_null_bytes);
  tcase_add_test(tc_memmove, test_for_memmove_more_memory);
  tcase_add_test(tc_memmove, test_for_memmove_in_other_string);
  tcase_add_test(tc_memmove, test_for_memmove_in_other_string_copy_zero_bytes);
  tcase_add_test(tc_memmove, test_for_memmove_in_other_string_more_bytes);

  // memset
  tcase_add_test(tc_memset, test_for_memset);
  tcase_add_test(tc_memset, test_for_memset_full_change);
  tcase_add_test(tc_memset, test_for_memset_empty_null);
  tcase_add_test(tc_memset, test_for_memset_more_bytes);

  //strcat
  tcase_add_test(tc_strcat,test_for_strcat);
  tcase_add_test(tc_strcat, test_for_strcat_with_empty_line);

  //strncat
  tcase_add_test(tc_strncat,test_for_strncat);
  tcase_add_test(tc_strncat, test_for_strncat_with_zero_bytes);
  tcase_add_test(tc_strncat, test_for_strncat_more_bytes);



  srunner_run_all(sr, CK_ENV);
  int a = srunner_ntests_failed(sr);
  srunner_free(sr);

  return a == 0 ? 0 : 1;
}