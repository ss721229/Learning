#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct{
	struct Node* lChild;
	struct Node* rChild;
	struct Node* parent;
	int key;
}Node;

Node* root;

int findElement(int k);
void insertItem(int k);
Node* treeSearch(int k);
int removeElement(int k);
int isExternal(Node* w);
int isInternal(Node* w);
Node* inOrderSucc(Node* w);
void expandExternal(Node* w);
Node* sibling(Node* w);
void reduceExternal(Node* w);
void print(Node* T);
void freeAll(Node* T);

int main() {
	char cmd = ' ';
	int k, t;

	root = NULL;

	while (cmd != 'q') {
		
		scanf("%c", &cmd);
		if (cmd == 'i') {
			scanf("%d", &k);
			getchar();
			insertItem(k);
		}
		else if (cmd == 'd') {
			scanf("%d", &k);
			getchar();

			t = removeElement(k);
			if (t == -1)
				printf("X\n");
			else
				printf("%d\n", t);
		}
		else if (cmd == 's') {
			scanf("%d", &k);
			getchar();
			t = findElement(k);
			if (t == -1)
				printf("X\n");
			else
				printf("%d\n", t);
		}
		else if (cmd == 'p') {
			print(root);
			printf("\n");
		}
	}
	freeAll(root);
	return 0;
}
int findElement(int k) {
	Node* tmp = treeSearch(k);
	if (isInternal(tmp))
		return k;
	else
		return -1;
}
void insertItem(int k) {
	Node* tmp = treeSearch(k);
	
	if (tmp == root) {
		tmp = (Node*)malloc(sizeof(Node));
		tmp->key = k;
		tmp->parent = NULL;
		expandExternal(tmp);
		root = tmp;
	}
	else if (isExternal(tmp)) {
		Node* tmp_parent = tmp->parent;
		tmp->key = k;
		tmp->parent = tmp_parent;
		expandExternal(tmp);
		if (tmp_parent->key > k)
			tmp_parent->lChild = tmp;
		else
			tmp_parent->rChild = tmp;
	}
}
Node* treeSearch(int k) {
	// 키가 k인 노드가 없으면 위치할 외부 노드 반환
	Node* tmp = root;
	if (tmp == NULL) // tmp == root
		return tmp;

	while (isInternal(tmp)) {
		if (k == tmp->key)
			return tmp;
		else if (k < tmp->key)
			tmp = tmp->lChild;
		else
			tmp = tmp->rChild;
	}
	return tmp;
}
int removeElement(int k) {
	Node* tmp = treeSearch(k);

	if (isExternal(tmp))
		return -1;
	int e = tmp->key;
	Node* z = tmp->lChild;
	Node* y;

	if (isInternal(z))
		z = tmp->rChild;
	
	if (isExternal(z))
		reduceExternal(z);
	else {
		y = inOrderSucc(tmp);
		z = y->lChild;
		tmp->key = y->key;
		reduceExternal(z);
	}
	return e;
}

Node* inOrderSucc(Node* w) {
	Node* tmp = w->rChild;
	while (isInternal(tmp->lChild))
		tmp = tmp->lChild;
	return tmp;
}

int isExternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL)
		return 1;
	else
		return 0;
} 
int isInternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL)
		return 0;
	else
		return 1;
}

void expandExternal(Node* w) {
	Node* r = (Node*)malloc(sizeof(Node));
	Node* l = (Node*)malloc(sizeof(Node));
	w->lChild = l;
	w->rChild = r;
	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
}

void reduceExternal(Node* w) {
	if (w == NULL)
		return;
	
	Node* z = w->parent;
	Node* zs = sibling(w);
	if (z->parent == NULL) {
		root = zs;
		zs->parent = NULL;
	}
	else {
		Node* g = z->parent;
		zs->parent = g;
		if (z == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}
	free(z);
	free(w);
}

Node* sibling(Node* w) {
	Node* tmp = w;

	tmp = tmp->parent;

	if (w == tmp->rChild)
		tmp = tmp->lChild;
	else
		tmp = tmp->rChild;

	return tmp;
	
}

void print(Node* T) {
	printf(" %d", T->key);
	if(isInternal(T->lChild))
		print(T->lChild);
	if (isInternal(T->rChild))
		print(T->rChild);
}

void freeAll(Node* T) {
	if (isExternal(T))
		return;
	freeAll(T->lChild);
	freeAll(T->rChild);
	free(T);
}
