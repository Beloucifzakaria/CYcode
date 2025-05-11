#include <locale.h>
#include <stdio.h>
#include "animaux.h"
#include "affichage.h"
#include "utils.h"
#include "menu.h"

void afficher_ecran_bienvenue();
void afficher_menu();
void afficher_ecran_sortie();

int main() {
creer_dossier_animaux();
setlocale(LC_ALL, "");
setbuf(stdin, NULL); // Évite les problèmes de buffer

int choix;
const char *fichier = "animaux/animaux.txt";

afficher_ecran_bienvenue();

while (1) {
afficher_menu();

while (1) {
choix = lireChoixUtilisateur();

if (choix >= 1 && choix <= 7) break;

printf("❌ Choix invalide ! Veuillez saisir un chiffre entre 1 et 7.\n");
}

switch (choix) {
case 1: ajouter_animal(fichier); break;
case 2: rechercher_animaux(fichier); break;
case 3: adopter_animal(fichier); break;
case 4: inventaire(fichier); break;
case 5: nourriture_quotidienne(fichier); break;
case 6: lancer_quiz(fichier); break;
case 7:
afficher_ecran_sortie();
return 0;
}
}

return 0;
}
