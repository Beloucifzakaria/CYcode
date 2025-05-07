#include <stdio.h>
#include <stdlib.h>

#include "ajout.h"
#include "recherche.h"
#include "adoption.h"
#include "affichage.h"
#include "quiz.h"
#include "utils.h"

int main() {
    system("chcp 65001 >nul"); // Pour l'encodage UTF-8 sur Windows

    int choix;
    const char *fichier = "animaux/animaux.txt";

    while (1) {
        printf("\n=========================================\n");
        printf("        🐾 MENU DU REFUGE ANIMALIER 🐾\n");
        printf("=========================================\n");
        printf("1. Ajouter un nouvel animal\n");
        printf("2. Rechercher des animaux\n");
        printf("3. Adopter un animal\n");
        printf("4. Inventaire\n");
        printf("5. Nourriture quotidienne necessaire\n");
        printf("6. Quizz - Trouve ton compagnon idéal\n");
        printf("7. Quitter\n");
        printf("-----------------------------------------\n");
        printf("Entrez votre choix : ");

        choix = lireChoixUtilisateur();

        if (choix == -1) {
            printf("❌ Choix invalide ! Veuillez saisir un chiffre entre 1 et 7.\n");
            continue;
        }

        switch (choix) {
            case 1:
                ajouter_animal(fichier);
                break;
            case 2:
                rechercher_animaux(fichier);
                break;
            case 3:
                adopter_animal(fichier);
                break;
            case 4:
                inventaire(fichier);
                break;
            case 5:
                nourriture_quotidienne(fichier);
                break;
            case 6:
                lancer_quiz(fichier);
                break;
            case 7:
                printf("\n👋 Merci et à bientôt !\n");
                return 0;
            default:
                printf("❌ Choix invalide ! Essayez à nouveau.\n");
        }
    }

    return 0;
}