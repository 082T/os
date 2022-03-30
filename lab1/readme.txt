prevođenje:
- ručno: gcc lab1.c -o lab1 -lm
- makefile: make

pokretanje: 
- ručno: ./lab1 status.txt obrada.txt
- preko makefile: make pokreni

brisanje:
- preko makefile: make obrisi


Primjer ispisa:

//TERMINAL 1: make pokreni

cc lab1.c -Wall -O -lm -o lab1
Koristenje datoteka: status.txt i obrada.txt
Program s PID = 127 krenuo s radom
Trenutni status: 2, stavljam 4 u obrada.txt
Trenutni status: 3, stavljam 9 u obrada.txt
Trenutni status: 4, stavljam 16 u obrada.txt
Trenutni status: 5, stavljam 25 u obrada.txt      //TERMINAL 2: kill -SIGUSR1 127
Prihvatio SIGTUSR1, trenutni status: 5
Trenutni status: 6, stavljam 36 u obrada.txt
Trenutni status: 7, stavljam 49 u obrada.txt      //TERMINAL 2: kill -SIGINT 127
Prihvacen SIGINT, gasim program bez spremanja statusa

//TERMINAL 1: make pokreni

Koristenje datoteka: status.txt i obrada.txt
Program s PID = 131 krenuo s radom
Trenutni status: 8, stavljam 64 u obrada.txt
Trenutni status: 9, stavljam 81 u obrada.txt      //TERMINAL 2: kill -SIGTERM 131
Prihvatio SIGTERM, status 9 spremljen u status.txt i program se gasi
Program s PID = 131 zavrsio s radom
