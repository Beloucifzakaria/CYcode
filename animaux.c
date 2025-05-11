#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "animaux.h"
#include "utils.h"
#include "affichage.h"



// Création du dossier "animaux" s'il n'existe pas
void creer_dossier_animaux() {
if (mkdir("animaux", 0777) == 0) {
printf("Le dossier 'animaux' a été créé avec succès.\n");
} else {
perror("Erreur lors de la création du dossier");
}// Cette fonction utilise une commande système (ioctl) pour obtenir la largeur actuelle du terminal.
// Elle renvoie le nombre de colonnes afin de pouvoir centrer ou adapter dynamiquement l'affichage.
}

// Génère un ID unique pour chaque nouvel animal
int generer_id(const char *fichier) {
FILE *file = fopen(fichier, "r");
int max_id = 0;
if (file) {
char ligne[256];
int id;
while (fgets(ligne, sizeof(ligne), file)) {
if (sscanf(ligne, "%d", &id) == 1 && id > max_id)
max_id = id;
}
fclose(file);
}
return max_id + 1;
}

//On crée une variable nouvel_animal de type Animal et on lui donne un ID unique automatiquement grâce à la fonction generer_id
void ajouter_animal(const char *fichier) {
    Animal nouvel_animal;
    nouvel_animal.id = generer_id(fichier);

//Affichage
    afficher_ligne_pleine();
    afficher_centre_plein("🐾 AJOUT D'UN NOUVEL ANIMAL 🐾");
    afficher_ligne_pleine();
    printf("\n");
    printf("\n");

    // Nom
    int nom_valide;
    //L’utilisateur entre un nom et on vérifie qu’il est valide (que des lettres, pas trop long). Si c’est bon on le formate (ex : “bella” devient “Bella”).
    do {
        lireChaine("➡️  Entrez le nom (max 19 lettres, sans chiffres) : ", nouvel_animal.nom, sizeof(nouvel_animal.nom));
        nom_valide = valider_et_formater_nom(nouvel_animal.nom);
        if (!nom_valide)
            printf("❌ Nom invalide. Le nom doit contenir uniquement des lettres (max 19).\n");
    } while (!nom_valide);
    printf("✅ Nom enregistré : %s\n", nouvel_animal.nom);

    // Espèce
    int espece_valide;
    //boucle Demande une espèce reconnue
    do {
        lireChaine("➡️  Entrez l'espèce (chien, chat, hamster, autruche) : ", nouvel_animal.espece, sizeof(nouvel_animal.espece));
        espece_valide = valider_espece(nouvel_animal.espece);
    } while (!espece_valide);
    printf("✅ Espèce enregistrée : %s\n", nouvel_animal.espece);

// Année de naissance 
int annee_valide;
char buffer[100];
// Demande une année cohérente (selon espèce)
do {
    printf("➡️  Entrez l'année de naissance : ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("❌ Erreur de lecture. Veuillez réessayer.\n");
        annee_valide = 0;
        continue;
    }

    // Vérifie si la saisie déborde le buffer (pas de \n)
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Vider le reste
        printf("❌ Entrée trop longue. Veuillez entrer une année valide.\n");
        annee_valide = 0;
        continue;
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // Supprimer le \n

    if (buffer[0] == '\0') {
        printf("❌ Entrée vide. Veuillez entrer une année.\n");
        annee_valide = 0;
        continue;
    }

    char *fin;
    int annee = strtol(buffer, &fin, 10);
    if (*fin != '\0') {
        printf("❌ Entrée invalide. Veuillez entrer une année valide.\n");
        annee_valide = 0;
        continue;
    }

    annee_valide = valider_annee_naissance(nouvel_animal.espece, annee);
    if (annee_valide) {
        nouvel_animal.annee_naissance = annee;
        printf("✅ Année enregistrée : %d\n", nouvel_animal.annee_naissance);
    }

} while (!annee_valide);

    
        // Poids
    int poids_valide = 0;
    char *endptr;

    do {
        printf("➡️  Entrez le poids en kg (utilisez une virgule pour les décimales) : ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("❌ Erreur de lecture. Veuillez réessayer.\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) {
            printf("❌ Entrée vide. Veuillez entrer un poids.\n");
            continue;
        }

        nouvel_animal.poids = strtof(buffer, &endptr);
        if (*endptr != '\0') {
            printf("❌ Entrée invalide. Veuillez entrer un nombre réel.\n");
            continue;
        }

        poids_valide = valider_poids(nouvel_animal.espece, nouvel_animal.poids);

    } while (!poids_valide);
    
    printf("✅ Poids enregistré : %.2f kg\n", nouvel_animal.poids);


    // Description
    
    int description_valide;
    do {
        lireChaineFacultative("➡️  Entrez une description (facultatif, max 30 mots, 200 caractères) : ", nouvel_animal.description, sizeof(nouvel_animal.description));

        if (strlen(nouvel_animal.description) == 0) {
            strcpy(nouvel_animal.description, "Aucune description");
            description_valide = 1;
        } else if (strlen(nouvel_animal.description) > 200) {
            printf("❌ Description trop longue. Elle doit faire au maximum 200 caractères.\n");
            description_valide = 0;
        } else {
            int nb_mots = compter_mots(nouvel_animal.description);
            if (nb_mots > 30) {
                printf("❌ Trop de mots : %d. La description doit contenir au maximum 30 mots.\n", nb_mots);
                description_valide = 0;
            } else {
                description_valide = 1;
            }
        }
    } while (!description_valide);
    printf("✅ Description enregistrée : %s\n", nouvel_animal.description);

    // Écriture dans le fichier
	// Sauvegarde l’animal dans le fichier et l’affiche
    FILE *file = fopen(fichier, "a");
    if (file) {
        fprintf(file, "%d %s %s %d %.2f %s\n",
                nouvel_animal.id,
                nouvel_animal.nom,
                nouvel_animal.espece,
                nouvel_animal.annee_naissance,
                nouvel_animal.poids,
                nouvel_animal.description);
        fclose(file);
printf("\n");
        afficher_animal(&nouvel_animal);
    } else {
        printf("❌ Erreur : Impossible d'ouvrir le fichier pour écrire.\n");
    }

    printf("\nAppuyez sur Entrée pour revenir au menu...");
    getchar();  
    
    
    system("clear"); 
}

// Affiche les informations d’un animal
void afficher_animal(const Animal *animal) {
char ligne[512];

snprintf(ligne, sizeof(ligne), "🐾 ID : %d", animal->id);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "📛 Nom : %s", animal->nom);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "🦴 Espèce : %s", animal->espece);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "📆 Naissance : %d", animal->annee_naissance);
afficher_centre_plein(ligne);

snprintf(ligne, sizeof(ligne), "⚖️ Poids : %.2f kg", animal->poids);
afficher_centre_plein(ligne);

if (strlen(animal->description) == 0 || strspn(animal->description, " \t\n") == strlen(animal->description)) {
snprintf(ligne, sizeof(ligne), "📝 Description : Aucune description");
} else {
snprintf(ligne, sizeof(ligne), "📝 Description : %s", animal->description);
}

afficher_centre_plein(ligne);
}


void rechercher_animaux(const char *fichier) {
    char recherche_nom_temp[1024], recherche_espece_temp[1024];
    char recherche_nom[50], recherche_espece[20];
    int type_age_recherche;

    afficher_ligne_pleine();
    afficher_centre_plein("🔍 Recherche d'animaux 🔍");
    afficher_ligne_pleine();

    printf("\n");

    // Nom
    while (1) {
        printf("Entrez le nom de l'animal à rechercher : ");
        if (!fgets(recherche_nom_temp, sizeof(recherche_nom_temp), stdin)) {
            printf("❌ ERREUR DE LECTURE, VEUILLEZ REESSAYER.\n");
            return;
        }

       
        if (recherche_nom_temp[strlen(recherche_nom_temp) - 1] != '\n') {
            vider_buffer();
            printf("❌ Nom trop long. Veuillez réessayer avec un nom plus court.\n");
            continue;
        }

       
        recherche_nom_temp[strcspn(recherche_nom_temp, "\n")] = '\0';

        
        if (strlen(recherche_nom_temp) >= sizeof(recherche_nom)) {
            printf("❌ Nom trop long. Veuillez réessayer avec un nom plus court.\n");
            continue;
        }

        
        strncpy(recherche_nom, recherche_nom_temp, sizeof(recherche_nom) - 1);
        recherche_nom[sizeof(recherche_nom) - 1] = '\0';
        break;  
    }

    // Espèce
    while (1) {
        printf("Entrez l'espèce à rechercher (chien, chat, hamster, autruche) : ");
        if (!fgets(recherche_espece_temp, sizeof(recherche_espece_temp), stdin)) {
            printf("❌ ERREUR DE LECTURE, VEUILLEZ REESSAYER.\n");
            return;
        }

        
        if (recherche_espece_temp[strlen(recherche_espece_temp) - 1] != '\n') {
            vider_buffer();
            printf("❌ Espèce trop longue. Veuillez réessayer avec une espèce plus courte.\n");
            continue;
        }

       
        recherche_espece_temp[strcspn(recherche_espece_temp, "\n")] = '\0';

       
        strncpy(recherche_espece, recherche_espece_temp, sizeof(recherche_espece));
        recherche_espece[sizeof(recherche_espece) - 1] = '\0';

        
        char espece_minuscule[20];
        to_lowercase_str(espece_minuscule, recherche_espece);

       
        if (strcmp(espece_minuscule, "chien") == 0 ||
            strcmp(espece_minuscule, "chat") == 0 ||
            strcmp(espece_minuscule, "hamster") == 0 ||
            strcmp(espece_minuscule, "autruche") == 0) {
            break; 
        }

        printf("❌ Espèce invalide. Veuillez entrer : chien, chat, hamster ou autruche.\n");
    }

    
    do {
        printf("Rechercher par âge :\n");
        printf("  1 - Jeune (< 2 ans)\n");
        printf("  2 - Senior (> 10 ans)\n");
        printf("  3 - Entre 1 et 10 ans\n");
        printf("Votre choix : ");
        if (scanf("%d", &type_age_recherche) != 1 || type_age_recherche < 1 || type_age_recherche > 3) {
            printf("❌ Choix invalide. Veuillez entrer 1, 2 ou 3.\n");
            viderBuffer();
        } else {
            break;
        }
    } while (1);
    viderBuffer();

   
    char recherche_nom_lower[50], recherche_espece_lower[20];
    to_lowercase_str(recherche_nom_lower, recherche_nom);
    to_lowercase_str(recherche_espece_lower, recherche_espece);

    FILE *file = fopen(fichier, "r");
    if (!file) {
        printf("❌ Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    char ligne[256];
    Animal animal;
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {

            char nom_lower[50], espece_lower[20];
            to_lowercase_str(nom_lower, animal.nom);
            to_lowercase_str(espece_lower, animal.espece);

            int age = 2025 - animal.annee_naissance;

            if (strstr(nom_lower, recherche_nom_lower) &&
    strstr(espece_lower, recherche_espece_lower) &&
    ((type_age_recherche == 1 && age < 2) ||
     (type_age_recherche == 2 && age > 10) ||
     (type_age_recherche == 3 && age >= 1 && age <= 10))) {
    afficher_animal(&animal);
    printf("\n");  
    trouve = 1;
}
        }
    }

    fclose(file);

    if (!trouve) {
        printf("\n❌ Aucun animal correspondant trouvé.\n");
    }

    printf("\nAppuyez sur Entrée pour revenir au menu...");
    getchar();  
    
    
    system("clear");  
}

void adopter_animal(const char *fichier) {
    int id;

    afficher_ligne_pleine();
    afficher_centre_plein("🏠 Adopter un animal 🏠");
    afficher_ligne_pleine();

    printf("\n");
    
    int saisie_valide = 0;
    do {
        printf("Entrez l'ID de l'animal à adopter : ");
        if (scanf("%d", &id) != 1) {
            printf("❌ Entrée invalide. Veuillez entrer un nombre.\n");
            vider_buffer();
        } else {
            saisie_valide = 1;
        }
    } while (!saisie_valide);
    vider_buffer(); 

    FILE *file = fopen(fichier, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file || !temp) {
        printf("❌ Erreur lors de l'ouverture des fichiers.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    char ligne[256];
    Animal animal;
    int trouve = 0;

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {
            if (animal.id != id) {
                fprintf(temp, "%s", ligne); 
            } else {
               
                printf("\n🎉 Félicitations ! Vous avez adopté l'animal suivant :\n");
                afficher_animal(&animal);
                trouve = 1;
            }
        }
    }

    fclose(file);
    fclose(temp);

    if (trouve) {
        remove(fichier);
        rename("temp.txt", fichier);
        printf("✅ L'animal avec l'ID %d a été adopté avec succès !\n", id);
    } else {
        remove("temp.txt");
        printf("❌ Aucun animal avec l'ID %d trouvé.\n", id);
    }

    printf("\nAppuyez sur Entrée pour revenir au menu...");
    getchar();  
    
    
    system("clear");  
}

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

    
    char *emoji[] = {
        "🐕",  
        "😺",  
        "🐹",  
        "🦤"   
    };

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

    afficher_ligne_pleine();
    afficher_centre_plein("📋 INVENTAIRE DU REFUGE 📋");
    afficher_ligne_pleine();

    printf("\nNombre total d'animaux : %d\n", total);
    for (int i = 0; i < nb_especes; i++) {
        char nom_affiche[20];
        strcpy(nom_affiche, stats[i].espece);
        nom_affiche[0] = toupper(nom_affiche[0]);

       
        char *espèce = stats[i].espece;
        char *animal_emoji = NULL;
        if (strcmp(espèce, "chien") == 0) {
            animal_emoji = emoji[0];
        } else if (strcmp(espèce, "chat") == 0) {
            animal_emoji = emoji[1];
        } else if (strcmp(espèce, "hamster") == 0) {
            animal_emoji = emoji[2];
        } else if (strcmp(espèce, "autruche") == 0) {
            animal_emoji = emoji[3];
        }

       
        printf("• %-10s %s : %2d\n", animal_emoji, nom_affiche, stats[i].compteur);
    }

    printf("\nAppuyez sur Entrée pour revenir au menu...");
    getchar(); 
    
    
    system("clear"); 
}

void nourriture_quotidienne(const char *fichier) {
    FILE *file = fopen(fichier, "r");
    if (!file) {
        printf("❌ Erreur lors de l'ouverture du fichier pour la lecture.\n");
        return;
    }

    float nourriture_totale = 0;
    float nourriture_chien = 0;
    float nourriture_chat = 0;
    float nourriture_hamster = 0;
    float nourriture_autruche = 0;

    Animal animal;
    char ligne[256];

    afficher_ligne_pleine();
    afficher_centre_plein("🍽️ NOURRITURE QUOTIDIENNE DU REFUGE 🍽️");
    afficher_ligne_pleine();

    while (fgets(ligne, sizeof(ligne), file)) {
        if (sscanf(ligne, "%d %s %s %d %f %[^\n]",
                   &animal.id, animal.nom, animal.espece,
                   &animal.annee_naissance, &animal.poids, animal.description) >= 5) {

            if (strcasecmp(animal.espece, "hamster") == 0) {
                nourriture_hamster += 0.02;
                nourriture_totale += 0.02;
            } else if (strcasecmp(animal.espece, "autruche") == 0) {
                nourriture_autruche += 2.5;
                nourriture_totale += 2.5;
            } else if (strcasecmp(animal.espece, "chien") == 0) {
                int age = 2025 - animal.annee_naissance;
                float ration = (age < 2) ? 0.5 : animal.poids * 0.10;
                nourriture_chien += ration;
                nourriture_totale += ration;
            } else if (strcasecmp(animal.espece, "chat") == 0) {
                int age = 2025 - animal.annee_naissance;
                float ration = (age < 2) ? 0.5 : animal.poids * 0.10;
                nourriture_chat += ration;
                nourriture_totale += ration;
            }
        }
    }

    fclose(file);

    // Affichage des résultats
    printf("\n📊 Détail par espèce :\n");
    if (nourriture_chien > 0)
        printf("   🐶 Chiens     : %.2f kg\n", nourriture_chien);
    if (nourriture_chat > 0)
        printf("   🐱 Chats      : %.2f kg\n", nourriture_chat);
    if (nourriture_hamster > 0)
        printf("   🐹 Hamsters   : %.2f kg\n", nourriture_hamster);
    if (nourriture_autruche > 0)
        printf("   🦤 Autruches  : %.2f kg\n", nourriture_autruche);

    printf("\n➡️  Total de nourriture quotidienne nécessaire : %.2f kg\n", nourriture_totale);

   
    printf("\nℹ️  Ce total est une estimation basée sur les poids et âges des animaux du refuge.\n");
    printf("   Il peut varier selon l'appétit et les besoins individuels des animaux.\n");

    printf("\nAppuyez sur Entrée pour revenir au menu...");
    getchar();
    system("clear");  
}
