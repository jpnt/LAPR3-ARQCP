#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int sensor_id;
	char* type;
	char* unit;
	int buffer_len;
	int window_len;
	int timeout;
} ConfigData;

ConfigData* configdata_extract(char* config_file) {
	// sensor_id#type#unit#buffer_len#window_len#timeout
	return NULL; //TODO
}

int main(int argc, char *argv[])
{

	//read from file

	if (argc == 1) {
		printf("Por favor introduza o caminho para o ficheiro dos dados do sensor\n");
		return EXIT_FAILURE;
	}

	printf("%s\n", argv[1]);
	

	FILE* port = fopen(argv[1], "r");
	if (port == NULL) {
		perror("Erro ao abrir porta série");
		return EXIT_FAILURE;
	}

	char buf[256];
	/* char * buf;  */
	if (fgets(buf, sizeof(buf), port) == NULL) {
		perror("Erro ao ler porta série");
		fclose(port);
		return EXIT_FAILURE;
	}

	printf("Received data: %s\n", buf);



	fclose(port);

	// extract config data

	return EXIT_SUCCESS;
}
