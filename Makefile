canvascii: canvascii.c
	gcc -g -o canvascii -std=c11 -Wextra canvascii.c

test:
	bats check.bats
