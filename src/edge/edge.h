
/**
 * Soubor obsahuje definici struktury edge pro hrany grafu a funkce pro tuto strukturu
 * @author Jan Rubas
 * janrubas@students.zcu.cz
 */
#ifndef PILSENDATA_EDGE_H
#define PILSENDATA_EDGE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../vector/vector.h"

/**
 * Struktura pro repreyentaci hrany
 */
typedef struct edge_{
    int id;     /* identifikator */
    int source;  /* pocatecni vrchol */
    int target; /* cilovy vrchol */
    int capacity; /* kapacita hrany */
    char *description; /* v souboru oznaceno jako WKT, popis hrany */
} edge;

/**
 * Pridani dalsi hrany
 * @param line  radka ze souboru pro generovani nove hrany
 */
edge *edge_create(char *line);

/**
 * Uvolneni seznamu hran
 * @param poor hrana pro uvlneni
 */
void edge_destroy(edge **poor);

/**
 * Funkce pro hledani hrany podle jejiho ID
 * @param vec vektor, ve kterem se hleda
 * @param id identifikator hrany
 * @return hrana, ktera se shoduje s ID a je ve vektoru,pokud neni nalezena vrati null.
 */
edge *find_edge_by_id(const vector_t *vec, int id);


#endif
