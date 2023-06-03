#ifndef DODACI_H_INCLUDED
#define DODACI_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#define CRTA "\n-------------------------------------\n"
#define ADMIN 0
#define KORISNIK 1
#define SERVIS 0
#define BLOK 1

bool provjeriFajl(FILE *);
bool potvrdanUnos();
void stringUnos(char *, int, int);
void delay(int);
void cls();

#endif // DODACI_H_INCLUDED
