EXE = canvascii
C = canvascii.c
CC = gcc
DEBUG = -g
CREATE_EXE = -o
WARNINGS = -Wextra
VERSION11 = -std=c11
RUN_TESTS = bats
TESTS_LIST = check.bats

canvascii: $(C)
	$(CC) $(DEBUG) $(CREATE_EXE) $(EXE) $(VERSION11) $(WARNINGS) $(C)

test: $(TESTS_LIST)
	$(RUN_TESTS) $(TESTS_LIST)
clean: 
	rm $(EXE) *.o