CC = gcc
FLAGS = -Wall -Wextra -fanalyzer
INCLUDES = ../USAC07/coletordata.h ../USAC07/configdata.h
SOURCES =  main.c ../USAC07/coletordata.c ../USAC07/configdata.c
ASMSOURCES =
OBJFILES =  main.o ../USAC07/coletordata.o ../USAC07/configdata.o
EXEC = usac08

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
	rm -f ${OBJFILES} *.o ${EXEC}
