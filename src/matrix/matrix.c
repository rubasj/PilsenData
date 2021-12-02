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

mat_num_t matrix_get_item(matrix *mat, const size_t row, const size_t col) {
    if (!mat || !mat->items) {
    return -1;
    }
    return mat->items[row * mat->cols + col];
}


void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val) {
    printf("SET src %d, tar %d, cap %d\n", row, col, val);
    if (!mat || !mat->items) {
        return;
    }
//    printf("%d - %d\n", val, val);

    mat->items[row * mat->cols + col] = val;
    printf("%d\n",  mat->items[row * mat->cols + col]);



}

int get_node_position(const vector_t *nodes, const int id_node) {

    if (!nodes || !id_node){
        return 0;
    }

    size_t i, curr_val;
    for (i = 0; i < vector_count(nodes); i++) {
        if (id_node == *(int *)vector_at(nodes, i)) {
            return i;
        }
    }

    return -5;
}

void matrix_fill_edges( matrix *mat_cap, matrix *mat_id, const vector_t *nodes, const vector_t *edges) {

    int i, target, source, capacity, id_edge, source_pos, target_pos;
    if (!mat_cap || !mat_id || !nodes || !edges) {
        return;
    }

    for (i = 0; i < vector_count(edges); ++i) {
        source = (*(edge **)vector_at(edges, i))->source;
        target = (*(edge **)vector_at(edges, i))->target;
        capacity = (*(edge **)vector_at(edges, i))->capacity;
        id_edge = (*(edge **)vector_at(edges, i))->id;
        // nastaveni kapacity
        source_pos = get_node_position(nodes, source);

        target_pos = get_node_position(nodes, target);
        printf("FILL src %d, tar %d, cap %d\n", source_pos, target_pos, capacity);
        matrix_set(mat_cap, source_pos, target_pos, capacity);

        matrix_set(mat_id, get_node_position(nodes, source), get_node_position(nodes, target), id_edge);
//        matrix_print(mat_id);
    }

    matrix_print(mat_cap);
    matrix_print(mat_id);

}

void matrix_print(matrix *m){
    int i;
    printf("\n");
    if (!m) {
        printf("|X|\n");
        return;
    }
//    printf("%d\n", m->rows * m->cols);    TODO: OK
    for (i = 0; i < m->rows * m->cols; i++) {

        if (i % (m->cols) == 0) {
            printf("\n");
        }

        printf(" %d ", m->items[i]);

    }
    printf("\n");


}