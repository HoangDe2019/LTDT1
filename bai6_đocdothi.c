#include <stdio.h>

typedef int ElementType;
typedef struct {
ElementType data[100];
int size;
} List;
typedef struct{
	int n,m;
	int A[100][500];
}Graph;
void init_graph(Graph *G, int n){
	int i,j;
	G->n =n;
	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
		G->A[i][j]=0;
}
void add_edge(Graph*G, int x, int y){
	G->A[x][y]=1;
	G->A[y][x]=1;
}


int main(){
	freopen("dt1.txt", "r", stdin); 
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	int i,j;
	for (i =1;i<=n;i++){
		for (j=1;j<=n;j++){
			printf("%d ",G.A[i][j]);
		} printf("\n");
	}
}
