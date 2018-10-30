/*
 * main0.c
 * COMP 2160 Programming Practices
 * Assignment 4
 */

#include <stdio.h>
#include "ObjectManager.h"

int main(int argc, char *argv[])
{
  char *ptr;
  int i;
  Ref id1,id2,id3;
  initPool();

  id1= insertObject(100);
  fprintf(stdout,"id1 = %lu\n", id1); //SF
  fprintf(stdout,"doing retrieve object in main.c\n"); //SF
  ptr = (char*)retrieveObject(id1);
  fprintf(stdout,"ptr = %s\n", ptr); //SF
  
  for (i = 0; i < 100; i++)
    ptr[i] = (char)(i%26 + 'A');

  id2 = insertObject(4000);
  fprintf(stdout,"id2 = %lu\n", id2); //SF

  id3 = insertObject(20200);
  fprintf(stdout,"id3 = %lu\n", id3); //SF

  dropReference(id3);
  id3 = insertObject(10);
  fprintf(stdout,"id3 = %lu\n", id3); //SF

  ptr = (char*)retrieveObject(id1);
  for (i = 0; i < 100; i++)
    fprintf(stdout,"%c",ptr[i]);
  fprintf(stdout,"\n");

  dumpPool();
  destroyPool();
  fprintf(stdout,"---\n");

  return 0;
}

