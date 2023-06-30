#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int w;
	int ver1, ver2;
}Edge;

typedef struct {
	int num;
}Vertex;

typedef struct {
	Vertex ver[6];
	Edge edge[21];
	int adj[6][6];
}Graph;


void insertVertex(Graph* g, int n, int k);
void insertEdge(Graph* g, int u, int v, int w);
void printNodeAndWeight(Graph* g, int a);
void changeWeightOrInsertEdge(Graph* g, int a, int b, int w);
void removeEdge(Graph* g, int a, int b);

int i = 0;

int main() {
	Graph* graph = malloc(sizeof(Graph));

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			graph->adj[i][j] = -1;

	for (int i = 0; i < 6; i++)
		insertVertex(graph, i + 1, i);

	// 1
	insertEdge(graph, 0, 5, 2);
	insertEdge(graph, 0, 3, 1);
	insertEdge(graph, 0, 2, 1);
	insertEdge(graph, 0, 1, 1);

	// 2
	insertEdge(graph, 1, 2, 1);
	insertEdge(graph, 1, 0, 1);

	// 3
	insertEdge(graph, 2, 4, 4);
	insertEdge(graph, 2, 1, 1);
	insertEdge(graph, 2, 0, 1);

	// 4
	insertEdge(graph, 3, 0, 1);

	// 5
	insertEdge(graph, 4, 5, 3);
	insertEdge(graph, 4, 4, 4);
	insertEdge(graph, 4, 2, 4);

	// 6
	insertEdge(graph, 5, 4, 3);
	insertEdge(graph, 5, 0, 2);

	char cmd = ' ';
	int n;
	int a, b, w;

	while (cmd != 'q') {
		scanf("%c", &cmd);
		if (cmd == 'a') {
			scanf("%d", &n);
			if (n >= 1 && n <= 6)
				printNodeAndWeight(graph, n);
			else
				printf("-1\n");
		}
		else if (cmd == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			if (a >= 1 && a <= 6 && b >= 1 && b <= 6)
				changeWeightOrInsertEdge(graph, a, b, w);
			else
				printf("-1\n");
		}
		getchar();
	}
	free(graph);
	return 0;
}

void insertVertex(Graph* g, int n, int k) {
	Vertex ver;
	ver.num = n;
	g->ver[k] = ver;
}

void insertEdge(Graph* g, int u, int v, int w) {
	int flag = 0;
	for (int j = 0; j <= i; j++) {
		if (u + 1 == g->edge[j].ver1 && v + 1 == g->edge[j].ver2) {
			
			flag = 1;
			if (g->adj[u][v] == -1 && g->adj[v][u] == -1) {
				g->adj[u][v] = j;
				g->adj[v][u] = j;
				break;
			}
		}
		else if (v + 1 == g->edge[j].ver1 && u + 1 == g->edge[j].ver2) {
			
			flag = 1;
			if (g->adj[u][v] == -1 && g->adj[v][u] == -1) {
				g->adj[u][v] = j;
				g->adj[v][u] = j;
				break;
			}
		}

	}
	if (flag == 0) {
		if (g->adj[u][v] == -1 && g->adj[v][u] == -1) {
			g->edge[i].ver1 = g->ver[u].num;
			g->edge[i].ver2 = g->ver[v].num;
			g->edge[i].w = w;
			g->adj[u][v] = i;
			g->adj[v][u] = i;
			i++;
		}
	}
}

void printNodeAndWeight(Graph* g, int a) {
	int t = 0;
	for (int j = 0; j < 6; j++) {
		if (g->adj[a - 1][j] != -1) {
			t = g->adj[a - 1][j];
			if (g->edge[t].ver1 == a)
				printf(" %d %d", g->edge[t].ver2, g->edge[t].w);
			else
				printf(" %d %d", g->edge[t].ver1, g->edge[t].w);
		}
	}
	printf("\n");
}

void changeWeightOrInsertEdge(Graph* g, int a, int b, int w) {
	
	if (!w) {
		if (g->adj[a - 1][b - 1] == -1)
			printf("-1\n");
		else
			removeEdge(g, a, b);
	}
	else {
		if (g->adj[a - 1][b - 1] == -1) {
			insertEdge(g, a - 1, b - 1, w);
		}
		else
			g->edge[g->adj[a - 1][b - 1]].w = w;

	}
}

void removeEdge(Graph* g, int a, int b) {
	a -= 1;
	b -= 1;
	g->adj[a][b] = -1;
	g->adj[b][a] = -1;
}