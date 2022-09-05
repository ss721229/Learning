#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct{
	int num;
	struct BinaryTree* leftChild, * rightChild;
}BinaryTree;

BinaryTree* firstAdd(int p, int lh, int rh) {
	BinaryTree* left = NULL, * right = NULL;
	BinaryTree* root = (BinaryTree*)malloc(sizeof(BinaryTree));

	root->num = p;

	if (lh != 0) {
		left = (BinaryTree*)malloc(sizeof(BinaryTree));
		left->num = lh;
		left->leftChild = NULL;
		left->rightChild = NULL;
		root->leftChild = left;
	}
	else
		root->leftChild = NULL;

	if (rh != 0) {
		right = (BinaryTree*)malloc(sizeof(BinaryTree));
		right->num = rh;
		right->leftChild = NULL;
		right->rightChild = NULL;
		root->rightChild = right;
	}
	else
		root->rightChild = NULL;

	return root;
}

void insertNode(BinaryTree* tree, int p, int lh, int rh) {
	BinaryTree* left = NULL, * right = NULL;

	if (lh != 0) {
		left = (BinaryTree*)malloc(sizeof(BinaryTree));
		left->num = lh;
		left->leftChild = NULL;
		left->rightChild = NULL;
		tree->leftChild = left;
	}
	else
		tree->leftChild = NULL;

	if (rh != 0) {
		right = (BinaryTree*)malloc(sizeof(BinaryTree));
		right->num = rh;
		right->leftChild = NULL;
		right->rightChild = NULL;
		tree->rightChild = right;
	}
	else
		tree->rightChild = NULL;
}

void findNum(BinaryTree* tree, int p, int lh, int rh) {
	if (tree) {
		if (tree->num == p) {
			insertNode(tree, p, lh, rh);
			return;
		}
		findNum(tree->leftChild, p, lh, rh);
		findNum(tree->rightChild, p, lh, rh);
	}
}


int main() {
	int n, s, p, rh, lh;
	char search[100];
	BinaryTree* root = NULL, *q = NULL;

	scanf("%d", &n);

	scanf("%d %d %d", &p, &lh, &rh);
	root = firstAdd(p, lh, rh);
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &p, &lh, &rh);
		findNum(root, p, lh, rh);
	}

	scanf("%d", &s);
	for (int i = 0; i < s; i++) {
		q = root;
		scanf("%s", search);
		for (int j = 0; j < strlen(search); j++) {
			printf(" %d", q->num);
			if (search[j] == 'R')
				q = q->rightChild;
			else
				q = q->leftChild;
		}
		printf(" %d\n", q->num);
	}
	return 0;
}