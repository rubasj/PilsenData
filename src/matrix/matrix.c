#include "matrix.h"

matrix *matrix_create(const size_t rows, const size_t cols, const mat_num_t i_val) {
    matrix *new_mat;

    if (rows == 0 || cols == 0) {
        return NULL;
    }

    new_mat = (matrix *)malloc(sizeof(matrix));
    if (!new_mat) {
        return NULL;
    }

    new_mat->rows = rows;
    new_mat->cols = cols;

    new_mat->items = (mat_num_t *)malloc(rows * cols * sizeof(mat_num_t));
    if (!new_mat->items) {
        free(new_mat);
        return NULL;
    }

    matrix_fill(new_mat, i_val);
    return new_mat;
}

void matrix_fill(matrix *mat, const mat_num_t val) {
    size_t i;

    if (!mat || !mat->items) {
        return;
    }

    for (i = 0; i < mat->cols * mat->rows; ++i) {
        mat->items[i] = val;
    }
}


void matrix_free(matrix **poor) {
    if (!poor || !*poor)
        return;

    (*poor)->cols = 0;
    (*poor)->rows = 0;

    free((*poor)->items);
    (*poor)->items = NULL;

    free(*poor);
    *poor = NULL;
}


void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val) {
    if (!mat || !mat->items || !row || !col || !val) {
        return;
    }
//    printf("%d - %d\n", val, val);

    mat->items[row * mat->cols + col] = val;
//    printf("%d\n",  mat->items[row * mat->cols + col]);

}

int get_node_position(const vector_t *nodes, const int id_node) {

    if (!nodes || !id_node){
        return 0;
    }

    size_t i;
    for (i = 0; i < vector_count(nodes); ++i) {
        if (id_node == *(int *)vector_at(nodes, id_node)) {
            return i;
        }
    }

    return 0;
}

void matrix_fill_edges( matrix *mat_cap, matrix *mat_id, const vector_t *nodes, const vector_t *edges) {

    if (!mat_cap || !mat_id || !nodes || !edges) {
        return;
    }

    //TODO Vymyslet plneni matic

//    while (list) {
////        printf("%d - %d\n", list->id, list->capacity);
//        matrix_set(mat_cap, list->source, list->target, list->capacity);
//        matrix_set(mat_id, list->source, list->target, list->id);
//    }


}