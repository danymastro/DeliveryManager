/*
 * weighted_direct_graph.c
 *
 * Implementazione di un grafo orientato pesato di interi come Tipo di Dato Astratto (ADT),
 * rappresentato tramite matrice di adiacenza dei pesi. I nodi sono identificati da interi
 * e ogni arco ha un peso associato. Supporta operazioni di creazione, accesso, inserimento,
 * rimozione, visite (DFS, BFS) e calcolo di percorsi e pesi.
 */

#include <stdlib.h>
#include "weighted_directed_graph.h"
#include "list_stack.h"
#include "list_queue.h"
#include <limits.h>
#include <string.h>

#define MAX_SIZE 100
#define INITIAL_CAPACITY 10
#define GROWTH_FACTOR 2
#define NO_EDGE 0
#define INFINITY_DISTANCE INT_MAX

struct _weighted_direct_graph_node {
    int id;             // Identificativo del nodo
    int value;          // Valore associato al nodo
    void* data;         // Dati aggiuntivi associati al nodo
};

struct _weighted_direct_graph {
    int** adj_matrix;   // Matrice di adiacenza dei pesi
    struct _weighted_direct_graph_node* nodes;        // Array di nodi
    int size;           // Numero di nodi presenti
    int capacity;       // Capacità massima attuale
};

// Funzione di utilità per inizializzare la matrice di adiacenza
static int** create_matrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    if (matrix == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
        if (matrix[i] == NULL) {
            // Pulizia in caso di errore
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

// Funzione di utilità per espandere la matrice di adiacenza
static int expand_matrix(weighted_direct_graph _graph, int new_capacity) {
    int** new_matrix = create_matrix(new_capacity);
    if (new_matrix == NULL) return WDG_ERROR_MEMORY;

    // Copia i valori dalla vecchia matrice
    for (int i = 0; i < _graph->size; i++) {
        for (int j = 0; j < _graph->size; j++) {
            new_matrix[i][j] = _graph->adj_matrix[i][j];
        }
    }

    // Libera la vecchia matrice
    for (int i = 0; i < _graph->capacity; i++) {
        free(_graph->adj_matrix[i]);
    }
    free(_graph->adj_matrix);

    _graph->adj_matrix = new_matrix;
    return WDG_SUCCESS;
}

weighted_direct_graph weighted_direct_graph_create() {
    weighted_direct_graph graph = (weighted_direct_graph)malloc(sizeof(struct _weighted_direct_graph));
    if (graph == NULL) return NULL;

    graph->adj_matrix = create_matrix(INITIAL_CAPACITY);
    if (graph->adj_matrix == NULL) {
        free(graph);
        return NULL;
    }

    graph->nodes = (struct _weighted_direct_graph_node*)malloc(INITIAL_CAPACITY * sizeof(struct _weighted_direct_graph_node));
    if (graph->nodes == NULL) {
        for (int i = 0; i < INITIAL_CAPACITY; i++) {
            free(graph->adj_matrix[i]);
        }
        free(graph->adj_matrix);
        free(graph);
        return NULL;
    }

    for (int i = 0; i < INITIAL_CAPACITY; i++) {
        graph->nodes[i].id = -1;
        graph->nodes[i].value = 0;
        graph->nodes[i].data = NULL;
    }

    graph->size = 0;
    graph->capacity = INITIAL_CAPACITY;
    return graph;
}

void weighted_direct_graph_destroy(weighted_direct_graph* _graph) {
    if (_graph == NULL || *_graph == NULL) return;

    // Libera i nodi
    for (int i = 0; i < (*_graph)->size; i++) {
        if ((*_graph)->nodes[i].data != NULL) {
            free((*_graph)->nodes[i].data);
        }
    }
    free((*_graph)->nodes);

    // Libera la matrice di adiacenza
    for (int i = 0; i < (*_graph)->capacity; i++) {
        free((*_graph)->adj_matrix[i]);
    }
    free((*_graph)->adj_matrix);

    free(*_graph);
    *_graph = NULL;
}

weighted_direct_graph_node_id weighted_direct_graph_add_node(weighted_direct_graph _graph, int _value, void* _data) {
    if (_graph == NULL) return WDG_ERROR_NULL;

    // Se necessario, espandi la capacità
    if (_graph->size >= _graph->capacity) {
        int new_capacity = _graph->capacity * GROWTH_FACTOR;
        
        // Espandi la matrice di adiacenza
        int result = expand_matrix(_graph, new_capacity);
        if (result != WDG_SUCCESS) return WDG_ERROR_MEMORY;

        // Espandi l'array dei nodi
        struct _weighted_direct_graph_node* new_nodes = (struct _weighted_direct_graph_node*)realloc(_graph->nodes, new_capacity * sizeof(struct _weighted_direct_graph_node));
        if (new_nodes == NULL) return WDG_ERROR_MEMORY;

        _graph->nodes = new_nodes;
        for (int i = _graph->capacity; i < new_capacity; i++) {
            _graph->nodes[i].id = -1;
            _graph->nodes[i].value = 0;
            _graph->nodes[i].data = NULL;
        }

        _graph->capacity = new_capacity;
    }

    // Crea il nuovo nodo
    struct _weighted_direct_graph_node new_node;
    new_node.id = _graph->size;
    new_node.value = _value;
    new_node.data = _data;
    
    _graph->nodes[_graph->size] = new_node;
    return _graph->size++;
}

int weighted_direct_graph_get_value(weighted_direct_graph _graph, weighted_direct_graph_node_id _node, int* _value_out) {
    if (_graph == NULL || _value_out == NULL) return WDG_ERROR_NULL;
    if (_node < 0 || _node >= _graph->size) return WDG_ERROR_INVALID_ID;

    *_value_out = _graph->nodes[_node].value;
    return WDG_SUCCESS;
}

void* weighted_direct_graph_get_node_data(weighted_direct_graph _graph, weighted_direct_graph_node_id _node) {
    if (_graph == NULL || _node < 0 || _node >= _graph->size) return NULL;
    return _graph->nodes[_node].data;
}

int weighted_direct_graph_set_node_data(weighted_direct_graph _graph, weighted_direct_graph_node_id _node, void* _data, void (*_free_data)(void*)) {
    if (_graph == NULL) return WDG_ERROR_NULL;
    if (_node < 0 || _node >= _graph->size) return WDG_ERROR_INVALID_ID;

    // Libera i dati precedenti se necessario
    if (_free_data != NULL && _graph->nodes[_node].data != NULL) {
        _free_data(_graph->nodes[_node].data);
    }

    _graph->nodes[_node].data = _data;
    return WDG_SUCCESS;
}

struct _weighted_direct_graph_node* weighted_direct_graph_get_node(weighted_direct_graph _graph, weighted_direct_graph_node_id _node) {
    if (_graph == NULL || _node < 0 || _node >= _graph->size) return NULL;
    return &_graph->nodes[_node];
}

weighted_direct_graph_node_id weighted_direct_graph_get_node_id(struct _weighted_direct_graph_node* _node) {
    if (_node == NULL) return WDG_ERROR_NULL;
    return _node->id;
}

int weighted_direct_graph_add_edge(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst, int _weight) {
    if (_graph == NULL) return WDG_ERROR_NULL;
    if (_src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return WDG_ERROR_INVALID_ID;
    if (_weight <= 0) return WDG_ERROR_INVALID_ID; // Il peso deve essere positivo

    _graph->adj_matrix[_src][_dst] = _weight;
    return WDG_SUCCESS;
}

int weighted_direct_graph_get_edge_weight(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst, int* _weight_out) {
    if (_graph == NULL || _weight_out == NULL) return WDG_ERROR_NULL;
    if (_src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return WDG_ERROR_INVALID_ID;

    *_weight_out = _graph->adj_matrix[_src][_dst];
    return (*_weight_out > 0) ? 1 : 0;
}

int weighted_direct_graph_remove_edge(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst) {
    if (_graph == NULL) return WDG_ERROR_NULL;
    if (_src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return WDG_ERROR_INVALID_ID;

    _graph->adj_matrix[_src][_dst] = NO_EDGE;
    return WDG_SUCCESS;
}

int weighted_direct_graph_size(weighted_direct_graph _graph) {
    if (_graph == NULL) return WDG_ERROR_NULL;
    return _graph->size;
}

int weighted_direct_graph_adjacent(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst) {
    if (_graph == NULL) return WDG_ERROR_NULL;
    if (_src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return WDG_ERROR_INVALID_ID;

    return (_graph->adj_matrix[_src][_dst] > 0) ? 1 : 0;
}

linked_list weighted_direct_graph_neighbors(weighted_direct_graph _graph, weighted_direct_graph_node_id _node) {
    if (_graph == NULL || _node < 0 || _node >= _graph->size) return NULL;

    linked_list neighbors = linked_list_create();
    if (neighbors == NULL) return NULL;

    for (int i = 0; i < _graph->size; i++) {
        if (_graph->adj_matrix[_node][i] > 0) {
            linked_list_append(neighbors, i);
        }
    }

    return neighbors;
}

// Funzione di utilità per la visita DFS ricorsiva
static void dfs_recursive(weighted_direct_graph _graph, weighted_direct_graph_node_id _node, bool* _visited, linked_list _result) {
    _visited[_node] = true;
    linked_list_append(_result, _node);

    for (int i = 0; i < _graph->size; i++) {
        if (_graph->adj_matrix[_node][i] > 0 && !_visited[i]) {
            dfs_recursive(_graph, i, _visited, _result);
        }
    }
}

linked_list weighted_direct_graph_dfs(weighted_direct_graph _graph, weighted_direct_graph_node_id _start) {
    if (_graph == NULL || _start < 0 || _start >= _graph->size) return NULL;

    bool* visited = (bool*)calloc(_graph->size, sizeof(bool));
    if (visited == NULL) return NULL;

    linked_list result = linked_list_create();
    if (result == NULL) {
        free(visited);
        return NULL;
    }

    dfs_recursive(_graph, _start, visited, result);
    free(visited);
    return result;
}

linked_list weighted_direct_graph_bfs(weighted_direct_graph _graph, weighted_direct_graph_node_id _start) {
    if (_graph == NULL || _start < 0 || _start >= _graph->size) return NULL;

    bool* visited = (bool*)calloc(_graph->size, sizeof(bool));
    if (visited == NULL) return NULL;

    linked_list result = linked_list_create();
    if (result == NULL) {
        free(visited);
        return NULL;
    }

    queue queue = queue_create(MAX_SIZE);
    if (queue == NULL) {
        free(visited);
        linked_list_destroy(&result);
        return NULL;
    }

    visited[_start] = true;
    queue_enqueue(queue, _start);

    while (!queue_is_empty(queue)) {
        int current;
        queue_dequeue(queue, &current);
        linked_list_append(result, current);

        for (int i = 0; i < _graph->size; i++) {
            if (_graph->adj_matrix[current][i] > 0 && !visited[i]) {
                visited[i] = true;
                queue_enqueue(queue, i);
            }
        }
    }

    queue_destroy(&queue);
    free(visited);
    return result;
}

int weighted_direct_graph_path_exists(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst) {
    if (_graph == NULL) return WDG_ERROR_NULL;
    if (_src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return WDG_ERROR_INVALID_ID;

    // Caso speciale: stesso nodo
    if (_src == _dst) return 1;

    bool* visited = (bool*)calloc(_graph->size, sizeof(bool));
    if (visited == NULL) return 0;

    queue queue = queue_create(MAX_SIZE);
    if (queue == NULL) {
        free(visited);
        return 0;
    }

    visited[_src] = true;
    queue_enqueue(queue, _src);

    while (!queue_is_empty(queue)) {
        int current;
        queue_dequeue(queue, &current);

        for (int i = 0; i < _graph->size; i++) {
            if (_graph->adj_matrix[current][i] > 0) {
                if (i == _dst) {
                    queue_destroy(&queue);
                    free(visited);
                    return 1;
                }

                if (!visited[i]) {
                    visited[i] = true;
                    queue_enqueue(queue, i);
                }
            }
        }
    }

    queue_destroy(&queue);
    free(visited);
    return 0;
}

// Funzione di utilità per ricostruire il percorso dai predecessori
static linked_list reconstruct_path(int* _predecessors, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst) {
    linked_list path = linked_list_create();
    if (path == NULL) return NULL;

    int current = _dst;
    while (current != -1) {
        linked_list_prepend(path, current);
        current = _predecessors[current];
    }

    return path;
}

linked_list weighted_direct_graph_get_path(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst) {
    if (_graph == NULL || _src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return NULL;

    // Caso speciale: stesso nodo
    if (_src == _dst) {
        linked_list path = linked_list_create();
        if (path == NULL) return NULL;
        linked_list_append(path, _src);
        return path;
    }

    bool* visited = (bool*)calloc(_graph->size, sizeof(bool));
    int* predecessors = (int*)malloc(_graph->size * sizeof(int));
    if (visited == NULL || predecessors == NULL) {
        free(visited);
        free(predecessors);
        return NULL;
    }

    for (int i = 0; i < _graph->size; i++) {
        predecessors[i] = -1;
    }

    queue queue = queue_create(MAX_SIZE);
    if (queue == NULL) {
        free(visited);
        free(predecessors);
        return NULL;
    }

    visited[_src] = true;
    queue_enqueue(queue, _src);

    bool found = false;
    while (!queue_is_empty(queue) && !found) {
        int current;
        queue_dequeue(queue, &current);

        for (int i = 0; i < _graph->size; i++) {
            if (_graph->adj_matrix[current][i] > 0 && !visited[i]) {
                visited[i] = true;
                predecessors[i] = current;
                queue_enqueue(queue, i);

                if (i == _dst) {
                    found = true;
                    break;
                }
            }
        }
    }

    queue_destroy(&queue);
    free(visited);

    if (!found) {
        free(predecessors);
        return NULL;
    }

    linked_list path = reconstruct_path(predecessors, _src, _dst);
    free(predecessors);
    return path;
}

int weighted_direct_graph_get_path_weight(weighted_direct_graph _graph, linked_list _path, int* _weight_out) {
    if (_graph == NULL || _path == NULL || _weight_out == NULL) return WDG_ERROR_NULL;

    int total_weight = 0;
    int path_size = linked_list_size(_path);
    
    if (path_size <= 1) {
        *_weight_out = 0;
        return WDG_SUCCESS;
    }

    int prev_node, curr_node;
    linked_list_get_at(_path, 0, &prev_node);

    for (int i = 1; i < path_size; i++) {
        linked_list_get_at(_path, i, &curr_node);
        
        if (prev_node < 0 || prev_node >= _graph->size || curr_node < 0 || curr_node >= _graph->size) {
            return WDG_ERROR_INVALID_ID;
        }
        
        int edge_weight = _graph->adj_matrix[prev_node][curr_node];
        if (edge_weight <= 0) {
            return WDG_ERROR_INVALID_ID; // Arco non esistente
        }
        
        total_weight += edge_weight;
        prev_node = curr_node;
    }

    *_weight_out = total_weight;
    return WDG_SUCCESS;
}

linked_list weighted_direct_graph_shortest_path(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst) {
    if (_graph == NULL || _src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return NULL;

    // Caso speciale: stesso nodo
    if (_src == _dst) {
        linked_list path = linked_list_create();
        if (path == NULL) return NULL;
        linked_list_append(path, _src);
        return path;
    }

    // Inizializzazione per Dijkstra
    int* distances = (int*)malloc(_graph->size * sizeof(int));
    int* predecessors = (int*)malloc(_graph->size * sizeof(int));
    bool* visited = (bool*)calloc(_graph->size, sizeof(bool));
    
    if (distances == NULL || predecessors == NULL || visited == NULL) {
        free(distances);
        free(predecessors);
        free(visited);
        return NULL;
    }

    // Inizializza distanze e predecessori
    for (int i = 0; i < _graph->size; i++) {
        distances[i] = INFINITY_DISTANCE;
        predecessors[i] = -1;
    }
    distances[_src] = 0;

    // Algoritmo di Dijkstra
    for (int count = 0; count < _graph->size - 1; count++) {
        // Trova il nodo con la distanza minima tra quelli non visitati
        int min_dist = INFINITY_DISTANCE;
        int min_index = -1;
        
        for (int v = 0; v < _graph->size; v++) {
            if (!visited[v] && distances[v] < min_dist) {
                min_dist = distances[v];
                min_index = v;
            }
        }
        
        // Se non ci sono più nodi raggiungibili
        if (min_index == -1) break;
        
        visited[min_index] = true;
        
        // Aggiorna le distanze dei nodi adiacenti
        for (int v = 0; v < _graph->size; v++) {
            int edge_weight = _graph->adj_matrix[min_index][v];
            if (!visited[v] && edge_weight > 0 && 
                distances[min_index] != INFINITY_DISTANCE && 
                distances[min_index] + edge_weight < distances[v]) {
                distances[v] = distances[min_index] + edge_weight;
                predecessors[v] = min_index;
            }
        }
    }
    
    free(distances);
    free(visited);
    
    // Se la destinazione non è raggiungibile
    if (predecessors[_dst] == -1 && _src != _dst) {
        free(predecessors);
        return NULL;
    }
    
    // Ricostruisci il percorso
    linked_list path = reconstruct_path(predecessors, _src, _dst);
    free(predecessors);
    return path;
}

int weighted_direct_graph_shortest_path_weight(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst, int* _weight_out) {
    if (_graph == NULL || _weight_out == NULL) return WDG_ERROR_NULL;
    if (_src < 0 || _src >= _graph->size || _dst < 0 || _dst >= _graph->size) return WDG_ERROR_INVALID_ID;

    // Caso speciale: stesso nodo
    if (_src == _dst) {
        *_weight_out = 0;
        return WDG_SUCCESS;
    }

    // Inizializzazione per Dijkstra
    int* distances = (int*)malloc(_graph->size * sizeof(int));
    bool* visited = (bool*)calloc(_graph->size, sizeof(bool));
    
    if (distances == NULL || visited == NULL) {
        free(distances);
        free(visited);
        return WDG_ERROR_MEMORY;
    }

    // Inizializza distanze
    for (int i = 0; i < _graph->size; i++) {
        distances[i] = INFINITY_DISTANCE;
    }
    distances[_src] = 0;

    // Algoritmo di Dijkstra
    for (int count = 0; count < _graph->size - 1; count++) {
        // Trova il nodo con la distanza minima tra quelli non visitati
        int min_dist = INFINITY_DISTANCE;
        int min_index = -1;
        
        for (int v = 0; v < _graph->size; v++) {
            if (!visited[v] && distances[v] < min_dist) {
                min_dist = distances[v];
                min_index = v;
            }
        }
        
        // Se non ci sono più nodi raggiungibili
        if (min_index == -1) break;
        
        visited[min_index] = true;
        
        // Aggiorna le distanze dei nodi adiacenti
        for (int v = 0; v < _graph->size; v++) {
            int edge_weight = _graph->adj_matrix[min_index][v];
            if (!visited[v] && edge_weight > 0 && 
                distances[min_index] != INFINITY_DISTANCE && 
                distances[min_index] + edge_weight < distances[v]) {
                distances[v] = distances[min_index] + edge_weight;
            }
        }
    }
    
    // Verifica se la destinazione è raggiungibile
    if (distances[_dst] == INFINITY_DISTANCE) {
        free(distances);
        free(visited);
        return WDG_ERROR_INVALID_ID; // Destinazione non raggiungibile
    }
    
    *_weight_out = distances[_dst];
    
    free(distances);
    free(visited);
    return WDG_SUCCESS;
}
