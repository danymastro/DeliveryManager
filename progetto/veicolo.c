#include "veicolo.h"
#include "carico.h"
#include <string.h>

struct Veicolo {
    char* targa;                // Targa del veicolo
    int capacita;               // Capacità massima del veicolo in kg
    StatoOperativoVeicolo stato; // Stato operativo del veicolo
    dynamic_array carichi;      // Array dinamico dei carichi assegnati
};

Veicolo veicolo_create(const char* _targa, int _capacita) {
    if (_targa == NULL || _capacita <= 0) return NULL;

    Veicolo veicolo = (Veicolo)malloc(sizeof(struct Veicolo));
    if (veicolo == NULL) return NULL;

    veicolo->targa = strdup(_targa);
    if (veicolo->targa == NULL) {
        free(veicolo);
        return NULL;
    }

    veicolo->capacita = _capacita;
    veicolo->stato = STATO_DISPONIBILE;

    veicolo->carichi = dynamic_array_create(5, sizeof(void*));
    if (veicolo->carichi == NULL) {
        free(veicolo->targa);
        free(veicolo);
        return NULL;
    }

    return veicolo;
}

void veicolo_destroy(Veicolo* _veicolo) {
    if (_veicolo == NULL || *_veicolo == NULL) return;

    // Libera la targa
    free((*_veicolo)->targa);

    // Libera l'array dinamico dei carichi
    // Nota: non liberiamo i carichi stessi, poiché potrebbero essere
    // referenziati altrove
    dynamic_array_destroy(&((*_veicolo)->carichi), NULL);

    // Libera la struttura
    free(*_veicolo);
    *_veicolo = NULL;
}

const char* veicolo_get_targa(Veicolo _veicolo) {
    if (_veicolo == NULL) return NULL;
    return _veicolo->targa;
}

int veicolo_get_capacita(Veicolo _veicolo) {
    if (_veicolo == NULL) return -1;
    return _veicolo->capacita;
}

StatoOperativoVeicolo veicolo_get_stato_operativo(Veicolo _veicolo) {
    if (_veicolo == NULL) return -1;
    return _veicolo->stato;
}

int veicolo_set_stato_operativo(Veicolo _veicolo, StatoOperativoVeicolo _stato) {
    if (_veicolo == NULL) return -1;
    _veicolo->stato = _stato;
    return 0;
}

int veicolo_add_carico(Veicolo _veicolo, void* _carico) {
    if (_veicolo == NULL || _carico == NULL) return -1;
    
    // Verifica che il carico non sia già presente
    for (int i = 0; i < dynamic_array_size(_veicolo->carichi); i++) {
        void* carico = *(void**)dynamic_array_get_at(_veicolo->carichi, i);
        if (carico == _carico) {
            return -1; // Carico già presente
        }
    }
    
    // Verifica che il veicolo possa accettare il carico
    int peso_carico = carico_get_peso((Carico)_carico);
    if (!veicolo_puo_accettare_carico(_veicolo, peso_carico)) {
        return -1; // Capacità insufficiente
    }
    
    // Aggiungi il carico all'array
    return dynamic_array_append(_veicolo->carichi, &_carico);
}

int veicolo_remove_carico(Veicolo _veicolo, void* _carico) {
    if (_veicolo == NULL || _carico == NULL) return -1;
    
    // Cerca il carico nell'array
    for (int i = 0; i < dynamic_array_size(_veicolo->carichi); i++) {
        void** carico_ptr = (void**)dynamic_array_get_at(_veicolo->carichi, i);
        if (carico_ptr != NULL && *carico_ptr == _carico) {
            // Rimuovi il carico dall'array
            return dynamic_array_remove_at(_veicolo->carichi, i, NULL);
        }
    }
    
    return -1; // Carico non trovato
}

void* veicolo_get_carico(Veicolo _veicolo, int _index) {
    if (_veicolo == NULL || _index < 0 || _index >= dynamic_array_size(_veicolo->carichi)) {
        return NULL;
    }
    
    void** carico_ptr = (void**)dynamic_array_get_at(_veicolo->carichi, _index);
    if (carico_ptr == NULL) return NULL;
    
    return *carico_ptr;
}

int veicolo_get_num_carichi(Veicolo _veicolo) {
    if (_veicolo == NULL) return -1;
    return dynamic_array_size(_veicolo->carichi);
}

int veicolo_get_peso_totale_carichi(Veicolo _veicolo) {
    if (_veicolo == NULL) return -1;
    
    int peso_totale = 0;
    for (int i = 0; i < dynamic_array_size(_veicolo->carichi); i++) {
        void** carico_ptr = (void**)dynamic_array_get_at(_veicolo->carichi, i);
        if (carico_ptr != NULL) {
            Carico carico = (Carico)*carico_ptr;
            peso_totale += carico_get_peso(carico);
        }
    }
    
    return peso_totale;
}

int veicolo_puo_accettare_carico(Veicolo _veicolo, int _peso_carico) {
    if (_veicolo == NULL || _peso_carico <= 0) return 0;
    
    // Verifica che il veicolo sia disponibile o in viaggio
    if (_veicolo->stato == STATO_IN_MANUTENZIONE) return 0;
    
    // Verifica che ci sia capacità sufficiente
    int peso_attuale = veicolo_get_peso_totale_carichi(_veicolo);
    return (peso_attuale + _peso_carico <= _veicolo->capacita) ? 1 : 0;
}

const char* veicolo_stato_to_string(StatoOperativoVeicolo _stato) {
    switch (_stato) {
        case STATO_DISPONIBILE:
            return "Disponibile";
        case STATO_IN_VIAGGIO:
            return "In Viaggio";
        case STATO_IN_MANUTENZIONE:
            return "In Manutenzione";
        default:
            return "Sconosciuto";
    }
} 