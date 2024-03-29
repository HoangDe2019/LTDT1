#define maxe 100
#define maxn 100
#define maxm 100
#include <stdio.h>

int mark[maxn], num[maxn], min_num[maxn], on_stack[maxn];
int idx=1;
int cnt =0;
typedef struct{
	int data[maxe];
	int size;
}Stack;
Stack S;
void make_null_stack(Stack* S){
	S->size = 0;
}

void push(Stack* S,int x){
	S->data[S->size]=x;
	S->size++;
}

int top(Stack* S){
	return S->data[S->size -1];
}

void pop(Stack* S){
	S->size --;
}

int empty(Stack* S){
	return S->size == 0;
}

typedef struct{
	int data[maxn];
	int size;
}List;

void make_null(List* L){
	L->size=0;
}

void push_back(List* L, int x){
	L->data[L->size]=x;
	L->size++;
}

int element_at(List* L, int p){
	return L->data[p-1];
}

int size(List* L){
	return L->size;
}

typedef struct{
	int n,m;
	int a[maxn][maxm];
}Graph;

void init_graph(Graph* pG, int n, int m){
	int i,j;
	pG->m = m;
	pG->n = n;
	for (i=1; i<=n; i++)
		for (j=1; j<=m; j++)
			pG->a[i][j]=0;
}

void add_edge(Graph* pG,int e, int x, int y){
	pG->a[x][e]=1;
	pG->a[y][e]=-1;
}

int degree(Graph* pG, int x){
	int i,deg=0;
	for (i=1; i<=pG->m; i++)
		deg= deg + pG->a[x][i];
	return deg;
}

int adjacent(Graph* pG, int x, int y){
	int i,j;
	for (i=1; i<=pG->m; i++)
		for (j=1; j<=pG->m; j++)
		if ((pG->a[x][i]==1)&&(pG->a[y][i]==-1)||(pG->a[x][j]==1)&&(pG->a[y][j]==-1))
			return 1;
	return 0;
}

List neighbors(Graph* G,int x){
	int i;
	List list;
	make_null(&list);
	for (i=1; i<= G->n; i++)
		if (i!=x)
			if (adjacent(G,x,i)) push_back(&list,i);
	return list;	
}

void traversal(Graph* G, int x){
	int i,y;
	if (mark[x]==1)
		return;
	printf("%d \n",x);
	mark[x] = 1;
	List list = neighbors(G,x);
	for (i=1 ; i<=list.size ; i++){
		y = element_at(&list,i);
		traversal(G,y);
	}
}

int min(int a, int b){
	if (a>b) return b;
	else return a;
}
void strong_connect(Graph* G, int x){
	int i;
	num[x] = min_num[x] = idx; idx ++;	
	push(&S, x);		
	on_stack[x] = 1;	
	List list = neighbors(G,x);
	for (i = 1; i<= list.size; i++){
		int y = element_at(&list,i);
		if (num[y] < 0){
			strong_connect(G,y);
			min_num[x] = min(min_num[x], min_num[y]);
		}else if (on_stack[y])
			min_num[x] = min(min_num[x], num[y]);
	}
	if (num[x] == min_num[x]){
		cnt ++;
		int w;
		do{
			w = top(&S); pop(&S);
			on_stack[w]= 0;
		} while (w!= x);
	}
}

void main(){
	//freopen("dt.txt","r",stdin);
	Graph G;
	List list;
	make_null(&list);
	int i,j,n,m,x,y;
	scanf("%d%d",&n,&m);
	init_graph(&G,n,m);
	
	for (i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		add_edge(&G,i,x,y);
	}
	for (i =1; i<=n ; i++){
		num[i]= -1;
		on_stack[i]=0;}
	idx = 1;
	make_null_stack(&S);
	for (i =1; i<=n ; i++){
		if (num[i]==-1)
			strong_connect(&G, i);
	}
	if (cnt ==1 ) printf("strong connected");
	else printf("unconnected");
}
