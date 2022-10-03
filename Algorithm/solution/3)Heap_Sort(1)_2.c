#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int arr[100], n = 0;

void rBuildHeap(int i);
void buildHeap();
void downHeap(int i);
void printHeap();

int main() {
	// 배열 개수와 값 입력
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);

	rBuildHeap(1);
	printHeap();
	return 0;
}

// 재귀적 구현
void rBuildHeap(int i) {

	if (i > n)
		return;

	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
}

// 비재귀적 구현
void buildHeap() {

	// 배열 개수와 값 입력
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);

	// 바깥쪽 내부노드부터 순서대로 정렬
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
}

void downHeap(int i) {
	int left = 2 * i, right = 2 * i + 1, greater, tmp;
	// 왼쪽 자식이 key 개수를 넘어가면 종료
	if (left > n)
		return;
	
	greater = left;
	
	// 오른쪽 자식이 key 개수를 넘지 않고 왼쪽 key 값보다 크면 greater로 지정
	if (right <= n)
		if (arr[right] > arr[left])
			greater = right;

	// arr[i]가 자식들의 노드보다 클 경우 종료
	if (arr[i] >= arr[greater])
		return;

	// arr[i]가 자식들의 노드보다 작을 경우 swap
	tmp = arr[i];
	arr[i] = arr[greater];
	arr[greater] = tmp;

	downHeap(greater);

}

void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", arr[i]);
	printf("\n");
}