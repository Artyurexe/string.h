#include "s21_sscanf2.h"
#define flags_char "CcsS"
#define flags_int "diouxn"
#define flags_float "EeFfGgAa"
#define width_float "L"
#define width_int_char "h"
#define width_shared "l"
#define int_64 "I64"
#define width_num "0123456789"

enum type_flag{
    SHARED,
    CHAR_INT,
    CHAR_FLAG,
    INT_FLAG,
    FLOAT_FLAG
};

int check_falid_format(const char *format, char *string){
  if ((strchr(format, ',')) != NULL){
    return 0;
  }
  int flags_type = -1;
  int count_shared = 0;
  int count_width = 0;
  int count_flags = 0;
  int width_type = -1;
  int shared_width = -1;
  //int flag = 1;
  char *temp_format = malloc(strlen(format)*sizeof(char));
  strcpy(temp_format, format);
 // char *temp_char = NULL;
  //char width_int[] = "lh"
  while (*temp_format!='\0'){
   //  int flag = 1;
    if (*temp_format == '\n' || *temp_format == ' ' || *temp_format == '\t'){
        printf("nice\n");
        temp_format++;
        continue;
    } 
    if (*temp_format != '%' && (flags_type == -1 && width_type == -1 && shared_width == -1)){
        if (*temp_format != *string){
            printf("symbol2 %c\n", *temp_format);
            return 0;
        }
        temp_format++;
        string++;
    } else {
        if (*temp_format == '%'){
            printf("nice %c \n",*temp_format);
            shared_width = -1;
            width_type = -1;
            flags_type = -1;
            count_flags = 0;
            count_width = 0;
            count_shared = 0;
            temp_format++;
        }
        printf("symb1 is %c\n", *temp_format);
            if (strchr(width_shared, *temp_format) != NULL && count_shared <= 2){
                shared_width = SHARED;
                count_shared++;
                temp_format++;
            }
        printf("symb %c \n", *temp_format);
            printf("symb2 is %c\n", *temp_format);
            if (width_type == -1 && count_width <= 2){
                if (strchr(width_int_char, *temp_format) != NULL){
                    width_type = CHAR_INT;
                     temp_format++;
                    count_width++;
                } else if(strchr(width_float, *temp_format) != NULL){
                    width_type = FLOAT_FLAG;
                     temp_format++;
                    count_width++;
                }
               // temp_format++;
            }
            printf("symb3 is %c\n", *temp_format);
            if (flags_type == -1 && count_flags < 1){
                if (strchr(flags_char, *temp_format) != NULL){
                    flags_type = CHAR_FLAG;
                    count_flags ++;
                     temp_format++;
                } else if (strchr(flags_int, *temp_format) != NULL){
                    flags_type = INT_FLAG;
                    count_flags ++;
                     temp_format++;
                } else if (strchr(flags_float, *temp_format) != NULL){
                    flags_type = FLOAT_FLAG;
                    count_flags ++;
                     temp_format++;
                }
             //   temp_format++;
            }
            printf("1) flag_type %d shared flag is %d shared_count %d width %d count_width %d\n", flags_type, shared_width, count_shared, width_type, count_width);
        printf("2) symb is %c  flag_type %d shared flag is %d shared_count %d width %d count_width %d\n", *temp_format, flags_type, shared_width, count_shared, width_type, count_width);
        if (flags_type == CHAR_FLAG && (width_type != -1 && width_type != CHAR_INT)){
            printf("is not char\n");
            return 0;
        } 
        if (flags_type == INT_FLAG &&(width_type != -1 && width_type != CHAR_INT)){
            printf("is not int\n");
            return 0;
        } 
        if (flags_type == FLOAT_FLAG && (width_type != -1 && width_type != FLOAT_FLAG)){
            printf("is not float\n");
            return 0;
        }
        if (count_shared > 2){
            printf("count shared\n");
            return 0;
        }
        if (count_width > 2){
            return 0;
        }
         if (flags_type != -1 ){
                if(*temp_format == ' '){
                    temp_format++;
                }
                if (*temp_format != *string){
                    printf("symbol2 %c\n", *temp_format);
                    return 0;
                }
                temp_format++;
                string++;
        }
        
    }

  } 
  return 1;  
}


int main(){
    char format[] = "   %hd sdas";
    char string[] = "sdas";
    printf("%d", check_falid_format(format, string));
}