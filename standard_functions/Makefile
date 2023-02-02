CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

all: s21_string.a

s21_string.a:
	$(CC) -c s21_string.c -o s21_string.o
	ar rcs s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test:
	make s21_string.a
	$(CC) $(CFLAGS) -lcheck -lm -lpthread s21_test.c s21_string.a  -o test
	./test
	rm test

clean:
	rm -rf s21_string.a test