#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int dir_exists(const char* dir_name) {
	struct stat sb;
	// S_ISDIR é uma macro da biblioteca stat para verificar se é um diretório
	// stat coloca os dados de dir_name para a struct sb recebida como referencia
	if (stat(dir_name, &sb) == 0 && S_ISDIR(sb.st_mode)) {
		return 1;
	}
	return 0;
}

int dir_create(const char* dir_name) {
	// 0755 representa 111 101 101 em binário
	// o que significa em unix rwx r-x r-x
	// permissões para user, group e others
	if(mkdir(dir_name, 0755) == -1) {
		// caso o mkdir retorne -1 significa que houve um erro
		fprintf(stderr, "Erro: Não foi possível criar o diretório '%s'\n",
				dir_name);
		perror("Error");
		return -1;
	}
	return 0;
}

void dir_configure(const char* dir_name) {
	// Se o diretório ainda não existe tenta cria-lo. Caso falhe sai com erro
	if (!dir_exists(dir_name)) {
		if(dir_create(dir_name) == -1) {
			fprintf(stderr, "Erro: Não foi possível configurar o "
					"diretório '%s'\n", dir_name);
			exit(1);
		}
	}
}
