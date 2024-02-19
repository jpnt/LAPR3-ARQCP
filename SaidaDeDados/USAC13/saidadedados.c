#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>

#include "saidadedados.h"

// Converte o número inteiro da string recebida para float e retorna. Exemplo:
// 1,1,soil_humidity,percentage,2160# -> 1,1,soil_humidity,percentage,21.60#
// Caso a string contenha valor em erro, retorna NULL.
// ...error# -> NULL
char* str_int_to_float(const char* str_in) {
	int charCount = 0;
	for (int i = 0; str_in[i] != 0; i++) {
		charCount++;
	}

	// Verificar se está em erro: ...'r'#
	if (str_in[charCount-2] == 'r' || charCount < 8) {
		return NULL;
	}

	char* str_out = (char*) malloc(charCount+2);

	if (str_out == NULL) {
		fprintf(stderr, "Erro: str_in_to_float: "
		"Não foi possível alocar memória para a string.");
		exit(1);
	}

	// Copiar a string
	for (int i = 0; i < charCount; i++) {
		str_out[i] = str_in[i];
	}

	str_out[charCount+1] = 0; // NUL - fim da string

	// Deslocar digitos para a frente:
	// 2160#
	// 21 60#
	// Adicionar ponto
	// 21.60#
	str_out[charCount] = str_in[charCount-1]; // #
	str_out[charCount-1] = str_in[charCount-2]; // first digit
	str_out[charCount-2] = str_in[charCount-3]; // second digit
	str_out[charCount-3] = '.';

	return str_out; // free after use
}

// Processa cada linha do ficheiro usando str_int_to_float
void process_file(const char* input_filename, const char* dir_out) {
	FILE* inputFile = fopen(input_filename, "r");

	if (inputFile == NULL) {
		perror("Error opening file");
		return;
	}

	// Obter o ficheiro de output
	char outputFilePath[256];
	snprintf(outputFilePath, sizeof(outputFilePath), "%s/%s", dir_out, SAIDADEDADOS_FILENAME);

	FILE* outputFile = fopen(outputFilePath, "w");

	if (outputFile == NULL) {
		perror("Error opening file");
		fclose(inputFile);
		return;
	}

	char line[256];

	while(fgets(line, sizeof(line), inputFile) != NULL) {
		int len = strlen(line);
		if (len > 0 && line[len - 1] == '\n') {
			line[len - 1] = '\0';
		}
		
		char* result = str_int_to_float(line);
		if (result != NULL) {
			fprintf(outputFile, "%s\n", result);
			printf("Resultado: %s\n", result);
			free(result);
		}
	}
	fclose(inputFile);
	fclose(outputFile);
}

// Processa cada ficheiro dentro de um diretorio
void process_directory(const char* path_in, const char* path_out) {
	DIR* dir = opendir(path_in);

	if (dir == NULL) {
		perror("Error opening directory");
		return;
	}
	
	struct dirent* entry;

	while((entry = readdir(dir)) != NULL) {
		if(entry->d_type == DT_REG) {
			char filepath[512];

			snprintf(filepath, sizeof(filepath), "%s/%s", path_in, entry->d_name);

			process_file(filepath, path_out);
		}
	}

	closedir(dir);
}

void saida_de_dados(const char* dir_in, const char* dir_out) {
	process_directory(dir_in, dir_out);
}

void saida_de_dados_periodo(const char* dir_in, const char* dir_out, unsigned int periodo) {
	while (1) {
		saida_de_dados(dir_in, dir_out);
		usleep(periodo * 1000); // periodo em milisegundos
	}
}










//
// Versão antiga do saida_de_dados. NAO USAR!
//
void saida_de_dados_deprecated(const char* dir_in, const char* dir_out) {
	DIR *dir;
	struct dirent *entry;

	if((dir = opendir(dir_in)) == NULL) {
		perror("Error opening input directory");
		exit(1);
	}

	// Criar diretorio output se ainda não existir
	struct stat st = {0};
	if (stat(dir_out, &st) == -1) {
		if (mkdir(dir_out, 0755) == -1) {
			perror("Error creating output directory");
			exit(1);
		}
	}

	while((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}

		// File paths para o input e output
		char in_path[512];
		char out_path[512];
		snprintf(in_path, sizeof(in_path), "%s/%s", dir_in, entry->d_name);
		snprintf(out_path, sizeof(out_path), "%s/%s", dir_out, entry->d_name);

		// Abrir ficheiros
		FILE *in_file = fopen(in_path, "r");
		FILE *out_file = fopen(out_path, "w");

		if (in_file == NULL || out_file == NULL) {
			perror("Error opening input or output file");
			exit(1);
		}

		// Ler cada linha do ficheiro input
		char line[256];
		while (fgets(line, sizeof(line), in_file) != NULL) {
			int value;
			if (sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%d#", &value) == 1) {
				// Converter valor inteiro da componente do processador para float
				float float_value = value / 100.0;
				sprintf(line, "%s%.2f#", strtok(line, "#"), float_value); //ERRO: 216021.60 invés de 21.60
			}
			// Escrever a linha modificada
			fputs(line, out_file);
			// Ver se a string foi modificada corretamente
			printf("%s\n", line);
		}

		fclose(in_file);
		fclose(out_file);
	}
	closedir(dir);
}
