#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elencoClienti.h"

/*elencoClienti* inizializzaElencoClienti()

Specifica sintattica: elencoClienti* inizializzaElencoClienti() -> elencoClienti*

Specifica semantica:elencoClienti* inizializzaElenco() -> nuovoElenco

Pre-condizioni: DIM_TABELLA deve essere definito e maggiore di 0

Post-condizioni: Se l'allocazione ha successo viene restituito un puntatore a nuova struttura elencoClienti, altrimentu restituisce 0  */

elencoClienti* inizializzaElencoClienti() {
    elencoClienti* elenco = (elencoClienti*)calloc(1, sizeof(elencoClienti));
    if (elenco == NULL) {
        return NULL;
    }
    for (int i = 0; i < DIM_TABELLA; i++) {
        elenco->bucket[i] = NULL;
    }
    return elenco;
}

/* void inserisciClienteElenco(elencoClienti* elenco, Cliente* cliente)

Specifica sintattica:inserisciClienteElenco(elencoClienti*, Cliente*) -> void

Specifica semantica: inserisciClienteElenco(elenco, cliente)

Pre-condizioni:
	-elenco è un puntatore valido a una struttura elencoClienti.
	-cliente è un puntatore valido a una struttura Cliente inizializzata correttamente.
	-cliente->codiceFiscale è una stringa valida, terminata da \0.
	-La funzione calcolaHash è definita e restituisce un intero compreso tra 0 e DIM_TABELLA - 1.
*/

void inserisciClienteElenco(elencoClienti* elenco, Cliente* cliente) {
    if (elenco == NULL || cliente == NULL){
        return;
    }
    unsigned int indice = calcolaHash(cliente->codiceFiscale, DIM_TABELLA);
    cliente->nodoNext = elenco->bucket[indice];
    elenco->bucket[indice] = cliente;
    printf("Cliente %s aggiunto correttamente.\n", cliente->codiceFiscale);
}

/* Cliente* cercaClienteElenco(elencoClienti* elenco, const char* codiceFiscale)

Specifica Sintattica: cercaClienteElenco(elencoClienti*, const char*) -> Cliente*

Specifica Semantica: cercaClienteElenco(elenco, codiceFiscale) -> clienteTrovato

Pre-condizioni:
	-elenco è un puntatore valido a una struttura elencoClienti inizializzata(contenente DIM_TABELLA bucket).
	-codiceFiscale è una stringa valida e terminata da '\0'.
	-La funzione calcolaHash è correttamente definita e restituisce un valore unsigned int nell’intervallo [0, DIM_TABELLA - 1].
	-Ogni bucket della tabella può contenere una lista concatenata di oggetti Cliente (tramite il campo nodoNext).

Post-condizioni:
	-Se viene trovato un cliente con codice fiscale uguale a codiceFiscale, la funzione restituisce il puntatore a quel cliente
	-se non viene trovato nessun cliente con quel codice fiscale o se elenco o codiceFiscale è NULL la funzione restituisce NULL
	-la struttura elencoClienti non viene modificata
*/

Cliente* cercaClienteElenco(elencoClienti* elenco, const char* codiceFiscale) {
    if (elenco == NULL || codiceFiscale == NULL) {
        return NULL;
    }
    unsigned int indice = calcolaHash(codiceFiscale, DIM_TABELLA);
    Cliente* corrente = elenco->bucket[indice];
    while (corrente != NULL){
        if (strcmp(corrente->codiceFiscale, codiceFiscale) == 0) {
        printf("Cliente %s trovato correttamente. \n" , codiceFiscale);
	return corrente;
        }
        corrente = corrente->nodoNext;
    }
    return NULL;
}
/*int rimuoviClienteElenco(elencoClienti* elenco, const char* codiceFiscale)

Specifica Sintattica: rimuoviClienteElenco(elencoClienti*, const char*) -> int

Specifica Semantica: rimuoviClienteElenco(elenco, codiceFiscale) -> esito

Pre-condizioni:
	-elenco è un puntatore valido a una struttura elencoClienti inizializzata
	-codiceFiscale è una stringa valida, terminata da '\0'
	-la funzione calcolaHash è correttamente definita e restituisce un valore unsigned int compresotra 0 e DIM_TABELLA - 1
	- i bucket della tabella possono contenere liste concatenate di oggetti Cliente.

Post-condizioni
	-Se un cliente con codiceFiscale corrispondente viene trovato nel bucket calcolato, viene rimosso dalla lista:
		-Se era il primo della lista, il puntatore del bucket viene aggiornato.
		-Se era in posizione successiva, viene aggiornato il collegamento del nodo precedente.
		-Il nodo del cliente viene deallocato con free.
	-La funzione restituisce 1 per indicare che la rimozione è avvenuta con successo.
	-Se il cliente non viene trovato o se uno dei parametri è NULL, la funzione restituisce 0 e non modifica la struttura elencoClienti.
*/

int rimuoviClienteElenco(elencoClienti* elenco, const char* codiceFiscale) {
    if (elenco == NULL || codiceFiscale == NULL) {
        return 0;
    }
    unsigned int indice = calcolaHash(codiceFiscale, DIM_TABELLA);
    Cliente* corrente = elenco->bucket[indice];
    Cliente* precedente = NULL;
    while (corrente != NULL) {
        if (strcmp(corrente->codiceFiscale, codiceFiscale) == 0) {
            if (precedente == NULL) {
                elenco->bucket[indice] = corrente->nodoNext;
            } else {
                precedente->nodoNext = corrente->nodoNext;
            }
            free(corrente);
	    printf(Cliente %s rimosso correttamente.\n", codiceFiscale);
            return 1;
        }
        precedente = corrente;
        corrente = corrente->nodoNext;
    }
    return 0; 
}
/*void stampaElencoClienti(elencoClienti* elenco)

Specifica Sintattica:stampaElencoClienti(elencoClienti*) -> void

Specifica Semantica: stampaElencoClienti(elenco)

Pre-condizioni:
	-elenco è un puntatore valido a una struttura elencoClienti inizializzata (contenente DIM_TABELLA bucket).
	-La funzione stampaCliente(Cliente*) è definita correttamente e stampa le informazioni di un singolo cliente su stdout.
	-Ogni bucket può contenere una lista concatenata di nodi Cliente.

Post-condizioni:
	-Vengono stampati tutti i clienti presenti nella tabella hash, uno per riga, separati da una linea orizzontale (----------------------).
	-Se elenco è NULL, la funzione non stampa nulla e termina immediatamente.
	-La struttura elencoClienti non viene modificata.
*/

void stampaElencoClienti(elencoClienti* elenco) {
    if (elenco == NULL) {
        return;
    }
    for (int i = 0; i < DIM_TABELLA; i++) {
        Cliente* corrente = elenco->bucket[i];
        while (corrente != NULL) {
            stampaCliente(corrente);
            printf("----------------------\n");
            corrente = corrente->nodoNext;
        }
    }
}
/*void liberaElencoClienti(elencoClienti* elenco)

Specifica Sintattica:liberaElencoClienti(elencoClienti*) -> void

Specifica Semantica: liberaElencoClienti(elenco)

Pre-condizioni:
	-elenco è un puntatore valido a una struttura elencoClienti inizializzata o è NULL.
	-I nodi Cliente* contenuti nei bucket sono stati allocati dinamicamente con calloc

Post-condizioni:
	-Tutti i nodi Cliente contenuti nei bucket vengono deallocati (liberati).
	-Anche la struttura elencoClienti viene deallocata.
	-Se elenco è NULL, la funzione non esegue alcuna operazione e termina immediatamente.
	-Dopo la chiamata, il puntatore originale a elenco non deve più essere utilizzato
*/

void liberaElencoClienti(elencoClienti* elenco) {
    if (elenco == NULL) {
        return;
    }
    for (int i = 0; i < DIM_TABELLA; i++) {
        Cliente* corrente = elenco->bucket[i];
        while (corrente != NULL) {
            Cliente* temp = corrente;
            corrente = corrente->nodoNext;
            free(temp);
        }
    }
    free(elenco);
}

/* unsig=ned int calcolaHash(const char* codiceFiscale)
Specifica Sintattica:calcolaHash(const char*) -> unsigned int

Specifica Semantica:calcolaHash(codiceFiscale)

Pre-condizioni:
	-codiceFiscale è una stringa valida terminata dal carattere '\0'.
	-DIM_TABELLA è una costante intera positiva che rappresenta la dimensione della tabella hash.
	-La funzione calcolaHashFunzione è definita e restituisce un valore valido all'interno del range [0, DIM_TABELLA - 1].

Post-condizioni:
	-Viene restituito un valore intero indice appartenente all’intervallo [0, DIM_TABELLA - 1], utilizzabile come indice della tabella hash.
	-La funzione non modifica né alloca memoria.
*/

unsigned int calcolaHash(const char* codiceFiscale) {
    return calcolaHashFunzione(codiceFiscale, DIM_TABELLA);
}
