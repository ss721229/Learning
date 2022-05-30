#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

int sum = 0;
typedef struct {
	int data, id;
	struct BinaryTree* right,* left;
}BinaryTree;

void findNode(BinaryTree* tree, int id);
void sumFileVolume(BinaryTree* tree);
BinaryTree* add(int data, BinaryTree* p, BinaryTree* q);


int main() {
	BinaryTree* BT[8], * tree = NULL;
	int nodeID;

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

	scanf("%d", &nodeID);

	if (nodeID >= 9)
		printf("%d", -1);
	else
		findNode(tree, nodeID);

	for (int i = 0; i < 8; i++)
		free(BT[i]);

	return 0;
}
void findNode(BinaryTree* tree, int id) {
	if (tree) {
		if (tree->id == id) {
			sumFileVolume(tree);
			printf("%d",sum);
		}
		findNode(tree->left, id);
		findNode(tree->right, id);
	}
}

void sumFileVolume(BinaryTree* tree) {
	if (tree) {
		sumFileVolume(tree->left);
		sum += tree->data;
		sumFileVolume(tree->right);
	}
	
}

BinaryTree* add(int data, BinaryTree* p, BinaryTree* q) {
	BinaryTree* BT = malloc(sizeof(BinaryTree));
	BT->data = data;
	BT->left = p;
	BT->right = q;
	return BT;
}