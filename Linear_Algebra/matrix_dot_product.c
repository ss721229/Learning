#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

// 두 행렬의 크기와 값을 입력받아 행렬 곱을 계산
void sum_with_two_array();

// 행(n)과 열(m)의 개수에 맞춰 arr을 동적할당 후 반환
int** allocate_array(int** arr, int n, int m);

// 행(n)과 열(m)의 개수에 맞춰 2차원 배열에 값 입력
void enter_array_value(int** arr, int n, int m);

// 두 행렬의 곱을 계산하고 출력
void print_multiply_array(int** arr1, int** arr2, int n1, int m1, int n2, int m2);

// arr 배열 free
void free_all(int** arr, int n);


int main() {
	sum_with_two_array();
	return 0;
}


void sum_with_two_array() {
	int** arr1 = NULL, ** arr2 = NULL, n1, m1, n2, m2;

	printf("행렬곱 계산 프로그램\n\n");

	printf("첫번째 행렬의 크기를 입력하세요\n");
	printf("행의 크기 입력: ");
	scanf("%d", &n1);
	printf("열의 크기 입력: ");
	scanf("%d", &m1);
	printf("\n");

	printf("두번째 행렬의 크기를 입력하세요\n");
	printf("행의 크기 입력: ");
	scanf("%d", &n2);
	printf("열의 크기 입력: ");
	scanf("%d", &m2);
	printf("\n");

	if (m1 != n2) {
		printf("내측의 값이 서로 달라 계산할 수 없습니다.\n");
		return;
	}

	printf("첫번째 행렬을 입력하세요.\n");
	arr1 = allocate_array(arr1, n1, m1);
	enter_array_value(arr1, n1, m1);
	printf("\n");


	printf("두번째 행렬을 입력하세요.\n");
	arr2 = allocate_array(arr2, n2, m2);
	enter_array_value(arr2, n2, m2);
	printf("\n\n");

	printf("행렬곱 결과\n");
	print_multiply_array(arr1, arr2, n1, m1, n2, m2);

	free_all(arr1, n1);
	free_all(arr2, n2);
}

int** allocate_array(int** arr, int n, int m) {
	arr = (int**)malloc(sizeof(int*) * m);
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

void print_multiply_array(int** arr1, int** arr2, int n1, int m1, int n2, int m2) {
	int tmp = 0;

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			for (int k = 0; k < m1; k++)
				tmp += arr1[i][k] * arr2[k][j];
			printf("%6d", tmp);
			tmp = 0;
		}
		printf("\n");
	}
}

void free_all(int** arr, int n) {
	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}