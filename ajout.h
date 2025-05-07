#ifndef AJOUT_H
#define AJOUT_H

#include "structures.h"

// Déclaration de la fonction pour ajouter un animal
void ajouter_animal(const char *fichier);

// Déclaration de la fonction pour valider et formater un nom
int valider_et_formater_nom(char *nom);

// Déclaration de la fonction pour générer un ID unique
int generer_id(const char *fichier);

// Déclaration de la fonction pour valider une espèce
int valider_espece(const char *espece);

// Déclaration de la fonction pour valider l'année de naissance
int valider_annee_naissance(const char *espece, int annee_naissance);

// Déclaration de la fonction pour valider le poids
int valider_poids(const char *espece, float poids);

// Déclaration de la fonction pour compter les mots dans un texte
int compter_mots(const char *texte);

// Déclaration de la fonction de lecture facultative d'une chaîne
void lireChaineFacultative(const char *message, char *chaine, int taille);

#endif