#ifndef CENTRO_SMISTAMENTO_H
#define CENTRO_SMISTAMENTO_H

#include <stdlib.h>
#include "queue.h"
#include "weighted_directed_graph.h"

typedef struct CentroSmistamento* CentroSmistamento;

/*
 * Crea un nuovo centro di smistamento
 * @param _id Identificativo del centro di smistamento
 * @param _nome Nome del centro di smistamento
 * @param _nodo Nodo del grafo associato al centro di smistamento
 * @return Puntatore al centro di smistamento creato, oppure NULL in caso di errore
 */
CentroSmistamento centro_smistamento_create(int _id, const char* _nome, Node _nodo);

/*
 * Distrugge un centro di smistamento e libera la memoria
 * @param _centro Puntatore al puntatore del centro di smistamento da distruggere
 */
void centro_smistamento_destroy(CentroSmistamento* _centro);

/*
 * Restituisce l'ID del centro di smistamento
 * @param _centro Centro di smistamento da cui leggere
 * @return ID del centro di smistamento, oppure -1 se _centro è NULL
 */
int centro_smistamento_get_id(CentroSmistamento _centro);

/*
 * Restituisce il nome del centro di smistamento
 * @param _centro Centro di smistamento da cui leggere
 * @return Nome del centro di smistamento, oppure NULL se _centro è NULL
 */
const char* centro_smistamento_get_nome(CentroSmistamento _centro);

/*
 * Restituisce il nodo del grafo associato al centro di smistamento
 * @param _centro Centro di smistamento da cui leggere
 * @return Nodo del grafo, oppure NULL se _centro è NULL
 */
Node centro_smistamento_get_nodo(CentroSmistamento _centro);

/*
 * Aggiunge un carico alla coda del centro di smistamento
 * @param _centro Centro di smistamento a cui aggiungere il carico
 * @param _carico Carico da aggiungere
 * @param _priorita Priorità del carico
 * @return 0 se aggiunto con successo, -1 altrimenti
 */
int centro_smistamento_add_carico(CentroSmistamento _centro, void* _carico, int _priorita);

/*
 * Estrae il carico con la priorità più alta dalla coda del centro di smistamento
 * @param _centro Centro di smistamento da cui estrarre
 * @param _carico_out Puntatore dove salvare il puntatore al carico estratto
 * @return 0 se estratto con successo, -1 altrimenti
 */
int centro_smistamento_get_next_carico(CentroSmistamento _centro, void** _carico_out);

/*
 * Restituisce il numero di carichi in attesa nel centro di smistamento
 * @param _centro Centro di smistamento da cui leggere
 * @return Numero di carichi in attesa, oppure -1 se _centro è NULL
 */
int centro_smistamento_get_num_carichi(CentroSmistamento _centro);

/*
 * Verifica se ci sono carichi in attesa nel centro di smistamento
 * @param _centro Centro di smistamento da verificare
 * @return 1 se ci sono carichi in attesa, 0 altrimenti
 */
int centro_smistamento_has_carichi(CentroSmistamento _centro);

/*
 * Aggiunge un veicolo alla coda del centro di smistamento
 * @param _centro Centro di smistamento a cui aggiungere il veicolo
 * @param _veicolo Veicolo da aggiungere
 * @return 0 se aggiunto con successo, -1 altrimenti
 */
int centro_smistamento_add_veicolo(CentroSmistamento _centro, void* _veicolo);

/*
 * Estrae il prossimo veicolo dalla coda del centro di smistamento
 * @param _centro Centro di smistamento da cui estrarre
 * @param _veicolo_out Puntatore dove salvare il puntatore al veicolo estratto
 * @return 0 se estratto con successo, -1 altrimenti
 */
int centro_smistamento_get_next_veicolo(CentroSmistamento _centro, void** _veicolo_out);

/*
 * Restituisce il numero di veicoli in attesa nel centro di smistamento
 * @param _centro Centro di smistamento da cui leggere
 * @return Numero di veicoli in attesa, oppure -1 se _centro è NULL
 */
int centro_smistamento_get_num_veicoli(CentroSmistamento _centro);

/*
 * Verifica se ci sono veicoli in attesa nel centro di smistamento
 * @param _centro Centro di smistamento da verificare
 * @return 1 se ci sono veicoli in attesa, 0 altrimenti
 */
int centro_smistamento_has_veicoli(CentroSmistamento _centro);

#endif /* CENTRO_SMISTAMENTO_H */