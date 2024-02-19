#include <stdio.h>
#include "mediana.h"
#include "../USAC04/sort.h"

/* int mediana_c(int* ptr, int num) { */
/*     sort(ptr, num); */
/*     num /= 2; */
/*     return *(ptr+num); */
/* } */

int main() {

    int vec[] = {3,2,1,4,5};
    int num = sizeof(vec)/sizeof(vec[0]);

    int *ptr = vec;

    int median = mediana(ptr, num);
    printf("%d\n", median);

    return 0;
}
