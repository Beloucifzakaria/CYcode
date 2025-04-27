#include "animal.h"
#include <stdio.h>

#define CYAN    "\033[96m"
#define YELLOW  "\033[93m"
#define RED     "\033[91m"
#define RESET   "\033[0m"

int stringsEgaux(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        char ca = a[i];
        char cb = b[i];

        if (ca >= 'A' && ca <= 'Z') ca += 32;
        if (cb >= 'A' && cb <= 'Z') cb += 32;

        if (ca != cb)
            return 0;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

Espece strToEspece(const char* str) {
    if (stringsEgaux(str, "Chien")) return CHIEN;
    if (stringsEgaux(str, "Chat")) return CHAT;
    if (stringsEgaux(str, "Hamster")) return HAMSTER;
    if (stringsEgaux(str, "Autruche")) return AUTRUCHE;
    return -1;
}

const char* especeToStr(Espece e) {
    switch (e) {
        case CHIEN: return "Chien";
        case CHAT: return "Chat";
        case HAMSTER: return "Hamster";
        case AUTRUCHE: return "Autruche";
        default: return "Inconnu";
    }
}

Espece choisirEspece() {
    int c;
    char input;

    while (1) {
        printf(CYAN "\n📋 Choisissez une espèce d’animal :\n" RESET);
        printf(YELLOW "  1️⃣  Chien     🐶\n" RESET);
        printf(YELLOW "  2️⃣  Chat      🐱\n" RESET);
        printf(YELLOW "  3️⃣  Hamster   🐹\n" RESET);
        printf(YELLOW "  4️⃣  Autruche  🦤\n" RESET);
        printf(CYAN "\n➡️  Votre choix (1-4) : " RESET);

        if (scanf(" %c", &input) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        if (input >= '1' && input <= '4') {
            if (getchar() == '\n') {
                return (Espece)(input - '1');
            } else {
                printf(RED "⚠️  Erreur : Entrez UN SEUL chiffre.\n" RESET);
                while ((c = getchar()) != '\n' && c != EOF);
            }
        } else {
            printf(RED "❌ Entrée invalide. Veuillez choisir un chiffre entre 1 et 4.\n" RESET);
        }

        while ((c = getchar()) != '\n' && c != EOF);
    }
}
