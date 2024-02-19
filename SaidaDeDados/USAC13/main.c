#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "saidadedados.h"

int main(int argc, char *argv[])
{
	if (argc != 4) {
		fprintf(stderr, "Erro: Argumentos específicados incorretamente.\n");
		printf("Uso: saida-de-dados [DIR_INTERMEDIO] [DIR_OUTPUT] [PERIODO_MILLIS]\n");
		return 1;
	}
	const char* dirIn = argv[1];
	const char* dirOut = argv[2];
	unsigned int periodicidade = atoi(argv[3]);

	/* char testStr[] = "1,1,soil_humidity,percentage,2160#"; */
	
	/* str_int_to_float(testStr); */
	
	//process_file("./intermedio/20240103_sensors.txt");

	saida_de_dados_periodo(dirIn, dirOut, periodicidade);

	return 0;
}
