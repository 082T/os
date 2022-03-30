#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

void provjeri_unos(int argc, char *argv[]);
void izvadi_zadnji(char *status_dat);
void obradi_zapis_nula();
void stavi_nulu_na_status();
void obradi_status();
void obradi_sigusr1(int sig);
void obradi_sigterm(int sig);
void obradi_sigint(int sig);

char *obrada_dat;
char *status_dat;
int nije_kraj = 1;
int last = -1;

int main(int argc, char *argv[])
{
    struct sigaction act;

    // provjera ispravnosti unosa
    provjeri_unos(argc, argv);

    // maskiranje SIGUSR1
    act.sa_handler = obradi_sigusr1;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGTERM);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, NULL);
    // maskiranje SIGTERM
    act.sa_handler = obradi_sigterm;
    sigemptyset(&act.sa_mask);
    sigaction(SIGTERM, &act, NULL);
    // maskiranje SIGINT
    act.sa_handler = obradi_sigint;
    sigaction(SIGINT, &act, NULL);

    // izvadi zapis o zadnjem statusu i stavi na last
    izvadi_zadnji(status_dat);

    // ako je prekinuto sa SIGINT (last == 0)
    if (last == 0) obradi_zapis_nula(obrada_dat);

    // status_dat => "0\n"
    stavi_nulu_na_status();
    // obrada svakih 5 sekundi
    printf("Program s PID = %ld krenuo s radom\n", (long)getpid());
    while (nije_kraj)
    {
        obradi_status();
        sleep(5);
    }
    printf("Program s PID = %ld zavrsio s radom\n", (long)getpid());

    return 0;
}

void provjeri_unos(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Unos: %s <datoteka sa statusom> <datoteka za obradu>", argv[0]);
        exit(1);
    }
    if (argc == 3)
    {
        status_dat = argv[1];
        obrada_dat = argv[2];
        printf("Koristenje datoteka: %s i %s\n", status_dat, obrada_dat);
    }
}

void izvadi_zadnji(char *status_dat)
{
    FILE *status;
    status = fopen(status_dat, "a+");
    if (!status)
    {
        printf("Greska pri otvaranju datoteke %s", status_dat);
        exit(1);
    }

    while (!feof(status))
    {
        if(fscanf(status, "%d", &last));
    }
    fclose(status);
}

void obradi_zapis_nula()
{
    FILE *obrada;
    int zadnji = 0;

    obrada = fopen(obrada_dat, "a+");
    if (!obrada)
    {
        printf("Greska pri otvaranju datoteke %s\n", obrada_dat);
        exit(1);
    }

    while (!feof(obrada))
    {
        if(fscanf(obrada, "%d", &zadnji));
    }
    fclose(obrada);

    last = sqrt(zadnji);
}

void stavi_nulu_na_status()
{
    FILE *status;
    status = fopen(status_dat, "w+");
    if(!status)
    {
        printf("Greska pri otvaranju datoteke %s\n", status_dat);
        exit(1);
    }
    fprintf(status, "0\n");
    fclose(status);
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

void obradi_sigusr1(int sig)
{
    printf("Prihvatio SIGTUSR1, trenutni status: ");
    printf("%d\n", last);
}

void obradi_sigterm(int sig)
{
    FILE *status;

    printf("Prihvatio SIGTERM, status %d spremljen u status.txt i program se gasi\n", last);

    status = fopen(status_dat, "w");
    if (!status)
    {
        printf("Greska pri otvaranju datoteke %s\n", status_dat);
        exit(1);
    }
    fprintf(status, "%d\n", last);
    fclose(status);
    nije_kraj = 0;
}

void obradi_sigint(int sig)
{
    printf("Prihvacen SIGINT, gasim program bez spremanja statusa\n");
    exit(1);
}
