#include <check.h>
#include <string.h>

#include "s21_string.h"

// tests for comparison functions Takakoka
START_TEST(s21_strcmp_tests) {
  char *str1 = "atoms\0\0\0\0";
  char *str2 = "atoms\0abc";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));

  char *str3 = "atom";
  char *str4 = "atom";
  ck_assert_int_eq(s21_strcmp(str3, str4), strcmp(str3, str4));

  char *str5 = "atoms";
  char *str6 = " ";
  ck_assert_int_ge(s21_strcmp(str5, str6), strcmp(str5, str6));

  char *str7 = "";
  char *str8 = "";
  ck_assert_int_eq(s21_strcmp(str7, str8), strcmp(str7, str8));
}
END_TEST

START_TEST(s21_strncmp_tests) {
  char *str1 = "atoms\0\0\0\0";
  char *str2 = "atoms\0abc";
  ck_assert_int_eq(s21_strncmp(str1, str2, 7), strncmp(str1, str2, 7));

  char *str3 = "atom";
  char *str4 = "atom";
  ck_assert_int_eq(s21_strncmp(str3, str4, 3), strncmp(str3, str4, 3));

  char *str5 = "atoms";
  char *str6 = " ";
  ck_assert_int_ge(s21_strncmp(str5, str6, 1), strncmp(str5, str6, 1));

  char *str7 = "";
  char *str8 = "";
  ck_assert_int_eq(s21_strncmp(str7, str8, 1), strncmp(str7, str8, 1));

  char *str9 = "";
  char *str10 = "Hello world!";
  ck_assert_int_le(s21_strncmp(str9, str10, 5), strncmp(str9, str10, 5));

  char *str11 = "Hello world!0123";
  char *str12 = "Hello world!";
  ck_assert_int_le(s21_strncmp(str11, str12, 10), strncmp(str11, str12, 10));
  ck_assert_int_ge(s21_strncmp(str11, str12, 15), strncmp(str11, str12, 15));
  ck_assert_int_le(s21_strncmp(str12, str11, 13), strncmp(str12, str11, 13));
}
END_TEST

START_TEST(s21_memcmp_tests) {
  char *str1 = "atoms\0\0\0\0";
  char *str2 = "atoms\0abc";
  ck_assert_int_eq(s21_memcmp(str1, str2, 7), memcmp(str1, str2, 7));

  char *str3 = "atom";
  char *str4 = "atom";
  ck_assert_int_eq(s21_memcmp(str3, str4, 3), memcmp(str3, str4, 3));

  char *str5 = "atoms";
  char *str6 = " ";
  ck_assert_int_eq(s21_memcmp(str5, str6, 1), memcmp(str5, str6, 1));

  char *str7 = "";
  char *str8 = "";
  ck_assert_int_eq(s21_memcmp(str7, str8, 0), memcmp(str7, str8, 0));

  int array1[] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
  int array2[] = {11, 12, 13, 14, 15, 16, 17, 17, 19};
  s21_size_t n = 7 * sizeof(int);
  ck_assert_int_eq(s21_memcmp(array1, array2, n), memcmp(array1, array2, n));

  char *str9 = "Hello world!0123";
  char *str10 = "Hello world!";
  ck_assert_int_le(s21_memcmp(str9, str10, 10), memcmp(str9, str10, 10));
  ck_assert_int_ge(s21_memcmp(str9, str10, 15), memcmp(str9, str10, 15));
  ck_assert_int_le(s21_memcmp(str9, str10, 13), memcmp(str9, str10, 13));
}
END_TEST

// tests for search functions Takakoka

START_TEST(test_s21_strchr_test1) {
  char *str = "ABCZ";
  char c = 'Z';
  ck_assert_pstr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_s21_strchr_test) {
  char *str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  char c = '\0';
  ck_assert_pstr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_s21_strpbrk_test1) {
  char *str1 = "1234567890";
  char *str2 = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_pstr_eq(s21_strpbrk(str2, str1), strpbrk(str2, str1));
}
END_TEST

START_TEST(test_s21_strpbrk_test2) {
  char *str1 = "";
  char *str2 = "";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_test3) {
  char *str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char *str2 = "12345Z67890";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_pstr_eq(s21_strpbrk(str2, str1), strpbrk(str2, str1));
}
END_TEST

START_TEST(test_s21_strpbrk_test4) {
  char *str1 = "";
  char *str2 = "AB";
  ck_assert_pstr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strrchr_test1) {
  char *str = "";
  char c = '0';
  ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_s21_strrchr_test2) {
  char *str = "AZNOPQRSTZUVWXYZ";
  char c = 'Z';
  ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_s21_strrchr_test3) {
  char *str = "12341234123412341234123410";
  char c = '1';
  ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_s21_strrchr_test4) {
  char *str = "ABC";
  char c = '\0';
  ck_assert_pstr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_s21_strstr_test1) {
  char *str1 = "";
  char *str2 = "";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test2) {
  char *str1 = "ABC";
  char *str2 = "";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test3) {
  char *str1 = "";
  char *str2 = "ABC";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test4) {
  char *str1 = "ABCabc";
  char *str2 = "AB";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test5) {
  char *str1 = "qwertyuiopQWERTYUIOP{}|\":<>?";
  char *str2 = "YTREWQ";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test6) {
  char *str1 = "q";
  char *str2 = "q";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test7) {
  char *str1 = "HI HI HI";
  char *str2 = "HI";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test8) {
  char *str1 = "AbOBosNyTSa";
  char *str2 = "aBoboSNYTsa";
  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_strstr_test9) {
  char str1[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  char *str2 = "woo";
  ck_assert_pstr_eq(strstr(str1, str2), s21_strstr(str1, str2));
}
END_TEST

START_TEST(test_s21_memchr_test1) {
  char str[] = "";
  char c = 'A';
  s21_size_t n = 0;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_s21_memchr_test2) {
  char str[] = "123456789";
  char c = '0';
  s21_size_t n = 9;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_s21_memchr_test3) {
  char str[] = "123456789";
  char c = '1';
  s21_size_t n = 9;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_s21_memchr_test4) {
  int array[] = {11, 12, 13, 14, 15, 16, 17, 18, 19};
  int c = 19;
  s21_size_t n = 5 * sizeof(int);
  ck_assert_ptr_eq(s21_memchr(array, c, n), memchr(array, c, n));
}
END_TEST

START_TEST(test_s21_memchr_test5) {
  float array[] = {11.1, 12.1, 13.1, 14, 15.99, 16.001, 17, 18, 19};
  int c = 14;
  s21_size_t n = 9 * sizeof(float);
  ck_assert_ptr_eq(s21_memchr(array, c, n), memchr(array, c, n));
}
END_TEST

// tests for copy functions Jesicahi
START_TEST(s21_memcpy_tests) {
  char *s21_result;
  char *str_result;

  char str[20] = "Hello world!!";
  char s21_buffer[20] = {'\0'}, str_buffer[20] = {'\0'};
  int len_array[5] = {1, 20, 15, 0, 5};

  s21_result = s21_memcpy(s21_buffer, str, len_array[_i]);
  str_result = memcpy(str_buffer, str, len_array[_i]);
  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_memmove_tests) {
  char s21_dest[] = "1234567890";
  char str_dest[] = "1234567890";
  char *src_arr[5] = {"abcdefg", "ax+=0998765432", "NAN", " ", "\0"};
  s21_size_t len_arr[5] = {2, 3, 4, 5, 0};

  char *s21_result =
      s21_memmove(&s21_dest[len_arr[_i]], src_arr[_i], len_arr[_i]);
  char *str_result = memmove(&str_dest[len_arr[_i]], src_arr[_i], len_arr[_i]);

  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_memmove_tests_2) {
  char s21_dest[] = "1234567890";
  char str_dest[] = "1234567890";
  char *s21_result = s21_memmove(&s21_dest[0], &s21_dest[5], 5);
  char *str_result = memmove(&str_dest[0], &str_dest[5], 5);

  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_memset_tests) {
  char test_1[20] = "polskaya_notatsia";
  char test_2[25] = "lublu svooih rodichey";

  s21_size_t len_arr[5] = {0, 3, 4, 15, 10};
  char char_arr[5] = {'a', 'c', '.', '0', '%'};

  char *s21_result = s21_memset(test_1, char_arr[_i], len_arr[_i]);
  char *str_result = memset(test_1, char_arr[_i], len_arr[_i]);
  ck_assert_str_eq(s21_result, str_result);

  s21_result = s21_memset(test_2, char_arr[_i], len_arr[_i]);
  str_result = memset(test_2, char_arr[_i], len_arr[_i]);
  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_strcpy_tests) {
  char s21_dest[20] = "polskaya_notatsia";
  char str_dest[20] = "polskaya_notatsia";

  char *src_arr[6] = {"aaaaaaaaaaa", "ax+=0998765432", "_+!2345a  r", "mmm..",
                      " "};

  char *s21_result = s21_strcpy(s21_dest, src_arr[_i]);
  char *str_result = strcpy(str_dest, src_arr[_i]);

  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_strncpy_tests) {
  char s21_dest[20] = "polskaya_notatsia";
  char str_dest[20] = "polskaya_notatsia";

  char *src_arr[5] = {"amammamama", "8765432", "_+!ddddd  r", "mmm.....", " "};
  s21_size_t len_arr[5] = {4, 3, 2, 5, 1};

  char *s21_result = s21_strncpy(s21_dest, src_arr[_i], len_arr[_i]);
  char *str_result = strncpy(str_dest, src_arr[_i], len_arr[_i]);

  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(strncpy_simple_test) {
  char copy[] = "simple copy";
  char got[30];
  char must[30];
  s21_size_t size = 12;

  s21_strncpy(got, copy, size);
  strncpy(must, copy, size);

  ck_assert_str_eq(got, must);
}
END_TEST

START_TEST(strncpy_rewrite_copy) {
  char copy[] = "simple copy";
  char got[30] = "Rewrite me pls";
  char must[30] = "Please me too";
  s21_size_t size = 12;

  s21_strncpy(got, copy, size);
  strncpy(must, copy, size);

  ck_assert_str_eq(got, must);
}
END_TEST

START_TEST(strncpy_copy_empty) {
  char copy[] = "";
  char got[30] = "Rewrite me pls";
  char must[30] = "Please me too";
  s21_size_t size = 1;

  s21_strncpy(got, copy, size);
  strncpy(must, copy, size);

  ck_assert_str_eq(got, must);
}
END_TEST

START_TEST(strncpy_all_empty) {
  char copy[] = "";
  char got[] = "";
  char must[] = "";
  s21_size_t size = 0;

  s21_strncpy(got, copy, size);
  strncpy(must, copy, size);

  ck_assert_str_eq(got, must);
}
END_TEST

START_TEST(strncpy_long_full_test) {
  char copy[] =
      "1234567890qwertyuiop[]asdfghjkl;zxcvbnm,./"
      "\n\tQWERTYUIOPASDFGHJKLZXCVBNM";
  char got[100] = "Rewrite me pls";
  char must[100] = "Please me too";
  s21_size_t size = 71;

  s21_strncpy(got, copy, size);
  strncpy(must, copy, size);

  ck_assert_str_eq(got, must);
}
END_TEST

START_TEST(strncpy_loop_check) {
  char copy[] =
      "1234567890qwertyuiop[]asdfghjkl;zxcv\0bnm,./"
      "\n\tQWERTYUIOPASDFGHJ\0KLZXCVBNM";
  char got[100] = "Rewrite me pls";
  char must[100] = "Rewrite me pls";
  for (s21_size_t size = 0; size < 71; size++) {
    s21_strncpy(got, copy, size);
    strncpy(must, copy, size);
    ck_assert_str_eq(got, must);
  }
}
END_TEST

// tests for help functions Jesicahi
START_TEST(s21_strtok_tests) {
  char str[30] = "test1/test2/test3/test4";

  /*test 1*/
  ck_assert_str_eq(s21_strtok(str, "/"), strtok(str, "/"));

  /*test 2*/
  ck_assert_ptr_eq(s21_strtok(str, "test"), strtok(str, "test"));

  /*test 3*/
  ck_assert_ptr_eq(s21_strtok(str, "st"), strtok(str, "st"));
}
END_TEST

START_TEST(s21_strtok_tests_2) {
  // Массив со строкой для поиска
  char str_str[30] = " test1/test2/test3/test4\0";
  char s21_str[30] = " test1/test2/test3/test4\0";
  // Набор символов, которые должны входить в искомый сегмент
  char sep[10] = "/";
  // Переменная, в которую будут заноситься начальные адреса частей
  // строки str
  char *i_str_str;
  char *i_s21_str;
  // Выделение первой части строки
  i_str_str = strtok(str_str, sep);
  i_s21_str = s21_strtok(s21_str, sep);

  // Выделение последующих частей
  while (i_str_str != NULL || i_s21_str != NULL) {
    // Вывод очередной выделенной части
    ck_assert_str_eq(i_s21_str, i_str_str);

    // Выделение очередной части строки
    i_str_str = strtok(NULL, sep);
    i_s21_str = s21_strtok(NULL, sep);
  }
}
END_TEST

START_TEST(s21_strcat_tests) {
  char *s21_result;
  char *str_result;
  char buffer[100] = {" "};
  char s21_buffer[100] = {" "};

  char *test_array[5] = {"abracadabra", "papa./'[]\'%s   ", "0-s221A", "\0",
                         ""};

  s21_result = s21_strcat(s21_buffer, test_array[_i]);
  str_result = strcat(buffer, test_array[_i]);
  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_strncat_tests) {
  char *s21_result;
  char *str_result;
  char buffer[100] = {" "};
  char s21_buffer[100] = {" "};

  char *test_array[5] = {"abracadabra", "   ", "0-s221A", "\0", ""};
  int len_array[5] = {1, 100, 32, 0, 100};

  s21_result = s21_strncat(s21_buffer, test_array[_i], len_array[_i]);
  str_result = strncat(buffer, test_array[_i], len_array[_i]);
  ck_assert_str_eq(s21_result, str_result);
}
END_TEST

START_TEST(s21_strerror_tests) {
  ck_assert_str_eq(s21_strerror(_i), strerror(_i));
}
END_TEST

// tests for calculation functions Cupcakep
START_TEST(s21_strlen_tests) {
  char *str1 = "";
  ck_assert_int_eq(s21_strlen(str1), strlen(str1));

  char *str2 = "0123456789";
  ck_assert_int_eq(s21_strlen(str2), strlen(str2));

  char *str3 = "Hello World!";
  ck_assert_int_eq(s21_strlen(str3), strlen(str3));

  char *str4 = "Я люблю школу 21, The BEST place 213213!";
  ck_assert_int_eq(s21_strlen(str4), strlen(str4));
}
END_TEST

START_TEST(s21_strcspn_tests) {
  char *str1 = "0123456789";
  char *str2 = "9876";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));

  char *str3 = "0123456789";
  char *str4 = "210";
  ck_assert_int_eq(s21_strcspn(str3, str4), strcspn(str3, str4));

  char *str5 = "str test spn";
  char *str6 = "test";
  ck_assert_int_eq(s21_strcspn(str5, str6), strcspn(str5, str6));

  char *str7 = "str test spn";
  char *str8 = "tsr";
  ck_assert_int_eq(s21_strcspn(str7, str8), strcspn(str7, str8));

  char *str9 = "str test spn";
  char *str10 = "abc";
  ck_assert_int_eq(s21_strcspn(str9, str10), strcspn(str9, str10));

  char *str11 = "str test spn";
  char *str12 = "";
  ck_assert_int_eq(s21_strcspn(str11, str12), strcspn(str11, str12));

  char *str13 = "";
  char *str14 = "str";
  ck_assert_int_eq(s21_strcspn(str13, str14), strcspn(str13, str14));
}
END_TEST

START_TEST(s21_strspn_tests) {
  char *str1 = "0123456789";
  char *str2 = "9876";
  ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));

  char *str3 = "0123456789";
  char *str4 = "210";
  ck_assert_int_eq(s21_strspn(str3, str4), strspn(str3, str4));

  char *str5 = "str test spn";
  char *str6 = "test";
  ck_assert_int_eq(s21_strspn(str5, str6), strspn(str5, str6));

  char *str7 = "str test spn";
  char *str8 = "tsr";
  ck_assert_int_eq(s21_strspn(str7, str8), strspn(str7, str8));

  char *str9 = "str test spn";
  char *str10 = "abc";
  ck_assert_int_eq(s21_strspn(str9, str10), strspn(str9, str10));

  char *str11 = "str test spn";
  char *str12 = "";
  ck_assert_int_eq(s21_strspn(str11, str12), strspn(str11, str12));

  char *str13 = "";
  char *str14 = "str";
  ck_assert_int_eq(s21_strspn(str13, str14), strspn(str13, str14));
}
END_TEST

// tests for C# functions Cupcakep
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

  char *str12 = NULL;
  char *str22 = "1234567890";
  char *str32 = "ABC";
  char *str_res12 = s21_insert(str12, str22, 0);
  ck_assert_str_eq(str_res12, "1234567890");
  free(str_res12);
  char *str_res22 = s21_insert(str22, str12, 0);
  ck_assert_str_eq(str_res22, "1234567890");
  free(str_res22);
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
  ck_assert_str_eq(str_res33, "\n111");
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *s;

  TCase *tc_tests_copy;
  s = suite_create("s21_string.h tests");
  tc_tests_copy = tcase_create("copy_func");
  tcase_add_loop_test(tc_tests_copy, s21_memcpy_tests, 0, 5);
  tcase_add_loop_test(tc_tests_copy, s21_memmove_tests, 0, 5);
  tcase_add_test(tc_tests_copy, s21_memmove_tests_2);
  tcase_add_loop_test(tc_tests_copy, s21_memset_tests, 0, 5);
  tcase_add_loop_test(tc_tests_copy, s21_strcpy_tests, 0, 5);
  tcase_add_loop_test(tc_tests_copy, s21_strncpy_tests, 0, 5);
  tcase_add_test(tc_tests_copy, strncpy_simple_test);
  tcase_add_test(tc_tests_copy, strncpy_rewrite_copy);
  tcase_add_test(tc_tests_copy, strncpy_copy_empty);
  tcase_add_test(tc_tests_copy, strncpy_all_empty);
  tcase_add_test(tc_tests_copy, strncpy_long_full_test);
  tcase_add_test(tc_tests_copy, strncpy_loop_check);
  suite_add_tcase(s, tc_tests_copy);

  TCase *tc_tests_help;
  tc_tests_help = tcase_create("help_func");
  tcase_add_loop_test(tc_tests_help, s21_strcat_tests, 0, 5);
  tcase_add_loop_test(tc_tests_help, s21_strncat_tests, 0, 5);
#if defined(__APPLE__)
  tcase_add_loop_test(tc_tests_help, s21_strerror_tests, -1, 109);
#elif defined(__linux__)
  tcase_add_loop_test(tc_tests_help, s21_strerror_tests, -1, 149);
#endif
  tcase_add_test(tc_tests_help, s21_strtok_tests);
  tcase_add_test(tc_tests_help, s21_strtok_tests_2);
  suite_add_tcase(s, tc_tests_help);

  TCase *tc_tests_comp;
  tc_tests_comp = tcase_create("comparison_func");
  tcase_add_test(tc_tests_comp, s21_strcmp_tests);
  tcase_add_test(tc_tests_comp, s21_strncmp_tests);
  tcase_add_test(tc_tests_comp, s21_memcmp_tests);
  suite_add_tcase(s, tc_tests_comp);

  TCase *tc_tests_strchr = tcase_create("Tests_strchr");
  tcase_add_test(tc_tests_strchr, test_s21_strchr_test);
  tcase_add_test(tc_tests_strchr, test_s21_strchr_test1);
  suite_add_tcase(s, tc_tests_strchr);

  TCase *tc_tests_strpbrk = tcase_create("Tests_strpbrk");
  tcase_add_test(tc_tests_strpbrk, test_s21_strpbrk_test1);
  tcase_add_test(tc_tests_strpbrk, test_s21_strpbrk_test2);
  tcase_add_test(tc_tests_strpbrk, test_s21_strpbrk_test3);
  tcase_add_test(tc_tests_strpbrk, test_s21_strpbrk_test4);
  suite_add_tcase(s, tc_tests_strpbrk);

  TCase *tc_tests_strrchr = tcase_create("Tests_strrchr");
  tcase_add_test(tc_tests_strrchr, test_s21_strrchr_test1);
  tcase_add_test(tc_tests_strrchr, test_s21_strrchr_test2);
  tcase_add_test(tc_tests_strrchr, test_s21_strrchr_test3);
  tcase_add_test(tc_tests_strrchr, test_s21_strrchr_test4);
  suite_add_tcase(s, tc_tests_strrchr);

  TCase *tc_tests_strstr = tcase_create("Tests_strstr");
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test1);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test2);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test3);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test4);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test5);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test6);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test7);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test8);
  tcase_add_test(tc_tests_strstr, test_s21_strstr_test9);
  suite_add_tcase(s, tc_tests_strstr);

  TCase *tc_tests_memchr = tcase_create("Tests_memchr");
  tcase_add_test(tc_tests_memchr, test_s21_memchr_test1);
  tcase_add_test(tc_tests_memchr, test_s21_memchr_test2);
  tcase_add_test(tc_tests_memchr, test_s21_memchr_test3);
  tcase_add_test(tc_tests_memchr, test_s21_memchr_test4);
  tcase_add_test(tc_tests_memchr, test_s21_memchr_test5);
  suite_add_tcase(s, tc_tests_memchr);

  TCase *tc_tests_calc;
  tc_tests_calc = tcase_create("calculation_func");
  tcase_add_test(tc_tests_calc, s21_strlen_tests);
  tcase_add_test(tc_tests_calc, s21_strcspn_tests);
  tcase_add_test(tc_tests_calc, s21_strspn_tests);
  suite_add_tcase(s, tc_tests_calc);

  TCase *tc_tests_CS;
  tc_tests_CS = tcase_create("C#_func");
  tcase_add_test(tc_tests_CS, s21_to_upper_tests);
  tcase_add_test(tc_tests_CS, s21_to_lower_tests);
  tcase_add_test(tc_tests_CS, s21_insert_tests);
  tcase_add_test(tc_tests_CS, s21_trim_tests);
  suite_add_tcase(s, tc_tests_CS);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *runner;

  s = s21_string_suite();

  runner = srunner_create(s);

  srunner_run_all(runner, CK_VERBOSE);

  srunner_ntests_failed(runner);
  srunner_free(runner);

  return 0;
}
