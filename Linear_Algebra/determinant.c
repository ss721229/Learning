#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#pragma warning(disable:4996)

#define N 4 // 행과 열의 최댓값

double det(double(*A)[N], int n); // 행렬식을 구하는 재귀호출 함수

int main()
{
	int i = 0, j = 0;
	int n;
	double A[N][N] = { 0, };

	printf("***************************************\n");
	printf("*                                     *\n");
	printf("*        Calculate Determinant        *\n");
	printf("*                                     *\n");
	printf("***************************************\n");

	// 행렬의 크기 입력
	printf("Enter Size of Matrix: ");
	scanf("%d", &n);
	printf("\n");

	printf("Enter value of Matrix");
	printf("\n");

	// 각각의 행렬 값 입력
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d X %d: ", i + 1, j + 1);
			scanf("%lf", &A[i][j]);
		}
	}

	// 입력한 행렬 값 출력
	printf("\nEntered Matrix A = \n");
	for (i = 0; i < n; i++) {
		printf("\t|\t");
		for (j = 0; j < n; j++)
			printf("%.f\t", A[i][j]);
		printf("|\n");
	}
	printf("\n");

	// 행렬식 값 출력
	printf("Determinant of Entered Matrix\n");
	printf("Det(A) = %.f\n\n", det(A, n));

	return 0;
}

// 행렬식 값 계산 함수
double det(double(*A)[N], int n) {
	int i, j, k, y;
	double det_a = 0;
	double tmp[N][N];

	// 알고리즘
	if (n != 1) {
		for (i = 0; i < n; i++) {
			for (j = 1; j < n; j++) {
				y = 0;
				// 소행렬식을 구하기 위해 각 행렬의 원소들을 재배치
				for (k = 0; k < n; k++)
					if (k != i)
						tmp[j - 1][y++] = *(A[0] + j * N + k);
			}
			// 소행렬식들의 전체 합을 구하는 과정
			det_a = det_a + *(A[0] + i) * (pow(-1, i)) * det(tmp, n - 1);
		}
		return det_a;
	}
	else
		return *A[0];

}