#include <stdio.h>
#define MAX_ELEMENTS 100

// STACK
typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} Stack;

void make_null_stack(Stack* S) {
	S->size = 0;
}

void push(Stack* S, int x) {
	S->data[S->size] = x;
	S->size++;
}

int top(Stack* S) {
	return S->data[S->size - 1];
}

void pop(Stack* S) {
	S->size--;
}

int empty(Stack* S) {
	return S->size == 0;
}

// LIST
typedef int ElementType;

typedef struct {
	ElementType data[MAX_ELEMENTS];
	int size;
} List;

void make_null(List* L) {
	L->size = 0;
}

void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}

ElementType element_at(List* L, int i) {
	return L->data[i-1];
}

int count_list(List* L) {
	return L->size;
}

#define MAX_VERTICES 100
#define MAX_EDGES 500

typedef struct {
	int n, m;
	int A[MAX_VERTICES][MAX_EDGES];
} Graph;

void init_graph(Graph* G, int n, int m) {
	int i, j;
	G->n = n;
	G->m = m;
	for (i = 1; i <= n; i++) 
		for (j = 1; j <= m; j++)
			G->A[i][j] = 0;
}

void add_edge(Graph* G, int e, int x, int y) {
	G->A[x][e] = 1;
	G->A[y][e] = 1;
}

int adjeacent(Graph* G, int x, int y) {
	int e;
	for (e = 1; e <= G->m; e++) 
		if (G->A[x][e] == 1 && G->A[y][e] == 1)
			return 1;
	return 0;
}

int degree(Graph* G, int x) {
	int e, deg = 0;
	for (e = 1; e <= G->m; e++) 
		if (G->A[x][e] == 1)
			deg++;
	return deg;
}
List neighbors(Graph* G, int x) {
    List ansList;
    make_null(&ansList);
    int col, row, temp;
    for(col = 1; col <= G->m; col++) {
        if(G->A[x][col] == 1) {
            for(row = 1; row <= G->n; row++) {
                if(G->A[row][col] == 1 && row != x) { 
                    push_back(&ansList, row);
                }
            }
        }
    }
    int i, j;
    for(i = 1; i <= count_list(&ansList)-1; i++) {
        for(j = i+1; j <= count_list(&ansList); j++) {
            if(element_at(&ansList, i) > element_at(&ansList, j)) {
                temp = ansList.data[i-1];
                ansList.data[i-1] = ansList.data[j-1];
                ansList.data[j-1] = temp;
            }
        }
    }
    List checkList;
    make_null(&checkList);
    int check = 1;
    for(i = 1; i <= count_list(&ansList); i++) {
        for(j = 1; j <= count_list(&checkList); j++) {
            if(element_at(&ansList, i) == element_at(&checkList, j)) {
                check = 0;
            }
        }
        if(check) {
            push_back(&checkList, element_at(&ansList, i));
        }
    }
    return checkList;
}
// Duyet do thi theo chieu sau khong su dung de quy
void depth_first_search(Graph* G) {
	Stack S;
	make_null_stack(&S);
	int mark[MAX_VERTICES];
	int j;
	for (j = 1; j <= G->n; j++) 
		mark[j] = 0;
	Stack T;
	make_null_stack(&T);
	for (j = G->n; j >= 1; j--) {
	    push(&T, j);
	}
	int parent[MAX_VERTICES];
	for (j = 1; j <= G->n; j++) {
		parent[j] = -1;
	}
	while (!empty(&T)) {
		// Tao list de xet do uu tien khi chon cha (Chon thang co chi so lon hon)
		List moixet;
		make_null(&moixet);
		if (parent[top(&T)] == -1)
			parent[top(&T)] = 0;
	    push(&S, top(&T));
	    pop(&T);
	    while (!empty(&S)) {
		    int x = top(&S);
		    pop(&S);
		    if (mark[x] != 0)
			    continue;
		    mark[x] = 1;
			push_back(&moixet, x);
			
			List list = neighbors(G, x);
		    for (j = 1; j <= list.size; j++) {
			    int y = element_at(&list, j);
			    if (mark[y] == 0)
				    push(&S, y);
		    }
			int i, timthay = 0;
		    for (i = moixet.size; i >= 1; i--) {
		    	for (j = 1; j <= list.size; j++) {
		    		int y = element_at(&list, j);
		    		if (mark[y] == 1 && parent[x] == -1 && y == element_at(&moixet, i)) {
		    			parent[x] = y;
		    			timthay = 1;
		    			break;
					}
				}
				if (timthay) 
					break;
			}
		    	
 	    }
	}
	for (j = 1; j <= G->n; j++) {
		printf("%d %d\n", j, parent[j]);
	}
}
int main() {
	Graph G;
	int n, m, e, u, v;
//	freopen("dt.txt","r",stdin);
	scanf("%d %d", &n, &m);
	init_graph(&G, n, m);

	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, e, u, v);
	}
	depth_first_search(&G);
	return 0;
}
