#ifndef GESTION_ANIMAUX_H
#define GESTION_ANIMAUX_H


#include "structure.h"

int generer_id(const char *fichier);
int valider_espece(const char *espece);
int valider_annee_naissance(const char *espece, int annee_naissance);
int valider_poids(const char *espece, float poids);
void ajouter_animal(const char *fichier);
void afficher_animal(const Animal *animal);
void rechercher_animaux(const char *fichier);
void adopter_animal(const char *fichier);
void inventaire(const char *fichier);
void nourriture_quotidienne(const char *fichier);


#endif
