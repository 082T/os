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
void *obradarad(void *p);
void *obradadjeljiv(void *p);

int trenutni_broj_dretvi = 3;
int postavljeni_broj_dretvi = 3;

pthread_mutex_t m; 
pthread_cond_t red; 

int broj;
int trenutno_radi = 0;

char *obrada_dat;
char *status_dat;
char *dat_mreza;

pthread_t opisnik[100];
int id[100];

int nije_kraj = 1;
int last = -1;

int main(int argc, char *argv[])
{
    int scanbroj;
    int j;
    FILE *fp;

    pthread_mutex_init (&m, NULL);
    pthread_cond_init (&red, NULL);

    broj = 1;
    trenutno_radi = 0;
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
    id[1] = 1;
    if(pthread_create(&opisnik[1],NULL,obradadjeljiv,&id[1]))
    {
        printf("Greska pri otvaranju dretvi\n");
        exit(1);
    }
    id[2] = 2;
    if(pthread_create(&opisnik[2],NULL,obradarad,&id[2]))
    {
        printf("Greska pri otvaranju dretvi\n");
        exit(1);
    }
    
    //stvori mreznu dretvu
    id[0] = 0;
    if(pthread_create(&opisnik[0],NULL,mreza,&id[0]))
    {
        printf("Greska pri otvaranju dretvi\n");
        exit(1);
    }

    printf("Program s PID = %ld krenuo s radom\n", (long)getpid());

    //skeniraj broj i stavi kao last
    while (nije_kraj)
    {
        if(scanf("%d", &scanbroj)>0)
            {
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
    }

    for (j = 0; j < BROJ_DRETVI;j++)
    {
        pthread_join(opisnik[j], NULL);
    }

    printf("Program s PID = %ld zavrsio s radom\n", (long)getpid());

    pthread_mutex_destroy (&m);
    pthread_cond_destroy (&red);

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
        if(k>1 && k < 101)
        {
            printf("Broj dretvi promijenjen s %d na %d!\n",postavljeni_broj_dretvi,k);
            postavljeni_broj_dretvi=k;
        }
	else continue;
        while(trenutni_broj_dretvi < postavljeni_broj_dretvi)
        {
            if(pthread_create(&opisnik[trenutni_broj_dretvi],NULL,obradarad,&id[trenutni_broj_dretvi]))
            {
                printf("Greska pri otvaranju dretvi\n");
                exit(1);
            }
            trenutni_broj_dretvi++;
            sleep(1);
        }
    }
    
    return NULL;
}

void *obradarad(void *p)
{
    while(nije_kraj)
    {
        pthread_mutex_lock (&m); 
        while(trenutno_radi)
        {
            pthread_cond_wait(&red,&m);
        }
        trenutno_radi=*((int*)p);
        pthread_mutex_unlock(&m);

        if(trenutni_broj_dretvi > postavljeni_broj_dretvi)
        {
            pthread_mutex_lock (&m);
            trenutno_radi = 0;
            broj++;
            pthread_mutex_unlock (&m);
            pthread_cond_broadcast (&red);

            trenutni_broj_dretvi--;
            pthread_exit(NULL);
        }

	    obradi_status();
        
        pthread_mutex_lock (&m);
        trenutno_radi = 0;
        broj++;
        pthread_mutex_unlock (&m);
        pthread_cond_broadcast (&red);

        sleep(5);
    }
    return NULL;
}
    
void *obradadjeljiv(void *p)
{
    int t;

    while(nije_kraj)
    {
        pthread_mutex_lock (&m); 
        while(trenutno_radi)
        {
            pthread_cond_wait(&red,&m);
        }
        trenutno_radi=*((int*)p);
        pthread_mutex_unlock(&m);

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
        
        pthread_mutex_lock (&m);
        trenutno_radi = 0;
        broj++;
        pthread_mutex_unlock (&m);
        pthread_cond_broadcast (&red);
        
        sleep(3);
    }

	return NULL;
}
