#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int top = -1;

void push(char stack[], int size, char str);
void pop(char stack[]);

int main() {
	char* stack, str[1000];
	int cnt = 0;
	gets(str);
	stack = (char*)malloc(sizeof(char) * strlen(str));
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == '(' || str[i] == '{' || str[i] == '[' || str[i] == ')' || str[i] == '}' || str[i] == ']')
			cnt++;

	if (cnt % 2 == 0) {
		for (int i = 0; i < strlen(str); i++) {
			if (str[i] == '(' || str[i] == '{' || str[i] == '[')
				push(stack, strlen(str), str[i]);
			else if (str[i] == ')' && stack[top] == '(')
				pop(stack);
			else if (str[i] == '}' && stack[top] == '{')
				pop(stack);
			else if (str[i] == ']' && stack[top] == '[')
				pop(stack);
		}
		if (top == -1)
			printf("OK_%d", cnt);
		else
			printf("Wrong_%d", cnt);
	}
	else
		printf("Wrong_%d", cnt);

	free(stack);

	return 0;
}
void push(char stack[], int size, char str) {
	if (top >= size - 1)
		printf("Stack FULL\n");
	else {
		top++;
		stack[top] = str;
	}
}
void pop(char stack[]) {
	if (top == -1)
		printf("Stack Empty\n");
	else
		top--;
}
