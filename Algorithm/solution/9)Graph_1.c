#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct {
	int w, id;
	int ver1, ver2;
}Edge;

typedef struct {
	int edgeNum;
	struct Incident* next;
}Incident;

typedef struct {
	int num;
	Incident* header;
}Vertex;

typedef struct {
	Vertex ver[8];
	Edge edge[50];
}Graph;

void insertVertex(Graph* g, int n, int i);
void insertEdge(Graph* g, int u, int v, int o);
void printNodeAndWeight(Graph* g, int a);
void changeWeightOrInsertEdge(Graph* g, int a, int b, int w);
int removeEdge(Graph* g, int a, int b);
void freeAll(Graph* g);

int i = 0;

int main() {
	Graph* graph = malloc(sizeof(Graph));

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
	freeAll(graph);
	return 0;
}

void insertVertex(Graph* g, int n, int i) {
	Vertex ver;
	Incident* inc = malloc(sizeof(Incident));
	ver.num = n;
	ver.header = inc;

	inc->edgeNum = 0;
	inc->next = NULL;

	g->ver[i] = ver;
}

void insertEdge(Graph* g, int u, int v, int o) {
	Incident* inc = malloc(sizeof(Incident));
	int flag = 0;
	//inc->next = g->ver[u].header->next;
	//g->ver[u].header->next = inc;
	
	for (int j = 0; j <= i; j++) {
		if (u == g->edge[j].ver1 && v == g->edge[j].ver2) {
			inc->edgeNum = j;
			continue;
		}
		else if (v == g->edge[j].ver1 && u == g->edge[j].ver2) {
			inc->edgeNum = j;
			continue;
		}
		else {
			g->edge[i].ver1 = g->ver[u].num;
			g->edge[i].ver2 = g->ver[v].num;
			g->edge[i].w = o;
			g->edge[i].id = 1;
			inc->edgeNum = i;
			flag = 1;
			break;
		}
	}

	Incident* p = g->ver[u].header, * q = g->ver[u].header;
	if (p->next != NULL) {
		p = p->next;

		if (g->edge[inc->edgeNum].ver2 > g->edge[p->edgeNum].ver2) {
			while (g->edge[inc->edgeNum].ver2 > g->edge[p->edgeNum].ver2 && p->next != NULL) {
				//printf("%d %d\n", g->edge[inc->edgeNum].ver2, g->edge[p->edgeNum].ver2);
				p = p->next;
			}
			if (g->edge[inc->edgeNum].ver2 < g->edge[p->edgeNum].ver2) {
				while (q->next != p)
					q = q->next;
				p = q;
			}
		}
		else
			p = q;
	}
	inc->next = p->next;
	p->next = inc;

	if (flag)
		i++;

}

void printNodeAndWeight(Graph* g, int a) {
	Incident* p = g->ver[a - 1].header;
	if (p->next == NULL)
		printf("-1\n");
	else {
		while (p->next != NULL) {
			p = p->next;
			printf(" %d %d", g->edge[p->edgeNum].ver2, g->edge[p->edgeNum].w);
		}
		printf("\n");
	}
}

void changeWeightOrInsertEdge(Graph* g, int a, int b, int w) {
	Incident* p = g->ver[a - 1].header;
	int flag = 0, f1, f2;
	if (w != 0) {
		
		for (int j = 0; j <= i; j++) {
			//printf("%d %d %d %d %d\n", a, b, g->edge[j].ver1, g->edge[j].ver2, g->edge[j].id);
			if (a == g->edge[j].ver1 && b == g->edge[j].ver2 && g->edge[j].id == 1) {
				g->edge[j].w = w;
				flag = 1;
			}
			else if (b == g->edge[j].ver1 && a == g->edge[j].ver2 && g->edge[j].id == 1) {
				g->edge[j].w = w;
				flag = 1;
			}
		}
		if (flag == 0 || p->next == NULL) {
			if(a != b)
				insertEdge(g, a - 1, b - 1, w);
			insertEdge(g, b - 1, a - 1, w);
		}
	}
	else {
		f1 = removeEdge(g, a, b);
		f2 = removeEdge(g, b, a);
		if (f1 == 0 && f2 == 0)
			printf("-1\n");
	}
}

int removeEdge(Graph* g, int a, int b) {
	Incident* p = g->ver[a - 1].header, * q = g->ver[a - 1].header;
	int flag = 0;
	while (p->next != NULL) {
		p = p->next;
		if (g->edge[p->edgeNum].ver1 == a && g->edge[p->edgeNum].ver2 == b) {
			g->edge[p->edgeNum].id = -1;
			q->next = p->next;
			free(p);
			p = q;
			flag = 1;
			
			
		}
		else if (g->edge[p->edgeNum].ver1 == b && g->edge[p->edgeNum].ver2 == a) {
			g->edge[p->edgeNum].id = -1;
			q->next = p->next;
			free(p);
			p = q;
			flag = 1;
			
		}
		else
			q = q->next;
	}

	return flag;

}
void freeAll(Graph* g) {
	Incident* p, *pnext;
	
	for (int i = 0; i < 6; i++) {
		p = g->ver[i].header;
		while (p->next != NULL) {
			pnext = p->next;
			free(p);
			p = pnext;
		}
		free(p);
	}
	free(g);
}