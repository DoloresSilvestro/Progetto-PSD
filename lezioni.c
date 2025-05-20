#include "lezioni.h"

/* Lezione* aggiungiLezione(Lezione* testa, int id, const char* nome, const char* giorno, int durata, int maxPartecipanti)

Specifica Sintattica:
aggiugiLezione(Lezione*, const char*,const char*, int, int) -> Lezione*

Specifica Semantica:
aggiungiLezione(testa, nome, giorno, durata, maxPartecipanti) -> nuova

Pre-condizioni:
  - testa è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
  - nome e giorno sono stringhe valide terminate da '\0'.
  - durata e maxPartecipanti sono valori  interi, positivi, validi e coerenti.

Postcondizioni:
  - Viene creato un nuovo nodo Lezione con i valori passati.
  - Il campo partecipantiAttuali è inizializzato a 0.
  - Il nuovo nodo è inserito in testa alla lista (nodoNext punta alla vecchia testa).
  - La funzione restituisce il puntatore al nuovo nodo (nuova testa della lista).
  - Se l’allocazione fallisce, la lista non viene modificata e viene restituito il puntatore originale testa.

*/

Lezione* creaLezione(const char* nome, struct tm dataOra, int maxPartecipanti) {
	if (nome==NULL || maxPartecipanti <=0){
		return NULL;
	}

	Lezione* nuova = (Lezione*)calloc(1, sizeof(Lezione));
		if (!nuova) {
		printf("Errore di allocazione\n");
		return NULL;
		}

	strncpy(nuova->nome, nome, sizeof(nuova->nome) - 1);
    	nuova->nome[sizeof(nuova->nome) - 1] = '\0';

	nuova->dataOra = dataOra;
	nuova->maxPartecipanti = maxPartecipanti;
	nuova->partecipantiAttuali = 0;
	nuova->nodoNext = NULL;
	return nuova;
}

/*void modificaLezione(Lezione* nodo, const char* nuovoNome, struct tm* nuovoDataOra, int nuovoMaxPartecipanti)

 Specifica Sintattica:
 modificaLezione(Lezione*, const char*, struct tm*, int) -> void

 Specifica Semantica:
 modificaLezione(nodo, nuovoNome, nuovoDataOra, nuovoMaxPartecipanti) -> void

 Pre-condizioni:
 - nodo è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
 - nuovoNome è una stringhe valida terminata da '\0'.
 - nuovaDurata e nuovoMaxPartecipanti sono valori interi positivi e coerenti.

 Postcondizioni:
 - La funzione non restituisce alcun valore (void).
 */

void modificaLezione(Lezione* nodo, const char* nuovoNome, struct tm* nuovoDataOra, int nuovoMaxPartecipanti) {
	if (nodo == NULL || nuovoNome == NULL || nuovoDataOra == NULL || nuovoMaxPartecipanti <=0){
		printf(stderr, " Modifica Lezione impossibile");
		return;
	}

	strncpy(modifica->nome, nuovoNome, sizeof(modifica->nome) - 1);
    	nodo->nome[sizeof(modifica->nome) - 1] = '\0';
	nodo->dataOra = *nuovoDataOra;
	nodo->maxPartecipanti = nuovoMaxPartecipanti;

	printf("Lezione modificata correttamente.\n", dataOra);
}

/* void liberaLezioni(Lezione* nodo)
Specifica Sintattica:
 liberaLezioni(Lezione*) -> void

Specifica Semantica:
 liberaLezioni(nodo) → void

Pre-condizioni:
 - nodo è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
 - Ogni nodo della lista è stato precedentemente allocato dinamicamente

Post-condizioni:
 - Tutti i nodi della lista vengono deallocati.
 - Non ci sono più riferimenti a memoria allocata dalla lista.
 - La funzione non restituisce alcun valore (void).
 - La funzione non modifica il valore del puntatore testa nel chiamante (passaggio per valore), ma la memoria a cui nodo puntava viene liberata.
 */

void liberaLezioni(Lezione* nodo) {
	Lezione* temp;
	while (testa != NULL) {
		temp = nodo;
		nodo = nodo->nodoNext;
		free(temp);
	}
}
