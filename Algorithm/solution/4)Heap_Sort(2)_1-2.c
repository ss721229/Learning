#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int H[100], n;

/*
inPlaceHeapSort: 무작위로 들어있는 키 값을 오름차순으로 정렬한다.
buildHeap: 키 값이 들어있는 배열을 힙으로 만든다.
downHeapForSort: 제자리 힙정렬을 위한 다운힙
downHeap: 상향식(최대힙) 정렬을 위한 다운힙
printArray: 순차힙(배열)을 출력한다.
*/
void inPlaceHeapSort();
void buildHeap();
void downHeapForSort(int i, int last);
void downHeap(int i);
void printArray();

int main(void) {
	// 키의 개수와 키 값들을 입력받은 후 힙정렬을 진행 및 출력한다.

	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		scanf("%d", &H[i]);

	inPlaceHeapSort();
	printArray();
	return 0;
}

void inPlaceHeapSort() {
	int tmp, m = n / 2;

	buildHeap();

	for (int i = 0; i < n; i++) {
		tmp = H[1];
		H[1] = H[n - i];
		H[n - i] = tmp;
		downHeapForSort(1, n - i - 1);
	}


}
void buildHeap() {
	int m = n / 2;
	for (int i = m; i >= 1; i--)
		downHeap(i);
}
void downHeapForSort(int i, int last) {
	int left = i * 2, right = i * 2 + 1, greater, tmp;

	if (left > last)
		return;

	greater = left;

	if (right <= last)
		if (H[right] > H[left])
			greater = right;

	if (H[i] >= H[greater])
		return;

	tmp = H[greater];
	H[greater] = H[i];
	H[i] = tmp;

	downHeapForSort(greater, last);
}
void downHeap(int i) {
	int left = i * 2, right = i * 2 + 1, greater, tmp;

	if (left > n)
		return;

	greater = left;

	if (right <= n)
		if (H[right] > H[left])
			greater = right;

	if (H[i] >= H[greater])
		return;

	tmp = H[greater];
	H[greater] = H[i];
	H[i] = tmp;

	downHeap(greater);
}
void printArray() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
}