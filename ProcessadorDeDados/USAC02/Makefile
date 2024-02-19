CC = gcc
FLAGS = -g -Wall -Wextra -fanalyzer
INCLUDES = enqueue_value.h
SOURCES =  main.c
ASMSOURCES = enqueue_value.s
OBJFILES =  main.o enqueue_value.o
EXEC = enqueue-value

# Suffix rules
.SUFFIXES : .c .s .o

# How to build an object .o from a code file .c ; $< -- file name
.c.o:
	${CC} ${FLAGS} -c $<

# How to build an object .o from a code file .s 
.s.o:
	${CC} ${FLAGS} -c $<

${EXEC}: ${OBJFILES}
	${CC} ${OBJFILES} -o ${EXEC}

${OBJFILES}: ${SOURCES} ${ASMSOURCES} ${INCLUDES}

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${OBJFILES} ${EXEC}
