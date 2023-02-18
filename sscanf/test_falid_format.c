#include "s21_sscanf2.h"

int check_falid_format(const char *format, char *string){
  char *ptr = NULL;
  if ((strchr(format, ',')) != NULL){
    return 0;
  }
  char *temp_format = malloc(strlen(format)*sizeof(char));
  strcpy(temp_format, format);
  
  while (*temp_format!='\0'){
    char temp_ch = *temp_format;
    //printf("%c",temp_ch);
    if (temp_ch == '%'){
        
        temp_format++;
        
        while(*temp_format!='%' && *temp_format!='\0'){
            printf("1\n");
            char *ptr = NULL;
            if ((strchr(string, '%')) != NULL){
                
                printf("%s\n", ptr);
            }
            temp_format++;
        }
    } else if (*temp_format!='\0') {
        if (temp_ch != *string && *string !='\0'){
            printf("fuck2 %c %s\n", temp_ch, string);
        }
        temp_format++;
        string++;
    }
  }   
}


int main(){
    char format[] = "sdafsdf%dasda%d";
    char string[] = "sdafsdf%asdas%d";
    check_falid_format(format, string);
}