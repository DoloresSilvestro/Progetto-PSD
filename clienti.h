#ifndef CLIENTI_H
#define CLIENTI_H

#define DIM_TABELLA 97

typedef struct Cliente {
    char codiceFiscale[17];
    char nome[30];
    char cognome[30];
    struct Cliente* nodoNext;
} Cliente;

Cliente** inizializzaTabellaClienti();
void inserisciCliente(Cliente** tabella, const char* codiceFiscale, const char* nome, const char* cognome);
Cliente* cercaCliente(Cliente** tabella, const char* codiceFiscale);
int rimuoviCliente(Cliente** tabella, const char* codiceFiscale);
void stampaClienti(Cliente** tabella);
void liberaTabellaClienti(Cliente** tabella);

unsigned int hash(const char* codiceFiscale);

#endif

