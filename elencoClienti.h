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

#endif
