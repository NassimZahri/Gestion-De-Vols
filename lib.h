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

typedef struct prix{
    float eco; 
    float bus;
    float pre;
}prix;

// Structure représentant un vol
typedef struct Vol {
    int numero_vol;
    char compagnie[20];
    char depart[20];        // ville de depart
    char destination[20];   // ville d'arrivee
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
    prix prix_vol;
    struct Vol* precedent;
    struct Vol* suivant;
} Vol;


// Structure représentant une liste de vols
typedef struct ListeVols {
    struct Vol* tete;
    struct Vol* queue;
    int nombre_vols;
    char admin_id[10];
    char admin_pwd[20];
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
    nouveauVol->compagnie[strcspn(nouveauVol->compagnie, "\n")] = '\0';

    printf("Depart: ");
    fgets(nouveauVol->depart, sizeof(nouveauVol->depart), stdin);
    nouveauVol->depart[strcspn(nouveauVol->depart, "\n")] = '\0';

    printf("Destination: ");
    fgets(nouveauVol->destination, sizeof(nouveauVol->destination), stdin);
    nouveauVol->destination[strcspn(nouveauVol->destination, "\n")] = '\0';

    printf("Date de vol: ");
    fgets(nouveauVol->date_vol, sizeof(nouveauVol->date_vol), stdin);
    nouveauVol->date_vol[strcspn(nouveauVol->date_vol, "\n")] = '\0';

    fflush(stdin);
    printf("Heure de depart: ");
    fgets(nouveauVol->heure_depart, sizeof(nouveauVol->heure_depart), stdin);
    nouveauVol->heure_depart[strcspn(nouveauVol->heure_depart, "\n")] = '\0';

    printf("Heure d'arrivee: ");
    fgets(nouveauVol->heure_arrivee, sizeof(nouveauVol->heure_arrivee), stdin);
    nouveauVol->heure_arrivee[strcspn(nouveauVol->heure_arrivee, "\n")] = '\0';

    printf("Gate: ");
    fgets(nouveauVol->gate, sizeof(nouveauVol->gate), stdin);
    nouveauVol->gate[strcspn(nouveauVol->gate, "\n")] = '\0';

    printf("Terminal: ");
    scanf("%d", &(nouveauVol->terminal));

    printf("Statut: ");
    fflush(stdin);
    fgets(nouveauVol->status, sizeof(nouveauVol->status), stdin);

    printf("\n--- TARIFS :\n");
    printf("Economique: ");
    scanf("%f", &(nouveauVol->prix_vol.eco));

    printf("Business: ");
    scanf("%f", &(nouveauVol->prix_vol.bus));

    printf("Premiere Class: ");
    scanf("%f", &(nouveauVol->prix_vol.pre));

    printf("\n--- INFORMATIONS SUR L'AVION :\n");

    printf("Capacite de l'avion: ");
    scanf("%d", &(nouveauVol->av.capacite));

    printf("Model de l'avion: ");
    fflush(stdin);
    fgets(nouveauVol->av.model, sizeof(nouveauVol->av.model), stdin);
    fflush(stdin);

    printf("\n--- INFORMATIONS SUR L'EQUIPAGE :\n");

    int nbr_eq=0;
    do
    {
        printf("nombre max. d'equipage : ");
        scanf("%d",&nbr_eq);
        if (nbr_eq <= 0){printf("Nombre invalide!\n");}
    } while (nbr_eq <= 0);
    
    nouveauVol->equipage = (crew*)malloc(nbr_eq * sizeof(crew));


    int count = 0;
    char choice;

    while (count <= nbr_eq) {
        printf("\nCrew Member %d:\n", count + 1);

        printf("Nom: ");
        fflush(stdin);
        fgets(nouveauVol->equipage[count].nom_complet, sizeof(nouveauVol->equipage[count].nom_complet), stdin);

        printf("Role: ");
        fflush(stdin);
        fgets(nouveauVol->equipage[count].role, sizeof(nouveauVol->equipage[count].role), stdin);

        printf("Matricule: ");
        scanf("%d", &(nouveauVol->equipage[count].matricule));

        count++;

        if (count >= nbr_eq ) {
            break;
        }

        printf("\nVoulez-vous ajouter un autre membre d'equipage ? (O/N): ");
        fflush(stdin);
        scanf("%c", &choice);

        if (choice == 'N' || choice == 'n') {
            break;
        }
    }
    nouveauVol->nbr_crew = count;

    nouveauVol->nbr_passagers = 0;  // initialiser le nombre de passagers
    nouveauVol->Passager = NULL;


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
            sleep(1.5);
            L->nombre_vols--;
            return;
        }

        volCourant = volCourant->suivant;
    }

    // not found
    system("cls");
    printf("Vol avec le numero %d non trouve.\n", numero_vol);
    sleep(1.5);
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
        printf("\n0. Retour\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                system("cls");
                printf("=== TOUS LES VOLS ===\n");
                Vol* volCourant = L->tete;
                while (volCourant != NULL) {   
                    printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
                    printf("%-8d", volCourant->numero_vol);
                    printf("%-15s", volCourant->compagnie);
                    printf("%-15s", volCourant->depart);
                    printf("%-15s", volCourant->destination);
                    printf("%-15s", volCourant->date_vol);
                    printf("%-16s", volCourant->heure_depart);
                    printf("%s\n", volCourant->heure_arrivee);
                    printf("Gate: %s\t", volCourant->gate);
                    printf("Terminal: %d\t", volCourant->terminal);
                    printf("Statut: %s\n", volCourant->status);
                   
                    printf("--- TARIFS :\n");
                    printf("Economique: %.2f\t",volCourant->prix_vol.eco);
                    printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
                    printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);
                    

                    printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                    printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                    printf("Model de l'avion: %s\n", volCourant->av.model);
                    printf("Nombre de passager: %d\n",volCourant->nbr_passagers);

                    printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                    for (int i = 0; i < volCourant->nbr_crew; i++) {
                        printf("Membre %d:\n", i + 1);
                        printf("Nom: %s", volCourant->equipage[i].nom_complet);
                        printf("Role: %s", volCourant->equipage[i].role);
                        printf("Matricule: %d\n\n", volCourant->equipage[i].matricule);
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
                        printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
                        printf("%-8d", volCourant->numero_vol);
                        printf("%-15s", volCourant->compagnie);
                        printf("%-15s", volCourant->depart);
                        printf("%-15s", volCourant->destination);
                        printf("%-15s", volCourant->date_vol);
                        printf("%-16s", volCourant->heure_depart);
                        printf("%s\n", volCourant->heure_arrivee);
                        printf("Gate: %s\t", volCourant->gate);
                        printf("Terminal: %d\t", volCourant->terminal);
                        printf("Statut: %s\n", volCourant->status);
                    
                        printf("--- TARIFS :\n");
                        printf("Economique: %.2f\t",volCourant->prix_vol.eco);
                        printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
                        printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);
                        

                        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                        printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                        printf("Model de l'avion: %s\n", volCourant->av.model);
                        printf("Nombre de passager: %d\n",volCourant->nbr_passagers);

                        printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                        for (int i = 0; i < volCourant->nbr_crew; i++) {
                            printf("Membre %d:\n", i + 1);
                            printf("Nom: %s", volCourant->equipage[i].nom_complet);
                            printf("Role: %s", volCourant->equipage[i].role);
                            printf("Matricule: %d\n\n", volCourant->equipage[i].matricule);
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
                        printf("%-8d", volCourant->numero_vol);
                        printf("%-15s", volCourant->compagnie);
                        printf("%-15s", volCourant->depart);
                        printf("%-15s", volCourant->destination);
                        printf("%-15s", volCourant->date_vol);
                        printf("%-16s", volCourant->heure_depart);
                        printf("%s\n", volCourant->heure_arrivee);
                        printf("Gate: %s\t", volCourant->gate);
                        printf("Terminal: %d\t", volCourant->terminal);
                        printf("Statut: %s\n", volCourant->status);
                    
                        printf("--- TARIFS :\n");
                        printf("Economique: %.2f\t",volCourant->prix_vol.eco);
                        printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
                        printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);
                        

                        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                        printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                        printf("Model de l'avion: %s\n", volCourant->av.model);
                        printf("Nombre de passager: %d\n",volCourant->nbr_passagers);

                        printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                        for (int i = 0; i < volCourant->nbr_crew; i++) {
                            printf("Membre %d:\n", i + 1);
                            printf("Nom: %s", volCourant->equipage[i].nom_complet);
                            printf("Role: %s", volCourant->equipage[i].role);
                            printf("Matricule: %d\n\n", volCourant->equipage[i].matricule);
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
            case 0:
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                printf("\n**appuyer sur n'importe quelle touche.");
                while (!kbhit()) {}
                getch();
                fflush(stdin);
                break;
        }

        if (choix != 0) {
            printf("\n**appuyer sur n'importe quelle touche pour revenir.");
            while (!kbhit()) {}
            getch();
            fflush(stdin);
        }
    } while (choix != 0 /*&& (cont == 'O' || cont == 'o')*/);
}

void modifierVol(ListeVols* L, int numero_vol) {
    system("cls");

    if (L->tete == NULL) {
        printf("La liste des vols est vide.\n");
        return;
    }

    Vol* volCourant = L->tete;
    
    while (volCourant != NULL) {
        if (volCourant->numero_vol == numero_vol) {
            // avant modification
                printf("%-8d", volCourant->numero_vol);
                printf("%-15s", volCourant->compagnie);
                printf("%-15s", volCourant->depart);
                printf("%-15s", volCourant->destination);
                printf("%-15s", volCourant->date_vol);
                printf("%-16s", volCourant->heure_depart);
                printf("%s\n", volCourant->heure_arrivee);
                printf("Gate: %s\t", volCourant->gate);
                printf("Terminal: %d\t", volCourant->terminal);
                printf("Statut: %s\n", volCourant->status);
            
                printf("--- TARIFS :\n");
                printf("Economique: %.2f\t",volCourant->prix_vol.eco);
                printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
                printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);
                

                printf("\n--- INFORMATIONS SUR L'AVION ---\n");
                printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
                printf("Model de l'avion: %s\n", volCourant->av.model);
                printf("Nombre de passager: %d\n",volCourant->nbr_passagers);

                printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
                for (int i = 0; i < volCourant->nbr_crew; i++) {
                    printf("Membre %d:\n", i + 1);
                    printf("Nom: %s", volCourant->equipage[i].nom_complet);
                    printf("Role: %s", volCourant->equipage[i].role);
                    printf("Matricule: %d\n\n", volCourant->equipage[i].matricule);
                }
                printf("\n===============================================\n");

            // saisie des donnees
            printf("Numero de vol: ");
            scanf("%d", &(volCourant->numero_vol));

            printf("Compagnie: ");
            fflush(stdin);
            fgets(volCourant->compagnie, sizeof(volCourant->compagnie), stdin);
            volCourant->compagnie[strcspn(volCourant->compagnie, "\n")] = '\0';

            printf("Depart: ");
            fgets(volCourant->depart, sizeof(volCourant->depart), stdin);
            volCourant->depart[strcspn(volCourant->depart, "\n")] = '\0';

            printf("Destination: ");
            fgets(volCourant->destination, sizeof(volCourant->destination), stdin);
            volCourant->destination[strcspn(volCourant->destination, "\n")] = '\0';

            printf("Date de vol: ");
            fgets(volCourant->date_vol, sizeof(volCourant->date_vol), stdin);
            volCourant->date_vol[strcspn(volCourant->date_vol, "\n")] = '\0';

            fflush(stdin);
            printf("Heure de depart: ");
            fgets(volCourant->heure_depart, sizeof(volCourant->heure_depart), stdin);
            volCourant->heure_depart[strcspn(volCourant->heure_depart, "\n")] = '\0';

            printf("Heure d'arrivee: ");
            fgets(volCourant->heure_arrivee, sizeof(volCourant->heure_arrivee), stdin);
            volCourant->heure_arrivee[strcspn(volCourant->heure_arrivee, "\n")] = '\0';

            printf("Gate: ");
            fgets(volCourant->gate, sizeof(volCourant->gate), stdin);
            volCourant->gate[strcspn(volCourant->gate, "\n")] = '\0';

            printf("Terminal: ");
            scanf("%d", &(volCourant->terminal));

            printf("Statut: ");
            fflush(stdin);
            fgets(volCourant->status, sizeof(volCourant->status), stdin);
            volCourant->status[strcspn(volCourant->status, "\n")] = '\0';

            printf("\n--- TARIFS :\n");
            printf("Economique: ");
            scanf("%f", &(volCourant->prix_vol.eco));

            printf("Business: ");
            scanf("%f", &(volCourant->prix_vol.bus));

            printf("Premiere Class: ");
            scanf("%f", &(volCourant->prix_vol.pre));

            printf("\n--- INFORMATIONS SUR L'AVION :\n");

            printf("Capacite de l'avion: ");
            scanf("%d", &(volCourant->av.capacite));

            printf("Model de l'avion: ");
            fflush(stdin);
            fgets(volCourant->av.model, sizeof(volCourant->av.model), stdin);
            volCourant->av.model[strcspn(volCourant->av.model, "\n")] = '\0';

            printf("\n--- INFORMATIONS SUR L'EQUIPAGE :\n");

            int nbr_eq = 0;
            do {
                printf("nombre max. d'equipage : ");
                scanf("%d", &nbr_eq);
                if (nbr_eq <= 0) {
                    printf("Nombre invalide!\n");
                }
            } while (nbr_eq <= 0);

            volCourant->equipage = (crew*)malloc(nbr_eq * sizeof(crew));

            int count = 0;
            char choice;

            while (count <= nbr_eq) {
                printf("\nCrew Member %d:\n", count + 1);

                printf("Nom: ");
                fflush(stdin);
                fgets(volCourant->equipage[count].nom_complet, sizeof(volCourant->equipage[count].nom_complet), stdin);
                volCourant->equipage[count].nom_complet[strcspn(volCourant->equipage[count].nom_complet, "\n")] = '\0';

                printf("Role: ");
                fflush(stdin);
                fgets(volCourant->equipage[count].role, sizeof(volCourant->equipage[count].role), stdin);
                volCourant->equipage[count].role[strcspn(volCourant->equipage[count].role, "\n")] = '\0';

                printf("Matricule: ");
                scanf("%d", &(volCourant->equipage[count].matricule));

                count++;

                if (count >= nbr_eq) {
                    break;
                }

                printf("\nVoulez-vous ajouter un autre membre d'equipage ? (O/N): ");
                fflush(stdin);
                scanf("%c", &choice);

                if (choice == 'N' || choice == 'n') {
                    break;
                }
            }

    volCourant->nbr_crew = count;

            system("cls");
            printf("\n--- DETAILS DU VOL APRES MODIFICATION ---\n");
            printf("%-8d", volCourant->numero_vol);
            printf("%-15s", volCourant->compagnie);
            printf("%-15s", volCourant->depart);
            printf("%-15s", volCourant->destination);
            printf("%-15s", volCourant->date_vol);
            printf("%-16s", volCourant->heure_depart);
            printf("%s\n", volCourant->heure_arrivee);
            printf("Gate: %s\t", volCourant->gate);
            printf("Terminal: %d\t", volCourant->terminal);
            printf("Statut: %s\n", volCourant->status);
        
            printf("--- TARIFS :\n");
            printf("Economique: %.2f\t",volCourant->prix_vol.eco);
            printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
            printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);
            

            printf("\n--- INFORMATIONS SUR L'AVION ---\n");
            printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
            printf("Model de l'avion: %s\n", volCourant->av.model);
            printf("Nombre de passager: %d\n",volCourant->nbr_passagers);

            printf("\n--- INFORMATIONS SUR L'EQUIPAGE ---\n");
            for (int i = 0; i < volCourant->nbr_crew; i++) {
                printf("Membre %d:\n", i + 1);
                printf("Nom: %s", volCourant->equipage[i].nom_complet);
                printf("Role: %s", volCourant->equipage[i].role);
                printf("Matricule: %d\n\n", volCourant->equipage[i].matricule);
            }
            printf("\n===============================================\n");



            printf("\nLe vol a ete modifie avec succes.\n");
            printf("\n**appuyer sur n'importe quelle touche pour revenir au menu.");
            while (!kbhit()) {}
            getch();
            fflush(stdin);
            return;
        }
        volCourant = volCourant->suivant;
    }

    printf("Le vol avec le numero %d n'a pas ete trouve.\n", numero_vol);
}

Vol* trouverVol(ListeVols* L, int numero_vol);

void modifierStatusVol(ListeVols *L) {
    int numVol;
    system("cls");
    printf("\nEntrez le numero de vol : ");
    scanf("%d", &numVol);

    Vol* vol = trouverVol(L, numVol);

    if (vol == NULL) {
        system("cls");
        printf("Vol introuvable!\n");
        sleep(1.5);
        return;
    }

    printf("\nVeuillez choisir le nouveau statut du vol : \n");
    printf("1. A l'heure\n");
    printf("2. En Retard\n");
    printf("3. Annule\n");

    int choix;
    printf("Votre choix : ");
    scanf("%d", &choix);

    int changed = 0;
    do{
        switch (choix) {
            case 1:
                strcpy(vol->status, "A l'heure");
                changed = 1;
                break;
            case 2:
                strcpy(vol->status, "En Retard");
                changed = 1;
                break;
            case 3:
                strcpy(vol->status, "Annule");
                changed = 1;
                break;
            default:
                system("cls");
                printf("Choix invalide!\n");
                return;
        }
    }while(changed = 0);
    printf("\nLe statut du vol a ete modifie avec succes.\n");
    sleep(1.5);
}



void afficherVolsClient(ListeVols* L) {
    if (L->tete == NULL) {
        printf("La liste des vols est vide.\n");
        return;
    }
    Vol* volCourant = L->tete;
    
    system("cls");
    while (volCourant != NULL) {
        printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
        printf("%-8d", volCourant->numero_vol);
        printf("%-15s", volCourant->compagnie);
        printf("%-10s", volCourant->depart);
        printf("%-15s", volCourant->destination);
        printf("%-15s", volCourant->date_vol);
        printf("%-16s", volCourant->heure_depart);
        printf("%s\n", volCourant->heure_arrivee);

        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
        printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
        printf("Model de l'avion: %s", volCourant->av.model);
        printf("\nNombre de passager: %d",volCourant->nbr_passagers);

        printf("\n--- TARIFS :\n");
        printf("Economique: %.2f\t",volCourant->prix_vol.eco);
        printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
        printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);
        
        printf("\n===============================================\n");
        
        volCourant = volCourant->suivant;
    }
    
    printf("\n**appuyer sur n'importe quelle touche pour revenir.");
    while (!kbhit()) {}
    getch();
    fflush(stdin);
}

int afficherVolsDestination(ListeVols* L, char destination[]) {
    int found = 0;
    if (L->tete == NULL) {
        printf("La liste des vols est vide.\n");
        return 0;
    }
    Vol* volCourant = L->tete;

    system("cls");
    while (volCourant != NULL) {
        if (strcmp(volCourant->destination, destination) == 0) {
            printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
            printf("%-8d", volCourant->numero_vol);
            printf("%-15s", volCourant->compagnie);
            printf("%-10s", volCourant->depart);
            printf("%-15s", volCourant->destination);
            printf("%-15s", volCourant->date_vol);
            printf("%-16s", volCourant->heure_depart);
            printf("%s\n", volCourant->heure_arrivee);

            printf("\n--- INFORMATIONS SUR L'AVION ---\n");
            printf("Capacite de l'avion: %d\n", volCourant->av.capacite);
            printf("Model de l'avion: %s", volCourant->av.model);
            printf("Nombre de passager: %d\n",volCourant->nbr_passagers);

            printf("\n--- TARIFS :\n");
            printf("Economique: %.2f\t",volCourant->prix_vol.eco);
            printf("Business: %.2f\t\t",volCourant->prix_vol.bus);
            printf("Premiere Class: %.2f\n",volCourant->prix_vol.pre);

            printf("\n===============================================\n");

            found++;
        }

        volCourant = volCourant->suivant;
    }

    if (found==0) {
        return 0;
    }else
        printf("\nNombre de vols disponibles: %d",found);
        return 1;
}

// fonction qui trouve un vol par son numero
Vol* trouverVol(ListeVols* L, int numero_vol) {
    Vol* ptr;
    for (ptr = L->tete; ptr != NULL; ptr = ptr->suivant) {
        if (ptr->numero_vol == numero_vol) {
            return ptr;
        }
    }
    return NULL; // not found
}


/*
void reserverVol(ListeVols* L, char *destination){
    int found = afficherVolsDestination(L,destination);
    int numVolRes;

    if (found == 0)
    {
        printf("\nAucune vol trouve pour cette destination. (%s)\n",destination);
        printf("\n**appuyer sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    printf("\nSaisir le numero de vol que vous voulez reserver:  ");
    scanf("%d", &numVolRes);

    Vol *volRes = trouverVol(L,numVolRes);
    

    if (volRes == NULL) {
        system("cls");
        printf("\nVol introuvable!\n");
        printf("\n**appuyer sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    if (volRes->nbr_passagers >= volRes->av.capacite) {
        system("cls");
        printf("Desole, pas de places disponible dans cette vol.\n");
        printf("\n**appuyer sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    // Ajouter a la liste
    if (volRes->Passager == NULL) {
        volRes->Passager = malloc(sizeof(passagers) * volRes->av.capacite);
        volRes->Passager->num_passager = 0;
        volRes->Passager->num_place = 0;
    }

    system("cls");

    //TEST
    printf("\nNum vol: %d",volRes->numero_vol);
    printf("\ndestination: %s",volRes->destination);

    //TEST

    //fflush(stdin);
    printf("\nNom complet: ");
    //scanf("%s",&volRes->Passager[volRes->nbr_passagers].nom_complet);
    fgets(volRes->Passager[volRes->nbr_passagers].nom_complet,49,stdin);
    volRes->Passager[volRes->nbr_passagers].nom_complet[strcspn(volRes->Passager[volRes->nbr_passagers].nom_complet, "\n")] = '\0';

    printf("\nNumero de passeport: ");
    scanf("%d",&volRes->Passager->num_passport);

    printf("\nVeuillez choisir une categorie: ");
    printf("\n--- TARIFS :\n");
        printf("Economique: %.2f\t",volRes->prix_vol.eco);
        printf("Business: %.2f\t\t",volRes->prix_vol.bus);
        printf("Premiere Class: %.2f\n",volRes->prix_vol.pre);
    printf("ECO: economique, BUS: business, PRE: premier classe \nVotre choix: ");
    scanf("%s",&volRes->Passager->categorie);

    volRes->nbr_passagers++;

    system("cls");
    printf("Reservation reussie.\n");
    printf("\nInformations sur la reservation:\n");
    printf("\n===============================================\n");
    printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
            printf("%-8d", volRes->numero_vol);
            printf("%-15s", volRes->compagnie);
            printf("%-10s", volRes->depart);
            printf("%-15s", volRes->destination);
            printf("%-15s", volRes->date_vol);
            printf("%-16s", volRes->heure_depart);
            printf("%s\n", volRes->heure_arrivee);

            printf("\n--- INFORMATIONS SUR L'AVION ---\n");
            printf("Capacite de l'avion: %d\n", volRes->av.capacite);
            printf("Model de l'avion: %s", volRes->av.model);

            printf("\n\nNumero Passager: %d",volRes->Passager[volRes->nbr_passagers - 1].num_passager);
            printf("\nNom Complet: %s",volRes->Passager[volRes->nbr_passagers - 1].nom_complet);
            printf("\nNumero Passeport: %d",volRes->Passager[volRes->nbr_passagers - 1].num_passport);
            printf("\nNumero de Place: %d",volRes->Passager[volRes->nbr_passagers - 1].num_place);
            printf("\nCategorie: %-3s",volRes->Passager[volRes->nbr_passagers - 1].categorie); 

            printf("\n===============================================\n");

    printf("\n**appuyer sur n'importe quelle touche pour revenir.");
    while (!kbhit()) {}
    getch();
    fflush(stdin);

}
*/

void reserverVol(ListeVols* L, char *destination) {
    int found = afficherVolsDestination(L, destination);
    int numVolRes;

    if (found == 0) {
        printf("\nAucun vol trouve pour cette destination. (%s)\n", destination);
        printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    printf("\nSaisir le numero de vol que vous voulez reserver :  ");
    scanf("%d", &numVolRes);

    Vol* volRes = trouverVol(L, numVolRes);

    if (volRes == NULL) {
        system("cls");
        printf("\nVol introuvable !\n");
        printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    if (volRes->nbr_passagers >= volRes->av.capacite) {
        system("cls");
        printf("Desole, pas de places disponibles dans ce vol.\n");
        printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    // Ajouter à la liste
    if (volRes->Passager == NULL) {
        volRes->Passager = (passagers*) malloc(sizeof(passagers) * volRes->av.capacite);
        volRes->nbr_passagers = 0;
    }

    system("cls");

    fflush(stdin);

    printf("\nNom complet : ");
    fgets(volRes->Passager[volRes->nbr_passagers].nom_complet, 49, stdin);
    volRes->Passager[volRes->nbr_passagers].nom_complet[strcspn(volRes->Passager[volRes->nbr_passagers].nom_complet, "\n")] = '\0';

    printf("\nNumero de passeport : ");
    scanf("%d", &(volRes->Passager[volRes->nbr_passagers].num_passport));

    printf("\nVeuillez choisir une categorie : ");
    printf("\n--- TARIFS :\n");
    printf("Economique: %.2f\t", volRes->prix_vol.eco);
    printf("Business: %.2f\t\t", volRes->prix_vol.bus);
    printf("Premiere Class: %.2f\n", volRes->prix_vol.pre);
    printf("ECO: economique, BUS: business, PRE: premiere classe\nVotre choix : ");
    scanf("%3s", volRes->Passager[volRes->nbr_passagers].categorie);
    volRes->Passager[volRes->nbr_passagers].num_place = volRes->nbr_passagers + 1;
    volRes->Passager[volRes->nbr_passagers].num_passager = volRes->nbr_passagers + 1;
    

    system("cls");
    printf("Reservation reussie.\n");
    printf("\nInformations sur la reservation :\n");
    printf("\n===============================================\n");
    printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
    printf("%-8d", volRes->numero_vol);
    printf("%-15s", volRes->compagnie);
    printf("%-10s", volRes->depart);
    printf("%-15s", volRes->destination);
    printf("%-15s", volRes->date_vol);
    printf("%-16s", volRes->heure_depart);
    printf("%s\n", volRes->heure_arrivee);

    printf("\n--- INFORMATIONS SUR L'AVION ---\n");
    printf("Capacite de l'avion : %d\n", volRes->av.capacite);
    printf("Modele de l'avion : %s\n", volRes->av.model);
    printf("Nombre de passager: %d\n",volRes->nbr_passagers);

    int latestPassengerIndex = volRes->nbr_passagers;

    printf("\n\nNumero Passager : %d", volRes->Passager[latestPassengerIndex].num_passager);
    printf("\nNom Complet : %s", volRes->Passager[latestPassengerIndex].nom_complet);
    printf("\nNumero Passeport : %d", volRes->Passager[latestPassengerIndex].num_passport);
    printf("\nNumero de Place : P%d", volRes->Passager[latestPassengerIndex].num_place);
    printf("\nCategorie : %-3s", volRes->Passager[latestPassengerIndex].categorie);
    printf("\n===============================================\n");

    volRes->nbr_passagers++;

    printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
    while (!kbhit()) {}
    getch();
    fflush(stdin);
}



void afficherPassagers(ListeVols *L, int num){
    Vol *volCourant = L->tete;
    while (volCourant != NULL) {
        if (volCourant->numero_vol == num && volCourant->nbr_passagers>0) {
            break;
        }
        volCourant = volCourant->suivant;
    }

    if (volCourant == NULL)
    {
        printf("Vol introuvable.");
        printf("\n**appuyer sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
    }else{
        printf("\nVOL\tCompagnie\tDepart\tDestination\tDate de vol\tHeure de depart\tHeure d'arrivee\n");
        printf("%-8d", volCourant->numero_vol);
        printf("%-15s", volCourant->compagnie);
        printf("%-10s", volCourant->depart);
        printf("%-15s", volCourant->destination);
        printf("%-15s", volCourant->date_vol);
        printf("%-16s", volCourant->heure_depart);
        printf("%s\n", volCourant->heure_arrivee);

        printf("\n--- INFORMATIONS SUR L'AVION ---\n");
        printf("Capacite de l'avion: %d", volCourant->av.capacite);
        printf("\nModel de l'avion: %s", volCourant->av.model);
        printf("\nNombre de passager: %d",volCourant->nbr_passagers);

        printf("\n===============================================\n");

        printf("\nPASSAGERS:\n");
        for (int i = 0; i < volCourant->nbr_passagers; i++)
        {
            printf("\nNumero Passager: %d",volCourant->Passager[i].num_passager);
            printf("\nNom Complet: %s",volCourant->Passager[i].nom_complet);
            printf("\nNumero Passeport: %d",volCourant->Passager[i].num_passport);
            printf("\nNumero de Place: P%d",volCourant->Passager[i].num_place);
            printf("\nCategorie: %-3s",volCourant->Passager[i].categorie);   
            printf("\n===============================================\n");
        }

        printf("\n**appuyer sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
    }
}


void supprimerPassager(ListeVols* L, int numero_vol, int num_passager) {
    Vol* vol = trouverVol(L, numero_vol);

    if (vol == NULL) {
        printf("Vol introuvable.\n");
        printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    if (vol->Passager == NULL) {
        printf("Aucun passager dans ce vol.\n");
        printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    int index = -1;
    for (int i = 0; i < vol->nbr_passagers; i++) {
        if (vol->Passager[i].num_passager == num_passager) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Passager introuvable dans ce vol.\n");
        printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
        while (!kbhit()) {}
        getch();
        fflush(stdin);
        return;
    }

    // reculer les elements du tableau
    for (int i = index; i < vol->nbr_passagers - 1; i++) {
        vol->Passager[i] = vol->Passager[i + 1];
    }

    vol->nbr_passagers--;

    printf("Passager supprime avec succes.\n");
    printf("\n** Appuyez sur n'importe quelle touche pour revenir.");
    while (!kbhit()) {}
    getch();
    fflush(stdin);
}





#endif // lib_h_included