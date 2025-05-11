#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "animaux.h"
#include "utils.h"
#include "affichage.h"

// Création du dossier "animaux" s'il n'existe pas
void creer_dossier_animaux() {
if (mkdir("animaux", 0777) == 0) {
printf("Le dossier 'animaux' a été créé avec succès.\n");
} else {
perror("Erreur lors de la création du dossier");
}
}

// Génère un ID unique pour chaque nouvel animal
int generer_id(const char *fichier) {
FILE *file = fopen(fichier, "r");
int max_id = 0;
if (file) {
char ligne[256];
int id;
while (fgets(ligne, sizeof(ligne), file)) {
if (sscanf(ligne, "%d", &id) == 1 && id > max_id)
max_id = id;
}
fclose(file);
}
return max_id + 1;
}

// Affiche les informations d’un animal
void afficher_animal(const Animal *animal) {
char ligne[512];

snprintf(ligne, sizeof(ligne), "🐾 ID : %d", animal->id);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "📛 Nom : %s", animal->nom);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "🦴 Espèce : %s", animal->espece);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "📆 Naissance : %d", animal->annee_naissance);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "⚖️ Poids : %.2f kg", animal->poids);
afficher_centre_plein(ligne);

if (strlen(animal->description) == 0 || strspn(animal->description, " \t\n") == strlen(animal->description)) {
snprintf(ligne, sizeof(ligne), "📝 Description : Aucune description");
} else {
snprintf(ligne, sizeof(ligne), "📝 Description : %s", animal->description);
}

afficher_centre_plein(ligne);
}
