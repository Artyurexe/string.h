NAME = s21_sscanf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SRCS=	s21_sscanf.c test_falid_format.c
TEST_SRC=	s21_sscanf_test.c 
TEST_FLAGS_LINUX= -lcheck -lm -lsubunit -lpthread
TEST_FLAGS= -lcheck -lm -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs

all: ${NAME}

${NAME}:
	$(CC) -c ${SRCS}
	ar rc ${NAME} *.o
	ranlib ${NAME}
	rm *.o

test:
	make ${NAME}
	$(CC) -c ${TEST_SRC}	
	$(CC) *.o ${NAME} ${TEST_FLAGS} -o test

test_linux:
	make rebuild
	$(CC) -c ${TEST_SRC}	
	$(CC) *.o ${NAME} ${TEST_FLAGS_LINUX} -o test_linux

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