


/**
 * Soubor obsahuje definice funkci pro hledani minimalniho rezu.
 * @author Jan Rubas
 * janrubas@students.zcu.cz
 */
#ifndef PILSENDATA_ALGORITHM_H
#define PILSENDATA_ALGORITHM_H

#include <limits.h>
#include <string.h>
#include "../matrix/matrix.h"
#include "../queue/queue.h"

/**
 * Funkce pro porovnani dvou celociselnych hodnot
 * @param x prvni porovnavana hodnota
 * @param y druha porovnavana hodnota
 * @return vrati vzdy mensi porovnavanou hodnotu
 */
int min(int x, int y);

/**
 * Pomoci BFS se prohledava graf a hleda cesty z vrcholu "S" do "T".
 * @param rGraph matice reprezentujici graf (sit)
 * @param s source
 * @param t target
 * @param parent pole vrcholu
 * @return vraci "1" pokud existuje cesta, jinak "0"
 */
int bfs(matrix *rGraph, const int s, const int t, int *parent);

/**
 * Algoritmus na hledani maximalniho toku a minimalního rezu
 * @param graph matice s grafem, kde budeme hledat
 * @param m_edges matice obsahujici id hran grafu, pokud hrana neexistuje, obsahuje -1 hodnotu
 * @param s source
 * @param t target
 * @param out_active promenna oznacujici, zda se maji vyhledat hrany minimalniho rezu pro zapis do souboru
 * @param min_cut vektor do nejz se ulozi hrany minimalniho rezu, jiz serazene podle ID
 * @return funkce vrati maximalni tok
 */
int ford_fulkerson(const matrix *graph, const matrix *m_edges, int s, int t, int out_active, vector_t *min_cut);

/**
 * Funkce pro serazeni hran minimalniho rezu podle ID, zalozena na Selection sort
 * @param pVector vektor, ktery se seradi
 */
void sort_mincut_id(vector_t *pVector);

/**
 * Funkce prohodi parametry, pomocna k selection sortu
 * @param a parametr pro prohozeni
 * @param b parametr pro prohozeni
 */
void swap(int *a, int *b);
#endif
