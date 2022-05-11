# CFLAGS = -g -fsanitize=address -Wall -Wextra -Wstrict-prototypes
CFLAGS = -g -O2 -Wall -Wextra -Wstrict-prototypes

#CC = /usr/local/opt/llvm/bin/clang
CC = /usr/local/opt/gcc/bin/gcc-11

main:
	${CC} ${CFLAGS} -o main main.c splaytree.c

.PHONY: clean
clean:
	rm main

