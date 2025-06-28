#ifndef PUNTO_CONSEGNA_H
#define PUNTO_CONSEGNA_H

#include <stdlib.h>
#include "weighted_directed_graph.h"

typedef struct PuntoConsegna* PuntoConsegna;

// Tipi di punto di consegna
typedef enum {
    TIPO_STANDARD = 1,
    TIPO_REFRIGERATO = 2,
    TIPO_FRAGILE = 3
} TipoPuntoConsegna;

/*
 * Crea un nuovo punto di consegna
 * @param _id Identificativo del punto di consegna
 * @param _nome Nome del punto di consegna
 * @param _priorita Priorità del punto di consegna (1-5)
 * @param _orario Orario di consegna (formato HHMM)
 * @param _tipo Tipo del punto di consegna
 * @param _nodo Nodo del grafo associato al punto di consegna
 * @param _zona_logistica Zona logistica a cui appartiene il punto di consegna
 * @return Puntatore al punto di consegna creato, oppure NULL in caso di errore
 */
PuntoConsegna punto_consegna_create(int _id, const char* _nome, int _priorita, 
                                   int _orario, TipoPuntoConsegna _tipo, 
                                   Node _nodo, void* _zona_logistica);

/*
 * Distrugge un punto di consegna e libera la memoria
 * @param _punto Puntatore al puntatore del punto di consegna da distruggere
 */
void punto_consegna_destroy(PuntoConsegna* _punto);

/*
 * Restituisce l'ID del punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return ID del punto di consegna, oppure -1 se _punto è NULL
 */
int punto_consegna_get_id(PuntoConsegna _punto);

/*
 * Restituisce il nome del punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return Nome del punto di consegna, oppure NULL se _punto è NULL
 */
const char* punto_consegna_get_nome(PuntoConsegna _punto);

/*
 * Restituisce la priorità del punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return Priorità del punto di consegna (1-5), oppure -1 se _punto è NULL
 */
int punto_consegna_get_priorita(PuntoConsegna _punto);

/*
 * Restituisce l'orario di consegna del punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return Orario di consegna (formato HHMM), oppure -1 se _punto è NULL
 */
int punto_consegna_get_orario(PuntoConsegna _punto);

/*
 * Restituisce il tipo del punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return Tipo del punto di consegna, oppure -1 se _punto è NULL
 */
TipoPuntoConsegna punto_consegna_get_tipo(PuntoConsegna _punto);

/*
 * Restituisce il nodo del grafo associato al punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return Nodo del grafo, oppure NULL se _punto è NULL
 */
Node punto_consegna_get_nodo(PuntoConsegna _punto);

/*
 * Restituisce la zona logistica a cui appartiene il punto di consegna
 * @param _punto Punto di consegna da cui leggere
 * @return Puntatore alla zona logistica, oppure NULL se _punto è NULL
 */
void* punto_consegna_get_zona_logistica(PuntoConsegna _punto);

/*
 * Restituisce una stringa che rappresenta il tipo del punto di consegna
 * @param _tipo Tipo del punto di consegna
 * @return Stringa che rappresenta il tipo, oppure "Sconosciuto" se non valido
 */
const char* punto_consegna_tipo_to_string(TipoPuntoConsegna _tipo);

#endif /* PUNTO_CONSEGNA_H */