/*
 * dynamic_array.c
 *
 * Implementazione di un array dinamico generico.
 */

#include "dynamic_array.h"
#include <string.h>

#define GROWTH_FACTOR 2

struct _dynamic_array {
    void* data;          // Puntatore ai dati
    int size;           // Dimensione logica (numero di elementi)
    int capacity;       // Capacità fisica (spazio allocato)
    size_t element_size; // Dimensione in byte di ciascun elemento
};

dynamic_array dynamic_array_create(int _initial_capacity, size_t _element_size) {
    if (_initial_capacity <= 0 || _element_size <= 0) {
        return NULL;
    }

    dynamic_array array = (dynamic_array)malloc(sizeof(struct _dynamic_array));
    if (array == NULL) {
        return NULL;
    }

    array->data = malloc(_initial_capacity * _element_size);
    if (array->data == NULL) {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = _initial_capacity;
    array->element_size = _element_size;

    return array;
}

void dynamic_array_destroy(dynamic_array* _array, void (*_free_element)(void*)) {
    if (_array == NULL || *_array == NULL) {
        return;
    }

    // Se è fornita una funzione per liberare gli elementi, chiamarla per ogni elemento
    if (_free_element != NULL) {
        for (int i = 0; i < (*_array)->size; i++) {
            void* element = (char*)((*_array)->data) + i * (*_array)->element_size;
            _free_element(element);
        }
    }

    free((*_array)->data);
    free(*_array);
    *_array = NULL;
}

// Funzione interna per espandere l'array quando necessario
static int _dynamic_array_ensure_capacity(dynamic_array _array) {
    if (_array->size >= _array->capacity) {
        int new_capacity = _array->capacity * GROWTH_FACTOR;
        void* new_data = realloc(_array->data, new_capacity * _array->element_size);
        if (new_data == NULL) {
            return DYN_ARRAY_ERROR_ALLOC;
        }
        _array->data = new_data;
        _array->capacity = new_capacity;
    }
    return DYN_ARRAY_SUCCESS;
}

int dynamic_array_append(dynamic_array _array, void* _element) {
    if (_array == NULL || _element == NULL) {
        return DYN_ARRAY_ERROR_NULL;
    }

    int result = _dynamic_array_ensure_capacity(_array);
    if (result != DYN_ARRAY_SUCCESS) {
        return result;
    }

    // Calcola l'indirizzo di destinazione e copia l'elemento
    void* dest = (char*)(_array->data) + _array->size * _array->element_size;
    memcpy(dest, _element, _array->element_size);
    _array->size++;

    return DYN_ARRAY_SUCCESS;
}

int dynamic_array_insert_at(dynamic_array _array, int _index, void* _element) {
    if (_array == NULL || _element == NULL) {
        return DYN_ARRAY_ERROR_NULL;
    }

    if (_index < 0 || _index > _array->size) {
        return DYN_ARRAY_ERROR_INDEX;
    }

    int result = _dynamic_array_ensure_capacity(_array);
    if (result != DYN_ARRAY_SUCCESS) {
        return result;
    }

    // Sposta gli elementi successivi a destra
    if (_index < _array->size) {
        void* src = (char*)(_array->data) + _index * _array->element_size;
        void* dest = (char*)(_array->data) + (_index + 1) * _array->element_size;
        size_t bytes_to_move = (_array->size - _index) * _array->element_size;
        memmove(dest, src, bytes_to_move);
    }

    // Inserisce il nuovo elemento
    void* dest = (char*)(_array->data) + _index * _array->element_size;
    memcpy(dest, _element, _array->element_size);
    _array->size++;

    return DYN_ARRAY_SUCCESS;
}

int dynamic_array_remove_at(dynamic_array _array, int _index, void (*_free_element)(void*)) {
    if (_array == NULL) {
        return DYN_ARRAY_ERROR_NULL;
    }

    if (_index < 0 || _index >= _array->size) {
        return DYN_ARRAY_ERROR_INDEX;
    }

    // Se è fornita una funzione per liberare l'elemento, chiamarla
    if (_free_element != NULL) {
        void* element = (char*)(_array->data) + _index * _array->element_size;
        _free_element(element);
    }

    // Sposta gli elementi successivi a sinistra
    if (_index < _array->size - 1) {
        void* dest = (char*)(_array->data) + _index * _array->element_size;
        void* src = (char*)(_array->data) + (_index + 1) * _array->element_size;
        size_t bytes_to_move = (_array->size - _index - 1) * _array->element_size;
        memmove(dest, src, bytes_to_move);
    }

    _array->size--;
    return DYN_ARRAY_SUCCESS;
}

void* dynamic_array_get_at(dynamic_array _array, int _index) {
    if (_array == NULL || _index < 0 || _index >= _array->size) {
        return NULL;
    }

    return (char*)(_array->data) + _index * _array->element_size;
}

int dynamic_array_size(dynamic_array _array) {
    if (_array == NULL) {
        return DYN_ARRAY_ERROR_NULL;
    }
    return _array->size;
}

bool dynamic_array_is_empty(dynamic_array _array) {
    return (_array == NULL || _array->size == 0);
}

int dynamic_array_sort(dynamic_array _array, int (*_compare)(const void*, const void*)) {
    if (_array == NULL || _compare == NULL) {
        return DYN_ARRAY_ERROR_NULL;
    }

    qsort(_array->data, _array->size, _array->element_size, _compare);
    return DYN_ARRAY_SUCCESS;
}

int dynamic_array_find(dynamic_array _array, void* _element, int (*_compare)(const void*, const void*)) {
    if (_array == NULL || _element == NULL || _compare == NULL) {
        return -1;
    }

    for (int i = 0; i < _array->size; i++) {
        void* current = (char*)(_array->data) + i * _array->element_size;
        if (_compare(current, _element) == 0) {
            return i;
        }
    }

    return -1;
}
