#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "GSet.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);

typedef struct dt
{
  int x1;
  int x2;
} *Dt;

GSetElement copyDt(GSetElement e)
{
    Dt e1=(GSetElement)e;

    if((Dt)e1==NULL)return NULL;
    Dt copy=malloc(sizeof(struct dt));
    if(!copy)return NULL;

    copy->x1=e1->x1;
    copy->x2=e1->x2;

    return copy;
}

void freeDt(GSetElement e)
{
    free(e);
}

int compareDt(GSetElement e1, GSetElement e2)
{
    Dt e11=(GSetElement)e1;
    Dt e22=(GSetElement)e2;

    if(e11->x1<e22->x1)return -1;
    if(e11->x1>e22->x1)return 1;

/* comparision is done according to the field x1.
   if x1 of e1 equals to x1 of e2 then the parameters are treated as equals.
   if x1 of e1 is smaller than x1 of e2 then e1 is smaller than e2.
   if x1 of e1 is bigger than x1 of e2 then e1 is bigger than e2.
*/
    return 0;
}

static bool equalGSet(GSetElement e1,GSetElement e2)
{
    if(!e1&&!e2)return true;
    if(!e1||!e2)return false;

    GSetElement ele2=gsetGetFirst(e2);

    GSetElement iterator=gsetGetFirst(e1);
    GSET_FOREACH(GSetElement,iterator,e1){
        if(compareDt(ele2,iterator)!=0)return false;
        ele2=gsetGetNext(e2);
    }
    if(!iterator&&!ele2)return true;
    if(!iterator||!ele2)return false;

    return true;
}

void test1() /* gsetCreate */
{
   GSet my_set=NULL;

   my_set=gsetCreate(NULL, freeDt, compareDt);
   ASSERT("1.1" , my_set == NULL);
   gsetDestroy(my_set);

   my_set=gsetCreate(copyDt, NULL, compareDt);
   ASSERT("1.2" , my_set == NULL);
   gsetDestroy(my_set);

   my_set=gsetCreate(copyDt, freeDt, NULL);
   ASSERT("1.3" , my_set == NULL);
   gsetDestroy(my_set);

   my_set=gsetCreate(copyDt, freeDt, compareDt);
   ASSERT("1.4" , my_set != NULL);

   int r1=gsetGetSize(my_set);
   ASSERT("1.5" , r1==0);

   gsetDestroy(my_set);

   printf("\n");
}

void test2() /* gsetCopy */
{
    ASSERT("2.1" ,gsetCopy(NULL)==NULL);

    GSet empty = gsetCreate(copyDt,freeDt,compareDt);
    GSet emptyCopy = gsetCopy(empty);
    ASSERT("2.2" ,equalGSet(empty,emptyCopy));
    gsetDestroy(emptyCopy);
    gsetDestroy(empty);
/*
    GSet set = gsetCreate(copyDt,freeDt,compareDt);
    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    struct dt Dt2 = {.x1 = 2, .x2 = 3};
    Dt t1=&Dt1;
    Dt t2=&Dt2;
    gsetAdd(set,t1);
    gsetAdd(set,t2);
    GSet copy = gsetCopy(set);
    ASSERT("2.3" ,equalGSet(copy,set));

    struct dt Dt3 = {.x1 = 4, .x2 = 5};
    Dt t3=&Dt3;
    gsetAdd(set,t3);
    ASSERT("2.4" ,!equalGSet(copy,set));

    gsetDestroy(copy);
    gsetDestroy(set);
*/
    printf("\n");
}

void test3()/* gsetDestroy */
{
    return;
}

void test4()/* gsetGetSize */
{
   GSet my_set=NULL;
   int r1=gsetGetSize(my_set);
   ASSERT("4.1" , r1==-1);
   gsetDestroy(my_set);

   my_set=gsetCreate(copyDt, freeDt, compareDt);
   int r2=gsetGetSize(my_set);
   ASSERT("4.2" , r2==0);


   struct dt Dt1 = {.x1 = 0, .x2 = 1};
   Dt t1=&Dt1;
   gsetAdd(my_set,t1);
   int r3=gsetGetSize(my_set);
   ASSERT("4.3" , r3==1);

   gsetDestroy(my_set);

   printf("\n");
}

void test5()/* gsetIsIn */
{
    GSet my_set=NULL;
    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;
    ASSERT("5.1" ,gsetIsIn(my_set,t1)==false);
    gsetDestroy(my_set);

    my_set=gsetCreate(copyDt, freeDt, compareDt);
    gsetAdd(my_set,t1);
    ASSERT("5.2" ,gsetIsIn(my_set,t1)==true);

    struct dt Dt2 = {.x1 = 2, .x2 = 3};
    Dt t2=&Dt2;
    ASSERT("5.3" ,gsetIsIn(my_set,t2)==false);

    gsetDestroy(my_set);

    printf("\n");
}

void test6()/* gsetGetFirst */
{
    GSet my_set=NULL;
    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;

    ASSERT("6.1" ,gsetGetFirst(my_set)==NULL);
    gsetDestroy(my_set);

    my_set=gsetCreate(copyDt, freeDt, compareDt);
    ASSERT("6.2" ,gsetGetFirst(my_set)==NULL);

    gsetAdd(my_set,t1);
    ASSERT("6.3" ,compareDt(t1, gsetGetFirst(my_set))==0);

    struct dt Dt2 = {.x1 = 2, .x2 = 3};
    Dt t2=&Dt2;
    gsetAdd(my_set,t2);
    ASSERT("6.4" ,compareDt(t1, gsetGetFirst(my_set))==0);

    gsetDestroy(my_set);

    printf("\n");

}

void test7()/* gsetGetNext */
{
    GSet my_set=NULL;
    ASSERT("7.1" ,gsetGetNext(my_set)==NULL);
    gsetDestroy(my_set);

    my_set=gsetCreate(copyDt, freeDt, compareDt);
    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;
    gsetAdd(my_set,t1);
    Dt iter=gsetGetFirst(my_set);
    iter=gsetGetNext(my_set);
    ASSERT("7.2" ,iter==NULL);

    struct dt Dt2 = {.x1 = 2, .x2 = 3};
    Dt t2=&Dt2;
    gsetAdd(my_set,t2);

    iter=gsetGetFirst(my_set);
    iter=gsetGetNext(my_set);
    ASSERT("7.3" ,compareDt(t2, iter)==0);
    gsetDestroy(my_set);

    printf("\n");
}

void test8()/* gsetGetCurrent */
{
    GSet my_set=NULL;
    ASSERT("8.1" ,gsetGetNext(my_set)==NULL);
    gsetDestroy(my_set);

    my_set=gsetCreate(copyDt, freeDt, compareDt);
    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;
    gsetAdd(my_set,t1);
    Dt iter=gsetGetFirst(my_set);
    iter=gsetGetCurrent(my_set);
    ASSERT("8.2" ,compareDt(t1, iter)==0);

    gsetDestroy(my_set);

    printf("\n");
}

void test9()/* gsetAdd */
{

    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;
    GSet my_set=NULL;
    ASSERT("9.1" ,gsetAdd(my_set,t1)==GSET_NULL_ARGUMENT);
    gsetDestroy(my_set);

    my_set=gsetCreate(copyDt, freeDt, compareDt);
    gsetAdd(my_set,t1);
    ASSERT("9.2" ,compareDt(t1, gsetGetFirst(my_set))==0);

    gsetDestroy(my_set);

    printf("\n");
}

void test10()/* gsetRemove */
{
    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;
    GSet my_set=NULL;
    ASSERT("10.1" ,gsetRemove(my_set,t1)==GSET_NULL_ARGUMENT);
    gsetDestroy(my_set);

    my_set=gsetCreate(copyDt, freeDt, compareDt);
    ASSERT("10.2" , gsetRemove(my_set,t1)==GSET_ITEM_DOES_NOT_EXIST);

    gsetAdd(my_set,t1);
    gsetRemove(my_set,t1);
    int r1=gsetGetSize(my_set);
    ASSERT("10.3" , r1==0);

    gsetDestroy(my_set);

    printf("\n");

}

void test11()/* gsetClear */
{
    GSet my_set=NULL;
    ASSERT("11.1" ,gsetClear(my_set)==GSET_NULL_ARGUMENT);
    gsetDestroy(my_set);

    struct dt Dt1 = {.x1 = 0, .x2 = 1};
    Dt t1=&Dt1;
    my_set=gsetCreate(copyDt, freeDt, compareDt);
    gsetAdd(my_set,t1);
    gsetClear(my_set);
    int r1=gsetGetSize(my_set);
    ASSERT("11.2" , r1==0);

    gsetDestroy(my_set);

    printf("\n");
}

static bool IsEqual(GSetElement e, GFilterKey key)
{
    Dt e1=(GSetElement)e;
    return e1->x1!=*(int*)key;
}

void test12()/* gsetFilter */
{
   GSet set=gsetCreate(copyDt, freeDt, compareDt);
   struct dt Dt1 = {.x1 = 2, .x2 = 1};
   struct dt Dt2 = {.x1 = 0, .x2 = 3};
   Dt t1=&Dt1;
   Dt t2=&Dt2;
   gsetAdd(set,t1);
   gsetAdd(set,t2);

   int x1_value=0;
   GSet my_set=NULL;
   my_set=gsetFilter(NULL,IsEqual,&x1_value);
   ASSERT("12.1" , my_set == NULL);
   gsetDestroy(my_set);

   my_set=gsetFilter(set,NULL,&x1_value);
   ASSERT("12.2" , my_set == NULL);
   gsetDestroy(my_set);


   my_set=gsetFilter(set,IsEqual,&x1_value);
   ASSERT("12.3" ,compareDt(t1, gsetGetFirst(my_set))==0);

   gsetDestroy(my_set);
   gsetDestroy(set);
   printf("\n");
}

int main(int argc, char **argv)
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();

  return 0;
}

