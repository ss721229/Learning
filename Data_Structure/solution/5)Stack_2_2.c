#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

int top = -1;

void push(int arr[], char e);
int pop(int arr[]);
int oper(char e, int a, int b);

int main() {
	char arr[101];
	int N, cal[10], a, b;

	scanf("%d", &N);
	
	for (int j = 0; j < N; j++) {
		scanf("%s", arr);
		for (int i = 0; i < strlen(arr); i++) {
			if (arr[i] >= '0' && arr[i] <= '9')
				push(cal, arr[i] - '0');
			else {
				a = pop(cal);
				b = pop(cal);
				push(cal, oper(arr[i], a, b));
			}
				
		}
		printf("%d\n", pop(cal));
	}
	return 0;
}

void push(int arr[], char e) {
	top++;
	arr[top] = e;
}

int pop(int arr[]) {
	top--;
	return arr[top + 1];
}

int oper(char e, int a, int b) {
	int k;
	if (e == '*')
		return a * b;
	else if (e == '/')
		return b / a;
	else if (e == '-')
		return b - a;
	else if (e == '+')
		return a + b;
}