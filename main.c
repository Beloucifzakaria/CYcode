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

while (1) { // Boucle infinie pour afficher le menu principal tant que l'utilisateur ne choisit pas de quitter.

afficher_menu();

while (1) {  // Boucle pour demander à l'utilisateur un choix valide entre 1 et 7.

choix = lireChoixUtilisateur();

if (choix >= 1 && choix <= 7) break;
// Si le choix est entre 1 et 7 on sort de la boucle intérieure.


printf("❌ Choix invalide ! Veuillez saisir un chiffre entre 1 et 7.\n");
}


// En fonction du choix de l'utilisateur (1 à 7) on exécute l'action correspondante.
// Chaque case déclenche une fonctionnalité puis sort du switch grâce au break.
// Seule l'option 7 (quitter) termine réellement le programme avec return 0.
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
