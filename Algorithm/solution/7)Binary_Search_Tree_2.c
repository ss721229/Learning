#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct{
	struct Node* lChild;
	struct Node* rChild;
	struct Node* parent;
	int height;
	int key;
}Node;

Node* root;


void insertItem(int k);
Node* treeSearch(int k);
void expandExternal(Node* w);
int findElement(int k);
void searchAndFixAfterInsertion(Node* w);
int updateHeight(Node* w);
int isBalanced(Node* w);
Node* restructure(Node* x, Node* y, Node* z);
int isExternal(Node* w);
int isInternal(Node* w);
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

void insertItem(int k) {
	Node* tmp = treeSearch(k);

	if (tmp == root) {
		tmp = (Node*)malloc(sizeof(Node));
		tmp->key = k;
		tmp->parent = NULL;
		expandExternal(tmp);
		root = tmp;
		searchAndFixAfterInsertion(tmp);
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
		searchAndFixAfterInsertion(tmp);
		
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

void expandExternal(Node* w) {
	Node* r = (Node*)malloc(sizeof(Node));
	Node* l = (Node*)malloc(sizeof(Node));
	w->lChild = l;
	w->rChild = r;
	w->height = 1;
	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;
	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;
}

int findElement(int k) {
	Node* tmp = treeSearch(k);
	if (isInternal(tmp))
		return k;
	else
		return -1;
}

void searchAndFixAfterInsertion(Node* w) {
	Node* l = w->lChild, * r = w->rChild;
	Node* x, * y, * z;
	l->height = 0; // expandExternal에서 해주는데 또해줘야되나?
	r->height = 0;
	w->height = 1;

	if (w == root)
		return;
	
	z = w->parent;
	while (updateHeight(z) && isBalanced(z)) {
		if (z == root)
			return;
		z = z->parent;
	}
	if (isBalanced(z))
		return;
	
	Node* tmpR, * tmpL;
	tmpR = z->rChild;
	tmpL = z->lChild;

	if (tmpR->height < tmpL->height)
		y = tmpL;
	else
		y = tmpR;

	tmpR = y->rChild;
	tmpL = y->lChild;

	if (tmpR->height < tmpL->height)
		x = tmpL;
	else
		x = tmpR;

	restructure(x, y, z);
}

int updateHeight(Node* w) {
	Node* l = w->lChild, * r = w->rChild;
	int h;
	if (l->height < r->height)
		h = r->height + 1;
	else
		h = l->height + 1;

	if (h != w->height) {
		w->height = h;
		return 1;
	}
	else
		return 0;
}

int isBalanced(Node* w) {
	Node* l = w->lChild, * r = w->rChild;
	int diff = l->height - r->height;
	if (diff < 0)
		diff *= -1;
	if (diff <= 1) // 균형 맞음
		return 1;
	else // 균형 안맞음
		return 0; 
}

Node* restructure(Node* x, Node* y, Node* z) {
	Node* a, * b, * c; // a, b, c를 중위순회 순서에 맞게 선정
	Node* T0, * T1, * T2, * T3;
	if (z->key < y->key && y->key < x->key) {
		a = z;
		b = y;
		c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}
	else if (x->key < y->key && y->key < z->key) {
		a = x;
		b = y;
		c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else if (z->key < x->key && x->key < y->key) {
		a = z;
		b = x;
		c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else { // y->key < x->key < z<-key
		a = y;
		b = x;
		c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}

	Node* tmp = z->parent;
	if (z == root) {
		root = b;
		b->parent = NULL;
	}
	else if (tmp->lChild == z) {
		tmp->lChild = b;
		b->parent = tmp;
	}
	else {
		tmp->rChild = b;
		b->parent = tmp;
	}

	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	b->rChild = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);

	return b;

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
