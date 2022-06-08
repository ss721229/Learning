#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct { // 이진트리 구조체
	int data;
	struct BinaryTree* right,* left;
}BinaryTree;

void insert(BinaryTree* tree, int m, int k); // 이진트리 자식노드 삽입 함수
void searchNumAndInsert(BinaryTree* tree, int n, int m, int k); // data가 n인 경우에 insert를 해준다.
void freeAll(BinaryTree* tree); // 트리 free

int main() {
	// tree: 트리의 루트노드, root: 루트노드를 가리키는 포인터, tmp: 트리의 노드를 저장할 임시 변수
	// sizeOfTree: 입력받을 노드의 수, searchCnt: 탐색 횟수, n: 부모노드 데이터, m: left 자식노드 데이터, k: right 자식노드 데이터 
	// LR: 탐색방법을 저장할 리스트
	BinaryTree* tree = NULL, * root = NULL, * tmp = NULL;
	int sizeOfTree = 0, searchCnt = 0, n = 0, m = 0, k = 0;
	char LR[101];

	scanf("%d", &sizeOfTree); // 첫번째 입력은 루트노드를 생성하고 root와 연결시킴
	scanf("%d %d %d", &n, &m, &k);
	tree = (BinaryTree*)malloc(sizeof(BinaryTree));
	root = tree;
	tree->data = n;
	insert(tree, m, k);

	for (int i = 0; i < sizeOfTree - 1; i++) { // n, m, k를 입력받고 삽입 함수 실행
		scanf("%d %d %d", &n, &m, &k);
		searchNumAndInsert(tree, n, m, k);
	}

	scanf("%d", &searchCnt); // 탐색 횟수 입력
	// 루트노드부터 시작해서 L이면 왼쪽, R이면 오른쪽으로 이동하면서 데이터 출력
	for (int i = 0; i < searchCnt; i++) {
		scanf("%s", LR);
		tmp = root;
		printf("%d", tmp->data);
		for (int j = 0; j < strlen(LR); j++) {
			if (LR[j] == 'R') {
				tmp = tmp->right;
				printf(" %d", tmp->data);
			}
			else if (LR[j] == 'L') {
				tmp = tmp->left;
				printf(" %d", tmp->data);
			}
		}
		printf("\n");
	}

	freeAll(root); // 모든 노드 free

	return 0;
}

void insert(BinaryTree* tree, int m, int k) {
	BinaryTree* tmp1 = NULL, * tmp = NULL;

	if (m != 0) { // 데이터가 0일 경우 삽입하지 않고 NULL을 넣음
		tree->left = (BinaryTree*)malloc(sizeof(BinaryTree));
		tmp = tree->left;
		tmp->data = m;
		tmp->left = NULL;
		tmp->right = NULL;
	}
	else
		tree->left = NULL;

	if (k != 0) { // 데이터가 0일 경우 삽입하지 않고 NULL을 넣음
		tree->right = (BinaryTree*)malloc(sizeof(BinaryTree));
		tmp1 = tree->right;
		tmp1->data = k;
		tmp1->left = NULL;
		tmp1->right = NULL;
	}
	else
		tree->right = NULL;
}

void searchNumAndInsert(BinaryTree* tree, int n, int m, int k) {
	if (tree) { // 순회하면서 해당 데이터를 찾으면 insert 함수 실행
		if (tree->data == n) {
			insert(tree, m, k);
			return;
		}
		searchNumAndInsert(tree->left, n, m, k);
		searchNumAndInsert(tree->right, n, m, k);
	}
}
void freeAll(BinaryTree* tree) {
	if (tree) { // 후위순회하면서 모든 데이터 free
		freeAll(tree->left);
		freeAll(tree->right);
		free(tree);
	}
}
