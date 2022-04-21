#pragma once

extern int last, nije_kraj;
extern char *obrada_dat;
extern char *status_dat;
extern char *dat_mreza;


// last = zadnji broj u datoteci
void izvadi_zadnji(char *status_dat);

// last = korijen iz zadnjeg broja u datoteci
void obradi_zapis_nula();

// isprazni status.txt i append 0
void stavi_nulu_na_status();

// hvata zadnji broj iz dat_mreza
int dohvati_iz_cijevi();





