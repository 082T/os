#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <math.h>
#include "signali.h"
#include "datoteke.h"

#define BROJ_DRETVI 3

void provjeri_unos(int argc, char *argv[]);
void obradi_status();

void *mreza(void *p);
void *obrada(void *p);

char *obrada_dat;
char *status_dat;
char *dat_mreza;

int nije_kraj = 1;
int last = -1;

int main(int argc, char *argv[])
{
    int scanbroj;
    pthread_t opisnik[BROJ_DRETVI];
    int i, j;
    int id[BROJ_DRETVI];
    FILE *fp;
    // provjera ispravnosti unosa
    provjeri_unos(argc, argv);

    stavi_signale();

    status_dat = argv[1];
    obrada_dat = argv[2];
    dat_mreza = argv[3];

    // izvadi zapis o zadnjem statusu i stavi na last
    izvadi_zadnji(status_dat);

    // ako je prekinuto sa SIGINT (last == 0)
    if (last == 0) obradi_zapis_nula(obrada_dat);
    // status_dat => "0\n"
    stavi_nulu_na_status();

    //stvori radne dretve
    for (i = 0; i < BROJ_DRETVI - 1;i++)
    {
        id[i] = i;
        if(pthread_create(&opisnik[i],NULL,obrada,&id[i]))
        {
            printf("Greska pri otvaranju dretvi\n");
            exit(1);
        }
    }
    //stvori mreznu dretvu
    id[2] = 2;
    if(pthread_create(&opisnik[i],NULL,mreza,&id[i]))
    {
        printf("Greska pri otvaranju dretvi\n");
        exit(1);
    }

    printf("Program s PID = %ld krenuo s radom\n", (long)getpid());

    //skeniraj broj i stavi kao last
    while (nije_kraj)
    {
        scanf("%d", &scanbroj);
        if(scanbroj>0)
        {
            last = scanbroj;
        }
        else
        {
            nije_kraj = 0;
            fp=fopen(dat_mreza,"w+");
            fprintf(fp,"%d",0);
            fclose(fp);
        }
    }

    for (j = 0; j < BROJ_DRETVI;j++)
    {
        pthread_join(opisnik[j], NULL);
    }

    printf("Program s PID = %ld zavrsio s radom\n", (long)getpid());

    return 0;
}



void provjeri_unos(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Unos: %s <datoteka sa statusom> <datoteka za obradu> <cjevovod>\n", argv[0]);
        exit(1);
    }
}

void obradi_status()
{
    FILE *obrada;
    last++;

    obrada = fopen(obrada_dat, "a");
    if (!obrada)
    {
        printf("Greska pri otvaranju datoteke %s\n", obrada_dat);
        exit(1);
    }
    fprintf(obrada, "%d\n", last * last);
    fclose(obrada);
    printf("Trenutni status: %d, stavljam %d u %s\n", last, last * last, obrada_dat);
}

void *mreza(void *p)
{
    while(nije_kraj)
    {
        int k;
        k=dohvati_iz_cijevi();
        if(k>0)
        {
            last=k;
        }
    }
    
    return NULL;
}

void *obrada(void *p)
{
    int *i = p;
    int t;

    if(*i==0)
    {
        while(nije_kraj)
        {
	        obradi_status();
            sleep(5);
        }
    }
    else if(*i==1)
    {
        while(nije_kraj)
        {
            FILE *obrada;
            obrada = fopen(obrada_dat, "a+");
            if (!obrada)
            {
                printf("Greska pri otvaranju datoteke %s", obrada_dat);
                exit(1);
            }

            while (!feof(obrada))
            {
                if(fscanf(obrada, "%d", &t));
            }
            if(t%25 == 0)
            {
                printf("-Trenutni status je djeljiv s 5\n");
            }
            fclose(obrada);
            sleep(4.8);
        }
    }


	return NULL;
}

