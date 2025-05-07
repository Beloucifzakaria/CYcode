#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "recherche.h"
#include "utils.h"         // pour vider_buffer(), to_lowercase_str()
#include "affichage.h"     // pour afficher_animal()

void rechercher_animaux(const char *fichier) {
    char recherche_nom[50], recherche_espece[20];
    int type_age_recherche;

    printf("\n=== 🔍 Recherche d'animaux ===\n");
    printf("Entrez le nom de l'animal à rechercher : ");
    scanf("%49s", recherche_nom);
    vider_buffer();

    printf("Entrez l'espèce à rechercher : ");
    scanf("%19s", recherche_espece);
    vider_buffer();

    // Choix du type d'âge
    do {
        printf("Rechercher par âge :\n");
        printf("  1 - Jeune (< 2 ans)\n");
        printf("  2 - Senior (> 10 ans)\n");
        printf("  3 - Entre 1 et 10 ans\n");
        printf("Votre choix : ");
        if (scanf("%d", &type_age_recherche) != 1 || type_age_recherche < 1 || type_age_recherche > 3) {
            printf("❌ Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
            vider_buffer();
        } else {
            break;
        }
    } while (1);
    vider_buffer();

    // Conversion en minuscules pour la comparaison
    char recherche_nom_lower[50], recherche_espece_lower[20];
    to_lowercase_str(recherche_nom_lower, recherche_nom);
    to_lowercase_str(recherche_espece_lower, recherche_espece);

    FILE *file = fopen(fichier, "r");
    if (!file) {
        printf("❌ Erreur lors de l'ouverture du fichier pour la lecture.\n");
        return;
    }

    Animal animal;
    char ligne[256];
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {

            char nom_lower[50], espece_lower[20];
            to_lowercase_str(nom_lower, animal.nom);
            to_lowercase_str(espece_lower, animal.espece);

            int age = 2025 - animal.annee_naissance;

            if (strstr(nom_lower, recherche_nom_lower) &&
                strstr(espece_lower, recherche_espece_lower) &&
                ((type_age_recherche == 1 && age < 2) ||
                 (type_age_recherche == 2 && age > 10) ||
                 (type_age_recherche == 3 && age >= 1 && age <= 10))) {

                afficher_animal(&animal);
                trouve = 1;
            }
        }
    }

    if (!trouve) {
        printf("\n❌ Aucun animal correspondant trouvé.\n");
    }

    fclose(file);
}