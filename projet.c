#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//fonctions
int init_carte (int tab [20][20]);
int affiche_carte (int tab [20][20], int pos [2]);
int deplace_personnage (int tab [20][20], int pos [2]);
int delai (int s); //sert a faire un decompte de s secondes

//ecriture en couleur
#define cd "\033[0m" //normal
#define cr "\033[31m" //rouge
#define cv "\033[32m" //vert
#define cj "\033[33m" //jaune
#define cb "\033[34m" //bleu
#define cm "\033[35m" //magenta
#define cc "\033[36m" //cyan

int init_carte (int tab [20][20]) {
	int i, j, n, d, p;
	for (i = 0 ; i < 20 ; i++) {
		for (j = 0 ; j < 20 ; j++) {
			n = rand() % 1000; //rempli carte au hasard avec un taux de chaque element defini sur 1000
			if (0 < n && n < 900) {
				n = 0; //herbe
			}
			else if (900 < n && n < 920) {
				n = 1; //fleur
			}
			else if (920 < n && n < 935) {
				n = 2; //arbre
			}
			else if (935 < n && n < 950) {
				n = 3; //rocher
			}
			else if (950 < n && n < 970) {
				n = 5; //or
			}
			else if (970 < n && n < 985) {
				n = 7; //piege
			}
			else {
				n = 8; //monstre
			}
			tab [i][j] = n;
		}
	}
	tab [0][0] = 0; //le joueur commencera toujours sur de l'herbe
	//generation d'un "donjon" 4*4 avec monstres autour
	d = rand() % 15; //choisi au hasard coordonnees du donjon <= 15 pour pas depasser du jeu
	for (i = d ; i <= d+5 ; i++) {
		if (rand() % 2 == 1) { //place avec 1 chance sur 2 pour chaque case des monstres autour du donjon sinon herbe
			tab [i][15] = 8; //monstre
		}
		else {
			tab [i][15] = 0; //herbe
		}
		if (i == d || i == d+5) {
			for (j = 16 ; j < 20 ; j++) {
				if (rand() % 2 == 1) { //place avec 1 chance sur 2 pour chaque case des monstres autour du donjon sinon herbe
					tab [i][j] = 8; //monstre
				}
				else {
					tab [i][j] = 0; //herbe
				}
			}
		}
	}
	for (i = d+1 ; i <= d+4 ; i++) { //mur du donjon fait avec rochers
		tab [i][16] = 3;
		tab [i][19] = 3;
		if (i == d+1 || i == d+4) {
			for (j = 17 ; j <= 18 ; j++) {
				tab [i][j] = 3;
			}
		}
	}
	for (i = d+2 ; i <= d+3 ; i++){ //place 4 pieces d'or dans le donjon
		for (j = 17 ; j <= 18 ; j++) {
			tab [i][j] = 5;
		}
	}
	p = d + 2 + rand() % 2; //defini les coordonnees de la porte 
	tab [p][15] = 0; //assure que la porte est accessible
	tab [p][16] = 6; //porte
	tab [1 + rand() % 19][1 + rand() % 14] = 4; //place au hasard une clef sur la carte
}

int affiche_carte (int tab [20][20], int pos [2]) { //affichage personnalise de chaque element
	int i, j;
	for (i = 0 ; i < 20 ; i++) {
		for (j = 0 ; j < 20 ; j++) {
			if (pos [0] == j && pos [1] == i) {
				printf("%sX %s", cv, cd); //affiche joueur X vert
			}
			else {
				switch (tab [i][j]) {
					case 0 :
						printf("%s. %s", cv, cd); //herbe . vert
						break;
					case 1 :
						printf("%sF %s", cc, cd); //fleur F cyan
						break;
					case 2 :
						printf("A "); //arbre A normal
						break;
					case 3 :
						printf("R "); //rocher R normal
						break;
					case 4 :
						printf("%sC %s", cm, cd); //clef C magenta
						break;
					case 5 :
						printf("%sO %s", cj, cd); //or O jaune
						break;
					case 6 :
						printf("%s0 %s", cm, cd); //cadenas/porte 0 magenta
						break;
					case 7 :
						printf("%sP %s", cr, cd); //piege P rouge
						break;
					case 8 :
						printf("%sM %s", cr, cd); //monstre M rouge
						break;
				}
			}
		}
		printf("\n");
	}
}

int deplace_personnage (int tab [20][20], int pos [2]) {
	int  r = 1, x = pos [0], y = pos [1];
	while (r != 0) {
		printf("Ou voulez vous aller ? (8=haut, 2=bas, 6=droite, 4=gauche, 0=quitter)\n");
//		printf("Position : x = %d, y = %d\n", pos [0], pos [1]); //affiche coordonnees x y
		if(scanf("%d", &r) != 1) { //si le joueur entre autre qu'un nombre, evite le plantage du jeu
			printf("%sERREUR, commande invalide. Abandon...\n%s", cr, cd);
			delai (3);
			exit(EXIT_FAILURE); //fin du jeu due a l'erreur
		}
		switch (r) {
			case 8 :
				if (y == 0 || tab [y-1][x] == 2 || tab [y-1][x] == 3) { //empeche joueur de sortir du jeu ou d'aller sur des obstacles
					printf("%sObstacle !\n%s", cr, cd);
					delai (2);
					break;
				}
				else {
					y = y - 1; //haut
					break;
				}
			case 2 :
				if (y == 19 || tab [y+1][x] == 2 || tab [y+1][x] == 3) { //empeche joueur de sortir du jeu ou d'aller sur des obstacles
					printf("%sObstacle !\n%s", cr, cd);
					delai (2);
					break;
				}
				else {
					y = y + 1; //bas
					break;
				}
			case 6 :
				if (x == 19 || tab [y][x+1] == 2 || tab [y][x+1] == 3) { //empeche joueur de sortir du jeu ou d'aller sur des obstacles
					printf("%sObstacle !\n%s", cr, cd);
					delai (2);
					break;
				}
				else {
					x = x + 1; //droite
					break;
				}
			case 4 :
				if (x == 0 || tab [y][x-1] == 2 || tab [y][x-1] == 3) { //empeche joueur de sortir du jeu ou d'aller sur des obstacles
					printf("%sObstacle !\n%s", cr, cd);
					delai (2);
					break;
				}
				else {
					x = x - 1; //gauche
					break;
				}
			case 0 : //quitter le jeu
				printf("Au revoir !\n");
				delai (3);
				return -1;
				break;
		}
		return pos [0] = x, pos [1] = y, tab [y][x]; //retourne la position du joueur et l'element sur lequel le joueur est
	}
}

int delai (int s) {
	s = time(0) + s;
	while (time(0) <  s);
}

int main () {
	//initialisation du jeu et instructions
	printf("Bonjour !\n-Le but du jeu est de collecter 10 pieces d'or (%sO%s).\n-La clef (%sC%s) sert a ouvrir la porte (%s0%s).\n-Les rochers (R) et les arbres (A) sont infranchissables.\n-Attention a bien eviter les monstres (%sM%s) et les pieges (%sP%s).\n-Si le nombre de vies tombe a 0, c'est GAME OVER !\nBon jeu et profitez bien des fleurs (%sF%s) !\n", cj, cd, cm, cd, cm, cd, cr, cd, cr, cd, cc, cd);
	delai (5);
	srand(time(NULL)); //initialise pour pouvoir utiliser le hasard
	int tab [20][20]; //crée carte 20*20
	int pos [2] = {0, 0}; //position du joueur
	int i, j, jeu = 1, vie = 10, or = 0, clef = 0, verif = 0;
	while (verif < 10) { //verifie le jeu, on cherche a avoir exactement 10 pieces d'or sur la carte, sinon on refait une nouvelle carte 
		verif = 0;
		init_carte (tab);
		for (i = 0 ; i < 20 ; i++) {
			for (j = 0 ; j < 20 ; j++) {
				if (tab [i][j] == 5) {
					verif = verif + 1;
				}
			}
		}
		if (verif > 10) {
			verif = 0;
		}
	}
	//jeu
	while (jeu != -1) {
		for (i = 0 ; i <= 20 ; i++) { //saute des lignes pour faire disparaitre les anciennes cartes
			printf("\n");
		}
		printf("%sVie(s) : %d\t%sOr : %d\t%sClef : %d\n%s", cv, vie, cj, or, cm, clef, cd);
		affiche_carte (tab, pos);
		jeu = deplace_personnage (tab, pos); //stocke dans jeu l'element sur lequel le joueur est
		if (jeu == 4) { //ramasse clef et remplace par herbe
			clef = clef + 1;
			tab [pos [1]][pos [0]] = 0; 
		}
		if (jeu == 5) { //ramasse or et remplace par herbe
			or = or + 1;
			tab [pos [1]][pos [0]] = 0;
		}
		if (jeu == 7 || jeu == 8) { //enleve 1 de vie pour monstre et piege
			printf("%sAttention aux monstres et aux pieges !\n%s", cr, cd);
			delai (2);
			vie = vie - 1;
			tab [pos [1]][pos [0]] = 0;
		}
		if (jeu == 6) { //rencontre de porte/cadenas
			if (clef == 0) { //pas de clef = bloquage
				printf("%sPas de clef !\n%s", cm, cd);
				delai (2);
				pos [0] = pos [0] - 1;
			}
			else { //sinon utilise la clef et ouvre
				clef = clef - 1;
				tab [pos [1]][pos [0]] = 0;
			}
		}
		if (vie == 0) { //perdu
			printf("%sGAME OVER\n%s", cr, cd);
			delai (3);
			return jeu = -1;
		}
		if (or == 10) { //gagne
			printf("%sBRAVO !\n%s", cv, cd);
			delai (3);
			return jeu = -1;
		}
	}
}
