CC = gcc
FLAGS = -Wall -Wextra -fanalyzer
INCLUDES = 
SOURCES =  main.c
ASMSOURCES =
OBJFILES =  main.o 
EXEC = usac10

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
