#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../USAC07/configdata.h"
#include "../USAC07/coletordata.h"

// OLD FUNCTIONS
int old_count_lines(const char *file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		perror("Error opening file");
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

ConfigData* old_configdata_create(const char *file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		perror("Erro ao abrir ficheiro");
		exit(1);
	}

	int numLines = count_lines(file_name);

	ConfigData* configs = (ConfigData*) malloc(numLines * sizeof(ConfigData));
	if (configs == NULL) {
		perror("Erro: Não foi possível alocar memória para a estrutura de configuração.");
		exit(1);
	}

	for (int i = 0; i < numLines; i++) {
		if (fscanf(file, "%d#%[^#]#%[^#]#%u#%u#%u",
		&configs[i].sensor_id, configs[i].type, configs[i].unit,
		&configs[i].buffer_len, &configs[i].window_len, &configs[i].timeout) != 6) {
			printf("Error reading line %d of the configuration file\n", i + 1);
			free(configs);
			fclose(file);
			exit(1);
		}
	}
	fclose(file);

	return configs;

}

void read_sensor_data(char *str_out, int str_size, const char *file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		perror("Erro ao abrir ficheiro");
		exit(1);
	}

	if (fgets(str_out, str_size, file) == NULL) {
		perror("Erro ao ler ficheiro");
		fclose(file);
		exit(1);
	}
	fclose(file);
}

void parse_sensor_data(ColetorData* out, const char *sensordata_str) {
	int sensor_id;
	char type[32];
	double value_double;
	int value;
	char unit[32];
	int time;

	int ret = sscanf(sensordata_str, "sensor_id:%d#type:%[^#]#value:%lf#unit:%[^#]#time:%d",
                   &sensor_id, type, &value_double, unit, &time);
	if (ret != 5) {
		printf("Error parsing sensor data. sscanf returned %d\n", ret);
		exit(1);
	}

	value = (int)(value_double*100);

	// Only copy data if there are no errors
	out->sensor_id = sensor_id;
	strcpy(out->type, type);
	out->value = value;
	strcpy(out->unit, unit);
	out->time = time;
}

int old_main(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stderr, "Erro: "
		"Introduza o caminho para o ficheiro dos dados do sensor\n");
		return 1;
	}

	char* sensor_data_file = argv[1];
	char sensor_data_str[256];

	read_sensor_data(sensor_data_str, sizeof(sensor_data_str), sensor_data_file);

	ColetorData* col = (ColetorData*) malloc(sizeof(ColetorData));
	if (col == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para a estrutura do coletor.\n");
		return 1;
	}

	parse_sensor_data(col, sensor_data_str);




	//DATA FROM SENSOR
	printf("sensor_id: %d\n", col->sensor_id);
	printf("type: %s\n", col->type);
	printf("value: %d\n", col->value);
	printf("unit: %s\n", col->unit);
	printf("time: %d\n", col->time);


	ConfigData* cfg = old_configdata_create("config");
	if (col == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para a estrutura da configuração.\n");
		return 1;
	}

	int i = 0;

	while (cfg[i].sensor_id != col->sensor_id) {
		i++;
	}

	// DATA FROM CONFIG
	printf("buffer_len: %u\n", cfg[i].buffer_len);
	printf("window_len: %u\n", cfg[i].window_len);
	printf("timeout: %d\n", cfg[i].timeout);

	free(col);

	return 0;
}
// END OF OLD FUNCTIONS

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stderr, "Erro: "
		"Introduza o caminho para o ficheiro dos dados do sensor\n");
		return 1;
	}
	char* coletorDataFile = argv[1];
	
	ColetorData* col = coletordata_create(5);




	char strDestino[256];

	int s_port = coletordata_open_serial_port(coletorDataFile);

	coletordata_read_serial_port(s_port, strDestino);

	printf("%s\n", strDestino);


	coletordata_destroy(col);

	return 0;
}
