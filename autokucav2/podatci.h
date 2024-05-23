#pragma once

#define MODLEN 50

typedef struct {
    char model[MODLEN];
    float cijena;
    float potrosnja;
    float ubrzanje;
    int id;
    int snaga;
    int godinaProizvodnje;
    int kilometraza;
} BMW;