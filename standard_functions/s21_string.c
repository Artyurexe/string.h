#include "s21_string.h"
#include <string.h>

void *s21_memchr(const void *str, int c, s21_size_t n){
    const unsigned char *s = (const unsigned char *) str;
    char* res = NULL;
    for(int i = 0; i < n; i ++){
        if(s[i] == (char)c )
            res = (void *)s +i;
    }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n){
  const unsigned char *s1 = (const unsigned char *) str1;
   const unsigned char *s2 = (const unsigned char *) str2;
   int res = 0;
   for(; n --; s1--, s2--){
        if(*s1 != *s2)
            res = (*s1 > *s2) - (*s2 > *s1) ;
   }
   return res;
}
void *s21_memcpy(void *dest, const void *src, s21_size_t n){
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
  for(int i = 0; i < n; i++){
    s[i] = c;
  }
  return s;
}
char *s21_strcat(char *dest, const char *src){
  int dest_l = strlen(dest); // заменить на s21_strlen
  for(int i = 0; dest[i] != '\0'; i++)
    dest[dest_l + i] = src[i];
  dest[dest_l + strlen(dest)+ 1] = '\0';  
  return dest;
}
char *s21_strncat(char *dest, const char *src, s21_size_t n){
  int dest_l = strlen(dest); // заменить на s21_strlen
  for(int i = 0; dest[i] != '\0' && i < n; i++)
    dest[dest_l + i] = src[i];
  dest[dest_l + strlen(dest)+ 1] = '\0';  
  return dest;
}


char *s21_strchr(const char *str, int c) {
  int i = 0;
  char * res = NULL;
  for (; str[i] != c && str[i] != '\0'; i++) { // пробег 
    res = (char *)str + i + 1;
  }
  return res;
}


int s21_strcmp(const char *str1, const char *str2){
  for(; *str1 && (*str1 == *str2); str1++, str2++){
  }
  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n){
  for(int i =  0; i < n && (*str1 == *str2); str1++, str2++){
  }
  return *str1 - *str2;
}

char *s21_strcpy(char *dest, const char *src){ //посмотреть перекрытие
  int i;
  for (i = 0; src[i] != '\0'; i++) 
    dest[i] = src[i];
  dest[i] = '\0';
  return dest;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n){
  int i;
  for (i = 0; i < n; i++) 
    dest[i] = src[i];
  dest[i] = '\0';
  return dest;
}
s21_size_t s21_strcspn(const char *str1, const char *str2){  // то начала?

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

char *s21_strpbrk(const char *str1, const char *str2){ //??
  char * res = NULL;
  for(int i = 0; !s21_strchr(str1, str2[i]); i++){
     res = (char *)str1 + i;
     break;
  }
return res;
}
char *s21_strrchr(const char *str, int c){
  char* res = NULL;
  for(int i = 0; str[i] != '\n'; i++){
    if(str[i] ==  c)
      res = *(str+i);
  }
  return res;
}
char *s21_strstr(const char *haystack, const char *needle){
  int i = 0, j = 0;
  char * res = NULL;
  do {
    j = 0;
    while (haystack[i] == needle[j] && needle[j] != '\0') {
      j++;
      i++;
    }
    if (needle[j] == '\0') 
     res = haystack + i - j;
  } while (haystack[i++] != '\0');
  return res;
}

// char *s21_strtok(char *str, const char *delim) {
//   static char *start = S21_NULL;
//   if (!str) str = start;
//   str += s21_strspn(str, delim);
//   if (!*str) return S21_NULL;
//   char *r;
//   for (r = str; !s21_strchr(delim, *r) && *r != '\0'; r++) {
//   }
//   if (*r) *r++ = '\0';
//   start = r;
//   return str;
// }

/*
int main(){
    char str1[30] = "abcd12f";
    char str2[] = "abc";
    char str3[10];
    // s21_memset(str2, '1', 2);
    // s21_strncat(str1, str2, 5);
    // memmove(&str2[3], &str2[4], 2);
    
    // printf("memchr: %s  S21_memchr: %s\n",(char*) memchr(str1, '2', 6), (char*) s21_memchr(str1, '2', 6));
    // printf("memcmp: %d  s21_memcmp: %d", memcmp(str1, str2, 7), s21_memcmp(str1, str2, 7));
    // printf("s21_memcpy: %s memcpy: %s",(char*) s21_memcpy(&str2[3], &str2[4], 3), (char*) memcpy(&str2[3], &str2[4], 3));
    // printf("s21_memcmp: %d  memcmp: %d ", s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
    //  printf("s21_memcpy: %s \n memcpy: %s",(char*) s21_memmove(&str2[3], &str2[4], 3), (char*) memmove(&str2[3], &str2[4], 3));
    // printf("strcat %c ", str1[strlen(str1)]);
    // printf("s21_strchr %s strchr %s",  s21_strchr(str1, 'e'), strchr(str1, 'e'));
    // printf("s21_strcmp: %d strcmp: %d", s21_strcmp(str1, str2), strcmp(str1, str2));
    // printf("s21_strncmp: %d strncmp: %d", s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
    // printf("s21_strcpy: %s  strcpy: %s" , s21_strcpy(str3, str1), strcpy(str3, str1));
    // printf("s21_strncpy: %s  strncpy: %s" , s21_strncpy(str3, str1, 2), strncpy(str3, str1, 2));
    // printf("s21_strcspn %d strcspn %lu", s21_strcspn(str1, str2), strcspn(str1, str2));
    //printf("s21_strlen: %d strlen: %lu", s21_strlen(str1), strlen(str1));
    // printf("s21_strpbrk %s strpbrk %s", s21_strpbrk(str1, str2), strpbrk(str1, str2) );
    // printf("s21_strrchr: %s strrchr: %s", s21_strrchr(str1, 'e'), strrchr(str1, 'e'));
    //
  return 0;
}
*/
//error ?