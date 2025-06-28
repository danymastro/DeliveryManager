/*
 * weighted_direct_graph.h
 *
 * Interfaccia di un grafo orientato pesato, rappresentato tramite matrice di adiacenza
 * dei pesi. I nodi sono identificati da interi (0, 1, ..., n-1). Il grafo consente
 * operazioni di inserimento nodi, gestione degli archi pesati, interrogazione dei vicini,
 * calcolo del percorso e delle visite (DFS, BFS).
 */

#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

typedef struct _weighted_direct_graph* weighted_direct_graph;
typedef int weighted_direct_graph_node_id;
typedef struct _weighted_direct_graph_node* Node;

// Codici di ritorno
#define WDG_SUCCESS 0                // Operazione completata correttamente
#define WDG_ERROR_NULL -1            // Puntatore NULL passato come parametro
#define WDG_ERROR_INVALID_ID -2      // Identificatore di nodo fuori range
#define WDG_ERROR_MEMORY -3          // Errore di allocazione o capacità superata

/*
 * Crea un nuovo grafo orientato pesato vuoto.
 * @return Puntatore al grafo creato, oppure NULL se fallisce l'allocazione della memoria.
 */
weighted_direct_graph weighted_direct_graph_create();

/*
 * Distrugge il grafo e libera tutta la memoria associata.
 * @param _graph Puntatore al puntatore del grafo da distruggere.
 *               Dopo la chiamata, *_graph sarà impostato a NULL.
 */
void weighted_direct_graph_destroy(weighted_direct_graph* _graph);

/*
 * Aggiunge un nuovo nodo al grafo.
 * @param _graph Grafo su cui operare.
 * @param _value Valore intero da associare al nodo.
 * @param _data Dati aggiuntivi da associare al nodo (può essere NULL).
 * @return Identificativo del nodo appena creato (>= 0),
 *         oppure WDG_ERROR_NULL se _graph è NULL,
 *         oppure WDG_ERROR_MEMORY se si raggiunge la capacità massima.
 */
weighted_direct_graph_node_id weighted_direct_graph_add_node(weighted_direct_graph _graph, int _value, void* _data);

/*
 * Restituisce il valore associato a un nodo.
 * @param _graph Grafo da interrogare.
 * @param _node Identificativo del nodo.
 * @param _value_out Puntatore dove scrivere il valore.
 * @return WDG_SUCCESS se ok,
 *         WDG_ERROR_NULL se _graph o _value_out sono NULL,
 *         WDG_ERROR_INVALID_ID se _node è fuori range.
 */
int weighted_direct_graph_get_value(weighted_direct_graph _graph, weighted_direct_graph_node_id _node, int* _value_out);

/*
 * Restituisce i dati associati a un nodo.
 * @param _graph Grafo da interrogare.
 * @param _node Identificativo del nodo.
 * @return Puntatore ai dati associati al nodo, oppure NULL se il nodo non esiste o non ha dati.
 */
void* weighted_direct_graph_get_node_data(weighted_direct_graph _graph, weighted_direct_graph_node_id _node);

/*
 * Imposta i dati associati a un nodo.
 * @param _graph Grafo da modificare.
 * @param _node Identificativo del nodo.
 * @param _data Nuovi dati da associare al nodo.
 * @param _free_data Funzione per liberare i dati precedenti (può essere NULL).
 * @return WDG_SUCCESS se ok,
 *         WDG_ERROR_NULL se _graph è NULL,
 *         WDG_ERROR_INVALID_ID se _node è fuori range.
 */
int weighted_direct_graph_set_node_data(weighted_direct_graph _graph, weighted_direct_graph_node_id _node, void* _data, void (*_free_data)(void*));

/*
 * Restituisce il nodo corrispondente all'identificativo.
 * @param _graph Grafo da interrogare.
 * @param _node Identificativo del nodo.
 * @return Puntatore al nodo, oppure NULL se il nodo non esiste.
 */
Node weighted_direct_graph_get_node(weighted_direct_graph _graph, weighted_direct_graph_node_id _node);

/*
 * Restituisce l'identificativo di un nodo.
 * @param _node Nodo di cui ottenere l'identificativo.
 * @return Identificativo del nodo, oppure WDG_ERROR_NULL se _node è NULL.
 */
weighted_direct_graph_node_id weighted_direct_graph_get_node_id(Node _node);

/*
 * Aggiunge un arco diretto con peso da _src a _dst.
 * @param _graph Grafo su cui operare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @param _weight Peso dell'arco.
 * @return WDG_SUCCESS se inserito,
 *         WDG_ERROR_NULL se _graph è NULL,
 *         WDG_ERROR_INVALID_ID se _src o _dst non sono nodi validi.
 */
int weighted_direct_graph_add_edge(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst, int _weight);

/*
 * Restituisce il peso dell'arco da _src a _dst.
 * @param _graph Grafo da interrogare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @param _weight_out Puntatore dove scrivere il peso.
 * @return 1 se l'arco esiste e il peso è stato scritto in *_weight_out,
 *         0 se non esiste arco tra _src e _dst,
 *         WDG_ERROR_NULL se _graph o _weight_out sono NULL,
 *         WDG_ERROR_INVALID_ID se _src o _dst non sono validi.
 */
int weighted_direct_graph_get_edge_weight(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst, int* _weight_out);

/*
 * Rimuove l'arco da _src a _dst.
 * @param _graph Grafo su cui operare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @return WDG_SUCCESS se rimosso correttamente,
 *         WDG_ERROR_NULL se _graph è NULL,
 *         WDG_ERROR_INVALID_ID se _src o _dst non sono validi.
 */
int weighted_direct_graph_remove_edge(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst);

/*
 * Restituisce il numero di nodi presenti nel grafo.
 * @param _graph Grafo da interrogare.
 * @return Numero di nodi (>= 0),
 *         oppure WDG_ERROR_NULL se _graph è NULL.
 */
int weighted_direct_graph_size(weighted_direct_graph _graph);

/*
 * Verifica se esiste un arco da _src a _dst.
 * @param _graph Grafo da interrogare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @return 1 se esiste l'arco,
 *         0 se non esiste,
 *         WDG_ERROR_NULL se _graph è NULL,
 *         WDG_ERROR_INVALID_ID se _src o _dst non sono validi.
 */
int weighted_direct_graph_adjacent(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst);

/*
 * Restituisce la lista dei vicini raggiungibili da _node.
 * @param _graph Grafo da interrogare.
 * @param _node Nodo da cui partire.
 * @return Lista dei nodi adiacenti, oppure NULL se:
 *         - _graph è NULL
 *         - _node è fuori range
 *         - errore di allocazione
 */
linked_list weighted_direct_graph_neighbors(weighted_direct_graph _graph, weighted_direct_graph_node_id _node);

/*
 * Visita in profondità (DFS) a partire da _start.
 * @param _graph Grafo da visitare.
 * @param _start Nodo iniziale.
 * @return Lista dei nodi visitati nell'ordine DFS,
 *         oppure NULL se _graph è NULL o _start non valido.
 */
linked_list weighted_direct_graph_dfs(weighted_direct_graph _graph, weighted_direct_graph_node_id _start);

/*
 * Visita in ampiezza (BFS) a partire da _start.
 * @param _graph Grafo da visitare.
 * @param _start Nodo iniziale.
 * @return Lista dei nodi visitati nell'ordine BFS,
 *         oppure NULL se _graph è NULL o _start non valido.
 */
linked_list weighted_direct_graph_bfs(weighted_direct_graph _graph, weighted_direct_graph_node_id _start);

/*
 * Verifica se esiste un percorso da _src a _dst.
 * @param _graph Grafo da analizzare.
 * @param _src Nodo di partenza.
 * @param _dst Nodo di arrivo.
 * @return 1 se esiste un percorso da _src a _dst,
 *         0 se non esiste,
 *         WDG_ERROR_NULL se _graph è NULL,
 *         WDG_ERROR_INVALID_ID se _src o _dst sono invalidi.
 */
int weighted_direct_graph_path_exists(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst);

/*
 * Restituisce un percorso da _src a _dst (se esiste).
 * @param _graph Grafo da interrogare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @return Lista ordinata di nodi nel percorso da _src a _dst,
 *         oppure NULL se non esiste o in caso di errore.
 */
linked_list weighted_direct_graph_get_path(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst);

/*
 * Calcola il peso totale di un percorso.
 * @param _graph Grafo contenente gli archi.
 * @param _path Lista di nodi che rappresentano un percorso valido.
 * @param _weight_out Puntatore dove salvare il peso complessivo.
 * @return WDG_SUCCESS se il percorso è valido e il peso calcolato,
 *         WDG_ERROR_NULL se _graph, _path o _weight_out sono NULL,
 *         WDG_ERROR_INVALID_ID se uno degli archi del percorso non esiste.
 */
int weighted_direct_graph_get_path_weight(weighted_direct_graph _graph, linked_list _path, int* _weight_out);

/*
 * Calcola il percorso più breve da _src a _dst usando l'algoritmo di Dijkstra.
 * @param _graph Grafo da interrogare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @return Lista ordinata di nodi nel percorso più breve da _src a _dst,
 *         oppure NULL se non esiste o in caso di errore.
 */
linked_list weighted_direct_graph_shortest_path(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst);

/*
 * Calcola il peso del percorso più breve da _src a _dst usando l'algoritmo di Dijkstra.
 * @param _graph Grafo da interrogare.
 * @param _src Nodo sorgente.
 * @param _dst Nodo destinazione.
 * @param _weight_out Puntatore dove salvare il peso complessivo.
 * @return WDG_SUCCESS se il percorso è valido e il peso calcolato,
 *         WDG_ERROR_NULL se _graph o _weight_out sono NULL,
 *         WDG_ERROR_INVALID_ID se _src o _dst sono invalidi.
 */
int weighted_direct_graph_shortest_path_weight(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst, int* _weight_out);
