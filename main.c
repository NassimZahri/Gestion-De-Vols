#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include "lib.h"

#define ADMIN_ID "admin"
#define ADMIN_PWD "admin"

void adminMenu(ListeVols* L) {
    int choix;

    do {
        system("cls");
        printf("\n=== ADMIN MENU ===\n");
        printf("1. Ajouter un vol\n");
        printf("2. Supprimer un vol\n");
        printf("\n3. Modifier un vol\n");
        printf("4. Modifier statut d'un vol\n");
        printf("\n5. Affichage des vols\n");
        printf("\n6. Affichage des passager\n");
        printf("7.  Exclure un Passager \n");
        printf("8.  Trouver un Passager \n");
        printf("\n0. Retourner au menu principale\n");
        printf("\nChoix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterVol(L);
                break;
            case 2: {
                int numero_vol;
                printf("Numero de vol a supprimer : ");
                scanf("%d", &numero_vol);
                supprimerVol(L, numero_vol);
                break;
            }
            case 3: {
                int numero_vol;
                system("cls");
                printf("Numero de vol a modifier : ");
                scanf("%d", &numero_vol);
                modifierVol(L, numero_vol);
                break;
            }
            case 4:
                modifierStatusVol(L);
                break;
            case 5:
                afficherVols(L);
                break;
            case 6: {
                int num;
                printf("Entrez le numero de vol : ");
                scanf("%d", &num);
                afficherPassagers(L,num);
                break;
            }
            case 7: {
                int numV,numP;
                printf("Entrez le numero de vol : ");
                scanf("%d", &numV);
                printf("Entrew le numero de passager : ");
                scanf("%d", &numP);
                supprimerPassager(L,numV,numP);
                break;
            }
            case 8: {
                int numP;
                printf("Entrez le numero de passager : ");
                scanf("%d", &numP);
                trouverPassager(L,numP);
                break;
            }
            
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                system("cls");
                printf("Choix invalide. Veuillez reessayer.\n");
                sleep(1.5);
                break;
        }

    } while (choix != 0);
}

void userMenu(ListeVols* L) {
    int choix;

    do {
        system("cls");
        printf("\n=== USER MENU ===\n");
        printf("1. Afficher Vols\n");
        printf("2. Reserver un Vol\n");
        printf("\n0. Retourner au menu principale\n");
        printf("\nChoix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherVolsClient(L);
                break;
            case 2: {
                char destination[50];
                printf("Entrez la destination : ");
                scanf("%s", destination);
                reserverVol(L, destination);
                break;
            }

            case 0:
                printf("Au revoir !\n");
                break;
            default:
                system("cls");
                printf("Choix invalide. Veuillez reessayer.\n");
                sleep(1.5);
                break;
        }

    } while (choix != 0);
}

int main() {
    ListeVols* L = initialiserListe();
    int choix;
    int isAdmin = 0;

    do {
        system("cls");
        printf("\n=== MAIN MENU ===\n");
        printf("1. Admin\n");
        printf("2. Normal User\n");
        printf("\n0. Quitter\n");
        printf("\nChoix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                char admin_id[20];
                char admin_pwd[20];

                printf("Admin ID: ");
                scanf("%s", admin_id);
                printf("Password: ");
                scanf("%s", admin_pwd);

                if (strcmp(admin_id, ADMIN_ID) == 0 && strcmp(admin_pwd, ADMIN_PWD) == 0) {
                    isAdmin = 1;
                    adminMenu(L);
                } else {
                    printf("Identifiant ou mot de passe incorrect.\n");
                    sleep(1.5);
                }
                break;
            }
            case 2:
                userMenu(L);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                system("cls");
                printf("Choix invalide. Veuillez reessayer.\n");
                sleep(1.5);
                break;
        }

    } while (choix != 0);

    

    return 0;
}
