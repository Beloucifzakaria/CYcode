#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX_ANIMAUX 50
#define FICHIER_ANIMAUX "animaux/animaux.txt"

typedef struct {
    int id;
    char nom[20];
    char espece[20];
    int annee_naissance;
    float poids;
    char description[200]; // Facultatif
} Animal;

typedef struct {
    char espece[20];
    int compteur;
} StatEspece;


#endif
