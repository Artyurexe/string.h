#ifndef SRC_STRING_S21_STRING_H_
#define SRC_STRING_S21_STRING_H_
 
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int s21_size_t;
#define S21_NULL (void*)0
void * s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *s21_memmove(void *dest, const void *src, size_t n);
void *s21_memset(void *str, int c, size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, size_t n);

 #endif  // SRC_STRING_S21_STRING_H_