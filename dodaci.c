#include "dodaci.h"
#include <time.h>
#include <ctype.h>
#include <string.h>

bool provjeriFajl(FILE *fp) {
    if(fp == NULL) {
        printf("\nDoslo je do neocekivanog problema\n");
        fclose(fp);
        return false;
    }
    return true;
}

bool potvrdanUnos() {
    char c;
    do {
        printf("[y/n]: ");
        scanf(" %c", &c);
        c = tolower(c);
    } while(c != 'y' && c != 'n');
    return c == 'y';
}

void stringUnos(char *s, int min_duz, int max_duz) {
    int duz;
    do {
        printf("(%d-%d znakova): ", min_duz, max_duz-1);
        fflush(stdin); // Da se unos koji je bio viska ne bi prenio u sljedeci unos
        memset(s, '\0', max_duz); // Da se string ocisti/inicijalizira kao prazan
        fgets(s, max_duz+1, stdin);

        if(strchr(s, ' ') != NULL) {
            printf("Bez praznih mjesta!\n");
            continue;
        }
        duz = strlen(s);
        if(s[duz-1] == '\n') {
            s[duz-1] = '\0';
            duz--;
            if(duz >= min_duz) break;
        }
    } while(1);
}

void delay(int br_sekundi)
{
    int milisekunde = 1000 * br_sekundi;
    clock_t pocetno = clock();
    while (clock() < pocetno + milisekunde) {}
}

void cls() {
    system("cls");
    printf("\x1b[7m%70s%50s\x1b[m\n", "L I F T  T R A C K E R", "");
}
