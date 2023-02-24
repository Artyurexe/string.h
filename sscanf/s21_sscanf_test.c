#include <check.h>
#include <string.h>
#include "s21_sscanf.h"

//%s
START_TEST(test_s_single) {
    char str1[30];
    char str2[30];
    s21_sscanf("string", "%s", str1);
    sscanf("string", "%s", str2);
    ck_assert_pstr_eq(str1, str2);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Tests_for_ssanf");

    TCase *tc_s = tcase_create("Test_s");


    SRunner *sr = srunner_create(s1);


    suite_add_tcase(s1, tc_s);

    tcase_add_test(tc_s, test_s_single);



    srunner_run_all(sr, CK_ENV);
    int a = srunner_ntests_failed(sr);
    srunner_free(sr);

    return a == 0 ? 0 : 1;
}