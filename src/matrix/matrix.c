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

mat_num_t matrix_get_item(const matrix *mat, const size_t row, const size_t col) {
    if (!mat || !mat->items) {
    return -1;
    }
    return mat->items[row * mat->cols + col];
}


void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val) {
/*    printf("SET src %d, tar %d, cap %d\n", row, col, val);*/
    if (!mat || !mat->items) {
        return;
    }
    /*printf("%d - %d\n", val, val);*/

    mat->items[row * mat->cols + col] = val;
/*    printf("%d\n",  mat->items[row * mat->cols + col]);
*/


}

int get_vertex_position(const vector_t *vertexes, const int vertex_id) {

    size_t i;
    if (!vertexes || !vertex_id){
        return 0;
    }


    for (i = 0; i < vector_count(vertexes); i++) {
        if (vertex_id == *(int *)vector_at(vertexes, i)) {
            return i;
        }
    }

    return -5;
}

void matrix_fill_edges(matrix *mat_cap, matrix *mat_id, const vector_t *vertexes, const vector_t *edges) {

    int target, source, capacity, id_edge, source_pos, target_pos;
    size_t i;
    if (!mat_cap || !mat_id || !vertexes || !edges) {
        return;
    }

    for (i = 0; i < vector_count(edges); ++i) {
        source = (*(edge **)vector_at(edges, i))->source;
        target = (*(edge **)vector_at(edges, i))->target;
        capacity = (*(edge **)vector_at(edges, i))->capacity;
        id_edge = (*(edge **)vector_at(edges, i))->id;

        /* nastaveni kapacity */
        source_pos = get_vertex_position(vertexes, source);

        target_pos = get_vertex_position(vertexes, target);
        /* printf("FILL src %d, tar %d, cap %d\n", source_pos, target_pos, capacity);*/
        matrix_set(mat_cap, source_pos, target_pos, capacity);

        matrix_set(mat_id, get_vertex_position(vertexes, source), get_vertex_position(vertexes, target), id_edge);
    }

}

void matrix_print(const matrix *m)
{
    size_t i;
    printf("\n");
    if (!m) {
        printf("|X|\n");
        return;
    }
    /*  printf("%d\n", m->rows * m->cols); */
    for (i = 0; i < m->rows * m->cols; i++) {

        if (i % (m->cols) == 0) {
            printf("\n");
        }

        printf(" %d ", m->items[i]);

    }
    printf("\n");


}

matrix *matrix_duplicate(const matrix *original) {
    matrix *new_mat;
    size_t i, j;

    if (!original) {
        return NULL;
    }

    new_mat = (matrix *)malloc(sizeof(matrix));
    if (!new_mat) {
        return NULL;
    }

    new_mat->rows = original->rows;
    new_mat->cols = original->cols;

    new_mat->items = (mat_num_t *)malloc(original->rows * original->cols * sizeof(mat_num_t));
    for (i = 0; i < original->rows; ++i) {
        for (j = 0; j < original->cols; ++j) {
            matrix_set(new_mat, i, j, matrix_get_item(original, i, j));
        }
    }

    return new_mat;
}
