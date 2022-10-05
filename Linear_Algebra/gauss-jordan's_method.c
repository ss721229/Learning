#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#pragma warning(disable:4996)

#define MAX 5 // 행과 열의 최댓값

// 선형방정식의 행렬 배열구조체 선언
typedef struct _matrix {
	double a[MAX][MAX];
}matrix;

// 선형방정식 해의 행별 배열구조체 선언
typedef struct _column{
	double c[MAX];
}column;


// True, False 구조체 선언
typedef enum {
	E_FALSE, E_TRUE
}E_BOOL;

void printOut(matrix a, column c, int n); // 연산 결과 출력함수
void gauss(matrix a, column c, int n); // 가우스 소거법 계산함수
void backSub(matrix a, column c, int n); // 역대입법 계산함수

int main()
{
	int i = 0, j = 0;
	int n;

	matrix a;
	column c;

	printf("********************************************************\n");
	printf("*                                                      *\n");
	printf("* 가우스-조단 소거법을 이용한 선형방정식 계산 프로그램 *\n");
	printf("*                                                      *\n");
	printf("********************************************************\n");

	// 행렬(선형방정식의 차수)의 크기 값 입력
	printf("선형방정식의 최대 차수를 입력하세요: ");
	scanf("%d", &n);
	printf("\n");

	// 선형방정식의 수식을 입력(A)
	printf("선형방정식의 수식을 입력하세요. \n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%d 번째 선형방정식 x%d의 값: ", i + 1, j + 1);
			scanf("%lf", &a.a[i][j]);
		}
	}

	// 선형방정식의 결과 값을 입력(C)
	printf("\n선형방정식의 결과 값을 입력하세요. \n");
	for (i = 0; i < n; i++) {
		printf("%d 번째 선형방정식의 결과 값: ", i + 1);
		scanf("%lf", &c.c[i]);
	}
	printf("\n");

	gauss(a, c, n);
	return 0;
}

// 연산 결과를 출력
void printOut(matrix a, column c, int n) {
	int i = 0, j = 0;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%+.1f\t", a.a[i][j]);
		printf("x%d", i + 1);
		printf("%+.1f \n", c.c[i]);
	}
	printf("\n");
}

// 입력받은 선형방정식을 가우스 소거법으로 계산
void gauss(matrix a, column c, int n) {
	E_BOOL error;
	int i = 0, j = 0, k = 0, l = 0;
	double multi = 0, tmp = 0;

	printf("\n 가우스-조단소거법 풀이 과정: \n");
	printf("**************************************** \n\n");

	error = E_FALSE;
	k = 0;

	while (k < n && error != E_TRUE) {
		l = k;
		for (j = k + 1; j < n; j++) {
			if (fabs(a.a[j][k] > fabs(a.a[l][k])))
				l = j;
			
			for (j = k; j < n; j++) {
				tmp = a.a[k][j];
				a.a[k][j] = a.a[l][j];
				a.a[l][j] = tmp;
			}
			tmp = c.c[k];
			c.c[k] = c.c[l];
			c.c[l] = tmp;
			if (a.a[k][k] != 0) {
				for (j = k + 1; j < n; j++) {
					multi = -1 * a.a[j][k] / a.a[k][k];
					for (i = k; i < n; i++)
						if (multi != 0)
							a.a[j][i] = a.a[j][i] + multi * a.a[k][i];
					c.c[j] += multi * c.c[k];

					printOut(a, c, n);
				}
			}
			else
				error = E_TRUE;
		}
		k += 1;
	}
	if (error == E_TRUE)
		printf("Trap condition....");
	printOut(a, c, n);
	printf("******************************** \n\n");
	backSub(a, c, n);
}

// 역대입법 계산함수 
void backSub(matrix a, column c, int n) {
	int i = 0, j = 0, k = 0;
	float sum;
	column mat = { 0, };

	printf(" a[n, n] = %.f\n\n", a.a[n - 1][n - 1]);

	if (fabs(a.a[n - 1][n - 1]) == 0 || fabs(a.a[n - 1][n - 1]) < 1 / 1000000)
		printf("This matrix is singular, does not hava unique solution \n\n");
	else {
		mat.c[n - 1] = c.c[n - 1] / a.a[n - 1][n - 1];

		for (i = n - 2; i > -1; i--) {
			sum = 0.0f;
			for (j = n - 1; j > i; j--)
				sum += a.a[i][j] * mat.c[j];

			if (fabs(a.a[n - 1][n - 1]) == 0 || fabs(a.a[n - 1][n - 1]) < 1 / 1000000)
				printf("This matrix is singular, does not hava unique solution \n\n");
			else
				mat.c[i] = (c.c[i] - sum) / a.a[i][i];
		}
		printf("입력한 선형방정식의 해답\n");
		for (k = 0; k < n; k++) {
			printf("x%d = ", k + 1);
			printf("%.lf \t", mat.c[k]);
		}
		printf("\n\n");
	}
}