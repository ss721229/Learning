#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int data;
	struct BinaryTree* right, * left;
}BinaryTree;

BinaryTree* insert(int data, BinaryTree* p, BinaryTree* q);

int main() {
	BinaryTree* BT[8], * tmp;
	int N;

	BT[7] = insert(80, NULL, NULL);
	BT[6] = insert(130, NULL, NULL);
	BT[5] = insert(120, BT[6], BT[7]);
	BT[4] = insert(90, NULL, NULL);
	BT[3] = insert(70, NULL, NULL);
	BT[2] = insert(50, NULL, BT[5]);
	BT[1] = insert(30, BT[3], BT[4]);
	BT[0] = insert(20, BT[1], BT[2]);

	scanf("%d", &N);

	if (N >= 9)
		printf("-1");
	else {
		printf("%d", BT[N - 1]->data);

		if (BT[N - 1]->left != NULL) {
			tmp = BT[N - 1]->left;
			printf(" %d", tmp->data);
		}
		if (BT[N - 1]->right != NULL) {
			tmp = BT[N - 1]->right;
			printf(" %d", tmp->data);
		}
	}

	for (int i = 0; i < 8; i++)
		free(BT[i]);
	return 0;
}

BinaryTree* insert(int data, BinaryTree* p, BinaryTree* q) {
	BinaryTree* BT = malloc(sizeof(BinaryTree));
	BT->data = data;
	BT->left = p;
	BT->right = q;
	return BT;
}