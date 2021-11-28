//
// Created by janru on 21.11.2021.
//

#include "edge.h"

#define DELIM ","
#define DELIM_2 "\""

//TODO create check duplicit id

edge *edge_create(char *line) {
//    printf("%s \n", line);
    edge *temp = NULL;
    char *token;
    char *tmp_line;

    if (!line) {
        return NULL;
    }
//    printf(line);
    temp = (edge *) malloc(sizeof(edge));
    if (!temp) {
        return NULL;
    }
    temp->description = line;
    tmp_line = line;
    token = strtok(tmp_line, DELIM);

    int idx = 0;
    while (token != NULL)
    {
        switch (idx) {
            case 0:
                temp->id = atoi(token);
//                printf("%d\n", temp->id);
                break;
            case 1:
                temp->source = atoi(token);
                break;
            case 2:
                temp->target = atoi(token);

            case 3:
                if (strstr(token, DELIM_2)){
                    char *tok = strtok(token, DELIM_2);
                    temp->capacity = atoi(tok);
                }
                else {
                    temp->capacity = atoi(token);
                }
                break;
            default:
                break;
        }

        if (idx == 3){
            break;

        }

        idx++;
        token = strtok(NULL, DELIM);
    }


    return temp;
}

void edge_destroy(edge **poor){
    if (!poor || !*poor) {
        return;
    }

    free((*poor)->description);
    (*poor)->description = NULL;

    (*poor)->id = 0;
    (*poor)->target = 0;
    (*poor)->source = 0;
    (*poor)->capacity = 0;

    free(*poor);
    *poor = NULL;
}


