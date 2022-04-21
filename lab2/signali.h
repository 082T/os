#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

extern int last, nije_kraj;
extern char *obrada_dat;
extern char *status_dat;

// napravi sigaction i stavi signale
void stavi_signale();

// ispisi trenutni status
void obradi_sigusr1(int sig);

// spremi broj u status i gasi program
void obradi_sigterm(int sig);

// ostavi 0 u status, gasi program 
void obradi_sigint(int sig);