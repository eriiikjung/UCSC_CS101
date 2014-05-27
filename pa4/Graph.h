// Rahul Palamutam, rpalamut@ucsc.edu
// Programming Assignment 4
// $Id: Graph.h,v 1.3 2014-02-25 09:31:15-08 - - $

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"
#define INF -255
#define NIL -254

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/ 
// returns a Graph pointing to newly created GraphObj
Graph newGraph(int n); 
// frees a;; dynamic memory associated with Graph *pG
void freeGraph(Graph* pG); 

 

/*** Access functions ***/ 
// returns Order field values
int getOrder(Graph G); 
// returns size field value
int getSize(Graph G);
// returns source vertex most recently used in function BFS()
// or NIL if BFS() has not yet been called 
int getSource(Graph G); 
// return the parent of vertex u in the BFS tree
// or NIL if BFS() has not yet been called
// Pre : 1 <= U <= getOrder(G)
int getParent(Graph G, int u); 
//returns distance from most recent BFS source to vertex u
// Pre : 1 <= U <= getOrder(G)
int getDist(Graph G, int u); 
// appends to List L the vertices of shortest path in G from source to U
// or appends to L the value NIL if no such path exists
// Pre : getSource(G) != NIL
// Pre : 1 <= U <= getOrder()
void getPath(List L, Graph G, int u); 

/*** Manipulation procedures ***/
// deletes all edges of G restoring it to no edge state 
void makeNull(Graph G); 
// inserts a new edge joining u to v
// 1<= u | v < getOrder(G) 
void addEdge(Graph G, int u, int v);
// inserts a new directed edge from u to v
// v is added to the adjacency List of u
// 1<= u | v < getOrder(G) 
void addArc(Graph G, int u, int v);
//runs the BFS algorithm on the Graph G with source s 
void BFS(Graph G, int s); 

/*** Other operations ***/ 
// prints the adjacenct list representation of G
void printGraph(FILE* out, Graph G); 


#endif
