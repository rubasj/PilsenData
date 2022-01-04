
/**
 * Soubor s definici struktury pro matici,  jeji kod je zalozen na kodu ze 6. cviceni,
 * jediny rozdil je v tom, ze hodnoty v polich jsou signed int.
 */
#ifndef PILSENDATA_MATRIX_H
#define PILSENDATA_MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "../edge/edge.h"
#include "../vector/vector.h"

/** Definice typu pro polozky obsazene v matici. */
typedef int mat_num_t;

/**
 * Struktura představující matici s polozkami typu mat_num_t.
 */
typedef struct matrix {
    size_t rows;            /** Pocet radku matice. */
    size_t cols;            /** Pocet sloupcu matice. */
    mat_num_t *items;       /** Ukazatel na data matice. */
} matrix;
/**
 * Funkce dynamicky alokuje novou matici o danych rozmerech
 *  a jejích položky nastaví na hodnotu i_val.
 * @param rows Pocet radku nove matice.
 * @param cols Pocet soupcu nove matice.
 * @param i_val Hodnota polozek nove matice.
 * @return Ukazatel na nove vytvorenou matici nebo NULL pri chybe.
 */
matrix *matrix_create(const size_t rows, const size_t cols, const mat_num_t i_val);

/**
 * Funkce nastavi polozky zadane matice mat na hodnotu val.
 * @param mat Ukazatel na matici, jejiz polozky budou nastaveny.
 * @param val Nova hodnota polozek matice.
 */
void matrix_fill(matrix *mat, const mat_num_t val);

/**
 * @brief matrix_free Funkce provede uvolneni dynamicky alokované matice.
 * @param poor Ukazatel na ukazatel na matici urcenou k uvolneni.
 */
void matrix_free(matrix **poor);



/**
 * \brief matrix_set Funkce nastaví hodnotu prvku matice na daných souřadnicích na hodnotu val.
 * \param mat Ukazatel na matici, jejíž prvek bude nastavován.
 * \param row Řádek matice.
 * \param col Sloupec matice.
 * \param val Nová hodnota prvku na daných souřadnicích.
 */
void matrix_set(matrix *mat, const size_t row, const size_t col, mat_num_t val);

/**
 * Funkce pro ziskani konkretniho prvku z matice
 * @param mat matice, ze ktere chceme ziskat prvek
 * @param row radkova souradnice prvku
 * @param col sloupcova souradnice prvku
 * @return vrati ziskanou hodnotu
 */
mat_num_t matrix_get_item(const matrix *mat, const size_t row, const size_t col);

/**
 * Vlozeni kapacity hran do matice kapacit a vlozeni id hran do matice s id
 * @param mat_cap matice kapacit
 * @param mat_id matice id
 * @param vertexes vektor uzlu
 * @param edges vektor hran
 */
void matrix_fill_edges(matrix *mat_cap, matrix *mat_id, const vector_t *vertexes, const vector_t *edges);

/**
 * Duplikovani matice
 * @param original puvodni matice
 * @return pointer na duplikovanou matici
 */
matrix *matrix_duplicate(const matrix *original);

/**
 * Funkce najde index nodu, kde se nachazi ve vektoru
 * @param verteces vector verteces
 * @param vertex_id uzel, jehoz index hledame
 * @return kdyz uzel je v zaznamu, vrati se jeho index, jinak -1
 */
int get_vertex_position(const vector_t *verteces, const int vertex_id);

/**
 * Tisk matice pro kontrolu do konzole (v hotovem programu nepouziva se)
 * @param m matice pro tisk
 */
void matrix_print(const matrix *m);
#endif



