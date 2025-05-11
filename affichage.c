#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
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

void afficher_ecran_bienvenue() {
    afficher_ligne_pleine();
    afficher_centre_plein("🐾 BIENVENUE DANS LE REFUGE ANIMALIER 🐾");
    afficher_ligne_pleine();
    printf("\n");
    printf("\n");

    afficher_centre_plein("Ce programme vous permet de :");
    afficher_centre_plein("• Ajouter des animaux 🐶");
    afficher_centre_plein("• Rechercher des pensionnaires 🔍");
    afficher_centre_plein("• Organiser des adoptions 🏠");
    afficher_centre_plein("• Gérer les stocks de nourriture 🍽️");
    afficher_centre_plein("• Trouver un ami fidèle 💖");
    printf("\n");
    
    afficher_centre_plein("Chargement du menu principal en cours...");
    printf("\n");

   
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    sleep(1);

    printf("\n");
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
}

void afficher_menu() {
    system("clear"); 

    
    
    afficher_ligne_pleine();
    afficher_centre_plein("🐾 REFUGE ANIMALIER 🐾");
    afficher_ligne_pleine();
    
   
    printf("\n");

    
    afficher_centre_plein("1. 🐾 AJOUTER UN NOUVEL ANIMAL");
    afficher_centre_plein("2. 🔍 RECHERCHER DES ANIMAUX");
    afficher_centre_plein("3. 🏠 ADOPTER UN ANIMAL");
    afficher_centre_plein("4. 📋 INVENTAIRE");
    afficher_centre_plein("5. 🍽️  NOURRITURE QUOTIDIENNE NÉCESSAIRE");
    afficher_centre_plein("6. ❔ QUIZZ D'ADOPTION");
    afficher_centre_plein("7. ❌ QUITTER");
    
   
    printf("\n");

    printf("\n");
    printf("ENTREZ VOTRE CHOIX : ");
}

void afficher_ecran_sortie() {

    afficher_ligne_pleine();
    afficher_centre_plein("🙏 MERCI D'AVOIR UTILISÉ LE REFUGE ANIMALIER 🙏");
    afficher_ligne_pleine();
    printf("\n");

    afficher_centre_plein("Nous espérons vous revoir bientôt !");
    afficher_centre_plein("Prenez soin de vous et des animaux 🐾");
    printf("\n");

    afficher_centre_plein("Fermeture du programme...");
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf(".");
        fflush(stdout);
    }
    printf("\n\n");

    sleep(1);

    system("clear");
}

