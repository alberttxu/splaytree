CFLAGS = -g -fsanitize=address
# CFLAGS = -g

CC = /usr/local/opt/llvm/bin/clang
#CC = /usr/local/opt/gcc/bin/gcc-11

main:
	${CC} ${CFLAGS} -o main main.c splaytree.c

.PHONY: clean
clean:
	rm main

