# Grafo Orientato Pesato - Documentazione Dettagliata

## Descrizione

L'ADT `weighted_direct_graph` implementa un grafo orientato pesato dove i nodi sono identificati da interi e gli archi hanno un peso associato. Questa struttura dati è utilizzata nel sistema DeliveryManager per rappresentare la rete stradale dell'area metropolitana, dove i nodi rappresentano i punti di consegna e i centri di smistamento, mentre gli archi rappresentano i collegamenti stradali con i relativi tempi di percorrenza.

## Struttura Interna

```c
struct _weighted_direct_graph_node {
    int id;             // Identificativo del nodo
    int value;          // Valore associato al nodo
    void* data;         // Dati aggiuntivi associati al nodo
};

struct _weighted_direct_graph {
    int** adj_matrix;   // Matrice di adiacenza dei pesi
    struct _weighted_direct_graph_node* nodes;  // Array di nodi
    int size;           // Numero di nodi presenti
    int capacity;       // Capacità massima attuale
};
```

## Modifiche Rispetto all'Implementazione Standard

### Aggiunta del Campo `data` nei Nodi

La modifica principale rispetto a un'implementazione standard di un grafo orientato pesato è l'aggiunta del campo `void* data` nella struttura del nodo. Questo permette di associare dati arbitrari a ciascun nodo del grafo.

**Motivazione:** Nel contesto del DeliveryManager, questo campo è utilizzato per memorizzare puntatori a strutture come `PuntoConsegna` o `CentroSmistamento`, consentendo un accesso diretto a queste entità a partire dai nodi del grafo.

### Funzioni di Accesso ai Dati dei Nodi

Sono state aggiunte funzioni specifiche per accedere e modificare i dati associati ai nodi:

- `void* weighted_direct_graph_get_node_data(weighted_direct_graph _graph, weighted_direct_graph_node_id _node)`
- `int weighted_direct_graph_set_node_data(weighted_direct_graph _graph, weighted_direct_graph_node_id _node, void* _data, void (*_free_data)(void*))`

**Motivazione:** Queste funzioni consentono di manipolare i dati associati ai nodi in modo sicuro e controllato, facilitando l'integrazione del grafo con il resto del sistema.

### Accesso Diretto ai Nodi

È stata aggiunta la funzione `struct _weighted_direct_graph_node* weighted_direct_graph_get_node(weighted_direct_graph _graph, weighted_direct_graph_node_id _node)` per ottenere un puntatore diretto a un nodo del grafo.

**Motivazione:** Questa funzione permette un accesso più efficiente ai dati dei nodi quando si eseguono operazioni ripetute sullo stesso nodo, evitando ricerche multiple.

## Utilizzo delle Liste Concatenate nel Grafo

Le liste concatenate (`linked_list`) sono utilizzate estensivamente nel grafo per diverse funzionalità:

### 1. Rappresentazione dei Percorsi

Le funzioni che calcolano percorsi nel grafo restituiscono il risultato come liste concatenate di ID di nodi:

- `linked_list weighted_direct_graph_get_path(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst)`
- `linked_list weighted_direct_graph_shortest_path(weighted_direct_graph _graph, weighted_direct_graph_node_id _src, weighted_direct_graph_node_id _dst)`

**Motivazione:** Le liste concatenate sono ideali per rappresentare sequenze di nodi in un percorso, poiché consentono di attraversare il percorso in ordine e di manipolarlo facilmente (ad esempio, per convertire gli ID dei nodi in nomi di punti di consegna).

### 2. Risultati delle Visite

Le funzioni di visita del grafo (DFS e BFS) restituiscono i nodi visitati come liste concatenate:

- `linked_list weighted_direct_graph_dfs(weighted_direct_graph _graph, weighted_direct_graph_node_id _start)`
- `linked_list weighted_direct_graph_bfs(weighted_direct_graph _graph, weighted_direct_graph_node_id _start)`

**Motivazione:** Le liste concatenate permettono di mantenere l'ordine di visita dei nodi, che è importante per analizzare la struttura del grafo.

### 3. Elenco dei Vicini

La funzione `linked_list weighted_direct_graph_neighbors(weighted_direct_graph _graph, weighted_direct_graph_node_id _node)` restituisce l'elenco dei nodi adiacenti a un dato nodo come una lista concatenata.

**Motivazione:** Le liste concatenate sono una struttura flessibile per rappresentare insiemi di elementi di dimensione variabile, come l'insieme dei vicini di un nodo.

## Algoritmi Implementati

### Ricerca di Percorsi

1. **Esistenza di un Percorso**: `weighted_direct_graph_path_exists` verifica se esiste un percorso tra due nodi utilizzando una visita BFS.

2. **Calcolo di un Percorso**: `weighted_direct_graph_get_path` calcola un percorso (non necessariamente il più breve) tra due nodi utilizzando una visita BFS.

3. **Calcolo del Percorso Più Breve**: `weighted_direct_graph_shortest_path` implementa l'algoritmo di Dijkstra per trovare il percorso più breve tra due nodi.

4. **Calcolo del Peso di un Percorso**: `weighted_direct_graph_get_path_weight` calcola il peso totale di un percorso dato come lista di nodi.

5. **Calcolo del Peso del Percorso Più Breve**: `weighted_direct_graph_shortest_path_weight` calcola il peso del percorso più breve tra due nodi senza costruire esplicitamente il percorso.

### Visite del Grafo

1. **Visita in Profondità (DFS)**: `weighted_direct_graph_dfs` implementa una visita in profondità a partire da un nodo.

2. **Visita in Ampiezza (BFS)**: `weighted_direct_graph_bfs` implementa una visita in ampiezza a partire da un nodo.

## Gestione della Memoria

Il grafo implementa una gestione dinamica della memoria:

1. **Creazione Iniziale**: La matrice di adiacenza e l'array dei nodi sono inizialmente allocati con una capacità predefinita.

2. **Espansione Automatica**: Quando la capacità è esaurita, la struttura viene automaticamente ridimensionata utilizzando la funzione `expand_matrix`.

3. **Distruzione**: La funzione `weighted_direct_graph_destroy` libera tutta la memoria associata al grafo, inclusi i dati associati ai nodi se viene fornita una funzione di liberazione.

## Utilizzo nel Sistema DeliveryManager

Nel contesto del sistema DeliveryManager, il grafo orientato pesato è utilizzato per:

1. **Rappresentazione della Rete Stradale**: I nodi rappresentano punti di consegna e centri di smistamento, mentre gli archi rappresentano collegamenti stradali con i relativi tempi di percorrenza.

2. **Calcolo dei Percorsi**: Il sistema utilizza l'algoritmo di Dijkstra per calcolare il percorso più breve tra due punti, ottimizzando i tempi di consegna.

3. **Analisi della Connettività**: Le funzioni di visita del grafo sono utilizzate per verificare la connettività della rete stradale e identificare eventuali punti isolati.

## Esempio di Utilizzo

```c
// Creazione del grafo
weighted_direct_graph graph = weighted_direct_graph_create();

// Aggiunta di nodi (punti di consegna)
weighted_direct_graph_node_id node1 = weighted_direct_graph_add_node(graph, 1, punto_consegna1);
weighted_direct_graph_node_id node2 = weighted_direct_graph_add_node(graph, 2, punto_consegna2);
weighted_direct_graph_node_id node3 = weighted_direct_graph_add_node(graph, 3, punto_consegna3);

// Aggiunta di archi (collegamenti stradali)
weighted_direct_graph_add_edge(graph, node1, node2, 15); // 15 minuti da node1 a node2
weighted_direct_graph_add_edge(graph, node2, node3, 20); // 20 minuti da node2 a node3
weighted_direct_graph_add_edge(graph, node1, node3, 25); // 25 minuti da node1 a node3

// Calcolo del percorso più breve
linked_list path = weighted_direct_graph_shortest_path(graph, node1, node3);

// Calcolo del peso del percorso
int weight;
weighted_direct_graph_get_path_weight(graph, path, &weight);
printf("Tempo di percorrenza: %d minuti\n", weight);

// Pulizia
linked_list_destroy(&path);
weighted_direct_graph_destroy(&graph);
```

## Considerazioni sulla Progettazione

1. **Rappresentazione con Matrice di Adiacenza**: La scelta di utilizzare una matrice di adiacenza per rappresentare il grafo offre un accesso rapido (O(1)) agli archi, ma può essere inefficiente in termini di memoria per grafi sparsi. Questa scelta è appropriata per il contesto del DeliveryManager, dove il numero di punti di consegna è generalmente limitato e la rete stradale è relativamente densa.

2. **Utilizzo di Liste Concatenate per i Risultati**: L'utilizzo di liste concatenate per rappresentare percorsi e risultati di visite offre una gestione flessibile e intuitiva dei dati, facilitando l'integrazione con il resto del sistema.

3. **Supporto per Dati Arbitrari nei Nodi**: L'aggiunta del campo `data` nei nodi permette di integrare facilmente il grafo con le altre strutture dati del sistema, consentendo un accesso diretto alle entità associate ai nodi.

4. **Algoritmi Efficienti**: L'implementazione dell'algoritmo di Dijkstra per il calcolo dei percorsi più brevi garantisce prestazioni ottimali anche per grafi di grandi dimensioni.

## Conclusioni

Le modifiche apportate all'ADT `weighted_direct_graph` rispetto a un'implementazione standard sono state guidate dall'obiettivo di integrare efficacemente il grafo con il resto del sistema DeliveryManager. L'aggiunta del supporto per dati arbitrari nei nodi e l'utilizzo estensivo di liste concatenate per rappresentare percorsi e risultati di visite hanno contribuito a creare una struttura dati flessibile e potente, in grado di modellare efficacemente la rete stradale dell'area metropolitana e di supportare le operazioni di calcolo dei percorsi necessarie per ottimizzare le consegne.
