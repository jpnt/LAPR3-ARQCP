#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#include <assert.h>

#include "coletordata.h"

#define MAXSTRSIZE 256

ColetorData* coletordata_create(int num_leituras) {
	ColetorData* col = (ColetorData *) calloc(num_leituras, sizeof(ColetorData));
	if (col == NULL) {
		fprintf(stderr, "Erro: coletordata_create: "
		"Não foi possível alocar memória para a estrutura do coletor.\n");
	}
	return col;
}

void coletordata_destroy(ColetorData *col) {
	free(col);
}

int coletordata_add(ColetorData *col, const char* file_dados_coletor) {

	char str[MAXSTRSIZE];

	int s_port = coletordata_open_serial_port(file_dados_coletor);

	coletordata_read_serial_port(s_port, str);

	printf("%s\n", str);
	
	int result = coletordata_parse(col, str);

	/* coletordata_print(col); */

	return result;
}

// Lê os dados do coletor e copia uma linha para a str_out: NAO FUNCIONA PARA
// O FICHEIRO /dev/ttyACM0 !!!
void coletordata_read(char *str_out, int str_size, const char *file_name) {
	FILE* file = fopen(file_name, "r");
	if (file == NULL) {
		perror("Erro ao abrir ficheiro dos dados do coletor");
		exit(1);
	}

	if (fgets(str_out, str_size, file) == NULL) {
		fprintf(stderr, "Erro: "
		"Não foi possível ler o ficheiro dos dados do coletor.");
		fclose(file);
		exit(1);
	}
	fclose(file);

	printf("%s\n", str_out);
}

void coletordata_read_serial_port(int s_prt, char* dest_str) {
	ssize_t bytes_read = read(s_prt, dest_str, MAXSTRSIZE);
	if (bytes_read > 0) {
		dest_str[bytes_read] = '\0'; // null terminate
	}
}

int coletordata_open_serial_port(const char* serial_port) {
	int s_prt = open(serial_port, O_RDWR); // open: read and write
	if (s_prt == -1) {
		perror("Erro ao abrir porta série");
		exit(1);
	}

	struct termios tty;
	memset(&tty, 0, sizeof(tty));

	if (tcgetattr(s_prt, &tty) != 0) {
		perror("Erro: tcgetattr");
		close(s_prt);
		exit(1);
	}

	// set baud rate
	cfsetospeed(&tty, B9600);
	cfsetispeed(&tty, B9600);

	// set serial port parameters
	tty.c_cflag |= (CLOCAL | CREAD);
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;
	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr(s_prt, TCSANOW, &tty) != 0) {
		perror("Erro: tcsetattr");
		close(s_prt);
		exit(1);
	}

	return s_prt;
}

// Coloca os dados da string lida na estrutura do coletor de dados
int coletordata_parse(ColetorData *col_out, const char *str) {
	int sensor_id, value;
	unsigned int time;
	char type[32], unit[32];
	double valueDouble;

	int ret = sscanf(str, "sensor_id:%d#type:%[^#]#value:%lf#unit:%[^#]#time:%u",
			&sensor_id, type, &valueDouble, unit, &time);
	if (ret != 5) {
		printf("Info: Não foi possível extrair linha, a tentar novamente...\n");
		return 0;
	}
	value = (int) (valueDouble * 100);

	// Apenas copiar dados se não tiver erros
	col_out->sensor_id = sensor_id;
	strcpy(col_out->type, type);
	col_out->value = value;
	strcpy(col_out->unit, unit);
	col_out->time = time;

	// Verificar se as strings foram copiadas corretamente com o strcpy
	assert(strcmp(col_out->type, type) == 0);
	assert(strcmp(col_out->unit, unit) == 0);

	printf("Info: Linha extraída com sucesso!\n");
	return 1;
}

void coletordata_print(ColetorData *col) {
	printf("ColetorData = {\n"
		"  sensor_id: %d\n"
		"  type: %s\n"
		"  value: %d\n"
		"  unit: %s\n"
		"  time: %u\n}\n",
		col->sensor_id, col->type,
		col->value, col->unit, col->time);
}
