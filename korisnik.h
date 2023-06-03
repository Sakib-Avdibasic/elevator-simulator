#ifndef KORISNIK_H_INCLUDED
#define KORISNIK_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#define MAX_DUZ_EMAIL 257
#define MAX_DUZ_SIFRA 21

typedef struct
{
    char email[MAX_DUZ_EMAIL];
    char sifra[MAX_DUZ_SIFRA];
} Korisnik;

bool prijava(Korisnik *, short int);
void kreirajKorisnika();
void meniAdmin();
void meniKorisnik();

#endif // KORISNIK_H_INCLUDED
