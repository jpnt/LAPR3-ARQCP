#include <stdio.h>
#include "asm.h"

int main() {
	int array[] = {10,20,30,40,50,60,70,80,90,100};
	int length = sizeof(array) / sizeof(*array);
	int read = 6;
	int write = 7;
	int num = 5;
	int vec[num];

	int copied = move_num_vec(array, length, &read, &write, num, vec);

	if (copied) {
		for (int i = 0; i < num; i++) {
			printf("%d ", *(vec+i));
		}
		printf("\nread=%d\twrite=%d\n",read,write);
	} else {
		printf("no copy: invalid values\n");
	}

	return 0;
}
