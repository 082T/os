#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "signali.h"



void stavi_signale()
{
    struct sigaction act;
    
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
}

void obradi_sigusr1(int sig)
{
    printf("Prihvatio SIGTUSR1, trenutni status: ");
    printf("%d\n", last);
}

void obradi_sigterm(int sig)
{
    FILE *status;
    FILE *fp;
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
    fp=fopen(dat_mreza,"w+");
    fprintf(fp,"%d",0);
    fclose(fp);
}

void obradi_sigint(int sig)
{
    printf("Prihvacen SIGINT, gasim program bez spremanja statusa\n");
    exit(0);
}










