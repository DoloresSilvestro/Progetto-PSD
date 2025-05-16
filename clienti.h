#ifndef CLIENTI_H
#define CLIENTI_H

#define DIM_TABELLA 97

typedef struct Cliente {
    char codiceFiscale[17];
    char nome[30];
    char cognome[30];
    struct Cliente* nodoNext;
} Cliente;

/*
La struttura Cliente rappresenta un singolo nodo della lista collegata associata a ciascuna posizione della tabella hash.
Gli elementi principali sono:
• Codice Fiscale: stringa identificativa univoca del cliente;
• nome, cognome: dati anagrafici;
• nodoNext: puntatore al nodo successivo, per la gestione delle collisioni mediante lista collegata.
*/

Cliente** inizializzaTabellaClienti();
void inserisciCliente(Cliente** tabella, const char* codiceFiscale, const char* nome, const char* cognome);
Cliente* cercaCliente(Cliente** tabella, const char* codiceFiscale);
int rimuoviCliente(Cliente** tabella, const char* codiceFiscale);
void stampaClienti(Cliente** tabella);
void liberaTabellaClienti(Cliente** tabella);
unsigned int hash(const char* codiceFiscale);

#endif

