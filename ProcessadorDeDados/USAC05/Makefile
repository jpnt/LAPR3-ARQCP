CC = gcc
FLAGS = -g -Wall -Wextra -fanalyzer
INCLUDES = mediana.h
SOURCES =  main.c
ASMSOURCES = mediana.s sort.s
OBJFILES =  main.o mediana.o sort.o
EXEC = mediana

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
