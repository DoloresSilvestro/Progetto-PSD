#ifndef LEZIONI_H
#define LEZIONI_H

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
