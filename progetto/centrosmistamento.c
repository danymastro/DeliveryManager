#include "centrosmistamento.h"
#include <string.h>

struct CentroSmistamento {
    int id;                      // Identificativo del centro di smistamento
    char* nome;                  // Nome del centro di smistamento
    Node nodo;                   // Nodo del grafo associato al centro di smistamento
    priority_queue carichi;      // Coda con priorità dei carichi disponibili
    priority_queue veicoli;      // Coda dei veicoli in attesa
};

CentroSmistamento centro_smistamento_create(int _id, const char* _nome, Node _nodo) {
    if (_nome == NULL || _nodo == NULL) return NULL;

    CentroSmistamento centro = (CentroSmistamento)malloc(sizeof(struct CentroSmistamento));
    if (centro == NULL) return NULL;

    centro->id = _id;
    centro->nome = strdup(_nome);
    if (centro->nome == NULL) {
        free(centro);
        return NULL;
    }

    centro->nodo = _nodo;

    centro->carichi = priority_queue_create();
    if (centro->carichi == NULL) {
        free(centro->nome);
        free(centro);
        return NULL;
    }

    centro->veicoli = priority_queue_create();
    if (centro->veicoli == NULL) {
        priority_queue_destroy(&(centro->carichi), NULL);
        free(centro->nome);
        free(centro);
        return NULL;
    }

    return centro;
}

void centro_smistamento_destroy(CentroSmistamento* _centro) {
    if (_centro == NULL || *_centro == NULL) return;

    // Libera il nome
    free((*_centro)->nome);

    // Libera le code
    // Nota: non liberiamo i carichi e i veicoli stessi, poiché potrebbero essere
    // referenziati altrove
    priority_queue_destroy(&((*_centro)->carichi), NULL);
    priority_queue_destroy(&((*_centro)->veicoli), NULL);

    // Libera la struttura
    free(*_centro);
    *_centro = NULL;
}

int centro_smistamento_get_id(CentroSmistamento _centro) {
    if (_centro == NULL) return -1;
    return _centro->id;
}

const char* centro_smistamento_get_nome(CentroSmistamento _centro) {
    if (_centro == NULL) return NULL;
    return _centro->nome;
}

Node centro_smistamento_get_nodo(CentroSmistamento _centro) {
    if (_centro == NULL) return NULL;
    return _centro->nodo;
}

int centro_smistamento_add_carico(CentroSmistamento _centro, void* _carico, int _priorita) {
    if (_centro == NULL || _carico == NULL) return -1;
    if (_priorita < 1 || _priorita > 5) return -1;  // Priorità deve essere tra 1 e 5
    
    return priority_queue_enqueue(_centro->carichi, _carico, _priorita);
}

int centro_smistamento_get_next_carico(CentroSmistamento _centro, void** _carico_out) {
    if (_centro == NULL || _carico_out == NULL) return -1;
    
    return priority_queue_dequeue(_centro->carichi, _carico_out);
}

int centro_smistamento_get_num_carichi(CentroSmistamento _centro) {
    if (_centro == NULL) return -1;
    return priority_queue_size(_centro->carichi);
}

int centro_smistamento_has_carichi(CentroSmistamento _centro) {
    if (_centro == NULL) return 0;
    return priority_queue_is_empty(_centro->carichi) ? 0 : 1;
}

int centro_smistamento_add_veicolo(CentroSmistamento _centro, void* _veicolo) {
    if (_centro == NULL || _veicolo == NULL) return -1;
    
    // I veicoli vengono inseriti con priorità 1 (FIFO)
    return priority_queue_enqueue(_centro->veicoli, _veicolo, 1);
}

int centro_smistamento_get_next_veicolo(CentroSmistamento _centro, void** _veicolo_out) {
    if (_centro == NULL || _veicolo_out == NULL) return -1;
    
    return priority_queue_dequeue(_centro->veicoli, _veicolo_out);
}

int centro_smistamento_get_num_veicoli(CentroSmistamento _centro) {
    if (_centro == NULL) return -1;
    return priority_queue_size(_centro->veicoli);
}

int centro_smistamento_has_veicoli(CentroSmistamento _centro) {
    if (_centro == NULL) return 0;
    return priority_queue_is_empty(_centro->veicoli) ? 0 : 1;
} 