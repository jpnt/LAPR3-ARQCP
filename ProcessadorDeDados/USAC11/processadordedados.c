#include <stdio.h>
#include <stdlib.h>
#include "processadordedados.h"
#include "../USAC07/sensordata.h"
#include "../USAC07/dir.h"

void processador_de_dados(const char* file_dados_coletor, const char* config_file,
		const char* dir_intermedio, int num_leituras) {

	// Configurar o diretório intermédio (USAC07)
	dir_configure(dir_intermedio);

	// Criar estruturas (USAC07)
	ConfigData* cfg = configdata_create(config_file);
	SensorData* ssr = sensordata_create(cfg);
	ColetorData* col = coletordata_create(num_leituras);

	int numSensores = cfg->num_lines;

	// srlInfo é a informação serializada dos sensores
	char srlInfo[numSensores][256];

	while (1) {
		int contLeitura = 0;
		do {
			// receber os dados envidados pelo coletor e insere dados
			// nas estruturas de dados criadas   (USAC08 e USAC09)

			// conta apenas leituras que são bem sucedidas
			contLeitura += coletordata_add(&col[contLeitura], file_dados_coletor);

		} while (contLeitura < num_leituras);

		// continuação da USAC09
		for (int i = 0; i < num_leituras; i++) {
			sensordata_add(ssr, cfg, &col[i]);
		}

		for (int i = 0; i < numSensores; i++) {
			if (sensordata_not_null(&ssr[i])) {

				sensordata_compute_median(&ssr[i]);

				sensordata_serialize(&ssr[i], &srlInfo[i][0]);
			}
			printf("serialized info : %s\n", srlInfo[i]);
		}


		sensordata_fwrite_srl(dir_intermedio, srlInfo, numSensores); // AAAAMMDD_sensors.txt
	}

	configdata_destroy(cfg);
	sensordata_destroy(ssr);
	coletordata_destroy(col);
}

