#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

// 두 행렬을 입력받아 합 or 차를 계산
void cal_with_two_array();

// 행(n)과 열(m)의 개수에 맞춰 arr을 동적할당 후 반환
int** allocate_array(int** arr, int n, int m);

// 행(n)과 열(m)의 개수에 맞춰 2차원 배열에 값 입력
void enter_array_value(int** arr, int n, int m);

// 두 행렬의 합을 계산하고 출력
void print_sum_array(int** arr1, int** arr2, int n, int m);

// 두 행렬의 차을 계산하고 출력
void print_subtract_array(int** arr1, int** arr2, int n, int m);

// arr 배열 free
void free_all(int** arr, int n);


int main() {
	cal_with_two_array();
	return 0;
}


void cal_with_two_array() {
	int** arr1 = NULL, ** arr2 = NULL, n, m, cmd;

	printf("행렬 계산 프로그램\n\n");
	printf("행렬의 크기를 입력하세요\n");
	printf("행의 크기 입력: ");
	scanf("%d", &n);
	printf("열의 크기 입력: ");
	scanf("%d", &m);
	printf("\n");

	printf("계산 방법을 선택하세요.\n");
	printf("1: 합 2: 차\n");
	scanf("%d", &cmd);
	while (cmd != 1 && cmd != 2) {
		printf("올바른 값을 입력해주세요.\n");
		printf("1: 합  2: 차\n");
		scanf("%d", &cmd);
	}
	printf("\n");

	arr1 = allocate_array(arr1, n, m);
	printf("첫번째 행렬을 입력하세요.\n");
	enter_array_value(arr1, n, m);
	printf("\n");

	arr2 = allocate_array(arr2, n, m);
	printf("두번째 행렬을 입력하세요.\n");
	enter_array_value(arr2, n, m);
	printf("\n");




	if (cmd == 1) {
		printf("행렬합 결과\n");
		print_sum_array(arr1, arr2, n, m);
	}
	else {
		printf("행렬차 결과\n");
		print_subtract_array(arr1, arr2, n, m);
	}

	free_all(arr1, n);
	free_all(arr2, n);
}

int** allocate_array(int** arr, int n, int m) {
	arr = (int**)malloc(sizeof(int *) * m);
	for (int i = 0; i < n; i++)
		arr[i] = (int*)malloc(sizeof(int) * n);
	return arr;
}

void enter_array_value(int** arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d X %d 행렬의 값을 입력하세요 : ", i + 1, j + 1);
			scanf("%d", &arr[i][j]);
		}
	}
}

void print_sum_array(int** arr1, int** arr2, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%6d", arr1[i][j] + arr2[i][j]);
		printf("\n");
	}
}

void print_subtract_array(int** arr1, int** arr2, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			printf("%6d", arr1[i][j] - arr2[i][j]);
		printf("\n");
	}
}

void free_all(int** arr, int n) {
	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}