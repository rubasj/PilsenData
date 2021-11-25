//
// Created by janru on 21.11.2021.
//

#include "edge.h"

#define DELIM ","
#define DELIM_2 "\""

//TODO create check duplicit id

edge *edge_create(const char *line) {
    edge *temp = NULL;
    char *token;

    if (!line) {
        return NULL;
    }
//    printf(line);
    temp = (edge *) malloc(sizeof(edge));

    temp->description = line;
    token = strtok(line, DELIM);

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

    printf("id: %d, src: %d, tar: %d, cap: %d\n", temp->id, temp->source, temp->target, temp->capacity);

    return EXIT_SUCCESS;
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


