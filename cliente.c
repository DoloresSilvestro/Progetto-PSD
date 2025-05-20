#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"
/*
Cliente* creaCliente(const char* codiceFiscale, const char* nome, const char* cognome) 

Specifica Sintattica:
creaCliente(const char*, const char*, const char*) -> Cliente*

Specifica Semantica:
creaCliente(codiceFiscale, nome, cognome) -> clienteCreato
Pre-condizioni:
Le stringhe codiceFiscale, nome e cognome devono essere terminate da '\0'.
I parametri devono essere stringhe valide (non NULL).

Post-condizioni:
La funzione restituisce un puntatore a un nuovo oggetto Cliente allocato dinamicamente,
inizializzando il campo nodoNext a NULL e copiando nei rispettivi campi i valori di codiceFiscale, nome e cognome
con il terminatore di stringa; in caso di fallimento dell’allocazione, stampa un messaggio d’errore e restituisce NULL.
*/
Cliente* creaCliente(const char* codiceFiscale, const char* nome, const char* cognome) {
    	Cliente* nuovo = (Cliente*) malloc(sizeof(Cliente));
    	if (nuovo == NULL) {
        	fprintf(stderr, "Errore allocazione memoria per nuovo cliente\n");
        	return NULL;
    	}

    	strncpy(nuovo->codiceFiscale, codiceFiscale, 16);
    	nuovo->codiceFiscale[16] = '\0';
	strncpy(nuovo->nome, nome, 29);
    	nuovo->nome[29] = '\0';
    	strncpy(nuovo->cognome, cognome, 29);
    	nuovo->cognome[29] = '\0';
    	nuovo->nodoNext = NULL;

	printf("Il cliente %s è stato aggiunto correttamente!\n", codiceFiscale);
    	return nuovo;
}
/*
void modificaCliente(Cliente* cliente, const char* nome, const char* cognome)

Specifica Sintattica:
modificaCliente(Cliente*, const char*, const char*) -> void

Specifica Semantica:
modificaCliente(cliente, nome, cognome) -> void

Pre-condizioni:
Il puntatore cliente deve essere valido.
I parametri nome e cognome devono essere stringhe valide terminate da '\0'.

Post-condizioni:
La funzione, essendo void, non restituisce nessun valore, ma la struttura viene modificata tramite side effect:
I campi nome e cognome della struttura Cliente vengono sovrascritti con i nuovi valori forniti.
*/
void modificaCliente(Cliente* cliente, const char* nome, const char* cognome) {
	if (cliente == NULL)
	return;

    	strncpy(cliente->nome, nome, 29);
   	cliente->nome[29] = '\0';
    	strncpy(cliente->cognome, cognome, 29);
    	cliente->cognome[29] = '\0';

	printf("Il cliente %s è stato modificato con successo!", codiceFiscale);
}
/*
void liberaCliente(Cliente* cliente)

Specifica Sintattica:
liberaCliente(Cliente*) -> void

Specifica Semantica:
liberaCliente(cliente) -> void

Pre-condizioni:
Il parametro cliente può essere NULL oppure puntare al primo nodo di una lista concatenata dinamicamente allocata.

Post-condizioni:
La funzione (void) non restituisce alcun valore, ma la struttura viene alterata da un side effect:
tutti i nodi della lista concatenata a partire da cliente vengono deallocati e la memoria associata
a ciascun nodo viene liberata.
*/
void liberaCliente(Cliente* cliente) {
    	while (cliente != NULL) {
        	Cliente* temp = cliente;
        	cliente = cliente->nodoNext;
        	free(temp);
	}
}
