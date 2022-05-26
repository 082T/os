#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

#include "datoteke.h"




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

int dohvati_iz_cijevi()
{
	FILE *fp;
	int x, y = -1;

	fp = fopen(dat_mreza, "r");
	if (!fp) {
		fprintf(stderr, "Ne mogu otvoriti cijev %s\n", dat_mreza);
		exit(1);
	}
	if (fscanf(fp, "%d", &x) > 0)
		y = x;
	fclose(fp);

	return y;
}








