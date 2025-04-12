#include <stdlib.h>
#include <stdio.h>

//structura unui nod in lista de adiacenta
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

//structura grafului
typedef struct g {
    int v;
    int *vis;
    NODE **alst;
} GPH;

//structura stivei
typedef struct s {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

//adauga o muchie intre doua noduri
void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;
    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

//initializeaza un graf cu 'v' noduri
GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(sizeof(NODE *) * v);
    g->vis = malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

//creeaza o stiva cu capacitatea data
STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s) {
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

//parcurgere DFS care inregistreaza nodurile in stiva
void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest, i;
    printf("adauga %d muchii (de la 0 la %d)\n", edg_nr, nrv-1);
    for (i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

int canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g, nrv);
        for (int j = 0; j < nrv; j++) {
            DFS(g, s2, j);
            wipe(g, nrv);
            for (int k = 0; k <= s1->t; k++) {
                for (int l = 0; l <= s2->t; l++) {
                    if (s1->arr[k] == l && s2->arr[l] == k) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    int nrv;
    int edg_nr;
    
    printf("cate noduri are graful?");
    scanf("%d", &nrv);

    printf("cate muchii are graful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    int result = canbe(g, nrv, s1, s2);
    printf("Rezultat: %d\n", result);

    return 0;
}                                                                                                                                                                                                                                                                                                                     /*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
