#include "s21_string.h"
#include <string.h>

void *s21_memchr(const void *str, int c, s21_size_t n){
    const unsigned char *s = (const unsigned char *) str;
    char* res = S21_NULL;
    s21_size_t i = 0;
    while (res == S21_NULL && i < n) {
      if(s[i] == c)
        res = (void *)s + i;
      i++;
    }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *) str1;
   const unsigned char *s2 = (const unsigned char *) str2;
   s21_size_t i = 0;
   while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) 
      i++;
   return s1[i] - s2[i];
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *dest_s = (unsigned char *)dest;
  const unsigned char *src_s = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++)
    dest_s[i] = src_s[i];
  return dest_s;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n){
    unsigned char *dest_s = (unsigned char *)dest;
    const unsigned char *src_s = (const unsigned char *)src;
    unsigned char* buffer = malloc(sizeof(char) *n);
    for (s21_size_t i = 0; i < n; i++)
      buffer[i] = src_s[i];
    for (s21_size_t i = 0; i < n; i++)
      dest_s[i] = buffer[i];
    free(buffer);
    return dest_s;
}

void *s21_memset(void *str, int c, s21_size_t n){
  unsigned char *s = (unsigned char *)str;
  for(s21_size_t i = 0; i < n; i++){
    s[i] = c;
  }
  return s;
}

char *s21_strcat(char *dest, const char *src){
  s21_size_t dest_l = s21_strlen(dest);
  for(s21_size_t i = 0; src[i] != '\0'; i++)
    dest[dest_l + i] = src[i];
  dest[dest_l + s21_strlen(src) + 1] = '\0';  
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n){
  s21_size_t dest_l = s21_strlen(dest);
  for(s21_size_t i = 0; src[i] != '\0' && i < n; i++)
    dest[dest_l + i] = src[i];
  dest[dest_l + s21_strlen(dest) + 1] = '\0';  
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char * res = S21_NULL;
  s21_size_t i = 0;
  while (str[i] != '\0' && res == S21_NULL) {
    if (str[i] == c)
      res =  (char*) &str[i];
    i++;
  }
  return res;
}

int s21_strcmp(const char *str1, const char *str2) {
  for(;*str2 && *str1 && (*str1 == *str2); str1++, str2++) {
  }
  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i =  0;
  for(;str2[i] && str1[i] && i < n && (str1[i] == str2[i]); i++) {
  }
  return str1[i] - str2[i];
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i, len = s21_strlen(src);
  for (i = 0; i <= len; i++) 
    dest[i] = src[i];
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i, len = s21_strlen(src);
  for (i = 0; i <= len && i < n; i++) 
    dest[i] = src[i];
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  for (; !s21_strchr(str2, str1[i]) && str1[i]; i++) {
  }
  return i;
 }

s21_size_t s21_strlen(const char *str){
  s21_size_t i;
  for (i = 0; str[i] != '\0'; i++) {
  }
  return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  return (char *)str1 + s21_strcspn(str1, str2);
}

char *s21_strrchr(const char *str, int c){
  char* res = S21_NULL;
  for(s21_size_t i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      res = (char *) str + i;
    }
  }
  return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t i = 0, j = 0;
  char * res = S21_NULL;
  do {
    j = 0;
    while (haystack[i] == needle[j] && needle[j] != '\0') {
      j++;
      i++;
    }
    if (needle[j] == '\0') 
     res = (char*) haystack + i - j;
  } while (haystack[i++] != '\0');
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char* adr;
    char* newtok = S21_NULL;
    char* oldtok = S21_NULL;
    int i = 0, index_buffer = 0, flag2 = 1;
    if (str != S21_NULL)
        adr = str;
    while (adr[i] != '\0' && flag2) {
      for (s21_size_t k = 0; k < s21_strlen(delim); k++) {
        if (adr[i] == delim[k] && !index_buffer) {
            index_buffer = i;
          break;
        }
        if (k == s21_strlen(delim) - 1 && adr[i] != delim[k] && index_buffer != 0) {
          flag2 = 0;
          newtok = adr + i;
          adr[index_buffer] = '\0';
        }
      }
      i++;
    }
    oldtok = adr;
    adr = newtok;
    return oldtok;
}


int main(){
    char str[] = "Geeks-for-Geeks";
 
    char* token = s21_strtok(str, " - ");
    
    while (token != S21_NULL) {
        printf("%s\n", token);
        token = s21_strtok(S21_NULL, " - ");
    }

  return 0;
}
