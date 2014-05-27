// Rahul Palamutam, rpalamut@ucsc.edu
// Programming Assignment 4
// $Id: Graph.c,v 1.4 2014-02-26 03:00:50-08 - - $

#include <stdlib.h>

#include "Graph.h"

static void insertsort(List L, int u);

#define WHITE 10000001
#define BLACK 19999991
#define GRAY  -6666669
struct GraphObj {
  List *array;
  int *colors;
  int *parents;
  int *distances;
  int order; // number of vertices
  int size; // number of edges
  int source; 
};



//Returns a Graph pointing to a newly created GraphObj
//representing a graph with n vertices and no edges
Graph newGraph(int n){ 
  Graph new = malloc(sizeof(struct GraphObj)); 
  new->array = calloc (n + 1, sizeof(List)); 
  new->colors = calloc(n + 1, sizeof(int)); 
  new->parents = calloc(n + 1, sizeof(int)); 
  new->distances = calloc(n + 1, sizeof(int));

  new->source = NIL;// none of the actual labels were recently used
  new->order = n; // n vertices
  new->size = 0; // no edges
  for (int i = 0; i < n + 1; i++){
    new->array[i] = newList();
    new->colors[i] = WHITE;
    new->parents[i] = NIL; // no parents as of yet
    new->distances[i] = INF; // no edges so no distances
  }
  return new;
} 
// frees all dynamic memory associated with Graph 
void freeGraph(Graph* pG){
  Graph freed = *pG; 
  for(int i = 0; i < (freed->order) + 1; i++){
    freeList(&(freed->array[i]));
  }
  free(freed->array); 
  free(freed->colors); 
  free(freed->parents); 
  free(freed->distances); 
  free(*pG);
  *pG = NULL; 
} 

 

/*** Access functions ***/
// returns the number of vertices
int getOrder(Graph G){
  return G->order;
}
// returns the number of edges
int getSize(Graph G){
  return G->size;
}
// returns the source vertex
int getSource(Graph G){
  return G->source;
}
// returns the parent vertex of the chosen vertex
int getParent(Graph G, int u){
  if(u < 1 || u > getOrder(G)){
    printf("getParent: invalid u parameter");
    return 0;
  }
  return G->parents[u];
}

// returns the distance of the vertex from source 
int getDist(Graph G, int u){
  if(getSource(G) == NIL){
    return INF;
  }
  if(u < 1 || u > getOrder(G)){
    printf("getDist: invalid u parameter");
    return 0;
  }
  return G->distances[u];
}
 
// computes the shortest path from vertex to source
void getPath(List L, Graph G, int u){
  if(getSource(G) == NIL){
    printf("Source is NIL. Please call BFS()");
  }
  if(u < 1 || u > getOrder(G)){
    printf("getPath: invalid u parameter");
    return;
  }
  int s = G->source;
  if (u == s){
    prepend(L, s);
    return;
  } else if (G->parents[u] == NIL) {
    append(L, NIL);
  } else {
    prepend(L,u);
    getPath(L, G, G->parents[u]);
  }
} 

/*** Manipulation procedures ***/ 
// clear's all the edges
void makeNull(Graph G){
  for(int i = 0; i < G->order + 1; i++){
    clear(G->array[i]);
  } 
}

// creates an edge between vertices
// precondition, the vertex numbers must be > 1 and < getOrder(G) 
void addEdge(Graph G, int u, int v){
  if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Addedge: preconditions not met\n");
    printf("%d %d\n", u, v);
    return;
  }
  List U = G->array[u];
  List V = G->array[v];
  insertsort(U, v);
  insertsort(V, u);
}

// private function to append vertices in adjacency list in order
static void insertsort(List L, int u){
  if (length(L) == 0){
    append(L, u);
    return;
  }
  for(moveTo(L, 0); getIndex(L) >= 0; moveNext(L)){
    int big = getElement(L);
    if(u < big){
      insertBefore(L, u);
      break;
    }
  }
  if(getIndex(L) == -1){
    append(L, u);
  }
}
 
// adds a directed edge
void addArc(Graph G, int u, int v){
  if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Addarc: preconditions not met");
  }
  List U = G->array[u];
  insertsort(U, v);
}
 
// BFS algorithm
void BFS(Graph G, int s){
  for (int u = 0; u < G->order + 1; u++){
    if(u != s){
      G->colors[u] = WHITE;
      G->distances[u] = INF;
      G->parents[u] = NIL;
    }
  }
  // sets the source vetex
  G->source = s;
  G->colors[s] = GRAY;
  G->distances[s] = 0;
  G->parents[s] = NIL;
  // creates List object as Q
  List Q = newList();
  prepend(Q, s);
  while(length(Q) > 0){
    int u = back(Q);
    deleteBack(Q);
    List adj = G->array[u];
    // sets all other vertex attributes in relation to source vertex
    for(moveTo(adj, 0);getIndex(adj) >= 0 ; moveNext(adj)){
      int vertex = getElement(adj);
      if(G->colors[vertex] == WHITE){
	G->colors[vertex] = GRAY;
	G->distances[vertex] = G->distances[u] + 1;
	G->parents[vertex] = u;
	prepend(Q, vertex);
      }
    }
    // vertex is now discovered
    G->colors[u] = BLACK;
  }
  // frees the temporary queue
  freeList(&Q);
} 

/*** Other operations ***/ 
// print function to print the graph in pretty format
void printGraph(FILE* out, Graph G){
  if(out == NULL || G == NULL){
    printf("Passed in NUll parameters");
    return;
  }

  for (int i = 1; i < getOrder(G) + 1; i++){
    fprintf(out, "%d: ", i);
    printList(out, G->array[i]);
    fprintf(out, "\n");
  }
}
 
