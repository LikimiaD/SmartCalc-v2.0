CC = g++
CFLAGS = -Werror -Wall -Wextra -std=c++17 -fPIC
GTEST_FLAGS = -lgtest -lgtest_main -pthread
QT = qmake
MODEL_DIR = ./model
TEST_DIR = ./tests
VIEW_DIR = ./view
CONTROLLER_DIR = ./controller
MODEL_LIB_NAME = libmodel.a
CONTROLLER_LIB_NAME = libcontroller.a
TEST_BIN_NAME = test_executable
QT_BIN_NAME = qt_app

QT_INCPATH = -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCharts
QT_LIBS = -lQt5Widgets -lQt5Gui -lQt5Core -lQt5Charts


.PHONY: all clean model_lib controller_lib install test coverage

all: clean gcov_flag model_lib controller_lib test coverage

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

model_lib:
	$(CC) $(CFLAGS) -c $(MODEL_DIR)/*.cpp -I$(MODEL_DIR)
	ar rcs $(MODEL_LIB_NAME) *.o
	rm -f *.o

lint:
	clang-format -n $(CONTROLLER_DIR)/*.cpp $(MODEL_DIR)/*.cpp $(TEST_DIR)/*.cpp $(VIEW_DIR)/*.cpp
	clang-format -n $(CONTROLLER_DIR)/*.h $(MODEL_DIR)/*.h $(VIEW_DIR)/*.h
	clang-format -n *.cpp

controller_lib:
	$(CC) $(CFLAGS) $(QT_INCPATH) -c $(CONTROLLER_DIR)/*.cpp -I$(CONTROLLER_DIR) -I$(MODEL_DIR) -I$(VIEW_DIR)
	ar rcs $(CONTROLLER_LIB_NAME) *.o
	rm -f *.o

install: model_lib controller_lib
	cd $(VIEW_DIR) && $(QT) view.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && make
	mv view/view ./$(QT_BIN_NAME)
	./$(QT_BIN_NAME)

test: model_lib controller_lib
	$(CC) $(CFLAGS) $(TEST_DIR)/*.cpp -L. -lmodel -lcontroller $(GTEST_FLAGS) -o $(TEST_BIN_NAME)
	./$(TEST_BIN_NAME)

coverage:
	lcov --directory . --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' '*/gtest/*' --output-file coverage.info.cleaned
	genhtml coverage.info.cleaned --output-directory coverage_report

dvi:
	open ../README.md

uninstall: clean

dist: install
	tar -czvf qt_app.tar.gz $(QT_BIN_NAME) view

clean:
	rm -f *.o *.a $(TEST_BIN_NAME) $(QT_BIN_NAME) *.gcda *.gcno *.gcov coverage.info
	rm -rf coverage_report
	if [ -d $(VIEW_DIR) ]; then cd $(VIEW_DIR) && $(QT) view.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug && make clean || true; fi
