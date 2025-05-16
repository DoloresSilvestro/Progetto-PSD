#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"

/*
Cliente** inizializzaTabellaClienti()
Specifica Sintattica:
	inizializzaTabellaClienti() -> Cliente**

Specifica Semantica:
	inizializzaTabellaClienti() -> tabella

Pre-condizioni:
1. Nessuna.

Post-condizioni:
La funzione alloca dinamicamente un array di puntatori a Cliente, inizializzati a NULL,
e restituisce un puntatore a tale array, che rappresenta una tabella hash vuota.
*/

Cliente** inizializzaTabellaClienti() {
    return (Cliente**) calloc(DIM_TABELLA, sizeof(Cliente*));
}

/*
unsigned int hash(const char* codiceFiscale)
Specifica Sintattica:
	hash(const char*) -> unsigned int

Specifica Semantica:
	hash(codiceFiscale) -> somma

Pre-condizioni:
1. codiceFiscale dev'essere una stringa valida terminata dal carattere '\0'.

Post-condizioni:
La funzione restituisce un intero non negativo compreso tra 0 e DIM_TABELLA - 1, ottenuto calcolando la
somma dei caratteri del codice fiscale e applicando l’operazione modulo DIM_TABELLA.
*/

unsigned int hash(const char* codiceFiscale) {
    unsigned int somma = 0;
    while (*codiceFiscale) {
        somma += *codiceFiscale++;
    }
    return somma % DIM_TABELLA;
}

/*
void inserisciCliente(Cliente** tabella, const char* codiceFiscale, const char* nome, const char* cognome)

Specifica Sintattica:
	inserisciCliente(Cliente**, const char*, const char*, const char*) -> void

Specifica Semantica:
	inserisciCliente(tabella, codiceFiscale, nome, cognome) -> void

Pre-condizioni:
1. La tabella hash deve essere già inizializzata correttamente.
2. Il parametro codiceFiscale deve essere una stringa terminata con '\0'.
3. Il parametro nome deve essere una stringa terminata con '\0'.
4. Il parametro cognome deve essere una stringa terminata con '\0'.

Post-condizioni:
La funzione, essendo void, non restituisce alcun valore, ma ha un side effect: alloca dinamicamente
un nuovo nodo di tipo Cliente contenente i dati forniti, che viene inserito
nella lista associata alla posizione calcolata nella tabella hash.
*/

void inserisciCliente(Cliente** tabella, const char* codiceFiscale, const char* nome, const char* cognome) {
    unsigned int indice = hash(codiceFiscale);

    Cliente* nuovoCliente = (Cliente*) calloc(1, sizeof(Cliente));
    if (!nuovoCliente) {
        fprintf(stderr, "Errore nell'allocazione della memoria per il nuovo cliente.\n");
        return;
    }

    strncpy(nuovoCliente->codiceFiscale, codiceFiscale, 16);
    strncpy(nuovoCliente->nome, nome, 29);
    strncpy(nuovoCliente->cognome, cognome, 29);
    nuovoCliente->codiceFiscale[16] = '\0';
    nuovoCliente->nome[29] = '\0';
    nuovoCliente->cognome[29] = '\0';

    nuovoCliente->nodoNext = tabella[indice];
    tabella[indice] = nuovoCliente;

    printf("Cliente %s inserito con successo!\n", codiceFiscale);
}
