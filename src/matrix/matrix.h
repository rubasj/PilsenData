//
// Created by janru on 21.11.2021.
//

#ifndef PILSENDATA_MATRIX_H
#define PILSENDATA_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "../edge/edge.h"
#include "../vector/vector.h"

/**< Definice typu pro položky obsažené v matici. */
typedef int mat_num_t;

/**
 * \struct matrix
 * \brief Struktura představující matici s položkami typu mat_num_t.
 */
typedef struct matrix {
    size_t rows;            /**< Počet řádků matice. */
    size_t cols;            /**< Počet sloupců matice. */
    mat_num_t *items;       /**< Ukazatel na data matice. */
} matrix;
/**
 * \brief matrix_create Funkce dynamicky alokuje novou matici o daných rozměrech
 *                      a jejích položky nastaví na hodnotu i_val.
 * \param rows Počet řádků nové matice.
 * \param cols Počet soupců nové matice.
 * \param i_val Hodnota položek nové matice.
 * \return Ukazatel na nově vytvořenou matici nebo NULL při chybě.
 */
matrix *matrix_create(const size_t rows, const size_t cols, const mat_num_t i_val);

/**
 * \brief matrix_fill Funkce nastaví položky zadané matice mat na hodnotu val.
 * \param mat Ukazatel na matici, jejíž položky budou nastaveny.
 * \param val Nová hodnota položek matice.
 */
void matrix_fill(matrix *mat, const mat_num_t val);

/**
 * \brief matrix_free Funkce provede uvolnění dynamicky alokované matice.
 * \param poor Ukazatel na ukazatel na matici určenou k uvolnění.
 */
void matrix_free(matrix **poor);



/**
 * \brief matrix_set Funkce nastaví hodnotu prvku matice na daných souřadnicích na hodnotu val.
 * \param mat Ukazatel na matici, jejíž prvek bude nastavován.
 * \param row Řádek matice.
 * \param col Sloupec matice.
 * \param val Nová hodnotu prvku na daných souřadnicích.
 */
void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val);


void matrix_fill_edges( matrix *mat_cap, matrix *mat_id, const vector_t *nodes, const vector_t *edges);

#endif //PILSENDATA_MATRIX_H
