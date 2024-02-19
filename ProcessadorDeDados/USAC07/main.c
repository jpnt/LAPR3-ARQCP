#include <stdio.h>
#include "circularbuffer.h"
#include "sensordata.h"
#include "dir.h"

int main(void)
{
	// NOTA: Ler a main.c é um bom começo para perceber o programa. Aconselho
	// a abir uma janela ao lado com os header files (*.h) das estruturas,
	// com destaque à sensordata.h pois esta depende de quase todo o resto
	// (circularbuffer.h, coletordata.h e configdata.h).



	// CIRCULARBUFFER: é uma estrutura de dados definida em circularbuffer.h
	// com as suas respetivas funções. No código em baixo constam alguns 
	// testes iniciais que fiz com a estrutura e as suas funções.

	CircularBuffer* cb = NULL;
	cb = circularbuffer_create(10);

	for (int i = 1; i < cb->capacity; i++) {
		circularbuffer_enqueue(cb, i*10);
	}

	circularbuffer_enqueue(cb, 100);
	circularbuffer_enqueue(cb, 110);

	circularbuffer_print(cb);



	// SENSORDATA: dados de um sensor tratados após efetuar a leitura dos 
	// dados do coletor e de um ficheiro de configuração. Aqui apenas consta
	// uma demonstração da função sensordata_create. Foi feito assim para 
	// agilizar o processo. NOTA: Ver sensordata.h e USAC11 para ver como
	// realmente são criadas as estruturas no âmbito do projeto.

	SensorData* s = NULL;
	s = sensordata_create_test(1, "soil_humidity", "percentage", 50, 20, 2470030, 40000);

	if (sensordata_is_error_state(s)) {
		printf("SensorData is in error state\n");
	} else {
		printf("SensorData is not in error state\n");
	}

	sensordata_print(s);



	// CONFIGURAÇÃO DE UM DIRETÓRIO: segue aqui um exemplo de como configurar
	// um ficheiro e escrever algo. Ler dir.h e dir.c para mais detalhes.

	dir_configure("testdir");

	FILE* file = fopen("testdir/file.txt", "w");
	if (file == NULL) {
		perror("Error");
		return 1;
	}
	fprintf(file, "Lá está 2.0\n");
	fclose(file);


	// Tamanho das estruturas
	printf("sizeof CircularBuffer = %lu\n", sizeof(CircularBuffer));
	printf("sizeof SensorData = %lu\n", sizeof(SensorData));

	return 0;
}
