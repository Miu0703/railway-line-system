#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Station.h"

pStat createStation(char* name, unsigned int id, unsigned int platforms) {
    pStat stat = (pStat)malloc(sizeof(Stat));
    if (stat==NULL) {return NULL;}
    stat->name = (char *)malloc(strlen(name));
    if (stat->name==NULL) {return NULL;}
    strcpy(stat->name,name);
    stat->id = id;
    stat->platforms = platforms;
    return stat;
}

result deleStation(pStat stat) {
    result rslt = SUCCESS;
    if (stat==NULL) {
        rslt = LOSS_OF_ARGUMENT;
        return rslt;
    }
    free(stat->name);
    free(stat);
    return rslt;
}