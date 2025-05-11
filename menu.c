#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "utils.h"
#include "affichage.h"
#include "animaux.h"

void lancer_quiz(const char *fichier) {
afficher_ligne_pleine();
afficher_centre_plein("🎯 QUIZ D’ADOPTION - TROUVEZ VOTRE COMPAGNON IDÉAL");
afficher_ligne_pleine();
printf("\n");

int energie = lireEntier(
"➡️ Quel est votre niveau d'énergie ?\n"
" 1 - Très actif\n"
" 2 - Moyennement actif\n"
" 3 - Plutôt calme\n"
"Votre choix : ", 1, 3);
printf("\n");

int temps = lireEntier(
"➡️ Avez-vous du temps à consacrer à un animal ?\n"
" 1 - Oui\n"
" 2 - Non\n"
"Votre choix : ", 1, 2);
printf("\n");

int logement = lireEntier(
"➡️ Vous vivez :\n"
" 1 - En appartement\n"
" 2 - En maison avec jardin\n"
" 3 - Sur un grand terrain / ferme\n"
"Votre choix : ", 1, 3);
printf("\n");

char espece_suggeree[20];

if (energie == 1 && temps == 1 && logement == 2) {
strcpy(espece_suggeree, "chien");
} else if (energie == 2 && temps == 1 && logement == 1) {
strcpy(espece_suggeree, "chat");
} else if (energie == 3 && temps == 2) {
strcpy(espece_suggeree, "hamster");
} else if (logement == 3) {
strcpy(espece_suggeree, "autruche");
} else {
strcpy(espece_suggeree, "chat");
}

printf("✅ D'après vos réponses, un %s pourrait vous convenir !\n", espece_suggeree);
printf("🔍 Voici les animaux disponibles de cette espèce :\n\n");

FILE *file = fopen(fichier, "r");
if (!file) {
printf("❌ Erreur : impossible d'ouvrir le fichier %s.\n", fichier);
printf("\nAppuyez sur Entrée pour revenir au menu...");
getchar();
return;
}

Animal animal;
char ligne[256];
int trouve = 0;

while (fgets(ligne, sizeof(ligne), file)) {
if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
&animal.id, animal.nom, animal.espece,
&animal.annee_naissance, &animal.poids, animal.description) >= 5) {

char espece_lower[20];
to_lowercase_str(espece_lower, animal.espece);

if (strcmp(espece_lower, espece_suggeree) == 0) {
afficher_animal(&animal);
printf("\n");
trouve = 1;
}
}
}

fclose(file);

if (!trouve) {
printf("❌ Aucun animal de cette espèce n'est actuellement disponible.\n");
}

printf("\nAppuyez sur Entrée pour revenir au menu...");
getchar();
system("clear");
}
