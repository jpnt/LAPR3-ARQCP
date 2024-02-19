#include <stdio.h>
#include <stdlib.h>
#include "processadordedados.h"

int main(int argc, char *argv[])
{
	if (argc != 5) {
		fprintf(stderr, "Erro: Argumentos específicados incorretamente.\n");
		printf("Uso: processador-de-dados [SERIAL_PORT] [CONFIG_FILE]"
					" [DIR_INTERMEDIO] [NUM_LEITURAS]\n");
		return 1;
	}
	// Parametros
	const char* serialPort = argv[1];
	const char* configFile = argv[2];
	const char* dirIntermedio = argv[3];
	int numLeituras = atoi(argv[4]);

	processador_de_dados(serialPort, configFile, dirIntermedio, numLeituras);

	return 0;
}
