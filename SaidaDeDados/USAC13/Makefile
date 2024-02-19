CC = gcc
FLAGS = -Wall -Wextra -fanalyzer
INCLUDES = saidadedados.h
SOURCES =  main.c saidadedados.c
ASMSOURCES =
OBJFILES =  main.o saidadedados.o
EXEC = usac13

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
	./${EXEC} intermedio output 60000

clean:
	rm -f ${OBJFILES} *.o ${EXEC}
