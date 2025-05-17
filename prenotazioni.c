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

/*
Prenotazione* modificaPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezioneVecchio,
					struct tm dataVecchia,int idLezioneNuovo, struct tm dataNuova,
					Abbonamento* listaAbbonamenti, Lezione* listaLezioni, int maxPrenotazioni)
Specifica Sintattica:
    modificaPrenotazione(Prenotazione*, const char*, int, struct tm, int, struct tm,
                        Abbonamento*, Lezione*, int) -> Prenotazione*

Specifica Semantica:
    modificaPrenotazione(lista, codiceFiscale, idLezioneVecchio,
			dataVecchia, idLezioneNuovo, dataNuova,
			listaAbbonamenti, listaLezioni, maxPrenotazioni) -> esito

Pre-condizioni:
1. La lista delle prenotazioni (lista) può essere vuota o valida.
2. codiceFiscale è una stringa valida e terminata da '\0'.
3. Le strutture dataVecchia e dataNuova sono correttamente inizializzate.
4. La lista degli abbonamenti e delle lezioni devono essere valide (o vuote).
5. Le funzioni cercaLezione, abbonamentoValido e contaPrenotazioni devono essere implementate correttamente.
6. maxPrenotazioni è un intero positivo.

Post-condizioni:
La funzione stampa a video un messaggio che indica un esito:
1. Se la prenotazione esiste e tutte le condizioni sono rispettate (lezione nuova trovata, abbonamento valido,
   limiti di prenotazioni non superati), la funzione aggiorna la prenotazione corrispondente a codiceFiscale,
   idLezioneVecchio e dataVecchia con idLezioneNuovo e dataNuova, restituendo la lista modifica.

2. Se la prenotazione non è trovata o una delle condizioni fallisce, la funzione restituisce la lista invariata.
*/

Prenotazione* modificaPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezioneVecchio, struct tm dataVecchia,
                                   int idLezioneNuovo, struct tm dataNuova, Abbonamento* listaAbbonamenti,
					Lezione* listaLezioni, int maxPrenotazioni) {
    Prenotazione* nodoCorrente = lista;
    while (nodoCorrente != NULL) {
        if (strcmp(nodoCorrente->codiceFiscale, codiceFiscale) == 0 &&
            nodoCorrente->idLezione == idLezioneVecchio &&
            nodoCorrente->data.tm_mday == dataVecchia.tm_mday &&
            nodoCorrente->data.tm_mon == dataVecchia.tm_mon &&
            nodoCorrente->data.tm_year == dataVecchia.tm_year) {

            if (!cercaLezione(listaLezioni, idLezioneNuovo)) {
                printf("Nuova lezione non trovata.\n");
                return lista;
            }

            if (!abbonamentoValido(codiceFiscale, dataNuova, listaAbbonamenti)) {
                printf("Abbonamento non valido nella nuova data.\n");
                return lista;
            }

            if (contaPrenotazioni(lista, idLezioneNuovo) >= maxPrenotazioni) {
                printf("Limite raggiunto per la nuova lezione.\n");
                return lista;
            }

            nodoCorrente->idLezione = idLezioneNuovo;
            nodoCorrente->data = dataNuova;

            printf("Prenotazione modificata correttamente.\n");
            return lista;
        }
        nodoCorrente = nodoCorrente->nodoNext;
    }

    printf("Prenotazione da modificare non trovata.\n");
    return lista;
}

/*
Prenotazione* rimuoviPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezione, struct tm data)

Specifica Sintattica:
    rimuoviPrenotazione(Prenotazione*, const char*, int, struct tm) -> Prenotazione*

Specifica Semantica:
    rimuoviPrenotazione(lista, codiceFiscale, idLezione, data) -> listaModificata

Pre-condizioni:
1. La lista delle prenotazioni (lista) può essere vuota o valida.
2. codiceFiscale è una stringa valida e terminata da '\0'.
3. La struttura data dev'essere correttamente inizializzata.

Post-condizioni:
Le funzione stampa a schermo l'esito finale, che:
1. Se la prenotazione che corrisponde a codiceFiscale, idLezione e data esiste, la funzione la rimuoverà dalla lista
   , liberando la memoria del nodo eliminato e restituiendo la lista modificata.

2. Se la prenotazione non viene trovata, la funzione lascerà invariata la lista.
*/

Prenotazione* rimuoviPrenotazione(Prenotazione* lista, const char* codiceFiscale, int idLezione, struct tm data) {
    Prenotazione* nodoCorrente = lista;
    Prenotazione* nodoPrecedente = NULL;

    while (nodoCorrente != NULL) {
        if (strcmp(nodoCorrente->codiceFiscale, codiceFiscale) == 0 &&
            nodoCorrente->idLezione == idLezione &&
            nodoCorrente->data.tm_mday == data.tm_mday &&
            nodoCorrente->data.tm_mon == data.tm_mon &&
            nodoCorrente->data.tm_year == data.tm_year) {

            if (nodoPrecedente == NULL) {
                lista = nodoCorrente->nodoNext;
            } else {
                nodoPrecedente->nodoNext = nodoCorrente->nodoNext;
            }

            free(nodoCorrente);
            printf("Prenotazione rimossa correttamente.\n");
            return lista;
        }

        nodoPrecedente = nodoCorrente;
        nodoCorrente = nodoCorrente->nodoNext;
    }

    printf("Prenotazione non trovata.\n");
    return lista;
}

/*
void stampaPrenotazioni(Prenotazione* lista)
Specifica Sintattica:
    stampaPrenotazioni(Prenotazione*) -> void

Specifica Semantica:
    stampaPrenotazioni(lista) -> void

Pre-condizioni:
1. La lista delle prenotazioni (lista) può essere vuota o valida.

Post-condizioni:
La funzione stampa a schermo tutte le prenotazioni presenti nella lista, includendo codice fiscale,
id della lezione e data formattata.
*/

void stampaPrenotazioni(Prenotazione* lista) {
    while (lista != NULL) {
        printf("CF: %s | Lezione ID: %d | Data: %02d/%02d/%04d\n",
               lista->codiceFiscale, lista->idLezione,
               lista->data.tm_mday, lista->data.tm_mon + 1, lista->data.tm_year + 1900);
        lista = lista->nodoNext;
    }
}

/*
void liberaPrenotazioni(Prenotazione* lista)
Specifica Sintattica:
    liberaPrenotazioni(Prenotazione*) -> void

Specifica Semantica:
    liberaPrenotazioni(lista) -> void

Pre-condizioni:
1. La lista delle prenotazioni (lista) può essere vuota o valida.

Post-condizioni:
La funzione libera la memoria di tutti i nodi della lista di prenotazioni.
*/

void liberaPrenotazioni(Prenotazione* lista) {
    Prenotazione* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->nodoNext;
        free(temp);
    }
}
