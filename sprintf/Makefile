CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_string.a

s21_string.a:
	$(CC) -c ../standard_functions/s21_string.c s21_sprintf.c 
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test:
	make s21_string.a
	$(CC) $(CFLAGS) -lcheck -lm -lpthread s21_string.a s21_test.c -o test
	./test
	rm test

clean:
	rm -rf s21_string.a