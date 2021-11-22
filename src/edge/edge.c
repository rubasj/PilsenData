//
// Created by janru on 21.11.2021.
//

#include "edge.h"

#define DELIM ","
#define DELIM_2 "\""

//TODO create check duplicit id

int *edge_add(edge **list, char *line) {
    edge *temp = NULL;
    char *token;

    if (!list || !line) {
        return NULL;
    }
//    printf("%s\n\n", line);
    temp = (edge *) malloc(sizeof(edge));

    temp->description = line;
    token = strtok(line, DELIM);

    int inc = 0;
    while (token != NULL)
    {
        switch (inc) {
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

        if (inc == 3){
            break;

        }

        inc++;
        token = strtok(NULL, DELIM);
    }

//    printf("id: %d, src: %d, tar: %d, cap: %d\n", temp->id, temp->source, temp->target, temp->capacity);
    temp->next = *list;
    *list = temp;

    return EXIT_SUCCESS;
}


void edge_free(edge **head){
    edge *temp = *head;

    while (*head) {
        temp = (*head)->next;

        free(*head);
        *head = temp;
    }

}


