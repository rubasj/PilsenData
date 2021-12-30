
#include "edge.h"

#define DELIM ","
#define DELIM_2 "\""


edge *edge_create(char *line) {
    edge *temp = NULL;
    char *token = NULL;
    int idx;

    if (!line) {
        return NULL;
    }
    temp = (edge *) malloc(sizeof(edge));
    if (!temp) {
        return NULL;
    }

    temp->description = (char *) malloc(sizeof(char *) * strlen(line));
    memset(temp->description, 0, strlen(line));
    memcpy(temp->description, line, strlen(line));
    token = strtok(line, DELIM);

    idx = 0;
    while (token != NULL)
    {
        switch (idx) {
            case 0:
                temp->id = atoi(token);
                break;
            case 1:
                temp->source = atoi(token);
                break;
            case 2:
                temp->target = atoi(token);
                break;

            case 3: {
                if (strstr(token, DELIM_2)) {
                    char *tok = strtok(token, DELIM_2);
                    temp->capacity = atoi(tok);
                } else {
                    temp->capacity = atoi(token);
                }
                break;
            }
        }

        if (idx == 3){
            break;

        }

        idx++;
        token = strtok(NULL, DELIM);
    }

    token = NULL;
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

edge *find_edge_by_id(const vector_t *vec, int id) {
    size_t i;

    if (!vec)
        return NULL;

    for (i = 0; i < vector_count(vec); ++i) {
        if ((*(edge **)vector_at(vec, i))->id == id) {
            return (*(edge **)vector_at(vec, i));
        }
    }
    return NULL;
}






