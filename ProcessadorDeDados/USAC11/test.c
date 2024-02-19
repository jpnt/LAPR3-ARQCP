#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../USAC07/sensordata.h"
#include "../USAC07/dir.h"

int main(int argc, char *argv[])
{
	if (argc != 5) {
		fprintf(stderr, "Erro: Argumentos específicados incorretamente.\n");
		printf("Uso: processador-de-dados [SERIAL_PORT] [CONFIG_FILE]"
					" [DIR_INTERMEDIO] [NUM_LEITURAS]\n");
		return EXIT_FAILURE;
	}
	// Parametros
	const char* serialPort = argv[1];
	const char* configFile = argv[2];
	const char* dirIntermedio = argv[3];
	int numLeituras = atoi(argv[4]);

	// Configurar o diretório intermédio
	dir_configure(dirIntermedio);

	// Criar estruturas
	ConfigData* cfg = configdata_create(configFile);
	SensorData* ssr = sensordata_create(cfg);
	ColetorData* col = NULL;

	int numSensores = cfg->num_lines;
	
	// START TESTES ESTRUTURAS
	/* configdata_print(cfg); */
	/* sensordata_print(&s[0]); */
	
	/* ColetorData* col = coletordata_create(serialPort); */
	/* coletordata_print(col); */
	
	/* sensordata_add(cfg, col, s); */

	/* sensordata_print(&s[9]); */
	/* circularbuffer_print(s[9].cb); */

	/* for (int i = 0; i < numSensores; i++) { */
	/* 	configdata_print(&cfg[i]); */
	/* } */


	// srlInfo é a informação serializada dos sensores
	char* srlInfo[numSensores];

	/* while (1) { */
		int contadorLeitura = 0;
		do {
			col = coletordata_create(serialPort);
			sensordata_add(cfg, col, ssr);
			coletordata_destroy(col);

			contadorLeitura++;
		
		} while (contadorLeitura < numLeituras);

		for (int i = 1; i <= numSensores; i++) {
			sensordata_compute_median(&ssr[i]);
			sensordata_serialize(ssr, i, srlInfo);
		}
		sensordata_fwrite_srl(dirIntermedio, srlInfo); // AAAAMMDD_sensors.txt */ 
	/* } */


	// TESTES PARA IMPRIMIR DADOS OBTIDOS
	/* int numSensores = cfg->num_lines; */
	/* for(int i = 0; i < numSensores; i++) { */
	/* 	sensordata_print(&s[i]); */
	/* 	circularbuffer_print(s[i].cb); */
	/* } */

	return EXIT_SUCCESS;
}
