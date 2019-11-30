#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_VERTICES 100
typedef int Element_Type;

typedef struct {
	Element_Type data[MAX_ELEMENTS];
	int size;
}List;

void make_null_list(List *L){
	L->size=0;
}

void push_back(List *L, Element_Type x){
	L->data[L->size]=x;
	L->size++;
}

Element_Type element_at(List *L, int i){
	return L->data[i-1];
}

int count_list(List *L){
	return L->size;
}


typedef struct {
	int n;
	List adj[MAX_VERTICES];
}Graph;				

void init_graph(Graph *G, int n){
	G->n=n;
	int i;
	for(i=1; i<=n; i++)
		make_null_list(&G->adj[i]);  
}

void add_edge(Graph *G, int x, int y){   
	push_back(&G->adj[x], y);
	push_back(&G->adj[y], x);
}

int adjacent(Graph *G, int x, int y){
	int i;
	for(i=1; i<=G->adj[x].size; i++)
		if(element_at(&G->adj[x],i) == y)	
			return 1;
	return 0;
}

int degree(Graph *G, int x){
	return G->adj[x].size;
}
List neighbors(Graph *G, int x){
	List L;
	make_null_list(&L);
	int y;
	for(y=1 ;y<=G->n; y++)
		if(adjacent(G,x,y) ) push_back(&L, y);
	return L;
	
}

int mark[MAX_VERTICES];
void traversal(Graph *G, int x){
	if(mark[x] == 1) return;
		mark[x]=1;
	printf("%d\n",x);
	List L=neighbors(G,x);
	int i;
	for(i=1; i<=L.size; i++){
		int y=element_at(&L,i);
		traversal(G,y);
	}
}
void depth_first_search(Graph *G, int x){
	int i;
	for(i=1; i<=G->n; i++)
		//mark[i]=0;
		traversal(G,x);
}


int main(){
//	freopen("dt.txt", "r", stdin); 
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	depth_first_search(&G, 1);
	for (w = 1; w <= n; w++)
		if (mark[w] == 0)
			depth_first_search(&G,w);
}
