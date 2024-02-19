#include <stdio.h>
#include "asm.h"

int main() {
	int output;
	char input[] = "sensor_id:8#type:atmospheric_temperature#value:21.60#unit:celsius#time:2470030";

	char* token = "sensor_id";
	extract_token(input,token, &output);
	printf("sensor_id: %d\n",output);

	token = "type";
	extract_token(input,token, &output);
	printf("type: %d\n",output);

	token = "value";
	extract_token(input,token, &output);
	printf("value: %d\n",output);

	token = "unit";
	extract_token(input,token, &output);
	printf("unit: %d\n",output);

	token = "time";
	extract_token(input,token, &output);
	printf("time: %d\n",output);

	printf("%s\n",input);
}
