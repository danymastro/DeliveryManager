/*
 * queue.h
 *
 * Interfaccia di un Tipo di Dato Astratto (ADT) per una coda con priorità.
 * La coda con priorità è una struttura dati che mantiene gli elementi ordinati
 * in base alla loro priorità. Gli elementi con priorità più alta vengono estratti
 * prima degli elementi con priorità più bassa.
 */

#include <stdbool.h>
#include <stdlib.h>

typedef struct _priority_queue* priority_queue;

#define QUEUE_SUCCESS 0
#define QUEUE_ERROR_NULL -1
#define QUEUE_ERROR_ALLOC -2
#define QUEUE_ERROR_EMPTY -3

/*
 * Crea una nuova coda con priorità vuota.
 * @return Puntatore alla coda creata, oppure NULL se fallisce l'allocazione.
 */
priority_queue priority_queue_create();

/*
 * Distrugge la coda e libera la memoria.
 * @param _queue Puntatore al puntatore della coda da distruggere.
 *               Dopo la chiamata, *_queue sarà impostato a NULL.
 * @param _free_element Funzione per liberare la memoria degli elementi (può essere NULL).
 */
void priority_queue_destroy(priority_queue* _queue, void (*_free_element)(void*));

/*
 * Inserisce un elemento nella coda con la priorità specificata.
 * @param _queue Coda in cui inserire.
 * @param _element Puntatore all'elemento da inserire.
 * @param _priority Priorità dell'elemento (valori più alti indicano priorità maggiore).
 * @return QUEUE_SUCCESS se inserito,
 *         QUEUE_ERROR_NULL se _queue è NULL,
 *         QUEUE_ERROR_ALLOC se fallisce l'allocazione.
 */
int priority_queue_enqueue(priority_queue _queue, void* _element, int _priority);

/*
 * Estrae l'elemento con la priorità più alta dalla coda.
 * @param _queue Coda da cui estrarre.
 * @param _element_out Puntatore dove salvare il puntatore all'elemento estratto.
 * @return QUEUE_SUCCESS se estratto,
 *         QUEUE_ERROR_NULL se _queue o _element_out sono NULL,
 *         QUEUE_ERROR_EMPTY se la coda è vuota.
 */
int priority_queue_dequeue(priority_queue _queue, void** _element_out);

/*
 * Restituisce l'elemento con la priorità più alta senza rimuoverlo.
 * @param _queue Coda da cui leggere.
 * @param _element_out Puntatore dove salvare il puntatore all'elemento.
 * @return QUEUE_SUCCESS se trovato,
 *         QUEUE_ERROR_NULL se _queue o _element_out sono NULL,
 *         QUEUE_ERROR_EMPTY se la coda è vuota.
 */
int priority_queue_peek(priority_queue _queue, void** _element_out);

/*
 * Restituisce la dimensione della coda.
 * @param _queue Coda da interrogare.
 * @return Numero di elementi, oppure QUEUE_ERROR_NULL se _queue è NULL.
 */
int priority_queue_size(priority_queue _queue);

/*
 * Verifica se la coda è vuota.
 * @param _queue Coda da verificare.
 * @return true se vuota o NULL, false altrimenti.
 */
bool priority_queue_is_empty(priority_queue _queue);

/*
 * Svuota la coda, rimuovendo tutti gli elementi.
 * @param _queue Coda da svuotare.
 * @param _free_element Funzione per liberare la memoria degli elementi (può essere NULL).
 * @return QUEUE_SUCCESS se svuotata,
 *         QUEUE_ERROR_NULL se _queue è NULL.
 */
int priority_queue_clear(priority_queue _queue, void (*_free_element)(void*));

/*
 * Cerca un elemento nella coda utilizzando la funzione di confronto fornita.
 * @param _queue Coda in cui cercare.
 * @param _element Elemento da cercare.
 * @param _compare Funzione di confronto tra elementi.
 * @return true se l'elemento è presente, false altrimenti.
 */
bool priority_queue_contains(priority_queue _queue, void* _element, int (*_compare)(const void*, const void*));
