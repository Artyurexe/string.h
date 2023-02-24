#include <check.h>
#include <string.h>
#include "s21_sscanf.h"

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

// :(
// START_TEST(test_s_two_bad) {
//     char str1[30];
//     char str2[30];
//     char str3[30];
//     char str4[30];
//     s21_sscanf("string \0", "%s%s", str1, str2);
//     sscanf("string \0", "%s%s", str3, str4);
//     ck_assert_pstr_eq(str1, str3);
//     ck_assert_pstr_eq(str2, str4);
// }
//END_TEST

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
// START_TEST(sscanf_spec_c_2) {
//     char format[] = "%c";
//     char str[] = "\t\n\n  1 \n  \t";
//     char c1, c2;

//     int16_t res1 = s21_sscanf(str, format, &c1);
//     int16_t res2 = sscanf(str, format, &c2);
//     ck_assert_int_eq(res1, res2);
//     ck_assert_int_eq(c1, c2);
// }
// END_TEST

// START_TEST(sscanf_spec_c_4) {
//     char format[] = "%c";
//     char str[] = "\t\n\n   \n  \ta";
//     char c1, c2;
//     int16_t res1 = s21_sscanf(str, format, &c1);
//     int16_t res2 = sscanf(str, format, &c2);
//     ck_assert_int_eq(res1, res2);
//     ck_assert_int_eq(c1, c2);
// }
// END_TEST

int main() {
    Suite *s1 = suite_create("Tests_for_sscanf");

    TCase *tc_s = tcase_create("Test_string");
    TCase *tc_c = tcase_create("test_char");

    SRunner *sr = srunner_create(s1);

    //%s
    suite_add_tcase(s1, tc_s);
    suite_add_tcase(s1, tc_c);

    //%s
    tcase_add_test(tc_s, test_s_single);
    tcase_add_test(tc_s, test_s_two_normal);
    //tcase_add_test(tc_s, test_s_two_bad);
    tcase_add_test(tc_s, test_s_two_with_extra_spaces);
    tcase_add_test(tc_s, test_s_int);

    //%c
    tcase_add_test(tc_c, test_c_single);
    tcase_add_test(tc_c, test_c_null_terminator);
    tcase_add_test(tc_c, test_c_empty_string);
    tcase_add_test(tc_c, test_c_two_normal);
    tcase_add_test(tc_c, test_c_two_special);
    tcase_add_test(tc_c, test_c_two_bad);
    // tcase_add_test(tc_c, sscanf_spec_c_2);
    // tcase_add_test(tc_c, sscanf_spec_c_4);

    srunner_run_all(sr, CK_ENV);
    int a = srunner_ntests_failed(sr);
    srunner_free(sr);

    return a == 0 ? 0 : 1;
}