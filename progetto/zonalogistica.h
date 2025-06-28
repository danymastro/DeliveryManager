#ifndef ZONA_LOGISTICA_H
#define ZONA_LOGISTICA_H

#include <stdlib.h>
#include <string.h>
#include "weighted_directed_graph.h"
#include "dynamic_array.h"

typedef struct ZonaLogistica* ZonaLogistica;

/*
 * Crea una nuova zona logistica
 * @param _id Identificativo della zona logistica
 * @param _nome Nome della zona logistica
 * @return Puntatore alla zona logistica creata, oppure NULL in caso di errore
 */
ZonaLogistica zona_logistica_create(int _id, const char* _nome);

/*
 * Distrugge una zona logistica e libera la memoria
 * @param _zona Puntatore al puntatore della zona logistica da distruggere
 */
void zona_logistica_destroy(ZonaLogistica* _zona);

/*
 * Restituisce l'ID della zona logistica
 * @param _zona Zona logistica da cui leggere
 * @return ID della zona logistica, oppure -1 se _zona è NULL
 */
int zona_logistica_get_id(ZonaLogistica _zona);

/*
 * Restituisce il nome della zona logistica
 * @param _zona Zona logistica da cui leggere
 * @return Nome della zona logistica, oppure NULL se _zona è NULL
 */
char* zona_logistica_get_nome(ZonaLogistica _zona);

/*
 * Aggiunge un punto di consegna alla zona logistica
 * @param _zona Zona logistica in cui aggiungere
 * @param _punto Punto di consegna da aggiungere
 * @return 0 se aggiunto con successo, -1 altrimenti
 */
int zona_logistica_add_punto_consegna(ZonaLogistica _zona, void* _punto);

/*
 * Restituisce un punto di consegna dato il suo indice
 * @param _zona Zona logistica da cui leggere
 * @param _index Indice del punto di consegna
 * @return Puntatore al punto di consegna, oppure NULL se non trovato
 */
void* zona_logistica_get_punto_consegna(ZonaLogistica _zona, int _index);

/*
 * Restituisce un punto di consegna dato il suo ID
 * @param _zona Zona logistica da cui leggere
 * @param _id ID del punto di consegna
 * @return Puntatore al punto di consegna, oppure NULL se non trovato
 */
void* zona_logistica_find_punto_consegna_by_id(ZonaLogistica _zona, int _id);

/*
 * Restituisce un punto di consegna dato il suo nome
 * @param _zona Zona logistica da cui leggere
 * @param _nome Nome del punto di consegna
 * @return Puntatore al punto di consegna, oppure NULL se non trovato
 */
void* zona_logistica_find_punto_consegna_by_nome(ZonaLogistica _zona, const char* _nome);

/*
 * Restituisce il numero di punti di consegna nella zona logistica
 * @param _zona Zona logistica da cui leggere
 * @return Numero di punti di consegna, oppure -1 se _zona è NULL
 */
int zona_logistica_get_num_punti_consegna(ZonaLogistica _zona);

#endif /* ZONA_LOGISTICA_H */
