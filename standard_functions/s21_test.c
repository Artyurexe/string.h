#include <check.h>
#include <string.h>
#include "../sprintf/s21_sprintf_tests.h"
#include "../sscanf/s21_sscanf_tests.h"

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

START_TEST(s21_memcmp_tests) {
  char *str1 = "atoms\0\0\0\0";
  char *str2 = "atoms\0abc";
  ck_assert_int_eq(s21_memcmp(str1, str2, 7), memcmp(str1, str2, 7));
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

START_TEST(test_for_strchr_null_terminator_1) {
  char *str = "ABCDEFGHIJKLMNOPQ";
  char c = '\0';
  ck_assert_pstr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_for_strchr_null_terminator_2) {
  char *str = "ABC\0JKLMNOPQ";
  char c = '\0';
  ck_assert_pstr_eq(s21_strchr(str, c), strchr(str, c));
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
  }
END_TEST

//strcspn
START_TEST(test_for_strcspn_str2_not_include) {
    char str[30] = "qwerty";
    char str1[30] = "rty";
    char str2[30] = "uio";
    char str3[30] = "tyr";
    ck_assert_int_eq(s21_strcspn(str, str1), strcspn(str, str1));
    ck_assert_int_eq(s21_strcspn(str, str2), strcspn(str, str2));
    ck_assert_int_eq(s21_strcspn(str, str3), strcspn(str, str3));
  }
END_TEST

START_TEST(test_for_strcspn_str2_include) {
    char str[30] = "qwerty";
    char str1[30] = "wq";
    char str2[30] = "qwer";
    ck_assert_int_eq(s21_strcspn(str, str1), strcspn(str, str1));
    ck_assert_int_eq(s21_strcspn(str, str2), strcspn(str, str2));
  }
END_TEST

START_TEST(test_for_strcspn_str2_is_empty_line) {
    char str[30] = "qwerty";
    char str1[30] = "\0";
    ck_assert_int_eq(s21_strcspn(str, str1), strcspn(str, str1));
}
END_TEST

//strlen 
START_TEST(test_for_strlen) {
  char str[30] = "qwerty";
  char str1[30] = "qwe       rty";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));
}
END_TEST

START_TEST(test_for_strlen_empty_line) {
  char str[30] = "\0\0";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST


//strpbrk
START_TEST(test_for_strpbrk) {
  char str[30] = "1q2W3e4R";
  char str1[30] = "u2134";
  ck_assert_pstr_eq (s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_str2_not_unclude_symbols) {
  char str[30] = "1q2W3e4R";
  char str1[30] = "zxcvf";
  ck_assert_pstr_eq (s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_str2_null_literal) {
  char str[30] = "1q2W3e4R";
  char str1[30] = "\0";
  ck_assert_pstr_eq (s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_empry_str1) {
  char str[30] = "\0";
  char str1[30] = "23e4";
  ck_assert_pstr_eq (s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_for_strpbrk_empry_str1_and_str2_include_null_literal) {
  char str[30] = "\0";
  char str1[30] = "23e\04";
  ck_assert_pstr_eq (s21_strpbrk(str, str1), strpbrk(str, str1));
}
END_TEST

START_TEST(test_s21_strpbrk_test3) {
  char *str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *str2 = "12345Z67890";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_pstr_eq(s21_strpbrk(str2, str1), strpbrk(str2, str1));
}
END_TEST

//strrchr
START_TEST(test_for_strrchr) {
    const char str[30] = "qwertye";
    char c = 'e';
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
  }
END_TEST

START_TEST(test_for_strrchr_will_not_find) {
    const char str[30] = "qwerty";
    char c = 'u';
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
  }
END_TEST

START_TEST(test_for_strrchr_null_terminator) {
    const char str[30] = "qwerty";
    char c = '\0';
    ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
  }
END_TEST

///strstr
START_TEST(test_for_strstr) {
    char str[30] = "qwerty";
    char str1[30] = "erty";
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  }
END_TEST

START_TEST(test_for_strstr_will_not_find) {
    char str[30] = "qwerty";
    char str1[30] = "uio";
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
  }
END_TEST

START_TEST(test_for_strstr_null_terminator) {
    char str[30] = "qwerty";
    char str1[30] = "\0";
    ck_assert_pstr_eq(s21_strstr(str, str1), strstr(str, str1));
}
END_TEST

//strtok//////////

//strspn
START_TEST(test_for_strspn) {
    char str[30] = "qwerty";
    char str1[30] = "qrty";
    char str2[30] = "yt";
    ck_assert_int_eq(s21_strspn(str, str1), strspn(str, str1));
    ck_assert_int_eq(s21_strspn(str, str2), strspn(str, str2));
  }
END_TEST

START_TEST(test_for_strspn_str2_not_include_symbols) {
    char str[30] = "qwerty";
    char str1[30] = "uio";
    char str2[30] = "QWERT";
    ck_assert_int_eq(s21_strspn(str, str1), strspn(str, str1));
    ck_assert_int_eq(s21_strspn(str, str2), strspn(str, str2));
  }
END_TEST

START_TEST(test_for_strspn_str2_is_empty_line) {
    char str[30] = "qwerty";
    char str1[30] = "\0";
    ck_assert_int_eq(s21_strspn(str, str1), strspn(str, str1));
}
END_TEST

START_TEST(test_for_strspn_str1_is_empty_line) {
    char str[30] = "\0";
    char str1[30] = "qwe";
    ck_assert_int_eq(s21_strspn(str, str1), strspn(str, str1));
}
END_TEST

START_TEST(s21_strtok_tests_1) {
  char str_str[30] = " test1/test2/test3/test4\0";
  char s21_str[30] = " test1/test2/test3/test4\0";
  char sep[10] = "/";

  char *i_str_str;
  char *i_s21_str;

  i_str_str = strtok(str_str, sep);
  i_s21_str = s21_strtok(s21_str, sep);

  while (i_str_str != S21_NULL || i_s21_str != S21_NULL) {
    ck_assert_str_eq(i_s21_str, i_str_str);

    i_str_str = strtok(S21_NULL, sep);
    i_s21_str = s21_strtok(S21_NULL, sep);
  }
}
END_TEST

START_TEST(s21_strtok_tests_2) {
  char str_str[30] = " test1 test2   test3";
  char s21_str[30] = " test1 test2   test3";
  char sep[10] = " ";

  char *i_str_str;
  char *i_s21_str;

  i_str_str = strtok(str_str, sep);
  i_s21_str = s21_strtok(s21_str, sep);

  while (i_str_str != S21_NULL || i_s21_str != S21_NULL) {
    ck_assert_str_eq(i_s21_str, i_str_str);

    i_str_str = strtok(S21_NULL, sep);
    i_s21_str = s21_strtok(S21_NULL, sep);
  }
}
END_TEST

START_TEST(s21_strtok_tests_3) {
  char str_str[30] = " test1 test2   test3";
  char s21_str[30] = " test1 test2   test3";
  char sep[10] = "est";

  char *i_str_str;
  char *i_s21_str;

  i_str_str = strtok(str_str, sep);
  i_s21_str = s21_strtok(s21_str, sep);

  while (i_str_str != S21_NULL || i_s21_str != S21_NULL) {
    ck_assert_str_eq(i_s21_str, i_str_str);

    i_str_str = strtok(S21_NULL, sep);
    i_s21_str = s21_strtok(S21_NULL, sep);
  }
}
END_TEST

START_TEST(s21_strtok_tests_4) {
  char str_str[30] = " test1 test2   test3";
  char s21_str[30] = " test1 test2   test3";
  char sep[10] = "aa";

  char *i_str_str;
  char *i_s21_str;

  i_str_str = strtok(str_str, sep);
  i_s21_str = s21_strtok(s21_str, sep);

  while (i_str_str != S21_NULL || i_s21_str != S21_NULL) {
    ck_assert_str_eq(i_s21_str, i_str_str);

    i_str_str = strtok(S21_NULL, sep);
    i_s21_str = s21_strtok(S21_NULL, sep);
  }
}
END_TEST

START_TEST(s21_error){
    ck_assert_str_eq(s21_strerror(_i), strerror(_i));
}
END_TEST

START_TEST(s21_to_upper_tests) {
  char *str1 = "abcdefghijklmnopqrstuvwxyz";
  char *str2 = s21_to_upper(str1);
  ck_assert_str_eq(str2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  free(str2);

  char *str3 = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  char *str4 = s21_to_upper(str3);
  ck_assert_str_eq(str4, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
  free(str4);

  char *str5 = "1234567890abcdefghijklmnopqrstuvwxyz1234567890";
  char *str6 = s21_to_upper(str5);
  ck_assert_str_eq(str6, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
  free(str6);

  char *str7 = S21_NULL;
  char *str8 = s21_to_upper(str7);
  ck_assert_ptr_null(str8);
  free(str8);
}
END_TEST

START_TEST(s21_to_lower_tests) {
  char *str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *str2 = s21_to_lower(str1);
  ck_assert_str_eq(str2, "abcdefghijklmnopqrstuvwxyz");
  free(str2);

  char *str3 = "1234567890abcdefghijklmnopqrstuvwxyz1234567890";
  char *str4 = s21_to_lower(str3);
  ck_assert_str_eq(str4, "1234567890abcdefghijklmnopqrstuvwxyz1234567890");
  free(str4);

  char *str5 = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
  char *str6 = s21_to_lower(str5);
  ck_assert_str_eq(str6, "1234567890abcdefghijklmnopqrstuvwxyz1234567890");
  free(str6);

  char *str7 = S21_NULL;
  char *str8 = s21_to_lower(str7);
  ck_assert_ptr_null(str8);
  free(str8);
}
END_TEST

START_TEST(s21_insert_tests) {
  char *str1 = "1";
  char *str2 = "2";
  char *str_res1 = s21_insert(str1, str2, 0);
  ck_assert_str_eq(str_res1, "21");
  free(str_res1);
  char *str_res2 = s21_insert(str1, str2, 1);
  ck_assert_str_eq(str_res2, "12");
  free(str_res2);

  char *str10 = "";
  char *str20 = "abcdefghijklmnopqrstuvwxyz";
  char *str_res10 = s21_insert(str10, str20, 0);
  ck_assert_str_eq(str_res10, "abcdefghijklmnopqrstuvwxyz");
  free(str_res10);
  char *str_res20 = s21_insert(str20, str10, 0);
  ck_assert_str_eq(str_res20, "abcdefghijklmnopqrstuvwxyz");
  free(str_res20);

  char *str11 = "12345678901234567890";
  char *str21 = "abcdefghijklmnopqrstuvwxyz";
  char *str_res11 = s21_insert(str11, str21, 10);
  ck_assert_str_eq(str_res11, "1234567890abcdefghijklmnopqrstuvwxyz1234567890");
  free(str_res11);
  char *str_res21 = s21_insert(str21, str11, 0);
  ck_assert_str_eq(str_res21, "12345678901234567890abcdefghijklmnopqrstuvwxyz");
  free(str_res21);
  char *str_res31 = s21_insert(str11, str21, 20);
  ck_assert_str_eq(str_res31, "12345678901234567890abcdefghijklmnopqrstuvwxyz");
  free(str_res31);
  char *str22 = "1234567890";
  char *str32 = "ABC";
  char *str_res32 = s21_insert(str22, str32, -1);
  ck_assert_ptr_null(str_res32);
  free(str_res32);
  char *str_res42 = s21_insert(str22, str32, 11);
  ck_assert_ptr_null(str_res42);
  free(str_res42);
}
END_TEST

START_TEST(s21_trim_tests) {
  char *str = "111222111";
  char *str_res1 = s21_trim(str, "1");
  ck_assert_str_eq(str_res1, "222");
  free(str_res1);
  char *str_res2 = s21_trim(str, "12");
  ck_assert_str_eq(str_res2, "");
  free(str_res2);

  char *str1 = "qwertyuiop ,. qwertyuiop";
  char *str_res11 = s21_trim(str1, " ,.");
  ck_assert_str_eq(str_res11, "qwertyuiop ,. qwertyuiop");
  free(str_res11);
  char *str_res21 = s21_trim(str1, "qwertyuiop");
  ck_assert_str_eq(str_res21, " ,. ");
  free(str_res21);

  char *str0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *str_res10 = s21_trim(str0, " ,.");
  ck_assert_str_eq(str_res10, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  free(str_res10);
  char *str_res20 = s21_trim(str0, "ABC");
  ck_assert_str_eq(str_res20, "DEFGHIJKLMNOPQRSTUVWXYZ");
  free(str_res20);
  char *str_res30 = s21_trim(str0, "A");
  ck_assert_str_eq(str_res30, "BCDEFGHIJKLMNOPQRSTUVWXYZ");
  free(str_res30);
  char *str_res40 = s21_trim(str0, "Z");
  ck_assert_str_eq(str_res40, "ABCDEFGHIJKLMNOPQRSTUVWXY");
  free(str_res40);
  char *str_res50 = s21_trim(str0, "XYZ");
  ck_assert_str_eq(str_res50, "ABCDEFGHIJKLMNOPQRSTUVW");
  free(str_res50);
  char *str_res60 = s21_trim(str0, "ABCXYZ");
  ck_assert_str_eq(str_res60, "DEFGHIJKLMNOPQRSTUVW");
  free(str_res60);
  char *str23 = " 111 ";
  char *str33 = "\n111";
  char *str_res23 = s21_trim(str23, "");
  char *str_res33 = s21_trim(str33, S21_NULL);
  ck_assert_str_eq(str_res23, "111");
  ck_assert_str_eq(str_res33, "111");
}
END_TEST

Suite *s21_string_suite(void) {
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
  TCase *tc_strrchr = tcase_create("Tests_for_strrchr ");
  TCase *tc_strstr = tcase_create("Tests_for_strstr ");
  TCase *tc_strcspn = tcase_create("Tests_for_strcspn ");
  TCase *tc_strlen = tcase_create("Tests_for_strlen ");
  TCase *tc_strpbrk = tcase_create("Tests_for_strbrk ");
  TCase *tc_strspn = tcase_create("Tests_for_strspn ");
  TCase *tc_strtok = tcase_create("Tests_for_strtok ");
  TCase *tc_strerror = tcase_create("Tests_for_strerror ");
  TCase *tc_tests_CS = tcase_create("C#_func");
  suite_add_tcase(s1, tc_tests_CS);
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
  //
  suite_add_tcase(s1, tc_strcspn);
  suite_add_tcase(s1, tc_strlen);
  suite_add_tcase(s1, tc_strpbrk);
  suite_add_tcase(s1, tc_strspn);
  suite_add_tcase(s1, tc_strtok);
  suite_add_tcase(s1, tc_strerror);


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
  tcase_add_test(tc_memcmp, s21_memcmp_tests);

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
  tcase_add_test(tc_strchr, test_for_strchr_null_terminator_1);
  tcase_add_test(tc_strchr, test_for_strchr_null_terminator_2);

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


  //strcspn
  tcase_add_test(tc_strcspn, test_for_strcspn_str2_not_include);
  tcase_add_test(tc_strcspn, test_for_strcspn_str2_include);
  tcase_add_test(tc_strcspn, test_for_strcspn_str2_is_empty_line);
  
  //strerror/////////

  //strlen
  tcase_add_test(tc_strlen, test_for_strlen);
  tcase_add_test(tc_strlen, test_for_strlen_empty_line);

  //strpbrk
  tcase_add_test(tc_strpbrk, test_for_strpbrk);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_str2_not_unclude_symbols);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_str2_null_literal);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_empry_str1);
  tcase_add_test(tc_strpbrk, test_for_strpbrk_empry_str1_and_str2_include_null_literal);
  tcase_add_test(tc_strpbrk, test_s21_strpbrk_test3);

  //strspn
  tcase_add_test(tc_strspn, test_for_strspn);
  tcase_add_test(tc_strspn, test_for_strspn_str2_not_include_symbols);
  tcase_add_test(tc_strspn, test_for_strspn_str2_is_empty_line);
  tcase_add_test(tc_strspn, test_for_strspn_str1_is_empty_line);

  //strrchr
  tcase_add_test(tc_strrchr, test_for_strrchr);
  tcase_add_test(tc_strrchr, test_for_strrchr_will_not_find);
  tcase_add_test(tc_strrchr, test_for_strrchr_null_terminator);

  //strstr
  tcase_add_test(tc_strstr, test_for_strstr);
  tcase_add_test(tc_strstr, test_for_strstr_will_not_find);
  tcase_add_test(tc_strstr, test_for_strstr_null_terminator);

  //strtok
  tcase_add_test(tc_strstr, s21_strtok_tests_1);
  tcase_add_test(tc_strstr, s21_strtok_tests_2);
  tcase_add_test(tc_strstr, s21_strtok_tests_3);
  tcase_add_test(tc_strstr, s21_strtok_tests_4);

  //strerror
  tcase_add_loop_test(tc_strerror, s21_error, -1, 108);

  //C#
  tcase_add_test(tc_tests_CS, s21_to_upper_tests);
  tcase_add_test(tc_tests_CS, s21_to_lower_tests);
  tcase_add_test(tc_tests_CS, s21_insert_tests);
  tcase_add_test(tc_tests_CS, s21_trim_tests);
  return s1;
}

int main() {
 Suite *s, *s1, *s2;
  SRunner *runner, *runner1, *runner2;

  s = s21_string_suite();
  s1 = s21_sprintf_test();
  s2 = s21_sscanf_test();
  runner = srunner_create(s);
  runner1 = srunner_create(s1);
  runner2 = srunner_create(s2);

  srunner_run_all(runner, CK_ENV);
  srunner_run_all(runner1, CK_ENV);
  srunner_run_all(runner2, CK_ENV);

  // srunner_ntests_failed(runner);
  // srunner_ntests_failed(runner1);
  // srunner_ntests_failed(runner2);
  srunner_free(runner);
  srunner_free(runner1);
  srunner_free(runner2);
  return 0;
}