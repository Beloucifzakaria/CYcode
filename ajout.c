#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ajout.h"
#include "utilitaires.h"

int valider_et_formater_nom(char *nom) {
    for (int i = 0; nom[i] != '\0'; i++) {
        if (!isalpha(nom[i])) {
            return 0;
        }
    }

    nom[0] = toupper(nom[0]);
    for (int i = 1; nom[i] != '\0'; i++) {
        nom[i] = tolower(nom[i]);
    }

    return 1;
}

int generer_id(const char *fichier) {
    FILE *file = fopen(fichier, "r");
    int max_id = 0;
    char ligne[256];
    int id;

    if (file) {
        while (fgets(ligne, sizeof(ligne), file)) {
            if (sscanf(ligne, "%d", &id) == 1 && id > max_id) {
                max_id = id;
            }
        }
        fclose(file);
    }

    return max_id + 1;
}

int valider_espece(const char *espece) {
    const char *especes_valides[] = {"chien", "chat", "hamster", "autruche"};
    char espece_min[20];
    to_lowercase_str(espece_min, espece);

    for (int i = 0; i < 4; i++) {
        if (strcmp(espece_min, especes_valides[i]) == 0) {
            return 1;
        }
    }

    printf("❌ Espèce invalide ! Choisissez parmi : chien, chat, hamster, autruche.\n");
    return 0;
}

int valider_annee_naissance(const char *espece, int annee_naissance) {
    int annee_courante = 2025;
    int age = annee_courante - annee_naissance;
    char espece_min[20];
    to_lowercase_str(espece_min, espece);

    if (annee_naissance > annee_courante || annee_naissance < 1900) {
        printf("❌ Année de naissance invalide.\n");
        return 0;
    }

    if ((strcmp(espece_min, "chien") == 0 && age > 20) ||
        (strcmp(espece_min, "chat") == 0 && age > 25) ||
        (strcmp(espece_min, "hamster") == 0 && age > 4) ||
        (strcmp(espece_min, "autruche") == 0 && age > 45)) {
        printf("❌ Âge trop élevé pour cette espèce.\n");
        return 0;
    }

    return 1;
}

int valider_poids(const char *espece, float poids) {
    char espece_min[20];
    to_lowercase_str(espece_min, espece);

    if (poids <= 0) {
        printf("❌ Le poids doit être supérieur à 0.\n");
        return 0;
    }

    if ((strcmp(espece_min, "chien") == 0 && (poids < 1 || poids > 100)) ||
        (strcmp(espece_min, "chat") == 0 && (poids < 1 || poids > 12)) ||
        (strcmp(espece_min, "hamster") == 0 && (poids < 0.02 || poids > 0.2)) ||
        (strcmp(espece_min, "autruche") == 0 && (poids < 50 || poids > 160))) {
        printf("❌ Poids incohérent pour cette espèce.\n");
        return 0;
    }

    return 1;
}

int compter_mots(const char *texte) {
    int mots = 0, dans_mot = 0;
    for (int i = 0; texte[i] != '\0'; i++) {
        if (!isspace(texte[i]) && !dans_mot) {
            mots++;
            dans_mot = 1;
        } else if (isspace(texte[i])) {
            dans_mot = 0;
        }
    }
    return mots;
}

void lireChaineFacultative(const char *message, char *chaine, int taille) {
    int trop_long;
    do {
        trop_long = 0;
        printf("%s", message);
        if (fgets(chaine, taille, stdin) != NULL) {
            size_t len = strlen(chaine);
            if (len > 0 && chaine[len - 1] == '\n') {
                chaine[len - 1] = '\0';
            } else {
                vider_buffer();
                trop_long = 1;
                printf("❌ Saisie trop longue (max %d caractères). Veuillez réessayer.\n", taille - 1);
            }
        } else {
            vider_buffer();
            printf("❌ Erreur de lecture. Veuillez réessayer.\n");
        }
    } while (trop_long);
}

void ajouter_animal(const char *fichier) {
    Animal nouvel_animal;
    nouvel_animal.id = generer_id(fichier);

    printf("\n🐾 === AJOUT D'UN NOUVEL ANIMAL === 🐾\n");

    int nom_valide;
    do {
        lireChaine("➡️  Entrez le nom (max 19 lettres, sans chiffres) : ", nouvel_animal.nom, sizeof(nouvel_animal.nom));
        nom_valide = valider_et_formater_nom(nouvel_animal.nom);
        if (!nom_valide)
            printf("❌ Nom invalide.\n");
    } while (!nom_valide);

    int espece_valide;
    do {
        lireChaine("➡️  Entrez l'espèce (chien, chat, hamster, autruche) : ", nouvel_animal.espece, sizeof(nouvel_animal.espece));
        espece_valide = valider_espece(nouvel_animal.espece);
    } while (!espece_valide);

    int annee_valide;
    do {
        printf("➡️  Entrez l'année de naissance : ");
        if (scanf("%d", &nouvel_animal.annee_naissance) != 1) {
            printf("❌ Entrée invalide.\n");
            vider_buffer();
            annee_valide = 0;
        } else {
            annee_valide = valider_annee_naissance(nouvel_animal.espece, nouvel_animal.annee_naissance);
        }
    } while (!annee_valide);

    int poids_valide;
    do {
        printf("➡️  Entrez le poids (kg) : ");
        if (scanf("%f", &nouvel_animal.poids) != 1) {
            printf("❌ Entrée invalide.\n");
            vider_buffer();
            poids_valide = 0;
        } else {
            poids_valide = valider_poids(nouvel_animal.espece, nouvel_animal.poids);
        }
    } while (!poids_valide);
    getchar();

    int description_valide;
    do {
        lireChaineFacultative("➡️  Entrez une description (facultatif, max 30 mots, 200 caractères) : ", nouvel_animal.description, sizeof(nouvel_animal.description));

        if (strlen(nouvel_animal.description) == 0) {
            strcpy(nouvel_animal.description, "Aucune description");
            description_valide = 1;
        } else if (strlen(nouvel_animal.description) > 200) {
            printf("❌ Trop long.\n");
            description_valide = 0;
        } else {
            int nb_mots = compter_mots(nouvel_animal.description);
            if (nb_mots > 30) {
                printf("❌ Trop de mots : %d\n", nb_mots);
                description_valide = 0;
            } else {
                description_valide = 1;
            }
        }
    } while (!description_valide);

    FILE *file = fopen(fichier, "a");
    if (file) {
        fprintf(file, "%d %s %s %d %.2f %s\n", nouvel_animal.id, nouvel_animal.nom,
                nouvel_animal.espece, nouvel_animal.annee_naissance, nouvel_animal.poids, nouvel_animal.description);
        fclose(file);
        printf("✅ Animal ajouté avec succès !\n");
    } else {
        printf("❌ Erreur : impossible d’ouvrir le fichier.\n");
    }
}