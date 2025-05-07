#ifndef UTILS_H
#define UTILS_H

void vider_buffer();
void lireChaine(const char *invite, char *buffer, int tailleMax);
int lireEntier(const char *invite, int min, int max);
void lireChaineFacultative(const char *message, char *chaine, int taille);
int compter_mots(const char *texte);
void nettoyer_chaine(char *chaine);
void to_lowercase(char *str);
void to_lowercase_str(char *dest, const char *src);

#endif