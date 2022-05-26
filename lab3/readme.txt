### Kompajliranje i pokretanje programa ###
  make pokreni
  
### Resetiranje datoteka ###
  make obrisi

### Opis programa ###

Program na početku ima 3 dretve (uz main).
U main preko scanf čeka int "broj", te kad "broj">0, mijenja trenutni status na "broj".
U jednoj dretvi čeka int "broj" preko cijevi, te taj broj označava novi maksimalni broj dretvi (početni = 3).
U drugoj dretvi program provjerava je li trenutni status djeljiv s 5 te ako je, ispisuje odgovarajuću poruku.
U trećoj ("radnoj") dretvi, program povećava status za 1, te zapisuje (status^2) u obrada.txt

-napomene:

-Početni broj dretvi je 3. 
-Ukoliko je kroz cijev primljen broj veći od trenutnog (početni = 3), kreiraju se nove "radne dretve". 
-Ukoliko je kroz cijev primljen manji broj od trenutnog, brišu se samo "radne dretve". Cijev i dretva koja govori o (status % 5) se ne diraju.
-Dakle, najmanji mogući broj dretvi je 2, te tada program ništa ne radi (osim ako nije trenutni broj djeljiv s 5, tada će konstantno ispisivati da je status djeljiv s 5)

### Primjer poziva programa ###

// terminal 1: make pokreni

cc -Wall -MMD   -c -o lab3.o lab3.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab3.o signali.o datoteke.o -lm -lpthread -o lab3
Program s PID = 87552 krenuo s radom
Trenutni status: 2, stavljam 4 u obrada.txt
Trenutni status: 3, stavljam 9 u obrada.txt

// terminal 2: echo 5 > cijev 

Broj dretvi promjenjen s 3 na 5!
Trenutni status: 4, stavljam 16 u obrada.txt
Trenutni status: 5, stavljam 25 u obrada.txt
-Trenutni status je djeljiv s 5
Trenutni status: 6, stavljam 36 u obrada.txt
Trenutni status: 7, stavljam 49 u obrada.txt
Trenutni status: 8, stavljam 64 u obrada.txt

// terminal 1: 2

Trenutni status: 3, stavljam 9 u obrada.txt
Trenutni status: 4, stavljam 16 u obrada.txt
Trenutni status: 5, stavljam 25 u obrada.txt
-Trenutni status je djeljiv s 5

// terminal 2: echo 2 > cijev

Broj dretvi promjenjen s 5 na 2!
-Trenutni status je djeljiv s 5
-Trenutni status je djeljiv s 5
-Trenutni status je djeljiv s 5
-Trenutni status je djeljiv s 5

// terminal 2: echo 10 > cijev

Broj dretvi promjenjen s 2 na 10!
Trenutni status: 6, stavljam 36 u obrada.txt
Trenutni status: 7, stavljam 49 u obrada.txt
Trenutni status: 8, stavljam 64 u obrada.txt
Trenutni status: 9, stavljam 81 u obrada.txt
Trenutni status: 10, stavljam 100 u obrada.txt
-Trenutni status je djeljiv s 5
Trenutni status: 11, stavljam 121 u obrada.txt
Trenutni status: 12, stavljam 144 u obrada.txt
Trenutni status: 13, stavljam 169 u obrada.txt
Trenutni status: 14, stavljam 196 u obrada.txt
Trenutni status: 15, stavljam 225 u obrada.txt
Trenutni status: 16, stavljam 256 u obrada.txt

// terminal1: ctrl+c

^CPrihvacen SIGINT, gasim program bez spremanja statusa




