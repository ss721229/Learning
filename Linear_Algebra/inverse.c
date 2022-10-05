#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable:4996)

typedef struct _MATRIX {
	double** m_data;
	int m_size;
}MATRIX;

void initMatrix(MATRIX* A, int n); // 동적배열 생성함수
void deleteMatrix(MATRIX* A); // 동적배열 해제함수
void inputMatrix(MATRIX* A); // 행렬 값 입력함수
void printMatrix(MATRIX matrix); // 행렬 값 출력함수
double determinant(MATRIX matrix); // 행렬식 계산함수
MATRIX transpose(MATRIX matrix); // 전치행렬 계산함수
MATRIX minorMatrix(MATRIX matrix, int col, int row); // 소행렬식 계산함수
MATRIX cofactorMatrix(MATRIX matrix); // 여인자행렬 계산함수
MATRIX adjoint(MATRIX matrix); // 수반행렬 계산함수
MATRIX inverseMatrix(MATRIX matrix); // 역행렬 계산함수

int main()
{
	MATRIX matrix;
	MATRIX inverse;
	int n;
	double det = 0;

	printf("***************************************\n");
	printf("*                                     *\n");
	printf("*            Inverse Matrix           *\n");
	printf("*                                     *\n");
	printf("***************************************\n");

	// 행렬의 크기 입력
	printf("Enter Size of Matrix: ");
	scanf("%d", &n);

	// matrix 구조체와 inverse 구초제를 동적배열로 행렬을 생성
	initMatrix(&matrix, n);
	initMatrix(&inverse, n);

	// matrix 구조체에 값 입력
	inputMatrix(&matrix);

	// matrix 구조체의 행렬식 값을 계산하여 det 변수에 저장
	det = determinant(matrix);

	// matrix 구조체의 역행렬을 계산하여 inverse 구조체에 저장
	inverse = inverseMatrix(matrix);

	// 입력한 행렬의 핵렬식 출력
	printf("\nDeterminant of Enterd Matrix\n");
	printf("Det(A) = %.3lf\n\n", det);

	// 입력한 행렬의 역행렬 출력
	printf("Inverse Matrix = \n");
	printMatrix(inverse);
	printf("\n");

	// matrix 구조체와 inverse 구조체에 할당된 동적배열 해제
	deleteMatrix(&matrix);
	deleteMatrix(&inverse);

	return 0;
}

// 입력 크기에 따라 동적배열 생성
void initMatrix(MATRIX* A, int n) {
	int i = 0;

	A->m_data = (double**)malloc(sizeof(double*) * n);
	for (i = 0; i < n; i++)
		A->m_data[i] = (double*)malloc(sizeof(double) * n);
	A->m_size = n;
}

// 사용하고 난 후 다른 입력을 위해 동적배열을 해제
void deleteMatrix(MATRIX* A) {
	int i = 0;

	for (i = 0; i < A->m_size; i++)
		free(A->m_data[i]);
	free(A->m_data);
}

// 행렬 값을 입력
void inputMatrix(MATRIX* A) {
	int i = 0, j = 0;
	double input = 0;

	printf("\n");
	printf("Enter Value of Matrix\n");
	for (i = 0; i < A->m_size; i++) {
		for (j = 0; j < A->m_size; j++) {
			fflush(stdin);
			printf("%d X %d : ", i + 1, j + 1);
			scanf("%lf", &input);
			A->m_data[i][j] = input;
		}
	}
}

// 행렬 값을 출력
void printMatrix(MATRIX matrix) {
	int i = 0, j = 0;

	for (i = 0; i < matrix.m_size; i++) {
		printf("\t|\t");
		for (j = 0; j < matrix.m_size; j++)
			printf("%.3lf\t", matrix.m_data[i][j]);
		printf("|\n");
	}
}

// 행렬식 계산(크기 관계 X)
double determinant(MATRIX matrix) {
	int i = 0;
	double det = 0;
	int sign = 1;

	// 2X2일 경우 행렬식을 구하는 과정
	if (matrix.m_size == 2) {
		det = matrix.m_data[0][0] * matrix.m_data[1][1] - matrix.m_data[1][0] * matrix.m_data[0][1];
		return det;
	}

	// 3X3 이상일 경우 소행렬식을 이용하여 행렬식을 구하는 과정
	for (i = 0; i < matrix.m_size; i++) {
		MATRIX minor;
		initMatrix(&minor, matrix.m_size);

		minor = minorMatrix(matrix, 0, i);
		det = det + sign * matrix.m_data[i][0] * determinant(minor);
		sign *= -1;
	}
	return det;
}

// 행과 열을 서로 바꾸어 전치행렬 생성
MATRIX transpose(MATRIX matrix) {
	MATRIX result;
	int i = 0, j = 0;

	initMatrix(&result, matrix.m_size);

	for (i = 0; i < matrix.m_size; i++)
		for (j = 0; j < matrix.m_size; j++)
			result.m_data[i][j] = matrix.m_data[j][i];
	return result;
}

// 행과 열의 크기를 각각 1씩 줄인 소행렬식 값 반환
MATRIX minorMatrix(MATRIX matrix, int col, int row) {
	MATRIX result;
	int i = 0, j = 0;
	int rowIndex = 0;
	int colIndex = 0;

	initMatrix(&result, matrix.m_size - 1);
	for (i = 0; i < matrix.m_size; i++) {
		for (j = 0; j < matrix.m_size; j++) {
			if (i != row && j != col) {
				result.m_data[rowIndex][colIndex] = matrix.m_data[i][j];
				colIndex++;
			}
		}
		if (i != row && j != col) {
			colIndex = 0;
			rowIndex++;
		}
	}
	return result;
}

// 여인수 행렬을 계산
MATRIX cofactorMatrix(MATRIX matrix) {
	MATRIX result;
	int i = 0, j = 0;

	initMatrix(&result, matrix.m_size);
	for (i = 0; i < matrix.m_size; i++)
		for (j = 0; j < matrix.m_size; j++)
			result.m_data[j][i] = determinant(minorMatrix(matrix, i, j));
	return result;
}

// 여인수행렬을 전치하여 수반행렬 생성
MATRIX adjoint(MATRIX matrix) {
	MATRIX result;
	MATRIX confactor;
	MATRIX transposed;
	int i = 0, j = 0;
	double ipow = 1;

	initMatrix(&result, matrix.m_size);
	initMatrix(&confactor, matrix.m_size);
	initMatrix(&transposed, matrix.m_size);

	confactor = cofactorMatrix(matrix);
	transposed = transpose(confactor);
	
	for (i = 0; i < matrix.m_size; i++) {
		for (j = 0; j < matrix.m_size; j++) {
			ipow = pow(-1, (i + j));
			result.m_data[i][j] = ipow * transposed.m_data[i][j];
		}
	}
	deleteMatrix(&confactor);
	deleteMatrix(&transposed);

	return result;
}

// 수반행렬을 이용한 최종적인 역행렬 생성
MATRIX inverseMatrix(MATRIX matrix) {
	MATRIX result;
	MATRIX tmp;
	double det;
	int i, j;

	det = determinant(matrix);

	initMatrix(&tmp, matrix.m_size);
	initMatrix(&result, matrix.m_size);

	// 2X2일 경우 역행렬을 구하는 과정
	if (matrix.m_size == 2) {
		tmp.m_data[0][0] = matrix.m_data[1][1];
		tmp.m_data[1][1] = matrix.m_data[0][0];
		tmp.m_data[0][1] = -matrix.m_data[0][1];
		tmp.m_data[1][0] = -matrix.m_data[1][0];

		for (i = 0; i < matrix.m_size; i++)
			for (j = 0; j < matrix.m_size; j++)
				result.m_data[i][j] = (double)((double)1 / det * tmp.m_data[i][j]);
		deleteMatrix(&tmp);

		return result;
	}

	// 3X3 이상인 경우 역행렬을 구하는 과정
	tmp = adjoint(matrix);
	for (i = 0; i < matrix.m_size; i++)
		for (j = 0; j < matrix.m_size; j++)
			result.m_data[i][j] = (double)((double)1 / det * tmp.m_data[i][j]);

	deleteMatrix(&tmp);

	return result;
}