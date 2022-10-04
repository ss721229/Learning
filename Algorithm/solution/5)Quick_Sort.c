#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct {
	int a;
	int b;
}Index;

/*
findPivot: 무작위로 피벗의 인덱스를 설정하여 반환한다.
inPlaceQuickSort: 부리스트의 퀵정렬 진행
	=> 피벗 원소를 맨 뒤에 숨기고 정렬을 한 후에 자리에 다시 배치
inPlacePartition: 부리스트로 나눠 퀵정렬을 진행할 수 있도록 재귀적으로 진행
*/
int findPivot(int* arr, int l, int r);
void inPlaceQuickSort(int* L, int l, int r);
Index inPlacePartition(int* L, int l, int r, int k);

int main() {
	int n;
	int* arr;

	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	inPlaceQuickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	free(arr);
	return 0;
}
int findPivot(int* arr, int l, int r) {
	// l ~ r 사이의 난수 반환
	srand(time(NULL));
	int num = rand() % (r - l + 1) + l;
	return num;
}


Index inPlacePartition(int* L, int l, int r, int k) {
	Index ab;
	int p = L[k];
	int tmp, i, j;
	tmp = L[k];
	L[k] = L[r];
	L[r] = tmp;

	i = l;
	j = r - 1;

	while (i <= j) {
		while (i <= j && L[i] <= p)
			i += 1;
		while (j >= i && L[j] >= p)
			j -= 1;
		if (i < j) {
			tmp = L[i];
			L[i] = L[j];
			L[j] = tmp;
		}
	}
	tmp = L[i];
	L[i] = L[r];
	L[r] = tmp;
	ab.a = i;
	while (p == L[i])
		i++;
	ab.b = i - 1;
	return ab;


}
void inPlaceQuickSort(int* L, int l, int r) {
	if (l >= r)
		return;
	Index ab;
	int k = findPivot(L, l, r);
	ab = inPlacePartition(L, l, r, k);
	inPlaceQuickSort(L, l, ab.a - 1);
	inPlaceQuickSort(L, ab.b + 1, r);
}