#include <stdio.h>
#include <stdlib.h>

void swap(int a[], int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void myqsort(int v[], int left, int right)
{
    int i, last;
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for(i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    myqsort(v, left, last - 1);
    myqsort(v, last + 1, right);
}

void show(const int v[], int i)
{
    int s = 0;
    for (; s < i; ++s)
        printf("%d ", v[s]);
    printf("\n");
}

static int cmpint(const void *p1, const void *p2)
{
    if (*(int *)p1 == *(int *)p2)
        return 0;
    else if (*(int *)p1 > *(int *)p2)
        return 1;
    else
        return -1;
}

int main()
{
    int ai[] = { 12, 13, 6, 98, 75, 99 };
    
    show(ai, sizeof(ai)/sizeof(ai[0]));  

    qsort(ai, sizeof(ai)/sizeof(ai[0]), sizeof(ai[0]), &cmpint);
    
    printf("After qsort:\n"); 
    show(ai, sizeof(ai)/sizeof(ai[0]));
    return 0;
}
