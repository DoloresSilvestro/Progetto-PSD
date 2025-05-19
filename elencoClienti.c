#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elencoClienti.h"

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

void inserisciClienteElenco(elencoClienti* elenco, Cliente* cliente) {
    if (elenco == NULL || cliente == NULL) {
        return;
    }
    unsigned int indice = calcolaHash(cliente->codiceFiscale, DIM_TABELLA);
    cliente->nodoNext = elenco->bucket[indice];
    elenco->bucket[indice] = cliente;
}

Cliente* cercaClienteElenco(elencoClienti* elenco, const char* codiceFiscale) {
    if (elenco == NULL || codiceFiscale == NULL) {
        return NULL;
    }
    unsigned int indice = calcolaHash(codiceFiscale, DIM_TABELLA);
    Cliente* corrente = elenco->bucket[indice];
    while (corrente != NULL) {
        if (strcmp(corrente->codiceFiscale, codiceFiscale) == 0) {
            return corrente;
        }
        corrente = corrente->nodoNext;
    }
    return NULL;
}

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
            return 1;
        }
        precedente = corrente;
        corrente = corrente->nodoNext;
    }
    return 0;
}

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

unsigned int calcolaHash(const char* codiceFiscale) {
    return calcolaHashFunzione(codiceFiscale, DIM_TABELLA);
}
