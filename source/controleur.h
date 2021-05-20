/**
 * @file controleur.h
 * @brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation du controleur du jeu Five or More
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 * Manipule les controleurs en tant que structure opaque.
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 */

#ifndef __CONTROLEUR__
#define __CONTROLEUR__

#include <stdlib.h>
#include <assert.h>
#include <gtk/gtk.h>

#include "modele.h"
#include "vue.h"
#include "utils.h"

/**
 * @struct typedef struct Controler_t Controler
 * @brief Controler structure opaque représentant un contrôleur.
 */
typedef struct Controler_t Controler;

/**
 * @struct typedef struct Data_tab_t Data_tab
 * @brief Data structure opaque comprenant les information utiles à la gestion du tableau de jeux
 */
typedef struct Data_tab_t Data_tab;

/**
 * @fn GtkWidget creer_menu*(Modele*)
 * @brief Permet de créé le menu d'interaction
 *
 * @pre p_filename != NULL
 * @post le menu est créé
 * @param p_modele La structure modele
 * @return GtkWidget* l_barreMenu la barre de menu
 */
GtkWidget* creer_menu(Controler *p_controler, GtkWidget* p_window, char p_level);

/**
 * @fn Data_tab creer_data_tab*(Controler*)
 * @brief Création et initalisation des données du tableau
 *
 * @pre p_controler != NULL
 * @post Data_tab * != NULL
 * @param p_controler Un pointeur sur la structure de contrôle
 * @return Data_tab * Un pointeur sur la structure de données
 * 			NULL en cas d'erreur
 */
Data_tab* creer_data_tab(Controler *p_controler);

/**
 * @fn Data_tab set_data_controler*(Data_tab*, Controler*)
 * @brief Initialise la structure de données
 *
 * @pre p_data != NULL && p_controler != NULL
 * @post /
 * @param p_data Un pointeur sur la structure de données
 * @param p_controler Un pointeur sur la structure de contrôle
 * @return Data_tab * Un pointeur sur la structure de données
 */
Data_tab* set_data_controler(Data_tab *p_data, Controler *p_controler);

/**
 * @fn Controler creer_controler*()
 * @brief Création et initalisation de la structure de contrôle
 *
 * @pre /
 * @post Controler * != NULL
 * @return Controler * Un pointeur sur la structure de contrôle
 * 			NULL en cas d'erreur
 */
Controler* creer_controler();

/**
 * @fn void detruire_controler(Controler* p_controler)
 * @brief destruction de la structure de contrôle
 *
 * @pre p_controler != NULL
 * @post controleur détruit
 * @return /
 */
void detruire_controler(Controler* p_controler);

/**
 * @fn Controler set_controler_modele*(Controler*, Modele*)
 * @brief Initialise la structure de contrôle
 *
 * @pre p_controler!= NULL && p_modele!= NULL
 * @post /
 * @param p_controler Un pointeur sur la structure de contrôle
 * @param p_modele Un pointeur sur la structure du modele
 * @return Controler * un pointeur sur la structure de contrôle
 *
 */
Controler* set_controler_modele(Controler *p_controler, Modele *p_modele);

/**
 * @fn Controler set_controler_vue*(Controler*, Vue*)
 * @brief Initisialise la structure de vue présente dans le contrôleur
 *
 * @pre p_controler != NULL && p_vue != NULL
 * @post /
 * @param p_controler Un pointeur sur la structure de contrôle
 * @param p_vue Un pointeur sur la structure de vue
 * @return Controler *  Un pointeur sur la structure de contrôle
 */
Controler* set_controler_vue(Controler *p_controler, Vue *p_vue);

/**
 * @fn void nouveau_tour*(Controler*)
 * @brief Permet d'actualiser la page pour chaque nouveau tour
 * @warning control reaches end of non-void function
 *
 * @pre p_controler != NULL
 * @post la page est actualisée
 * @param p_controler Un pointeur sur la structure de contrôle
 */
void* nouveau_tour(Controler *p_controler);

/**
 * @fn void creer_connections(Controler*, Data_tab*)
 * @brief Créé une connection de type "clicked" pour chaque bouton présent dans le tableau de jeux
 * @warning cast to pointer from integer of different size
 *
 * @pre p_controler != NULL && p_data != NULL
 * @post /
 * @param p_controler Un pointeur sur la structure de contrôle
 * @param p_data Un pointeur sur la structure de données
 */
void creer_connections(Controler *p_controler, Data_tab *p_data);

#endif
