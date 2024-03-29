#include<stdio.h>
#define MAX 100
#define oo 99999
typedef int ElementType;
typedef struct{
    ElementType data[MAX];
    int size;
}List;

void make_null_list(List *L){
    L->size = 0;
}
void push_back(List *L , ElementType x){
    L->data[L->size] = x;
    L->size++;
}

ElementType element_at(List *L, int i){
    return L->data[i-1];
}

///
typedef struct{
    int n,m;
    int A[MAX][MAX];
}Graph;

void init_graph(Graph *G, int n){
    G->n=n;
    G->m=0;
}
void add_edge(Graph *G,int x,int y){
    G->A[x][y] += 1;
}
int adjacent(Graph *G,int x,int y){
    return G->A[x][y] != 0;
}
List neighbors(Graph *G, int x){
    int y;
    List list;
    make_null_list(&list);
    for(y=1;y<=G->n;y++)
        if(adjacent(G,x,y))
            push_back(&list,y);
    return list;
}
///
typedef struct{
    int front,rear;
    int data[MAX];
}Queue;
void make_null_queue(Queue *Q){
    Q->front = 0;
    Q->rear = -1;
}

void push(Queue *Q, int x){
    Q->rear++;
    Q->data[Q->rear] = x;
}

int top(Queue *Q){
    return Q->data[Q->front];
}
int pop(Queue *Q){
    return Q->front++;
}
int empty(Queue *Q){
    return Q->front > Q->rear;
}

// Ham min
int min(int a,int b){
    if(a<b) return a;
    else return b;
}

int max(int a , int b){
    if(a>b) return a;
    else return b;
}
int d[MAX];     // thoi gian hoan thanh cong viec
void topo_sort(Graph *G, List *L){
    int d[MAX];
    int x,u;
    Queue Q;
    // khoi tao hang doi rong 
    make_null_queue(&Q);
    // khoi tao bac vao cua u = 0
    for(u=1;u<=G->n;u++)
        d[u] = 0;
    // duyet qua all dinh , neu co duong di tu x->u thi bac vao u++
    for(x=1;x<=G->n;x++)
        for(u=1;u<=G->n;u++)
            if(G->A[x][u] > 0)
                d[u]++;     // tang bac vao cua u
    // dinh nao co bac vao = 0 thi push vao Queue
    for(u=1;u<=G->n;u++)
        if(d[u] ==0)
            push(&Q,u);
    // khoi tao danh sach de luu 
    make_null_list(L);
    while(!empty(&Q)){
        int u = top(&Q);    pop(&Q);        // lay u tu trong Queue ra sau do push_back vao List
        push_back(L,u);     
        // xet cac dinh ke v cua u
        List list = neighbors(G,u);
        for(x=1;x<=list.size;x++){
            int v = element_at(&list,x);
            d[v]--;
            if(d[v]==0)
                push(&Q,v);
        }
    }
}

int main(){
    Graph G;
    int n,u,x,v,i,j;
    int p;
    List L;
    //FILE* file = fopen("dt2.txt","r");
    //freopen("dt-B2.txt","r",stdin);
    scanf("%d",&n);
    init_graph(&G,n+2);
    d[n+1] = 0; // thoi gian hoan thanh cong viec cua n+1 = 0
    for(u=1;u<=n;u++){
        scanf("%d",&d[u]);    // thoi gian hoan thanh cong viec u
        do{
            scanf("%d",&x);
            if(x>0) add_edge(&G,x,u);
        }while(x>0);
    }

    // Them cung noi alpha voi cac dinh co bac vao = 0
    for(u=1;u<=n;u++){
        int deg_neg = 0;
        for(x=1;x<=n;x++)
            if(G.A[x][u] > 0)       // neu co duong di tu x->u thi bac vao cua u++
                deg_neg++;
        if(deg_neg == 0)
            add_edge(&G,n+1,u);     // alpha->u
    }
    // Them cung noi cac dinh co bac ra = 0 voi beta
    for(u=1;u<=n;u++){
        int deg_pos = 0;
        for(v=1;v<=n;v++)
            if(G.A[u][v] > 0)      
                deg_pos++;
        if(deg_pos==0)
            add_edge(&G,u,n+2);
    }
    topo_sort(&G,&L);

    // Xac dinh thoi diem som nhat
    int t[100];
    t[n+1] = 0;     // t[alpha] = 0
    for(j=2;j<=L.size;j++){
        int u = element_at(&L,j);
        t[u] = 0;
        for(x=1;x<=G.n;x++)
            if(G.A[x][u] > 0)   // co duong di tu x->u
                t[u] = max(t[u],t[x] + d[x]);
                
    }
    
    
    // Xac dinh thoi diem tre nhat
    int T[100];
    T[n+2] = t[n+2];        // T[beta] = t[beta]
    for(j=L.size-1;j>=1;j--){
        int u = element_at(&L,j);
        T[u] = oo;
        for(v=1;v<=G.n;v++)
            if(G.A[u][v] > 0)
                T[u] = min(T[u],T[v] - d[u]);
    }
    //printf("%d\n",t[n+2]);
   // printf("\n");
    //for(u=1;u<=G.n;u++)
	//	printf("%d-%d\n",t[u],T[u]);    
	for(u=1;u<=G.n;u++)
		if(t[u] == T[u]){
			printf("%d\n",u);
		}
    return 0;

}

