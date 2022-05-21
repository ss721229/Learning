#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int top = -1;
int size;

void push(char stack[], char c);
char pop(char stack[]);
void peek(char stack[]);
void duplicate(char stack[]);
void upRotate(char stack[], int n);
void downRotate(char stack[], int n);
void print(char stack[]);


int main() {
	char* stack, c, enter[15], elem;
	int num, n;

	scanf("%d", &size);
	stack = (char*)malloc(sizeof(char) * size);

	scanf("%d", &num);
	for (int i = 0; i < num; i++) {
		scanf("%s", enter);

		if (strcmp(enter,"PUSH")==0) {

			getchar();
			scanf("%c", &c);

			push(stack, c);
		}
		else if (strcmp(enter, "POP") == 0) {
			elem = pop(stack);
		}
		else if (strcmp(enter, "PEEK") == 0) {
			peek(stack);
		}
		else if (strcmp(enter, "DUP") == 0) {
			duplicate(stack);
		}
		else if (strcmp(enter, "UpR") == 0) {
			scanf("%d", &n);
			upRotate(stack, n);
		}
		else if (strcmp(enter, "DownR") == 0) {
			scanf("%d", &n);
			downRotate(stack, n);
		}
		else if (strcmp(enter, "PRINT") == 0) {
			print(stack);
		}
	}

	free(stack);
	return 0;
}

void push(char stack[], char c) {
	if (top >= size - 1)
		printf("Stack FULL\n");
	else {
		top++;
		stack[top] = c;
	}
}

char pop(char stack[]) {
	if (top == -1) {
		printf("Stack Empty\n");
		return 0;
	}
	else {
		top--;
		return stack[top + 1];
	}
}

void peek(char stack[]) {
	if (top == -1)
		printf("Stack Empty\n");
	else
		printf("%c\n", stack[top]);
}

void duplicate(char stack[]) {
	int elem;
	if(top == -1)
	    printf("Stack Empty\n");
	else if (top >= size - 1)
		printf("Stack FULL\n");
	else {
		elem = pop(stack);

		for (int i = 0; i < 2; i++) {
			push(stack, elem);
		}
	}
}

void upRotate(char stack[], int n) {
	char tmp = stack[top];
	int tmp1 = top;
	if(n<=top+1){
		for (int i = 0; i < n; i++) {
			stack[top] = stack[top - 1];
			top--;
		}
		stack[top + 1] = tmp;
	}
	top = tmp1;
}

void downRotate(char stack[], int n) {
	char tmp = stack[top - n + 1];
	int tmp1 = top;

	if(n<=top+1){
		top = top - n + 1;
		for (int i = 0; i < n; i++) {
			stack[top] = stack[top + 1];
			top++;
		}
		stack[top - 1] = tmp;
	}
	top = tmp1;
}

void print(char stack[]) {
	for (int i = top; i >= 0 ; i--)
		printf("%c", stack[i]);
	printf("\n");
}