CC = gcc
FLAGS = -Wall -Wextra -fanalyzer
INCLUDES = ../USAC07/coletordata.h ../USAC07/configdata.h ../USAC07/sensordata.h ../USAC07/dir.h ../USAC07/circularbuffer.h ./processadordedados.h
SOURCES =  main.c  ../USAC07/coletordata.c ../USAC07/configdata.c ../USAC07/sensordata.c ../USAC07/dir.c ../USAC07/circularbuffer.c ./processadordedados.c
ASMSOURCES =
OBJFILES =  main.o ../USAC07/coletordata.o ../USAC07/configdata.o ../USAC07/sensordata.o ../USAC07/dir.o ../USAC07/circularbuffer.o ./processadordedados.o
EXEC = usac11

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
	./${EXEC} sensor_data config intermedio 7

clean:
	rm -f ${OBJFILES} *.o ${EXEC}
