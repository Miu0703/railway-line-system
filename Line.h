#include <stdio.h>
#include <stdlib.h>

typedef struct Line_t {
    unsigned int id;
    unsigned int* route;
    int stops;
}*pLine , Line;

typedef enum lresult_t {
    lSUCCESS,
    lMEMORY_ERROR,
    lLOSS_OF_ARGUMENT,
    lSTATION_ERROR,
    lLINE_ERROR,
} lresult;

pLine creatLine(unsigned int id, unsigned int stid1, unsigned int stid2);

lresult lineUpdate(pLine line, unsigned int stid, int position);

lresult lineDelete(pLine line);