#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int coef, exp;
	struct Polynomial* next;
} Polynomial;


void appendTerm(Polynomial* list, int co, int ex);
void print(Polynomial* header);
Polynomial* addPoly(Polynomial* first, Polynomial* second);
void free_all(Polynomial* header);

int main() {
	Polynomial* first_header, * second_header, * a, * b, * c, * p;
	int N, co, ex;
	first_header = (Polynomial*)malloc(sizeof(Polynomial));
	first_header->next = NULL;
	second_header = (Polynomial*)malloc(sizeof(Polynomial));
	second_header->next = NULL;

	a = first_header;
	b = second_header;

	p = first_header;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &co, &ex);
		appendTerm(p, co, ex);
		p = p->next;
	}

	p = second_header;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &co, &ex);
		appendTerm(p, co, ex);
		p = p->next;
	}

	c = addPoly(first_header, second_header);
	print(c);

	free_all(first_header);
	free_all(second_header);
	free_all(c);

	return 0;
}

void appendTerm(Polynomial* list, int co, int ex) {
	Polynomial* node;
	node = (Polynomial*)malloc(sizeof(Polynomial));
	node->coef = co;
	node->exp = ex;
	node->next = NULL;
	list->next = node;
}

void print(Polynomial* header) {
	Polynomial* p = header->next;
	while (p != NULL) {
		printf(" %d %d", p->coef, p->exp);
		p = p->next;
	}
}

Polynomial* addPoly(Polynomial* first, Polynomial* second) {
	Polynomial* result, * curr;
	Polynomial* p = first->next, * q = second->next;

	result = (Polynomial*)malloc(sizeof(Polynomial));
	result->next = NULL;
	curr = result;

	while (p != NULL && q != NULL) {
		if (p->exp > q->exp) {
			appendTerm(curr, p->coef, p->exp);
			p = p->next;
			curr = curr->next;
		}
		else if (p->exp < q->exp) {
			appendTerm(curr, q->coef, q->exp);
			q = q->next;
			curr = curr->next;
		}
		else {
			if (q->coef + p->coef != 0) {
				appendTerm(curr, q->coef + p->coef, p->exp);
				curr = curr->next;
			}
			q = q->next;
			p = p->next;
		}
	}
	while (p != NULL) {
		appendTerm(curr, p->coef, p->exp);
		p = p->next;
		curr = curr->next;
	}

	while (q != NULL) {
		appendTerm(curr, q->coef, q->exp);
		q = q->next;
		curr = curr->next;
	}

	return result;
}

void free_all(Polynomial* header) {
	Polynomial* p = header, * q = header;

	while (p != NULL) {
		p = p->next;
		free(q);
		q = p;
	}

}