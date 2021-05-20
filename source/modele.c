/**
 * @file modele.c
 * @brief Ce fichier contient les contenus de types et
 * des fonctions pour la manipulation du modèle(boutons) du jeu Five or More
 *
 * @authors Noirfalise Martin S200912, Smeers Timothy S200930
 * @version 0.1
 * @date 05/04/2021
 *
 * Manipule les modele en tant que structure opaque.
 *
 * @warning No return, in function returning non-void
 *
 * Critère de style :
 * s_	Les variable globale à plusieurs fichiers
 * p_	Les paramètre de fonctions
 * l_	Les variables globale à une seule fonction
 *
 */

#include "modele.h"

/* DEFINE */
#define FACILE 0
#define DIMENSIONS_FACILE 7
#define BOUTONS_SUIVANT_FACILE 3
#define COULEURS_FACILE 5

#define MOYEN 1
#define DIMENSIONS_MOYEN 9
#define BOUTONS_SUIVANT_MOYEN 3
#define COULEURS_MOYEN 7

#define DIFFICILE 2
#define LIGNES_DIFFICILE 15
#define COLONNE_DIFFICILE 20
#define BOUTONS_SUIVANT_DIFFICILE 7
#define COULEURS_DIFFICILE 7

#define INITIAL_SCORE 0
#define ZERO_ASCII -48

#define BLUE_NBR 0
#define CYAN_NBR 1
#define GREEN_NBR 2
#define ORANGE_NBR 3
#define PURPLE_NBR 4
#define RED_NBR 5
#define YELLOW_NBR 6

#define DEFAULT_IMG 'd'
#define BLOCK 'z'

#define SCORE "Meilleurs score :"
#define FILE_NAME "score.txt"

#define VICTOIRE 5

/**
 * \struct boutons_t
 * \brief Data structure représentant un bouton.
 */
struct Modele_t {
	unsigned int *s_tabCasesLibres; /**< Un tableau des cases vide*/
	unsigned int s_positionBoutonTemp[2]; /**< Un tampon sur la position du bouton */
	unsigned int s_niveau; /**< Variable renseignant dans quel niveaux du jeux on est*/
	unsigned int s_lignes; /**< Le nombre de ligne du gameboard*/
	unsigned int s_colonnes; /**< Le nombre de colonne du gameboard*/
	unsigned int s_nbBoutonsSuivants; /**< Le nombre de bouton qui vont apparaitre au prochain tour */
	unsigned int s_tailleTabLibre; /**< La taille libre du gameboard */
	unsigned int s_nbCouleurs; /**< Le nombre de couleurs */
	unsigned int s_score; /**< Renseigne le score */
	char **s_etatBouton; /**< L'état de ce bouton en fonction de son image : d = default, r = RED, p = PINK, c = CYAN, b = BLUE, g = GREEN, o = ORANGE, y = YELLOW */
	char **s_copieEtatBouton;
	char *s_etatBoutonSuivant; /**< L'état du prochain bouton */
	char *s_filename; /**< Chemin d'acces du fichier de score */
	const char *s_nom; /**< Nom du joueur */
	char s_etatBoutonTemp; /**<  Un tampon sur l'état du bouton */
};

static char etat_random(unsigned int p_nbCouleursPossibles) {
	unsigned int l_rand = rand() % p_nbCouleursPossibles;
	char l_couleur;

	switch (l_rand) {
	case BLUE_NBR:
		l_couleur = 'b'; /* Blue */
		break;
	case CYAN_NBR:
		l_couleur = 'c'; /* Cyan */
		break;
	case GREEN_NBR:
		l_couleur = 'g'; /* Green */
		break;
	case ORANGE_NBR:
		l_couleur = 'o'; /* Orange */
		break;
	case PURPLE_NBR:
		l_couleur = 'p'; /* Purple */
		break;
	case RED_NBR:
		l_couleur = 'r'; /* Red */
		break;
	case YELLOW_NBR:
		l_couleur = 'y'; /* Yellow */
		break;
	default:
		printf("Aucune couleur ne peut être sélectionnée! Vérifiez le nombre de couleurs possible \n");
		break;
	}
	return (l_couleur);
}

static char* cree_fichier_score(char *p_filename, Modele *p_modele) {
	assert(p_filename != NULL);
	assert(p_modele != NULL);

	char *l_filename;
	FILE *l_fichier;

	if (p_filename == NULL) {

		l_fichier = fopen(FILE_NAME, "w");

		if (l_fichier == NULL) {
			printf("Erreur lors de la création du fichier !\n");
			fclose(l_fichier);
			return (NULL);
		}

		fputs(SCORE, l_fichier);
		l_filename = FILE_NAME;
		return (l_filename);

	} else {

		if (!access(p_filename, F_OK)) {
			l_fichier = fopen(p_filename, "r+");

		} else {
			l_fichier = fopen(p_filename, "w");
			fputs(SCORE, l_fichier);
		}

		if (l_fichier == NULL) {
			printf("Erreur lors de l'ouverture du fichier !\n");
			fclose(l_fichier);
			return (NULL);
		}
		fclose(l_fichier);
		return (p_filename);
	}
}

static long taille_fichier(char *p_filename) {
	assert(p_filename != NULL);

	long size;
	FILE *l_fichier;

	l_fichier = fopen(p_filename, "rb");

	if (l_fichier == NULL) {
		printf("Erreur lors de l'ouverture du fichier !\n");
		fclose(l_fichier);
		return (0);
	}

	if (l_fichier) {
		fseek(l_fichier, 0, SEEK_END);
		size = ftell(l_fichier);
		fclose(l_fichier);
	}
	return (size);
}

Modele* creer_modele(char p_niveau, char *p_filename) {
	assert(p_filename != NULL);

	char *l_filename;
	Modele *l_modele;

	l_modele = malloc(sizeof(Modele));

	if (l_modele == NULL) {
		printf("Erreur d'allocation mémoire");
		return (NULL);
	}

	l_modele->s_niveau = (unsigned int) (p_niveau)ZERO_ASCII;
	l_filename = cree_fichier_score(p_filename, l_modele);
	l_modele->s_filename = l_filename;

	switch (l_modele->s_niveau) {

	case FACILE:
		l_modele->s_lignes = DIMENSIONS_FACILE;
		l_modele->s_colonnes = DIMENSIONS_FACILE;
		l_modele->s_nbBoutonsSuivants = BOUTONS_SUIVANT_FACILE;
		l_modele->s_nbCouleurs = COULEURS_FACILE;
		break;

	case MOYEN:
		l_modele->s_lignes = DIMENSIONS_MOYEN;
		l_modele->s_colonnes = DIMENSIONS_MOYEN;
		l_modele->s_nbBoutonsSuivants = BOUTONS_SUIVANT_MOYEN;
		l_modele->s_nbCouleurs = COULEURS_MOYEN;
		break;

	case DIFFICILE:
		l_modele->s_lignes = LIGNES_DIFFICILE;
		l_modele->s_colonnes = COLONNE_DIFFICILE;
		l_modele->s_nbBoutonsSuivants = BOUTONS_SUIVANT_DIFFICILE;
		l_modele->s_nbCouleurs = COULEURS_DIFFICILE;
		break;

	default:
		printf("Erreur de sélection de niveaux \n");
		break;
	}

	l_modele->s_etatBoutonSuivant = malloc(sizeof(char*));

	generer_boutons_suivants(l_modele);

	l_modele->s_etatBouton = malloc(sizeof(char*) * l_modele->s_lignes);

	for (unsigned int i = 0; i < l_modele->s_lignes; i++) {
		l_modele->s_etatBouton[i] = malloc(sizeof(char*));

		for (unsigned int j = 0; j < l_modele->s_colonnes; j++)
			l_modele->s_etatBouton[i][j] = DEFAULT_IMG;
	}

	l_modele->s_copieEtatBouton = malloc(sizeof(char*) * l_modele->s_lignes);
	for (unsigned int i = 0; i < l_modele->s_lignes; i++) {
		l_modele->s_copieEtatBouton[i] = malloc(sizeof(char*));
	}

	l_modele->s_tailleTabLibre = (l_modele->s_lignes * l_modele->s_colonnes);

	l_modele->s_tabCasesLibres = malloc(sizeof(unsigned int) * l_modele->s_tailleTabLibre);

	for (unsigned int i = 0; i < l_modele->s_tailleTabLibre; i++)
		l_modele->s_tabCasesLibres[i] = i;

	l_modele->s_positionBoutonTemp[0] = 0;
	l_modele->s_positionBoutonTemp[1] = 0;
	l_modele->s_etatBoutonTemp = BLOCK;

	l_modele->s_score = INITIAL_SCORE;
	return (l_modele);
}//fin creer_modele

void detruire_modele(Modele* p_modele){
	assert(p_modele != NULL);

	free(p_modele->s_etatBoutonSuivant);
	free(p_modele->s_etatBouton);
	free(p_modele->s_copieEtatBouton);
	/*
	for (unsigned int i = 0; i < p_modele->s_lignes; i++) {
		free(p_modele->s_etatBouton[i]);
	}
	*/
	free(p_modele->s_tabCasesLibres);
	free(p_modele);
}//fin detruire_fenetre

GtkWidget* lire_score(char *p_filename) {
	assert(p_filename != NULL);

	char *l_buff;
	char *l_buff2;
	long l_taille;
	FILE *l_fichier;
	GtkWidget *l_label;
	GError *l_err;

	l_taille = taille_fichier(p_filename);
	l_buff = malloc(l_taille);
	l_fichier = fopen(p_filename, "r");

	if (l_buff == NULL) {
		printf("Erreur d'allocation mémoire !\n");
		return (NULL);
	}

	if (l_fichier == NULL) {
		printf("Erreur lors de l'ouverture du fichier !\n");
		fclose(l_fichier);
		return (NULL);
	}

	if (g_file_get_contents(p_filename, &l_buff, NULL, &l_err))
	    l_label = gtk_label_new(l_buff);
	else {
	    g_error("%s", l_err->message);
	    g_error_free (l_err);
	}
	return (l_label);
}

void ecrire_fichier(Modele *p_modele) {

}

void generer_boutons_suivants(Modele *p_modele) {
	assert(p_modele != NULL);

	for (unsigned int k = 0; k < p_modele->s_nbBoutonsSuivants; k++)
		p_modele->s_etatBoutonSuivant[k] = etat_random(p_modele->s_nbCouleurs);
}

void remove_case_libre(Modele *p_modele, unsigned int p_num) {
	assert(p_modele != NULL);
	assert(p_num >= 0);

	int l_position = -1;

	for (unsigned int i = 0; i < p_modele->s_tailleTabLibre && l_position == -1; i++) {

		if (p_modele->s_tabCasesLibres[i] == p_num)
			l_position = i;
	}

	for (unsigned int j = l_position; j < p_modele->s_tailleTabLibre - 1; j++)
		p_modele->s_tabCasesLibres[j] = p_modele->s_tabCasesLibres[j + 1];

	p_modele->s_tailleTabLibre--;
}

void add_case_libre(Modele *p_modele, unsigned int p_num) {
	assert(p_modele != NULL);
	assert(p_num >= 0);

	p_modele->s_tabCasesLibres[p_modele->s_tailleTabLibre] = p_num;
	p_modele->s_tailleTabLibre++;
}

void fin_de_partie(Modele *p_modele) {
	assert(p_modele != NULL);

	for (unsigned int i = 0; i < p_modele->s_lignes; i++) {

		for (unsigned int j = 0; j < p_modele->s_colonnes; j++)
			p_modele->s_etatBouton[i][j] = BLOCK;
	}
	nom_popUp(NULL, p_modele);
}

unsigned int select_case_libre(Modele *p_modele, unsigned int p_num) {
	assert(p_modele != NULL);
	assert(p_num >= 0);

	unsigned int l_caseLibre;

	l_caseLibre = p_modele->s_tabCasesLibres[p_num];

	return (l_caseLibre);
}

int parcours_autorise(Modele* p_modele, int p_NewLine, int p_newColumn, int p_memLine, int p_memColumn){
   assert(p_modele != NULL);

   if((p_NewLine == p_memLine) && (p_newColumn == p_memColumn)){
      p_modele->s_copieEtatBouton[p_NewLine][p_newColumn] = 'z';
      return 1;
   }
   if(p_NewLine >= 0 && p_newColumn >= 0 && p_NewLine < p_modele->s_lignes &&
		   p_newColumn < p_modele->s_colonnes &&
		   p_modele->s_copieEtatBouton[p_NewLine][p_newColumn] == 'd' &&
		   p_modele->s_etatBouton[p_NewLine][p_newColumn] == 'd'){

      p_modele->s_copieEtatBouton[p_NewLine][p_newColumn] = 'z';

      if(parcours_autorise(p_modele, p_NewLine + 1, p_newColumn, p_memLine, p_memColumn))
         return 1;

      if(parcours_autorise(p_modele, p_NewLine, p_newColumn + 1, p_memLine, p_memColumn))
         return 1;

      if(parcours_autorise(p_modele, p_NewLine - 1, p_newColumn, p_memLine, p_memColumn))
         return 1;

      if(parcours_autorise(p_modele, p_NewLine, p_newColumn - 1, p_memLine, p_memColumn))
         return 1;

      p_modele->s_copieEtatBouton[p_NewLine][p_newColumn] = 'd';
      return 0;
   }
   return 0;
}//fin parcours_autorise

int case_deplacable(Modele* p_modele, int p_ligne, int p_colonne){
	assert(p_modele != NULL && p_ligne >= 0 && p_colonne >= 0);

	if(p_ligne > 0 && p_modele->s_etatBouton[p_ligne-1][p_colonne] == 'd')
		return 1;

	if(p_ligne < p_modele->s_lignes-1 && p_modele->s_etatBouton[p_ligne+1][p_colonne] == 'd')
		return 1;

	if(p_colonne > 0 && p_modele->s_etatBouton[p_ligne][p_colonne-1] == 'd'){
		return 1;
	}

	if(p_colonne < p_modele->s_lignes-1 && p_modele->s_etatBouton[p_ligne][p_colonne+1] == 'd'){
		return 1;
	}

	return 0;
}

unsigned int deplacement_etat(Modele *p_modele, unsigned int p_ligne, unsigned int p_colonne) { /* @suppress("No return") */
	assert(p_modele != NULL);
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);

	unsigned int l_numCaseClick;
	unsigned int l_numCaseMem;

	l_numCaseClick = convert_coord_num(p_ligne, p_colonne, p_modele->s_colonnes);
	l_numCaseMem = convert_coord_num(p_modele->s_positionBoutonTemp[0], p_modele->s_positionBoutonTemp[1], p_modele->s_colonnes);

	if (p_modele->s_etatBoutonTemp == BLOCK) { 											/* si on a pas de bouton mem */

		if (p_modele->s_etatBouton[p_ligne][p_colonne] != DEFAULT_IMG) { 				/* si bouton cliqué occupé */
			if(case_deplacable(p_modele, p_ligne, p_colonne)){										/*si au moins une case est accessible autour de lui*/
				p_modele->s_etatBoutonTemp = p_modele->s_etatBouton[p_ligne][p_colonne]; 	/* on mémorise son état */
				p_modele->s_positionBoutonTemp[0] = p_ligne; 								/* et sa position en ligne */
				p_modele->s_positionBoutonTemp[1] = p_colonne; 								/* et sa position en colonne */
				return (0);
			}
		}
	} else { /*si on a un bouton memorisé */
		if (p_modele->s_etatBouton[p_ligne][p_colonne] == DEFAULT_IMG) {												/*si le bouton cliqué est vide */

			for(int i = 0; i < p_modele->s_lignes; i++){
				for(int j = 0; j < p_modele->s_colonnes; j++){																			/*on crée une copie de la grille */
					p_modele->s_copieEtatBouton[i][j] = p_modele->s_etatBouton[i][j];
				}
			}

			if(parcours_autorise(p_modele, p_ligne, p_colonne, p_modele->s_positionBoutonTemp[0], p_modele->s_positionBoutonTemp[1])){			/*si le chemin est accessible */
				p_modele->s_etatBouton[p_ligne][p_colonne] = p_modele->s_etatBoutonTemp; 									/*on copie le premier bouton ds le deuxième */
				p_modele->s_etatBouton[p_modele->s_positionBoutonTemp[0]][p_modele->s_positionBoutonTemp[1]] = DEFAULT_IMG; /*premier bouton se vide */
				p_modele->s_etatBoutonTemp = BLOCK; 																	    /*on supprime le bouton mémorisé */
				remove_case_libre(p_modele, l_numCaseClick);
				add_case_libre(p_modele, l_numCaseMem);
				return (1);
			}
		}
	}
}

void incrementer_score(Modele *p_modele, unsigned int p_nombre) {
	assert(p_nombre >= 0);

	switch (p_nombre) {

	case 5: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 10; /* @suppress("Avoid magic numbers") */
		break;

	case 6: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 12; /* @suppress("Avoid magic numbers") */
		break;

	case 7: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 18; /* @suppress("Avoid magic numbers") */
		break;

	case 8: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 28; /* @suppress("Avoid magic numbers") */
		break;

	case 9: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 42; /* @suppress("Avoid magic numbers") */
		break;
	case 10: /* @suppress("Avoid magic numbers") */

		p_modele->s_score += 82; /* @suppress("Avoid magic numbers") */
		break;

	case 11: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 108; /* @suppress("Avoid magic numbers") */
		break;

	case 12: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 138; /* @suppress("Avoid magic numbers") */
		break;

	case 13: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 172; /* @suppress("Avoid magic numbers") */
		break;

	case 14: /* @suppress("Avoid magic numbers") */
		p_modele->s_score += 210; /* @suppress("Avoid magic numbers") */
		break;

	default:
		printf("erreur incrementation score\n");
		break;
	}
}

int victoire_detect(Modele *p_modele) {
	assert(p_modele != NULL);

	for (int i = 0; i < p_modele->s_lignes; i++) {
		int l_compteurHoriz;
		l_compteurHoriz = 1;

		for (int j = 0; j < p_modele->s_colonnes - 1; j += l_compteurHoriz) {

			for (int k = j; k < p_modele->s_colonnes - 1
							&& p_modele->s_etatBouton[i][k] != DEFAULT_IMG
							&& p_modele->s_etatBouton[i][k] == p_modele->s_etatBouton[i][k + 1]; k++) {
				l_compteurHoriz++;
			}

			if (l_compteurHoriz >= 5) {

				for (int l = j, cpt = 0; cpt < l_compteurHoriz; cpt++, l++) {
					int l_num;
					p_modele->s_etatBouton[i][l] = DEFAULT_IMG;
					l_num = convert_coord_num(i, l, p_modele->s_colonnes);
					add_case_libre(p_modele, l_num);
				}
				incrementer_score(p_modele, l_compteurHoriz);
				return (1);
			}
		}
	}

	for (int i = 0; i < p_modele->s_colonnes; i++) {
		int l_compteurVertical;
		l_compteurVertical = 1;

		for (int j = 0; j < p_modele->s_lignes - 1; j += l_compteurVertical) {

			for (int k = j; k < p_modele->s_lignes - 1
							&& p_modele->s_etatBouton[k][i] != DEFAULT_IMG
							&& p_modele->s_etatBouton[k][i] == p_modele->s_etatBouton[k + 1][i]; k++) {
				l_compteurVertical++;
			}
			if (l_compteurVertical >= 5) {

				for (int l = j, cpt = 0; cpt < l_compteurVertical; l++, cpt++) {
					int l_num;
					p_modele->s_etatBouton[l][i] = DEFAULT_IMG;
					l_num = convert_coord_num(l, i, p_modele->s_colonnes);
					add_case_libre(p_modele, l_num);
				}
				incrementer_score(p_modele, l_compteurVertical);
				return (1);
			}
		}
	}

	int l_compteurDiagonalDrt;
	l_compteurDiagonalDrt = 1;

	for (int i = 0; i < p_modele->s_lignes - 1; i += l_compteurDiagonalDrt) {

		for (int j = 0; j < p_modele->s_colonnes - 1; j += l_compteurDiagonalDrt) {

			for (int k = i, l = j; k < p_modele->s_lignes - 1 && l < p_modele->s_colonnes - 1
							&& p_modele->s_etatBouton[k][l] != DEFAULT_IMG
							&& p_modele->s_etatBouton[k][l] == p_modele->s_etatBouton[k + 1][l + 1]; k++, l++) {
				l_compteurDiagonalDrt++;
			}
			if (l_compteurDiagonalDrt >= 5) {

				for (int m = i, n = j, cpt = 0; cpt < l_compteurDiagonalDrt && m < p_modele->s_lignes
								&& n < p_modele->s_colonnes; m++, n++, cpt++) {
					int l_num;
					p_modele->s_etatBouton[m][n] = DEFAULT_IMG;
					l_num = convert_coord_num(m, n, p_modele->s_colonnes);
					add_case_libre(p_modele, l_num);
				}
				incrementer_score(p_modele, l_compteurDiagonalDrt);
				return (1);
			}
		}
	}

	int l_compteurDiagonalGch = 1;

	for (int i = p_modele->s_lignes - 1; i >= 0; i -= l_compteurDiagonalGch) {

		for (int j = 0; j < p_modele->s_colonnes - 1; j += l_compteurDiagonalGch) {

			for (int k = i, l = j; k > 0 && l < p_modele->s_colonnes - 1
							&& p_modele->s_etatBouton[k][l] != DEFAULT_IMG
							&& p_modele->s_etatBouton[k][l] == p_modele->s_etatBouton[k - 1][l + 1]; k--, l++) {
				l_compteurDiagonalGch++;
			}
			if (l_compteurDiagonalGch >= 5) {

				for (int m = i, n = j, cpt = 0; cpt < l_compteurDiagonalGch; m--, n++, cpt++) {
					int l_num;
					p_modele->s_etatBouton[m][n] = DEFAULT_IMG;
					l_num = convert_coord_num(m, n, p_modele->s_colonnes);
					add_case_libre(p_modele, l_num);
				}
				incrementer_score(p_modele, l_compteurDiagonalGch);
				return (1);
			}
		}
	}
	return (0);
}

/* GETTERS & SETTERS */

char get_etat_bouton_suivant(Modele *p_modele, unsigned int p_count) {
	assert(p_modele != NULL);
	assert(p_count >= 0);
	return (p_modele->s_etatBoutonSuivant[p_count]);
}

char get_etat_bouton(Modele *p_modele, unsigned int p_ligne, unsigned int p_colonne) {
	assert(p_modele != NULL);
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);
	return (p_modele->s_etatBouton[p_ligne][p_colonne]);
}

char get_etat_bouton_temp(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_etatBoutonTemp);
}

char* get_filename(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_filename);
}

const char* get_nom(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_nom);
}

void set_nom(Modele *p_modele, const char *p_nom) {
	assert(p_modele != NULL);
	p_modele->s_nom = p_nom;
}

unsigned int get_nb_boutons_suivants(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_nbBoutonsSuivants);
}

unsigned int get_score(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_score);
}

unsigned int get_modele_lignes(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_lignes);
}

unsigned int get_modele_colonnes(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_colonnes);
}

unsigned int* get_position_bouton_temp(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_positionBoutonTemp);
}

unsigned int get_taille_tab_libre(Modele *p_modele) {
	assert(p_modele != NULL);
	return (p_modele->s_tailleTabLibre);
}

void set_taille_tab_libre(Modele *p_modele, unsigned int p_taille) {
	assert(p_modele != NULL);
	assert(p_taille >= 0);
	p_modele->s_tailleTabLibre = p_taille;
}

void set_etat_bouton(Modele *p_modele, char p_etat, unsigned int p_ligne, unsigned int p_colonne) {
	assert(p_modele != NULL);
	assert(p_ligne >= 0);
	assert(p_colonne >= 0);

	p_modele->s_etatBouton[p_ligne][p_colonne] = p_etat;
}
