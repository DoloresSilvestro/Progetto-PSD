#include "lezioni.h"

/* Lezione* aggiungiLezione(Lezione* testa, int id, const char* nome, const char* giorno, int durata, int maxPartecipanti)

Specifica Sintattica:
aggiugiLezione(Lezione*, int, const char*,const char*, int, int) -> Lezione*

Specifica Semantica:
aggiungiLezione(testa, id, nome, giorno, durata, maxPartecipanti) -> nuova

Pre-condizioni:
  - testa è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
  - nome e giorno sono stringhe valide terminate da '\0'.
  - id, durata e maxPartecipanti sono valori  interi, positivi, validi e coerenti.

Postcondizioni:
  - Viene creato un nuovo nodo Lezione con i valori passati.
  - Il campo partecipantiAttuali è inizializzato a 0.
  - Il nuovo nodo è inserito in testa alla lista (nodoNext punta alla vecchia testa).
  - La funzione restituisce il puntatore al nuovo nodo (nuova testa della lista).
  - Se l’allocazione fallisce, la lista non viene modificata e viene restituito il puntatore originale testa.

*/

Lezione* aggiungiLezione(Lezione* testa, int id, const char* nome, const char* giorno, int durata, int maxPartecipanti) {
	Lezione* nuova = (Lezione*)calloc(1, sizeof(Lezione));
		if (!nuova) {
		printf("Errore di allocazione\n");
		return testa;
		}
	nuova->id = id;
	strncpy(nuova->nome, nome, sizeof(nuova->nome));
	strncpy(nuova->giorno, giorno, sizeof(nuova->giorno));
	nuova->durata = durata;
	nuova->maxPartecipanti = maxPartecipanti;
	nuova->partecipantiAttuali = 0;
	nuova->nodoNext = testa;
	return nuova;
}

