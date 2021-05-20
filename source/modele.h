/**
 * @file modele.h
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation du modèle(boutons) du jeu Five or More
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 * Manipule les modele en tant que structure opaque.
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 */

#include <assert.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"
/**
 * @struct typedef struct Modele_t Modele
 * @brief Data structure opaque représentant le modele
 */
typedef struct Modele_t Modele;

/**
 * @fn Modele creer_modele*(char, char*)
 * @brief Création et initalisation des données du modèle
 *
 * @pre p_niveau != NULL
 * @post Modele * != NULL
 * @param p_niveau  Le niveaux sélectionné permettant de généré le tableau de jeux
 * @param p_filename Le path du fichier de score
 * @return Modele * Un pointeur sur le modele
 * 			NULL en cas d'erreur
 */
Modele* creer_modele(char p_niveau, char *p_filename);

/**
 * @fn void detruire_modele(Modele* p_modele)
 * @brief destruction  du modèle
 *
 * @pre p_modele != NULL
 * @post le modèle est détruit
 * @param p_modele  Le modèle à détruire
 * @return /
 */
void detruire_modele(Modele* p_modele);

/**
 * @fn GtkWidget lire_score*(char*)
 * @brief Permet de lire le fichier de score
 *
 * @pre p_filename != NULL
 * @post /
 * @param p_filename Le path du fichier de score
 * @return GtkWidget* un label contenant la liste de score
 * 			NULL en cas d'erreur
 */
GtkWidget* lire_score(char *p_filename);

/**
 * @fn void ecrire_fichier(Modele*)
 * @brief Permet d"écrire dans le fichier de score
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 */
void ecrire_fichier(Modele *p_modele);

/**
 * @fn void generer_boutons_suivants(Modele*)
 * @brief Génère le prochain bouton à apparaitre dans les cases de jeux
 *
 * @pre	p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 */
void generer_boutons_suivants(Modele *p_modele);

/**
 * @fn void remove_case_libre(Modele*, unsigned int)
 * @brief Actualise la taille du tableau s_tailleTabLibre si la taille diminue
 *
 * @pre p_modele != NULL && p_num >= 0
 * @post s_tailleTabLibre_0 > s_tailleTabLibre
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_num Le nombre à décrémenter du tableau
 */
void remove_case_libre(Modele *p_modele, unsigned int p_num);

/**
 * @fn void add_case_libre(Modele*, int)
 * @brief Actualise la taille du tableau s_tailleTabLibre si la taille augmente
 *
 * @pre p_modele != NULL && p_num >= 0
 * @post s_tailleTabLibre_0 < s_tailleTabLibre
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_num Le nombre à incrémenter du tableau
 */
void add_case_libre(Modele *p_modele, unsigned int p_num);

/**
 * @fn void fin_de_partie(Modele*)
 * @brief Empêche de modifier le tableau une fois que la partie est terminée
 *
 * @pre p_modele != NULL
 * @post s_etatBouton = 'z'
 * @param p_modele Un pointeur sur la structure de modele
 */
void fin_de_partie(Modele *p_modele);

/**
 * @fn unsigned int select_case_libre(Modele*, unsigned int)
 * @brief retourne la case libre selectionnée
 *
 * @pre p_modele != NULL && p_num >= 0
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_num le numéro de la case libre
 * @return unsigned int l_caseLibre la case libre selectionnée
 */
unsigned int select_case_libre(Modele *p_modele, unsigned int p_num);

/**
 * @fn unsigned int deplacement_etat(Modele*, unsigned int, unsigned int)
 * @brief Donne l'état du bouton si il est déplacer ou non et actualise les case libre
 * @warning control reaches end of non-void function
 *
 * @pre p_modele != NULL && p_ligne >= 0 && p_colonne >= 0
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_ligne la ligne selectionnée
 * @param p_colonne la colonne selectionnée
 * @return 0 si le bouton est déja mémorisé
 * 			1 si le bouton n'est pas encore mémorisé
 */
unsigned int deplacement_etat(Modele *p_modele, unsigned int p_ligne, unsigned int p_colonne);

/**
 * @fn int victoire_detect(Modele*)
 * @brief Detecte si l'alignement des couleurs est favorable à une victoire
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return 1 si une victoire à été détectée
 * 			0 sinon
 */
int victoire_detect(Modele *p_modele);

/**
 * @fn char get_etat_bouton_suivant(Modele*, unsigned int)
 * @brief getter pour le pointeur s_etatBoutonSuivant
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_count le compteur
 * @return char s_etatBoutonSuivant[p_count]
 */
char get_etat_bouton_suivant(Modele *p_modele, unsigned int p_count);

/**
 * @fn char get_etat_bouton(Modele*, unsigned int, unsigned int)
 * @brief getter pour la matrice s_etatBouton
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_ligne la ligne selectionnée
 * @param p_colonne la colonne selectionnée
 * @return char s_etatBouton[p_ligne][p_colonne]
 */
char get_etat_bouton(Modele *p_modele, unsigned int p_ligne, unsigned int p_colonne);

/**
 * @fn char get_etat_bouton_temp(Modele*)
 * @brief getter pour s_etatBouton
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return char s_etatBoutonTemp
 */
char get_etat_bouton_temp(Modele *p_modele);

/**
 * @fn char get_filename(Modele*)
 * @brief getter pour s_filename
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return char *s_filename
 */
char* get_filename(Modele *p_modele);

/**
 * @fn char get_nom(Modele*)
 * @brief getter pour s_nom
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return char *s_nom
 */
const char* get_nom(Modele *p_modele);

/**
 * @fn void set_nom(Modele*, const char*)
 * @brief setter pour s_nom
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_nom Le nouveaux nom
 */
void set_nom(Modele *p_modele, const char *p_nom);

/**
 * @fn unsigned int get_nb_boutons_suivants(Modele*)
 * @brief getter pour s_nbBoutonsSuivants
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return s_nbBoutonsSuivants
 */
unsigned int get_nb_boutons_suivants(Modele *p_modele);

/**
 * @fn unsigned int get_score(Modele*)
 * @brief getter pour s_score
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return s_score
 */
unsigned int get_score(Modele *p_modele);

/**
 * @fn unsigned int get_modele_lignes(Modele*)
 * @brief getter pour s_lignes
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return s_lignes
 */
unsigned int get_modele_lignes(Modele *p_modele);

/**
 * @fn unsigned int get_modele_colonnes(Modele*)
 * @brief getter pour s_colonnes
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return s_colonnes
 */
unsigned int get_modele_colonnes(Modele *p_modele);

/**
 * @fn unsigned int get_position_bouton_temp*(Modele*)
 * @brief getter pour s_positionBoutonTemp
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return s_positionBoutonTemp
 */
unsigned int* get_position_bouton_temp(Modele *p_modele);

/**
 * @fn unsigned int get_taille_tab_libre(Modele*)
 * @brief getter pour s_tailleTabLibre
 *
 * @pre p_modele != NULL
 * @post /
 * @param p_modele Un pointeur sur la structure de modele
 * @return s_tailleTabLibre
 */
unsigned int get_taille_tab_libre(Modele *p_modele);

/**
 * @fn void set_taille_tab_libre(Modele*, unsigned int)
 * @brief setter pour s_tailleTabLibre
 *
 * @pre p_modele != NULL && p_taille >= 0
 * @post s_tailleTabLibre0 != s_tailleTabLibre
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_taille la nouvelle valeur de s_tailleTabLibre
 */
void set_taille_tab_libre(Modele *p_modele, unsigned int p_taille);

/**
 * @fn void set_etat_bouton(Modele*, char, unsigned int, unsigned int)
 * @brief setter pour **s_etatBouton
 *
 * @pre p_modele != NULL && p_ligne >= 0 && p_colonne >= 0
 * @post s_etatBouton0 != s_etatBouton
 * @param p_modele Un pointeur sur la structure de modele
 * @param p_etat l'état du bouton
 * @param p_ligne la ligne selectionnée
 * @param p_colonne la colonne selectionnée
 */
void set_etat_bouton(Modele *p_modele, char p_etat, unsigned int p_ligne, unsigned int p_colonne);
