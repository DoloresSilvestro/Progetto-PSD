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

/*Lezione* cercaLezione(Lezione* testa, int id)

Specifica Sintattica:
  cercaLezione(Lezione*, int) -> Lezione*

Specifica Semantica:
  cercaLezione(testa, id) -> nodo

 Pre-condizioni:
 - testa è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
 - id è un valore intero valido.

 Postcondizioni:
 - Se esiste almeno un nodo nella lista con campo id uguale a id, la funzione restituisce il puntatore al primo nodo trovato.
 - Se non esiste nessun nodo con id uguale a id, la funzione restituisce NULL.
 - La lista non viene modificata dalla funzione.
 */


Lezione* cercaLezione(Lezione* testa, int id) {
        Lezione* nodoCorrente = testa;
        while (nodoCorrente != NULL) {
                if (nodoCorrente->id == id) {
                return nodoCorrente;
                }
        nodoCorrente = nodoCorrente->nodoNext;
        }
        return NULL;
}



/*void modificaLezione(Lezione* testa, int id, const char* nuovoNome, const char* nuovoGiorno, int nuovaDurata, int nuovoMaxPartecipanti)

 Specifica Sintattica:
 modificaLezione(Lezione*, int, const char*, const char*, int, int) -> void

 Specifica Semantica:
 modificaLezione(testa, id, nuovoNome, nuovoGiorno, nuovaDurata, nuovoMaxPartecipanti) -> void

 Pre-condizioni:
 - testa è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
 - id è un valore intero che rappresenta l'identificatore della lezione da modificare.
 - nuovoNome e nuovoGiorno sono stringhe valide terminate da '\0'.
 - nuovaDurata e nuovoMaxPartecipanti sono valori interi positivi e coerenti.

 Postcondizioni:
 - Se esiste un nodo nella lista con campo id uguale a id, i suoi campi vengono aggiornati con i valori passati:
 	nome viene aggiornato con nuovoNome.
 	giorno viene aggiornato con nuovoGiorno.
 	durata viene aggiornato con nuovaDurata.
 	maxPartecipanti viene aggiornato con nuovoMaxPartecipanti.
 - Se non esiste nessun nodo con id uguale a id, la funzione non modifica la lista.
 - La funzione non restituisce alcun valore (void).
 */

void modificaLezione(Lezione* testa, int id, const char* nuovoNome, const char* nuovoGiorno, int nuovaDurata, int nuovoMaxPartecipanti) {
	Lezione* modifica = cercaLezione(testa, id);
	if (modifica == NULL) {
		printf("Lezione con ID %d non trovata.\n", id);
		return;
	}

	strncpy(modifica->nome, nuovoNome, sizeof(modifica->nome));
	strncpy(modifica->giorno, nuovoGiorno, sizeof(modifica->giorno));
	modifica->durata = nuovaDurata;
	modifica->maxPartecipanti = nuovoMaxPartecipanti;

	printf("Lezione con ID %d modificata correttamente.\n", id);
}

/* Lezione* rimuoviLezione(Lezione* testa, int id)

Specifica Sintattica:
 rimuoviLezione(Lezione*, int) -> Lezione*

Specifica Semantica:
 rimuoviLezione(testa, id) -> testa

Pre-condizioni:
 - testa è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
 - id è un valore intero che rappresenta l'identificatore della lezione da rimuovere.

Post-condizioni:
 - Se esiste un nodo nella lista con campo id uguale a id, viene rimosso dalla lista e la memoria allocata per quel nodo viene liberata.
 - Se il nodo rimosso era in testa, la funzione restituisce il puntatore al nuovo nodo di testa.
 - Se il nodo rimosso era in mezzo o in fondo alla lista, la funzione collega correttamente i puntatori per mantenere la lista concatenata.
 - Se non esiste nessun nodo con id uguale a id, la lista rimane invariata.
 - La funzione restituisce il puntatore alla testa (aggiornata se necessario).
 */

Lezione* rimuoviLezione(Lezione* testa, int id) {
	Lezione* nodoCorrente = testa;
	Lezione* nodoPrecedente = NULL;

	while (nodoCorrente != NULL) {
		if (nodoCorrente->id == id) {
			if (nodoPrecedente == NULL) {
				testa = nodoCorrente->nodoNext;
			} else {
				nodoPrecedente->nodoNext = nodoCorrente->nodoNext;
			}

		free(nodoCorrente);
		printf("Lezione con ID %d rimossa con successo.\n", id);
		return testa;
		}
		nodoPrecedente = nodoCorrente;
		nodoCorrente = nodoCorrente->nodoNext;
	}

	printf("Lezione con ID %d non trovata.\n", id);
	return testa;
}

/* int lezioneCompleta(Lezione* lezione)

Specifica Sintattica:
 lezioneCompleta(Lezione*) -> int

Specifica Semantica:
 lezioneCompleta(lezione) -> risultato

Pre-condizioni:
 - lezione è un puntatore a una struttura di tipo Lezione oppure NULL.
 - Il campo maxPartecipanti deve contenere un valore intero positivo.
 - Il campo partecipantiAttuali deve contenere un valore intero maggiore o uguale a 0.

Post-condizioni:
 - Se il puntatore lezione è NULL, la funzione restituisce 1 (considera la lezione come completa).
 - Se partecipantiAttuali >= maxPartecipanti, la funzione restituisce 1.
 - Altrimenti, la funzione restituisce 0.
 - La funzione non modifica in alcun modo i dati della lezione (nessun side effect).
 */

int lezioneCompleta(Lezione* lezione) {
	if (lezione == NULL) return 1; // trattata come piena se non esiste

	return lezione->partecipantiAttuali >= lezione->maxPartecipanti;
}


/* void liberaLezioni(Lezione* testa)
Specifica Sintattica:
 liberaLezioni(Lezione*) -> void

Specifica Semantica:
 liberaLezioni(testa) → void

Pre-condizioni:
 - testa è un puntatore a una lista (anche vuota) di nodi di tipo Lezione.
 - Ogni nodo della lista è stato precedentemente allocato dinamicamente (es. con malloc/calloc).

Post-condizioni:
 - Tutti i nodi della lista vengono deallocati.
 - Non ci sono più riferimenti a memoria allocata dalla lista.
 - La funzione non restituisce alcun valore (void).
 - La funzione non modifica il valore del puntatore testa nel chiamante (passaggio per valore), ma la memoria a cui testa puntava viene liberata.
 */

void liberaLezioni(Lezione* testa) {
	Lezione* temp;
	while (testa != NULL) {
		temp = testa;
		testa = testa->nodoNext;
		free(temp);
	}
}
