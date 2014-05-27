// Rahul Palamuttam, rpalamut@ucsc.edu
// Programming Assignment 2
// $Id: Lex.c,v 1.2 2014-01-19 18:12:14-08 - - $

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "List.h"

#define MAX_LEN 160

// carries out a variation of the insertion sort
List insertsort(char array[][MAX_LEN], int length){
  // makes a new list object
  List list = newList();

  // appends first element
  if (length > 0) append(list, 0);
  for (int j = 1; j < length; j++){
    char *temp = array[j];
    int index = j - 1;
    //move cursor to current position
    moveTo(list, index);
    
    //sorting
    while (index > -1 && strcmp(temp, array[getElement(list)]) < 1){
      index--;
      movePrev(list);
    }
    
    // if cursor is null, then prepend
    // otherwise insert after it
    if(getIndex(list) == -1){
      prepend(list, j);
    } else {
      insertAfter(list, j);
    }
  }

  return list;
}


int main(int argc, char* argv[]){
  int count = 0;
  char line[MAX_LEN];
  char tokenlist[MAX_LEN];
  char strings[count][MAX_LEN];
  char *token;

  if(argc != 3) {
    printf("Invalid number of inputs");
    exit(1);
  }
  
  FILE* input = fopen(argv[1], "r");
  FILE* output = fopen(argv[2], "w");

  if(input == NULL){ 
    printf("Unable to open file %s for reading\n", argv[1]);
    return 1;
  } else if (output == NULL){
    printf("Unable to open file %s for reading\n", argv[2]);
    return 1;
  }

  // read each line of input file, then count and print tokens
  while( fgets(line, MAX_LEN, input) != NULL) {
    count++;
  }

  // close and reopen file to reset fgets
  fclose(input);
  input = fopen(argv[1], "r");

  for(int i = 0; fgets(line, MAX_LEN, input) != NULL; i++){
    token = strtok(line, "\n");
    tokenlist[0] = '\0';

    while(token != NULL){
      strcat(tokenlist, token);
      token = strtok(NULL, " \n");
      
    // appends new lines to the end of every line
      strncat(tokenlist, "\n", 10);
    }

    strcpy(strings[i], tokenlist);
  }

  
  List list = insertsort(strings, count);
  for(moveTo(list, 0); getIndex(list) >= 0; moveNext(list)){
    fprintf(output, "%s", strings[getElement(list)]);
  }

  //close files
  fclose(input);
  fclose(output);

  return(0);
}
