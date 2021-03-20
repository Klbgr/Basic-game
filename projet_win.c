#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int init_carte (int tab [20][20]);
int affiche_carte (int tab [20][20], int pos [2]);
int deplace_personnage (int tab [20][20], int pos [2]);
int delai (int s);
int couleur ();

int init_carte (int tab [20][20]) {
	int i, j, n, d, p;
	for (i = 0 ; i < 20 ; i++) {
		for (j = 0 ; j < 20 ; j++) {
			n = rand() % 1000;
			if (0 < n && n < 900) {
				n = 0;
			}
			else if (900 < n && n < 920) {
				n = 1;
			}
			else if (920 < n && n < 935) {
				n = 2;
			}
			else if (935 < n && n < 950) {
				n = 3;
			}
//			else if (950 < n && n < 955) {
//				n = 4;
//			}
			else if (950 < n && n < 970) {
				n = 5;
			}
//			else if (975 < n && n < 980) {
//				n = 6;
//			}
			else if (970 < n && n < 985) {
				n = 7;
			}
			else {
				n = 8;
			}
			tab [i][j] = n;
		}
	}
	tab [0][0] = 0;
	d = rand() % 15;
	for (i = d ; i <= d+5 ; i++) {
		if (rand() % 2 == 1) {
			tab [i][15] = 8;
		}
		else {
			tab [i][15] = 0;
		}
		if (i == d || i == d+5) {
			for (j = 16 ; j < 20 ; j++) {
				if (rand() % 2 == 1) {
					tab [i][j] = 8;
				}
				else {
					tab [i][j] = 0;
				}
			}
		}
	}
	for (i = d+1 ; i <= d+4 ; i++) {
		tab [i][16] = 3;
		tab [i][19] = 3;
		if (i == d+1 || i == d+4) {
			for (j = 17 ; j <= 18 ; j++) {
				tab [i][j] = 3;
			}
		}
	}
	for (i = d+2 ; i <= d+3 ; i++){
		for (j = 17 ; j <= 18 ; j++) {
			tab [i][j] = 5;
		}
	}
	p = d + 2 + rand() % 2;
	tab [p][15] = 0;
	tab [p][16] = 6;
	tab [1 + rand() % 19][1 + rand() % 14] = 4;
}

int affiche_carte (int tab [20][20], int pos [2]) {
	int i, j;
	for (i = 0 ; i < 20 ; i++) {
		for (j = 0 ; j < 20 ; j++) {
			if (pos [0] == j && pos [1] == i) {
				couleur (2);
				printf("X ");
				couleur (15);
			}
			else {
				switch (tab [i][j]) {
					case 0 :
						couleur (2);
						printf(". ");
						couleur (15);
						break;
					case 1 :
						couleur (11);
						printf("F ");
						couleur (15);
						break;
					case 2 :
						printf("A ");
						break;
					case 3 :
						printf("R ");
						break;
					case 4 :
						couleur (13);
						printf("C ");
						couleur (15);
						break;
					case 5 :
						couleur (6);
						printf("O ");
						couleur (15);
						break;
					case 6 :
						couleur (13);
						printf("0 ");
						couleur (15);
						break;
					case 7 :
						couleur (4);
						printf("P ");
						couleur (15);
						break;
					case 8 :
						couleur (4);
						printf("M ");
						couleur (15);
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
		printf("Ou voulez vous aller ? (zqsd ou fleches directionnelles, echap=quitter)\n");
//		printf("Position : x = %d, y = %d\n", pos [0], pos [1]);
		r = getch();
		switch (r) {
		    case 72 :
			case 122 :
            case 90 :
				if (y == 0 || tab [y-1][x] == 2 || tab [y-1][x] == 3) {
					couleur (4);
					printf("Obstacle !\n");
					couleur (15);
					delai (2);
					break;
				}
				else {
					y = y - 1;
					break;
				}
            case 80 :
			case 115 :
            case 83 :
				if (y == 19 || tab [y+1][x] == 2 || tab [y+1][x] == 3) {
					couleur (4);
					printf("Obstacle !\n");
					couleur (15);
					delai (2);
					break;
				}
				else {
					y = y + 1;
					break;
				}
            case 77 :
			case 100 :
            case 68 :
				if (x == 19 || tab [y][x+1] == 2 || tab [y][x+1] == 3) {
					couleur (4);
					printf("Obstacle !\n");
					couleur (15);
					delai (2);
					break;
				}
				else {
					x = x + 1;
					break;
				}
            case 75 :
            case 113 :
			case 81 :
				if (x == 0 || tab [y][x-1] == 2 || tab [y][x-1] == 3) {
					couleur (4);
					printf("Obstacle !\n");
					couleur (15);
					delai (2);
					break;
				}
				else {
					x = x - 1;
					break;
				}
			case 27 :
				printf("Au revoir !\n");
				delai (3);
				return -1;
				break;
		}
		return pos [0] = x, pos [1] = y, tab [y][x];
	}
}

int delai (int s) {
	s = time(0) + s;
	while (time(0) <  s);
}

int couleur (int c) {
	int h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, c);
}

int main () {
	printf("Bonjour !\n-Le but du jeu est de collecter 10 pieces d'or (");
	couleur (6);
	printf("O");
	couleur (15);
	printf(").\n-La clef (");
	couleur (13);
	printf("C");
	couleur (15);
	printf(") sert a ouvrir la porte (");
	couleur (13);
	printf("0");
	couleur (15);
	printf(").\n-Les rochers (R) et les arbres (A) sont infranchissables.\n-Attention a bien eviter les monstres (");
	couleur (4);
	printf("M");
	couleur (15);
	printf(") et les pieges (");
	couleur (4);
	printf("P");
	couleur (15);
	printf(").\n-Si le nombre de vies tombe a 0, c'est GAME OVER !\nBon jeu et profitez bien des fleurs (");
	couleur (11);
	printf("F");
	couleur (15);
	printf(") !\nAppuyez pour continuer...");
	getch();
	srand(time(NULL));
	int tab [20][20];
	int pos [2] = {0, 0};
	int i, j, jeu = 1, vie = 10, or = 0, clef = 0, verif = 0;
	while (verif < 10) {
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
	while (jeu != -1) {
		for (i = 0 ; i <= 20 ; i++) {
			printf("\n");
		}
		couleur (2);
		printf("Vie(s) : %d\t", vie);
		couleur (6);
		printf("Or : %d\t", or);
        couleur (13);
		printf("Clef : %d\n", clef);
		couleur (15);
		affiche_carte (tab, pos);
		jeu = deplace_personnage (tab, pos);
		if (jeu == 4) {
			clef = clef + 1;
			tab [pos [1]][pos [0]] = 0;
		}
		if (jeu == 5) {
			or = or + 1;
			tab [pos [1]][pos [0]] = 0;
		}
		if (jeu == 7 || jeu == 8) {
			couleur (4);
			printf("Attention aux monstres et aux pieges !\n");
			couleur (15);
			delai (2);
			vie = vie - 1;
			tab [pos [1]][pos [0]] = 0;
		}
		if (jeu == 6) {
			if (clef == 0) {
				couleur (13);
				printf("Pas de clef !\n");
				couleur (15);
				delai (2);
				pos [0] = pos [0] - 1;
			}
			else {
				clef = clef - 1;
				tab [pos [1]][pos [0]] = 0;
			}
		}
		if (vie == 0) {
			couleur (4);
			printf("GAME OVER\n");
			couleur (15);
			printf("Appuyez pour terminer...");
			getch();
			return jeu = -1;
		}
		if (or == 10) {
			couleur (4);
			printf("B");
			couleur (2);
			printf("R");
			couleur (6);
			printf("A");
			couleur (1);
			printf("V");
			couleur (13);
			printf("O ");
			couleur (11);
			printf("!\n");
			couleur (15);
			printf("Appuyez pour terminer...");
			getch();
			return jeu = -1;
		}
	}
}
