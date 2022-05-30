#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int data, id;
	struct BinaryTree* right,* left;
}BinaryTree;

void findNode(BinaryTree* tree, int id, int N);
void preOrder(BinaryTree *tree);
void postOrder(BinaryTree* tree);
void inOrder(BinaryTree* tree);

BinaryTree* add(int data, BinaryTree* p, BinaryTree* q);


int main() {
	BinaryTree* BT[8], * tree = NULL;
	int N, nodeID;

	BT[7] = add(80, NULL, NULL);
	BT[6] = add(130, NULL, NULL);
	BT[5] = add(120, BT[6], BT[7]);
	BT[4] = add(90, NULL, NULL);
	BT[3] = add(70, NULL, NULL);
	BT[2] = add(50, NULL, BT[5]);
	BT[1] = add(30, BT[3], BT[4]);
	BT[0] = add(20, BT[1], BT[2]);
	tree = BT[0];

	for (int i = 1; i < 9; i++)
		BT[i - 1]->id = i;

	scanf("%d %d", &N, &nodeID);

	if (nodeID >= 9)
		printf("%d", -1);
	else
		findNode(tree, nodeID, N);

	for (int i = 0; i < 8; i++)
		free(BT[i]);

	return 0;
}
void findNode(BinaryTree* tree, int id, int N) {
	if (tree) {
		if (tree->id == id) {
			if (N == 1)
				preOrder(tree);
			else if (N == 2)
				inOrder(tree);
			else if (N == 3)
				postOrder(tree);
		}
		findNode(tree->left, id, N);
		findNode(tree->right, id, N);
	}
}

void preOrder(BinaryTree* tree) {
	if (tree) {
		printf(" %d", tree->data);
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

void postOrder(BinaryTree* tree) {

	if (tree) {
		postOrder(tree->left);
		postOrder(tree->right);
		printf(" %d", tree->data);
	}
}

void inOrder(BinaryTree* tree) {
	if (tree) {
		inOrder(tree->left);
		printf(" %d", tree->data);
		inOrder(tree->right);
	}
}

BinaryTree* add(int data, BinaryTree* p, BinaryTree* q) {
	BinaryTree* BT = malloc(sizeof(BinaryTree));
	BT->data = data;
	BT->left = p;
	BT->right = q;
	return BT;
}