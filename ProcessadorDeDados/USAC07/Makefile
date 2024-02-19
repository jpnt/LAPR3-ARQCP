CC = gcc
FLAGS = -Wall -Wextra -fanalyzer
INCLUDES = dir.h circularbuffer.h sensordata.h coletordata.h configdata.h
SOURCES =  main.c dir.c circularbuffer.c sensordata.c coletordata.c configdata.c
ASMSOURCES = 
OBJFILES =  main.o dir.o circularbuffer.o sensordata.o coletordata.o configdata.o
EXEC = usac07

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
