/**
 * @file utils.c
 * @brief Ce fichier contient les contenus de types et
 * des fonctions pour la manipulation du jeu Five or More
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 */

#include "utils.h"

unsigned int* tab_random(unsigned int p_nombre, unsigned int p_max) {
	assert(p_nombre > 0);
	assert(p_max > 0);

	unsigned int *l_tab;
	unsigned int l_count;
	l_tab = malloc(sizeof(int) * p_nombre);

	for (unsigned int i = 0; i < p_nombre && i < p_max; i++) {
		l_tab[i] = rand() % p_max;

		if (i > 0) {
			l_count = i - 1;

			while (l_count >= 0) {

				if (l_tab[i] == l_tab[l_count])
					l_tab[i] = rand() % p_max;

				l_count--;
			}
		}
	}
	return (l_tab);
}

unsigned int convert_num_ligne(unsigned int p_num, unsigned int p_colonnes) {
	assert(p_num >= 0);
	assert(p_colonnes > 0);

	if (p_num == 0) {
		return (0);
	}

	return (p_num / p_colonnes);
}

unsigned int convert_num_colonne(unsigned int p_num, unsigned int p_colonnes) {
	assert(p_num >= 0);
	assert(p_colonnes > 0);

	if (p_num == 0) {
		return (0);
	}

	return (p_num % p_colonnes);
}

unsigned int convert_coord_num(unsigned int p_ligne, unsigned int p_colonne, unsigned int p_colonnes) {
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);

	return ((p_ligne * p_colonnes) + p_colonne);
}

char* num_to_char(int p_num) {
	assert(p_num >= 0);

	char *l_array;

	l_array = malloc(sizeof(char) * 5); /* @suppress("Avoid magic numbers") */

	for (unsigned int i = 0; i < 4; i++) { /* @suppress("Avoid magic numbers") */
		l_array[i] = '0';
	}

	for (unsigned int i = 4; p_num > 0; i--) {
		l_array[i] = p_num % 10; /* @suppress("Avoid magic numbers") */
		p_num /= 10; /* @suppress("Avoid magic numbers") */
	}
	return (l_array);
}
