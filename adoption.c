#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adoption.h"
#include "utils.h"     // pour vider_buffer()

#include "animal.h"    // pour la structure Animal

void adopter_animal(const char *fichier) {
    int id;
    printf("\n========== 🏠 Adopter un animal ==========\n");

    // Lecture sécurisée de l’ID
    int saisie_valide = 0;
    do {
        printf("Entrez l'ID de l'animal à adopter : ");
        if (scanf("%d", &id) != 1) {
            printf("❌ Entrée invalide. Veuillez entrer un nombre.\n");
            vider_buffer();
        } else {
            saisie_valide = 1;
        }
    } while (!saisie_valide);
    vider_buffer(); // Important pour ne pas laisser de caractères

    FILE *file = fopen(fichier, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("❌ Erreur lors de l'ouverture des fichiers.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    char ligne[256];
    Animal animal;
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {
            if (animal.id != id) {
                fprintf(temp, "%s", ligne); // Écrire la ligne si ce n’est pas l’animal à supprimer
            } else {
                trouve = 1;
            }
        }
    }

    fclose(file);
    fclose(temp);

    if (trouve) {
        remove(fichier);
        rename("temp.txt", fichier);
        printf("✅ L'animal avec l'ID %d a été adopté avec succès !\n", id);
    } else {
        remove("temp.txt");
        printf("❌ Aucun animal avec l'ID %d trouvé.\n", id);
    }
}