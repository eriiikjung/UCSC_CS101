// Rahul Palamuttam, rpalamut@ucsc.edu
// Programming Assignment 4
// $Id: FindPath.c,v 1.1 2014-02-26 03:00:50-08 - - $

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Graph.h"
#define MAX_LEN 165

int main (int argc, char* argv[]){
  // temporary string holder
  char line[MAX_LEN];
  // checks for correct command line inputs
  if(argc != 3) {
    printf("Invalid number of inputs");
    exit(1);
  }

  // opens the file
  FILE* input = fopen(argv[1], "r");
  FILE* output = fopen(argv[2], "w");

  // checks if files have been open and or created
  if(input == NULL){ 
    printf("Unable to open file %s for reading\n", argv[1]);
    return 1;
  } else if (output == NULL){
    printf("Unable to open file %s for reading\n", argv[2]);
    return 1;
  }
    
  // read each line of input file, then count and print tokens
  fgets(line, MAX_LEN, input);
  int numVertex = 0;
  sscanf(line, "%d", &numVertex);
  
  // Graph creation
  Graph G = newGraph(numVertex);
  while( fgets(line, MAX_LEN, input) != NULL) {
    int vert1 = 0;
    int vert2 = 0;
    sscanf(line, "%d %d", &vert1, &vert2);
    if(vert1 == 0 && vert2 == 0) break;
    addEdge(G, vert1, vert2);
  }
  printGraph(output, G);
  // print path and compute distances
  List L;
  // this is just to elminate the starting newline
  int start = 0;
  while(fgets(line, MAX_LEN, input) != NULL) {
    int vert1 = 0;
    int vert2 = 0;
    start ++;
    sscanf(line, "%d %d", &vert1, &vert2);

    if(vert1 == 0 && vert2 == 0) break;
    if(start != 1) fprintf(output, "\n");
    fprintf(output, "\n");
    BFS(G, vert1);
    int dist = getDist(G, vert2);
    fprintf(output, "The distance from %d to %d is ", vert1, vert2);
    if(dist == -255) {
      fprintf(output, "infinity\n");
    } else {
      fprintf(output, "%d\n", dist);
    }
    L = newList();
    getPath(L, G, vert2);
    if(front(L) == -254){
      fprintf(output, "No %d-%d path exists", vert1, vert2);
    } else {
      fprintf(output, "A shortest %d-%d path is: ", vert1, vert2);
      printList(output, L);
    }


    freeList(&L);
  }
  // frees all the necessary items
  fprintf(output, "\n");
  freeGraph(&G);
  fclose(input);
  fclose(output);
  return(0);
}
