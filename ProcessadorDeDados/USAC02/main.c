#include <stdio.h>
#include "enqueue_value.h"

int increment(int value, int length) {
	return (value + 1) % length;
}

void enqueue_value_c(int * array, int length, int * read, int * write, int value) {
	*(array + *write) = value;
	*write = increment(*write, length);
	if (*write == *read) *read = increment(*read, length);
}

int main() {
	int arr[10];
	int length = 10;
	int read = 0;
	int write = 0;

	enqueue_value(arr,length,&read,&write,10);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,20);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	
	enqueue_value(arr,length,&read,&write,30);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,40);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,50);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,60);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,70);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,80);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,90);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,100);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,110);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,120);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,130);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,140);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	enqueue_value(arr,length,&read,&write,150);
	for (int i = 0; i < length; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n read=%d\t write=%d\n", read, write);

	return 0;
}
