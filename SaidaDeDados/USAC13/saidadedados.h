#ifndef SAIDADEDADOS
#define SAIDADEDADOS

#define SAIDADEDADOS_FILENAME "farmcoordinator_data.txt"

void saida_de_dados(const char* dir_in, const char* dir_out);
void saida_de_dados_periodo(const char* dir_in, const char* dir_out, unsigned int periodo);
char* str_int_to_float(const char* str_in);
void process_file(const char* input_filename, const char* dir_out);
void process_directory(const char* path_in, const char* path_out);

#endif // !SAIDADEDADOS
