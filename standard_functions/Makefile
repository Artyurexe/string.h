CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 

all: s21_string.a

s21_string.a:
	$(CC) -c s21_string.c ../special_functions/special_functions.c
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: rebuild
	$(CC) $(CFLAGS) -lcheck -lm -lpthread s21_test.c s21_string.a  -o tests
	./tests
	rm tests

test_linux:
	make s21_string.a
	$(CC) $(CFLAGS) s21_test.c s21_string.a  -o test -lcheck_pic -pthread -lrt -lm -lsubunit
	./test
	rm test	

clean:
	rm -rf s21_string.a test

rebuild: clean all