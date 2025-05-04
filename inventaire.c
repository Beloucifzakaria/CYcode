void inventaire(const char *fichier) {
    FILE *file = fopen(fichier, "r");
    if (!file) {
        printf("❌ Erreur lors de l'ouverture du fichier pour la lecture.\n");
        return;
    }

    Animal animal;
    int total = 0;
    StatEspece stats[] = {
        {"chien", 0},
        {"chat", 0},
        {"hamster", 0},
        {"autruche", 0}
    };
    int nb_especes = sizeof(stats) / sizeof(stats[0]);

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), file)) {
        ligne[strcspn(ligne, "\n")] = 0;

        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {

            total++;
            nettoyer_chaine(animal.espece);
            to_lowercase(animal.espece);

            for (int i = 0; i < nb_especes; i++) {
                if (strcmp(animal.espece, stats[i].espece) == 0) {
                    stats[i].compteur++;
                    break;
                }
            }
        }
    }

    fclose(file);

    qsort(stats, nb_especes, sizeof(StatEspece), comparer_desc);

    printf("\n========= 📋 INVENTAIRE DU REFUGE 📋 =========\n");
    printf("Nombre total d'animaux : %d\n", total);
    printf("---------------------------------------------\n");
    for (int i = 0; i < nb_especes; i++) {
        char nom_affiche[20];
        strcpy(nom_affiche, stats[i].espece);
        nom_affiche[0] = toupper(nom_affiche[0]);
        printf("• %-10s : %2d\n", nom_affiche, stats[i].compteur);
    }
    printf("=============================================\n");
}
