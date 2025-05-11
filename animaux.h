#ifndef ANIMAUX_H
#define ANIMAUX_H

#define MAX_ANIMAUX 50
#define FICHIER_ANIMAUX "animaux/animaux.txt"

typedef struct {
int id;
char nom[20];
char espece[20];
int annee_naissance;
float poids;
char description[200];
} Animal;

typedef struct {
char espece[20];
int compteur;
} StatEspece;

// Fonctions de gestion des animaux
void creer_dossier_animaux();
int generer_id(const char *fichier);
void ajouter_animal(const char *fichier);
void afficher_animal(const Animal *animal);
void rechercher_animaux(const char *fichier);
void adopter_animal(const char *fichier);
void inventaire(const char *fichier);
void nourriture_quotidienne(const char *fichier);

#endif
