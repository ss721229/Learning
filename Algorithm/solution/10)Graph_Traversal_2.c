#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex {
	int name, label;
	struct incidentEdges* header;
}VERTEX;

typedef struct edge {
	int start, end, label;
}EDGE;

typedef struct incidentEdges {
	int edgeIdx;
	struct incidentEdges* next;
}IncidentEdges;

typedef struct graph {
	struct vertex vertices[100];
	struct edge edges[1000];
}GRAPH;

IncidentEdges* getIncidence(int idx);
void makeGraph(GRAPH* g, int n, int m);
int opposite(GRAPH* g, int v, int e);
void DFS(GRAPH* g, int v);
void sortIncidence(GRAPH* g, int n);
void print(GRAPH* g, int n);

int main() {
	GRAPH* graph = malloc(sizeof(GRAPH));
	int n, m, s;
	scanf("%d %d %d", &n, &m, &s);
	makeGraph(graph, n, m);

	for (int i = s - 1; i < s + n - 1; i++)
		if (graph->vertices[i % n].label == 0)
			DFS(graph, i % n);
	return 0;
}

IncidentEdges* getIncidence(int idx) {
	IncidentEdges* p = NULL;
	p = (IncidentEdges*)malloc(sizeof(IncidentEdges));
	if (p == NULL) exit(1);
	p->edgeIdx = idx;
	p->next = NULL;
	return p;
}

void makeGraph(GRAPH* g, int n, int m) { // 초기 그래프 생성
	IncidentEdges* p = NULL, * t = NULL;
	int i, j, u, v;
	for (i = 0; i < n; i++) { // vertices
		g->vertices[i].name = i + 1;
		p = getIncidence(-1);
		g->vertices[i].header = p;
		g->vertices[i].label = 0; // fresh
	}
	for (i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		g->edges[i].start = u - 1;
		g->edges[i].end = v - 1;
		g->edges[i].label = 0; // fresh
	}

	for (i = 0; i < n; i++) { // 인접리스트
		p = g->vertices[i].header;
		for (j = 0; j < m; j++) { // 인접리스트
			if (g->edges[j].start == i || g->edges[j].end == i) {
				t = getIncidence(j);
				p->next = t;
				p = t;
			}
		}
	}
	sortIncidence(g, n);
}

int opposite(GRAPH* g, int v, int e) {
	int u = g->edges[e].start;
	int w = g->edges[e].end;
	if (v == w)
		return u;
	else
		return w;
}

void DFS(GRAPH* g, int v) {
	g->vertices[v].label = 1; // visited
	printf("%d\n", g->vertices[v].name);
	IncidentEdges* p = g->vertices[v].header;
	while (p != NULL) {
		if (p == g->vertices[v].header) {
			p = p->next;
			continue;
		}
		if (g->edges[p->edgeIdx].label == 0) {
			int w = opposite(g, v, p->edgeIdx);
			if (g->vertices[w].label == 0) {
				DFS(g, w);
			}
			else
				g->edges[p->edgeIdx].label = 1; // back
		}
		p = p->next;
	}
}

void sortIncidence(GRAPH* g, int n) {
	IncidentEdges* p = NULL, *q = NULL;
	int tmp;
	
	for (int i = 0; i < n; i++) {
		p = g->vertices[i].header;
		if (p->next != NULL)
			p = p->next;
		
		while (p != NULL) {
			q = p->next;
			while (q != NULL) {
				int w = opposite(g, i, q->edgeIdx);
				int v = opposite(g, i, p->edgeIdx);
				if (g->vertices[w].name < g->vertices[v].name) {
					tmp = p->edgeIdx;
					p->edgeIdx = q->edgeIdx;
					q->edgeIdx = tmp;
				}
				q = q->next;
			}
			p = p->next;
		}

	}
}

void print(GRAPH* g, int n) {
	IncidentEdges* p = NULL;

	for (int i = 0; i < n; i++) {
		p = g->vertices[i].header->next;

		while (p != NULL) {
			printf(" %d", g->vertices[opposite(g, i, p->edgeIdx)].name);
			p = p->next;
		}
		printf("\n");

	}
}