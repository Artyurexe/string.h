#include "s21_sprintf.h"

void s21_sprintf(char *str, const char *format, ...) {
  const char* types = "cdieEfgGosuxXpn%%";
  va_list ap;
  va_start(ap, format);
  struct specifier spec;
  for (s21_size_t i = 0; i < s21_strlen(format); i++) {
    specifier_init(&spec);
    if (format[i] == '%') {
      specifier_parsing((char *) &(format[i + 1]), &spec);
      record(str, spec, &ap);
      i += s21_strcspn(&format[i + 1], types) + 1;
      printf("%s %s %s %s %c\n", spec.flag, spec.length, spec.precision, spec.width, spec.type);
    }
  }
}

void specifier_parsing(char *str, struct specifier* spec) {
  char* buff = str;
  char* buff1 = malloc(1024);
  int k = 0;
  const char* flags = "-+ #0";
  const char* numbers = "1234567890*";
  const char* length = "hlL";
  const char* types = "cdieEfgGosuxXpn%%";
  s21_size_t spec_length = s21_strcspn(str, types);
  spec->type = str[spec_length];
  pointer_shift(&spec_length, buff, buff1, flags);
  for (int i = 0; i < 5; i++) {
    if (s21_strchr(buff1, flags[i]) != S21_NULL && ((flags[i] == ' ' && s21_strchr(buff1, '+') == S21_NULL) || (flags[i] == '0' && s21_strchr(buff1, '-') == S21_NULL)))
      spec->flag[k++] = flags[i];
  }
  spec->flag[k] = '\0';
  k = 0;
  pointer_shift(&spec_length, buff, buff1, numbers);
  numbers_parsing(spec->width, buff1);
  if (*(buff++) == '.') {
    pointer_shift(&spec_length, buff, buff1, numbers);
    numbers_parsing(spec->precision, buff1);
  }
  s21_memcpy(buff1, buff, s21_strspn((const char*) buff, length));
  for (int i = 0; i < 3; i++) {
    char* c = s21_strchr(buff1, length[i]);
    if (c != S21_NULL) {
      if (length[i] == 'L' || (length[i] == 'h' && c < s21_strchr(buff1, 'l')) || (length[i] == 'l' && s21_strchr(c, length[i]) == S21_NULL && spec->length[0] != 'h')) {
        spec->length[k++] = length[i];
      } else if (length[i] == 'l' && s21_strchr(c, length[i]) != S21_NULL && spec->length[0] != 'h') {
        spec->length[k++] = length[i];
        spec->length[k++] = length[i];
      } 
    }
  }
  spec->length[k] = '\0';
  free(buff1);
}

void numbers_parsing(char* str, char* buff) {
  s21_size_t length = s21_strspn((const char*) buff, (const char*) "1234567890");
  if (*buff == '*' && length == 0)
    length = 1;
  s21_memcpy(str, buff, length);
}

void pointer_shift(s21_size_t* length, char* buff, char* buff1, const char* str) {
  *length = s21_strspn((const char*) buff, str);
  s21_memcpy(buff1, buff, *length);
  buff += *length;
}

void specifier_init(struct specifier* spec) {
  spec->flag[0] = '\0';
  spec->width[0] = '\0';
  spec->precision[0] = '\0';
  spec->length[0] = '\0';
  spec->type = 0;
}
char* dec_to_hex(int dec){
  char *hec= malloc(9*sizeof(char));
  int i = 7;

  while(i >= 0){
    int x = dec%16;
    dec /= 16;
    if(x < 10)
      x = x + '0';
    else 
     x = x-10 + 'a';
    hec[i] = x;
    i-- ;
  }
  hec[8] = '\0';
  return hec;
}

void record_pointer(char *str, struct specifier spec, va_list *ap){
  int pointer = va_arg(*ap, int);
  char str1[100] = "0x";
  char str2[100];
  char *hex = dec_to_hex(pointer);
  // s21_strcat(str1, hex);
  // free(hex);

  // printf("%s \n", str1);
  s21_size_t width = 0;
  if (s21_strlen(spec.width) != 0) {
    width = atoi(spec.width);
    if(width > 11){
      int dif = width - 11;
      if (s21_strchr(spec.flag, '0')){
        for(int i = 0; i < dif; i++){
          s21_strcat(str1, "0");
        }
        s21_strcat(str1, "1");
        s21_strcat(str1, hex);
      }
      if(s21_strchr(spec.flag, '-')){
        s21_strcat(str1, "1");
        s21_strcat(str1, hex);
        for(int i = 0; i < dif; i++){
          s21_strcat(str1, " ");
        }
      }
      else{
        for(int i = 0; i < dif; i++){
          s21_strcat(str2, " ");
        }
        s21_strcat(str2, str1);
        s21_strcpy(str1, str2);
        s21_strcat(str1, "1");
        s21_strcat(str1, hex);
      }
    } else {
      s21_strcat(str1, "1");
      s21_strcat(str1, hex);
    }
  }
  printf("%s\n", str1);
  free(hex);
}

void record(char *str, struct specifier spec, va_list *ap) {
  if (spec.type == 'c') {


  } else if (spec.type == 'd' || spec.type == 'i') {
    
  } else if (spec.type == 'e' || spec.type == 'E' || spec.type == 'f' || spec.type == 'g' || spec.type == 'G' ) {
    double num = va_arg(*ap, double);
  } else if (spec.type == 'o' || spec.type == 'u' || spec.type == 'x' || spec.type == 'X') {
    unsigned int num = va_arg(*ap, unsigned int);
  } else if (spec.type == 's') {
    char *str = va_arg(*ap, char *);
  } else if (spec.type == 'p') {
    record_pointer(str, spec, ap);
  } else if (spec.type == 'n') {
    int *arr = va_arg(*ap, int *);
  }

}

// int record_char(char *str, struct specifier spec, va_list *ap) {
//   s21_size_t width = 0;
//   if (s21_strlen(spec.width) != 0) {
//     width = atoi(spec.width);
//     if (!width)
//       return 1;
//     if (s21_strchr(spec.flag, '-') == S21_NULL)
//       for(int i = 0; i < width - 1; i++)
//         s21_strcat(str, " ");
//   }
//   if (s21_strchr(spec.length, 'l')) {
//     wchar_t wc = va_arg(*ap, wchar_t);
//     if (wcstombs(str + s21_strlen(str), &wc, 1) == 0)
//       return 1;
//   }
//   else {
//     char c = va_arg(*ap, char);
//     s21_size_t len = s21_strlen(str);
//     str[len] = c;
//     str[len + 1] = '\0';
//   }
//   if (width && s21_strchr(spec.flag, '-'))
//     for(int i = 0; i < width - 1; i++)
//         s21_strcat(str, " ");
//   return 0;
// }

// int record_str(char *str, struct specifier spec, va_list *ap) {
//   s21_size_t width = 0;
//   if (s21_strlen(spec.width) != 0) {
//     width = atoi(spec.width);
//     if (!width)
//       return 1;
//   }
//   if (s21_strchr(spec.length, 'l')) {
//     wchar_t *ws = va_arg(*ap, wchar_t*);
//     width -= wcslen(ws);
//     if (width) {
//       for(int i = 0; i < width; i++)
//         s21_strcat(str, " ");
//     }
//     if (wcstombs(str + s21_strlen(str), ws, wcslen(ws) * sizeof(wchar_t)) == 0)
//       return 1;
//   }
//   else {
//     char* s = va_arg(*ap, char*);
//     s21_size_t len = s21_strlen(str);
//     width -= s21_strlen(s);
//     if (width) {
//       for(int i = 0; i < width; i++)
//         s21_strcat(str, " ");
//     }
//     strcat(str, s);
//   }
//   if (width && s21_strchr(spec.flag, '-'))
//     for(int i = 0; i < width; i++)
//         s21_strcat(str, " ");
//   return 0;
// }



int main() {
  char test[] = "%20ppr";
  int a = 3;
  int *b;
  b = &a;
  char str[100];
  sprintf(str, test, b);
  puts(str);
  // char* str = dec_to_hex(1875620280);
  // printf("%x\n", 1875620280);
  
  
}