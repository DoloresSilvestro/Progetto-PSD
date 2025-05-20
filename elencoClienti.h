/*
La struttura elencoClienti implementa una tabella hash per la gestione efficiente di clienti registrati nel sistema.
Gli elementi principali sono:
	-bucket: array di puntatori a Cliente, con dimensione DIM_TABELLA (97), usato come tabella hash;
	-ogni bucket contiene la lista dei clienti con codice fiscale il cui hash cade in quella posizione;
	-le funzioni permettono di inizializzare la tabella, inserire, cercare e rimuovere clienti tramite il codice fiscale, stampare l’elenco e liberare la memoria occupata;
	-la funzione calcolaHash genera un indice valido per la tabella a partire dal codice fiscale del cliente.
*/

#ifndef ELENCOCLIENTI_H
#define ELENCOCLIENTI_H

#include "cliente.h"

#define DIM_TABELLA 97

typedef struct {
    Cliente* bucket[DIM_TABELLA];
} elencoClienti;

elencoClienti* inizializzaElencoClienti();
void inserisciClienteElenco(elencoClienti* elenco, Cliente* cliente);
Cliente* cercaClienteElenco(elencoClienti* elenco, const char* codiceFiscale);
int rimuoviClienteElenco(elencoClienti* elenco, const char* codiceFiscale);
void stampaElencoClienti(elencoClienti* elenco);
void liberaElencoClienti(elencoClienti* elenco);
unsigned int calcolaHash(const char* codiceFiscale);

#endif


