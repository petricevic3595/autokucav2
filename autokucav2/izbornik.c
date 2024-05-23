#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "podatci.h"
#include "functions.h"
#define LOGIN 20

static bool adminLogin() {
    char password[LOGIN];

    printf("Admin Login\n");
    printf("Password: ");
    scanf("%19s", password);

    if (strcmp(password, "admin123") == 0) {
        printf("Uspjesno logiranje\n");
        return true;
    }
    else {
        printf("Kriva lozinka\n");
        return false;
    }
}



int izbornik(const char* imeDatoteke) {

    static BMW* nizPodataka = NULL;
    static BMW* pModel = NULL;
    int izbor;


    nizPodataka = ispisBMW(imeDatoteke);
    if (nizPodataka == NULL) {
        printf("Error: Unable to read BMW data from file.\n");
        return -1;
    }

    brojBMW = getBrojBMW(imeDatoteke);
    if (brojBMW < 0) {
        printf("Error: Invalid number of BMWs.\n");
        return -1;
    }
    while (1) {
        system("cls");
        printf("\nIzbornik:\n");
        printf("1. Dodaj novi BMW(ADMIN)\n");
        printf("2. Ispisi sve BMW automobile\n");
        printf("3. Uredi BMW(ADMIN)\n");
        printf("4. Obrisi BMW(ADMIN)\n");
        printf("5. Sortiraj BMW-ove po cijeni (od najvise do najnize)\n");
        printf("6. Sortiraj BMW-ove po cijeni (od najnize do najvise)\n");
        printf("7. Sortiraj BMW-ove po snazi (uzlazno)\n");
        printf("8. Sortiraj BMW-ove po snazi (silazno)\n");
        printf("9. Izadji iz programa\n");
        printf("Odabir: ");

        if (scanf("%d", &izbor) != 1) {
            printf("Krivi odabir!\n");
            while (getchar() != '\n');
            continue;
        }
        switch (izbor) {
        case 1:
            if (adminLogin()) {
                unosBMW(imeDatoteke, nizPodataka);
            }
            break;
        case 2:
            ispisBMW(imeDatoteke);
            break;
        case 3:
            if (adminLogin()) {
                urediBMW(imeDatoteke);
            }
            break;
        case 4:
            if (adminLogin()) {
                obrisiBMW(imeDatoteke);
            }
            break;
        case 5:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoCijeniPadajuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW array is not initialized or contains zero elements.\n");
            }
            break;
        case 6:
            sortirajBMWpoCijeniRastuce(nizPodataka, brojBMW);
            break;
        case 7:
            sortirajBMWpoSnaziRastuce(nizPodataka, brojBMW);
            break;
        case 8:
            sortirajBMWpoSnaziOpadajuce(nizPodataka, brojBMW);
            break;
        case 9:
            izlazIzPrograma(nizPodataka);
            return 0;
        default:
            printf("Nepostojeci izbor.\n");
        }
        system("pause");
    }
    free(nizPodataka);
    nizPodataka = NULL;

    return izbor;

}
