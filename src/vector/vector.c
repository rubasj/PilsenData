#include "vector.h"


vector_t *vector_create(const size_t item_size, const vec_it_dealloc_t deallocator) {

    vector_t *v;


    if (item_size == 0) {
        return NULL;
    }

    v = (vector_t *)malloc(sizeof(vector_t));

    if (!v) {
        return NULL;
    }

    if (!vector_init(v, item_size, deallocator)) {
        free(v);
        return NULL;
    }

    return v;
}


int vector_init(vector_t *v, const size_t item_size, const vec_it_dealloc_t deallocator) {

    if (!v || item_size == 0) {
        return 0;
    }

    v->capacity = 0;
    v->count = 0;
    v->data = NULL;
    v->item_size = item_size;
    v->deallocator = deallocator;

    if (!vector_realloc(v, VECTOR_INIT_SIZE)){
        return 0;
    }

    ((char *)v->data)[0] = 0;

    return 1;
}

void vector_destroy(vector_t **v){
    size_t i;

    if (!v || !*v) {
        return;
    }

    if((*v)->deallocator){
        for (i = 0; i < (*v)->count; i++) {
            ((*v)->deallocator)((void **)((*v)->data) + i);
        }
    }

    if ((*v)->data) {
        free((*v)->data);
    }

    free(*v);
    *v = NULL;



}

int vector_realloc(vector_t *v, const size_t size) {
    void *data;

    if (!v || v->capacity >= size || size == 0) {
        return 0;
    }

  /*  data = malloc(v->item_size * size);

    if (!data) {
        return 0;
    }

    memcpy(data, v->data, v->count * v->item_size);

    free(v->data);

    */

    data = realloc(v->data, v->item_size * size);

    if (!data) {
        return 0;
    }

    v->capacity = size;


    v->data = data;
    return v->capacity;


}

void *vector_at(const vector_t *v, const size_t at){

    if (!v || at > v->count - 1) {
        return NULL;
    }

    return (void *)((char *)v->data + (at * v->item_size));

}

int vector_push_back(vector_t *v, const void *item){

    if (!v || !item) {
        return INVALID_INDEX;
    }

    if (v->count >= v->capacity) {
        if (vector_realloc(v, v->capacity * VECTOR_SIZE_MULT) == 0){
            return INVALID_INDEX;
        }

    }

    memcpy((void *)((char *)v->data + (v->count * v->item_size)), item, v->item_size);

    v->count++;
    return v->count - 1;
}

size_t vector_count(const vector_t *v) {
    return (v) ? v->count : 0;
}

int vector_isempty(const vector_t *v) {
    return !v ? v->count : 0;
}
/*pomoci vektor add a person print*/
