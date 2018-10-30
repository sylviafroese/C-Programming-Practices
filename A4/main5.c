/* 
 * main5.c
 * COMP 2160 Programming Practices
 * Assignment 4
 * 
 * A large program with lots of allocations and GC
 * compact should be called 7 times
 *
 * dumpPool should give something like this:
 *  Reference ID   starting addr.    size (Bytes)
 *       1001              0             272
 *       2252            272             272
 *       3503            544             272
 *       4754            816             272
 *       6005           1088             272
 *       8256           1360             272
 *       9507           1632             272
 *      10758           1904             272
 *      12009           2176             272
 *      13260           2448             272
 *      15511           2720             272
 *      16762           2992             272
 *      18013           3264             272
 *      19264           3536             272
 *      20515           3808             272
 *      22766         276080             272
 *      24017         276352             272
 *      25268         276624             272
 *      26519         276896             272
 *      27770         353168             272
 */

#include "ObjectManager.h"
#include <stdio.h>

#define OBJECTS 1000

typedef struct LUCKY{
  int value1;
  int value2;
}lucky;

typedef struct ALF{
  double value;
  double day;
  char buffer[256];
}alf;

void subTester( const Ref obj, const Ref objects[] ){
  int i;
  Ref more[OBJECTS/4];
  for( i = 0; i < OBJECTS/4; i++)
    more[i] = insertObject(sizeof(alf));

  for ( i=0 ; i<OBJECTS ; i++ )
    fprintf( stdout, "lucky object %d: %d %d\n", i, 
    ((lucky *)retrieveObject(objects[i]))->value1, 
    ((lucky *)retrieveObject(objects[i]))->value2 );

  ((alf *)retrieveObject(obj))->value = 2.71719;
  for( i = 0; i < OBJECTS/4; i++)
    dropReference(more[i]);
}// subTester

void tester(){
  int i;
  Ref test = insertObject(sizeof(alf));
  Ref objects[OBJECTS];

  for ( i=0 ; i<OBJECTS ; i++ ){
    objects[i] = insertObject(sizeof(lucky));
    ((lucky *)retrieveObject(objects[i]))->value1 = i;
    ((lucky *)retrieveObject(objects[i]))->value2 = i*2;
  }

  ((alf *)retrieveObject(test))->value = 3.14159;
  
  fprintf( stdout, "before: %2.5f\n", ((alf *)retrieveObject(test))->value );

  subTester( test, objects );

  fprintf( stdout, "after: %2.5f\n", ((alf *)retrieveObject(test))->value );
  for ( i=0 ; i<OBJECTS ; i++ )
    dropReference(objects[i]);
}// tester

void initialTester(){
  int i;
  // lets keep a bunch of objects around for a while...
  Ref objects[OBJECTS];
  for(i = 0; i < OBJECTS; i++)
    objects[i] = insertObject(sizeof(alf));

  for ( i=0 ; i<5 ; i++ )
    tester();
  for(i = 0; i < OBJECTS; i++)
    dropReference(objects[i]);
}// tester

int main( int argc, char *argv[] ){
  int i;  
  initPool();

  for ( i=0 ; i<4 ; i++ ){
    initialTester();
  }
  dumpPool();
  destroyPool();
  
  return 0;
}// main
