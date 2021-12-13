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

    if (!line) {
        return NULL;
    }
//    printf(line);
    temp = (edge *) malloc(sizeof(edge));
    if (!temp) {
        return NULL;
    }
    memset(temp->description, 0, strlen(temp->description));
    memcpy(temp->description, line, strlen(line));
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

//    if (temp->id > ) {
//        printf("%s\n",temp->description);
//    }
    return temp;
}

void edge_destroy(edge **poor){
    if (!poor || !*poor) {
        return;
    }

    free((*poor)->description);
//    (*poor)->description = NULL;

    (*poor)->id = 0;
    (*poor)->target = 0;
    (*poor)->source = 0;
    (*poor)->capacity = 0;

    free(*poor);
    *poor = NULL;
}

edge *find_edge_by_id(const vector_t *vec, int id) {
    int i;
    for (i = 0; i < vector_count(vec); ++i) {
        int x = (*(edge **)vector_at(vec, i))->id;
        if ((*(edge **)vector_at(vec, i))->id == id) {
            return (*(edge **)vector_at(vec, i));
        }
    }
    return NULL;
}
