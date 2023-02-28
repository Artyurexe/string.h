#include <check.h>
#include <string.h>

#include "s21_string.h"



START_TEST(test_for_memchr) {
    char *tests_strings[] = {"This",  //18
                            "This string",
                            "This string",
                            "\0This string for",
                            "\0This string for", //5 
                            "This striNg for tests.",
                            "This striNg for tests.",
                            "This striNg for tests.",
                            " ",
                            "   ", //10
                            ".   ",
                            "\0", 
                            S21_NULL ,
                            "This string for tests.", 
                            "special symbol:\\", //15
                            "@\\%^&#",
                            "@\\%_^&#",
                            "4ance" };

    s21_size_t butes[] = {4, 2, 20, 20, 20,
                         5, 3, 21, 30, 3,
                          5, 7, 20, 4, 70,
                          5, 9, 5};
    char symbols[] = {'T', 'i', '\0', 0, 78,
                    78, '.', 's', 'q', ' ',
                     '.', '\0', '\0', 'f', '\\',
                     '@', 36, '4'};
    for (int i = 0; i <18; i++)
        ck_assert_pstr_eq(s21_memchr(tests_strings[i], symbols[i], butes[i]),memchr(tests_strings[i], symbols[i], butes[i]));

  }
END_TEST

int main() {
    Suite *s1 = suite_create("Tests_for_string");
    TCase *tc_memchr = tcase_create("Tests_for_memchr");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, tc_memchr);
    tcase_add_test(tc_memchr, test_for_memchr);
    srunner_run_all(sr, CK_ENV);
    int a = srunner_ntests_failed(sr);
    srunner_free(sr);

  return a == 0 ? 0 : 1;
}