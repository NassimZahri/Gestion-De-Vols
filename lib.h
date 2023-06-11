#ifndef lib_h_included
#define lib_h_included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    char date_vol[10];
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
}


void supprimerVol(ListeVols* L, int numero_vol) {
    // Check if the list is empty
    if (L->tete == NULL) {
        printf("La liste de vols est vide.\n");
        return;
    }

    Vol* volCourant = L->tete;

    // Find the flight with the specified flight number
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

            printf("Vol avec le numero %d supprime avec succes.\n", numero_vol);
            L->nombre_vols--;
            return;
        }

        volCourant = volCourant->suivant;
    }

    // not found
    printf("Vol avec le numero %d non trouve.\n", numero_vol);
}

void afficherVols(ListeVols* L) {
    if (L->tete == NULL) {
        printf("La liste des vols est vide.\n");
        return;
    }

    Vol* volCourant = L->tete;

    while (volCourant != NULL) {
        printf("\n--- VOL %d ---\n", volCourant->numero_vol);
        printf("Compagnie: %s", volCourant->compagnie);
        printf("Depart: %s", volCourant->depart);
        printf("Destination: %s", volCourant->destination);
        printf("Date de vol: %s", volCourant->date_vol);
        printf("Heure de depart: %s", volCourant->heure_depart);
        printf("Heure d'arrivee: %s", volCourant->heure_arrivee);
        printf("Gate: %s", volCourant->gate);
        printf("Terminal: %d\n", volCourant->terminal);
        printf("Statut: %s", volCourant->status);

        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
        printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
        printf("Model de l'avion: %s", volCourant->av.model);

        printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---");
        for (int i = 0; i < volCourant->nbr_crew; i++) {
            printf("\nMembre %d:\n", i + 1);
            printf("Nom de l'equipage: %s", volCourant->equipage[i].nom_complet);
            printf("Role de l'equipage: %s", volCourant->equipage[i].role);
            printf("Matricule de l'equipage: %d\n", volCourant->equipage[i].matricule);
        }

        volCourant = volCourant->suivant;
    }
}








#endif // lib_h_included