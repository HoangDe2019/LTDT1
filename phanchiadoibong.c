#include <stdio.h>
#define INFINITY 9999
#define MAXN 500
#define NO_EDGE 0

typedef struct {
	int n; // Dinh
	int m;
	int L[MAXN][MAXN];
} Graph;

void init_graph(Graph* G, int n, int m) {
	G->n = n;
	G->m = m;
	int i, j;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			G->L[i][j] = NO_EDGE;
		}
	}
}

// LIST
#define MAX_ELEMENTS 100
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

int adjeacent(Graph* G, int x, int y) {
	int e;
	for (e = 1; e <= G->m; e++) 
		if (G->L[x][e] == 1 && G->L[y][e] == 1)
			return 1;
	return 0;
}

int degree(Graph* G, int x) {
	int e, deg = 0;
	for (e = 1; e <= G->m; e++) 
		if (G->L[x][e] == 1)
			deg++;
	return deg;
}

void print_list(List L) {
	int i;
	for (i = 1; i <= L.size; i++) {
		printf("%d ", element_at(&L, i));
	}
}

List neighbors(Graph* G, int x) {
    List ansList;
    make_null(&ansList);
    int col, row, temp;
    for(col = 1; col <= G->m; col++) {
        if(G->L[x][col] == 1) {
            for(row = 1; row <= G->n; row++) {
                if(G->L[row][col] == 1 && row != x) { 
                    push_back(&ansList, row);
                }
            }
        }
    }
    int i, j;
    for(i = 1; i <= count_list(&ansList); i++) {
        for(j = i+1; j <= count_list(&ansList)-1; j++) {
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

void add_edge(Graph* G, int e, int x, int y) {
	G->L[x][e] = 1;
	G->L[y][e] = 1;
}

#define MAX_VERTICES 1000

int color[MAX_VERTICES];
int fail;

// To mau dinh bang phuong phap de quy
void colorize(Graph* G, int x, int c) {
	// Neu dinh x da chua co mau => to no
	if (color[x] == -1) {
		color[x] = c;
		List list = neighbors(G, x);
		int j;
		for (j = 1; j <= list.size; j++) {
			int y = element_at(&list, j);
			colorize(G, y, !c);
		} 
	} else {
		if (color[x] != c) // 1 dinh bi to 2 mau khac nhau
			fail = 1;
	}
}

int is_bigraph(Graph* G) {
	// Khoi tao color, chua dinh nao co mau
	int j;
	for (j = 1; j <= G->n; j++) {
		color[j] = -1;
	}
	fail = 0;
	colorize(G, 1, 0); // To mau dinh 1 bang mau den
	return !fail;
}

int main() {
	// Kiem tra ton tai chu trinh doi voi do thi vo huong
	
	Graph G;
	int e, j, u, v, w, n, m;
//	freopen("dt.txt","r",stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n, m);
	for (e = 1; e <= m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, e, u, v);
	}
	
	if (is_bigraph(&G)) {
		int i;
		for (i = 1; i <= G.n; i++) {
			if (!color[i]) {
				printf("%d ", i);
			}
		}
		printf("\n");
		for (i = 1; i <= G.n; i++) {
			if (color[i]) {
				printf("%d ", i);
			}
		}		
	}
	else
		printf("IMPOSSIBLE");
	
	return 0;
}
