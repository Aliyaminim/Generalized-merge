#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gen_merge.h"

int main()
{
    int arr[10000];
    int sizes[10000];
    
    int nelts;
    scanf("%d", &nelts);

    for (int i = 0; i < nelts; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < nelts; i++)
        sizes[i] = 4;

    xmsort(arr, sizes, nelts, cmp_int);


    for (int i = 0; i < nelts; i++)
        printf("%d ", arr[i]);

    return 0;
}
