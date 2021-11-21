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

mat_num_t matrix_get(const matrix *mat, const size_t row, const size_t col) {
    return mat->items[row * mat->cols + col];
}

void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val) {
    if (!mat || !mat->items) {
        return;
    }

    mat->items[row * mat->cols + col] = val;
}