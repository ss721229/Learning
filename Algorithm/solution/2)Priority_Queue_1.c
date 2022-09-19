#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int* findMaxNum(int* list, int n) {
	// list[0] ~ list[n] 까지의 값 중에 가장 큰 값의 주소 반환
	int maxNum = list[0], * addr = list;
	for (int* p = list; p < list + n; p++)
		if (*p > maxNum) {
			maxNum = *p;
			addr = p;
		}
	return addr;
}
void swap(int *list, int* maxNum, int n) {
	// 가장 큰 값과 정렬 안된 가장 오른쪽 값과 swap
	int tmp;
	tmp = list[n];
	list[n] = *maxNum;
	*maxNum = tmp;
}

int main() {
	int n, * list, *maxNum;
	scanf("%d", &n);
	list = (int*)malloc(sizeof(int) * n);

	for (int *p = list; p < list + n; p++)
		scanf("%d", p);

	for (int i = 0; i < n; i++) {
		maxNum = findMaxNum(list, n - i);
		swap(list, maxNum, n - i - 1);
	}

	for (int* p = list; p < list + n; p++)
		printf(" %d", *p);
	free(list);
	
	return 0;
}