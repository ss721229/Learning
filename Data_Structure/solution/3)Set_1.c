#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int elem;
	struct ListNode* next;

}ListNode;

ListNode* getnode(int e);
void add(ListNode** head, int e);
int subset(ListNode* A, ListNode* B);
int member(ListNode* p, int e);
void freeAll(ListNode* p);
void print(ListNode* p);

int main() {
	ListNode* A, * B, *p;
	int N, e;
	A = NULL;
	B = NULL;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &e);
		add(&A, e);
	}


	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &e);
		add(&B, e);
	}
	printf("%d", subset(A, B));

	freeAll(A);
	freeAll(B);

	return 0;
}

ListNode* getnode(int e) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->elem = e;
	node->next = NULL;
	return node;
}
void add(ListNode** head, int e) {
	ListNode* node = getnode(e);
	if (*head == NULL)
		*head = node;
	else {
		ListNode* temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}

int subset(ListNode* A, ListNode* B) {
	ListNode* p;
	if (A == NULL)
		return 0;
	p = A;
	while (1) {
		if (member(B, p->elem))
			if (p->next == NULL)
				return 0;
			else
				p = p->next;
		else {
			return p->elem;
		}
	}

}

int member(ListNode* p, int e) {
	ListNode* q;
	int a;
	if (p == NULL)
		return 0;
	q = p;
	while (1) {
		a = q->elem;
		if (a < e) {
			if (q->next == NULL)
				return 0;
			else
				q = q->next;
		}
		else if (a > e)
			return 0;
		else
			return 1;
	}
}

void freeAll(ListNode* p) {
	ListNode* curr1 = p, * curr2 = p;

	while (curr1 != NULL) {
		curr1 = curr1->next;
		free(curr2);
		curr2 = curr1;
	}
}