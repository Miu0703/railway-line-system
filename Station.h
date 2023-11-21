#include <stdio.h>
#include <stdlib.h>

typedef struct station_t {
    char* name;
    unsigned int id;
    unsigned int platforms; 
} *pStat, Stat;

typedef enum result_t {
    SUCCESS,
    MEMORY_ERROR,
    LOSS_OF_ARGUMENT,
    STATION_ERROR,
    LINE_ERROR,
} result;

pStat createStation(char* name, unsigned int id, unsigned int platforms);

result deleStation(pStat stat);


