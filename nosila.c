#include "nosila.h"
#include "dodaci.h"

void kreirajNosilo()
{
    Nosilo n;
    printf("Unos podataka o nosilu" CRTA);

    printf("Naziv nosila ");
    stringUnos(n.naziv, 1, MAX_DUZ_NAZIV);
    printf("Broj spratova ");
    do {
        printf("(min. 2): ");
        scanf("%d", &(n.br_spratova));
    } while(n.br_spratova < 2);
    printf("Broj mogucih koristenja prije servisiranja ");
    do {
        printf("(min. 1): ");
        scanf("%d", &(n.limit_servis));
    } while (n.limit_servis < 1);
    printf("Broj mogucih dodatnih koristenja prije blokiranja ");
    do {
        printf("(min. 1): ");
        scanf("%d", &(n.limit_blok));
    } while (n.limit_blok < 1);
    n.br_koristenja = 0;

    printf("Zelite li pohraniti podatke o nosilu ");
    if(potvrdanUnos()) {
        FILE *fp = fopen("nosila.dat", "rb+");
        if(fp != NULL) {
            Nosilo postojece;
            while(fread(&postojece, sizeof(Nosilo), 1, fp) == 1) {
                if(strcmp(postojece.naziv, n.naziv) == 0) {
                    printf("Vec postoji nosilo sa tim nazivom, zelite li promjeniti njegove podatke ");
                    if(potvrdanUnos()) {
                        fseek(fp, -sizeof(Nosilo), SEEK_CUR);
                        fwrite(&n, sizeof(Nosilo), 1, fp);
                        printf("\nPromjene uspjesno pohranjene!\n");
                    }
                    fclose(fp);
                    return;
                 }
            }
        }

        fp = fopen("nosila.dat", "ab+");
        if(!provjeriFajl(fp)) return;
        fwrite(&n, sizeof(Nosilo), 1, fp);
        fclose(fp);
        printf("\nNosilo uspjesno pohranjeno!\n");
    }
}

void prikaziNosilo() {
    char s[MAX_DUZ_NAZIV];
    printf("Naziv zeljenog nosila ");
    stringUnos(s, 1, MAX_DUZ_NAZIV);

    FILE *fp = fopen("nosila.dat", "rb");
    if(!provjeriFajl(fp)) return;

    Nosilo n;
    while(fread(&n, sizeof(Nosilo), 1, fp) == 1) {
        if (strcmp(n.naziv, s) == 0) {
            printf("\nNosilo '%s'" CRTA, n.naziv);
            printf("Broj koristenja - %d\n", n.br_koristenja);
            int x = n.limit_servis - n.br_koristenja;
            printf(x > 0 ? "%d do servisa" : "Nosilu potreban servis", x);
            printf("\n");
            x = n.limit_servis+n.limit_blok - n.br_koristenja;
            printf(x > 0 ? "%d do blokade" : "Nosilo je blokirano", x);
            printf("\n");
            fclose(fp);
            return;
        }
    }
    printf("\nNe postoji nosilo sa trazenim imenom\n");
    fclose(fp);
}

void spisakNosila(short int tip) {
    FILE *fp = fopen("nosila.dat", "rb+");
    if(!provjeriFajl(fp)) return;

    Nosilo n;
    bool potreban = false;
    while(fread(&n, sizeof(Nosilo), 1, fp) == 1) {
        int razlika = tip == SERVIS ? n.limit_servis-n.br_koristenja : n.limit_blok+n.limit_servis-n.br_koristenja;
        if (razlika <= 0) {
            if(!potreban) {
                printf(tip == SERVIS ? "Sljedecim nosilima je potreban servis:\n\n" : "Sljedeca nosila su blokirana:\n\n");
                potreban = true;
            }
            printf("'%s'\n", n.naziv);
        }
    }
    printf("\n");

    if(!potreban) {
        printf(tip == SERVIS ? "Nijednom nosilu nije potreban servis.\n" : "Nijedno nosilo nije blokirano\n");
        fclose(fp);
        return;
    }

    printf("Zelite li servisirati nosila ");
    if(potvrdanUnos()) {
        fseek(fp, 0, SEEK_SET);
        while(fread(&n, sizeof(Nosilo), 1, fp) == 1) {
            int razlika = tip == SERVIS ? n.limit_servis-n.br_koristenja : n.limit_blok+n.limit_servis-n.br_koristenja;
            if (razlika <= 0) {
                n.br_koristenja = 0;
                fseek(fp, -sizeof(Nosilo), 1);
                fwrite(&n, sizeof(Nosilo), 1, fp);
                fflush(fp);
            }
        }
        printf("\nNosila uspjesno servisirana!\n");
    }

    fclose(fp);
}

void aktivirajNosilo(Nosilo *aktiv, FILE *fp) {
    printf("Naziv zeljenog nosila ");
    char s[MAX_DUZ_NAZIV];
    stringUnos(s, 1, MAX_DUZ_NAZIV);
    if(strcmp(aktiv->naziv, s) == 0) {
        printf("\nNosilo '%s' je vec aktivirano!\n", s);
        return;
    }
    strcpy(aktiv->naziv, "");
    fflush(fp);
    fseek(fp, 0, SEEK_SET);
    Nosilo n;
    while(fread(&n, sizeof(Nosilo), 1, fp)==1) {
        if(strcmp(n.naziv, s) == 0) {
            printf("\nNosilo uspjesno aktivirano!\n");
            *aktiv = n;
            return;
        }
    }
    if(strcmp(aktiv->naziv, "") == 0) printf("\nNe postoji nosilo sa zeljenim imenom.\n");
}

bool pomjeriNosilo(Nosilo *n, int sprat, FILE *fp) {
    if(n->br_koristenja == n->limit_servis + n->limit_blok) {
        printf("\nAktivirano nosilo '%s' je trenutno blokirano\n", n->naziv);
        return false;
    }

    bool dize = sprat != 0;
    int br_pomjeranja = dize ? sprat+1 : n->br_spratova;
    for(int i = 0; i < br_pomjeranja; i++) {
        if (i > 0) delay(1);
        cls();
        for(int j = 0; j < n->br_spratova; j++) {
            if((!dize && i == j) || (dize && n->br_spratova-i-1 == j)) printf("\x1b[92m|||\x1b[m");
            else printf("|");
            printf("\n\n");
        }
        printf(i==br_pomjeranja-1 ? "\aNosilo je stiglo! " : dize ? "Nosilo se dize..." : "Nosilo se spusta...");
    }

    n->br_koristenja++;
    fseek(fp, -sizeof(Nosilo), SEEK_CUR);
    fwrite(n, sizeof(Nosilo), 1, fp);
    fflush(fp);

    return true;
};
