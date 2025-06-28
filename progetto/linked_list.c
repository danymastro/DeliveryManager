/*
 * linked_list.c
 *
 * Implementazione di una lista concatenata di interi come Tipo di Dato Astratto (ADT),
 * con puntatori opachi per nascondere i dettagli interni. Le operazioni includono
 * inserimento, accesso, rimozione e ricerca.
 *
 * Include anche il supporto a un iteratore per la scansione sequenziale della lista.
 */

#include "linked_list.h"

typedef struct _node {
    int value;
    struct _node* next;
} node;

struct linked_list {
    node* head;
    node* tail;
    int size;
};

struct linked_list_iterator {
    linked_list list;
    node* current;
};

linked_list linked_list_create() {
    linked_list list = malloc(sizeof(struct linked_list));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

int linked_list_insert_front(linked_list _list, int _value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = _value;
    new_node->next = _list->head;
    _list->head = new_node;

    if (_list->tail == NULL) {
        _list->tail = new_node;
    }

    _list->size++;
    return LINKED_LIST_SUCCESS;
}

int linked_list_insert_back(linked_list _list, int _value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = _value;
    new_node->next = NULL;

    if (_list->tail != NULL) {
        _list->tail->next = new_node;
    } else {
        _list->head = new_node;
    }

    _list->tail = new_node;
    _list->size++;
    return LINKED_LIST_SUCCESS;
}

int linked_list_insert_at(linked_list _list, int _index, int _value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    if (_index < 0 || _index > _list->size) return LINKED_LIST_ERROR_INDEX;

    if (_index == 0) return linked_list_insert_front(_list, _value);

    if (_index == _list->size) return linked_list_insert_back(_list, _value);

    node* prev = _list->head;
    for (int i = 0; i < _index - 1; i++) {
        prev = prev->next;
    }

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return LINKED_LIST_ERROR_ALLOC;

    new_node->value = _value;
    new_node->next = prev->next;
    prev->next = new_node;

    _list->size++;
    return LINKED_LIST_SUCCESS;
}

int linked_list_get_at(linked_list _list, int _index, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    if (_list->head == NULL) return LINKED_LIST_ERROR_EMPTY;

    if (_index < 0 || _index >= _list->size) return LINKED_LIST_ERROR_INDEX;

    node* current = _list->head;
    for (int i = 0; i < _index; i++) {
        current = current->next;
    }

    *_value_out = current->value;
    return LINKED_LIST_SUCCESS;
}

int linked_list_get_front(linked_list _list, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    if (_list->head == NULL) return LINKED_LIST_ERROR_EMPTY;

    *_value_out = _list->head->value;
    return LINKED_LIST_SUCCESS;
}

int linked_list_get_back(linked_list _list, int* _value_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    if (_list->tail == NULL) return LINKED_LIST_ERROR_EMPTY;

    *_value_out = _list->tail->value;
    return LINKED_LIST_SUCCESS;
}

int linked_list_find(linked_list _list, int _value, int* _index_out) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* current = _list->head;
    int index = 0;
    while ((current != NULL) && (current->value != _value)) {
        current = current->next;
        index++;
    }
    if (current == NULL)
        return LINKED_LIST_ERROR_NOT_FOUND;
    else {
        *_index_out = index;
        return LINKED_LIST_SUCCESS;
    }
}

int linked_list_remove_at(linked_list _list, int _index) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    if (_index < 0 || _index >= _list->size) return LINKED_LIST_ERROR_INDEX;

    if (_list->head == NULL) return LINKED_LIST_ERROR_EMPTY;

    node* to_delete;

    if (_index == 0) {
        to_delete = _list->head;
        _list->head = to_delete->next;
        if (_list->head == NULL) _list->tail = NULL;
    } else {
        node* prev = _list->head;
        for (int i = 0; i < _index - 1; i++) {
            prev = prev->next;
        }
        to_delete = prev->next;
        prev->next = to_delete->next;
        if (to_delete == _list->tail) {
            _list->tail = prev;
        }
    }

    free(to_delete);
    _list->size--;
    return LINKED_LIST_SUCCESS;
}

int linked_list_remove_value(linked_list _list, int _value) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    node* current = _list->head;
    node* prev = NULL;

    while ((current != NULL) && (current->value != _value)) {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return LINKED_LIST_ERROR_NOT_FOUND;
    else {
        if (prev == NULL) {
            _list->head = current->next;
            if (_list->head == NULL) _list->tail = NULL;
        } else {
            prev->next = current->next;
            if (current == _list->tail) _list->tail = prev;
        }
        free(current);
        _list->size--;
        return LINKED_LIST_SUCCESS;
    }
}

int linked_list_remove_back(linked_list _list) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;

    if (_list->head == NULL) return LINKED_LIST_ERROR_EMPTY;

    node* current = _list->head;
    node* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        _list->head = NULL;
        _list->tail = NULL;
    } else {
        prev->next = NULL;
        _list->tail = prev;
    }

    free(current);
    _list->size--;
    return LINKED_LIST_SUCCESS;
}

int linked_list_is_empty(const linked_list _list) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    return (_list->size == 0);
}

int linked_list_size(const linked_list _list) {
    if (_list == NULL) return LINKED_LIST_ERROR_NULL;
    return _list->size;
}

void linked_list_destroy(linked_list* _list) {
    if (_list == NULL || *_list == NULL) return;

    node* current = (*_list)->head;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }

    free(*_list);
    *_list = NULL;
}

linked_list_iterator linked_list_iterator_create(linked_list _list) {
    if (_list == NULL) return NULL;

    linked_list_iterator iterator = malloc(sizeof(struct linked_list_iterator));
    if (iterator == NULL) return NULL;

    iterator->current = _list->head;
    return iterator;
}

bool linked_list_iterator_has_next(linked_list_iterator _iterator) {
    return (_iterator != NULL && _iterator->current != NULL);
}

int linked_list_iterator_next(linked_list_iterator _iterator) {
    int value = _iterator->current->value;
    _iterator->current = _iterator->current->next;
    return value;
}

void linked_list_iterator_destroy(linked_list_iterator* _iterator) {
    if (_iterator == NULL || *_iterator == NULL) return;
    free(*_iterator);
    *_iterator = NULL;
}

// Funzione di utilità per aggiungere un elemento alla fine della lista (alias di insert_back)
int linked_list_append(linked_list _list, int _value) {
    return linked_list_insert_back(_list, _value);
}

// Funzione di utilità per aggiungere un elemento all'inizio della lista (alias di insert_front)
int linked_list_prepend(linked_list _list, int _value) {
    return linked_list_insert_front(_list, _value);
}