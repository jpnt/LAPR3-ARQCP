#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char data[] = "sensor_id:10#type:atmospheric_temperature#value:23.40#unit:celsius#time:36026";

	int sensor_id;
	char type[256];
	double value_double;
	int value;
	char unit[256];
	int time;

	if (sscanf(data, "sensor_id:%d#type:%[^#]#value:%lf#unit:%[^#]#time:%d",
				&sensor_id, type, &value_double, unit, &time) != 5) {
		printf("Error parsing sensor data\n");
		return 1;
	}

	value = (int)(value_double*100);

	printf("%s\n", data);
	printf("sensor_id: %d\n", sensor_id);
	printf("type: %s\n", type);
	printf("value: %d\n", value);
	printf("unit: %s\n", unit);
	printf("time: %d\n", time);

	return EXIT_SUCCESS;
}
