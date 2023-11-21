#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "GSet.h"

struct GSet_t {
    int members;
    int count;
    GCopySetElements copyElement;
    GFreeSetElements freeElement;
    GCompareSetElements compareElements;
    GSetElement iterator;
    GSetElement *elements;
};


GSet gsetCreate(GCopySetElements copyElement, GFreeSetElements freeElement, GCompareSetElements compareElements){
    if (copyElement==NULL || freeElement==NULL || compareElements==NULL) {
        return NULL;
    }
    GSet gset = (GSet)malloc(sizeof(struct GSet_t));
    if (gset==NULL) {
        return NULL;
    } else {
        gset->members = 0;
        gset->count = 0;
        gset->copyElement = copyElement;
        gset->freeElement = freeElement;
        gset->compareElements = compareElements;
        gset->iterator = NULL;
        gset->elements = (GSetElement*)malloc(sizeof(GSetElement)*(gset->members));
    }
    return gset;
}

GSet gsetCopy(GSet set) {
    if (set==NULL) {
        return NULL;
    } else {
        GSet gset = (GSet)malloc(sizeof(struct GSet_t));
        if (gset==NULL) {
            return NULL;
        } else {
            gset->members = set->members;
            gset->count = set->count;
            gset->copyElement = set->copyElement;
            gset->freeElement = set->freeElement;
            gset->compareElements = set->compareElements;
            GSetElement* elements = (GSetElement*)malloc(sizeof(GSetElement)*(gset->members));
            if (elements==NULL) {
                return NULL;
            }
            for (int i=0;i<gset->members;i++) {
                elements[i] = gset->copyElement(set->elements[i]);
            }
            gset->elements = elements;
            gset->iterator = gset->elements[gset->count];
            return gset;
        }
    }
}

void gsetDestroy(GSet set) {
    if (set == NULL) {
            return;
    } else {
        for (int i=0;i<set->members;i++) {
            set->freeElement(set->elements[i]);
        }
        free(set->elements);
        free(set);
    }
}

int gsetGetSize(GSet set){
    return set->members;
}

bool gsetIsIn(GSet set, GSetElement element){
    bool result = false;
    for (int i=0;i<set->members;i++) {
        if (set->compareElements(set->elements[i],element)==0){
            result = true;
        }
    }
    return result;
}

GSetElement gsetGetFirst(GSet set) {
    if (set==NULL) {
        return NULL;
    }
    if (set->members==0) {
        return NULL;
    }
    int count = 0;
    for (int i=0;i<set->members;i++) {
        if (set->compareElements(set->elements[count],set->elements[i])>0){
            count = i;
        }
    }
    set->count = count;
    set->iterator = set->elements[count];
    return set->iterator;
}

GSetElement gsetGetNext(GSet set) {
    if (set==NULL){
        return NULL;
    }
    int count=0;
    for (int i=0;i<set->members;i++){
        if (set->compareElements(set->elements[i],set->elements[count])>0) {
            count = i;
        }
    }
    if (count == set->count) {
        return NULL;
    }
    for (int i=0;i<set->members;i++) {
        if (set->compareElements(set->elements[i],set->elements[count])<0){
            if (set->compareElements(set->iterator,set->elements[count])<0){
                count = i;
            }
        }
    }
    set->count = count;
    set->iterator = set->elements[count];
    return set->iterator;
}

GSetElement gsetGetCurrent(GSet set) {
    if (set==NULL || set->members==0) {
        return NULL;
    }
    return set->iterator;
}

GSetResult gsetAdd(GSet set, GSetElement element) {
    GSetResult result = GSET_SUCCESS;
    if (set==NULL || element==NULL) {
        result = GSET_NULL_ARGUMENT;
        return result;
    }
    GSetElement* np = (GSetElement*)realloc(set->elements,sizeof(GSetElement)*(set->members+1));
    if (np==NULL) {
        result = GSET_OUT_OF_MEMORY;
        return result;
    }
    set->members += 1;
    set->elements = np;
    set->elements[set->members-1] = element;
    return result;
}

GSetResult gsetRemove(GSet set, GSetElement element) {
    GSetResult result = GSET_SUCCESS;
    if (set==NULL || element==NULL) {
        result = GSET_NULL_ARGUMENT;
        return result;
    }
    int target = -1;
    for (int i=0;i<set->members;i++) {
        if (set->compareElements(set->elements[i],element)==0) {
            target = i;
        }
    }
    if (target==-1) {
        result = GSET_ITEM_DOES_NOT_EXIST;
        return result;
    }
    GSetElement* tp=(GSetElement*)malloc(sizeof(GSetElement)*(set->members-1));
    int k =0;
    for (int i=0;i<set->members;i++) {
        if (i==target) {
            k += -1;
        } else {
            tp[i+k] = set->copyElement(set->elements[i]);
        }
    }
    for (int i=0;i<set->members;i++) {
        set->freeElement(set->elements[i]);
    }
    free(set->elements);
    set->elements = tp;
    set->members--;
    set->count = -1;
    set->iterator = NULL;
    return result;
}

GSetResult gsetClear(GSet set) {
    GSetResult result = GSET_SUCCESS;
    if (set==NULL) {
        result = GSET_NULL_ARGUMENT;
        return result;
    }
    for (int i=0;i<set->members;i++) {
        set->freeElement(set->elements[i]);
    }
    free(set->elements);
    set->members = 0;
    set->count = -1;
    set->elements = NULL;
    set->iterator = NULL;
    return result;
}

GSet gsetFilter(GSet set, GFilterFunction func, GFilterKey key) {
    GSet nset = (GSet)malloc(sizeof(struct GSet_t));
    if (nset == NULL || func==NULL) {
        return NULL;
    }
    nset->compareElements = set->compareElements;
    nset->copyElement = set->copyElement;
    nset->freeElement = set->freeElement;
    int members = 0;
    for (int i=0;i<set->members;i++) {
        if (func(set->elements[i],key)==true) {
            members ++;
        }
    }
    nset->members = members;
    nset->elements = (GSetElement*)malloc(sizeof(GSetElement)*members);
    int p1 = 0;
    for (int i=0;i<set->members;i++) {
        if (func(set->elements[i],key)==true) {
            nset->elements[p1] = set->copyElement(set->elements[i]);
            p1++;
        }
    }
    nset->iterator=NULL;
    nset->count=-1;
    return nset;
}
