#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main() {
	int n, * list, tmp, j;
	scanf("%d", &n);
	list = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", &list[i]);
	
	for (int i = 1; i < n; i++) {
		j = i;
		while (list[j] < list[j - 1] && j >= 1) {
			tmp = list[j];
			list[j] = list[j - 1];
			list[j - 1] = tmp;
			j--;
		}
	}
	for (int* p = list; p < list + n; p++)
		printf(" %d", *p);

	free(list);
	return 0;
}