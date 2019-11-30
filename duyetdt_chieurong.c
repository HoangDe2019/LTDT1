#include <stdio.h>
#define MAX_ELEMENTS 100
#define MAX_VERTEXES 100
typedef int ElementType;
int mark[MAX_VERTEXES];
/*khai bao do thi */
typedef struct {
	int A[MAX_VERTEXES][MAX_VERTEXES];
	int n,m;
}Graph;
/*khai bao cau truc list */
typedef struct {
	ElementType data[MAX_ELEMENTS];
	int size;
} List;
/* Khai bao hang doi */
typedef struct {	
	int data[MAX_ELEMENTS];
	int front, rear;
} Queue;
void make_null_queue(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}
void push(Queue* Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}
int top(Queue* Q) {
	return Q->data[Q->front];
}
void pop(Queue* Q) {
	Q->front++;
}
int empty(Queue* Q) {
	return Q->front > Q->rear;
}
void make_null(List* L) {
L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List* L, ElementType x) {
L->data[L->size] = x;
L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1 */
ElementType element_at(List* L, int i) {
return L->data[i-1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List* L) {
return L->size;
}
/* phan do thi */
void init_graph(Graph *G,int n){
	int i,j;
	G->n = n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			G->A[i][j]=0;
}
void add_edge(Graph *G, int x,int y){
	G->A[x][y]=1;
	G->A[y][x]=1;
}
int adjacent(Graph *G, int x, int y){
	return G->A[x][y] != 0;
}
int degree(Graph *G,int x){
	int y,deg=0;
	for(y=1; y<= G->n; y++)
		deg+= G->A[x][y];
	return deg;
}
List neighbors(Graph *G, int x){
	int y;
	List list;
	make_null(&list);
	for(y=1;y<=G->n;y++)
		if(adjacent(G,x,y))
			push_back(&list,y);
	return list;
}

void breadth_first_search(Graph *G, int x){
	
	Queue frontier;
	
	make_null_queue(&frontier);
		int j;
	push(&frontier, x );
	mark[x] = 1;

	
	while(!empty(&frontier)){
		int x = top(&frontier);
		pop(&frontier);
		
		printf("%d\n", x);
		
		List list = neighbors(G, x);
		
		for(j = 1; j <= list.size; j++){
			int y = element_at(&list,j);
			
			if(mark[y] == 0){
				mark[y] = 1;
				push(&frontier, y);
			}
		}
	}
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
	for(e=1;e<=n;e++)
		if(mark[e]==0)
			breadth_first_search(&G,e);
	return 0;
}
