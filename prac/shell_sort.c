#include <stdio.h>


void show(const int v[],const int n) 
{
    int i = 0;
    for (;i < n; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i ++)
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
                printf("exchange: %dth->%d, %dth->%d (gap:%d)\n", 
                        j, v[j + gap],
                        j + gap, v[j]
                        , gap);
                show(v, n);
            }
}

int main()
{
    int test[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

    shellsort(test, sizeof(test)/sizeof(test[0]));
    printf("After sort:\n");
    show(test, sizeof(test)/sizeof(test[0]));

    return 0;
}
