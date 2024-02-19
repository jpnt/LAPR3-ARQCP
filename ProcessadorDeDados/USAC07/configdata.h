#ifndef CONFIGDATA_H
#define CONFIGDATA_H

typedef struct {
	char type[32];
	char unit[32];
	int sensor_id;
	unsigned int buffer_len;
	unsigned int window_len;
	unsigned int timeout;
	unsigned int num_lines;
} ConfigData;

int count_lines(const char *file_name);
ConfigData* configdata_create(const char *file_name);
void configdata_destroy(ConfigData *cfg);
int configdata_idx_sensor_id(ConfigData *cfg, int sensor_id);
void configdata_print(ConfigData *cfg);

#endif // !CONFIGDATA_H 
