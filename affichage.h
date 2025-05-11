#ifndef AFFICHAGE_H
#define AFFICHAGE_H

// Calcule la largeur d'affichage visuelle d'une chaîne UTF-8
int largeur_affichage(const char *texte);

// Récupère la largeur du terminal en colonnes
int obtenir_largeur_terminal();

// Affiche une ligne de séparation avec des égalités
void afficher_ligne_pleine();

// Affiche une ligne de séparation avec des tirets
void afficher_ligne_pleine2();

// Affiche une ligne de texte centrée dans la largeur du terminal
void afficher_centre_plein(const char *texte);

#endif
