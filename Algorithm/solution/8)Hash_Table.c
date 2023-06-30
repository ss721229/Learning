#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int key;
	struct Node* next;
}Node;

int hash(int x, int M);
void insertItem(int x, int M);
int searchItem(int x, int M);
int deleteItem(int x, int M);
void print(int M);
void freeAll(int M);

Node** hashTable;

int main() {
	int M, x, k, rank;
	char cmd = ' ';

	scanf("%d", &M);

	hashTable = (Node**)malloc(sizeof(Node*) * M);

	for (int i = 0; i < M; i++) {
		hashTable[i] = malloc(sizeof(Node));
		hashTable[i]->next = NULL;
	}

	while (cmd != 'e') {
		scanf("%c", &cmd);

		if (cmd == 'i') {
			scanf("%d", &x);
			insertItem(x, M);
			getchar();
		}
		else if (cmd == 's') {
			scanf("%d", &x);
			getchar();
			rank = searchItem(x, M);
			printf("%d\n", rank);
			
		}
		else if (cmd == 'd') {
			scanf("%d", &x);
			getchar();
			rank = deleteItem(x, M);
			printf("%d\n", rank);
			
		}
		else if (cmd == 'p') {
			print(M);
		}
	}
	return 0;
}

int hash(int x, int M) {
	return x % M;
}

void insertItem(int x, int M) {
	int k = hash(x, M);
	
	Node* newNode = malloc(sizeof(Node));

	newNode->key = x;
	newNode->next = hashTable[k]->next;
	hashTable[k]->next = newNode;
}

int searchItem(int x, int M) {
	int k = hash(x, M);
	int rank = 0, flag = 0;
	Node* p = hashTable[k];

	while (p->next != NULL) {
		p = p->next;
		rank++;
		if (p->key == x) {
			flag = 1;
			break;
		}
	}
	if (flag)
		return rank;
	else
		return 0;
}

int deleteItem(int x, int M) {
	int k = hash(x, M);
	int rank = searchItem(x, M);
	Node* p = hashTable[k];
	Node* delNode;

	if (!rank)
		return 0;

	for (int i = 0; i < rank - 1; i++)
		p = p->next;
	delNode = p->next;

	p->next = delNode->next;
	free(delNode);

	return rank;
}

void print(int M) {
	Node* p;
	for (int i = 0; i < M; i++) {
		p = hashTable[i]->next;
		while (p != NULL) {
			printf(" %d", p->key);
			p = p->next;
		}
	}
	printf("\n");
}