#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "korisnik.h"
#include "nosila.h"
#include "dodaci.h"

bool prijava(Korisnik *k, short int tip) {
    FILE *fp = fopen(tip == ADMIN ? "admin.dat" : "korisnici.dat", "rb");
    if(!provjeriFajl(fp)) return false;

    Korisnik a;
    while(!feof(fp))
    {
        fscanf(fp, "%s %s", a.email, a.sifra);
        if(strcmp(k->email, a.email) == 0 && strcmp(k->sifra, a.sifra) == 0) {
            fclose(fp);
            return true;
        }
    }

    fclose(fp);
    return false;
}

void kreirajKorisnika()
{
    Korisnik k;
    printf("Unos podataka novog korisnika" CRTA);
    printf("Email ");
    stringUnos(k.email, 1, MAX_DUZ_EMAIL);
    printf("Sifra ");
    stringUnos(k.sifra, 1, MAX_DUZ_SIFRA);

    FILE *fp = fopen("korisnici.dat", "rb+");
    if(fp != NULL) {
        Korisnik postojeci;
        while(!feof(fp)) {
            fscanf(fp, "%s %s", postojeci.email, postojeci.sifra);
            if(strcmp(postojeci.email, k.email) == 0) {
                printf("Vec postoji korisnik sa tim emailom, zelite li promjeniti njegovu sifru ");
                if(potvrdanUnos()) {
                    fseek(fp, -(strlen(postojeci.email)+strlen(postojeci.sifra)+1), 1);
                    fprintf(fp, "%s %s\n", k.email, k.sifra);
                    printf("\nSifra uspjesno promjenjena!\n");
                }
                fclose(fp);
                return;
            }
        }
    }

    fp = fopen("korisnici.dat", "ab+");
    fprintf(fp, "%s %s\n", k.email, k.sifra);
    printf("\nKorisnik uspjesno kreiran!\n");
    fclose(fp);
}

void meniAdmin()
{
    cls();
    printf("Uspjesno logovani kao administrator!\n");
    while(1)
    {
        printf("\nIzbornik" CRTA);
        printf("1. Kreiranje novog korisnika\n2. Kreiranje novog nosila\n3. Ispis stanja odredjenog nosila\n4. Ispis nosila kojima je potrebno servisiranje\n5. Ispis blokiranih nosila\n6. Izlaz iz programa" CRTA);
        printf("Broj pored zeljene opcije: ");
        int opcija;
        scanf("%d", &opcija);
        cls();

        switch(opcija)
        {
        case 1:
            kreirajKorisnika();
            break;
        case 2:
            kreirajNosilo();
            break;
        case 3:
            prikaziNosilo();
            break;
        case 4:
            spisakNosila(SERVIS);
            break;
        case 5:
            spisakNosila(BLOK);
            break;
        case 6:
            return;
        default:
            printf("\nNe postoji opcija pod unesenim brojem\n");
        }
    }
}

void meniKorisnik()
{
    cls();
    printf("Uspjesno logovani kao korisnik!\n");
    FILE *fp = fopen("nosila.dat", "rb+");
    if(!provjeriFajl(fp)) return;

    Nosilo aktiv;
    while(1)
    {
        printf("\nIzbornik" CRTA);
        printf("1. Aktivacija nosila\n2. Poziv nosila\n3. Izlaz iz programa" CRTA);
        printf("Broj pored zeljene opcije: ");
        int opcija;
        scanf("%d", &opcija);
        cls();

        switch(opcija) {
            case 1:
                aktivirajNosilo(&aktiv, fp);
                break;
            case 2:
                if(strcmp(aktiv.naziv, "") == 0) {
                    printf("\nNi jedno nosilo nije aktivirano za koristenje.\n");
                    break;
                }
                if(!pomjeriNosilo(&aktiv, 0, fp)) break;
                int br_sprata;
                if(aktiv.br_spratova > 2) {
                    printf("Broj zeljenog sprata ");
                    do {
                        printf("(1-%d): ", aktiv.br_spratova-1);
                        scanf("%d", &br_sprata);
                    } while(br_sprata < 1 || br_sprata > aktiv.br_spratova-1);
                }
                else br_sprata = 1;
                if(!pomjeriNosilo(&aktiv, br_sprata, fp)) break;
                delay(1);
                cls();
                break;
            case 3:
                fclose(fp);
                return;
            default:
                 printf("\nNe postoji opcija pod unesenim brojem\n");
        }
    }
}
