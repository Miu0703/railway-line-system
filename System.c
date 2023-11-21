#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "System.h"

pSys initial(char* sys_name) {
    pSys system = (pSys)malloc(sizeof(Sys));
    if (system==NULL) {
        return NULL;
    }
    system->name = (char*)malloc(sizeof(char)*strlen(sys_name));
    strcpy(system->name,sys_name);
    system->num_of_line = 0;
    system->num_of_stat = 0;
    system->stations = (pStat*)malloc(sizeof(pStat)*0);
    system->lines = (pLine*)malloc(sizeof(pLine)*0);
    return system;
}

result destroy(pSys system) {
    result rslt = SUCCESS;
    if (system==NULL) {
        return rslt;
    }
    for (int i=0; i<system->num_of_stat; i++) {
        deleStation(system->stations[i]);
    }
    for (int j=0; j<system->num_of_line; j++) {
        lineDelete(system->lines[j]);
    }
    free(system->name);
    free(system->lines);
    free(system->stations);
    free(system);
    return rslt;
}

result addStation(pSys system, char* name, unsigned int id, unsigned int platforms) {
    result rslt = SUCCESS;
    if (system == NULL) {
        rslt = LOSS_OF_ARGUMENT;
        return rslt;
    }
    pStat* np = (pStat*)realloc(system->stations,sizeof(pStat)*(system->num_of_stat+1));
    if (np==NULL) {
        rslt = MEMORY_ERROR;
        return rslt;
    }
    system->stations = np;
    system->num_of_stat += 1;
    system->stations[system->num_of_stat-1] = createStation(name, id,platforms);
    return rslt;
}

result deleteStation(pSys system, unsigned int id) {
    result rslt = SUCCESS;
    if (system == NULL) {
        rslt = LOSS_OF_ARGUMENT;
        return rslt;
    }
    int k =0;
    for (int i=0; i<system->num_of_stat-1; i++) {
        if (system->stations[i]->id == id) {
            deleStation(system->stations[i]);
            k = 1;
        }
        if (k==1) {
            system->stations[i] = system->stations[i+1];
        }
    }
    if (k==0) {
        rslt = STATION_ERROR;
        return rslt;
    }
    system->stations[system->num_of_stat-1]=NULL;
    system->num_of_stat -= 1;
    return rslt;
}

result addLine(pSys system, unsigned int lineid, unsigned int stid1, unsigned stid2) {
    result rslt = SUCCESS;
    if (system == NULL) {
        rslt = LOSS_OF_ARGUMENT;
        return rslt;
    }
    pLine* np = (pLine*)realloc(system->lines,sizeof(pLine)*(system->num_of_line+1));
    if (np==NULL) {
        rslt = MEMORY_ERROR;
        return rslt;
    }
    system->lines = np;
    system->num_of_line += 1;
    system->lines[system->num_of_line-1] = creatLine(lineid, stid1, stid2);
    return rslt;
}

result updateLine(pSys system, unsigned int lineid, unsigned int stid, int position){
    result rslt = SUCCESS;
    if (system == NULL) {
        rslt = LOSS_OF_ARGUMENT;
        return rslt;
    }
    int k=0;
    for (int i=0; i<system->num_of_line; i++){
        if (system->lines[i]->id == lineid) {
            k =1;
            lineUpdate(system->lines[i],stid,position);
            break;
        }
    }
    if (k==0) {
        rslt = LINE_ERROR;
        return rslt;
    }
    return rslt;
}

result removeLine(pSys system, unsigned int lineid) {
    result rslt = SUCCESS;
    if (system == NULL) {
        rslt = LOSS_OF_ARGUMENT;
        return rslt;
    }
    int k =0;
    for (int i=0; i<system->num_of_line-1; i++) {
        if (system->lines[i]->id == lineid) {
            lineDelete(system->lines[i]);
            k = 1;
        }
        if (k==1) {
            system->lines[i] = system->lines[i+1];
        }
    }
    if (k==0) {
        rslt = LINE_ERROR;
        return rslt;
    }
    system->lines[system->num_of_line-1]=NULL;
    system->num_of_line -= 1;
    return rslt;
}

result showLineByStation(pSys system, unsigned int stid) {
    result rslt = SUCCESS;
    if (system==NULL) {
        printf("Loss of system\n");
        rslt =  LOSS_OF_ARGUMENT;
        return rslt;
    }
    int isIn = 0;
    for (int i=0; i<system->num_of_stat; i++) {
        if (system->stations[i]->id == stid) {
            isIn = 1;
            break;
        }
    }
    if (isIn == 0) {
        rslt = STATION_ERROR;
        return rslt;
    }
    int count = 0;
    for (int i=0; i<system->num_of_line; i++) {
        for (int j=0; j<system->lines[i]->stops; j++) {
            if (system->lines[i]->route[j] == stid) {
                count++ ;
            }
        }
    }
    if (count==0) {
    } else {
        unsigned int* linelist = (unsigned int*)malloc(sizeof(unsigned int)*count);
        int cc = 0;
        for (int i=0; i<system->num_of_line; i++) {
            int cd = 0;
            for (int j=0; j<system->lines[i]->stops; j++) {
                if (system->lines[i]->route[j] == stid) {
                    cd ++;
                }
            }
            if (cd!=0) {
                linelist[cc] = system->lines[i]->id;
                cc++;
            }
        }
        bubleSort(linelist,count);
        for (int i=0; i<count; i++) {
            if (i==count-1) {
                printf("%d\n",linelist[i]);
            } else {
                printf("%d ", linelist[i]);
            }
        }
    }
    return rslt;
}

result showSingleStation(pSys system) {
    result rslt = SUCCESS;
    if (system==NULL) {
        printf("Loss of system\n");
        rslt =  LOSS_OF_ARGUMENT;
        return rslt;
    }
    int count = 0;
    for (int i=0; i<system->num_of_stat; i++) {
        unsigned int stid = system->stations[i]->id;
        int isIn=0;
        for (int i=0; i<system->num_of_line; i++){
            for (int j=0; j<system->lines[i]->stops; j++){
                if (system->lines[i]->route[j]==stid) {
                    isIn++;
                }
            }
        }
        if (isIn==0) {
            count++;
        }
    }
    if (count==0) {
        printf("No such station\n");
        return rslt;
    } else {
        unsigned int* statlist = (unsigned int*)malloc(sizeof(unsigned int)*count);
        int cd = 0;
        for (int i=0; i<system->num_of_stat; i++) {
            unsigned int stid = system->stations[i]->id;
            int isIn=0;
            for (int i=0; i<system->num_of_line; i++){
                for (int j=0; j<system->lines[i]->stops; j++){
                    if (system->lines[i]->route[j]==stid) {
                        isIn++;
                    }
                }
            }
            if (isIn==0) {
                statlist[cd] = stid;
                cd++;
            }
        }
        bubleSort(statlist,count);
        for (int i=0; i<count; i++) {
            if (i==count-1) {
                printf("%d\n",statlist[i]);
            } else {
                printf("%d ", statlist[i]);
            }
        }
    }
    return rslt;
}

result showLine(pSys system,unsigned int lineid) {
    result rslt = SUCCESS;
    if (system==NULL) {
        printf("Loss of system\n");
        rslt =  LOSS_OF_ARGUMENT;
        return rslt;
    }
    pLine line=NULL;
    for (int i=0; i<system->num_of_line; i++) {
        if (system->lines[i]->id==lineid) {
            line = system->lines[i];
        }
    }
    if (line==NULL) {
        printf("No such line\n");
        rslt = LINE_ERROR;
        return rslt;
    }
    int count = line->stops;
    for (int i=0; i<count; i++) {
        if (i==count-1) {
            printf("%d\n",line->route[i]);
        } else {
            printf("%d ",line->route[i]);
        }
    }
    return rslt;
}

void showSystem(pSys system) {
    if (system==NULL) {
        printf("Loss of system\n");
        return;
    } else {
        printf("%s\n",system->name);
    }
    int stnum = system->num_of_stat;
    int linenum = system->num_of_line;
    if (stnum!=0) {
        unsigned int* sts = (unsigned int *)malloc(sizeof(unsigned int)*stnum);
        for (int i=0; i<stnum; i++) {
            sts[i] = system->stations[i]->id;
        }
        bubleSort(sts,stnum);
        for (int i=0; i<stnum; i++) {
            if (i == stnum-1) {
                printf("%d\n",sts[i]);
            } else {
                printf("%d ",sts[i]);
            }
        }
        free(sts);
    }
    if (linenum!=0) {
        unsigned int* sts = (unsigned int *)malloc(sizeof(unsigned int)*linenum);
        for (int i=0; i<linenum; i++) {
            sts[i] = system->lines[i]->id;
        }
        bubleSort(sts,linenum);
        for (int i=0; i<linenum; i++) {
            if (i == linenum-1) {
                printf("%d\n",sts[i]);
            } else {
                printf("%d ",sts[i]);
            }
        }
        free(sts);
    }
    printf("Done\n");
    return;
}

void bubleSort(unsigned int* data, int n) {
    int i,j,temp;
    for(j=0;j<n-1;j++) {
        for(i=0;i<n-j-1;i++) {
            if(data[i]>data[i+1]) {
                temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;
            }
        }
    }
}


