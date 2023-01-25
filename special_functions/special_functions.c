#include <stdlib.h>
#include <string.h>
#include "../standard_functions/s21_string.h"
void *s21_to_upper(const char *str) {
  char* buff = calloc(s21_strlen(str), sizeof(char));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 96 && str[i] < 123)
      buff[i] = str[i] - 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}

void *s21_to_lower(const char *str) {
  char* buff = calloc(s21_strlen(str), sizeof(char));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 64 && str[i] < 91)
      buff[i] = str[i] + 32;
    else 
      buff[i] = str[i];
  }
  return buff;
}



void rtrim(char * string, const char* trim) {
    int i;
    for(i = s21_strlen(string) - 1; i >= 0 && s21_strchr(trim, string[i]) != NULL; i--) {  
        string[i] = '\0';
    }
}
 
void ltrim( char * string, const char* trim ){
    while ( string[0] != '\0' && strchr (trim, string[0]) != NULL ) {
        s21_memmove(&string[0], &string[1], strlen(string));
    }
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *new_str = malloc(strlen(src));
    new_str = s21_strcpy(new_str, src);
    rtrim(new_str, trim_chars);
    ltrim(new_str, trim_chars);
    new_str = realloc(new_str, s21_strlen(new_str));
    return new_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (start_index > s21_strlen(src))
    return NULL;
  char* buff = calloc(s21_strlen(str), sizeof(char));
  s21_size_t k = 0;
  for (s21_size_t i = 0; i < s21_strlen(src) + s21_strlen(str); i++) {
    if (i < start_index) {
      buff[i] = src[i];
    } else if (i >= start_index && i < start_index + s21_strlen(str)) {
      buff[i] = str[k];
      k++;
    } else 
      buff[i] = src[i - s21_strlen(str)];
  }
  return buff;
}
