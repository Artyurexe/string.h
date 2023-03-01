CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SRCS=	sscanf/s21_sscanf.c sscanf/test_falid_format.c sprintf/s21_sprintf.c special_functions/special_functions.c standard_functions/s21_string.c
TEST_SRC=	sprintf/s21_test.c
TEST_FLAGS_LINUX= -lcheck -lm -lsubunit -lpthread
TEST_FLAGS= -lcheck -lm -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs

all: s21_string.a

s21_string.a:
	$(CC) -c ${SRCS}
	ar rc s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: rebuild
	$(CC) ${CFLAGS} -c ${TEST_SRC}	
	$(CC) ${CFLAGS} *.o s21_string.a ${TEST_FLAGS} -o test
	./test
	rm *.o *.a test

test_linux: rebuild
	$(CC) -c ${TEST_SRC}	
	$(CC) *.o s21_string.a ${TEST_FLAGS_LINUX} -o test_linux

gcov_report:
	$(CC) ${GCOV_FLAGS} -c ${TEST_SRC}
	$(CC) $(GCOV_FLAGS) *.o $(TEST_FLAGS) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

gcov_report_linux:
	$(CC) ${GCOV_FLAGS} -c ${TEST_SRC}
	$(CC) $(GCOV_FLAGS) *.o $(TEST_FLAGS_LINUX) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o *.a test test_linux *.gcno *.gcda *.info report

rebuild : clean all

spr: rebuild
	$(CC) ${CFLAGS} sprintf/s21_sprintf.c standard_functions/s21_string.c
	./a.out
	rm a.out *.a