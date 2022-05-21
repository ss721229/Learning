#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct ListNode {
	char data;
	struct ListNode* prev, * next;
}ListNode;

void add(ListNode* head, ListNode* trailer, int r, char ch);
void print(ListNode* head);
void delete(ListNode* head, ListNode* trailer, int r);
ListNode* get(ListNode* head, ListNode* trailer, int r);
void free_all(ListNode* head, ListNode* trailer);

int main() {
	ListNode* head, * trailer;
	int N, rank;
	char big, ch;

	head = (ListNode*)malloc(sizeof(ListNode));
	trailer = (ListNode*)malloc(sizeof(ListNode));

	head->next = trailer;
	head->prev = NULL;
	trailer->next = NULL;
	trailer->prev = head;

	scanf("%d", &N);
	getchar();

	for (int i = 0; i < N; i++) {

		scanf("%c", &big);
		if (big == 'A') {
			scanf("%d %c", &rank, &ch);
			add(head, trailer, rank, ch);
		}
		if (big == 'P')
			print(head);
		if (big == 'D') {
			scanf("%d", &rank);
			delete(head, trailer, rank);
		}
		if (big == 'G') {
			scanf("%d", &rank);
			if (get(head, trailer, rank) != NULL)
				printf("%c\n", get(head, trailer, rank)->data);
		}

		getchar();
	}

	free_all(head, trailer);

	return 0;
}

void add(ListNode* head, ListNode* trailer, int r, char ch) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode)), * p = head;

	if (r <= 0) {
		printf("invalid position\n");
		return;
	}
	for (int i = 0; i < r; i++) {
		p = p->next;
		if (p == trailer && r - i > 1) {
			printf("invalid position\n");
			return;
		}
	}
	node->data = ch;
	node->next = p;
	node->prev = p->prev;
	p->prev->next = node;
	p->prev = node;
}

void print(ListNode* head) {
	ListNode* curr = head->next;
	while (curr->next != NULL) {
		printf("%c", curr->data);
		curr = curr->next;
	}
	printf("\n");
}

void delete(ListNode* head, ListNode* trailer, int r) {
	ListNode* p = head;

	if (r <= 0) {
		printf("invalid position\n");
		return;
	}
	for (int i = 0; i < r; i++) {
		p = p->next;
		if (p == trailer) {
			printf("invalid position\n");
			return;
		}
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;

	free(p);
}

ListNode* get(ListNode* head, ListNode* trailer, int r) {
	ListNode* p = head;

	if (r <= 0) {
		printf("invalid position\n");
		return NULL;
	}

	for (int i = 0; i < r; i++) {
		p = p->next;
		if (p == trailer) {
			printf("invalid position\n");
			return NULL;
		}
	}
	return p;
}

void free_all(ListNode* head, ListNode* trailer) {
	ListNode* p = head;
	while (p != trailer) {
		p = p->next;
		free(p->prev);
	}
	free(trailer);
}