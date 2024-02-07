CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SRC = C_part/*c
OS = $(shell uname)
QMAKE = qmake6

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
	EXE_FILE=3DViewer_v1.app
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lcheck_pic -lrt -lm
	EXE_FILE=3DViewer_v1
endif

all: install

install:
	mkdir -p build
	cd Qt && $(QMAKE) && make && mv $(EXE_FILE) ../build
	cd Qt && rm -rf *.o moc_* -rf ui_* Makefile .qmake.stash
    
uninstall:
	rm -rf build
    
dist: install
	tar -cf 3DViewer.tar.gz build/
	rm -rf build
    
extract:
	tar -xvf 3DViewer.tar.gz
    
dvi: open_dvi

open_dvi:
	open ./dvi/index.html

clean: clean_tests
	cd Qt && rm -rf *.o moc_* -rf ui_* Makefile .qmake.stash
	rm -rf build 3DViewer.tar.gz

gcov_report:
	cd Tests && \
    $(CC) $(GCOVFLAGS) s21_3DViewer_tests.c ../$(SRC) -o s21_3DViewer_tests $(TEST_LIBS) && \
	./s21_3DViewer_tests && \
    gcov -f *gcno *gcda 
	cd Tests && \
	rm -rf *.gcda *.gcno *gcov s21_3DViewer_tests

tests:
	cd Tests && \
	$(CC) s21_3DViewer_tests.c ../$(SRC) -o s21_3DViewer_tests $(TEST_LIBS) -L. --coverage && \
	./s21_3DViewer_tests

valgrind: clean
	cd Tests && \
	$(CC) s21_3DViewer_tests.c ../$(SRC) -o s21_3DViewer_tests $(TEST_LIBS) && \
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./s21_3DViewer_tests

sanitize: clean
	cd Tests && \
	$(CC) s21_3DViewer_tests.c ../$(SRC) -o s21_3DViewer_tests $(TEST_LIBS) -fsanitize=address && \
	./s21_3DViewer_tests

clean_tests:
	cd Tests && \
	rm -rf *.gcno *.gcda s21_3DViewer_tests report *.info *gcov *txt

do_style:
	clang-format -style=Google -i C_part/*c C_part/*h
	clang-format -style=Google -i Qt/*cpp Qt/*h
	clang-format -style=Google -i Tests/*c

check_style:
	clang-format -style=Google -n C_part/*c C_part/*h
	clang-format -style=Google -n Qt/*cpp Qt/*h
	clang-format -style=Google -n Tests/*c
