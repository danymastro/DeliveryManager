/*
 * queue.c
 *
 * Implementazione della coda con priorità definita in queue.h.
 *
 * La coda con priorità è implementata utilizzando una lista concatenata ordinata
 * per priorità, dove gli elementi con priorità più alta sono in testa alla lista.
 */

#include <stdlib.h>
#include "queue.h"

typedef struct _priority_queue_node {
    void* element;
    int priority;
    struct _priority_queue_node* next;
} priority_queue_node;

struct _priority_queue {
    priority_queue_node* head;
    int size;
};

priority_queue priority_queue_create() {
    priority_queue queue = (priority_queue)malloc(sizeof(struct _priority_queue));
    if (queue == NULL) return NULL;

    queue->head = NULL;
    queue->size = 0;
    return queue;
}

void priority_queue_destroy(priority_queue* _queue, void (*_free_element)(void*)) {
    if (_queue == NULL || *_queue == NULL) return;

    priority_queue_node* current = (*_queue)->head;
    while (current != NULL) {
        priority_queue_node* next = current->next;
        
        // Libera l'elemento se è fornita una funzione per farlo
        if (_free_element != NULL && current->element != NULL) {
            _free_element(current->element);
        }
        
        free(current);
        current = next;
    }

    free(*_queue);
    *_queue = NULL;
}

int priority_queue_enqueue(priority_queue _queue, void* _element, int _priority) {
    if (_queue == NULL) return QUEUE_ERROR_NULL;

    // Crea un nuovo nodo
    priority_queue_node* new_node = (priority_queue_node*)malloc(sizeof(priority_queue_node));
    if (new_node == NULL) return QUEUE_ERROR_ALLOC;

    new_node->element = _element;
    new_node->priority = _priority;

    // Caso speciale: coda vuota o il nuovo elemento ha priorità maggiore della testa
    if (_queue->head == NULL || _priority > _queue->head->priority) {
        new_node->next = _queue->head;
        _queue->head = new_node;
    } else {
        // Trova la posizione corretta in base alla priorità
        priority_queue_node* current = _queue->head;
        while (current->next != NULL && current->next->priority >= _priority) {
            current = current->next;
        }
        
        new_node->next = current->next;
        current->next = new_node;
    }

    _queue->size++;
    return QUEUE_SUCCESS;
}

int priority_queue_dequeue(priority_queue _queue, void** _element_out) {
    if (_queue == NULL || _element_out == NULL) return QUEUE_ERROR_NULL;
    if (_queue->head == NULL) return QUEUE_ERROR_EMPTY;

    priority_queue_node* node_to_remove = _queue->head;
    *_element_out = node_to_remove->element;
    
    _queue->head = node_to_remove->next;
    free(node_to_remove);
    
    _queue->size--;
    return QUEUE_SUCCESS;
}

int priority_queue_peek(priority_queue _queue, void** _element_out) {
    if (_queue == NULL || _element_out == NULL) return QUEUE_ERROR_NULL;
    if (_queue->head == NULL) return QUEUE_ERROR_EMPTY;

    *_element_out = _queue->head->element;
    return QUEUE_SUCCESS;
}

int priority_queue_size(priority_queue _queue) {
    if (_queue == NULL) return QUEUE_ERROR_NULL;
    return _queue->size;
}

bool priority_queue_is_empty(priority_queue _queue) {
    return (_queue == NULL || _queue->head == NULL);
}

int priority_queue_clear(priority_queue _queue, void (*_free_element)(void*)) {
    if (_queue == NULL) return QUEUE_ERROR_NULL;

    priority_queue_node* current = _queue->head;
    while (current != NULL) {
        priority_queue_node* next = current->next;
        
        // Libera l'elemento se è fornita una funzione per farlo
        if (_free_element != NULL && current->element != NULL) {
            _free_element(current->element);
        }
        
        free(current);
        current = next;
    }

    _queue->head = NULL;
    _queue->size = 0;
    return QUEUE_SUCCESS;
}

bool priority_queue_contains(priority_queue _queue, void* _element, int (*_compare)(const void*, const void*)) {
    if (_queue == NULL || _element == NULL || _compare == NULL) return false;

    priority_queue_node* current = _queue->head;
    while (current != NULL) {
        if (_compare(current->element, _element) == 0) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}
