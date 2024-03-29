#include <stdio.h>
#define MAXN 1000
#define INFINITY 9999999
int pi[MAXN];
int p[MAXN];

typedef struct {
	int u, v;
	int w;
} Edge;

typedef struct {
	int n, m;
	Edge edges[MAXN];
} Graph;
void init_graph(Graph *G, int n, int m){
	G->n = n;
	G->m = 0;
}
void add_edge(Graph *G, int u, int v, int w){
	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m].w = w;
	G->m++;
 }
 
 void BellmanFord(Graph *G, int s){
 	int i, j, it,k;
 	for(i=1; i<= G->n; i++){
 		pi[i] = INFINITY;
 	}
 	pi[s] = 0;
 	p[s] = -1;
 	for(it = 1; it < G->n; it++){
 		for(k=0; k< G->m; k++){
 			int u = G->edges[k].u;
 			int v = G->edges[k].v;
 			int w = G->edges[k].w;
 			if(pi[u] + w < pi[v]){
 				pi[v] = pi[u] + w;
 				p[v] = u;
 			}
 		}
 	}
 	for(k=0; k< G->m; k++){
 		int u = G->edges[k].u;
 		int v = G->edges[k].v;
 		int w = G->edges[k].w;
 		if(pi[u] + w < pi[v]){
 			printf("negative cycle"); break;
 		} else {
 			printf("ok"); break;
 		}						
 	}
 }
 int main(){
 //	freopen("dt.txt", "r", stdin);
	Graph G;
	int n, m, u, v, e, w;
	int i;
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	for (e = 1; e <= m; e++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G,u,v,w);
	}
	BellmanFord(&G, 1);
/*	for(i=1; i<=G.n;i++)
		printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);*/
 }
