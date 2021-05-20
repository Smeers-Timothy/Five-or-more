/**
 * @file controleur.c
 * @brief Ce fichier contient le contenu des types et
 * des fonctions pour la manipulation du controleur du jeu Five or More
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 * Manipule les controleurs en tant que structure opaque.
 *
 * @warning assignment to 'unsigned int' from 'gpointer' {aka 'void *'} makes integer from pointer without a cast [-Wint-conversion]
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 */

#include "controleur.h"

#define PARTIE "Partie"
#define NEW_PARTIE "Nouvelle partie"
#define SCORE_LISTE "Liste des scores"
#define QUITTER "Quitter"

#define NIVEAU "Niveau"
#define FACILE_TXT "Facile"
#define NORMAL_TXT "Normal"
#define DIFFICILE_TXT "Difficile"

#define AIDE "Aide"
#define A_PROPOS "A propos"

#define PADDING 3
#define VBOX_SPACING 0

struct Controler_t {
	Modele *s_modele;/**< Un poiteur vers une structure boutons_t (décrite dans modele.h) */
	Vue *s_vue; /**< Un poiteur sur la vue */
};

struct Data_tab_t {
	unsigned int s_ligne; /**< Un Integer du nombre de ligne du tableau de jeux */
	unsigned int s_colonne; /**< Un Integer du nombre de colonne du tableau de jeux */
	Controler *s_controler; /**< Un pointeur sur la structure opaque du controlêur contenant la vue et le modele */
};

void restart_game(GtkWidget *p_bouton, gpointer p_data){
	assert(p_data != NULL);

	GtkWidget* l_window;
	char l_niveau;
	gpointer l_ptrWindow;
	gpointer l_ptrNiveau;
	Controler *l_previous_controler;

	GtkWidget *l_fenetre;
	GtkWidget *l_vBox;
	GtkWidget *l_barreMenu;
	GtkWidget *l_barreInfos;
	GtkWidget *l_tableau;

	l_previous_controler = (Controler*) p_data;
	l_ptrWindow = g_object_get_data(G_OBJECT(p_bouton), "window");
	l_ptrNiveau = g_object_get_data(G_OBJECT(p_bouton), "level");
	l_niveau = l_ptrNiveau;
	l_window = l_ptrWindow;

	gtk_widget_hide(l_window);

	Modele *l_modele = creer_modele(l_niveau, get_filename(l_previous_controler->s_modele));

	detruire_controler(l_previous_controler);

	Vue *l_vue = creer_vue(l_niveau);
	set_vue_modele(l_vue, l_modele);

	Controler *l_controler = creer_controler();
	set_controler_modele(l_controler, l_modele);
	set_controler_vue(l_controler, l_vue);

	Data_tab *l_data = creer_data_tab(l_controler);
	set_data_controler(l_data, l_controler);

	l_fenetre = creer_fenetre();
	g_signal_connect(G_OBJECT(l_fenetre), "destroy", G_CALLBACK(detruire_fenetre), NULL);

	l_barreMenu = creer_menu(l_controler, l_fenetre, l_niveau);
	l_barreInfos = creer_barre_infos(l_vue);
	l_tableau = creer_tableau(l_vue);

	nouveau_tour(l_controler);


	l_vBox = gtk_vbox_new(FALSE, VBOX_SPACING);
	gtk_container_add(GTK_CONTAINER(l_fenetre), l_vBox);
	gtk_box_pack_start(GTK_BOX(l_vBox), l_barreMenu, FALSE, FALSE, PADDING);
	gtk_box_pack_start(GTK_BOX(l_vBox), l_barreInfos, FALSE, TRUE, PADDING);
	gtk_box_pack_start(GTK_BOX(l_vBox), l_tableau, TRUE, TRUE, PADDING);

	creer_connections(l_controler, l_data);

	gtk_widget_show_all(l_fenetre);

}//fin restart_game

static void fonction_click(GtkWidget *p_bouton, gpointer p_data) {
	assert(p_data != NULL);

	unsigned int l_ligne;
	unsigned int l_colonne;
	unsigned int l_deplacementEffectif;
	gpointer l_ptrLigne;
	gpointer l_ptrColonne;
	Controler *l_controler;

	l_controler = (Controler*) p_data;
	l_ptrLigne = g_object_get_data(G_OBJECT(p_bouton), "ligne");
	l_ptrColonne = g_object_get_data(G_OBJECT(p_bouton), "colonne");
	l_ligne = l_ptrLigne;
	l_colonne = l_ptrColonne;

	if (get_etat_bouton(l_controler->s_modele, l_ligne, l_colonne) != 'z') {
		l_deplacementEffectif = 0;

		if (deplacement_etat(l_controler->s_modele, l_ligne, l_colonne) == 1)
			l_deplacementEffectif = 1;

		deplacement_vue(l_controler->s_vue, l_ligne, l_colonne);


		if (l_deplacementEffectif == 1) {

			if (victoire_detect(l_controler->s_modele) != 0) {
				maj_score(l_controler->s_vue);
				retrace_defaults(l_controler->s_vue);
			} else {

				if (get_taille_tab_libre(l_controler->s_modele) > 0)
					nouveau_tour(l_controler);
			}
			if (get_taille_tab_libre(l_controler->s_modele) == 0) {
				fin_de_partie(l_controler->s_modele);
			}
		}
	}
}

GtkWidget* creer_menu(Controler *p_controler, GtkWidget* p_window, char p_level) {

	GtkWidget *l_barreMenu;
	GtkWidget *l_menuPartie;
	GtkWidget *l_itemPartie;
	GtkWidget *l_itemNouvellePartie;
	GtkWidget *l_itemListe;
	GtkWidget *l_itemQuitter;
	GtkWidget *l_menuNiveau;
	GtkWidget *l_itemNiveau;
	GtkWidget *l_itemFacile;
	GtkWidget *l_itemNormal;
	GtkWidget *l_itemDifficile;
	GtkWidget *l_menuAide;
	GtkWidget *l_itemAide;
	GtkWidget *l_itemAPropos;

	/* Barre de menu */
	l_barreMenu = gtk_menu_bar_new();

	/* le menu "partie" */
	l_menuPartie = gtk_menu_new();

	/* Création des items_partie */
	l_itemPartie = gtk_menu_item_new_with_label(PARTIE);
	l_itemNouvellePartie = gtk_menu_item_new_with_label(NEW_PARTIE);
	l_itemListe = gtk_menu_item_new_with_label(SCORE_LISTE);
	l_itemQuitter = gtk_menu_item_new_with_label(QUITTER);

	/* Attacher les items_partie */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(l_itemPartie), l_menuPartie);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuPartie), l_itemNouvellePartie);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuPartie), l_itemListe);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuPartie), l_itemQuitter);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_barreMenu), l_itemPartie);

	/* Les signaux partie */
	g_signal_connect(G_OBJECT(l_itemQuitter), "activate", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT(l_itemListe), "activate", G_CALLBACK(score_popUp), p_controler->s_modele);
	g_object_set_data(G_OBJECT(l_itemNouvellePartie), "window", (gpointer) p_window);
	g_object_set_data(G_OBJECT(l_itemNouvellePartie), "level", (gpointer) p_level);
	g_signal_connect(G_OBJECT(l_itemNouvellePartie), "activate", G_CALLBACK(restart_game), p_controler);

	/* le menu "niveau" */
	l_menuNiveau = gtk_menu_new();

	/* Création des items niveau */
	l_itemNiveau = gtk_menu_item_new_with_label(NIVEAU);
	l_itemFacile = gtk_menu_item_new_with_label(FACILE_TXT);
	l_itemNormal = gtk_menu_item_new_with_label(NORMAL_TXT);
	l_itemDifficile = gtk_menu_item_new_with_label(DIFFICILE_TXT);

	/* Attacher les items_niveau */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(l_itemNiveau), l_menuNiveau);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuNiveau), l_itemFacile);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuNiveau), l_itemNormal);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuNiveau), l_itemDifficile);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_barreMenu), l_itemNiveau);

	/* les signaux niveau */
	g_object_set_data(G_OBJECT(l_itemFacile), "window", (gpointer) p_window);
	g_object_set_data(G_OBJECT(l_itemFacile), "level", (gpointer) '0');
	g_signal_connect(G_OBJECT(l_itemFacile), "activate", G_CALLBACK(restart_game), p_controler);

	g_object_set_data(G_OBJECT(l_itemNormal), "window", (gpointer) p_window);
	g_object_set_data(G_OBJECT(l_itemNormal), "level", (gpointer) '1');
	g_signal_connect(G_OBJECT(l_itemNormal), "activate", G_CALLBACK(restart_game), p_controler);

	g_object_set_data(G_OBJECT(l_itemDifficile), "window", (gpointer) p_window);
	g_object_set_data(G_OBJECT(l_itemDifficile), "level", (gpointer) '2');
	g_signal_connect(G_OBJECT(l_itemDifficile), "activate", G_CALLBACK(restart_game), p_controler);

	/* le menu "aide" */
	l_menuAide = gtk_menu_new();

	/* Création des items aide */
	l_itemAide = gtk_menu_item_new_with_label(AIDE);
	l_itemAPropos = gtk_menu_item_new_with_label(A_PROPOS);


	/* Attacher les items_niveau */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(l_itemAide), l_menuAide);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_menuAide), l_itemAPropos);
	gtk_menu_shell_append(GTK_MENU_SHELL(l_barreMenu), l_itemAide);

	/* les signaux aide */
	g_signal_connect(G_OBJECT(l_itemAPropos), "activate", G_CALLBACK(aide_popUp), NULL);

	return (l_barreMenu);
}

Data_tab* creer_data_tab(Controler *p_controler) {
	assert(p_controler != NULL);

	Data_tab *l_data;

	l_data = malloc(sizeof(Data_tab));

	if (l_data == NULL) {
		printf("Erreur d'allocation memoire");
		return (NULL);
	}

	l_data->s_ligne = 0;
	l_data->s_colonne = 0;
	l_data->s_controler = NULL;

	return (l_data);
}

Data_tab* set_data_controler(Data_tab *p_data, Controler *p_controler) {
	assert(p_data != NULL);
	assert(p_controler != NULL);

	p_data->s_controler = p_controler;

	return (p_data);
}

Controler* creer_controler() {

	Controler *l_controler;

	l_controler = malloc(sizeof(Controler));

	if (l_controler == NULL) {
		printf("Erreur d'allocation memoire");
		return (NULL);
	}

	l_controler->s_modele = NULL;
	l_controler->s_vue = NULL;

	return (l_controler);
}

void detruire_controler(Controler* p_controler){
	assert(p_controler != NULL);

	detruire_vue(p_controler->s_vue);
	detruire_modele(p_controler->s_modele);

	free(p_controler);
}

Controler* set_controler_modele(Controler *p_controler, Modele *p_modele) {
	assert(p_controler!= NULL);
	assert(p_modele != NULL);

	p_controler->s_modele = p_modele;

	return (p_controler);
}

Controler* set_controler_vue(Controler *p_controler, Vue *p_vue) {
	assert(p_controler != NULL);
	assert(p_vue != NULL);

	p_controler->s_vue = p_vue;

	return (p_controler);
}

void* nouveau_tour(Controler *p_controler) { /* @suppress("No return") */
	assert(p_controler != NULL);

	unsigned int l_numRandom;
	unsigned int l_numConvert[2];
	unsigned int l_taille;
	unsigned int l_colonne;
	unsigned int *l_numCaseLibre;
	char l_etatSuivant;
	GtkWidget *l_vueWidget;
	GtkWidget *l_changerImage;

	l_taille = get_taille_tab_libre(p_controler->s_modele);
	l_numCaseLibre = malloc(sizeof(unsigned int) * l_taille);

	if (l_numCaseLibre == NULL) {
		printf("Erreur d'allocation memoire");
		return (NULL);
	}

	for(unsigned int j = 0; j < get_nb_boutons_suivants(p_controler->s_modele) && j < l_taille; j++){
			l_numRandom = rand() % get_taille_tab_libre(p_controler->s_modele);
			l_numCaseLibre[j] = select_case_libre(p_controler->s_modele, l_numRandom);
			remove_case_libre(p_controler->s_modele, l_numCaseLibre[j]);
		}


	for(unsigned int k = 0; k < get_nb_boutons_suivants(p_controler->s_modele) && k < l_taille; k++) {

		/* convertion du numero choisi au hasard en coordonnées */
		l_colonne = get_modele_colonnes(p_controler->s_modele);
		l_numConvert[0] = convert_num_ligne(l_numCaseLibre[k], l_colonne);
		l_numConvert[1] = convert_num_colonne(l_numCaseLibre[k], l_colonne);
		l_etatSuivant = get_etat_bouton_suivant(p_controler->s_modele, k);

		/* modification etat bouton */
		set_etat_bouton(p_controler->s_modele, l_etatSuivant, l_numConvert[0], l_numConvert[1]);

		/* modification image bouton dans tableau */
		l_vueWidget = get_vue_widget(p_controler->s_vue, l_numConvert[0], l_numConvert[1]);
		l_changerImage = changer_image(l_vueWidget, l_etatSuivant);
		set_vue_widget(p_controler->s_vue, l_changerImage, l_numConvert[0], l_numConvert[1]);
	}

	generer_boutons_suivants(p_controler->s_modele);
	maj_boutons_suivants(p_controler->s_vue);
}

void creer_connections(Controler *p_controler, Data_tab *p_data) {
	assert(p_controler != NULL);
	assert(p_data != NULL);

	GtkWidget *l_vueWidget;

	for (unsigned int i = 0; i < get_modele_lignes(p_controler->s_modele); i++) {

		for (unsigned int j = 0; j < get_modele_colonnes(p_controler->s_modele); j++) {

			l_vueWidget = get_vue_widget(p_controler->s_vue, i, j);
			g_object_set_data(G_OBJECT(l_vueWidget), "ligne", (gpointer) i);
			g_object_set_data(G_OBJECT(l_vueWidget), "colonne", (gpointer) j);
			g_signal_connect(G_OBJECT(l_vueWidget), "clicked", G_CALLBACK(fonction_click), p_controler);
		}
	}
}
