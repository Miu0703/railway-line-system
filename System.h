#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Station.h"
#include "Line.h"

typedef struct System_t
{
    char* name;
    pStat* stations;
    pLine* lines;
    int num_of_stat;
    int num_of_line;
} *pSys, Sys;

pSys initial(char* sys_name);

result destroy(pSys);

result addStation(pSys system, char* name, unsigned int id, unsigned int platforms);

result deleteStation(pSys system,unsigned int id);

result addLine(pSys system,unsigned int lineid, unsigned int stid1, unsigned stid2);

result updateLine(pSys system,unsigned int lineid, unsigned int stid, int position);

result removeLine(pSys system,unsigned int lineid);

result showLineByStation(pSys system,unsigned int stid);

result showSingleStation(pSys system);

result showLine(pSys system, unsigned int lineid);

void showSystem(pSys system);

void bubleSort(unsigned int* data, int n);












