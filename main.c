#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include "lib.h"

int main() {
    ListeVols* L = initialiserListe();
    int choix;

    do {
        system("cls");
        printf("\n=== MENU ===\n");
        printf("1. Ajouter un vol\n");
        printf("2. Supprimer un vol\n");
        printf("3. Modifier un vol\n");
        printf("4. Affichage des vols\n");
        printf("5. Quitter\n");
        printf("Choix : ");
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
                afficherVols(L);
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                system("cls");
                printf("Choix invalide. Veuillez reessayer.\n");
                sleep(1.5);
                break;
        }

    } while (choix != 5);

    // Free memory and clean up
    // ...

    return 0;
}