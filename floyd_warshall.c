#include<stdio.h>
#define MAXN 500
#define NO_EDGE 951
typedef struct{
	int n;
	int L[MAXN][MAXN];
}Graph;
void init_graph(Graph* G, int n){
	G->n=n;
	int i, j;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			G->L[i][j] = NO_EDGE;
}
void add_edge(Graph* G, int u, int v, int w){
	G->L[u][v]=w;
}
// giai thuat
#define INFINITY 9000
int pi[MAXN][MAXN];
int next[MAXN][MAXN];
void Floyd_Warshall(Graph* G){
	int u, v, k;
	for(u=1; u<=G->n; u++)
		for(v=1; v<=G->n; v++){
			pi[u][v] = INFINITY;
			next[u][v] = -1;
		}
	
	for(u=1; u<=G->n; u++)
		pi[u][u] = 0;
	
	for(u=1; u<=G->n; u++)
		for(v=1; v<=G->n; v++)
			if(G->L[u][v] != NO_EDGE){
				pi[u][v] = G->L[u][v];
				next[u][v] = v;
			}
	
	for(k=1; k<=G->n; k++)
		for(u=1; u<=G->n; u++)
			for(v=1; v<=G->n; v++)
				if(pi[u][k] + pi[k][v] < pi[u][v]){
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
}
int main(){
	Graph G;
	int n, m, u, v, w, e;
//	freopen("floy1.txt", "r", stdin); 
	scanf("%d%d",&n,&m);
	init_graph(&G,n);
	for(e=1; e<=m; e++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(&G,u,v,w);
		G.L[u][v]=w;
	}
	Floyd_Warshall(&G);
	for(u=1; u<=G.n; u++)
			for(v=1; v<=G.n; v++)
			if(pi[u][v]>=INFINITY-5){
				printf("%d -> %d: oo\n",u,v);
			}else
				printf("%d -> %d: %d \n",u,v,pi[u][v]);
	return 0;	
}
