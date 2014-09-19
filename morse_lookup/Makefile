CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

run : main.o morse_code.o
	${CC} ${CFLAGS} morse_code.o main.o ${LDFLAGS} -o run

morse_code.o : morse_code.c morse_code.h
	${CC} ${CFLAGS} -c morse_code.c

main.o : main.c morse_code.h
	${CC} ${CFLAGS} -c main.c

clean:
	rm *.o run
