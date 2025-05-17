#ifndef PRENOTAZIONI_H
#define PRENOTAZIONI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "clienti.h"
#include "lezioni.h"
#include "abbonamenti.h"

typedef struct Prenotazione {
    char codiceFiscale[17];
    int idLezione;
    struct tm data;
    struct Prenotazione* nodoNext;
} Prenotazione;

/*
La struttura Prenotazione rappresenta un singolo nodo della lista collegata utilizzata per gestire le prenotazioni effettuate dai clienti.
Gli elementi principali sono:
• codiceFiscale: stringa identificativa del cliente che ha effettuato la prenotazione, collegata alla struttura Cliente;
• idLezione: identificativo numerico della lezione prenotata, collegato alla struttura Lezione;
• data: struttura `tm` che rappresenta la data della prenotazione;
• nodoNext: puntatore al nodo successivo, per consentire la gestione dinamica di più prenotazioni mediante lista collegata.
*/

Prenotazione* aggiungiPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezione, struct tm data,
                                    Abbonamento* listaAbbonamenti, Lezione* listaLezioni, int maxPrenotazioni);

Prenotazione* modificaPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezioneVecchio, struct tm dataVecchia,
                                   int idLezioneNuovo, struct tm dataNuova, Abbonamento* listaAbbonamenti, Lezione* listaLezioni, int maxPrenotazioni);

Prenotazione* rimuoviPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezione, struct tm data);

void stampaPrenotazioni(Prenotazione* lista);

void liberaPrenotazioni(Prenotazione* lista);

#endif