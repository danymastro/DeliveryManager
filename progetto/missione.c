#include "missione.h"
#include "carico.h"
#include <string.h>

struct Missione {
    int id;                  // Identificativo della missione
    Veicolo veicolo;         // Veicolo associato alla missione
    StatoMissione stato;     // Stato della missione
    dynamic_array carichi;   // Array dinamico dei carichi associati
    time_t data_inizio;      // Data di inizio della missione
    time_t data_fine;        // Data di fine della missione
    char* nota;              // Nota testuale sulla missione
};

Missione missione_create(int _id, Veicolo _veicolo) {
    if (_veicolo == NULL) return NULL;

    Missione missione = (Missione)malloc(sizeof(struct Missione));
    if (missione == NULL) return NULL;

    missione->id = _id;
    missione->veicolo = _veicolo;
    missione->stato = STATO_MISSIONE_IN_CORSO;
    missione->data_inizio = 0;
    missione->data_fine = 0;
    missione->nota = NULL;

    missione->carichi = dynamic_array_create(5, sizeof(void*));
    if (missione->carichi == NULL) {
        free(missione);
        return NULL;
    }

    return missione;
}

void missione_destroy(Missione* _missione) {
    if (_missione == NULL || *_missione == NULL) return;

    // Libera la nota se presente
    if ((*_missione)->nota != NULL) {
        free((*_missione)->nota);
    }

    // Libera l'array dinamico dei carichi
    // Nota: non liberiamo i carichi stessi, poiché potrebbero essere
    // referenziati altrove
    dynamic_array_destroy(&((*_missione)->carichi), NULL);

    // Libera la struttura
    free(*_missione);
    *_missione = NULL;
}

int missione_get_id(Missione _missione) {
    if (_missione == NULL) return -1;
    return _missione->id;
}

Veicolo missione_get_veicolo(Missione _missione) {
    if (_missione == NULL) return NULL;
    return _missione->veicolo;
}

StatoMissione missione_get_stato(Missione _missione) {
    if (_missione == NULL) return -1;
    return _missione->stato;
}

int missione_set_stato(Missione _missione, StatoMissione _stato) {
    if (_missione == NULL) return -1;
    _missione->stato = _stato;
    return 0;
}

int missione_add_carico(Missione _missione, void* _carico) {
    if (_missione == NULL || _carico == NULL) return -1;
    
    // Verifica che il carico non sia già presente
    for (int i = 0; i < dynamic_array_size(_missione->carichi); i++) {
        void* carico = *(void**)dynamic_array_get_at(_missione->carichi, i);
        if (carico == _carico) {
            return -1; // Carico già presente
        }
    }
    
    // Aggiungi il carico all'array
    int result = dynamic_array_append(_missione->carichi, &_carico);
    if (result == 0) {
        // Associa la missione al carico
        carico_set_missione((Carico)_carico, _missione);
    }
    
    return result;
}

int missione_remove_carico(Missione _missione, void* _carico) {
    if (_missione == NULL || _carico == NULL) return -1;
    
    // Cerca il carico nell'array
    for (int i = 0; i < dynamic_array_size(_missione->carichi); i++) {
        void** carico_ptr = (void**)dynamic_array_get_at(_missione->carichi, i);
        if (carico_ptr != NULL && *carico_ptr == _carico) {
            // Rimuovi l'associazione tra carico e missione
            carico_set_missione((Carico)_carico, NULL);
            
            // Rimuovi il carico dall'array
            return dynamic_array_remove_at(_missione->carichi, i, NULL);
        }
    }
    
    return -1; // Carico non trovato
}

int missione_get_num_carichi(Missione _missione) {
    if (_missione == NULL) return -1;
    return dynamic_array_size(_missione->carichi);
}

void* missione_get_carico(Missione _missione, int _index) {
    if (_missione == NULL || _index < 0 || _index >= dynamic_array_size(_missione->carichi)) {
        return NULL;
    }
    
    void** carico_ptr = (void**)dynamic_array_get_at(_missione->carichi, _index);
    if (carico_ptr == NULL) return NULL;
    
    return *carico_ptr;
}

int missione_set_data_inizio(Missione _missione, time_t _data_inizio) {
    if (_missione == NULL) return -1;
    _missione->data_inizio = _data_inizio;
    return 0;
}

int missione_set_data_fine(Missione _missione, time_t _data_fine) {
    if (_missione == NULL) return -1;
    _missione->data_fine = _data_fine;
    return 0;
}

time_t missione_get_data_inizio(Missione _missione) {
    if (_missione == NULL) return 0;
    return _missione->data_inizio;
}

time_t missione_get_data_fine(Missione _missione) {
    if (_missione == NULL) return 0;
    return _missione->data_fine;
}

double missione_get_durata(Missione _missione) {
    if (_missione == NULL) return -1;
    if (_missione->data_inizio == 0 || _missione->data_fine == 0) return -1;
    
    return difftime(_missione->data_fine, _missione->data_inizio);
}

int missione_set_nota(Missione _missione, const char* _nota) {
    if (_missione == NULL) return -1;
    
    // Libera la nota precedente se presente
    if (_missione->nota != NULL) {
        free(_missione->nota);
        _missione->nota = NULL;
    }
    
    // Se la nuova nota è NULL, lasciamo la nota come NULL
    if (_nota == NULL) return 0;
    
    // Altrimenti, duplica la stringa
    _missione->nota = strdup(_nota);
    if (_missione->nota == NULL) return -1;
    
    return 0;
}

const char* missione_get_nota(Missione _missione) {
    if (_missione == NULL) return NULL;
    return _missione->nota;
}

const char* missione_stato_to_string(StatoMissione _stato) {
    switch (_stato) {
        case STATO_MISSIONE_IN_CORSO:
            return "In Corso";
        case STATO_MISSIONE_COMPLETATA:
            return "Completata";
        case STATO_MISSIONE_FALLITA:
            return "Fallita";
        default:
            return "Sconosciuto";
    }
} 