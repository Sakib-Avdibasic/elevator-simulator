#include <stdio.h>
#include "korisnik.h"
#include "dodaci.h"

int main()
{
    cls();
    short int br_pokusaja = 3;
    while(br_pokusaja > 0) {
        Korisnik k;
        printf("Prijava");
        if(br_pokusaja < 3) printf(" (preostalo pokusaja: %d)" CRTA, br_pokusaja);
        else printf(CRTA);
        printf("Email ");
        stringUnos(k.email, 3, MAX_DUZ_EMAIL);
        printf("Sifra ");
        stringUnos(k.sifra, 6, MAX_DUZ_SIFRA);

        bool postoji = prijava(&k, ADMIN);
        if(postoji) {
            meniAdmin();
            break;
        }
        else {
            postoji = prijava(&k, KORISNIK);
            if(postoji) {
                meniKorisnik();
                break;
            }
            else {
                cls();
                printf("Ne postoji korisnik sa unesenim podacima.\n\n");
                br_pokusaja--;
            }
        }
    }

    return 0;
}
