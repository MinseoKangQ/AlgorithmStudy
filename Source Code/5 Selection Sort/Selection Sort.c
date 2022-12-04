// 선택 정렬
// 가장 작은 값을 찾아서 앞에서부터 정렬

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

int list[MAX_SIZE];
int n;

void selection_sort(int list[], int n) {
    
    int i, j, least, temp;
    for (i = 0; i< n - 1; i++) {
        least = i; // 초기에 0번째가 least index라고 가정
        for (j = i + 1; j < n; j++)
            if(list[j] < list[least]) least = j; // 교환
        SWAP(list[i], list[least], temp);
        printf("%d 단계 : ", i+1);
        for (int k = 0; k < n; k++)
            printf("%d ", list[k]);
        printf("\n");
    }
    
}

int main() {
    
    int n;
    n = MAX_SIZE;
    srand(time(NULL));

    for (int i = 0; i < n; i++)
        list[i] = rand()%100;
    
    printf("초기 난수 발생 결과 : ");
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    
    selection_sort(list, n);
    
    printf("선택 정렬 수행 결과 : ");
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
    
    return 0;
    
}
