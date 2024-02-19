#include <stdio.h>
#include "sort.h"

void sort_c(int* arr, int length) {
	int i=0, j, temp;

outer_loop:
	//printf("ol . %d\n", length);
	if (i>=length-1) goto end;
	j = 0;

inner_loop:
	//printf("il . %d\n", length);
	if (j>=length-i-1) goto outer_increment;

	if (*(arr+j) > *(arr+j+1)) goto swap;

	j+=1;
	goto inner_loop;

outer_increment:
	i+=1;
	goto outer_loop;

swap:
	temp = *(arr+j);
	*(arr+j) = *(arr+j+1);
	*(arr+j+1) = temp;
	goto inner_loop;

end:
	return;
}

int main() {
	int arr[] = {2345,2345,223,76989,34,3};
	int length = sizeof(arr) / sizeof(*arr);

	sort(arr, length);

	for (int i = 0; i < length; i++) {
		printf("%d ",*(arr+i));
	}
}
