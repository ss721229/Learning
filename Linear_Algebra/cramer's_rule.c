#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#pragma warning(disable:4996)

#define N 5 // 행과 열의 최댓값

double det(double(*A)[N], int n); // 행렬식을 구하는 재귀호출 함수
void cramer(double(*A)[N], double C[N], int n, int c); // 크래머의 규칙을 이용한 선형방정식의 결과 계산함수

int main()
{
	int i = 0, j = 0;
	int n;
	double A[N][N] = { 0, };
	double C[N] = { 0, };

	printf("**************************************************\n");
	printf("*                                                *\n");
	printf("* Linear Equation Calculation with Cramer's Rule *\n");
	printf("*                                                *\n");
	printf("**************************************************\n");

	// 행렬의 크기 입력
	printf("Enter Size of Matrix: ");
	scanf("%d", &n);
	printf("\n");

	printf("Enter Linear Equations");
	printf("\n");

	// 선형방정식의 수식 입력
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("num:%d, x%d: ", i + 1, j + 1);
			scanf("%lf", &A[i][j]);
		}
	}

	printf("\nEnter Linear Equation's result value");
	printf("\n");

	// 선형방정식의 결과 값 입력
	for (i = 0; i < n; i++) {
		printf("num:%d: ", i + 1);
		scanf("%lf", &C[i]);
	}
	
	// 입력한 행렬 값 출력
	printf("\nEntered Matrix A = \n");
	for (i = 0; i < n; i++) {
		printf("\t|\t");
		for (j = 0; j < n; j++)
			printf("%.f x%d\t", A[i][j], j + 1);
		printf("=\t");
		printf("%.f\t", C[i]);
		printf("|\n");
	}
	printf("\n");

	// 행렬식 값 출력
	printf("Determinant of Entered Linear Equations\n");
	printf("Det(A) = %.f\n\n", det(A, n));

	printf("Answer of Entered Linear Equations");
	for (i = 1; i < n + 1; i++)
		cramer(A, C, n, i);
	printf("\n\n");

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

// 크래머의 규칙을 이용한 선형방정식 결과 값 계산
void cramer(double(*A)[N], double C[N], int n, int c) {
	int i = 0, j = 0;
	double tmp[N][N] = { 0, };

	// 입력받은 행렬 A의 값을 입시 배열에 저장
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			tmp[i][j] = A[i][j];

	// 행렬 A의 값을 넘겨받은 임시 배열 tmp의 각 열에 C의 값을 대입
	for (i = 0; i < n; i++)
		for (j = c - 1; j < c; j++)
			tmp[i][j] = C[i];

	// 선형방정식의 해를 출력한다(부분행렬의 행렬식/전체행렬의 행렬식)
	printf(" x%d = %.f \t", c, (det(tmp, n) / det(A, n)));
}