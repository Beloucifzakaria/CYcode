#indef UTILITAIRE_H
#define UTILITAIRE_H



int largeur_console();
int get_terminal_width();
void print_centered(const char *text, int width);
void print_horizontal_line(int width, char c);
void to_lowercase_str(char *dest, const char *src);
int valider_et_formater_nom(char *nom);
void nettoyer_chaine(char *chaine);
int compter_mots(const char *texte);
int comparer_desc(const void *a, const void *b);
void to_lowercase(char *str);
int lireChoixUtilisateur();
void lireChaine(const char *invite, char *buffer, int tailleMax);
void vider_buffer();


#endif
