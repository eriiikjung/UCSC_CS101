// Rahul Palamuttam, rpalamut@ucsc.edu
// Programming Assignment 2 : Lex
// $Id: GraphTest.c,v 1.3 2014-02-26 03:00:50-08 - - $


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  


   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){ 
     if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }
   
   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveTo(E,0);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = getElement(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");
   printf("--------------This concludes the given test by professor\n");
   // recomputes BFS with source vertex
   BFS(G, 2);
   clear(C);
   clear(P);
   getPath(C, G, 35);
   getPath(P, G, 2);
   // prints out computed paths and distances
   printf("The path from source to vertex 35(the source vertex): ");
   printList(stdout, C);
   printf("\nThe distance from source to vertex 35( the source vertex): ");
   printf("%d\n", getDist(G, 35));
   printf("\nThe path from source to vertex 2: ");
   printList(stdout, P);
   printf("\nThe distance from source to vertex 2( the source vertex): ");
   printf("%d\n", getDist(G, 2));
   printf("\n");
   
   // Free objects
   
   clear(C);
   clear(P);
   freeGraph(&G);
   //re-build graph G
   n = 100;
   G = newGraph(n);
   for(i = 1; i<n; i++){
     if(i%10 !=0) addEdge(G,i,i+1);
     if(i<=50) addArc(G, i, i+10);
   }
   addArc(G,9,31);
   addEdge(G,17,13);
   addArc(G,14,33);
   
   // recomputes BFS with source vertex
   BFS(G, 50);

   getPath(C, G, 50);
   getPath(P, G, 99);
   printGraph(stdout, G);
   printf("The path from source to vertex 50(the source vertex):");
   printList(stdout, C);
   printf("\nThe distance from source to vertex 50 (the source vertex):");
   printf("%d\n", getDist(G, 50));
   printf("\nThe path from source to vertex 99: ");
   printList(stdout, P);
   printf("\nThe distance from source to vertex 99: ");
   printf("%d\n", getDist(G,99));
   printf("\n");

   freeList(&C);

   
   freeList(&P);

   
   freeList(&E);
   freeGraph(&G);
   
   return(0);
}
