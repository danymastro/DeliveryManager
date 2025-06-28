/*
 * dynamic_array.h
 *
 * Interfaccia di un Tipo di Dato Astratto (ADT) per un array dinamico generico.
 *
 * L'array dinamico consente di gestire insiemi di dati con dimensione variabile,
 * offrendo un'alternativa flessibile agli array statici tradizionali.
 * La struttura cresce automaticamente al bisogno, grazie alla riallocazione
 * della memoria interna (realloc), mantenendo i dati già presenti.
 *
 * L'interfaccia fornisce operazioni per creare e distruggere l'array,
 * aggiungere e rimuovere elementi, accedere a una posizione specifica
 * e interrogare lo stato logico della struttura (vuota o meno, dimensione).
 */

#include <stdbool.h>
#include <stdlib.h>

typedef struct _dynamic_array* dynamic_array;

#define DYN_ARRAY_SUCCESS 0
#define DYN_ARRAY_ERROR_NULL -1
#define DYN_ARRAY_ERROR_ALLOC -2
#define DYN_ARRAY_ERROR_INDEX -3
#define DYN_ARRAY_ERROR_EMPTY -4

/*
 * Crea un nuovo array dinamico con capacità iniziale specificata
 * @param _initial_capacity Capacità iniziale (≥ 1)
 * @param _element_size Dimensione in byte di ciascun elemento
 * @return Puntatore all'array dinamico, oppure NULL in caso di errore
 */
dynamic_array dynamic_array_create(int _initial_capacity, size_t _element_size);

/*
 * Distrugge l'array dinamico e libera la memoria
 * @param _array Puntatore all'array dinamico da distruggere (sarà posto a NULL)
 * @param _free_element Funzione per liberare la memoria degli elementi (può essere NULL)
 */
void dynamic_array_destroy(dynamic_array* _array, void (*_free_element)(void*));

/*
 * Aggiunge un elemento in coda all'array
 * @param _array Array in cui inserire
 * @param _element Puntatore all'elemento da inserire
 * @return DYN_ARRAY_SUCCESS se inserito,
 *         DYN_ARRAY_ERROR_NULL se _array è NULL,
 *         DYN_ARRAY_ERROR_ALLOC se realloc fallisce
 */
int dynamic_array_append(dynamic_array _array, void* _element);

/*
 * Inserisce un elemento in posizione specifica (spostando gli elementi successivi)
 * @param _array Array in cui inserire
 * @param _index Indice di inserimento (0-based)
 * @param _element Puntatore all'elemento da inserire
 * @return DYN_ARRAY_SUCCESS se ok,
 *         DYN_ARRAY_ERROR_INDEX se l'indice non è valido,
 *         DYN_ARRAY_ERROR_ALLOC se realloc fallisce
 */
int dynamic_array_insert_at(dynamic_array _array, int _index, void* _element);

/*
 * Rimuove l'elemento in posizione specifica (spostando gli elementi successivi)
 * @param _array Array da cui rimuovere
 * @param _index Indice da rimuovere
 * @param _free_element Funzione per liberare la memoria dell'elemento (può essere NULL)
 * @return DYN_ARRAY_SUCCESS se rimosso,
 *         DYN_ARRAY_ERROR_INDEX se l'indice non è valido
 */
int dynamic_array_remove_at(dynamic_array _array, int _index, void (*_free_element)(void*));

/*
 * Recupera l'elemento in posizione i
 * @param _array Array da cui leggere
 * @param _index Indice da cui leggere
 * @return Puntatore all'elemento, oppure NULL se l'indice è fuori dai limiti
 */
void* dynamic_array_get_at(dynamic_array _array, int _index);

/*
 * Restituisce la dimensione logica (numero di elementi) dell'array
 * @param _array Array da cui leggere
 * @return Numero di elementi, oppure DYN_ARRAY_ERROR_NULL se _array è NULL
 */
int dynamic_array_size(dynamic_array _array);

/*
 * Verifica se l'array è vuoto
 * @param _array Array da verificare
 * @return true se vuoto o NULL, false altrimenti
 */
bool dynamic_array_is_empty(dynamic_array _array);

/*
 * Ordina gli elementi dell'array utilizzando la funzione di confronto fornita
 * @param _array Array da ordinare
 * @param _compare Funzione di confronto tra elementi
 * @return DYN_ARRAY_SUCCESS se ordinato,
 *         DYN_ARRAY_ERROR_NULL se _array o _compare sono NULL
 */
int dynamic_array_sort(dynamic_array _array, int (*_compare)(const void*, const void*));

/*
 * Cerca un elemento nell'array utilizzando la funzione di confronto fornita
 * @param _array Array in cui cercare
 * @param _element Elemento da cercare
 * @param _compare Funzione di confronto tra elementi
 * @return Indice dell'elemento se trovato, -1 altrimenti
 */
int dynamic_array_find(dynamic_array _array, void* _element, int (*_compare)(const void*, const void*));
