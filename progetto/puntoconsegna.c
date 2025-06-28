#include "puntoconsegna.h"
#include <string.h>

struct PuntoConsegna {
    int id;                  // Identificativo del punto di consegna
    char* nome;              // Nome del punto di consegna
    int priorita;            // Priorità del punto di consegna (1-5)
    int orario;              // Orario di consegna (formato HHMM)
    TipoPuntoConsegna tipo;  // Tipo del punto di consegna
    Node nodo;               // Nodo del grafo associato al punto di consegna
    void* zona_logistica;    // Zona logistica a cui appartiene il punto di consegna
};

PuntoConsegna punto_consegna_create(int _id, const char* _nome, int _priorita, 
                                   int _orario, TipoPuntoConsegna _tipo, 
                                   Node _nodo, void* _zona_logistica) {
    if (_nome == NULL || _nodo == NULL || _zona_logistica == NULL) return NULL;
    if (_priorita < 1 || _priorita > 5) return NULL;  // Priorità deve essere tra 1 e 5

    PuntoConsegna punto = (PuntoConsegna)malloc(sizeof(struct PuntoConsegna));
    if (punto == NULL) return NULL;

    punto->id = _id;
    punto->nome = strdup(_nome);
    if (punto->nome == NULL) {
        free(punto);
        return NULL;
    }

    punto->priorita = _priorita;
    punto->orario = _orario;
    punto->tipo = _tipo;
    punto->nodo = _nodo;
    punto->zona_logistica = _zona_logistica;

    return punto;
}

void punto_consegna_destroy(PuntoConsegna* _punto) {
    if (_punto == NULL || *_punto == NULL) return;

    // Libera il nome
    free((*_punto)->nome);

    // Libera la struttura
    free(*_punto);
    *_punto = NULL;
}

int punto_consegna_get_id(PuntoConsegna _punto) {
    if (_punto == NULL) return -1;
    return _punto->id;
}

const char* punto_consegna_get_nome(PuntoConsegna _punto) {
    if (_punto == NULL) return NULL;
    return _punto->nome;
}

int punto_consegna_get_priorita(PuntoConsegna _punto) {
    if (_punto == NULL) return -1;
    return _punto->priorita;
}

int punto_consegna_get_orario(PuntoConsegna _punto) {
    if (_punto == NULL) return -1;
    return _punto->orario;
}

TipoPuntoConsegna punto_consegna_get_tipo(PuntoConsegna _punto) {
    if (_punto == NULL) return -1;
    return _punto->tipo;
}

Node punto_consegna_get_nodo(PuntoConsegna _punto) {
    if (_punto == NULL) return NULL;
    return _punto->nodo;
}

void* punto_consegna_get_zona_logistica(PuntoConsegna _punto) {
    if (_punto == NULL) return NULL;
    return _punto->zona_logistica;
}

const char* punto_consegna_tipo_to_string(TipoPuntoConsegna _tipo) {
    switch (_tipo) {
        case TIPO_STANDARD:
            return "Standard";
        case TIPO_REFRIGERATO:
            return "Refrigerato";
        case TIPO_FRAGILE:
            return "Fragile";
        default:
            return "Sconosciuto";
    }
} 