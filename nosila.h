#ifndef NOSILA_H_INCLUDED
#define NOSILA_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#define MAX_DUZ_NAZIV 6

typedef struct
{
    char naziv[MAX_DUZ_NAZIV];
    int br_spratova;
    int br_koristenja, limit_servis, limit_blok;
} Nosilo;

void kreirajNosilo();
void prikaziNosilo();
void spisakNosila(short int);
void aktivirajNosilo(Nosilo *, FILE *);
bool pomjeriNosilo(Nosilo *, int, FILE *);

#endif // NOSILA_H_INCLUDED
