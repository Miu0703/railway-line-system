#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"System.h"

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

typedef struct arg {
	int argc;
	char** args;
} *pArg, Arg;

void shell_loop();
char *lsh_read_line(void);
pArg lsh_split_line(char *line);

int isExist = 0;
pSys system1 =NULL;

int main() {
	shell_loop();
	return 0;
}

void shell_loop(void)
{
  char *line;
  pArg argg;
  do {
    //printf("> ");
    line = lsh_read_line();
    argg = lsh_split_line(line);
    int argc = argg->argc;
    char** argv = argg->args;
    if (argc!=0) {
        if (strcmp(argv[0],"exit")==0) {
            exit(0);
        } else if (strcmp(argv[0],"init")==0) {
            if (isExist!=0) {
                printf("Problem\n");
            } else {
                system1 = initial(argv[1]);
                isExist = 1;
                printf("Done\n");
            }
        } else if (strcmp(argv[0],"addStation")==0) {
            result rslt = addStation(system1,argv[1],atoi(argv[2]),atoi(argv[3]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"addLine")==0) {
            result rslt = addLine(system1, atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"updateLine")==0) {
            result rslt = updateLine(system1, atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"deleteStation")==0) {
            result rslt = deleteStation(system1, atoi(argv[1]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            }  else {printf("Problem\n");}
        } else if (strcmp(argv[0],"removeLine")==0) {
            result rslt = removeLine(system1, atoi(argv[1]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"showLinesByStation")==0) {
            result rslt = showLineByStation(system1, atoi(argv[1]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"showSingleStations")==0) {
            result rslt = showSingleStation(system1);
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"showLine")==0) {
            result rslt = showLine(system1, atoi(argv[1]));
            if (rslt==SUCCESS) {
                printf("Done\n");
            } else {printf("Problem\n");}
        } else if (strcmp(argv[0],"showSystem")==0) {
            showSystem(system1);
        } else if (strcmp(argv[0],"destroy")==0) {
            destroy(system1);
            isExist = 0;
            printf("Done\n");
        } else {
            printf("Problem\n");
        }
    }



    free(line);
    free(argg);
  } while (1);
}

char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;
  if (!buffer) {
    fprintf(stderr, "allocation error\n");
    exit(0);
  }
  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "allocation error\n");
        exit(0);
      }
    }
  }
}

pArg lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  if (!tokens) {
    fprintf(stderr, "allocation error\n");
    exit(0);
  }
  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;
    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(0);
      }
    }
    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  pArg argg = (pArg)malloc(sizeof(Arg));
  argg->args = tokens;
  argg->argc = position;
  return argg;
}
