.PHONY: all, clean
# Disable implicit rules
.SUFFIXES:

CC = gcc
CFLAGS = -Wall -Werror -g
INCLUDE = grille.h regle.h
OBJS = grille.o regle.o

PROGS = jeu

all: $(PROGS)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INCLDIR) -c -o $@ $<

%: %.o $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^ $(LIBS)

clean:
	rm -f $(PROGS) *.o
