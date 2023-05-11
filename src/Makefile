UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LCOV= lcov
	GENHTML= genhtml 
	LFLAG= -lm -lrt -lpthread -lsubunit
endif
ifeq ($(UNAME), Darwin)
	PATH := $(PATH):${HOME}/homebrew/bin
	LCOV= $(shell PATH=$(PATH) which lcov)
	GENHTML= $(shell PATH=$(PATH) which genhtml) 
	LFLAG=
endif
CC=gcc
CFLAG= -Wall -Wextra -Werror -std=c11 -pedantic
DDEBUG= -g
SOURCE:=$(shell find . -maxdepth 2 -name "s21_*.c")
HEADER:=$(shell find . -maxdepth 2 -name "*.h")
LAUNCHER:=$(shell find s21_viewer -maxdepth 6 -name "3D_Viewer")
OBJECTS:=$(SOURCE:.c=.o)
RESULT= s21_viewer.a

all: $(RESULT) test gcov_report 

clean:
	rm -rf $(OBJECTS) $(RESULT) test report *.gc* *.out *.gch log.txt gcov* cov build

$(OBJECTS): %.o: %.c
	$(CC) $(DEBUG) $(CFLAG) -c $< -o $@ 

$(RESULT): $(OBJECTS)
	ar rc $@ $^
	ranlib $@

test: $(RESULT)
	$(CC) $(DEBUG) $(CFLAG) tests/*.c -o $@ $^ -lcheck $(LFLAG)
	rm -rf *.o *.gch
	./$@

gcov_report: clean
	mkdir -p cov
	$(CC) $(DEBUG) $(SOURCE) tests/*.c -lcheck -o $@ --coverage $(LFLAG)
	./$@
	rm -rf *test*.gc*
	gcov -d . s21_*.c 
	$(LCOV) -d . -o cov/$@.info -c
	$(GENHTML) -o cov/report cov/$@.info
	open cov/report/index.html
	mv *.gc* cov

leak_style: test
	leaks -atExit -- ./test
	make clean
	cp ../materials/linters/.clang-format .
	clang-format -n $(SOURCE) $(HEADER) ./3dview/*.cpp
	rm -rf .clang-format

valgrind: test
	valgrind --log-fd=1 --leak-check=full --log-file=log.txt -s ./test

main: $(OBJECTS)
	$(CC) $(DEBUG) $(OBJECTS) main.c -o $@ $(LFLAG) -g
	./$@

install: $(RESULT)
	mv $(RESULT) 3dview/lib$(RESULT)
	cmake -S 3dview -B s21_viewer
	make -C s21_viewer
	cp 3dview/lib$(RESULT) s21_viewer/lib$(RESULT)
	cp $(OBJECTS) s21_viewer/

uninstall: 
	rm -rf s21_viewer

dist: install
	tar -czf s21_viewer.tar.gz --directory=s21_viewer/ .

dvi:
	open README.md

launch:
	./$(LAUNCHER)
