#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct{
	char elem;
	struct linkedList* next, * prev;
}linkedList;

void add(linkedList* list, int r, int e) {
	linkedList* p = list, * q, * newData;

	// 새로운 노드에 elem 값 저장
	newData = (linkedList*)malloc(sizeof(linkedList));
	newData->elem = e;

	// 해당 순위로 이동
	for (int i = 0; i < r; i++)
		p = p->next;
	
	// 순서에 맞게 새로운 노드 연결
	q = p->prev;
	newData->next = p;
	newData->prev = q;
	q->next = newData;
	p->prev = newData;
}

void delete(linkedList* list, int r) {
	linkedList* p = list, * q;

	// 해당 순위로 이동
	for (int i = 0; i < r; i++)
		p = p->next;

	// 삭제 노드의 앞 뒤 노드를 서로 연결
	q = p->prev;
	q->next = p->next;
	q = p->next;
	q->prev = p->prev;

	free(p);
}

char get(linkedList* list, int r) {
	linkedList* p = list;
	char e;

	// 해당 순위로 이동
	for (int i = 0; i < r; i++)
		p = p->next;

	// 해당 순위에 있는 elem 반환
	e = p->elem;
	return e;
}

void print(linkedList* list) {
	linkedList* p = list;

	// 다음 노드부터 모든 elem 값 출력
	p = p->next;
	while (p->next != NULL) {
		printf("%c", p->elem);
		p = p->next;
	}
	
	printf("\n");
}
void freeAll(linkedList* list) {
	linkedList* p = list;

	// 연결리스트의 모든 노드 free
	while (p->next != NULL) {
		p = p->next;
		free(p->prev);
	}
	free(p);
	
}

int main() {
	// n: 반복 횟수, r:순위, k: 연결리스트 길이
	// cmd: 커맨드 입력, e: 값
	int n = 0, r = 0, k = 0;
	char cmd, e;
	linkedList* header = NULL, * trailer = NULL;
	header = (linkedList*)malloc(sizeof(linkedList));
	trailer = (linkedList*)malloc(sizeof(linkedList));
	header->elem = NULL;
	trailer->elem = NULL;
	header->next = trailer;
	header->prev = NULL;
	trailer->prev = header;
	trailer->next = NULL;


	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &cmd);
		if (cmd == 'A') {
			k++;
			scanf("%d %c", &r, &e);
			if (r <= 0 || r > k) {
				printf("invalid position\n");
				k--;
				continue;
			}
			add(header, r, e);
		}
		else if (cmd == 'D') {
			scanf("%d", &r);
			if (r <= 0 || r > k) {
				printf("invalid position\n");
				continue;
			}
			k--;
			delete(header, r);
		}
		else if (cmd == 'G') {
			scanf("%d", &r);
			if (r <= 0 || r > k) {
				printf("invalid position\n");
				continue;
			}
			printf("%c", get(header, r));
		}
		else if (cmd == 'P') {
			print(header);
		}
	}
	freeAll(header);
	return 0;
}