#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

typedef struct {
	int elem;
	struct Deque* next, * prev;
}Node;

typedef struct {
	Node* front, * rear;
}Deque;

void add_front(Deque* deque, int X); // 맨 앞에 원소 추가
void add_rear(Deque* deque, int X); // 맨 뒤에 원소 추가
int delete_front(Deque* deque); // 맨 앞 원소 제거
int delete_rear(Deque* deque); // 맨 뒤 원소 제거
int underflow_check(Deque* deque); // underflow인지 확인
void print(Deque* deque); // 모든 원소 출력
void free_all(Deque* deque); // 모든 원소 free

int main()
{
	// deque의 front, prev 구조체 변수
	// N: 연산 개수, num: 입력받을 원소, elem: pop 후에 저장할 변수, underflowFlag: underflow인지 확인
	// ch: 연산 선택 문자열
	Deque* deque;
	int N, num, elem, underflowFlag;
	char ch[3];

	deque = (Deque*)malloc(sizeof(Deque));
	deque->front = NULL;
	deque->rear = NULL;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%s", ch);

		if (strcmp(ch, "AF") == 0) {
			scanf("%d", &num);
			add_front(deque, num);
		}
		else if (strcmp(ch, "AR") == 0) {
			scanf("%d", &num);
			add_rear(deque, num);
		}
		else if (strcmp(ch, "DF") == 0) {
			if (!underflow_check(deque)) // underflow일 경우 프로그램 종료
				return 0;
			elem = delete_front(deque);
		}
		else if (strcmp(ch, "DR") == 0) {
			if (!underflow_check(deque))  // underflow일 경우 프로그램 종료
				return 0;
			elem = delete_rear(deque);
		}
		else if (strcmp(ch, "P") == 0) {
			print(deque);
		}
	}

	free_all(deque);

	return 0;
}

void add_front(Deque* deque, int X) {
	Node* node = (Node *)malloc(sizeof(Node));
	node->elem = X;

	if (deque->front == NULL && deque->rear == NULL) { // 연결리스트에 원소가 없을 때
		deque->front = node;
		deque->rear = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else{ // 연결리스트에 원소가 있을 때
		node->prev = NULL;
		node->next = deque->front;
		deque->front->prev = node;
		deque->front = node;
	}
}

void add_rear(Deque* deque, int X) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->elem = X;

	if (deque->front == NULL && deque->rear == NULL) { // 연결리스트에 원소가 없을 때
		deque->front = node;
		deque->rear = node;
		node->prev = NULL;
		node->next = NULL;
	}
	else { // 연결리스트에 원소가 있을 때
		node->prev = deque->rear;
		node->next = NULL;
		deque->rear->next = node;
		deque->rear = node;

	}
}
int delete_front(Deque* deque) {
	int elem;

	if (deque->front->prev == NULL && deque->front->next == NULL) { // 노드가 1개일 때
		elem = deque->front->elem;
		free(deque->front);
		deque->front = NULL;
		deque->rear = NULL;
	}
	else { // 노드가 2개 이상일 때
		Node* p = deque->front->next;

		elem = deque->front->elem;
		p->prev = NULL;
		free(deque->front);
		deque->front = p;
	}
	return elem;

}
int delete_rear(Deque* deque) {
	int elem;

	if (deque->front->prev == NULL && deque->front->next == NULL) { // 노드가 1개일 때
		elem = deque->rear->elem;
		free(deque->front);
		deque->front = NULL;
		deque->rear = NULL;
	}
	else { // 노드가 2개 이상일 때
		Node* p = deque->rear->prev;

		elem = deque->rear->elem;
		p->next = NULL;
		free(deque->rear);
		deque->rear = p;
	}
	return elem;
}

int underflow_check(Deque* deque) {
	if (deque->front == NULL && deque->rear == NULL) { // underflow check
		printf("underflow");
		return 0;
	}
	else
		return 1;
}

void print(Deque* deque) { // 연결리스트의 원소 모두 출력
	Node* p = deque->front;
	while (1) {
		printf(" %d", p->elem);
		if (p == deque->rear)
			break;
		p = p->next;
	}
	printf("\n");
}

void free_all(Deque* deque) { // 노드 free
	Node* p = deque->front, * pnext;
	while (p != NULL) {
		pnext = p->next;
		free(p);
		p = pnext;
	}
}