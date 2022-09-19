#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int arr[100], n = 0;

void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

int main() {
	int key;
	char cmd = '0';

	while (cmd != 'q') {
		scanf("%c", &cmd);

		if (cmd == 'i') {
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
		}
		else if (cmd == 'd') {
			printf("%d\n", removeMax());
		}
		else if (cmd == 'p') {
			printHeap();

		}
	}
	return 0;
}

void insertItem(int key) {
	n += 1;
	arr[n] = key;
	upHeap(n);
}

int removeMax() {
	int key = arr[1];
	arr[1] = arr[n];
	n -= 1;
	downHeap(1);
	return key;
}

void upHeap(int i) {
	int parent = i / 2, tmp;
	
	// i가 1, 즉 root일 때 종료
	if (i == 1)
		return;

	// parent의 key 값이 i의 key 값보다 작으면 swap
	// 그렇지 않으면 종료
	if (arr[parent] < arr[i]) {
		tmp = arr[parent];
		arr[parent] = arr[i];
		arr[i] = tmp;
	}
	else
		return;

	upHeap(parent);

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