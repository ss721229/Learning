#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

void push(int arr[], int e);
void pop(int arr[]);
void print(int arr[], int q);


int main()
{
	int* arr;
	int q, N, elem, front = 0, rear = 0; // q:배열의 크기, N:연산 개수
	char ch; // ch: 함수 선택을 위한 변수

	scanf("%d", &q);
	arr = (int*)malloc(sizeof(int) * q);
	for (int i = 0; i < q; i++)
		arr[i] = 0;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		getchar();
		scanf("%c", &ch);

		if (ch == 'I') {
			rear = (rear + 1) % q;
			if (rear == front) {
				printf("overflow");
				print(arr, q);
				return -1;
			}


			scanf("%d", &elem);

			push(arr + rear, elem);
		}
		else if (ch == 'D') {
			if (rear == front) {
				printf("underflow");
				return -1;
			}

			front = (front + 1) % q;
			pop(arr + front);

		}
		else if (ch == 'P') {
			print(arr, q);
		}
	}
	free(arr);

	return 0;
}

void push(int arr[], int e) {
	*arr = e;
}
void pop(int arr[]) {
	*arr = 0;
}
void print(int arr[], int q) {
	for (int i = 0; i < q; i++)
		printf(" %d", arr[i]);
	printf("\n");
}