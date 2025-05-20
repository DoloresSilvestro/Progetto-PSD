/*
 La struttura Lezione rappresenta un nodo della lista collegata delle lezioni disponibili.
 Campi:
 - nome: nome della lezione (es. "Zumba", "Yoga");
 - dataOra: data e ora della lezione (usando struct tm di <time.h>);
 - maxPartecipanti: numero massimo di persone che possono partecipare alla lezione;
 - partecipantiAttuali: numero attuale di partecipanti iscritti;
 - nodoNext: puntatore al nodo successivo nella lista.
 */

#ifndef LEZIONI_H
#define LEZIONI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Lezione {
	char nome[30];
	struct tm dataOra;
	int maxPartecipanti;
	int partecipantiAttuali;
	struct Lezione* nodoNext;
} Lezione;

Lezione* creaLezione(const char* nome, struct tm dataOra, int maxPartecipanti);
void modificaLezione(Lezione* testa, const char* nuovoNome, struct tm* nuovoDataOra, int nuovoMaxPartecipanti);
void liberaLezione(Lezione* testa);

#endif

