#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main(){
ListeVols* L = initialiserListe();
    int choix;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Ajouter un vol\n");
        printf("2. Supprimer un vol\n");
        printf("3. Afficher tous les vols\n");
        printf("4. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterVol(L);
                break;
            case 2:
                {
                    int numero_vol;
                    printf("Numero de vol a supprimer : ");
                    scanf("%d", &numero_vol);
                    supprimerVol(L, numero_vol);
                }
                break;
            case 3:
                afficherVols(L);
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

    } while (choix != 4);

    // Free memory and clean up
    // ...

    return 0;
}