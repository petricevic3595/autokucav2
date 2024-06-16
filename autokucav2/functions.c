#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"
#include "podatci.h"

#define PROVJERA 3

int brojBMW = 0;

void kreirajDatoteku(const char* imeDatoteke) {
    FILE* datoteka = fopen(imeDatoteke, "rb+");
    if (datoteka == NULL) {
        printf("Datoteka %s ne postoji. Kreiranje datoteke...\n", imeDatoteke);
        datoteka = fopen(imeDatoteke, "wb");
        if (datoteka == NULL) {
            perror("Greska prilikom kreiranja datoteke");
            exit(EXIT_FAILURE);
        }
        int tmp = 0;
        fwrite(&tmp, sizeof(int), 1, datoteka);
        fclose(datoteka);
        printf("Datoteka %s uspjesno kreirana!\n\n", imeDatoteke);
    }
    else {
        printf("Datoteka %s vec postoji!\n\n", imeDatoteke);
        fclose(datoteka);
    }
}

int getBrojBMW(const char* const imeDatoteke) {
    FILE* pF = fopen(imeDatoteke, "rb");
    if (pF == NULL) {
        perror("Error opening file");
        return -1;
    }

    int numBMW;
    fread(&numBMW, sizeof(int), 1, pF);
    fclose(pF);

    return numBMW;
}

void unosBMW(const char* const fileName, const BMW* nizPodataka) {
    printf("Dodavanje BMW:\n\n");
    bool validInput = false;

    FILE* pF = fopen(fileName, "rb+");

    if (pF == NULL) {
        perror("Dodavanje BMWa u BMW.bin");
        exit(EXIT_FAILURE);
    }
    printf("Broj dodanih BMW-ova: %d\n\n", brojBMW);

    BMW temp;
    temp.id = brojBMW;
    printf("Unesite model (do 30 znakova):\n");
    //pitaj matiju za zauzimanje ako treba ovdje
    char model[MODLEN];
    scanf(" %30[^\n]", model);
    if (strlen(model) <= MODLEN) {
        strcpy(temp.model, model);
        printf("Model unesen: %s\n", temp.model);
    }
    else {
        printf("Previše znakova. Unos odbijen.\n");
        while (getchar() != '\n');
    }

    getchar();
    while (!validInput) {
        printf("Cijena:\n ");
        if (scanf("%f", &temp.cijena) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Potrosnja (litara na 100km):\n ");
        if (scanf("%f", &temp.potrosnja) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Ubranje u sec(0-100km/h):\n ");
        if (scanf("%f", &temp.ubrzanje) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Snaga(HP):\n ");
        if (scanf("%d", &temp.snaga) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Godina proizvodnje:\n");
        if (scanf("%d", &temp.godinaProizvodnje) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        printf("Kilometraza:\n");
        if (scanf("%d", &temp.kilometraza) == 1) {
            validInput = true;
        }
        else {
            printf("Netocan unos!\n");
            while (getchar() != '\n');
        }
    }

    fread(&brojBMW, sizeof(int), 1, pF);
    fseek(pF, sizeof(BMW) * brojBMW, SEEK_CUR);
    fwrite(&temp, sizeof(BMW), 1, pF);
    rewind(pF);
    brojBMW++;
    fwrite(&brojBMW, sizeof(int), 1, pF);
    fclose(pF);
    printf("\n");
    printf("BMW uspjesno dodan!\n\n");
}

BMW* ispisBMW(const char* const imeDatoteke) {
    printf("Ucitavanje podataka...\n\n");
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL) {
        perror("Ucitavanje podataka iz datoteke");
        return NULL;
    }

    fread(&brojBMW, sizeof(int), 1, pF);
    printf("Broj BMW automobila: %d\n\n", brojBMW);
    BMW* nizBMW = (BMW*)calloc(brojBMW, sizeof(BMW));
    if (nizBMW == NULL) {
        perror("Alokacija memorije za BMW automobile");
        return NULL;
    }

    fread(nizBMW, sizeof(BMW), brojBMW, pF);
    if (nizBMW == NULL) {
        printf("Polje BMW automobila je prazno!\n");
        return NULL;
    }

    int i;
    for (i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", i + 1);
        printf("ID: %d\n", nizBMW[i].id);
        printf("Model: %s\n", nizBMW[i].model);
        printf("Cijena: %.2f\n", nizBMW[i].cijena);
        printf("Potrosnja: %.2f\n", nizBMW[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizBMW[i].ubrzanje);
        printf("Snaga: %d\n", nizBMW[i].snaga);
        printf("Godina proizvodnje: %d\n", nizBMW[i].godinaProizvodnje);
        printf("Kilometraza: %d\n\n", nizBMW[i].kilometraza);
    }

    printf("Uspjesno ucitano!\n");
    return nizBMW;
}

void urediBMW(const char* const imeDatoteke) {
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL) {
        perror("Uredjivanje BMW-a u BMW.bin");
        exit(EXIT_FAILURE);
    }

    fseek(pF, sizeof(int), SEEK_SET); 

    int urediBMW;
    printf("Unesite ID BMW-a koji zelite urediti: ");
    if (scanf("%d", &urediBMW) != 1) {
        printf("Neispravan unos ID-a BMW-a.\n");
        fclose(pF);
        return;
    }

   
    int pronadeniIndex = -1;
    BMW temp;
    while (fread(&temp, sizeof(BMW), 1, pF) == 1) {
        if (temp.id == urediBMW) {
            pronadeniIndex = ftell(pF) / sizeof(BMW) - 1; 
            break;
        }
    }

    if (pronadeniIndex == -1) {
        printf("BMW s ID-om %d nije pronaden!\n", urediBMW);
        fclose(pF);
        return;
    }

    printf("Uredjivanje BMW-a s ID-om %d\n", urediBMW);

    printf("Unesite novi model (do 30 znakova, moze sadrzavati razmake):\n");
    char model[PROVJERA];
    scanf(" %30[^\n]", model);
    if (strlen(model) <= 30) {
        strcpy(temp.model, model);
    }
    else {
        printf("Previse znakova. Model nece biti promijenjen.\n");
        while (getchar() != '\n');
    }

    printf("Unesite novu cijenu:\n");
    if (scanf("%f", &temp.cijena) != 1) {
        printf("Neispravan unos. Cijena nece biti promijenjena.\n");
        while (getchar() != '\n'); 
    }

    printf("Unesite novu potrosnju (litara na 100km):\n");
    if (scanf("%f", &temp.potrosnja) != 1) {
        printf("Neispravan unos. Potrosnja nece biti promijenjena.\n");
        while (getchar() != '\n'); 
    }

    printf("Unesite novo ubrzanje (0-100km/h):\n");
    if (scanf("%f", &temp.ubrzanje) != 1) {
        printf("Neispravan unos. Ubrzanje nece biti promijenjeno.\n");
        while (getchar() != '\n'); 
    }

    printf("Unesite novu snagu (HP):\n");
    if (scanf("%d", &temp.snaga) != 1) {
        printf("Neispravan unos. Snaga nece biti promijenjena.\n");
        while (getchar() != '\n'); 
    }

    printf("Unesite novu godinu proizvodnje:\n");
    if (scanf("%d", &temp.godinaProizvodnje) != 1) {
        printf("Neispravan unos. Godina proizvodnje nece biti promijenjena.\n");
        while (getchar() != '\n'); 
    }

    printf("Unesite novu kilometrazu:\n");
    if (scanf("%d", &temp.kilometraza) != 1) {
        printf("Neispravan unos. Kilometraza nece biti promijenjena.\n");
        while (getchar() != '\n'); 
    }

    
    fseek(pF, sizeof(int) + pronadeniIndex * sizeof(BMW), SEEK_SET);
    fwrite(&temp, sizeof(BMW), 1, pF);

    fclose(pF);
    printf("BMW s ID-om %d uspjesno uredjen!\n", urediBMW);
}

void obrisiBMW(const char* const imeDatoteke) {
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL) {
        perror("Brisanje BMW-a iz BMW.bin");
        exit(EXIT_FAILURE);
    }

    fseek(pF, sizeof(int), SEEK_SET); 

    int obrisiBMW;
    printf("Unesite ID BMW-a koji zelite obrisati: ");
    if (scanf("%d", &obrisiBMW) != 1) {
        printf("Neispravan unos ID-a BMW-a.\n");
        fclose(pF);
        return;
    }

    
    int pronadeniIndex = -1;
    BMW temp;
    while (fread(&temp, sizeof(BMW), 1, pF) == 1) {
        if (temp.id == obrisiBMW) {
            pronadeniIndex = ftell(pF) / sizeof(BMW) - 1; 
            break;
        }
    }

    if (pronadeniIndex == -1) {
        printf("BMW s ID-om %d nije pronaden!\n", obrisiBMW);
        fclose(pF);
        return;
    }
    char potvrda[PROVJERA];
    printf("Jeste li sigurni da zelite izbrisati BMW s ID-om %d? (da/ne): ", obrisiBMW);
    if (scanf("%2s", potvrda) != 1) {
        printf("Neispravan unos. Brisanje prekinuto.\n");
        fclose(pF);
        return;
    }
    if (strcmp(potvrda, "da") != 0) {
        printf("Brisanje prekinuto.\n");
        fclose(pF);
        return;
    }
    
    fseek(pF, -(long)sizeof(BMW), SEEK_END);

    
    BMW lastBMW;
    fread(&lastBMW, sizeof(BMW), 1, pF);

   
    fseek(pF, sizeof(int) + pronadeniIndex * sizeof(BMW), SEEK_SET);
    fwrite(&lastBMW, sizeof(BMW), 1, pF);

    
    fseek(pF, 0, SEEK_SET);
    int brojBMW;
    fread(&brojBMW, sizeof(int), 1, pF);
    brojBMW--;
    fseek(pF, 0, SEEK_SET);
    fwrite(&brojBMW, sizeof(int), 1, pF);

    fclose(pF);
    printf("BMW s ID-om %d uspjesno obrisan!\n", obrisiBMW);
}

int usporedbaSilazno(const void* a, const void* b) {
    const BMW* BMWa = (const BMW*)a;
    const BMW* BMWb = (const BMW*)b;
    if (BMWa->cijena < BMWb->cijena) return 1;
    if (BMWa->cijena > BMWb->cijena) return -1;
    return 0;
}

void sortirajBMWpoCijeniPadajuce(BMW* nizPodataka, int brojBMW) {

    qsort(nizPodataka, brojBMW, sizeof(BMW), usporedbaSilazno);

  
    printf("Sortirani BMW automobili po cijeni (od najvise do najnize):\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Cijena: %.2f\n", nizPodataka[i].cijena);
        printf("Potrošnja: %.2f\n", nizPodataka[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Snaga: %d\n", nizPodataka[i].snaga);
        printf("Godina proizvodnje: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Kilometraža: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int usporedbaUzlazno(const void* a, const void* b) {
    const BMW* bmw1 = (const BMW*)a;
    const BMW* bmw2 = (const BMW*)b;
    if (bmw1->cijena < bmw2->cijena) return -1;
    if (bmw1->cijena > bmw2->cijena) return 1;
    return 0;
}

void sortirajBMWpoCijeniRastuce(BMW* nizPodataka, int brojBMW) {
    
    qsort(nizPodataka, brojBMW, sizeof(BMW), usporedbaUzlazno);

    
    printf("BMW sortirannje od najnize do najvise cijene:\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobile %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Price: %.2f\n", nizPodataka[i].cijena);
        printf("Consumption: %.2f\n", nizPodataka[i].potrosnja);
        printf("Acceleration: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Power: %d\n", nizPodataka[i].snaga);
        printf("Year of production: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Mileage: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int snagaUzlazno(const void* a, const void* b) {
    const BMW* bmw1 = (const BMW*)a;
    const BMW* bmw2 = (const BMW*)b;
    if (bmw1->snaga < bmw2->snaga) return -1;
    if (bmw1->snaga > bmw2->snaga) return 1;
    return 0;
}

void sortirajBMWpoSnaziRastuce(BMW* nizPodataka, int brojBMW) {
    
    qsort(nizPodataka, brojBMW, sizeof(BMW), snagaUzlazno);

    
    printf("BMW automobili sortirani po snazi (Uzlazno):\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Cijena: %.2f\n", nizPodataka[i].cijena);
        printf("Potrošnja: %.2f\n", nizPodataka[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Snaga: %d\n", nizPodataka[i].snaga);
        printf("Godina proizvodnje: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Kilometraža: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int snagaSilazno(const void* a, const void* b) {
    return snagaUzlazno(b, a);
}

void sortirajBMWpoSnaziOpadajuce(BMW* nizPodataka, int brojBMW) {
    qsort(nizPodataka, brojBMW, sizeof(BMW), snagaSilazno);


    printf("BMW automobili sortirani po snazi (silazno):\n");
    for (int i = 0; i < brojBMW; i++) {
        printf("BMW automobil %d:\n", nizPodataka[i].id);
        printf("Model: BMW %s\n", nizPodataka[i].model);
        printf("Cijena: %.2f\n", nizPodataka[i].cijena);
        printf("Potrošnja: %.2f\n", nizPodataka[i].potrosnja);
        printf("Ubrzanje: %.2f\n", nizPodataka[i].ubrzanje);
        printf("Snaga: %d\n", nizPodataka[i].snaga);
        printf("Godina proizvodnje: %d\n", nizPodataka[i].godinaProizvodnje);
        printf("Kilometraža: %d\n\n", nizPodataka[i].kilometraza);
    }
}

int izlazIzPrograma(BMW* nizPodataka) {
    char potvrda[PROVJERA];
    while (1) {
        printf("Zaista zelite izaci iz programa?\n");
        printf("Upisite \"da\" ako zaista zelite izaci, inace upisite \"ne\"!\n");
        if (scanf("%3s", potvrda) == 1) {
            if (strcmp("da", potvrda) == 0) {
                free(nizPodataka);
                nizPodataka = NULL;
                return 0;
            }
            else if (strcmp("ne", potvrda) == 0) {
                return 1;
            }
        }
        else {
            printf("Neispravan unos. Molimo upisite \"da\" ili \"ne\".\n");
            
            while (getchar() != '\n');
        }
    }
    free(nizPodataka);
    nizPodataka = NULL;
}

void brisanjeDatoteke(const char* imeDatoteke) {
    printf("Zelite li uistinu obrisati datoteku %s?\n", imeDatoteke);
    printf("Utipkajte \"da\" ako uistinu želite obrisati datoteku u suprotno utipkajte\
\"ne\"!\n");
    char potvrda[PROVJERA] = { '\0' };
    scanf("%2s", potvrda);
    if (!strcmp("da", potvrda)) {
        remove(imeDatoteke) == 0 ? printf("Uspjesno obrisana datoteka %s!\n",
            imeDatoteke) : printf("Neuspjesno brisanje datoteke %s!\n", imeDatoteke);
    }
}
