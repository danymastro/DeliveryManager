/*
 * queue.h
 *
 * Interfaccia di un Tipo di Dato Astratto (ADT) per una coda di interi,
 * implementata mediante lista concatenata con capacità massima impostata
 * all'atto della creazione.
 *
 * La coda segue la semantica FIFO (First In, First Out), in cui gli
 * elementi vengono inseriti in coda (enqueue) e rimossi dalla testa (dequeue).
 *
 * L’uso di una lista concatenata consente flessibilità nell’allocazione
 * dinamica della memoria, mentre il vincolo di capacità mantiene
 * sotto controllo l’uso delle risorse, analogamente a un array.
 *
 * Il modulo fornisce operazioni per creare, distruggere, inserire,
 * rimuovere, consultare l’elemento in testa e verificare lo stato
 * della coda (vuota o piena).
 */

#include <stdbool.h>
#include <stdlib.h>

typedef struct _queue* queue;

#define QUEUE_SUCCESS 0
#define QUEUE_ERROR_NULL -1
#define QUEUE_ERROR_ALLOC -2
#define QUEUE_ERROR_EMPTY -3
#define QUEUE_ERROR_FULL -4

/*
 * Crea una nuova coda con capacità specificata
 * @param _capacity Numero massimo di elementi nella coda
 * @return Puntatore alla coda creata, oppure NULL se errore di allocazione
 */
queue queue_create(int _capacity);

/*
 * Distrugge la coda e libera la memoria associata
 * @param _queue Puntatore alla coda da distruggere (sarà posto a NULL)
 */
void queue_destroy(queue* _queue);

/*
 * Inserisce un elemento in coda (enqueue)
 * @param _queue Coda su cui inserire
 * @param _value Valore da inserire
 * @return QUEUE_SUCCESS se inserito,
 *         QUEUE_ERROR_NULL se _queue è NULL,
 *         QUEUE_ERROR_FULL se la coda è piena
 */
int queue_enqueue(queue _queue, int _ptr_value);

/*
 * Rimuove l’elemento in testa alla coda (dequeue)
 * @param _queue Coda da cui rimuovere
 * @param _value_out Puntatore dove scrivere il valore rimosso
 * @return QUEUE_SUCCESS se rimosso,
 *         QUEUE_ERROR_NULL se _queue è NULL,
 *         QUEUE_ERROR_EMPTY se la coda è vuota
 */
int queue_dequeue(queue _queue, int* _ptr_value_out);

/*
 * Restituisce l’elemento in testa senza rimuoverlo
 * @param _queue Coda da cui leggere
 * @param _value_out Puntatore dove scrivere il valore letto
 * @return QUEUE_SUCCESS se letto,
 *         QUEUE_ERROR_NULL se _queue è NULL,
 *         QUEUE_ERROR_EMPTY se la coda è vuota
 */
int queue_peek(queue _queue, int* _ptr_value_out);

/*
 * Verifica se la coda è vuota
 * @param _queue Coda da verificare
 * @return true se vuota, false altrimenti. Ritorna true anche se _queue è NULL
 */
bool queue_is_empty(queue _queue);

/*
 * Verifica se la coda è piena
 * @param _queue Coda da verificare
 * @return true se piena, false altrimenti. Ritorna false se _queue è NULL
 */
bool queue_is_full(queue _queue);
