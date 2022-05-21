#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

int top = -1;

void push(char arr[], char e);
char pop(char arr[]);
int P_operator(char arr[], int i);
int cal(char e, int i);

int main(){
	char oper[100], all[101], e;
	int N, flag = 0;

	scanf("%d", &N);


	for (int j = 0; j < N; j++) {
		scanf("%s", all);
		for (int i = 0; i < strlen(all); i++) {
			e = all[i];

			if (e >= 'A' && e <= 'Z')
				printf("%c", e);
			else if (e == '(')
				push(oper, e);
			else if (e == ')') {
				while (oper[top] != '(')
					printf("%c", pop(oper));
				pop(oper);
			}
			else {
				if ((all[i] == '&' && all[i + 1] == '&') || (all[i] == '|' && all[i + 1] == '|'))
					i++;
				if (cal(e, i) == 1)
					flag = 1;

				if (flag == 1 && i == 2)
					printf("%c", pop(oper));
				else
					while (top != -1 && P_operator(all, i) <= P_operator(oper, top))
						printf("%c", pop(oper));
				if (e == '&' || e == '|')
					push(oper, e);
				push(oper, e);



			}
		}
		while (top != -1)
			printf("%c", pop(oper));
		printf("\n");
	}

	return 0;
}

void push(char arr[], char e) {
	top++;
	arr[top] = e;
}

char pop(char arr[]) {
	top--;
	return arr[top + 1];
}

int P_operator(char arr[], int i) {
	char oper = arr[i];
	char preoper = arr[i - 1];

	if ((oper == '+' || oper == '-') && (preoper == '<' || preoper == '>' || preoper == '|' ||
		preoper == '&' || preoper == '-' || preoper == '+' || preoper == '*' || preoper == '/' || preoper == '!'))
		return 6;
	else if (oper == '(')
		return 0;
	else if (oper == '|')
		return 1;
	else if (oper == '&')
		return 2;
	else if (oper == '<' || oper == '>')
		return 3;
	else if (oper == '-' || oper == '+')
		return 4;
	else if (oper == '/' || oper == '*')
		return 5;
	else if (oper == '!')
		return 6;
}
int cal(char e, int i) {
	if (top == -1 && i == 0 && (e == '+' || e == '-'))
		return 1;
	else
		return 0;
}