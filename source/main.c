/**
 * @file main.c
 * @brief Ce fichier contient le contenu principal du jeux
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 * @todo variable 'l_help' set but not used [-Wunused-but-set-variable]
 * @todo variable 'l_fichier' set but not used [-Wunused-but-set-variable]
 * @warning variable 'l_help' set but not used [-Wunused-but-set-variable]
 * @warning variable 'l_fichier' set but not used [-Wunused-but-set-variable]
 */

#include <getopt.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "controleur.h"
#include "modele.h"
#include "vue.h"

#define PADDING 3
#define VBOX_SPACING 0

int main(int argc, char **argv) {

	srand(time(NULL));
	GtkWidget *l_fenetre;
	GtkWidget *l_vBox;
	GtkWidget *l_barreMenu;
	GtkWidget *l_barreInfos;
	GtkWidget *l_tableau;

	gtk_init(&argc, &argv);

	const char *optstring = ":n:f:H::"; /* mettre f en obligatoire */

	unsigned int l_val = 0;
	char *l_niveau = NULL;
	char *l_fichier = NULL;
	char *l_help;

	while ((l_val = getopt(argc, argv, optstring)) != EOF) {

		switch (l_val) {

		case 'n':
			printf("l_niveau :%s\n", optarg);
			if(optarg == NULL){
				return 0;
			}
			l_niveau = optarg;
			break;

		case 'f':
			printf("l_fichier :%s\n", optarg);
			if(optarg == NULL){
				return 0;
			}
			l_fichier = optarg;
			break;

		case 'H':
			printf("	help called ! :\n");
			printf("		the right command is : ./five -n <niveau> -f <filename>\n");
			printf("		where <niveau> can be 0, 1 or 2\n");
			printf("		for easy, normal or hard level\n");
			if (optarg != NULL)
				l_help = optarg;
			break;

		case ':':
			printf("missing arg: %c\n", optopt);
			return (0);
			break;

		case '?':
			printf("unknown option: %c\n", optopt);
			return (0);
			break;

		default:
			printf("arguments error\n");
			return 0;
			break;
		}
	}

	Modele *l_modele = creer_modele(l_niveau[0], l_fichier);

	Vue *l_vue = creer_vue(l_niveau[0]);
	set_vue_modele(l_vue, l_modele);

	Controler *l_controler = creer_controler();
	set_controler_modele(l_controler, l_modele);
	set_controler_vue(l_controler, l_vue);

	Data_tab *l_data = creer_data_tab(l_controler);
	set_data_controler(l_data, l_controler);

	l_fenetre = creer_fenetre();
	g_signal_connect(G_OBJECT(l_fenetre), "destroy", G_CALLBACK(detruire_fenetre), NULL);

	l_barreMenu = creer_menu(l_controler, l_fenetre, l_niveau[0]);
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

	gtk_main();

	/**
	 *@todo: free
	 */
	return (EXIT_SUCCESS);
}
