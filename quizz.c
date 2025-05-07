#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "quizz.h"
#include "utils.h"
#include "structure.h"
#include "affichage.h"

// Fonction du quiz d'adoption
void lancer_quiz(const char *fichier) {
    printf("\n=== 🎯 Quiz d'adoption - Trouvez votre compagnon idéal ===\n");

    int energie, temps, logement;

    printf("1. Quel est votre niveau d'énergie ?\n");
    printf("   1 - Très actif\n");
    printf("   2 - Moyennement actif\n");
    printf("   3 - Plutôt calme\n");
    energie = lireEntier("Votre choix : ", 1, 3);

    printf("\n2. Avez-vous peu de temps à consacrer à un animal ?\n");
    printf("   1 - Oui\n");
    printf("   2 - Non\n");
    temps = lireEntier("Votre choix : ", 1, 2);

    printf("\n3. Vous vivez :\n");
    printf("   1 - En appartement\n");
    printf("   2 - En maison avec jardin\n");
    logement = lireEntier("Votre choix : ", 1, 2);

    char espece_suggeree[20];

    // Déduction de l'espèce suggérée selon les réponses
    if (energie == 1 && temps == 2 && logement == 2) {
        strcpy(espece_suggeree, "chien");
    } else if (energie == 2 && temps == 2 && logement == 1) {
        strcpy(espece_suggeree, "chat");
    } else if (energie == 3 && temps == 1) {
        strcpy(espece_suggeree, "hamster");
    } else if (logement == 2 && temps == 1 && energie != 1) {
        strcpy(espece_suggeree, "autruche");
    } else {
        strcpy(espece_suggeree, "chat");
    }

    printf("\n✅ D'après vos réponses, un **%s** pourrait vous convenir !\n", espece_suggeree);
    printf("Voici les animaux disponibles de cette espèce :\n\n");

    FILE *file = fopen(fichier, "r");
    if (!file) {
        printf("❌ Erreur lors de l'ouverture du fichier.\n");
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
                trouve = 1;
            }
        }
    }

    fclose(file);

    if (!trouve) {
        printf("❌ Aucun animal de cette espèce n'est actuellement disponible.\n");
    }
}