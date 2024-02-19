#include <stdio.h>
#include <stdlib.h>
#include "configdata.h"

// Conta o número de linhas de um ficheiro
int count_lines(const char *file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		perror("Erro ao abrir ficheiro");
		exit(1);
	}
	int count = 0;
	char ch;
	while ((ch = fgetc(file)) != EOF) {
		if (ch == '\n') {
			count++;
		}
	}
	fclose(file);
	return count;
}

ConfigData* configdata_create(const char *file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		perror("Erro ao abrir ficheiro de configuração");
		return NULL;
	}
	int numLines = count_lines(file_name);

	ConfigData* configs = (ConfigData *) malloc(numLines * sizeof(ConfigData));
	if (configs == NULL) {
		fprintf(stderr, "Erro:"
		"Não foi possível alocar memória para a estrutura de configuração.");
		return NULL;
	}

	for (int i = 0; i < numLines; i++) {
		int ret = fscanf(file, "%d#%[^#]#%[^#]#%u#%u#%u",
		&configs[i].sensor_id, configs[i].type, configs[i].unit,
		&configs[i].buffer_len, &configs[i].window_len, &configs[i].timeout);
		if (ret != 6) {
			fprintf(stderr, "Error parsing config data. sscanf returned %d\n", ret);
			free(configs);
			fclose(file);
			exit(1);
		}
		configs[i].num_lines = numLines;
	}
	fclose(file);

	return configs;
}

	
void configdata_destroy(ConfigData *cfg) {
	free(cfg);
}

// Obtém o índice da lista de configs cujo o sensor_id corresponda ao sensor_id da config
int configdata_idx_sensor_id(ConfigData *cfg, int sensor_id) {
	if (cfg == NULL) {
		fprintf(stderr, "Erro:"
		"A estrutura da configuração está vazia.");
		exit(1);
	}
	int idx = 0;
	while(cfg[idx].sensor_id != sensor_id) {
		idx++;
	}
	return idx;
}

void configdata_print(ConfigData *cfg) {
	printf("ConfigData = {\n"
		"  sensor_id: %d\n"
		"  type: %s\n"
		"  unit: %s\n"
		"  buffer_len: %u\n"
		"  window_len: %u\n"
		"  timeout: %u\n"
		"  num_lines: %u\n}\n",
		cfg->sensor_id, cfg->type, cfg->unit,
		cfg->buffer_len, cfg->window_len, cfg->timeout, cfg->num_lines);
}
