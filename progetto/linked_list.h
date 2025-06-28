/*
 * linked_list.h
 *
 * Interfaccia per una lista concatenata generica (basata su interi), implementata come
 * Abstract Data Type (ADT) con puntatori opachi per nascondere i dettagli interni.
 *
 * La lista supporta operazioni di inserimento, rimozione, accesso e ricerca. È progettata
 * per essere sicura, modulare e facile da utilizzare in applicazioni C che richiedono
 * strutture dati flessibili.
 *
 * Include inoltre un iteratore, con funzioni per creare, scorrere e distruggere l'iteratore.
 */

#include <stdbool.h>
#include <stdlib.h>

// Tipo astratto per lista concatenata
typedef struct linked_list* linked_list;

// Tipo astratto per iteratore su lista
typedef struct linked_list_iterator* linked_list_iterator;

// Codici di ritorno
#define LINKED_LIST_SUCCESS 0           // Operazione eseguita correttamente
#define LINKED_LIST_ERROR_NULL -1       // Puntatore NULL passato come parametro
#define LINKED_LIST_ERROR_ALLOC -2      // Errore di allocazione dinamica
#define LINKED_LIST_ERROR_EMPTY -3      // Operazione non valida su lista vuota
#define LINKED_LIST_ERROR_INDEX -4      // Indice fuori dai limiti della lista
#define LINKED_LIST_ERROR_NOT_FOUND -5  // Valore non trovato nella lista

/*
 * Crea una nuova lista vuota
 * @return Puntatore alla nuova lista, oppure NULL se la fallisce l'allocazione della memoria
 */
linked_list linked_list_create();

/*
 * Inserisce un elemento in testa alla lista
 * @param _list Lista in cui inserire
 * @param _value Valore da inserire
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_ALLOC se fallisce l'allocazione della memoria
 */
int linked_list_insert_front(linked_list _list, int _value);

/*
 * Inserisce un elemento in coda alla lista
 * @param _list Lista in cui inserire
 * @param _value Valore da inserire
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_ALLOC se fallisce l'allocazione della memoria
 */
int linked_list_insert_back(linked_list _list, int _value);

/*
 * Inserisce un elemento in posizione i (0-based)
 * @param _list Lista in cui inserire
 * @param _index Posizione di inserimento (0 = testa)
 * @param _value Valore da inserire
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_INDEX se _index è negativo o troppo grande,
 *         LINKED_LIST_ERROR_ALLOC se fallisce l'allocazione della memoria
 */
int linked_list_insert_at(linked_list _list, int _index, int _value);

/*
 * Recupera l'elemento in posizione i (0-based)
 * @param _list Lista da cui recuperare l'elemento
 * @param _index Posizione da leggere
 * @param _value_out Puntatore dove scrivere il valore
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_INDEX se _index è fuori dai limiti
 *         LINKED_LIST_ERROR_ALLOC se fallisce l'allocazione della memoria
 */
int linked_list_get_at(linked_list _list, int _index, int* _value_out);

/*
 * Recupera il primo elemento della lista
 * @param _list Lista da cui recuperare l'elemento
 * @param _value_out Puntatore dove scrivere il valore
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_EMPTY se la lista è vuota
 */
int linked_list_get_front(linked_list _list, int* _value_out);

/*
 * Recupera l'ultimo elemento della lista
 * @param _list Lista da cui recuperare l'elemento
 * @param _value_out Puntatore dove scrivere il valore
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_EMPTY se la lista è vuota
 */
int linked_list_get_back(linked_list _list, int* _value_out);

/*
 * Ricerca la prima occorrenza di un valore
 * @param _list Lista in cui cercare
 * @param _value Valore da cercare
 * @param _index_out Puntatore dove scrivere la posizione trovata
 * @return LINKED_LIST_SUCCESS se trovato,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_NOT_FOUND se il valore non è presente
 */
int linked_list_find(linked_list _list, int _value, int* _index_out);

/*
 * Rimuove un elemento in posizione i
 * @param _list Lista da cui rimuovere
 * @param _index Posizione dell'elemento da rimuovere
 * @return LINKED_LIST_SUCCESS se rimosso,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_INDEX se la posizione non è valida,
 *         LINKED_LIST_ERROR_EMPTY se la lista è vuota
 */
int linked_list_remove_at(linked_list _list, int _index);

/*
 * Rimuove la prima occorrenza di un valore
 * @param _list Lista da cui rimuovere
 * @param _value Valore da rimuovere
 * @return LINKED_LIST_SUCCESS se rimosso,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_NOT_FOUND se il valore non è presente
 */
int linked_list_remove_value(linked_list _list, int _value);

/*
 * Rimuove l'ultimo elemento della lista.
 * @param _list Lista da cui rimuovere.
 * @return LINKED_LIST_SUCCESS se rimosso,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_EMPTY se la lista è vuota.
 */
int linked_list_remove_back(linked_list _list);

/*
 * Restituisce il numero di elementi nella lista
 * @param _list Lista di cui ottenere la dimensione
 * @return Numero di elementi, oppure LINKED_LIST_ERROR_NULL se _list è NULL
 */
int linked_list_size(linked_list _list);

/*
 * Verifica se la lista è vuota
 * @param _list Lista da verificare
 * @return 1 se vuota, 0 se non vuota, LINKED_LIST_ERROR_NULL se _list è NULL
 */
int linked_list_is_empty(linked_list _list);

/*
 * Dealloca la lista e tutti i suoi nodi
 * @param _list Lista da deallocare
 */
void linked_list_destroy(linked_list* _list);

/*
 * Crea un iteratore per la lista
 * @param _list Lista su cui iterare
 * @return Puntatore all'iteratore, oppure NULL in caso di errore
 */
linked_list_iterator linked_list_iterator_create(linked_list _list);

/*
 * Verifica se ci sono ancora elementi da iterare
 * @param _iterator Iteratore da controllare
 * @return true se ci sono altri elementi, false se finiti o _iterator è NULL
 */
bool linked_list_iterator_has_next(linked_list_iterator _iterator);

/*
 * Restituisce il valore corrente e avanza l'iteratore
 * @param _iterator Iteratore da usare (presuppone che has_next sia stato verificato)
 * @return Il valore corrente dell'iterazione
 */
int linked_list_iterator_next(linked_list_iterator _iterator);

/*
 * Dealloca l'iteratore
 * @param _iterator Iteratore da distruggere
 */
void linked_list_iterator_destroy(linked_list_iterator* _iterator);

/*
 * Aggiunge un elemento alla fine della lista (alias di insert_back)
 * @param _list Lista in cui inserire
 * @param _value Valore da inserire
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_ALLOC se fallisce l'allocazione della memoria
 */
int linked_list_append(linked_list _list, int _value);

/*
 * Aggiunge un elemento all'inizio della lista (alias di insert_front)
 * @param _list Lista in cui inserire
 * @param _value Valore da inserire
 * @return LINKED_LIST_SUCCESS se ok,
 *         LINKED_LIST_ERROR_NULL se _list è NULL,
 *         LINKED_LIST_ERROR_ALLOC se fallisce l'allocazione della memoria
 */
int linked_list_prepend(linked_list _list, int _value);
