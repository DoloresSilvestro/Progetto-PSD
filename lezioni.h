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

typedef struct Lezione {
	int id;
	char nome[30];
	char giorno[30];
	int durata;
	int maxPartecipanti;
	int partecipantiAttuali;
	struct Lezione* nodoNext;
} Lezione;

Lezione* aggiungiLezione(Lezione* testa, int id, const char* nome, const char* giorno, int durata, int maxPartecipanti);
Lezione* cercaLezione(Lezione* testa, int id);
void modificaLezione(Lezione* testa, int id, const char* nuovoNome, const char* nuovoGiorno, int nuovaDurata, int nuovoMaxPartecipanti);
Lezione* rimuoviLezione(Lezione* testa, int id);
void stampaLezioni(Lezione* testa);
void liberaLezioni(Lezione* testa);
int lezioneCompleta(Lezione* lezione);

#endif
