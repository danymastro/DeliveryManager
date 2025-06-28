#ifndef MISSIONE_H
#define MISSIONE_H

#include <stdlib.h>
#include "veicolo.h"
#include <time.h>

typedef struct Missione* Missione;

// Stati della missione
typedef enum {
    STATO_MISSIONE_IN_CORSO = 1,
    STATO_MISSIONE_COMPLETATA = 2,
    STATO_MISSIONE_FALLITA = 3
} StatoMissione;

/*
 * Crea una nuova missione
 * @param _id Identificativo della missione
 * @param _veicolo Veicolo associato alla missione
 * @return Puntatore alla missione creata, oppure NULL in caso di errore
 */
Missione missione_create(int _id, Veicolo _veicolo);

/*
 * Distrugge una missione e libera la memoria
 * @param _missione Puntatore al puntatore della missione da distruggere
 */
void missione_destroy(Missione* _missione);

/*
 * Restituisce l'ID della missione
 * @param _missione Missione da cui leggere
 * @return ID della missione, oppure -1 se _missione è NULL
 */
int missione_get_id(Missione _missione);

/*
 * Restituisce il veicolo associato alla missione
 * @param _missione Missione da cui leggere
 * @return Puntatore al veicolo, oppure NULL se _missione è NULL
 */
Veicolo missione_get_veicolo(Missione _missione);

/*
 * Restituisce lo stato della missione
 * @param _missione Missione da cui leggere
 * @return Stato della missione, oppure -1 se _missione è NULL
 */
StatoMissione missione_get_stato(Missione _missione);

/*
 * Imposta lo stato della missione
 * @param _missione Missione da modificare
 * @param _stato Nuovo stato della missione
 * @return 0 se impostato con successo, -1 altrimenti
 */
int missione_set_stato(Missione _missione, StatoMissione _stato);

/*
 * Aggiunge un carico alla missione
 * @param _missione Missione a cui aggiungere il carico
 * @param _carico Carico da aggiungere
 * @return 0 se aggiunto con successo, -1 altrimenti
 */
int missione_add_carico(Missione _missione, void* _carico);

/*
 * Rimuove un carico dalla missione
 * @param _missione Missione da cui rimuovere il carico
 * @param _carico Carico da rimuovere
 * @return 0 se rimosso con successo, -1 altrimenti
 */
int missione_remove_carico(Missione _missione, void* _carico);

/*
 * Restituisce il numero di carichi associati alla missione
 * @param _missione Missione da cui leggere
 * @return Numero di carichi, oppure -1 se _missione è NULL
 */
int missione_get_num_carichi(Missione _missione);

/*
 * Restituisce un carico dato il suo indice
 * @param _missione Missione da cui leggere
 * @param _index Indice del carico
 * @return Puntatore al carico, oppure NULL se non trovato
 */
void* missione_get_carico(Missione _missione, int _index);

/*
 * Imposta la data di inizio della missione
 * @param _missione Missione da modificare
 * @param _data_inizio Data di inizio della missione
 * @return 0 se impostata con successo, -1 altrimenti
 */
int missione_set_data_inizio(Missione _missione, time_t _data_inizio);

/*
 * Imposta la data di fine della missione
 * @param _missione Missione da modificare
 * @param _data_fine Data di fine della missione
 * @return 0 se impostata con successo, -1 altrimenti
 */
int missione_set_data_fine(Missione _missione, time_t _data_fine);

/*
 * Restituisce la data di inizio della missione
 * @param _missione Missione da cui leggere
 * @return Data di inizio della missione, oppure 0 se non impostata o _missione è NULL
 */
time_t missione_get_data_inizio(Missione _missione);

/*
 * Restituisce la data di fine della missione
 * @param _missione Missione da cui leggere
 * @return Data di fine della missione, oppure 0 se non impostata o _missione è NULL
 */
time_t missione_get_data_fine(Missione _missione);

/*
 * Calcola la durata della missione in secondi
 * @param _missione Missione da cui leggere
 * @return Durata della missione in secondi, oppure -1 se non calcolabile o _missione è NULL
 */
double missione_get_durata(Missione _missione);

/*
 * Imposta una nota testuale sulla missione
 * @param _missione Missione da modificare
 * @param _nota Nota testuale da impostare
 * @return 0 se impostata con successo, -1 altrimenti
 */
int missione_set_nota(Missione _missione, const char* _nota);

/*
 * Restituisce la nota testuale della missione
 * @param _missione Missione da cui leggere
 * @return Nota testuale, oppure NULL se non impostata o _missione è NULL
 */
const char* missione_get_nota(Missione _missione);

/*
 * Restituisce una stringa che rappresenta lo stato della missione
 * @param _stato Stato della missione
 * @return Stringa che rappresenta lo stato, oppure "Sconosciuto" se non valido
 */
const char* missione_stato_to_string(StatoMissione _stato);

#endif /* MISSIONE_H */
