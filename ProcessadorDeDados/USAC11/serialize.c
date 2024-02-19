#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../USAC07/sensordata.h"


void writeToFileSerializedSensorInfo(const char* serializedSensorInfo,
		int numLines, const char* filename) {

}

int main(int argc, char *argv[])
{
	const char* serializedSensorInfo[] = {
		"1,1,soil_humidity,percentage,2160#",
		"3,1,atmospheric_humidity,percentage,error#",
	};

	int numLines = sizeof(serializedSensorInfo) / sizeof(serializedSensorInfo[0]);

	const char* filename = "output.txt";

	writeToFileSerializedSensorInfo(serializedSensorInfo, numLines, filename);

	return EXIT_SUCCESS;
}
