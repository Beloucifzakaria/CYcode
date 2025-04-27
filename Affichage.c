#include <stdio.h>

// Couleurs stylisées (utilisation de couleurs plus fraîches)
#define BLUE    "\033[94m"
#define GREEN   "\033[92m"
#define WHITE   "\033[97m"
#define RESET   "\033[0m"

void afficherMenu() {
    printf(BLUE  "╔═══════════════════════════════════════════════════╗\n" RESET);
    printf(BLUE  "║" WHITE "        🌟 Bienvenue au Refuge ChenYl-Tech 🌟        " BLUE "║\n" RESET);
    printf(BLUE  "╚═══════════════════════════════════════════════════╝\n" RESET);

    printf(GREEN " [1] 🐶 Ajouter un animal\n" RESET);
    printf(GREEN " [2] 🔍 Rechercher des animaux\n" RESET);
    printf(GREEN " [3] 🏡 Faire adopter un animal\n" RESET);
    printf(GREEN " [4] 🍖 Nourriture quotidienne\n" RESET);
    printf(GREEN " [5] 📋 Inventaire du refuge\n" RESET);
    printf(GREEN " [6] ❌ Quitter\n" RESET);

    printf(WHITE "\n➡️  Entrez votre choix : " RESET);
}
