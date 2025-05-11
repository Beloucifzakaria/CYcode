#ifndef UTILS_H
#define UTILS_H

// Saisie et validation
int lireEntier(const char *invite, int min, int max);
int lireChoixUtilisateur();
void lireChaine(const char *invite, char *buffer, int tailleMax);
void lireChaineFacultative(const char *message, char *chaine, int taille);

// Nettoyage d'entrée
void vider_buffer();
void viderBuffer();

// Traitement de chaînes
void to_lowercase(char *str);
void to_lowercase_str(char *dest, const char *src);
int valider_et_formater_nom(char *nom);
void nettoyer_chaine(char *chaine);

// Validations spécifiques
int valider_espece(const char *espece);
int valider_annee_naissance(const char *espece, int annee_naissance);
int valider_poids(const char *espece, float poids);

// Utilitaires divers
int compter_mots(const char *texte);
int comparer_desc(const void *a, const void *b);
int obtenir_annee_actuelle();

#endif
