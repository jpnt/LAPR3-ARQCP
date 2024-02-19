#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "circularbuffer.h"
#include "sensordata.h"
#include "coletordata.h"
#include "configdata.h"

// Cria a estrutura de dados para armazenar n dados de todos os sensores que o 
// processador de dados pretende. Caso não seja possivel alocar memória retorna NULL.
// Para adicionar os dados recebidos do coletor, utilizar `sensordata_add`.
SensorData* sensordata_create(ConfigData* cfg) {
	int n = cfg->num_lines;

	// Alocar memória para n sensores, em que n é o número de linhas do config file
	//SensorData* s = (SensorData *) malloc(n * sizeof(SensorData));
	SensorData* s = (SensorData *) calloc(n, sizeof(SensorData));
	if (s == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para a estrutura do sensor.\n");
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		// Alocar espaço e criar estrutura do buffer circular para cada sensor
		s[i].cb = circularbuffer_create(cfg[i].buffer_len);
		if (s[i].cb == NULL) {
			fprintf(stderr, "Erro:" 
			"Não foi possível alocar memória para a estrutura do buffer circular. i = %d\n", i);
			free(&s[i]);
			return NULL;
		}

	}

	s->arr_median = NULL;

	// A config data é recebida como um array de estruturas, enquanto que o 
	// coletor apenas contém os dados lidos de apenas 1 sensor.

	return s;
}

// Adiciona dados de um sensor à lista de sensores da estrutura SensorData; Para usar esta função
// é necessário primeiramente alocar o bloco de memória com o devido tamanho (sensordata_create)
void sensordata_add(SensorData* s, ConfigData* cfg, ColetorData* col) {
	// Obter indice do configdata cujo id seja igual ao id lido pelo coletor
	int idx = configdata_idx_sensor_id(cfg, col->sensor_id);

	// TESTE: verificar se está a adicionar corretamente os dados
	// O idx corresponde ao sensor_id - 1
	/* printf("idx=%d\n",idx); */
	/* printf("col->sensor_id=%d\n",col->sensor_id); */
	/* printf("cfg[idx].sensor_id=%d\n",cfg[idx].sensor_id); */
	/* printf("col->type=%d\n",col->sensor_id); */
	/* printf("col->unit=%d\n",col->sensor_id); */
	/* printf("cfg[idx].type=%s\n",cfg[idx].type); */
	/* printf("cfg[idx].unit=%s\n",cfg[idx].unit); */

	// Dados de cfg: sensor_id, type, unit, buffer_len, window_len, timeout
	// Dados de col: sensor_id, type, unit, value, time
	// Colocar estes dados dentro da estrutura SensorData
	
	// Caso seja preciso verificar se os dados do coletor correspondem ao do
	// ficheiro de configuração, antes de os adicionar ao sensordata.
	assert(cfg[idx].sensor_id == col->sensor_id);
	assert(strcmp(cfg[idx].type, col->type) == 0);
	assert(strcmp(cfg[idx].unit, col->unit) == 0);
	
	s[idx].id = col->sensor_id;
	strcpy(s[idx].type, col->type);
	strcpy(s[idx].unit, col->unit);
	s[idx].timeout = cfg[idx].timeout;
	s[idx].timestamp = col->time;
	s[idx].window_len = cfg[idx].window_len;

	circularbuffer_enqueue(s[idx].cb, col->value);
}

// Liberta o espaço em memória da estrutura dos dados do sensor
void sensordata_destroy(SensorData* s) {
	circularbuffer_destroy(s->cb);
	if (s->arr_median) { // if not null
		free(s->arr_median);
	}
	free(s);
}

int sensordata_is_error_state(SensorData* s) {
	time_t current_timestamp = time(NULL);

	if (current_timestamp == -1) {
		fprintf(stderr, "Erro: Não foi possível obter o timestamp atual.\n");
		return 1;
	}

	// TEST VERIFICAR VALORES
	/* printf("CURRENT TIMESTAMP : %ld\n", current_timestamp); */
	/* printf("S->TIMESTAMP : %d\n", s->timestamp); */

	time_t diff = current_timestamp - s->timestamp;

	if (diff < s->timeout) {
		// Está em erro
		return 1;
	}

	return 0;
}

void sensordata_print(SensorData* s) {
	printf("SensorData = {\n"
		"  id: %d\n"
		"  type: %s\n"
		"  unit: %s\n"
		"  timestamp: %d\n"
		"  timeout: %d\n"
		"  write_counter: %d\n}\n",
		s->id, s->type, s->unit,
		s->timestamp, s->timeout, s->write_counter);
}

// Função para serializar informação do sensor. Coloca a informação em srl_info_out.
// Formato da string serializada: sensor_id,write_counter,type,unit,mediana#
void sensordata_serialize(SensorData* s, char* srl_info_out) {
	int srl_line_size = 256;

	if (sensordata_is_error_state(s) || s->arr_median == NULL) {
		snprintf(srl_info_out, srl_line_size, "%d,%d,%s,%s,error#",
		s->id, s->write_counter, s->type, s->unit);
	} else {
		snprintf(srl_info_out, srl_line_size, "%d,%d,%s,%s,%d#",
		s->id, s->write_counter, s->type, s->unit, s->arr_median[0]);
	}
}

int sensordata_not_null(SensorData* s) {
	if (s->id == 0) {
		return 0;
	}

	return 1;
}

// Escreve a informação serializada do sensor no ficheiro AAAAMMDD_sensors.txt
void sensordata_fwrite_srl(const char* dir, char srl_info[][256], int num_sensores) {
	time_t current_time;
	time(&current_time);

	char filename[21];
	strftime(filename, sizeof(filename), "%Y%m%d_sensors.txt", localtime(&current_time));

	// Concatenar diretório e nome do ficheiro
	char filepath[256];
	snprintf(filepath, sizeof(filepath), "%s/%s", dir, filename);

	FILE* file = fopen(filepath, "a");

	if (file == NULL) {
		perror("Error");
		exit(1);
	}

	for (int i = 0; i < num_sensores; i++) {
		fprintf(file, "%s\n", srl_info[i]);
	}

	fclose(file);
}

// Recebe um SensorData e coloca os dados do CircularBuffer dentro do arr_median;
// Depois ordena o arr_median e calcula a mediana. A mediana é colocada no primeiro
// indice no array (para facilitar o acesso) e é devolvida como retorno.
int sensordata_compute_median(SensorData* s) {
	int n = (int) s->window_len;
	// Não podemos retirar mais elementos do que aqueles que temos no buffer
	// circular. Porém só podemos tirar no máximo `window_len` elementos.
	if (s->cb->count < n) {
		n = s->cb->count;
	}

	// Alocar memória para o array de calculo da mediana dinamicamente com 
	// base no valor de n
	s->arr_median = (int *) calloc(n, sizeof(int));
	if (s->arr_median == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para o array da mediana.\n");
		exit(1);
	}

	for(int i = 0; i < n; i++) {
		s->arr_median[i] = circularbuffer_dequeue(s->cb);
	}

	sensordata_bbsort_arr_median(s, n);
	
	s->write_counter++;

	int median = s->arr_median[n/2];

	return median;
}

void sensordata_bbsort_arr_median(SensorData* s, int n) {
	if (s->arr_median == NULL) {
		fprintf(stderr, "Error: arr_median não foi inicializado\n");
		return;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (s->arr_median[j] > s->arr_median[j+1]) {
				int tmp = s->arr_median[j];
				s->arr_median[j] = s->arr_median[j+1];
				s->arr_median[j+1] = tmp;
			}
		}
	}
	// NOTA: Não é necessário retornar nada pois estamos a modificar diretamente
	// o arr_median dentro da estrutura SensorData !!!
}

// Função para testar a estrutura na USAC07
SensorData* sensordata_create_test(int id, char* type, char* unit, int buffer_size, 
		int median_size, unsigned int timestamp, int timeout) {

	SensorData* s = (SensorData *) malloc(sizeof(SensorData));
	if (s == NULL) {
		fprintf(stderr, "Erro:" 
		"Não foi possível alocar memória para a estrutura do sensor.\n");
		return NULL;
	}

	s->cb = circularbuffer_create(buffer_size);
	if (s->cb == NULL) {
		free(s);
		return NULL;
	}

	s->arr_median = (int*) malloc(median_size * sizeof(int));
	if (s->arr_median == NULL) {
		circularbuffer_destroy(s->cb);
		free(s);
		return NULL;
	}

	s->id = id;
	strcpy(s->type, type);
	strcpy(s->unit, unit);
	// s->timestamp = (unsigned int) time(NULL); */ 
	s->timestamp = timestamp;
	s->timeout = timeout;
	s->write_counter = 0;

	return s;
}
