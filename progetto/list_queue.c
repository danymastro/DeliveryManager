/*
 * queue.c
 *
 * Implementazione della coda di interi definita in queue.h.
 *
 * La coda è realizzata mediante lista concatenata, con riferimento esplicito
 * alla testa (head) e alla coda (tail). La capacità massima è rispettata come
 * vincolo logico e impedisce l'inserimento oltre il limite prefissato.
 *
 * Ogni operazione è protetta contro puntatori NULL e situazioni di errore
 * come coda vuota o piena. L’interfaccia è conforme al comportamento FIFO.
 */

#include <stdlib.h>
#include "list_queue.h"

typedef struct _node {
    int value;
    struct _node* next;
} node;

struct _queue {
    node* head;
    node* tail;
    int size;
    int capacity;
};

queue queue_create(int _capacity) {
    if (_capacity <= 0) return NULL;

    queue q = malloc(sizeof(struct _queue));
    if (q == NULL) return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    q->capacity = _capacity;

    return q;
}

void queue_destroy(queue* _queue) {
    if (_queue == NULL || *_queue == NULL) return;

    node* current = (*_queue)->head;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }

    free(*_queue);
    *_queue = NULL;
}

int queue_enqueue(queue _queue, int _value) {
    if (_queue == NULL) return QUEUE_ERROR_NULL;

    if (_queue->size == _queue->capacity) return QUEUE_ERROR_FULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return QUEUE_ERROR_ALLOC;

    new_node->value = _value;
    new_node->next = NULL;

    if (_queue->tail == NULL) {
        _queue->head = new_node;
    } else {
        _queue->tail->next = new_node;
    }

    _queue->tail = new_node;
    _queue->size++;

    return QUEUE_SUCCESS;
}

int queue_dequeue(queue _queue, int* _ptr_value_out) {
    if (_queue == NULL) return QUEUE_ERROR_NULL;

    if (_queue->head == NULL) return QUEUE_ERROR_EMPTY;

    node* to_remove = _queue->head;
    *_ptr_value_out = to_remove->value;
    _queue->head = to_remove->next;
    free(to_remove);

    _queue->size--;

    if (_queue->head == NULL) {
        _queue->tail = NULL;
    }

    return QUEUE_SUCCESS;
}

int queue_peek(queue _queue, int* _ptr_value_out) {
    if (_queue == NULL) return QUEUE_ERROR_NULL;

    if (_queue->head == NULL) return QUEUE_ERROR_EMPTY;

    *_ptr_value_out = _queue->head->value;
    return QUEUE_SUCCESS;
}

bool queue_is_empty(queue _queue) {
    return (_queue == NULL || _queue->size == 0);
}

bool queue_is_full(queue _queue) {
    if (_queue == NULL) return false;
    return (_queue->size == _queue->capacity);
}
