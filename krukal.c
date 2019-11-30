#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100
int parent[50];
//int root_u, root_v, sum_w;
typedef struct {
	int u, v, w;
} Edge;

typedef struct {
	Edge edge[MAX_EDGES];
	int n, m;
} Graph;

void init_graph (Graph *G, int n){
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int x, int y, int w){
	G->edge[G->m].u = x;
	G->edge[G->m].v = y;
	G->edge[G->m].w = w;
	G->m++;
}

void Swap(Edge *a, Edge *b){
	Edge temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void Sort(Graph *G){
	int i, j;
	for(i = 0; i < (G->m) -1; i++)
		for(j = i + 1; j < G->m; j++)
			if(G->edge[i].w > G->edge[j].w)
				Swap(&G->edge[i], &G->edge[j]);
}


int findRoot(int u){
	if(parent[u] == u)
		return u;
	return findRoot(parent[u]);
}

int kruskal(Graph *G, Graph *T){
	Sort(G);

	init_graph(T, G->n);
	int u, e;
	for(u = 0; u < G->n; u++)
		parent[u] = u;
	int sum_w = 0;
	for (e = 0; e < G->m; e++){
		int	u = G->edge[e].u;
		int v = G->edge[e].v;
		int w = G->edge[e].w;
		int root_u = findRoot(u);
		int root_v = findRoot(v);
		if(root_u != root_v){
			add_edge(T, u, v, w);
			parent[root_v] = root_u;
			sum_w += w ;
		}
	}
	return sum_w;
}

void main(){
	Graph G, T;
	int n, m, u, v, w, e;
//	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e = 1; e <= m; e++){
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	int sum_w = kruskal(&G, &T);
	if(sum_w > 0){
		printf("%d\n", sum_w);
		for (e = 0; e < T.m; e++)
			if(T.edge[e].u > T.edge[e].v)
			printf("%d %d %d\n", T.edge[e].v, T.edge[e].u, T.edge[e].w);
			else
			printf("%d %d %d\n", T.edge[e].u, T.edge[e].v, T.edge[e].w);
	}
}
