# Project based on Qt lib on Qt Creator
# On Ubumtu some lib need to install
# sudo apt install build-essential mesa-common-dev cmake clang clang-format
# qt6-base-dev qml-qt6 qt6-wayland qtcreator mailcap# Some commands must be used
# sudo update-alternatives --install /usr/bin/qmake qmake /usr/bin/qmake6 100
# sudo update-alternatives --config qmake
# gtests
# 
# May some of this not need
# make targets all, install, uninstall, clean, dvi, dist, tests
# xxd -i b.png > image_b_data.cpp
.PHONY: all clean build tests
CC = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra
GCOV = --coverage
TARGET = S21_MAZE
TESTSDIR = tests/
TESTS = $(TESTSDIR)tests.out
OS = $(shell uname -s)
GT_FLAGS = -DTESTS_OBJ_PATH='"$(shell pwd)/src/tests/samples/"' -lgtest_main -lgtest -pthread -g
PRO_FILE = src/view/maze_qt_view/maze_qt_view.pro
ARCHIVE = archive_1.0$(TARGET)
PWD = $(shell pwd)

#  Project files and directories
BUILD_DIR = build
INSTALLDIR = appfolder
CLANGFOLDERS = src/controller/*.h src/model/*.h src/model/*.cc src/tests/*.cc src/view/maze_qt_view/*.h src/view/maze_qt_view/*.cc

ifeq ($(OS), Darwin)
    LIBS := -lcheck
	APPLICATION = $(TARGET).app
	OPEN = open $(APPLICATION)
	APP_NAME = -DNAME_OF_APP=$(APPLICATION)
else
    LIBS := -lgtest -lstdc++ -lcheck_pic -lrt -lpthread -lsubTESTS -lm -g
	APPLICATION = $(TARGET)
	OPEN = ./$(APPLICATION)
	APP_NAME = -DNAME_OF_APP=$(APPLICATION)
endif

all: install

install: build
	mkdir -p $(INSTALLDIR)
	cp -rf ./$(BUILD_DIR)/$(APPLICATION) ./$(INSTALLDIR)
	cd $(INSTALLDIR) && $(OPEN)

uninstall:
	rm -rf $(INSTALLDIR)

clean:
	rm -rf ./$(BUILD_DIR)/* ./src/view/build* ./$(ARCHIVE)

dvi:
	# * * * * * * * * * * * * * * * *

	echo "$(PWD)/dvi.html"

	# * * * * * * * * * * * * * * * *
	open dvi.html

dist: build
	rm -rf $(ARCHIVE)/
	mkdir -p $(ARCHIVE)/
	mkdir -p $(ARCHIVE)/bin
	cp -r ./$(BUILD_DIR)/$(APPLICATION) $(ARCHIVE)/bin
	cp ./Makefile $(ARCHIVE)/
	cp ./dvi.html $(ARCHIVE)/
	mkdir -p $(ARCHIVE)/src
	cp -r ./src/* $(ARCHIVE)/src/
	tar cvzf $(ARCHIVE)/$(ARCHIVE).tgz $(ARCHIVE)/

tests: loadertest walkertest modeltest generatortest

gcov_report:
	mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CXXFLAGS) $(GT_FLAGS) $(GCOV) ./src/model/s21_maze.cc ./src/model/s21_maze_generator.cc ./src/tests/s21_maze_generator_test.cc ./src/model/s21_maze_walker.cc ./src/tests/s21_maze_walker_test.cc -o $(BUILD_DIR)/$(TESTS) 
	./$(BUILD_DIR)/$(TESTS)
	cd ./$(BUILD_DIR)/$(TESTSDIR) && lcov --ignore-errors unused --ignore-errors inconsistent -t "tests.out" -o test.info --exclude "*/11/*" --exclude "/usr/*" -c -d .
	cd ./$(BUILD_DIR)/$(TESTSDIR) && genhtml -o report test.info
	cd ./$(BUILD_DIR)/$(TESTSDIR) && open report/index.html

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && qmake TARGET=$(APPLICATION) CONFIG+=qtquickcompiler ../$(PRO_FILE) && make

open:
	cd $(BUILD_DIR) && $(OPEN)

loadertest:
	mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CXXFLAGS) $(GT_FLAGS) src/tests/s21_maze_loader_saver_test.cc src/model/s21_maze_loader_saver.cc src/model/s21_maze.cc -o $(BUILD_DIR)/$(TESTS)
	./$(BUILD_DIR)/$(TESTS)

modeltest:
	mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CXXFLAGS) $(GT_FLAGS) src/tests/s21_maze_model_test.cc src/model/* -o $(BUILD_DIR)/$(TESTS)
	./$(BUILD_DIR)/$(TESTS)

walkertest:
	mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CXXFLAGS) $(GT_FLAGS) src/tests/s21_maze_walker_test.cc src/model/s21_maze_walker.cc src/model/s21_maze.cc -o $(BUILD_DIR)/$(TESTS)
	./$(BUILD_DIR)/$(TESTS)

generatortest:
	mkdir -p $(BUILD_DIR)/tests
	$(CC) $(CXXFLAGS) $(GT_FLAGS) src/tests/s21_maze_generator_test.cc src/model/* -o $(BUILD_DIR)/$(TESTS)
	./$(BUILD_DIR)/$(TESTS)

clang:
	clang-format -style=file:./materials/linters/.clang-format -n $(CLANGFOLDERS)
	clang-format -style=file:./materials/linters/.clang-format -i $(CLANGFOLDERS)
