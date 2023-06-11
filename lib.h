#ifndef lib_h_included
#define lib_h_included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>


///     STRUCTURES:      ///


// Structure représentant un passager
typedef struct passagers {
    char nom_complet[50];
    int num_passager;
    int num_passport;
    int num_place;
    char categorie[5]; // ECO:economique - BUS: Business - PRE: Premiere Classe  
}passagers;

// Structure représentant l'équipage
typedef struct crew { 
    char nom_complet[50];
    char role[20];
    int matricule;
}crew;

// Structure représentant une avion
typedef struct avion {
    int capacite;
    char model[10];
}avion;

// Structure représentant un vol
typedef struct Vol {
    int numero_vol;
    char compagnie[50];
    char depart[50];        // ville de depart
    char destination[50];   // ville d'arrivee
    char date_vol[11];
    char heure_depart[10];
    char heure_arrivee[10];
    char gate[10];
    int terminal;
    char status[20];
    passagers *Passager;
    int nbr_passagers;
    avion av;
    crew *equipage;
    int nbr_crew;
    struct Vol* precedent;
    struct Vol* suivant;
} Vol;


// Structure représentant une liste de vols
typedef struct ListeVols {
    struct Vol* tete;
    struct Vol* queue;
    int nombre_vols;
    char admin_id[10];
    char admin_pwd[10];
}ListeVols;

///     FONCTIONS:      ///

ListeVols* initialiserListe() {
    // Allouer de la mémoire pour la liste
    struct ListeVols* liste = (struct ListeVols*)malloc(sizeof(struct ListeVols));
    liste->tete = NULL;
    liste->queue = NULL;
    return liste;
}

void ajouterVol(ListeVols* L) {

    system("cls");

    Vol* nouveauVol = (Vol*)malloc(sizeof(Vol));

    // saisie des donnees
    printf("Numero de vol: ");
    scanf("%d", &(nouveauVol->numero_vol));

    printf("Compagnie: ");
    fflush(stdin);
    fgets(nouveauVol->compagnie, sizeof(nouveauVol->compagnie), stdin);

    printf("Depart: ");
    fgets(nouveauVol->depart, sizeof(nouveauVol->depart), stdin);

    printf("Destination: ");
    fgets(nouveauVol->destination, sizeof(nouveauVol->destination), stdin);

    printf("Date de vol: ");
    fgets(nouveauVol->date_vol, sizeof(nouveauVol->date_vol), stdin);
    
    fflush(stdin);
    printf("Heure de depart: ");
    fgets(nouveauVol->heure_depart, sizeof(nouveauVol->heure_depart), stdin);

    printf("Heure d'arrivee: ");
    fgets(nouveauVol->heure_arrivee, sizeof(nouveauVol->heure_arrivee), stdin);

    printf("Gate: ");
    fgets(nouveauVol->gate, sizeof(nouveauVol->gate), stdin);

    printf("Terminal: ");
    scanf("%d", &(nouveauVol->terminal));

    printf("Statut: ");
    fflush(stdin);
    fgets(nouveauVol->status, sizeof(nouveauVol->status), stdin);

    printf("\n--- INFORMATIONS SUR L'AVION :\n");

    printf("Capacite de l'avion: ");
    scanf("%d", &(nouveauVol->av.capacite));

    printf("Model de l'avion: ");
    fflush(stdin);
    fgets(nouveauVol->av.model, sizeof(nouveauVol->av.model), stdin);

    printf("\n--- INFORMATIONS SUR L'EQUIPAGE :\n");

    nouveauVol->equipage = (crew*)malloc(sizeof(crew));


    int count = 0;
    char choice;

    while (1) {
        printf("\nCrew Member %d:\n", count + 1);

        printf("Nom de l'equipage: ");
        fflush(stdin);
        fgets(nouveauVol->equipage[count].nom_complet, sizeof(nouveauVol->equipage[count].nom_complet), stdin);

        printf("Role de l'equipage: ");
        fflush(stdin);
        fgets(nouveauVol->equipage[count].role, sizeof(nouveauVol->equipage[count].role), stdin);

        printf("Matricule de l'equipage: ");
        scanf("%d", &(nouveauVol->equipage[count].matricule));

        count++;

        printf("\nVoulez-vous ajouter un autre membre d'equipage ? (O/N): ");
        fflush(stdin);
        scanf("%c", &choice);

        if (choice == 'N' || choice == 'n') {
            break;
        }
    }
    nouveauVol->nbr_crew = count;

    nouveauVol->nbr_passagers = 0;  // Initialize the number of passengers to 0


    nouveauVol->precedent = NULL;
    nouveauVol->suivant = NULL;

    // ajouter a la liste
    if (L->tete == NULL) {
        L->tete = nouveauVol;
        L->queue = nouveauVol;
    } else {
        nouveauVol->precedent = L->queue;
        L->queue->suivant = nouveauVol;
        L->queue = nouveauVol;
    }

    L->nombre_vols++;

    system("cls");
    printf("\n\n Vol Ajoutee !");
    sleep(1.5);
}


void supprimerVol(ListeVols* L, int numero_vol) {
    
    system("cls");

    if (L->tete == NULL) {
        printf("La liste de vols est vide.\n");
        return;
    }

    Vol* volCourant = L->tete;

    
    while (volCourant != NULL) {
        if (volCourant->numero_vol == numero_vol) {

            // Debut
            if (volCourant == L->tete) {
                L->tete = volCourant->suivant;
                if (L->tete != NULL) {
                    L->tete->precedent = NULL;
                }
            }
            // Fin
            if (volCourant == L->queue) {
                L->queue = volCourant->precedent;
                if (L->queue != NULL) {
                    L->queue->suivant = NULL;
                }
            }
            
            if (volCourant->precedent != NULL) {
                volCourant->precedent->suivant = volCourant->suivant;
            }
            if (volCourant->suivant != NULL) {
                volCourant->suivant->precedent = volCourant->precedent;
            }

            // Liberer la memoire
            free(volCourant);
            system("cls");
            printf("\nVol avec le numero %d supprime avec succes.\n", numero_vol);
            sleep(3);
            L->nombre_vols--;
            return;
        }

        volCourant = volCourant->suivant;
    }

    // not found
    printf("Vol avec le numero %d non trouve.\n", numero_vol);
}

void afficherVols(ListeVols* L) {
    char cont;

    if (L->tete == NULL) {
        printf("La liste des vols est vide.\n");
        return;
    }

    int choix;
    do {
        system("cls");
        printf("\n=== AFFICHER LES VOLS ===\n");
        printf("1. Afficher tous les vols\n");
        printf("2. Afficher un vol par numero\n");
        printf("3. Afficher les vols par date\n");
        printf("4. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                system("cls");
                printf("=== TOUS LES VOLS ===\n");
                Vol* volCourant = L->tete;
                while (volCourant != NULL) {
                    printf("\n--- VOL %d ---\n", volCourant->numero_vol);
                    printf("Compagnie: %s\n", volCourant->compagnie);
                    printf("Depart: %s\n", volCourant->depart);
                    printf("Destination: %s\n", volCourant->destination);
                    printf("Date de vol: %s\n", volCourant->date_vol);
                    printf("Heure de depart: %s\n", volCourant->heure_depart);
                    printf("Heure d'arrivee: %s\n", volCourant->heure_arrivee);
                    printf("Gate: %s\n", volCourant->gate);
                    printf("Terminal: %d\n", volCourant->terminal);
                    printf("Statut: %s\n", volCourant->status);

                    printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                    printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                    printf("Model de l'avion: %s\n", volCourant->av.model);

                    printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                    for (int i = 0; i < volCourant->nbr_crew; i++) {
                        printf("Membre %d:\n", i + 1);
                        printf("Nom de l'equipage: %s\n", volCourant->equipage[i].nom_complet);
                        printf("Role de l'equipage: %s\n", volCourant->equipage[i].role);
                        printf("Matricule de l'equipage: %d\n", volCourant->equipage[i].matricule);
                    }
                    printf("\n===============================================\n");
                    volCourant = volCourant->suivant;
                }
                break;
            }
            case 2: {
                system("cls");
                int numero_vol;
                printf("Numero de vol : ");
                scanf("%d", &numero_vol);

                Vol* volCourant = L->tete;
                while (volCourant != NULL) {
                    if (volCourant->numero_vol == numero_vol) {
                        printf("\n--- VOL %d ---\n", volCourant->numero_vol);
                        printf("Compagnie: %s\n", volCourant->compagnie);
                        printf("Depart: %s\n", volCourant->depart);
                        printf("Destination: %s\n", volCourant->destination);
                        printf("Date de vol: %s\n", volCourant->date_vol);
                        printf("Heure de depart: %s\n", volCourant->heure_depart);
                        printf("Heure d'arrivee: %s\n", volCourant->heure_arrivee);
                        printf("Gate: %s\n", volCourant->gate);
                        printf("Terminal: %d\n", volCourant->terminal);
                        printf("Statut: %s\n", volCourant->status);

                        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                        printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                        printf("Model de l'avion: %s\n", volCourant->av.model);

                        printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                        for (int i = 0; i < volCourant->nbr_crew; i++) {
                            printf("Membre %d:\n", i + 1);
                            printf("Nom de l'equipage: %s\n", volCourant->equipage[i].nom_complet);
                            printf("Role de l'equipage: %s\n", volCourant->equipage[i].role);
                            printf("Matricule de l'equipage: %d\n", volCourant->equipage[i].matricule);
                        }
                        printf("\n===============================================\n");
                        break;
                    }
                    volCourant = volCourant->suivant;
                }

                if (volCourant == NULL) {
                    printf("Vol avec le numero %d non trouve.\n", numero_vol);
                }
                break;
            }
            case 3: {
                system("cls");
                char date[11];
                printf("Date (DD/MM/YYYY) : ");
                scanf("%s", date);

                printf("\n=== VOLS LE %s ===\n", date);
                Vol* volCourant = L->tete;
                int found = 0;
                while (volCourant != NULL) {
                    if (strcmp(volCourant->date_vol, date) == 0) {
                        printf("\n--- VOL %d ---\n", volCourant->numero_vol);
                        printf("Compagnie: %s\n", volCourant->compagnie);
                        printf("Depart: %s\n", volCourant->depart);
                        printf("Destination: %s\n", volCourant->destination);
                        printf("Date de vol: %s\n", volCourant->date_vol);
                        printf("Heure de depart: %s\n", volCourant->heure_depart);
                        printf("Heure d'arrivee: %s\n", volCourant->heure_arrivee);
                        printf("Gate: %s\n", volCourant->gate);
                        printf("Terminal: %d\n", volCourant->terminal);
                        printf("Statut: %s\n", volCourant->status);

                        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                        printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                        printf("Model de l'avion: %s\n", volCourant->av.model);

                        printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                        for (int i = 0; i < volCourant->nbr_crew; i++) {
                            printf("Membre %d:\n", i + 1);
                            printf("Nom de l'equipage: %s\n", volCourant->equipage[i].nom_complet);
                            printf("Role de l'equipage: %s\n", volCourant->equipage[i].role);
                            printf("Matricule de l'equipage: %d\n", volCourant->equipage[i].matricule);
                        }
                        printf("\n===============================================\n");

                        found = 1;
                    }
                    volCourant = volCourant->suivant;
                }

                if (!found) {
                    printf("Aucun vol trouve pour la date %s.\n", date);
                }
                break;
            }
            case 4:
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        if (choix != 4) {
            printf("\nVoulez-vous continuer ? (O/N) : ");
            scanf(" %c", &cont);
        }
    } while (choix != 4 && (cont == 'O' || cont == 'o'));
}









#endif // lib_h_included