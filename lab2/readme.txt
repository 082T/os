### NAPOMENA: ### 

$kill -SIGUSR1 /*PID*/
          iz meni nepoznatog razloga mijenja status (globalnu varijablu int last = 2,3,4...) u nasumični broj oko ~22000. Ostali signali rade kako trebaju.


### Kompajliranje i pokretanje programa ###
  make pokreni
  
### Resetiranje datoteka ###
  make obrisi

### Opis programa ###

Program je nadograda programa iz lab1 tako da:
-dretva "obrada" s id=0 izvršava zadatak iz lab1 (povećava status za 1 svakih 5 sekundi)
-dretva "obrada" s id=1 svakih 4.85 sekundi provjerava je li trenutni status djeljiv s 5, i ako je, ispisuje odgovarajuću poruku
-dretva "mreza" s id=2 dohvaća broj iz cijevi (cijev), te ako je broj>0, mjenja idući status u broj+1
-main dio programa za to vrijeme čeka unos korisnika preko scanf, te ako je unos>0, radi isto što i "mreza", a ako je unos<=0, završava program

### Primjer poziva programa ###

// terminal 1: make pokreni

cc -Wall -MMD   -c -o lab2.o lab2.c
cc -Wall -MMD   -c -o signali.o signali.c
cc -Wall -MMD   -c -o datoteke.o datoteke.c
cc -O lab2.o signali.o datoteke.o -lm -lpthread -o lab2
Program s PID = 20170 krenuo s radom
Trenutni status: 2, stavljam 4 u obrada.txt
Trenutni status: 3, stavljam 9 u obrada.txt

// terminal 1: 8

Trenutni status: 9, stavljam 81 u obrada.txt
Trenutni status: 10, stavljam 100 u obrada.txt
-Trenutni status je djeljiv s 5
Trenutni status: 11, stavljam 121 u obrada.txt

// terminal 2: echo 7 > cijev

Trenutni status: 8, stavljam 64 u obrada.txt
Trenutni status: 9, stavljam 81 u obrada.txt
Trenutni status: 10, stavljam 100 u obrada.txt
-Trenutni status je djeljiv s 5

// terminal 1: -4

Program s PID = 20170 zavrsio s radom

### kraj poziva programa ###




