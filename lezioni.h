/*
La struttura Lezione rappresenta un singolo nodo della lista collegata contenente le lezioni disponibili nel sistema.
Gli elementi principali sono:
• id: identificativo univoco della lezione;
• nome: nome della lezione;
• giorno: giorno della settimana in cui si svolge la lezione;
• durata: durata della lezione espressa in minuti;
• maxPartecipanti: numero massimo di partecipanti ammessi;
• partecipantiAttuali: numero attuale di iscritti alla lezione;
• nodoNext: puntatore al nodo successivo della lista.
*/


#ifndef LEZIONI_H define LEZIONI_H

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

Lezione* aggiungiLezione(const char* nome, struct tm dataOra, int maxPartecipanti);
void modificaLezione(Lezione* testa, const char* nuovoNome, struct tm* nuovoDataOra, int nuovoMaxPartecipanti);
void liberaLezione(Lezione* testa);

#endif
