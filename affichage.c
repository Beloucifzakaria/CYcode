#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "affichage.h"

// Récupère la largeur du terminal
int obtenir_largeur_terminal() {
struct winsize w;
if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
return 80; // valeur par défaut
}
return w.ws_col;
}

// Calcule la largeur visuelle (unicode)
int largeur_affichage(const char *texte) {
wchar_t tampon[1024];
mbstate_t etat;
memset(&etat, 0, sizeof(etat));
setlocale(LC_ALL, "");

size_t converti = mbsrtowcs(tampon, &texte, 1024, &etat);
if (converti == (size_t)-1) return strlen(texte);
return wcswidth(tampon, converti);
}

// Affiche une ligne pleine avec "="
void afficher_ligne_pleine() {
int largeur = obtenir_largeur_terminal();
for (int i = 0; i < largeur; i++) {
putchar('=');
}
putchar('\n');
}

// Affiche une ligne pleine avec "-"
void afficher_ligne_pleine2() {
int largeur = obtenir_largeur_terminal();
for (int i = 0; i < largeur; i++) {
putchar('-');
}
putchar('\n');
}

// Affiche du texte centré dans une ligne pleine
void afficher_centre_plein(const char *texte) {
int largeur = obtenir_largeur_terminal();
int len_visuel = largeur_affichage(texte);
int espaces = (largeur - len_visuel) / 2;
if (espaces < 0) espaces = 0;

for (int i = 0; i < espaces; i++) printf(" ");
printf("%s", texte);
for (int i = 0; i < largeur - (espaces + len_visuel); i++) printf(" ");
printf("\n");
}
