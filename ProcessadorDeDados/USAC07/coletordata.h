#ifndef COLETORDATA_H
#define COLETORDATA_H

typedef struct {
	char type[32];
	char unit[32];
	int sensor_id;
	int value;
	unsigned int time;
} ColetorData;

ColetorData* coletordata_create(int num_leituras);
void coletordata_destroy(ColetorData *col);
int coletordata_add(ColetorData *col, const char *);
void coletordata_read(char *str_out, int str_size, const char *file_name);
void coletordata_read_serial_port(int serial_port, char* dest_str);
int coletordata_open_serial_port(const char *serial_port);
int coletordata_parse(ColetorData *col_out, const char *str);
void coletordata_print(ColetorData *col);

#endif // !COLETORDATA_H
