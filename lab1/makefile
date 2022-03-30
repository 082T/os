CFLAGS = -Wall
LDFLAGS = -O
LDLIBS = -lm

PROGRAM = lab1
KOD = lab1.c

STATUS = status.txt
OBRADA = obrada.txt

$(PROGRAM): $(KOD)
	$(CC) $(KOD) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(PROGRAM)

.PHONY: init pokreni obrisi
init:
	@-if [ ! -e $(STATUS) ]; then echo 1 >> $(STATUS); fi;
	@-if [ ! -e $(OBRADA) ]; then echo 1 >> $(OBRADA); fi;

pokreni: $(PROGRAM) init
	@./$(PROGRAM) $(STATUS) $(OBRADA)

obrisi:
	-rm -rf $(PROGRAM) $(STATUS) $(OBRADA)