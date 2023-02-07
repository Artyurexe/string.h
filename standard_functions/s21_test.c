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

//strchr
START_TEST(test_for_strchr) {
    char str[30] = "123qwer143";
    ck_assert_pstr_eq(s21_strchr(str, 'q'), strchr(str, 'q'));
    char str1[30] = "qwer143";
    ck_assert_pstr_eq(s21_strchr(str1, 'q'), strchr(str1, 'q'));
  }
END_TEST

START_TEST(test_for_strchr_empty_str) {
    ck_assert_pstr_eq(s21_strchr("", 'q'), strchr("", 'q'));
  }

START_TEST(test_for_strchr_with_no_char) {
    ck_assert_pstr_eq(s21_strchr("werty", 'q'), strchr("werty", 'q'));
  }
END_TEST


///strcmp
START_TEST(test_for_strcmp_same_strings) {
    const char str[30] = "123qwer143";
    const char str1[30] = "123qwer143";
    ck_assert_int_eq(s21_strcmp(str, str1), strcmp(str, str1));
  }
END_TEST

START_TEST(test_for_strcmp_empty_str) {
    const char str[30] = "";
    const char str1[30] = "";
    ck_assert_int_eq(s21_strcmp(str, str1), strcmp(str, str1));
  }

//чекните этот тест на маке пж
START_TEST(test_for_strcmp_different_strings) {
    const char str[30] = "123qwer143";
    const char str1[30] = "123diffqwer143";
    ck_assert_int_eq(s21_strcmp(str, str1), strcmp(str, str1));
    const char str2[30] = "123qwer143";
    const char str3[30] = "123qwer164";
    ck_assert_int_eq(s21_strcmp(str2, str3), strcmp(str2, str3));
  }
END_TEST

//strncmp
START_TEST(test_for_strncmp_same_strings) {
    const char str[30] = "123qwer143";
    const char str1[30] = "123qwer143";
    ck_assert_int_eq(s21_strncmp(str, str1, 10), strncmp(str, str1, 10));
  }
END_TEST

START_TEST(test_for_strncmp_empty_str) {
    const char str[30] = "";
    const char str1[30] = "";
    ck_assert_int_eq(s21_strncmp(str, str1, 3), strncmp(str, str1, 3));
  }

//чекните этот тест на маке пж
START_TEST(test_for_strncmp_different_strings) {
    const char str[30] = "qwer2143";
    const char str1[30] = "qwer143";
    ck_assert_int_eq(s21_strncmp(str, str1, 5), strncmp(str, str1, 5));
    const char str2[30] = "143";
    const char str3[30] = "1643";
    ck_assert_int_eq(s21_strncmp(str2, str3, 2), strncmp(str2, str3, 2));
  }
END_TEST

//strcpy
START_TEST(test_for_strcpy) {
    char str[30] = "xxxxxxxxxx";
    char str1[30] = "123qwer143";
    ck_assert_pstr_eq(s21_strcpy(str, str1), strcpy(str, str1));
  }
END_TEST

START_TEST(test_for_strcpy_null_terminator) {
    char str[30] = "xxxxxxxxxx";
    char str1[30] = "\0";
    ck_assert_pstr_eq(s21_strcpy(str, str1), strcpy(str, str1));
  }
END_TEST

//strcpy
START_TEST(test_for_strncpy) {
    char str[30] = "xxxxxxxxxx";
    char str1[30] = "123qwer143";
    ck_assert_pstr_eq(s21_strncpy(str, str1, 5), strncpy(str, str1, 5));
  }
END_TEST

START_TEST(test_for_strncpy_null_terminator) {
    char str[30] = "xxxxxxxxxx";
    char str1[30] = "\0";
    ck_assert_pstr_eq(s21_strncpy(str, str1, 1), strncpy(str, str1, 1));
    ck_assert_pstr_eq(s21_strncpy(str, str1, 2), strncpy(str, str1, 2));
  }
END_TEST

//strcspn

//strlne

//strpbrk

//strrchr
START_TEST(test_for_strrchr) {
    const char str[30] = "qwerty";
    char c = 'e';
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
  }
END_TEST

START_TEST(test_for_strrchr_will_not_find) {
    const char str[30] = "qwerty";
    char c = 'u';
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
  }
END_TEST

START_TEST(test_for_strrchr_null_terminator) {
    const char str[30] = "qwerty";
    char c = '\0';
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
  }
END_TEST

///strstr
START_TEST(test_for_strstr) {
    char str[30] = "qwerty";
    char str1[30] = "erty";
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  }
END_TEST

START_TEST(test_for_strstr_will_not_find) {
    char str[30] = "qwerty";
    char str1[30] = "uio";
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  }
END_TEST

START_TEST(test_for_strstr_null_terminator) {
    char str[30] = "qwerty";
    char str1[30] = "\0";
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  }
END_TEST
//strtok

//strspn


int main() {
  Suite *s1 = suite_create("Tests_for_string");

  TCase *tc_memchr = tcase_create("Tests_for_memchr ");
  TCase *tc_memcmp = tcase_create("Tests_for_memcmp ");
  TCase *tc_memcpy = tcase_create("Tests_for_memcpy ");
  TCase *tc_memmove = tcase_create("Tests_for_memmove ");
  TCase *tc_memset = tcase_create("Tests_for_memset ");
  TCase *tc_strcat = tcase_create("Tests_for_strcat ");
  TCase *tc_strncat = tcase_create("Tests_for_strcat ");
  TCase *tc_strchr = tcase_create("Tests_for_strchr ");
  TCase *tc_strcmp = tcase_create("Tests_for_strcmp ");
  TCase *tc_strncmp = tcase_create("Tests_for_strncmp ");
  TCase *tc_strcpy = tcase_create("Tests_for_strcpy ");
  TCase *tc_strncpy = tcase_create("Tests_for_strncpy ");
  TCase *tc_strrchr = tcase_create("Tests_for_strrchr");
  TCase *tc_strstr = tcase_create("Tests_for_strstr ");

  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc_memchr);
  suite_add_tcase(s1, tc_memcmp);
  suite_add_tcase(s1, tc_memcpy);
  suite_add_tcase(s1, tc_memmove);
  suite_add_tcase(s1, tc_memset);
  suite_add_tcase(s1, tc_strcat);
  suite_add_tcase(s1, tc_strncat);
  suite_add_tcase(s1, tc_strchr);
  suite_add_tcase(s1, tc_strcmp);
  suite_add_tcase(s1, tc_strncmp);
  suite_add_tcase(s1, tc_strcpy);
  suite_add_tcase(s1, tc_strncpy);
  // ...
  suite_add_tcase(s1, tc_strrchr);
  suite_add_tcase(s1, tc_strstr);

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

  //strchr
  tcase_add_test(tc_strchr, test_for_strchr);
  tcase_add_test(tc_strchr, test_for_strchr_empty_str);
  tcase_add_test(tc_strchr, test_for_strchr_with_no_char);

  //strcmp
  tcase_add_test(tc_strcmp, test_for_strcmp_same_strings);
  tcase_add_test(tc_strcmp, test_for_strcmp_empty_str);
  tcase_add_test(tc_strcmp, test_for_strcmp_different_strings);

  //strncmp
  tcase_add_test(tc_strncmp, test_for_strncmp_same_strings);
  tcase_add_test(tc_strncmp, test_for_strncmp_empty_str);
  tcase_add_test(tc_strncmp, test_for_strncmp_different_strings);

  //strcpy
  tcase_add_test(tc_strcpy, test_for_strcpy);
  tcase_add_test(tc_strcpy, test_for_strcpy_null_terminator);

  //strncpy
  tcase_add_test(tc_strncpy, test_for_strncpy);
  tcase_add_test(tc_strncpy, test_for_strncpy_null_terminator);

  // ...

  //strchr
  tcase_add_test(tc_strrchr, test_for_strrchr);
  tcase_add_test(tc_strrchr, test_for_strrchr_will_not_find);
  tcase_add_test(tc_strrchr, test_for_strrchr_null_terminator);

  //strstr
  tcase_add_test(tc_strstr, test_for_strstr);
  tcase_add_test(tc_strstr, test_for_strstr_will_not_find);
  tcase_add_test(tc_strstr, test_for_strstr_null_terminator);

  srunner_run_all(sr, CK_ENV);
  int a = srunner_ntests_failed(sr);
  srunner_free(sr);

  return a == 0 ? 0 : 1;
}