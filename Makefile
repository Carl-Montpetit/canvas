canvascii: canvascii.c
	gcc -o canvascii -std=c11 -Wextra canvascii.c

test:
	bats check.bats
