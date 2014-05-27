// Rahul Palamutam, rpalamut@ucsc.edu
// Programming Assignment 5
// $Id: Graph.h,v 1.3 2014-03-10 11:36:19-07 - - $

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"
#define UNDEF -255
#define NIL 0

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 
// returns a Graph pointing to newly created GraphObj
Graph newGraph(int n); 
// frees all dynamic memory associated with Graph *pG
void freeGraph(Graph* pG); 
/*** Access functions ***/ 
// returns the number of vertices in G
int getOrder(Graph G); 
// returns size field value
int getSize(Graph G);
// return the parent of vertex u in the DFS tree
// or NIL if DFS() has not yet been called
// Pre : 1 <= U <= getOrder(G)
int getParent(Graph G, int u); 
// Pre : 1 <= U <= getOrder(G)
int getDiscover(Graph G, int u); 
// Pre : 1 <= U <= getOrder()
int getFinish(Graph G, int u); 

/*** Manipulation procedures ***/
// inserts a new edge joining u to v
// 1<= u | v < getOrder(G) 
void addEdge(Graph G, int u, int v);
// inserts a new directed edge from u to v
// v is added to the adjacency List of u
// 1<= u | v < getOrder(G) 
void addArc(Graph G, int u, int v);
//runs the DFS algorithm on the Graph G
//List s defines the order in which vertices will be processed
// DFS will store the vertices in order of decreasing finish times
// List S is both an input and output parameter
// Pre: getLength(s) == n 
// Pre: S contains some permutation of integers {1,2,...n}
// n = getOrder(G) 
void DFS(Graph G, List s); 

/*** Other operations ***/ 
// prints the adjacenct list representation of G
void printGraph(FILE* out, Graph G); 
// returns the transpose of Graph G
Graph transpose(Graph G);
// returns the copy of Graph G
Graph copyGraph(Graph G);

#endif
