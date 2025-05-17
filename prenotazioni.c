#include "prenotazioni.h"

/*
int contaPrenotazioni(Prenotazione* lista, int idLezione)
Specifica Sintattica:
	contaPrenotazioni(Prenotazione*, int) -> int

Specifica Semantica:
	contaPrenotazioni(lista, idLezione) -> conta

Pre-condizioni:
1. La lista delle prenotazioni (lista) deve essere correttamente inizializzata (può anche essere NULL).
2. idLezione dev'essere un valore intero positivo valido.

Post-condizioni:
La funzione restituisce un intero che rappresenta il numero di nodi
della lista in cui idLezione corrisponde all'ID della lezione indicata.
*/

int contaPrenotazioni(Prenotazione* lista, int idLezione) {
    int conta = 0;
    while (lista != NULL) {
        if (lista->idLezione == idLezione) {
            conta++;
        }
        lista = lista->nodoNext;
    }
    return conta;
}

/*
int abbonamentoValido(const char* codiceFiscale, struct tm data, Abbonamento* listaAbbonamenti)
Specifica Sintattica:
	abbonamentoValido(const char*, struct tm, Abbonamento*) -> int

Specifica Semantica:
	abbonamentoValido(codiceFiscale, data, listaAbbonamenti) -> esito

Pre-condizioni:
1. La lista listaAbbonamenti deve essere inizializzata correttamente (può essere anche vuota).
2. Il parametro codiceFiscale deve essere una stringa valida e terminata da '\0'.
3. Il campo data deve contenere una data valida.

Post-condizioni:
La funzione restituisce 1 se trova un abbonamento valido per il cliente nella data indicata, altrimenti 0.
*/

int abbonamentoValido(const char* codiceFiscale, struct tm data, Abbonamento* listaAbbonamenti) {
    while (listaAbbonamenti != NULL) {
        if (strcmp(listaAbbonamenti->codiceFiscale, codiceFiscale) == 0) {
            time_t dataPrenotazione = mktime(&data);
            time_t inizio = mktime(&listaAbbonamenti->dataInizio);
            time_t fine = mktime(&listaAbbonamenti->dataFine);

            return (difftime(dataPrenotazione, inizio) >= 0 && difftime(fine, dataPrenotazione) >= 0);
        }
        listaAbbonamenti = listaAbbonamenti->nodoNext;
    }
    return 0;
}

/*
Prenotazione* aggiungiPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezione, struct tm data,
                                   Abbonamento* listaAbbonamenti, Lezione* listaLezioni, int maxPrenotazioni)
Specifica Sintattica:
	aggiungiPrenotazione(Prenotazione*, const char*, int, struct tm,
				Abbonamento*, Lezione*, int) -> Prenotazione*

Specifica Semantica:
	aggiungiPrenotazione(lista, codiceFiscale, idLezione, data,
				listaAbbonamenti, listaLezioni, maxPrenotazioni) -> esito

Pre-condizioni:
1. La lista delle prenotazioni (lista) può essere anche vuota.
2. codiceFiscale è una stringa valida e terminata da '\0'.
3. La struttura data è correttamente inizializzata.
4. La lista degli abbonamenti e delle lezioni deve essere valida (eventualmente anche vuota).
5. La funzione cercaLezione, abbonamentoValido e contaPrenotazioni devono essere implementate correttamente.

Post-condizioni:
La funzione restituisce un messaggio che notifica l'esito dell'operazione. Se tutte le condizioni sono rispettate,
viene allocata dinamicamente una nuova prenotazione, inserita in testa alla lista,
e la funzione restituisce il nuovo puntatore alla testa. Altrimenti, se una qualsiasi condizione fallisce
(lezione non trovata, abbonamento non valido, numero massimo superato, errore di allocazione), la lista rimane invariata.
*/

Prenotazione* aggiungiPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezione, struct tm data,
                                   Abbonamento* listaAbbonamenti, Lezione* listaLezioni, int maxPrenotazioni) {
    if (!cercaLezione(listaLezioni, idLezione)) {
        printf("Lezione con ID %d non trovata.\n", idLezione);
        return lista;
    }

    if (!abbonamentoValido(codiceFiscale, data, listaAbbonamenti)) {
        printf("Abbonamento non valido per il CF: %s nella data specificata.\n", codiceFiscale);
        return lista;
    }

    if (contaPrenotazioni(lista, idLezione) >= maxPrenotazioni) {
        printf("Numero massimo di prenotazioni raggiunto per la lezione con ID %d.\n", idLezione);
        return lista;
    }

    Prenotazione* nuova = (Prenotazione*)calloc(1, sizeof(Prenotazione));
    if (!nuova) {
        printf("Errore di allocazione memoria per la prenotazione.\n");
        return lista;
    }

    strncpy(nuova->codiceFiscale, codiceFiscale, 16);
    nuova->codiceFiscale[16] = '\0';
    nuova->idLezione = idLezione;
    nuova->data = data;
    nuova->nodoNext = lista;

    printf("Prenotazione aggiunta per CF %s alla lezione %d.\n", codiceFiscale, idLezione);
    return nuova;
}
