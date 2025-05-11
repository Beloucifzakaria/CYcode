#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "utils.h"
#include "animaux.h"

void vider_buffer() {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}

void viderBuffer() {
vider_buffer();
}

int lireEntier(const char *invite, int min, int max) {
char buffer[100];
int entier;
char *fin;
while (1) {
printf("%s", invite);
if (!fgets(buffer, sizeof(buffer), stdin)) continue;
if (strchr(buffer, '\n') == NULL) vider_buffer();
buffer[strcspn(buffer, "\n")] = '\0';
if (strlen(buffer) == 0) continue;
entier = strtol(buffer, &fin, 10);
if (*fin != '\0') continue;
if (entier < min || entier > max) continue;
return entier;
}
}

int lireChoixUtilisateur() {
char buffer[256];
if (!fgets(buffer, sizeof(buffer), stdin)) return -1;
buffer[strcspn(buffer, "\n")] = 0;
for (int i = 0; buffer[i]; i++) {
if (!isdigit(buffer[i])) return -1;
}
return atoi(buffer);
}

void lireChaine(const char *invite, char *buffer, int tailleMax) {
while (1) {
printf("%s", invite);
if (!fgets(buffer, tailleMax, stdin)) continue;
if (strchr(buffer, '\n') == NULL) {
vider_buffer();
printf("❌ Trop long.\n");
continue;
}
buffer[strcspn(buffer, "\n")] = '\0';
if (strlen(buffer) == 0) {
printf("❌ Entrée vide.\n");
continue;
}
break;
}
}

void lireChaineFacultative(const char *message, char *chaine, int taille) {
int trop_long;
do {
trop_long = 0;
printf("%s", message);
if (fgets(chaine, taille, stdin)) {
size_t len = strlen(chaine);
if (len > 0 && chaine[len - 1] == '\n') {
chaine[len - 1] = '\0';
} else {
vider_buffer();
trop_long = 1;
printf("❌ Saisie trop longue.\n");
}
} else {
vider_buffer();
}
} while (trop_long);
}

void to_lowercase_str(char *dest, const char *src) {
for (int i = 0; src[i]; i++) dest[i] = tolower((unsigned char)src[i]);
dest[strlen(src)] = '\0';
}

void to_lowercase(char *str) {
for (int i = 0; str[i]; i++) str[i] = tolower((unsigned char)str[i]);
}

int valider_et_formater_nom(char *nom) {
for (int i = 0; nom[i]; i++) {
if (!isalpha(nom[i])) return 0;
}
nom[0] = toupper(nom[0]);
for (int i = 1; nom[i]; i++) nom[i] = tolower(nom[i]);
return 1;
}

int valider_espece(const char *espece) {
const char *especes_valides[] = {"chien", "chat", "hamster", "autruche"};
char espece_min[20];
to_lowercase_str(espece_min, espece);

for (int i = 0; i < 4; i++) {
if (strcmp(espece_min, especes_valides[i]) == 0) {
return 1;
}
}

printf("❌ Espèce invalide ! Choisissez parmi : chien, chat, hamster, autruche.\n");
return 0;
}

int valider_annee_naissance(const char *espece, int annee_naissance) {
int annee_courante = 2025;
int age = annee_courante - annee_naissance;
char espece_min[20];
to_lowercase_str(espece_min, espece);

if (annee_naissance > annee_courante || annee_naissance < 1900) {
printf("❌ Année de naissance invalide.\n");
return 0;
}

if (strcmp(espece_min, "chien") == 0 && age > 20) return 0;
if (strcmp(espece_min, "chat") == 0 && age > 25) return 0;
if (strcmp(espece_min, "hamster") == 0 && age > 4) return 0;
if (strcmp(espece_min, "autruche") == 0 && age > 45) return 0;

return 1;
}

int valider_poids(const char *espece, float poids) {
char espece_min[20];
to_lowercase_str(espece_min, espece);

if (poids <= 0.0f) return 0;
if (strcmp(espece_min, "chien") == 0 && (poids < 1.0f || poids > 100.0f)) return 0;
if (strcmp(espece_min, "chat") == 0 && (poids < 1.0f || poids > 12.0f)) return 0;
if (strcmp(espece_min, "hamster") == 0 && (poids < 0.02f || poids > 0.2f)) return 0;
if (strcmp(espece_min, "autruche") == 0 && (poids < 50.0f || poids > 160.0f)) return 0;

return 1;
}

int compter_mots(const char *texte) {
int mots = 0, dans_mot = 0;
for (int i = 0; texte[i]; i++) {
if (!isspace(texte[i]) && !dans_mot) {
mots++; dans_mot = 1;
} else if (isspace(texte[i])) {
dans_mot = 0;
}
}
return mots;
}

void nettoyer_chaine(char *chaine) {
for (int i = 0; chaine[i]; i++) {
if (chaine[i] == '\n' || chaine[i] == '\r') chaine[i] = '\0';
}
}

int comparer_desc(const void *a, const void *b) {
return ((StatEspece *)b)->compteur - ((StatEspece *)a)->compteur;
}

int obtenir_annee_actuelle() {
time_t t = time(NULL);
struct tm tm = *localtime(&t);
return tm.tm_year + 1900;
}
