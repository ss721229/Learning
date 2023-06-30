#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct vertex {
	char name;
	int inDegree;
	struct incidentEdges* outEdges;
	struct incidentEdges* inEdges;
}VERTEX;

typedef struct edge {
	int start, end;
}EDGE;

typedef struct incidentEdges {
	int edgeIdx;
	struct incidentEdges* next;
}IncidentEdges;

typedef struct graph {
	struct vertex vertices[100];
	struct edge edges[1000];
}GRAPH;

GRAPH* buildGraph();
GRAPH* insertVertex(char vName, int i);
GRAPH* insertDirectedEdge(char uName, char wName, int i);
int index(char vName);
void addFirst(IncidentEdges* header, int i);
int* topologicalSort();
int isEmpty(int* queue);
void enqueue(VERTEX v);
VERTEX dequeue();
void freeAll();

GRAPH* g;
int n, m;
int* queue;
int rear, front;
int* topOrder;


int main() {
	
	buildGraph();
	topologicalSort();
	
	if (topOrder[0] == 0)
		printf("0");
	else
		for (int i = 1; i <= n; i++)
			printf("%c ", g->vertices[topOrder[i]].name);

	freeAll();
	return 0;
}

GRAPH* buildGraph() {
	IncidentEdges* p = NULL, * t = NULL;
	char ch, u, v;
	int i;

	g = malloc(sizeof(GRAPH));

	scanf("%d", &n);


	for (i = 0; i < n; i++) { // vertices
		getchar();
		scanf("%c", &ch);
		insertVertex(ch, i);
	}

	scanf("%d", &m);
	for (i = 0; i < m; i++) { // edges
		getchar();
		scanf("%c %c", &u, &v);
		
		insertDirectedEdge(u, v, i);
	}

	
	return g;
}

GRAPH* insertVertex(char vName, int i) {
	IncidentEdges* p = malloc(sizeof(IncidentEdges));
	IncidentEdges* t = malloc(sizeof(IncidentEdges));
	p->next = NULL;
	t->next = NULL;

	g->vertices[i].name = vName;
	g->vertices[i].outEdges = p;
	g->vertices[i].inEdges = t;
	g->vertices[i].inDegree = 0;

	return g;
}

GRAPH* insertDirectedEdge(char uName, char wName, int i) {
	int u = index(uName);
	int w = index(wName);
	g->edges[i].start = u;
	g->edges[i].end = w;
	addFirst(g->vertices[u].outEdges, i);
	addFirst(g->vertices[w].inEdges, i);
	g->vertices[w].inDegree++;

	return g;
}

int index(char vName) {
	for (int i = 0; i < n; i++)
		if (g->vertices[i].name == vName)
			return i;
}

void addFirst(IncidentEdges* header, int i) {
	IncidentEdges* p = malloc(sizeof(IncidentEdges));
	p->edgeIdx = i;
	p->next = header->next;
	header->next = p;
}

int* topologicalSort() {
	int* in;
	int u, w;
	IncidentEdges* p = NULL;

	topOrder = malloc(sizeof(int) * (n + 1));
	queue = malloc(sizeof(int) * n);
	in = malloc(sizeof(int) * n);

	rear = 0;
	front = 0;

	for (int i = 0; i < n; i++) {
		in[i] = g->vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(g->vertices[i]);
	}

	int t = 1;

	while (!isEmpty(queue)) {
		u = index(dequeue(queue).name);

		topOrder[t] = u;
		t += 1;

		p = g->vertices[u].outEdges;

		while (p!= NULL) {
			if (p == g->vertices[u].outEdges)
				if (p->next == NULL)
					break;
				else
					p = p->next;
			w = g->edges[p->edgeIdx].end;
			
			in[w] -= 1;
			if (in[w] == 0)
				enqueue(g->vertices[w]);

			p = p->next;
		}
	}
	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;

	return topOrder;

}

int isEmpty(int* queue) {
	return rear == front;
}
void enqueue(VERTEX v) {
	queue[front++] = index(v.name);
}
VERTEX dequeue() {
	return g->vertices[queue[rear++]];
}


void freeAll() {
	IncidentEdges* p, * pnext;

	for (int i = 0; i < n; i++) {
		p = g->vertices[i].inEdges;
		while (p->next != NULL) {
			pnext = p->next;
			free(p);
			p = pnext;
		}
		free(p);
	}
	for (int i = 0; i < n; i++) {
		p = g->vertices[i].outEdges;
		while (p->next != NULL) {
			pnext = p->next;
			free(p);
			p = pnext;
		}
		free(p);
	}
	free(g);
}