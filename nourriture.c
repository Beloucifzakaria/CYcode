// nourriture.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"  // si Animal est défini dedans
#include "nourriture.h"

void nourriture_quotidienne(const char *fichier) {
    FILE *file = fopen(fichier, "r");
    if (!file) {
        printf("❌ Erreur lors de l'ouverture du fichier pour la lecture.\n");
        return;
    }

    float nourriture_totale = 0;
    Animal animal;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {

            if (strcasecmp(animal.espece, "hamster") == 0) {
                nourriture_totale += 0.02;
            } else if (strcasecmp(animal.espece, "autruche") == 0) {
                nourriture_totale += 2.5;
            } else if (strcasecmp(animal.espece, "chien") == 0 ||
                       strcasecmp(animal.espece, "chat") == 0) {
                int age = 2025 - animal.annee_naissance;
                if (age < 2)
                    nourriture_totale += 0.5;
                else
                    nourriture_totale += animal.poids * 0.10;
            }
        }
    }

    fclose(file);
    printf("\n🍽️  Nourriture quotidienne totale nécessaire : %.2f kg\n", nourriture_totale);
}