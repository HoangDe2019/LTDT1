#include <stdio.h>
typedef int ElemenType;
typedef struct {
    ElemenType data[100];
    int size;
}List;
void make_null(List *l){
    l->size=0;
}
void push_back(List *l,ElemenType x){
    l->data[l->size]=x;
    l->size++;
}
ElemenType element_at(List *L, int i){
    return L->data[i-1];
}
void inlist(List *L){
    for (int i=0;i<L->size;i++)
        printf("%d ",L->data[i]);
}
typedef struct {
    int n,m;
    List adj[100];
}Graph;

void init_graph(Graph *G,int n){
    G->n=n;
    G->m=0;
    for (int i=1;i<=n;i++)
        make_null(&G->adj[i]);
}
/* them cung cu
void add_edge(Graph *G,int x,int y){
    G->m=G->m+1;
    push_back(&G->adj[x],y);
    push_back(&G->adj[y],x);
}
 */
//them cung cay
void add_edge(Graph *G,int x,int y){
    G->m=G->m+1;
    push_back(&G->adj[x],y);
    push_back(&G->adj[y],x);
}
int adjacent(Graph *G,int x,int y){
    int i;
    for ( i=0;i<G->adj[x].size;i++)
        if (G->adj[x].data[i]==y)
            return 1;
    return 0;
}

List neighbours(Graph *G,int x){
    List l;
    int i,j,t;
    l=G->adj[x];
    for ( i=0;i<l.size;i++)
        for ( j=i;j<l.size;j++)
        if (l.data[i]>l.data[j])
        {
            t=l.data[i];
            l.data[i]=l.data[j];
            l.data[j]=t;
        }
    return l;
}
typedef struct {
    int data[100];
    int front,rear;
}Queue;
void make_null_queue(Queue *Q){
    Q->front=0;
    Q->rear=-1;
}
void push(Queue *Q,int x){
    Q->rear++;
    Q->data[Q->rear]=x;
}
int top(Queue *Q){
    return Q->data[Q->front];
}
void pop(Queue *Q){
    Q->front=Q->front+1;
}
int empty(Queue *Q){
    return (Q->front > Q->rear);
}
int mark[100];
int parent[100];
void mark_null(Graph *G){
    //int mark[100];
    //G->n=n;
    for (int i=1;i<=G->n;i++)
    {
        mark[i]=0;
        //printf("%d \n",mark[i]);
    }
}


void breath_frist_search(Graph *G,int i){
    Queue frontier;
    make_null_queue(&frontier);

    push(&frontier, i);//i=1
    mark[i]=1;
    int t;
    t=0;
    while (!empty(&frontier)){
        int x;//x=4
        x=top(&frontier);
        t=x; //t=4
        //printf("mark[%d]=%d\n",x,mark[x]);
        pop(&frontier);
        //printf("Duyet %d\n",x);
        List l;
        l=neighbours(G, x); // 1
        if (x==i)//4=1
            {   parent[x]=0;
            //printf("%d %d\n",x,parent[x]);
            for (int j=0;j<l.size;j++)
                if ((parent[l.data[j]]==0) && (l.data[j]!=i))
                        parent[l.data[j]]=t;//prent[4]=1;
            }
        else
            {
                for (int j=0;j<l.size;j++)//1
                    if ((parent[l.data[j]]==0) && (l.data[j]!=i))
                    {
                        parent[l.data[j]]=t;
                        // printf("t=%d \n",t);
                    }
            }
      
         //printf("%d %d\n",x,parent[x]);
        for (int j=0;j<l.size;j++)
        {
            int y;
            y=l.data[j];//y=1;
            //printf("data %d\n",l.data[j]);
            if (mark[y]==0)
            {
                //printf("bat dau duyet %d\n",y);
                mark[y]=1;
                push(&frontier, y);//4
            }
        }
    }
    //printf("\n");
   // for (int i=1;i<=G->n;i++)
     //   printf("%d %d\n",i,parent[i]);
}
void inparent(int x){
        printf("%d %d\n",x,parent[x]);
}

int main(){
    FILE *f;
    Graph G;
//    f=freopen("dt.txt","r",stdin);
    int n,m,u,v;
    scanf("%d %d",&n,&m);
    //     printf("%d %d",n,m);
    init_graph(&G, n);
    for (int i=1;i<=m;i++){
        scanf("%d %d",&u,&v);
        add_edge(&G,u, v);
    }
    for (int i=1;i<=G.n;i++)
    {
        if (mark[i]==0)
            breath_frist_search(&G,i);
        inparent(i);
    }
    return 0;
}
