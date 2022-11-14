#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int list[MAX_SIZE];
int n;

void print_sort(int list[], int n) {

	for (int i = 0; i < n; i++)
		printf("%3d", list[i]);
	printf("\n");

}

void selection_sort(int list[], int n) {

	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) { 

		least = i; 
		for (j = i + 1; j < n; j++) 
			if (list[j] < list[least]) least = j;

		if (i != least)
			SWAP(list[i], list[least], temp);

		printf("%d단계 : ", i + 1);
		print_sort(list, n);
	}

}

int main() {

	n = MAX_SIZE;

	srand(time(NULL)); 

	for (int i = 0; i < n; i++)
		list[i] = rand() % 100; 

	printf("--- 정렬 전 데이터 ---\n");
	print_sort(list, n);

	printf("--- 정렬 후 데이터 ---\n");
	selection_sort(list, n);

}