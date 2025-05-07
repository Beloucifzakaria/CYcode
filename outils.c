#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lireChaine(const char *invite, char *buffer, int tailleMax) {
    while (1) {
        printf("%s", invite);
        if (fgets(buffer, tailleMax, stdin) == NULL) {
            printf("❌ Erreur de lecture. Veuillez réessayer.\n");
            continue;
        }

        if (strchr(buffer, '\n') == NULL) {
            vider_buffer();
            printf("❌ Entrée trop longue. Max %d caractères.\n", tailleMax - 1);
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("❌ Vous devez entrer quelque chose.\n");
            continue;
        }

        break;
    }
}

int lireEntier(const char *invite, int min, int max) {
    char buffer[100];
    int entier;
    char *fin;

    while (1) {
        printf("%s", invite);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("❌ Erreur de lecture. Réessayez.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            printf("❌ Entrée vide. Veuillez entrer un nombre.\n");
            continue;
        }

        entier = strtol(buffer, &fin, 10);
        if (*fin != '\0') {
            printf("❌ Entrée invalide. Un nombre est requis.\n");
            continue;
        }

        if (entier < min || entier > max) {
            printf("❌ Valeur hors limites (%d à %d).\n", min, max);
            continue;
        }

        return entier;
    }
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
                printf("❌ Trop long. Max %d caractères.\n", taille - 1);
            }
        } else {
            vider_buffer();
            printf("❌ Erreur de lecture.\n");
        }
    } while (trop_long);
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

void nettoyer_chaine(char *chaine) {
    int i = 0;
    while (chaine[i] != '\0') {
        if (chaine[i] == '\n' || chaine[i] == '\r') {
            chaine[i] = '\0';
        }
        i++;
    }
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void to_lowercase_str(char *dest, const char *src) {
    for (int i = 0; src[i]; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[strlen(src)] = '\0';
}