#include "zonalogistica.h"
#include "puntoconsegna.h"

struct ZonaLogistica {
    int id;                 
    char* nome;            
    dynamic_array punti_consegna; 
};

ZonaLogistica zona_logistica_create(int _id, const char* _nome) {
    if (_nome == NULL) return NULL;

    ZonaLogistica zona = (ZonaLogistica)malloc(sizeof(struct ZonaLogistica));
    if (zona == NULL) return NULL;

    zona->id = _id;
    zona->nome = strdup(_nome);
    if (zona->nome == NULL) {
        free(zona);
        return NULL;
    }

    zona->punti_consegna = dynamic_array_create(5, sizeof(void*));
    if (zona->punti_consegna == NULL) {
        free(zona->nome);
        free(zona);
        return NULL;
    }

    return zona;
}

void zona_logistica_destroy(ZonaLogistica* _zona) {
    if (_zona == NULL || *_zona == NULL) return;

    // Libera il nome
    free((*_zona)->nome);

    // Libera l'array dinamico dei punti di consegna
    // Nota: non liberiamo i punti di consegna stessi, poiché potrebbero essere
    // referenziati altrove (ad es. dal grafo)
    dynamic_array_destroy(&((*_zona)->punti_consegna), NULL);

    // Libera la struttura
    free(*_zona);
    *_zona = NULL;
}

int zona_logistica_get_id(ZonaLogistica _zona) {
    if (_zona == NULL) return -1;
    return _zona->id;
}

char* zona_logistica_get_nome(ZonaLogistica _zona) {
    if (_zona == NULL) return NULL;
    return _zona->nome;
}

int zona_logistica_add_punto_consegna(ZonaLogistica _zona, void* _punto) {
    if (_zona == NULL || _punto == NULL) return -1;
    
    // Verifica che il punto di consegna non sia già presente
    for (int i = 0; i < dynamic_array_size(_zona->punti_consegna); i++) {
        void* punto = *(void**)dynamic_array_get_at(_zona->punti_consegna, i);
        if (punto == _punto) {
            return -1; // Punto già presente
        }
    }
    
    // Aggiungi il punto di consegna all'array
    return dynamic_array_append(_zona->punti_consegna, &_punto);
}

void* zona_logistica_get_punto_consegna(ZonaLogistica _zona, int _index) {
    if (_zona == NULL || _index < 0 || _index >= dynamic_array_size(_zona->punti_consegna)) {
        return NULL;
    }
    
    void** punto_ptr = (void**)dynamic_array_get_at(_zona->punti_consegna, _index);
    if (punto_ptr == NULL) return NULL;
    
    return *punto_ptr;
}

void* zona_logistica_find_punto_consegna_by_id(ZonaLogistica _zona, int _id) {
    if (_zona == NULL) return NULL;
    
    for (int i = 0; i < dynamic_array_size(_zona->punti_consegna); i++) {
        void** punto_ptr = (void**)dynamic_array_get_at(_zona->punti_consegna, i);
        if (punto_ptr != NULL) {
            PuntoConsegna punto = (PuntoConsegna)*punto_ptr;
            if (punto_consegna_get_id(punto) == _id) {
                return punto;
            }
        }
    }
    
    return NULL;
}

void* zona_logistica_find_punto_consegna_by_nome(ZonaLogistica _zona, const char* _nome) {
    if (_zona == NULL || _nome == NULL) return NULL;
    
    for (int i = 0; i < dynamic_array_size(_zona->punti_consegna); i++) {
        void** punto_ptr = (void**)dynamic_array_get_at(_zona->punti_consegna, i);
        if (punto_ptr != NULL) {
            PuntoConsegna punto = (PuntoConsegna)*punto_ptr;
            const char* nome_punto = punto_consegna_get_nome(punto);
            if (nome_punto != NULL && strcmp(nome_punto, _nome) == 0) {
                return punto;
            }
        }
    }
    
    return NULL;
}

int zona_logistica_get_num_punti_consegna(ZonaLogistica _zona) {
    if (_zona == NULL) return -1;
    return dynamic_array_size(_zona->punti_consegna);
} 