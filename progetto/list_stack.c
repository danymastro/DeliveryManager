/*
 * stack.c
 *
 * Implementazione dello stack di interi definito in stack.h.
 *
 * Lo stack è rappresentato tramite una lista concatenata (linked list)
 * in cui ogni nodo contiene un valore intero e un puntatore al nodo successivo.
 * La struttura mantiene un riferimento alla cima (top), alla capacità massima
 * e alla dimensione attuale (numero di elementi presenti).
 *
 * Anche se la struttura è dinamica, la capacità massima imposta all'atto
 * della creazione limita il numero di elementi inseribili, analogamente a un array.
 *
 * Tutte le funzioni restituiscono codici di errore e controllano
 * i puntatori NULL. La memoria viene gestita in modo esplicito e sicuro.
 */

#include "list_stack.h"

typedef struct _node {
    int value;
    struct _node* next;
} node;

struct _stack {
    node* top;
    int size;
    int capacity;
};

stack stack_create(int _capacity) {
    if (_capacity <= 0) return NULL;

    stack s = malloc(sizeof(struct _stack));
    if (s == NULL) return NULL;

    s->top = NULL;
    s->size = 0;
    s->capacity = _capacity;

    return s;
}

void stack_destroy(stack* _stack) {
    if (_stack == NULL || *_stack == NULL) return;

    node* current = (*_stack)->top;
    while (current != NULL) {
        node* next = current->next;
        free(current);
        current = next;
    }

    free(*_stack);
    *_stack = NULL;
}

int stack_push(stack _stack, int _ptr_value) {
    if (_stack == NULL) return STACK_ERROR_NULL;

    if (_stack->size == _stack->capacity) return STACK_ERROR_FULL;

    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) return STACK_ERROR_ALLOC;

    new_node->value = _ptr_value;
    new_node->next = _stack->top;
    _stack->top = new_node;
    _stack->size++;

    return STACK_SUCCESS;
}

int stack_pop(stack _stack, int* _ptr_value_out) {
    if (_stack == NULL) return STACK_ERROR_NULL;

    if (_stack->top == NULL) return STACK_ERROR_EMPTY;

    node* to_delete = _stack->top;
    *_ptr_value_out = to_delete->value;
    _stack->top = to_delete->next;
    free(to_delete);
    _stack->size--;

    return STACK_SUCCESS;
}

int stack_top(stack _stack, int* _ptr_value_out) {
    if (_stack == NULL) return STACK_ERROR_NULL;

    if (_stack->top == NULL) return STACK_ERROR_EMPTY;

    *_ptr_value_out = _stack->top->value;
    return STACK_SUCCESS;
}

bool stack_is_empty(stack _stack) {
    return ((_stack == NULL) || (_stack->size == 0));
}

bool stack_is_full(stack _stack) {
    if (_stack == NULL) return false;
    return (_stack->size == _stack->capacity);
}
