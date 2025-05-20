#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct Cliente {
    char codiceFiscale[17];
    char nome[30];
    char cognome[30];
    struct Cliente* nodoNext;
} Cliente;

Cliente* creaCliente(const char* codiceFiscale, const char* nome, const char* cognome);
void modificaCliente(Cliente* cliente, const char* nuovoNome, const char* nuovoCognome);
void stampaCliente(Cliente* cliente);
void liberaCliente(Cliente* cliente;

#endif
