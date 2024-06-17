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
    scanf("%19s", password);            // trazi verifikaciju korisnika pomocu lozinke 

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
    BMW* nizPodataka = NULL;
    BMW* pModel = NULL;
    int izbor;

    nizPodataka = ispisBMW(imeDatoteke);
    if (nizPodataka == NULL) {
        printf("Error: Unable to read BMW data from file.\n");
        return -1;
    }

    brojBMW = getBrojBMW(imeDatoteke);
    if (brojBMW < 0) {
        printf("Error: Invalid number of BMWs.\n");      // dohvacanje trenutno pohranjenih vozila
        return -1;
    }

    while (1) {
        system("cls");
        printf("\nIzbornik:\n");
        printf("1. Dodaj novi BMW(ADMIN)\n");
        printf("2. Ispisi sve BMW automobile\n");
        printf("3. Uredi BMW(ADMIN)\n");
        printf("4. Obrisi BMW(ADMIN)\n");
        printf("5. Obrisi DAT(ADMIN)\n");
        printf("6. Sortiraj BMW-ove po cijeni (od najvise do najnize)\n");
        printf("7. Sortiraj BMW-ove po cijeni (od najnize do najvise)\n");
        printf("8. Sortiraj BMW-ove po snazi (uzlazno)\n");
        printf("9. Sortiraj BMW-ove po snazi (silazno)\n");
        printf("10. Izadji iz programa\n");

        printf("Odabir: ");

        if (scanf("%d", &izbor) != 1) {     // petlja provjerava da je korisnicki unos tipa int
            printf("Krivi odabir!\n");
            while (getchar() != '\n');
            continue;                       // continue nas vraca na pocetak unosa izbora za izbornik
        }

        IzbornikOpcija opcija = (IzbornikOpcija)izbor;      // castovanje izbora u enum IzbornikOpcija
        switch (opcija) {
        case DODAJ_BMW:
            if (nizPodataka != NULL && adminLogin()) {
                unosBMW(imeDatoteke, nizPodataka);
            }
            else {
                printf("Neuspjela prijava ili BMW polje nije inicijalizirano.\n");
            }
            break;

        case ISPISI_BMW:
            if (nizPodataka != NULL && brojBMW > 0) {
                ispisBMW(imeDatoteke);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case UREDI_BMW:
            if (nizPodataka != NULL && brojBMW > 0 && adminLogin()) {
                urediBMW(imeDatoteke);
            }
            else {
                printf("Neuspjela prijava ili BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case OBRISI_BMW:
            if (nizPodataka != NULL && brojBMW > 0 && adminLogin()) {
                obrisiBMW(imeDatoteke);
            }
            else {
                printf("Neuspjela prijava ili BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case OBRISI_DAT:
            if (adminLogin()) {
                brisanjeDatoteke(imeDatoteke);
            }
            else {
                printf("Neuspjela prijava.\n");
            }
            break;
        case SORTIRAJ_CIJENA_PADAJUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoCijeniPadajuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case SORTIRAJ_CIJENA_RASTUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoCijeniRastuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case SORTIRAJ_SNAZI_RASTUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoSnaziRastuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case SORTIRAJ_SNAZI_OPADAJUCE:
            if (nizPodataka != NULL && brojBMW > 0) {
                sortirajBMWpoSnaziOpadajuce(nizPodataka, brojBMW);
            }
            else {
                printf("BMW polje nije inicijalizirano ili ne sadrzi elemente.\n");
            }
            break;

        case IZADJI:
            if (izlazIzPrograma(nizPodataka) == 0) {
                return 0;
            }
            break;

        default:
            printf("Nepostojeci izbor.\n");
            break;
        }

        system("pause");
    }

    free(nizPodataka);                  //oslobadjanje memorije i vracanje pokazivaca na NULL vrijednost
    nizPodataka = NULL;

    return izbor;
}
