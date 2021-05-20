/**
 * @file modele.h
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation de la vue du jeu Five or More
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 * Manipule la vue en tant que structure opaque.
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <gtk/gtk.h>

#include "controleur.h"
#include "modele.h"
#include "utils.h"

/**
 * @struct typedef struct Vue_t Vue
 * @brief Vue structure opaque contenant les structure des autres header
 */
typedef struct Vue_t Vue;

/**
 * @fn GtkWidget creer_boutons***(unsigned int, unsigned int)
 * @brief Permet de créé le gameboard avec les boutons
 *
 * @pre p_lignes > 0 && p_colonnes > 0
 * @post le gameboard est créé
 * @param p_lignes le nombre de lignes contenant des boutons
 * @param p_colonnes le nombre de colonnes contenant des boutons
 * @return GtkWidget*** l_bouton
 * 			NULL en cas d'erreur d'allocation mémoire
 */
GtkWidget*** creer_boutons(unsigned int p_lignes, unsigned int p_colonnes);

/**
 * @fn GtkWidget creer_fenetre*()
 * @brief Permet de créé la fenêtre principale du jeux
 *
 * @pre  /
 * @post la fenetre est créée
 * @return GtkWidget* l_fenetre la fenetre de jeu
 */
GtkWidget* creer_fenetre();



/**
 * @fn GtkWidget creer_barre_infos*(Vue*)
 * @brief Permet de créé la barre d'information dans le menu d'intéraction
 *
 * @pre p_vue != NULL
 * @post la barre d'inforamtion est créée
 * @param p_vue Un pointeur sur la structure de vue
 * @return GtkWidget* l_barreInfos la barre d'information
 */
GtkWidget* creer_barre_infos(Vue *p_vue);

/**
 * @fn GtkWidget creer_tableau*(Vue*)
 * @brief permet de créé la vBox du tableau de gameboard
 *
 * @pre p_vue != NULL
 * @post Une vBox est créée
 * @param p_vue Un pointeur sur la structure de vue
 * @return GtkWidget* l_vBox la vBox du tableau
 */
GtkWidget* creer_tableau(Vue *p_vue);

/**
 * @fn GtkWidget changer_image*(GtkWidget*, char)
 * @brief Permet de changer les images des boutons
 *
 * @pre p_bouton != NULL
 * @post /
 * @param p_bouton le bouton sur lequel changer l'image
 * @param p_etatBouton le type de bouton
 * @return GtkWidget* p_bouton un bouton avec une nouvelle image
 */
GtkWidget* changer_image(GtkWidget *p_bouton, char p_etatBouton);

/**
 * @fn Vue creer_vue*(char)
 * @brief Permet de créer la vue selon le niveaux sélectionné
 *
 * @pre /
 * @post La vue est créée
 * @param p_niveau le niveaux choisi
 * @return Vue* l_vue La vue
 * 			NULL en cas d'erreur
 */
Vue* creer_vue(char p_niveau);

/**
 * @fn void detruire_vue(Vue)
 * @brief Permet de détruire la vue en paramètre
 *
 * @pre p_vue != NULL
 * @post La vue est détruite
 * @param p_vue la vue à détruire
 * @return /
 *
 */
void detruire_vue(Vue* p_vue);

/**
 * @fn void maj_score(Vue*)
 * @brief permet de mettrre à jour le score
 *
 * @pre assert(p_vue != NULL);
 * @post /
 * @param p_vue La structure de la vue
 */
void maj_score(Vue* p_vue);

/**
 * @fn void detruire_fenetre(GtkWidget*, gpointer)
 * @brief Permet de détruire la fenetre de jeux
 *
 * @pre p_fenetre != NULL
 * @post La fenetre est détruite
 * @param p_fenetre la fenetre à détruire
 * @param p_data NULL
 */
void detruire_fenetre(GtkWidget *p_fenetre, gpointer p_data);

/**
 * @fn void maj_boutons_suivants(Vue*)
 * @brief Permet de mettre à jour les prochains boutons
 *
 * @pre p_vue != NULL
 * @post les prochain bouton in été mis a jour
 * @param p_vue Un pointeur sur la structure de vue
 */
void maj_boutons_suivants(Vue *p_vue);

/**
 * @fn void deplacement_vue(Vue*, unsigned int, unsigned int)
 * @brief
 *
 * @pre p_vue != NULL && p_ligne >= 0 && p_colonne >= 0
 * @post /
 * @param p_vue Un pointeur sur la structure de vue
 * @param p_ligne La ligne ou faire le déplacement
 * @param p_colonne La colonne ou faire le déplacement
 */
void deplacement_vue(Vue *p_vue, unsigned int p_ligne, unsigned int p_colonne);

/**
 * @fn void retrace_defaults(Vue*)
 * @brief Vérifie l'état des boutons defaut
 *
 * @pre p_vue != NULL
 * @post /
 * @param p_vue Un pointeur sur la structure de vue
 */
void retrace_defaults(Vue *p_vue);

/**
 * @fn void aide_popUp(GtkWidget*, gpointer)
 * @brief Créé un pop-up d'aide
 *
 * @pre p_widget != NULL
 * @post Un pop-up est créé
 * @param p_widget
 * @param p_data
 */
void aide_popUp(GtkWidget *p_widget, gpointer p_data);

/**
 * @fn void score_popUp(GtkWidget*, gpointer)
 * @brief Affiche la liste des meilleur score
 *
 * @pre p_widget != NULL
 * @post Un pop-up est créé
 * @param p_widget la widget
 * @param p_data la data (peut être null)
 */
void score_popUp(GtkWidget *p_widget, gpointer p_data);

/**
 * @fn void nom_popUp(GtkWidget*, gpointer)
 * @brief Affiche la selection des nom pour le meilleur score
 *
 * @pre p_widget != NULL
 * @post Un pop-up est créé
 * @param p_widget la widget
 * @param p_data la data (peut être null)
 */
void nom_popUp(GtkWidget *p_widget, gpointer p_data);

/**
 * @fn GtkWidget get_vue_widget*(Vue*, unsigned int, unsigned int)
 * @brief getter sur la matrice des boutons
 *
 * @pre p_vue != NULL && p_ligne >= 0 && p_colonne >= 0
 * @post /
 * @param p_vue Un pointeur sur la structure de vue
 * @param p_ligne La ligne du bouton
 * @param p_colonne La colonne du bouton
 * @return GtkWidget* s_boutons un pointeur sur le bouton
 */
GtkWidget* get_vue_widget(Vue *p_vue, unsigned int p_ligne, unsigned int p_colonne);

/**
 * @fn Vue set_vue_modele*(Vue*, Modele*)
 * @brief setter du model
 *
 * @pre p_vue != NULL && p_modele != NULL
 * @post Le model prend sa nouvelle valeur
 * @param p_vue  Un pointeur sur la structure de vue
 * @param p_modele Un pointeur sur la structure du modele
 * @return Vue* p_vue  Un pointeur sur la structure de vue
 */
Vue* set_vue_modele(Vue *p_vue, Modele *p_modele);

/**
 * @fn void set_vue_widget(Vue*, GtkWidget*, unsigned int, unsigned int)
 * @brief setter sur la matrice des boutons
 *
 * @pre p_vue != NULL && p_widget != NULL && p_ligne >= 0 && p_colonne >= 0
 * @post le bouton prend sa nouvelle valeur
 * @param p_vue Un pointeur sur la structure de vue
 * @param p_widget Un pointeur sur un widget
 * @param p_ligne La ligne du bouton
 * @param p_colonne La colonne du bouton
 */
void set_vue_widget(Vue *p_vue, GtkWidget *p_widget, unsigned int p_ligne, unsigned int p_colonne);

/**
 * @fn void set_vue_widget_suivant(Vue*, GtkWidget*, unsigned int)
 * @brief setter sur la matrice du bouton suivant
 *
 * @pre p_vue != NULL && p_widget != NULL && p_numero >= 0
 * @param p_vue Un pointeur sur la structure de vue
 * @param p_widget Un pointeur sur un widget
 * @param p_numero Le numéro du bouton suivant
 */
void set_vue_widget_suivant(Vue *p_vue, GtkWidget *p_widget, unsigned int p_numero);
