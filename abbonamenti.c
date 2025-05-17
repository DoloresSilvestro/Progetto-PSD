#include "abbonamenti.h"

/*
Specifica Sintattica:
	aggiungiAbbonamento(Abbonamento, const char, TipoAbbonamento) -> Abbonamento

Specifica Semantica
	aggiungiAbbonamento(lista, codiceFiscale, tipo) -> nuova

Pre-condizioni:
	-lista è un puntatore a una lista (anche vuota) di nodi di tipo Abbonamento.
	-codiceFiscale è una stringa valida terminata da '\0' e non vuota.
	-tipo è un valore valido del tipo enumerativo TipoAbbonamento (MENSILE o ANNUALE).

Post-condizioni:
	-Viene creato un nuovo nodo Abbonamento con i valori passati.
	-Il campo codiceFiscale viene copiato in modo sicuro nel campo omonimo del nodo.
	-Il campo tipo viene valorizzato con il parametro passato.
	-Il campo dataInizio viene impostato alla data corrente.
	-Il campo dataFine viene calcolato aggiungendo 1 mese se tipo == MENSILE, o 1 anno se tipo == ANNUALE.
	-Il nuovo nodo viene inserito in testa alla lista (nodoNext punta alla vecchia testa).
	-La funzione restituisce il puntatore al nuovo nodo (nuova testa della lista).
	-Se l’allocazione fallisce, la lista non viene modificata e viene restituito il puntatore originale lista.
*/

Abbonamento* aggiungiAbbonamento(Abbonamento* lista, const char* codiceFiscale, TipoAbbonamento tipo) {
    Abbonamento* nuovo = (Abbonamento*)calloc(1, sizeof(Abbonamento));
    if (!nuovo) {
        printf("Errore di allocazione memoria per l'abbonamento.\n");
        return lista;
    }

    strncpy(nuovo->codiceFiscale, codiceFiscale, sizeof(nuovo->codiceFiscale) - 1);
    nuovo->codiceFiscale[sizeof(nuovo->codiceFiscale) - 1] = '\0';
    nuovo->tipo = tipo;

    time_t now = time(NULL);
    nuovo->dataInizio = *localtime(&now);
    nuovo->dataFine = nuovo->dataInizio;

    if (tipo == MENSILE) {
        nuovo->dataFine.tm_mon += 1;
    } else if (tipo == ANNUALE) {
        nuovo->dataFine.tm_year += 1;
    }
    mktime(&nuovo->dataFine);

    nuovo->nodoNext = lista;

    printf("Abbonamento aggiunto correttamente per il CF: %s\n", codiceFiscale);
    return nuovo;
}

