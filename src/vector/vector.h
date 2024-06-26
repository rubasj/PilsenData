#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/** @brief Násobitel zvětšení pole při realokaci. */
#define VECTOR_SIZE_MULT 2

/** @brief Počáteční velikost vektoru. */
#define VECTOR_INIT_SIZE 4

/** @brief Nevalidní index. */
#define INVALID_INDEX -1

/**
 * @brief Definice ukazatele na obecnou funkci, která umí uvolnit prvek uložený ve vektoru.
 *        Využívá se ve funkci vector_destroy a vector_at_destroy.
 */
typedef void (*vec_it_dealloc_t)(void **item);

/**
 * @brief Struktura _vector
 * Přestavuje obecné dynamicky alokované pole, do které lze přidávat prvky, manipulovat s nimi a
 * odstraňovat je (včetně jeji uvolnění).
 */
typedef struct _vector_t {
    size_t count;                   /**< Počet prvků vektoru. */
    size_t capacity;                /**< Velikost vektoru. */
    size_t item_size;               /**< Velikost jednoho prvku vektoru. */
    void *data;                     /**< Pole ukazatelů, reprezentující prvky seznamu. */
    vec_it_dealloc_t deallocator;   /**< Ukazatel na funkci, která umí uvolnit dynamicky alokované prvky obsažené ve vektoru. */
} vector_t;

/**
 * @brief Alokuje na haldě prázdný vektor s kapacitou VECTOR_INIT_SIZE.
 * @param item_size Velikost jednoho prvku vektoru.
 * @return vector* Ukazatel na alokovaný vektor.
 */
vector_t *vector_create(const size_t item_size, const vec_it_dealloc_t deallocator);

/**
 * @brief Funkce provede inicializaci instance struktury vector, která je dána ukazatelem v.
 *        Datový segment bufferu bude prealokován pro VECTOR_INIT_SIZE prvků o velikosti item_size.
 *        Pozor při použití této funkce na již inicializované instanci struktury vector.
 * 
 * @param item_size Velikost jednoho prvku vektoru.
 * @return int 1, pokud se inicializace podařila, jinak 0.
 */
int vector_init(vector_t *v, const size_t item_size, const vec_it_dealloc_t deallocator);

/**
 * @brief Uvolní vektor z paměti. V případě platnosti ukazatele (*v)->deallocator je funkce, na kterou ukazatel odkazuje, zavolána
 *        nad všemi prvky vektoru. Interní pole je pak interpretováno jako pole void *.
 * @param v Ukazatel na vektor.
 */
void vector_destroy(vector_t **v);

/**
 * @brief Funkce zadanému vektoru odebere vlastnictví udržovaného ukazatele na dynamicky
 *        alokovaná data, tj. zároveň tedy vektor vyprázdní. Při destrukci vektoru tedy
 *        tato data uvolněna nebudou!
 * 
 * @param v Ukazatel na vektor, nad jehož daty přebíráme kontrolu.
 * @return void* Ukazatel na data získaná z vektoru.
 */
void *vector_giveup(vector_t *v);

/**
 * @brief Realokuje zadaný vektor tak, aby jeho kapacita byla new_size. Zmenšení vektoru není povoleno.
 * @param v Realokovaný vektor.
 * @param size Nová kapacita vektoru. 
 * @return int Nová kapacita vektoru pokud realokace proběhla v pořádku, jinak 0.
 */
int vector_realloc(vector_t *v, const size_t size);

/**
 * @brief Vrací ukazatel na at-tý prvek vektoru v. V případě neexistence prvku vratí NULL.
 * 
 * @param v Ukazatel na vektor.
 * @param at Index ve vektoru.
 * @return void* Ukazatel na prvek vektoru nebo NULL při neexitenci prvku.
 */
void *vector_at(const vector_t *v, const size_t at);

/**
 * @brief Přidá prvek do vektoru. Vrací index, kam byl prvek v vektor uložen
 *        nebo INVALID_INDEX v případě chyby.
 * @param v Ukazatel na vektor, kam se prvke přidává.
 * @param item Ukazatel na prvek k přidání.
 * @return int Index, kam byl prvek do vektoru zapsán nebo INVALID_INDEX při chybě.
 */
int vector_push_back(vector_t *v, const void *item);

/**
 * @brief Říká, zda je zadaný vektor prázdný nebo obsahuje nějaké prvky.
 * @param v Ukazatel na vektor.
 * @return int 1, pokud je vektor prázdný, jinak 0.
 */
int vector_is_empty(const vector_t *v);

/**
 * @brief Vrátí počet prvků vektoru.
 * @param v Ukazatel na vektor.
 * @return int Počet zapsaných prvků ve vektoru.
 */
size_t vector_count(const vector_t *v);

#endif