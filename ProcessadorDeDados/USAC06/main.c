#include <stdio.h>
#include "asm.h"

int main() {
	int output;
	int validation;
	char input[] = "sensor_id:8#type:atmospheric_temperature#value:21.60#unit:celsius#time:2470030";

	char* token = "sensor_id";
	validation = extract_token(input,token, &output);
	if (validation == 0) {
		printf("error\n");
		return 0;}
	printf("sensor_id: %d\n",output);

	token = "type";
	validation = extract_token(input,token, &output);
	if (validation == 0) {
		printf("error\n");
		return 0;}
	printf("type: %d\n",output);
	
	token = "value";
	validation = extract_token(input,token, &output);
	if (validation == 0) {
		printf("error\n");
		return 0;}
	printf("value: %d\n",output);
	
	token = "unit";
	validation = extract_token(input,token, &output);
	if (validation == 0) {
		printf("error\n");
		return 0;}
	printf("unit: %d\n",output);

	token = "time";
	validation = extract_token(input,token, &output);
	if (validation == 0) {
		printf("error\n");
		return 0;}
	printf("time: %d\n",output);

	printf("%s\n",input);
}
