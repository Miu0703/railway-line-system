#include <stdio.h>
#include <stdlib.h>

#include"Line.h"

pLine creatLine(unsigned int id, unsigned int stid1, unsigned int stid2) {
    pLine line = (pLine)malloc(sizeof(Line));
    if (line==NULL) {
        return NULL;
    }
    line->id = id;
    line->stops = 2;
    line->route = (unsigned int *)malloc(sizeof(int)*(line->stops));
    if (line->route==NULL) {
        free(line);
        return NULL;
    }
    line->route[0]=stid1;
    line->route[1]=stid2;
    return line;
}

lresult lineUpdate(pLine line, unsigned int stid, int position){
    lresult rslt = lSUCCESS;
    if (line ==NULL) {
        rslt = lLOSS_OF_ARGUMENT;
        return rslt;
    }
    unsigned int* np = (unsigned int *)realloc(line->route,sizeof(unsigned int)*(line->stops+1));
    if (np==NULL) {
        rslt = lMEMORY_ERROR;
        return rslt;
    }
    line->route = np;
    if (position>line->stops) {
        line->route[line->stops+1] = stid;
    } else {
        for (int i=line->stops;i>=(position-1);i--) {
            if (i==(position-1)) {
                line->route[i] = stid;
                break;
            } else {
                line->route[i] = line->route[i-1];
            }
        }
    }
    return rslt;
}

lresult lineDelete(pLine line){
    lresult rslt = lSUCCESS;
    if (line ==NULL) {
        rslt = lLOSS_OF_ARGUMENT;
        return rslt;
    }
    free(line->route);
    free(line);
    return rslt;
}