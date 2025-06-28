/*
 * stack.h
 *
 * Interfaccia di un Tipo di Dato Astratto (ADT) per uno stack di interi,
 * implementato mediante lista concatenata con capacità massima configurabile.
 *
 * Lo stack gestisce gli elementi secondo il paradigma LIFO (Last In, First Out),
 * limitando il numero massimo di elementi tramite una capacità impostata all'atto
 * della creazione, in modo analogo a un array a dimensione fissa.
 *
 * Fornisce operazioni per creare, distruggere, inserire (push),
 * rimuovere (pop), consultare l'elemento in cima (top) e verificare
 * lo stato dello stack (vuoto o pieno).
 */

#include <stdbool.h>
#include <stdlib.h>

typedef struct _stack* stack;

#define STACK_SUCCESS 0
#define STACK_ERROR_NULL -1
#define STACK_ERROR_ALLOC -2
#define STACK_ERROR_EMPTY -3
#define STACK_ERROR_FULL -4

/*
 * Crea un nuovo stack con capacità specificata
 * @param _capacity Capacità massima dello stack
 * @return Puntatore allo stack, oppure NULL in caso di errore di allocazione
 */
stack stack_create(int _capacity);

/*
 * Distrugge lo stack e libera la memoria
 * @param _stack Puntatore allo stack da distruggere (sarà posto a NULL)
 */
void stack_destroy(stack* _stack);

/*
 * Inserisce un valore in cima allo stack
 * @param _stack Stack su cui effettuare l’inserimento
 * @param _value Valore intero da inserire
 * @return STACK_SUCCESS se inserito,
 *         STACK_ERROR_NULL se _stack è NULL,
 *         STACK_ERROR_FULL se lo stack è pieno
 */
int stack_push(stack _stack, int _ptr_value);

/*
 * Rimuove l’elemento in cima allo stack
 * @param _stack Stack da cui rimuovere
 * @param _value_out Puntatore dove scrivere il valore
 * @return STACK_SUCCESS se rimosso,
 *         STACK_ERROR_NULL se _stack è NULL,
 *         STACK_ERROR_EMPTY se lo stack è vuoto
 */
int stack_pop(stack _stack, int* _ptr_value);

/*
 * Restituisce il valore in cima allo stack senza rimuoverlo
 * @param _stack Stack da cui leggere
 * @param _value_out Puntatore dove scrivere il valore
 * @return STACK_SUCCESS se letto,
 *         STACK_ERROR_NULL se _stack è NULL,
 *         STACK_ERROR_EMPTY se lo stack è vuoto
 */
int stack_top(stack _stack, int* _ptr_value);

/*
 * Verifica se lo stack è vuoto
 * @param _stack Stack da verificare
 * @return true se vuoto, false altrimenti. Ritorna true anche se _stack è NULL
 */
bool stack_is_empty(stack _stack);

/*
 * Verifica se lo stack è pieno
 * @param _stack Stack da verificare
 * @return true se pieno, false altrimenti. Ritorna false se _stack è NULL
 */
bool stack_is_full(stack _stack);
