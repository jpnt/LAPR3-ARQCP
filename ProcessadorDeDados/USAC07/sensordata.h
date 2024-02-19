#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "circularbuffer.h"
#include "coletordata.h"
#include "configdata.h"

typedef struct {
	int id;
	unsigned int timestamp;
	int timeout;
	int write_counter;
	char type[32];
	char unit[32];
	CircularBuffer* cb;
	int* arr_median;
	unsigned int window_len;
} SensorData;

SensorData* sensordata_create(ConfigData* cfg);
void sensordata_add(SensorData* s, ConfigData* cfg, ColetorData* col);
void sensordata_destroy(SensorData* s);
int sensordata_is_error_state(SensorData* s);
void sensordata_print(SensorData* s);
void sensordata_serialize(SensorData* s, char* srl_info_out);
void sensordata_fwrite_srl(const char* dir, char srl_info[][256], int n);
int sensordata_not_null(SensorData* s);
int sensordata_compute_median(SensorData* s);
void sensordata_bbsort_arr_median(SensorData* s, int n);
SensorData* sensordata_create_test(int id, char* type, char* unit, int buffer_size, 
		int median_size, unsigned int timestamp, int timeout); // for usac07

#endif // !SENSORDATA_H
