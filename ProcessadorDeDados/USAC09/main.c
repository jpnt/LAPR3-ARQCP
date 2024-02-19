#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../USAC07/sensordata.h"
#include "../USAC07/circularbuffer.h"
#include "../USAC07/configdata.h"
#include "../USAC07/coletordata.h"

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

	int result = coletordata_parse(col, strDestino);

	coletordata_print(col);




	coletordata_destroy(col);
	

	return EXIT_SUCCESS;
}
