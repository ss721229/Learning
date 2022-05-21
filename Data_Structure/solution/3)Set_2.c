#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int elem;
	struct ListNode* next;

}ListNode;

void add(ListNode* p, int e);
void freeAll(ListNode* p);
ListNode* unionSet(ListNode* A, ListNode* B);
ListNode* intersectSet(ListNode* A, ListNode* B);
void print(ListNode* p);

int main() {
	ListNode* Ahead, * Bhead, * Chead, * Dhead, * p;
	int N, e;

	Ahead = (ListNode*)malloc(sizeof(ListNode));
	Bhead = (ListNode*)malloc(sizeof(ListNode));
	Chead = (ListNode*)malloc(sizeof(ListNode));
	Dhead = (ListNode*)malloc(sizeof(ListNode));
	Ahead->next = NULL;
	Bhead->next = NULL;
	Chead->next = NULL;
	Dhead->next = NULL;

	scanf("%d", &N);
	p = Ahead;
	for (int i = 0; i < N; i++) {
		scanf("%d", &e);
		add(p, e);
		p = p->next;
	}

	scanf("%d", &N);
	p = Bhead;
	for (int i = 0; i < N; i++) {
		scanf("%d", &e);
		add(p, e);
		p = p->next;
	}

	Chead = unionSet(Ahead, Bhead);
	Dhead = intersectSet(Ahead, Bhead);
	print(Chead);
	printf("\n");
	print(Dhead);
	
	freeAll(Ahead);
	freeAll(Bhead);
	freeAll(Chead);
	freeAll(Dhead);
	return 0;
}

void add(ListNode* p, int e) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->elem = e;
	node->next = NULL;
	p->next = node;
}

void freeAll(ListNode* p) {
	ListNode* curr1 = p, * curr2 = p;

	while (curr1 != NULL) {
		curr1 = curr1->next;
		free(curr2);
		curr2 = curr1;
	}
}

ListNode* unionSet(ListNode* A, ListNode* B) {
	ListNode* C;
	
	if (A == NULL && B == NULL)
		return NULL;

	C = (ListNode*)malloc(sizeof(ListNode));
	C->next = NULL;

	if (A == NULL) {
		C->elem = B->elem;
		C->next = unionSet(A, B->next);
	}
	else if (B == NULL) {
		C->elem = A->elem;
		C->next = unionSet(A->next, B);
	}
	else
		if (A->elem < B->elem) {
			C->elem = A->elem;
			C->next = unionSet(A->next, B);
		}
		else if (A->elem > B->elem) {
			C->elem = B->elem;
			C->next = unionSet(A, B->next);
		}
		else {
			C->elem = A->elem;
			C->next = unionSet(A->next, B->next);
		}
	return C;
}

ListNode* intersectSet(ListNode* A, ListNode* B) {
	ListNode* C;
	
	if (A == NULL || B == NULL)
		return NULL;

	if (A->elem < B->elem) {
		return intersectSet(A->next, B);
	}
	else if (A->elem > B->elem) {
		return intersectSet(A, B->next);
	}
	else {
		C = (ListNode*)malloc(sizeof(ListNode));
		C->elem = A->elem;
		C->next = intersectSet(A->next, B->next);
		return C;
	}
}

void print(ListNode* p) {
	ListNode* curr = p->next;
	if (curr == NULL) {
		printf(" 0");
		return;
	}
	while (curr != NULL) {
		printf(" %d",curr->elem);
		curr = curr->next;
	}
}