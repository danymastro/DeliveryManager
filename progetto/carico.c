#include "carico.h"

struct Carico {
    int id;                  // Identificativo del carico
    int peso;                // Peso del carico in kg
    TipoCarico tipologia;    // Tipo del carico
    Node destinazione;       // Nodo del grafo associato al punto di consegna
    int priorita;            // Priorità del carico (1-5)
    Node centro_smistamento; // Nodo del grafo associato al centro di smistamento
    Missione missione;       // Missione associata al carico
};

Carico carico_create(int _id, int _peso, TipoCarico _tipologia, 
                    Node _destinazione, int _priorita, Node _centro_smistamento) {
    if (_peso <= 0 || _destinazione == NULL || _centro_smistamento == NULL) return NULL;
    if (_priorita < 1 || _priorita > 5) return NULL;  // Priorità deve essere tra 1 e 5

    Carico carico = (Carico)malloc(sizeof(struct Carico));
    if (carico == NULL) return NULL;

    carico->id = _id;
    carico->peso = _peso;
    carico->tipologia = _tipologia;
    carico->destinazione = _destinazione;
    carico->priorita = _priorita;
    carico->centro_smistamento = _centro_smistamento;
    carico->missione = NULL;

    return carico;
}

void carico_destroy(Carico* _carico) {
    if (_carico == NULL || *_carico == NULL) return;

    // Libera la struttura
    free(*_carico);
    *_carico = NULL;
}

int carico_get_id(Carico _carico) {
    if (_carico == NULL) return -1;
    return _carico->id;
}

int carico_get_peso(Carico _carico) {
    if (_carico == NULL) return -1;
    return _carico->peso;
}

TipoCarico carico_get_tipologia(Carico _carico) {
    if (_carico == NULL) return -1;
    return _carico->tipologia;
}

Node carico_get_destinazione(Carico _carico) {
    if (_carico == NULL) return NULL;
    return _carico->destinazione;
}

int carico_get_priorita(Carico _carico) {
    if (_carico == NULL) return -1;
    return _carico->priorita;
}

Node carico_get_centro_smistamento(Carico _carico) {
    if (_carico == NULL) return NULL;
    return _carico->centro_smistamento;
}

Missione carico_get_missione(Carico _carico) {
    if (_carico == NULL) return NULL;
    return _carico->missione;
}

int carico_set_missione(Carico _carico, Missione _missione) {
    if (_carico == NULL) return -1;
    _carico->missione = _missione;
    return 0;
}

const char* carico_tipo_to_string(TipoCarico _tipo) {
    switch (_tipo) {
        case CARICO_STANDARD:
            return "Standard";
        case CARICO_REFRIGERATO:
            return "Refrigerato";
        case CARICO_FRAGILE:
            return "Fragile";
        default:
            return "Sconosciuto";
    }
} 