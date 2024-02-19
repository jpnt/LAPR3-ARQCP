#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../USAC07/sensordata.h"

#define NUMSENSORES 10
#define STRMAXSIZE 100

void sensordata_serialize_test(SensorData* s, int idx, char** srl_info) {
	int sensor_id = s[idx].id;
	int write_counter = s[idx].write_counter;
	char* type = s[idx].type;
	char* unit = s[idx].unit;
	int mediana = s[idx].arr_median[0];
	
	snprintf(srl_info[idx], STRMAXSIZE, "%d,%d,%s,%s,%d#",
			sensor_id,write_counter,type,unit,mediana);
}

// TODO
void sensordata_fwrite_srl_test(char** srl_info) {
	time_t current_time; // Timer
	time(&current_time); // Return into timer

	char filename[21];
	strftime(filename, sizeof(filename), "%Y%m%d_sensors.txt", localtime(&current_time));

	FILE* file = fopen(filename, "w");

	if (file == NULL) {
		perror("Error");
		exit(1);
	}

	for (int i = 0; srl_info[i] != NULL; i++) {
		fprintf(file, "%s\n", srl_info[i]);
	}

	fclose(file);
}

int main()
{
	// TESTES PARA O NOME DO FICHEIRO
	time_t current_time;
	//printf("current_time=%ld\n",current_time); // Unitialized
	time(&current_time);
	printf("current_time=%ld\n",current_time);
	// YYYY-MM-DD
	char filename[21];
	strftime(filename, sizeof(filename), "%Y%m%d_sensors.txt", localtime(&current_time));
	printf("filename: %s\n",filename);

	
	

	// NOTA:
	// A funcao que serializa a informaçao do sensor está definida em
	// sensordata.h como `sensordata_serialize()`. Aqui estão alguns testes
	// feitos antes da implementação para encontrar a melhor solução para o
	// problema.


	// Valores teste da estrutura do sensor
	int sensor_id = 1;
	int write_counter = 1;
	char type[] = "type_whatever";
	char unit[] = "celcius";
	int mediana = 7;
	

	// TESTES...
	// SEM MEMORIA DINAMICA
	char* srlInfo[NUMSENSORES];

	srlInfo[0] = "sensor_id,write_counter,type,unit,mediana#1";

	srlInfo[1] = "sensor_id,write_counter,type,unit,mediana#2";


	// COM MEMORIA DINAMICA
	char* dynSrlInfo[NUMSENSORES];

	for (int i = 0; i < NUMSENSORES; i++) {
		dynSrlInfo[i] = (char *) malloc(STRMAXSIZE);
	}
	
	dynSrlInfo[0] = "teste";
	dynSrlInfo[1] = "testeaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	strcpy(dynSrlInfo[2], "teste_strcpy");

	for (int i = 3; i < NUMSENSORES; i++) {
		snprintf(dynSrlInfo[i], STRMAXSIZE, "%d,%d,%s,%s,%d#",sensor_id,write_counter,type,unit,mediana);
	}

	printf("dynSrlInfo[0]=%s\n",dynSrlInfo[0]);
	printf("dynSrlInfo[1]=%s\n",dynSrlInfo[1]);
	printf("dynSrlInfo[2]=%s\n",dynSrlInfo[2]);
	printf("dynSrlInfo[3]=%s\n",dynSrlInfo[3]);

	sensordata_fwrite_srl_test(dynSrlInfo);


	// FUNCOES QUE REQUEREM MALLOC:
	/* strcpy(srlInfo[2], "sensor_id,write_counter,type,unit,mediana#3"); */
	
	// char* str_into, size_t maxsize, const char* str_from
	/* snprintf(srlInfo[2], sizeof(srlInfo[2]), "sensor_id,write_counter,type,unit,mediana#3"); */



	// NOTA:
	// OS OUTROS VALORES DAQUI PARA A FRENTE SAO O QUER QUE SEJA QUE ESTEJA
	// EM MEMÓRIA!! PODE DAR SEGFAULT POIS TENTA ACESSAR MEMORIA QUE NAO PODE

	for (int i = 0; i < NUMSENSORES; i++) {
		printf("srlInfo[%d]=%s\n",i,srlInfo[i]);
	}


	return EXIT_SUCCESS;
}
