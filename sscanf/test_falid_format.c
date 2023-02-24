#include "s21_sscanf.h"

int check_falid_format(const char *format) {
  int flag = 1;
  if ((strchr(format, ',')) != NULL) {
    flag = 0;
  }
  int flags_type = -1;
  int count_shared = 0;
  int count_width = 0;
  int count_flags = 0;
  int width_type = -1;
  int shared_width = -1;
  char *temp_format = malloc(strlen(format) * sizeof(char));
  strcpy(temp_format, format);
  while (*temp_format != '\0') {
    if (*temp_format == '\n' || *temp_format == ' ' || *temp_format == '\t') {
      temp_format++;
      while (*temp_format == '\n' || *temp_format == ' ' ||
             *temp_format == '\t') {
        temp_format++;
      }
    }
    if (*temp_format != '%' &&
        (flags_type == -1 && width_type == -1 && shared_width == -1)) {
      while(*temp_format!='%'){
        temp_format++;
      }
    } else {
      if (*temp_format == '%') {
        shared_width = -1;
        width_type = -1;
        flags_type = -1;
        count_flags = 0;
        count_width = 0;
        count_shared = 0;
        temp_format++;
      }
        if (*temp_format == '\n' || *temp_format == ' ' || *temp_format == '\t') {
      temp_format++;
      while (*temp_format == '\n' || *temp_format == ' ' ||
             *temp_format == '\t') {
        temp_format++;
      }
    }
      if (strchr(width_num, *temp_format) != NULL) {
        temp_format++;
        while (strchr(width_num, *temp_format) != NULL) {
          temp_format++;
        }
      }

      if (strchr(width_shared, *temp_format) != NULL){
        shared_width = SHARED;
        count_shared++;
        temp_format++;
        while(strchr(width_shared, *temp_format) != NULL){
            count_shared++;
            temp_format++;
        }
        
      }
      if (count_shared > 2){
        return 0;
      } 
      if (count_shared + count_width > 2){
        return 0;
      }
      if (count_width < 2) {
        if (strchr(width_int_char, *temp_format) != NULL) {
          width_type = CHAR_INT;
          temp_format++;
          count_width++;
          while(strchr(width_int_char, *temp_format) != NULL){
            count_width++;
            temp_format++;
          }
        } else if (strchr(width_float, *temp_format) != NULL) {
          width_type = FLOAT_FLAG;
          temp_format++;
          count_width++;
          while(strchr(width_float, *temp_format) != NULL){
            count_width++;
            temp_format++;
          }
        }
      }
      if (count_width > 2){
        return 0;
      }
      if (flags_type == -1 && count_flags < 1) {
        if (strchr(flags_char, *temp_format) != NULL) {
          flags_type = CHAR_FLAG;
          count_flags++;
          temp_format++;
        } else if (strchr(flags_int, *temp_format) != NULL) {
          flags_type = INT_FLAG;
          count_flags++;
          temp_format++;
        } else if (strchr(flags_float, *temp_format) != NULL) {
          flags_type = FLOAT_FLAG;
          count_flags++;
          temp_format++;
        }
        
      }
      if (count_flags == 1){
        if (*temp_format!= '%' || *temp_format != '\0'){
            temp_format++;
            continue;
        }
      }
      if (flags_type == CHAR_FLAG &&
          (width_type != -1 && width_type != CHAR_INT)) {
        flag = 0;
      }
      if (flags_type == INT_FLAG &&
          (width_type != -1 && width_type != CHAR_INT)) {
        flag = 0;
      }
      if (flags_type == FLOAT_FLAG &&
          (width_type != -1 && width_type != FLOAT_FLAG)) {
        flag = 0;
      }
      if (count_width!=0 && count_shared != 0 && flags_type == -1){
        return 0;
      }
    }
  }
  return flag;
}


// int main(){
//     char format[] = "   %   daaaf";
//     printf("%d", check_falid_format(format));
//     return 0;
// }