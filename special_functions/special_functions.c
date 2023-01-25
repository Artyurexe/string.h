#include <stdlib.h>
#include <string.h>
void *s21_to_upper(const char *str) {
  char* buff = calloc(strlen(str), sizeof(char));
  for (size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 96 && str[i] < 123)
      buff[i] = str[i] - 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}

void *s21_to_lower(const char *str) {
  char* buff = calloc(s21_strlen(str), sizeof(char));
  for (size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 64 && str[i] < 91)
      buff[i] = str[i] + 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}


void *trim(const char *src, const char *trim_chars) {
    size_t from_start = 0, from_end = 0;
    int flag = 0, other_flag = 0, i = 0;
    while (!flag) {
        for (int j = 0; j < strlen(trim_chars) && !other_flag; j++)
            if (strchr(src + from_start, trim_chars[j]) == src + from_start) {
                from_start++;
                other_flag = 1;
            }
        if (!other_flag)
            flag = 1;
    }
    flag = 0, other_flag = 0;
    while (!flag) {
        i = strlen(src) - 1;
        for (int j = strlen(trim_chars) - 1; j >= 0 && !other_flag; j--)
            if (strchr(src + i - from_end, trim_chars[j]) == src + i - from_end) {
                from_end++;
                other_flag = 1;
            }
        if (!other_flag)
            flag = 1;
    }
    if ()
}