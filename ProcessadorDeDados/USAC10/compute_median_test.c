#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* arr = (int *) malloc(10 * 4);
	arr[0] = 12;

	printf("%ld\n", sizeof(arr)); // address/pointer -> 8 bytes
	printf("%ld\n", sizeof(arr[0])); // int -> 4 bytes

	int n = sizeof(arr) / sizeof(arr[0]); // 8/4 = 2

	printf("%d\n",n);

	return 0;
}
