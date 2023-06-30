#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex {
	int name;
}VERTEX;
typedef struct edge {
	int w;
	int endpoint1, endpoint2;
}EDGE;

typedef struct graph {
	struct vertex vertices[100];
	struct edge edges[1000];
	int adjacencyMatrix[100][100];
}GRAPH;

void makeGraph(GRAPH* g, int n, int m);
void PrimJarnik(GRAPH * g, int n);
int getMinVertex(GRAPH* g, int n);

int selected[100];
int dist[100];

int main() {
	GRAPH* graph = malloc(sizeof(GRAPH));
	int n, m;
	scanf("%d %d", &n, &m);
	makeGraph(graph, n, m);	
	PrimJarnik(graph, n);

	free(graph);

	return 0;
}
void makeGraph(GRAPH* g, int n, int m) { // 초기 그래프 생성
	int i, j, a, b;
	int u, v, w;
	for (i = 0; i < n; i++) // vertex 배열
		g->vertices[i].name = i + 1;

	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		g->edges[i].endpoint1 = u;
		g->edges[i].endpoint2 = v;
		g->edges[i].w = w;
	}

	for (i = 0; i < n; i++) // 인접행렬 초기화
		for (j = 0; j < n; j++)
			g->adjacencyMatrix[i][j] = -1;

	for (i = 0; i < m; i++) { // 인접행렬 설정
		a = g->edges[i].endpoint1;
		b = g->edges[i].endpoint2;
		g->adjacencyMatrix[a - 1][b - 1] = i;
		g->adjacencyMatrix[b - 1][a - 1] = i;
	}
}

int getMinVertex(GRAPH* g, int n) {
	int ver = 0;

	for (int i = 0; i < n; i++) {
		if (!selected[i]) {
			ver = i;
			break;
		}
	}
	for (int i = 0; i < n; i++)
		if (!selected[i] && dist[i] < dist[ver])
			ver = i;
	return ver;
}

void PrimJarnik(GRAPH* g, int n) {
	int u, v;
	int weight = 0;

	for (u = 0; u < n; u++) {
		dist[u] = 99999999;
		selected[u] = 0;
	}
	dist[0] = 0;

	for (int i = 0; i < n; i++) {
		u = getMinVertex(g, n);
		selected[u] = 1;
		if (dist[u] == 99999999) return;

		printf(" %d", u + 1);
		for (v = 0; v < n; v++) {
			if (g->adjacencyMatrix[u][v] != -1) {
				if (!selected[v] && g->edges[g->adjacencyMatrix[u][v]].w < dist[v])
					dist[v] = g->edges[g->adjacencyMatrix[u][v]].w;
			}
		}
	}
	printf("\n");
	for (int i = 0; i < n; i++)
		weight += dist[i];
	printf("%d", weight);
}

