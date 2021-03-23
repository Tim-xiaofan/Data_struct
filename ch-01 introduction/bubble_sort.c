/** 20210323 21:32, zyj, GuangDong*/
// bubble_sort.c -- bubble sort algorithm
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 12
#define M 100

/** algorithm implement*/
void bubble_sort(int *a, int n)
{
	int i, j, tmp;
	bool change = true;
	for(i = n - 1; i >= 1 && change; i--)
	{
		change = false;
		for(j = 0; j < i; j++)
		  if(a[j] > a[j + 1])
		  {
			  change = true;
			  tmp = a[j];
			  a[j] = a[j + 1];
			  a[j + 1] = tmp;
		  }
	}
}

void array_show(int *a, int n)
{
	int i;
	for(i = 0; i < n; i++)
	  printf("%d ", a[i]);
	printf("\n");
}

int main()
{
	int i, a[N];

	srand(time(NULL));
	for(i = 0; i < N; i++)
	  a[i] = rand() % M + 1;
	printf("origin array : ");
	array_show(a, N);

	bubble_sort(a, N);
	printf("sorted array : ");
	array_show(a, N);
}
