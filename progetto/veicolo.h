#ifndef VEICOLO_H
#define VEICOLO_H

#include <stdlib.h>
#include "dynamic_array.h"

typedef struct Veicolo* Veicolo;

// Stati operativi del veicolo
typedef enum {
    STATO_DISPONIBILE = 1,
    STATO_IN_VIAGGIO = 2,
    STATO_IN_MANUTENZIONE = 3
} StatoOperativoVeicolo;

/*
 * Crea un nuovo veicolo
 * @param _targa Targa del veicolo
 * @param _capacita Capacità massima del veicolo in kg
 * @return Puntatore al veicolo creato, oppure NULL in caso di errore
 */
Veicolo veicolo_create(const char* _targa, int _capacita);

/*
 * Distrugge un veicolo e libera la memoria
 * @param _veicolo Puntatore al puntatore del veicolo da distruggere
 */
void veicolo_destroy(Veicolo* _veicolo);

/*
 * Restituisce la targa del veicolo
 * @param _veicolo Veicolo da cui leggere
 * @return Targa del veicolo, oppure NULL se _veicolo è NULL
 */
const char* veicolo_get_targa(Veicolo _veicolo);

/*
 * Restituisce la capacità massima del veicolo
 * @param _veicolo Veicolo da cui leggere
 * @return Capacità massima in kg, oppure -1 se _veicolo è NULL
 */
int veicolo_get_capacita(Veicolo _veicolo);

/*
 * Restituisce lo stato operativo del veicolo
 * @param _veicolo Veicolo da cui leggere
 * @return Stato operativo del veicolo, oppure -1 se _veicolo è NULL
 */
StatoOperativoVeicolo veicolo_get_stato_operativo(Veicolo _veicolo);

/*
 * Imposta lo stato operativo del veicolo
 * @param _veicolo Veicolo da modificare
 * @param _stato Nuovo stato operativo
 * @return 0 se impostato con successo, -1 altrimenti
 */
int veicolo_set_stato_operativo(Veicolo _veicolo, StatoOperativoVeicolo _stato);

/*
 * Aggiunge un carico al veicolo
 * @param _veicolo Veicolo a cui aggiungere il carico
 * @param _carico Carico da aggiungere
 * @return 0 se aggiunto con successo, -1 altrimenti
 */
int veicolo_add_carico(Veicolo _veicolo, void* _carico);

/*
 * Rimuove un carico dal veicolo
 * @param _veicolo Veicolo da cui rimuovere il carico
 * @param _carico Carico da rimuovere
 * @return 0 se rimosso con successo, -1 altrimenti
 */
int veicolo_remove_carico(Veicolo _veicolo, void* _carico);

/*
 * Restituisce un carico dato il suo indice
 * @param _veicolo Veicolo da cui leggere
 * @param _index Indice del carico
 * @return Puntatore al carico, oppure NULL se non trovato
 */
void* veicolo_get_carico(Veicolo _veicolo, int _index);

/*
 * Restituisce il numero di carichi assegnati al veicolo
 * @param _veicolo Veicolo da cui leggere
 * @return Numero di carichi, oppure -1 se _veicolo è NULL
 */
int veicolo_get_num_carichi(Veicolo _veicolo);

/*
 * Calcola il peso totale dei carichi assegnati al veicolo
 * @param _veicolo Veicolo da cui leggere
 * @return Peso totale in kg, oppure -1 se _veicolo è NULL
 */
int veicolo_get_peso_totale_carichi(Veicolo _veicolo);

/*
 * Verifica se il veicolo può accettare un nuovo carico
 * @param _veicolo Veicolo da verificare
 * @param _peso_carico Peso del carico da aggiungere
 * @return 1 se può accettare il carico, 0 altrimenti
 */
int veicolo_puo_accettare_carico(Veicolo _veicolo, int _peso_carico);

/*
 * Restituisce una stringa che rappresenta lo stato operativo del veicolo
 * @param _stato Stato operativo del veicolo
 * @return Stringa che rappresenta lo stato, oppure "Sconosciuto" se non valido
 */
const char* veicolo_stato_to_string(StatoOperativoVeicolo _stato);

#endif /* VEICOLO_H */