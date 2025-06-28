#ifndef CARICO_H
#define CARICO_H

#include <stdlib.h>
#include "weighted_directed_graph.h"
#include "missione.h"

typedef struct Carico* Carico;

// Tipi di carico
typedef enum {
    CARICO_STANDARD = 1,
    CARICO_REFRIGERATO = 2,
    CARICO_FRAGILE = 3
} TipoCarico;

/*
 * Crea un nuovo carico
 * @param _id Identificativo del carico
 * @param _peso Peso del carico in kg
 * @param _tipologia Tipo del carico
 * @param _destinazione Nodo del grafo associato al punto di consegna
 * @param _priorita Priorità del carico (1-5)
 * @param _centro_smistamento Nodo del grafo associato al centro di smistamento
 * @return Puntatore al carico creato, oppure NULL in caso di errore
 */
Carico carico_create(int _id, int _peso, TipoCarico _tipologia, 
                    Node _destinazione, int _priorita, Node _centro_smistamento);

/*
 * Distrugge un carico e libera la memoria
 * @param _carico Puntatore al puntatore del carico da distruggere
 */
void carico_destroy(Carico* _carico);

/*
 * Restituisce l'ID del carico
 * @param _carico Carico da cui leggere
 * @return ID del carico, oppure -1 se _carico è NULL
 */
int carico_get_id(Carico _carico);

/*
 * Restituisce il peso del carico
 * @param _carico Carico da cui leggere
 * @return Peso del carico in kg, oppure -1 se _carico è NULL
 */
int carico_get_peso(Carico _carico);

/*
 * Restituisce il tipo del carico
 * @param _carico Carico da cui leggere
 * @return Tipo del carico, oppure -1 se _carico è NULL
 */
TipoCarico carico_get_tipologia(Carico _carico);

/*
 * Restituisce il nodo di destinazione del carico
 * @param _carico Carico da cui leggere
 * @return Nodo di destinazione, oppure NULL se _carico è NULL
 */
Node carico_get_destinazione(Carico _carico);

/*
 * Restituisce la priorità del carico
 * @param _carico Carico da cui leggere
 * @return Priorità del carico (1-5), oppure -1 se _carico è NULL
 */
int carico_get_priorita(Carico _carico);

/*
 * Restituisce il nodo del centro di smistamento del carico
 * @param _carico Carico da cui leggere
 * @return Nodo del centro di smistamento, oppure NULL se _carico è NULL
 */
Node carico_get_centro_smistamento(Carico _carico);

/*
 * Restituisce la missione associata al carico
 * @param _carico Carico da cui leggere
 * @return Puntatore alla missione, oppure NULL se non assegnata o _carico è NULL
 */
Missione carico_get_missione(Carico _carico);

/*
 * Imposta la missione associata al carico
 * @param _carico Carico da modificare
 * @param _missione Missione da associare
 * @return 0 se impostata con successo, -1 altrimenti
 */
int carico_set_missione(Carico _carico, Missione _missione);

/*
 * Restituisce una stringa che rappresenta il tipo del carico
 * @param _tipo Tipo del carico
 * @return Stringa che rappresenta il tipo, oppure "Sconosciuto" se non valido
 */
const char* carico_tipo_to_string(TipoCarico _tipo);

#endif /* CARICO_H */