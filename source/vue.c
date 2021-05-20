/**
 * @file vue.c
 * @brief Ce fichier contient les contenus de types et
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

#include "vue.h"

#define X_AIDE_SIZE 400
#define Y_AIDE_SIZE 150
#define SCORE_SIZE 300

#define FACILE '0'
#define DIMENSIONS_FACILE 7
#define BOUTONS_SUIVANT_FACILE 3
#define COULEURS_FACILE 5

#define MOYEN '1'
#define DIMENSIONS_MOYEN 9
#define BOUTONS_SUIVANT_MOYEN 3
#define COULEURS_MOYEN 7

#define DIFFICILE '2'
#define LIGNES_DIFFICILE 15
#define COLONNE_DIFFICILE 20
#define BOUTONS_SUIVANT_DIFFICILE 7
#define COULEURS_DIFFICILE 7

#define SCALE 20
#define SPACING 4
#define PADDING 5

#define DEFAULT_IMG "source/Images/default.png"
#define BLUE "source/Images/blue.png"
#define CYAN "source/Images/cyan.png"
#define GREEN "source/Images/green.png"
#define ORANGE "source/Images/orange.png"
#define PURPLE "source/Images/purple.png"
#define RED "source/Images/red.png"
#define YELLOW "source/Images/yellow.png"
#define OK "source/Images/ok.png"


#define A_PROPOS "A propos"
#define TEXTE "Five or More. \nSmeers Timothy (ULiege). \nNoirfalise Martin (ULiege). \nCours INFO0030 -- 04/05/2021"
#define VBOX_SPACING 0

#define SUIVANT "Suivants :"
#define SCORE "Score :"
#define BEST_SCORE "Meilleurs score :"
#define SELLECTION "Ok"
#define RETURN "Retour"
#define NOM "Entrez votre nom !"

#define DEFAULT 'd'
#define POPUP 'a'

struct Vue_t {
	Modele *s_modele; /**< La structure modele */
	GtkWidget ***s_boutons; /**< Un pointeur sur une matrice de bouton  */
	GtkWidget **s_boutonSuivant; /**< Un vecteur des boutons suivants */
	GtkWidget* s_score;
};

static void annuler(GtkWidget *p_entree, gpointer p_data) {
	assert(p_data != NULL);

	GtkWidget *l_parent = GTK_WIDGET(p_data);
	gtk_widget_destroy(l_parent);
}

GtkWidget*** creer_boutons(unsigned int p_lignes, unsigned int p_colonnes) {
	assert(p_lignes > 0);
	assert(p_colonnes > 0);

	GtkWidget ***l_bouton;

	l_bouton = malloc(sizeof(GtkWidget**) * p_lignes);

	if (l_bouton == NULL) {
		printf("Erreur d'allocation mémoire");
		return (NULL);
	}

	for (unsigned int i = 0; i < p_lignes; i++) {

		l_bouton[i] = malloc(sizeof(GtkWidget*) * p_colonnes);

		if (l_bouton[i] == NULL)
			free(l_bouton[i]);

		for (unsigned int j = 0; j < p_colonnes; j++)
			l_bouton[i][j] = gtk_button_new();
	}
	return (l_bouton);
}//fin creer_boutons

GtkWidget* creer_fenetre() {

	GtkWidget *l_fenetre;

	l_fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(l_fenetre), "Five");

	g_signal_connect(G_OBJECT(l_fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	return (l_fenetre);
}



GtkWidget* creer_barre_infos(Vue *p_vue) {
	assert(p_vue != NULL);

	unsigned int l_bouttonSuivant = get_nb_boutons_suivants(p_vue->s_modele);
	GtkWidget *l_barreInfos;
	GtkWidget *l_zoneTXTSuivants;
	GtkWidget *l_zoneTXTScore;

	/* Barre info */
	l_barreInfos = gtk_hbox_new(FALSE, SPACING);

	l_zoneTXTSuivants = gtk_label_new(SUIVANT);
	l_zoneTXTScore = gtk_label_new(SCORE);


	gtk_box_pack_start(GTK_BOX(l_barreInfos), l_zoneTXTSuivants, TRUE, TRUE, 0);

	maj_boutons_suivants(p_vue);

	for (unsigned int i = 0; i < l_bouttonSuivant; i++)
		gtk_box_pack_start(GTK_BOX(l_barreInfos), p_vue->s_boutonSuivant[i], FALSE, FALSE, PADDING);

	gtk_box_pack_start(GTK_BOX(l_barreInfos), l_zoneTXTScore, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(l_barreInfos), GTK_WIDGET(p_vue->s_score), TRUE, TRUE, 0);

	return (l_barreInfos);
}

GtkWidget* creer_tableau(Vue *p_vue) {
	assert(p_vue != NULL);

	unsigned int l_lignes;
	l_lignes = get_modele_lignes(p_vue->s_modele);

	unsigned int l_colonnes;
	GtkWidget *l_image;
	GtkWidget *l_vBox;
	GtkWidget *l_hBox[l_lignes];

	l_colonnes = get_modele_colonnes(p_vue->s_modele);
	l_vBox = gtk_vbox_new(TRUE, 0);

	for (unsigned int i = 0; i < l_lignes; i++) {
		l_hBox[i] = gtk_hbox_new(TRUE, 0);
		gtk_box_pack_start(GTK_BOX(l_vBox), l_hBox[i], TRUE, TRUE, 0);

		for (int j = 0; j < l_colonnes; j++) {
			l_image = changer_image(p_vue->s_boutons[i][j], DEFAULT);
			set_vue_widget(p_vue, l_image, i, j);
			gtk_box_pack_start(GTK_BOX(l_hBox[i]), p_vue->s_boutons[i][j], TRUE, TRUE, 0);
		}
	}
	return (l_vBox);
}


GtkWidget* changer_image(GtkWidget *p_bouton, char p_etatBouton) {
	assert(p_bouton != NULL);

	char *l_filename;
	GdkPixbuf *l_pixBufTemp;
	GdkPixbuf *l_pixBuf;
	GtkWidget *l_image;

	switch (p_etatBouton) {

	case 'b':
		l_filename = BLUE;
		break;

	case 'c':
		l_filename = CYAN;
		break;

	case 'd':
		l_filename = DEFAULT_IMG;
		break;

	case 'g':
		l_filename = GREEN;
		break;

	case 'o':
		l_filename = ORANGE;
		break;

	case 'p':
		l_filename = PURPLE;
		break;

	case 'r':
		l_filename = RED;
		break;

	case 'y':
		l_filename = YELLOW;
		break;

	case 'a':
		l_filename = OK;
		break;

	default:
		printf("erreur etat bouton : %c\n", p_etatBouton);
		break;
	}

	l_pixBufTemp = gdk_pixbuf_new_from_file(l_filename, NULL);

	if (l_pixBufTemp == NULL) {
		printf("Erreur de chargement de l'image\n");
		return (p_bouton);
	}

	l_pixBuf = gdk_pixbuf_scale_simple(l_pixBufTemp, SCALE, SCALE, GDK_INTERP_NEAREST);
	l_image = gtk_image_new_from_pixbuf(l_pixBuf);
	gtk_button_set_image(GTK_BUTTON(p_bouton), l_image);

	return (p_bouton);
}

Vue* creer_vue(char p_niveau) {

	unsigned int l_lignes;
	unsigned int l_colonnes;
	unsigned int l_boutonSuivants;
	Vue *l_vue;

	l_vue = malloc(sizeof(l_vue));

	if (l_vue == NULL) {
		printf("Erreur d'allocation mémoire");
		return NULL;
	}

	switch (p_niveau) {

	case FACILE:
		l_lignes = DIMENSIONS_FACILE;
		l_colonnes = DIMENSIONS_FACILE;
		l_boutonSuivants = BOUTONS_SUIVANT_FACILE;
		break;

	case MOYEN:
		l_lignes = DIMENSIONS_MOYEN;
		l_colonnes = DIMENSIONS_MOYEN;
		l_boutonSuivants = BOUTONS_SUIVANT_MOYEN;
		break;

	case DIFFICILE:
		l_lignes = LIGNES_DIFFICILE;
		l_colonnes = COLONNE_DIFFICILE;
		l_boutonSuivants = BOUTONS_SUIVANT_DIFFICILE;
		break;

	default:
		printf("Erreur de sélection de niveaux \n");
		break;
	}

	l_vue->s_modele = NULL;
	l_vue->s_boutons = creer_boutons(l_lignes, l_colonnes);

	l_vue->s_boutonSuivant = malloc(sizeof(GtkWidget*) * l_boutonSuivants);

	for (unsigned int i = 0; i < l_boutonSuivants; i++)
		l_vue->s_boutonSuivant[i] = gtk_button_new();

	l_vue->s_score = gtk_label_new("0000");

	return (l_vue);
}//fin creer_vue

void detruire_vue(Vue* p_vue){
	assert(p_vue != NULL);

/*
	for(int i = 0; i < get_modele_lignes(p_vue->s_modele); i++){
		free(p_vue->s_boutons[i]);
	}

	free(p_vue->s_boutons);

	*/
	free(p_vue->s_boutonSuivant);
	free(p_vue);
}//fin detruire_vue

void maj_score(Vue *p_vue){
	assert(p_vue != NULL);

	char l_ScoreToString[10];
	sprintf(l_ScoreToString, "%d", get_score(p_vue->s_modele));
	gtk_label_set_text(GTK_LABEL(p_vue->s_score), l_ScoreToString);
}

void detruire_fenetre(GtkWidget *p_fenetre, gpointer p_data) {
	assert(p_fenetre != NULL);

	gtk_main_quit();
}

void maj_boutons_suivants(Vue *p_vue) {
	assert(p_vue != NULL);

	unsigned int l_nbBoutonSuivants = get_nb_boutons_suivants(p_vue->s_modele);
	char l_etatBoutonSuivant;
	GtkWidget *l_changerImage;

	for (unsigned int i = 0; i < l_nbBoutonSuivants; i++) {
		l_etatBoutonSuivant = get_etat_bouton_suivant(p_vue->s_modele, i);
		l_changerImage = changer_image(p_vue->s_boutonSuivant[i], l_etatBoutonSuivant);
		set_vue_widget_suivant(p_vue, l_changerImage, i);
	}
}

void deplacement_vue(Vue *p_vue, unsigned int p_ligne, unsigned int p_colonne) {
	assert(p_vue != NULL);
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);

	unsigned int *l_positionPremierBouton;
	char l_etatPremierBouton;
	char l_etatBoutonClic;
	GtkWidget *l_image;

	l_positionPremierBouton = get_position_bouton_temp(p_vue->s_modele);
	l_etatPremierBouton = get_etat_bouton(p_vue->s_modele, l_positionPremierBouton[0], l_positionPremierBouton[1]);
	l_image = changer_image( p_vue->s_boutons[l_positionPremierBouton[0]][l_positionPremierBouton[1]], l_etatPremierBouton);
	l_etatBoutonClic = get_etat_bouton(p_vue->s_modele, p_ligne, p_colonne);

	set_vue_widget(p_vue, l_image, l_positionPremierBouton[0], l_positionPremierBouton[1]);

	l_image = changer_image(p_vue->s_boutons[p_ligne][p_colonne], l_etatBoutonClic);

	set_vue_widget(p_vue, l_image, p_ligne, p_colonne);

}

void retrace_defaults(Vue *p_vue) {
	assert(p_vue != NULL);

	for (int i = 0; i < get_modele_lignes(p_vue->s_modele); i++) {

		for (int j = 0; j < get_modele_colonnes(p_vue->s_modele); j++) {

			if (get_etat_bouton(p_vue->s_modele, i, j) == DEFAULT) {
				GtkWidget* l_vue;
				GtkWidget* l_image;

				l_vue = get_vue_widget(p_vue, i, j);
				l_image = changer_image(l_vue, DEFAULT);
				set_vue_widget(p_vue, l_image , i, j);
			}
		}
	}
}

void aide_popUp(GtkWidget *p_widget, gpointer p_data) {
	assert(p_widget != NULL);

	GtkWidget *l_popUp;
	GtkWidget *l_label;
	GtkWidget *l_table;
	GtkWidget *l_bouton;
	GtkWidget *l_image;

	l_popUp = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	l_label = gtk_label_new(TEXTE);
	l_table = gtk_table_new(4, 4, FALSE); /* @suppress("Avoid magic numbers") */
	l_bouton = gtk_button_new();
	l_image = gtk_image_new_from_stock(GTK_STOCK_INFO, GTK_ICON_SIZE_LARGE_TOOLBAR);

	changer_image(l_bouton, POPUP);

	gtk_window_set_title(GTK_WINDOW(l_popUp), A_PROPOS);
	gtk_window_set_default_size(GTK_WINDOW(l_popUp), X_AIDE_SIZE, Y_AIDE_SIZE);

	gtk_table_attach(GTK_TABLE(l_table), l_label, 2, 4, 0, 3, GTK_EXPAND, GTK_EXPAND, 0, 0); /* @suppress("Avoid magic numbers") */
	gtk_table_attach(GTK_TABLE(l_table), l_bouton, 3, 4, 3, 4, GTK_FILL, GTK_FILL, 10, 10); /* @suppress("Avoid magic numbers") */
	gtk_table_attach(GTK_TABLE(l_table), l_image, 0, 2, 0, 2, GTK_EXPAND, GTK_EXPAND, 0, 0); /* @suppress("Avoid magic numbers") */

	gtk_container_add(GTK_CONTAINER(l_popUp), l_table);

	g_signal_connect(G_OBJECT(l_popUp), "delete-event", G_CALLBACK(gtk_widget_destroy), l_popUp);
	g_signal_connect(G_OBJECT(l_bouton), "clicked", G_CALLBACK(annuler), (gpointer )l_popUp);

	gtk_widget_show_all(l_popUp);
}

void score_popUp(GtkWidget *p_widget, gpointer p_data) {
	assert(p_widget != NULL);

	char *l_filename;
	GtkWidget *l_popUp;
	GtkWidget *l_label;
	GtkWidget *l_table;
	GtkWidget *l_bouton;
	GtkWidget *l_image;

	l_filename = get_filename(p_data);
	l_popUp = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	l_label = lire_score(l_filename);
	l_table = gtk_table_new(4, 4, FALSE); /* @suppress("Avoid magic numbers") */
	l_bouton = gtk_button_new();
	l_image = gtk_image_new_from_stock(GTK_STOCK_INFO, GTK_ICON_SIZE_LARGE_TOOLBAR);

	changer_image(l_bouton, POPUP);

	gtk_window_set_title(GTK_WINDOW(l_popUp), BEST_SCORE);
	gtk_window_set_default_size(GTK_WINDOW(l_popUp), SCORE_SIZE, SCORE_SIZE);

	gtk_table_attach(GTK_TABLE(l_table), l_label, 2, 4, 0, 3, GTK_EXPAND, GTK_EXPAND, 0, 0); /* @suppress("Avoid magic numbers") */
	gtk_table_attach(GTK_TABLE(l_table), l_bouton, 3, 4, 3, 4, GTK_FILL, GTK_FILL, 10, 10); /* @suppress("Avoid magic numbers") */
	gtk_table_attach(GTK_TABLE(l_table), l_image, 0, 2, 0, 2, GTK_EXPAND, GTK_EXPAND, 0, 0); /* @suppress("Avoid magic numbers") */

	gtk_container_add(GTK_CONTAINER(l_popUp), l_table);

	g_signal_connect(G_OBJECT(l_popUp), "delete-event", G_CALLBACK(gtk_widget_destroy), l_popUp);
	g_signal_connect(G_OBJECT(l_bouton), "clicked", G_CALLBACK(annuler), (gpointer )l_popUp);

	gtk_widget_show_all(l_popUp);
}

void nom_popUp(GtkWidget *p_widget, gpointer p_data) {

	GtkWidget *l_popUp;
	GtkWidget *l_entree;
	const char *l_nom;
	Modele *p_modele = (Modele *)p_data;

	/* 1 bouton Valider */
	/* 1 bouton Annuler */
	l_popUp = gtk_dialog_new_with_buttons("Saisie du nom", NULL,
			GTK_DIALOG_MODAL,
			GTK_STOCK_OK, GTK_RESPONSE_OK,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			NULL);

	/* Création de la zone de saisie */
	l_entree = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(l_entree), "Saisissez votre nom");

	/* Insertion de la zone de saisie dans la boite de dialogue */
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(l_popUp)->vbox), l_entree, TRUE,
			FALSE, 0);

	gtk_widget_show_all(GTK_DIALOG(l_popUp)->vbox);

	/* On lance la boite de dialogue et on récupéré la réponse */
	switch (gtk_dialog_run(GTK_DIALOG(l_popUp))) {

	/* L utilisateur valide */
	case GTK_RESPONSE_OK:
		l_nom = gtk_entry_get_text(GTK_ENTRY(l_entree));
		set_nom(p_modele, l_nom);
		ecrire_fichier(p_modele);
		break;

		/* L utilisateur annule */
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:

	default:
		printf("Vous n'avez rien saisi !\n");
		break;
	}
	gtk_widget_destroy(l_popUp);
}

/* GETTERS & SETTERS */

GtkWidget* get_vue_widget(Vue *p_vue, unsigned int p_ligne, unsigned int p_colonne) {
	assert(p_vue != NULL);
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);

	return (p_vue->s_boutons[p_ligne][p_colonne]);
}

Vue* set_vue_modele(Vue *p_vue, Modele *p_modele) {
	assert(p_vue != NULL);
	assert(p_modele != NULL);

	p_vue->s_modele = p_modele;
	return (p_vue);
}

void set_vue_widget(Vue *p_vue, GtkWidget *p_widget, unsigned int p_ligne, unsigned int p_colonne) {
	assert(p_vue != NULL);
	assert(p_widget != NULL);
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);

	p_vue->s_boutons[p_ligne][p_colonne] = p_widget;
}

void set_vue_widget_suivant(Vue *p_vue, GtkWidget *p_widget, unsigned int p_numero) {
	assert(p_vue != NULL);
	assert(p_widget != NULL);
	assert(p_numero >= 0);

	p_vue->s_boutonSuivant[p_numero] = p_widget;
}
