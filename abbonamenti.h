/*
La struttura Abbonamento rappresenta un singolo nodo della lista collegata contenente gli abbonamenti registrati nel sistema.
Gli elementi principali sono:
• codiceFiscale: stringa identificativa univoca del cliente a cui l’abbonamento è associato;
• tipo: tipo di abbonamento sottoscritto (enum TipoAbbonamento);
• dataInizio, dataFine: periodo di validità dell’abbonamento (struttura tm);
• nodoNext: puntatore al nodo successivo della lista.
*/

#ifndef ABBONAMENTI_H
#define ABBONAMENTI_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clienti.h"

typedef enum {
    MENSILE,
    ANNUALE
} TipoAbbonamento;

typedef struct Abbonamento {
    char codiceFiscale[17];
    TipoAbbonamento tipo;
    struct tm dataInizio;
    struct tm dataFine;
    struct Abbonamento* nodoNext;
} Abbonamento;

Abbonamento* aggiungiAbbonamento(Abbonamento* lista, const char* codiceFiscale, TipoAbbonamento tipo);
Abbonamento* modificaAbbonamento(Abbonamento* lista, const char* codiceFiscale, TipoAbbonamento nuovoTipo);
void stampaAbbonamenti(Abbonamento* lista);
void liberaAbbonamenti(Abbonamento* lista);
int abbonamentoValido(Abbonamento* lista, const char* codiceFiscale, struct tm oggi);

#endif
