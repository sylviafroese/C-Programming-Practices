/*
 * NAME: Sylvia Froese
 * STUDENT NUMBER: 6203180
 * COURSE: COMP2160, SECTION A02
 * INSTRUCTOR: Yang Wang
 * ASSIGNMENT: Assignment 4
 * ObjectManager.c
 *
 * Object Manager source file
 */
#include <stdio.h>
#include <stdlib.h>
#include "ObjectManager.h"


/*
 * Note that we provide our entire interface via this object module
 * and completely hide our index (see course notes). This allows us to
 * change indexing strategies without affecting the interface to
 * everyone else.

 * This function tries to allocate a block of given size from our buffer.
 * It will fire the garbage collector as required.
 * We always assume that an insert always creates a new object...
 * On success it returns the reference number for the block of memory
 * allocated for the object.
 * On failure it returns NULL_REF (0)
*/
 
Ref insertObject( ulong size )
{

    NodePtr newNode;         // pointer to the newly allocated node

    ulong space_remaining;
  
   //if the size remaining on the buffer is equal to or more than what we need
   // insert the object into the buffer
   
    newNode = NULL;
   
    space_remaining = MEMORY_SIZE-1 - freePtr;
    if (space_remaining >= size)
       {
       if (freePtr == 0)
           {
	   // Create a new node for this object
	   // Add the node to the end of the linked list

           newNode = (NodePtr) malloc ((uchar) sizeof(struct Node));
           newNode->id = 1;
           newNode->size = size;
           newNode->refCnt = 1;
           newNode->offset = (newNode->offset) + size;
	   }
       else // freePtr > 0
            {
            while (newNode != NULL)
              {
              newNode = newNode->next;
              }
            // Create a new node for this object
	    // Add the node to the end of the linked list
            if (newNode == NULL)
              {
	       newNode = (NodePtr) malloc ((uchar) sizeof(struct Node));

               newNode->id = (newNode->id) + 1;
               newNode->size = (newNode->size) + size;
	       // refCnt property gets updated using the AddReference and DropReference functions.
               // Therefore we have no need to update it here when we create the node.
               newNode->offset = (newNode->offset) + size;
              }
           }
       // update freePtr appropriately
       freePtr = freePtr + size;
       fprintf(stdout,"Reference number %lu\n", freePtr);
       return freePtr;
       }
    else // if the memory size is not big enough, we need to compact the buffer
       {
        // compact not coded
       fprintf(stdout,"Need to compact buffer, but compact() not coded\n");
 
	return NULL_REF;
       }

}


// returns a pointer to the object being requested given by the reference id
// This function does not work and it is believed by the author that it is the cause of 
// a segmentation fault. 
void *retrieveObject( Ref ref )
{

  if (ref <= MEMORY_SIZE) 
    {
    return &BuffA[ref]; 
    }
  else // ref > MEMORY_SIZE , ie. we are past the end of the current buffer 
       // and unable to retrieve an object
    {
     return  NULL_REF; 
    }
}

// update our index to indicate that we have another reference to the given object
void addReference( Ref ref )
{
   NodePtr refObject;

   refObject = (NodePtr) retrieveObject(ref);
   refObject->refCnt = refObject->refCnt + 1;
 
}

// update our index to indicate that a reference is gone
void dropReference( Ref ref )
{
   NodePtr refObject;

   refObject = (NodePtr) retrieveObject(ref);
   refObject->refCnt = refObject->refCnt - 1;
   if (refObject->refCnt == 0)
      {
       refObject->next = refObject;
       free((void *)refObject);
      }

}


/* newList:
*    Calls malloc to allocate memory for a new list pointer.
* parameters:
*    none
* returns:
*    a pointer to the newly allocated list pointer
*/
ListPtr newList(void)
{
    ListPtr listPtr;         // pointer to the newly allocated node
    listPtr = (ListPtr) malloc ((ulong) sizeof(listPtr));
    *listPtr = NULL;
    return listPtr;
}



// initialize the object manager
void initPool()
{
  currBuf = BuffA;  // set which of the 2 arrays that is currently in use, start with BuffA
  head = newList(); // create empty linked list
  freePtr = 0;      // set freePtr = 0

}



// clean up the object manager (before exiting)
void destroyPool()
{
  NodePtr nodePtr;
  NodePtr next=NULL;

  nodePtr = *head;
  while (nodePtr->next != NULL)
  {
     nodePtr->next = next;
     free((void *) nodePtr);
  }

}


/* This function traverses the index and prints the info in each entry
 * corresponding to a block of allocated memory. You should print the
 * block's reference id, its starting address, and its size (in
 * bytes).
*/ 
void dumpPool()
{

  //variable head from InitPool() is the beginning of the linked list.

  NodePtr ptr;
  NodePtr obj;

  ptr = *head;  // initialize dump list pointer at start of object linked list

   while (ptr != NULL)  //traverse through linked list until end of list is reached
     {
     obj = (NodePtr) retrieveObject((Ref) &ptr);

     if (obj != NULL)  //if an object was retrieved, print out its node info
       {
        fprintf(stdout,"id = %lu", obj->id);
        fprintf(stdout,"size = %lu", obj->size);
        fprintf(stdout,"refCnt = %lu", obj->refCnt);
        fprintf(stdout,"offset = %lu\n\n", obj->offset);
       }

     else //if no object was not retrieved, print error message.
       {
       fprintf(stdout,"Error: No object was retrieved\n\n");
       }

       ptr++;

     } //end while

}

