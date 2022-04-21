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

### Primjer poziva ###

