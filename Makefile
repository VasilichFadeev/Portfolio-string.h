CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS_MACOS = -lcheck -lm -lpthread
LDFLAGS_LINUX = -lcheck -lm -lpthread -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
REPORT_DIR = report

LIB_NAME = s21_string.a
TEST_EXEC = $(BIN_DIR)/s21_test
GCOV_EXEC = $(BIN_DIR)/s21_test_gcov

SRCS = $(SRC_DIR)/s21_string.c
TEST_SRC = $(SRC_DIR)/s21_test.c
LIB_OBJS = $(OBJ_DIR)/s21_string.o
TEST_OBJS = $(OBJ_DIR)/s21_test.o
GCOV_OBJS = $(OBJ_DIR)/s21_string_gcov.o

ERRORS_HEADER = $(SRC_DIR)/s21_errors.h

ifeq ($(shell uname), Darwin)
	OPEN_CMD = open
else
	OPEN_CMD = xdg-open
endif

.PHONY: all clean test s21_string.a gcov_report

all: s21_string.a $(TEST_EXEC)

s21_string.a: $(LIB_OBJS)
		@ar rcs $@ $^
		@echo "Library built: $@"

test: $(TEST_EXEC)
		@./$<

$(TEST_EXEC): $(LIB_OBJS) $(TEST_OBJS)
		@mkdir -p $(BIN_DIR)
		$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

gcov_report: clean $(GCOV_EXEC)
		@mkdir -p $(REPORT_DIR)
		@./$(GCOV_EXEC)
		@lcov -t "gcov_report" -o $(REPORT_DIR)/coverage.info -c -d $(OBJ_DIR)
		@genhtml -o $(REPORT_DIR) $(REPORT_DIR)/coverage.info
		@$(OPEN_CMD) $(REPORT_DIR)/index.html

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	LDFLAGS := $(LDFLAGS_MACOS)
else ifeq ($(UNAME), Linux)
	LDFLAGS := $(LDFLAGS_LINUX)
endif

$(GCOV_EXEC): CFLAGS += $(GCOV_FLAGS)
$(GCOV_EXEC): $(GCOV_OBJS) $(TEST_OBJS)
		@mkdir -p $(BIN_DIR)
		$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

rebuild: clean all

clean:
		@rm -rf $(OBJ_DIR) $(BIN_DIR) $(REPORT_DIR) *.a *.gcda *.gcno *.info

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/s21_string.h $(SRC_DIR)/s21_errors.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%_gcov.o: $(SRC_DIR)/%.c $(SRC_DIR)/s21_string.h $(ERRORS_HEADER)
		@mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@