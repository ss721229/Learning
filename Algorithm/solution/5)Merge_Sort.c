#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

// mergeSort 함수에서 분할의 개수를 정하기 위한 n
int n;

typedef struct {
	int data;
	struct List* next;
}List;

/*
getNode: 연결리스트의 노드를 받아 연결 후 반환한다.
freeAll: 해당 연결리스트를 해제한다.
printNode: 해당 연결리스트를 출력한다.
size: 해당 연결리스트의 길이를 반환한다.

mergeSort: 합병 정렬을 실시한다 -> 재귀적 방법
merge: 분리된 두 개의 리스트를 오름차순에 맞게 정렬 후 반환한다.
	=> 작은 숫자를 큰 숫자 앞에 붙이는 것을 반복하여 하나가 NULL이 될때까지 반복
partition: 연결리스트를 개수에 맞게 분리한다.
*/
List* getNode(List* header, int value);
void freeAll(List* header);
void printNode(List* header);
int size(List* L);

void mergeSort(List** L);
List* merge(List* L1, List* L2);
List* partition(List* L, int k);


int main() {
	List* header = NULL;
	int value;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &value);
		header = getNode(header, value);
	}
	mergeSort(&header);
	printNode(header);
	freeAll(header);

	return 0;
}

List* getNode(List* header, int value) {
	List* newNode = malloc(sizeof(List));
	newNode->data = value;
	newNode->next = NULL;
	
	if (header == NULL)
		header = newNode;
	else {
		List* p = header;
		while (p->next != NULL)
			p = p->next;
		p->next = newNode;
	}
	return header;
}
void freeAll(List* header) {
	List* p = header, * pnext = header->next;
	while (pnext != NULL) {
		free(p);
		p = pnext;
		pnext = pnext->next;
	}
	free(p);
}
void printNode(List* header) {
	List* p = header;
	while (p != NULL) {
		printf(" %d", p->data);
		p = p->next;
	}
	printf("\n");
}
int size(List* L) {
	List* p = L;
	int cnt = 0;
	while (p != NULL) {
		p = p->next;
		cnt++;
	}
	return cnt;
}


void mergeSort(List** L) {
	List* L1, * L2;
	
	if (size(*L) > 1) {
		n /= 2;
		L1 = *L;
		L2 = partition(*L, n);

		mergeSort(&L1);
		mergeSort(&L2);
		*L = merge(L1, L2);
	}
}
List* merge(List* L1, List* L2) {
	List* p = L1, * q = L2, * pnext = NULL, * qnext = NULL;

	while (L1 != NULL && L2 != NULL) {
		if (p->data < q->data) {
			while (1) {
				pnext = p->next;
				if (pnext == NULL || pnext->data > q->data)
					break;
				p = p->next;
			}
			p->next = L2;
			L2 = L1;
			p = pnext;
			L1 = pnext;
		}
		else {
			while (1) {
				qnext = q->next;
				if (qnext == NULL || qnext->data > p->data)
					break;
				q = q->next;
			}
			q->next = L1;
			L1 = L2;
			q = qnext;
			L2 = qnext;
		}
	}
	if (L2 == NULL)
		return L1;
	else
		return L2;
}
List* partition(List* L, int k) {
	List* L2, * p = L;
	
	for (int i = 0; i < k - 1; i++)
		p = p->next;
	L2 = p -> next;
	p -> next = NULL;

	return L2;
}