/**
 * @file utils.h
 * @brief Ce fichier contient les déclarations de types et les prototypes
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

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/**
 * @fn unsigned int tab_random*(unsigned int, unsigned int)
 * @brief Créé un tableau aléatoire
 *
 * @pre p_nombre > 0 && p_max > 0
 * @post /
 * @param p_nombre la taille du tableau
 * @param p_max un nombre maximum
 * @return unsigned int* l_tab Un tabeau aléatoire
 */
unsigned int* tab_random(unsigned int p_nombre, unsigned int p_max);

/**
 * @fn unsigned int convert_num_ligne(unsigned int, unsigned int)
 * @brief Permet de convertir un nombre en numéro de ligne
 *
 * @pre p_num >= 0 &&  p_colonnes > 0
 * @post /
 * @param p_num un numéro à convertir
 * @param p_colonnes La colonne
 * @return unsigned int p_num / p_colonnes
 */
unsigned int convert_num_ligne(unsigned int p_num, unsigned int p_colonnes);

/**
 * @fn unsigned int convert_num_colonne(unsigned int, unsigned int)
 * @brief Permet de convertir un nombre en numéro de colonne
 *
 * @pre p_num >= 0 &&  p_colonnes > 0
 * @post /
 * @param p_num un numéro à convertir
 * @param p_colonnes La colonne
 * @return unsigned int p_num % p_colonnes
 */
unsigned int convert_num_colonne(unsigned int p_num, unsigned int p_colonnes);

/**
 * @fn unsigned int convert_coord_num(unsigned int, unsigned int, unsigned int)
 * @brief Permet de convertir les coordonée d'un nombre
 *
 * @pre  p_ligne >= 0 && p_colonne >= 0
 * @post /
 * @param p_ligne la ligne
 * @param p_colonne la colonne
 * @param p_colonnes les colonnes
 * @return unsigned int (p_ligne * p_colonnes) + p_colonne
 */
unsigned int convert_coord_num(unsigned int p_ligne, unsigned int p_colonne, unsigned int p_colonnes);

char* num_to_char(int p_num);
