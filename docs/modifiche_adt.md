# Modifiche agli ADT di Base - Riassunto

Questo documento riassume le principali modifiche apportate agli ADT di base utilizzati nel sistema DeliveryManager, con particolare attenzione al ruolo delle liste concatenate e alla presenza delle pile nel sistema.

## Panoramica degli ADT di Base

Il sistema DeliveryManager si basa su diversi ADT di base che sono stati adattati per soddisfare le esigenze specifiche del progetto:

1. **Grafo Orientato Pesato** (`weighted_direct_graph`): Rappresenta la rete stradale dell'area metropolitana
2. **Coda con Priorità** (`queue`): Gestisce i carichi nei centri di smistamento
3. **Array Dinamico** (`dynamic_array`): Memorizza collezioni di oggetti come veicoli, carichi e missioni
4. **Lista Concatenata** (`linked_list`): Supporta operazioni su percorsi e risultati di algoritmi sui grafi
5. **Pila** (`list_stack`): Presente ma non utilizzata attivamente nel sistema principale

## Modifiche all'ADT Grafo Orientato Pesato

### Modifiche Principali:

1. **Aggiunta del campo `data` nei nodi**: Permette di associare dati arbitrari (come punti di consegna o centri di smistamento) ai nodi del grafo.
2. **Funzioni di accesso ai dati dei nodi**: Consentono di manipolare i dati associati ai nodi in modo sicuro.
3. **Accesso diretto ai nodi**: Permette un accesso più efficiente ai dati dei nodi.

### Motivazione:

Queste modifiche consentono una migliore integrazione del grafo con il resto del sistema, permettendo di associare direttamente le entità del dominio (punti di consegna, centri di smistamento) ai nodi del grafo.

## Modifiche all'ADT Coda con Priorità

### Modifiche Principali:

1. **Aggiunta del campo `data` negli elementi**: Permette di associare dati arbitrari (come carichi o veicoli) agli elementi della coda.
2. **Funzioni di accesso ai dati**: Consentono di manipolare i dati associati agli elementi in modo sicuro.
3. **Gestione dinamica della capacità**: La coda si espande automaticamente quando necessario.

### Motivazione:

Queste modifiche rendono la coda più flessibile e adatta alla gestione di entità complesse come carichi e veicoli, mantenendo l'ordinamento per priorità.

## Modifiche all'ADT Array Dinamico

### Modifiche Principali:

1. **Supporto per dati generici**: L'array può memorizzare puntatori a qualsiasi tipo di dato.
2. **Funzioni di ricerca avanzate**: Permettono di trovare elementi in base a criteri specifici.
3. **Funzioni di ordinamento**: Consentono di ordinare gli elementi in base a diversi criteri.

### Motivazione:

Queste modifiche rendono l'array dinamico uno strumento versatile per la gestione di collezioni di oggetti nel sistema, facilitando operazioni come la ricerca e l'ordinamento.

## Ruolo delle Liste Concatenate nel Sistema

Le liste concatenate (`linked_list`) svolgono un ruolo fondamentale nel sistema DeliveryManager, nonostante non siano direttamente visibili nelle strutture dati principali. Sono utilizzate principalmente come strutture di supporto per:

### 1. Rappresentazione dei Percorsi nel Grafo

Le funzioni che calcolano percorsi nel grafo orientato pesato restituiscono il risultato come liste concatenate di ID di nodi:

```c
linked_list percorso = weighted_direct_graph_shortest_path(grafo, nodo_partenza, nodo_arrivo);
```

Questo permette di rappresentare in modo flessibile sequenze di nodi che formano un percorso, facilitando operazioni come:

- Attraversamento del percorso in ordine
- Conversione degli ID dei nodi in nomi di punti di consegna
- Calcolo del tempo totale di percorrenza

### 2. Risultati delle Visite del Grafo

Le funzioni di visita del grafo (DFS e BFS) utilizzano liste concatenate per memorizzare l'ordine di visita dei nodi:

```c
linked_list nodi_visitati = weighted_direct_graph_bfs(grafo, nodo_partenza);
```

Questo è fondamentale per analizzare la struttura della rete stradale e verificare la connettività tra i vari punti.

### 3. Implementazione di Algoritmi sui Grafi

Le liste concatenate sono utilizzate internamente nell'implementazione di algoritmi come Dijkstra per il calcolo dei percorsi più brevi, dove servono per memorizzare nodi visitati, predecessori, ecc.

### 4. Gestione dei Vicini di un Nodo

La funzione `weighted_direct_graph_neighbors` restituisce l'elenco dei nodi adiacenti a un dato nodo come una lista concatenata, facilitando l'esplorazione locale della rete stradale.

## Pile (Stack) nel Sistema

L'ADT `list_stack` (pila basata su lista concatenata) è presente nel sistema ma non viene utilizzato attivamente nelle funzionalità principali del DeliveryManager. Ecco i motivi:

### 1. Natura delle Operazioni del Sistema

Il sistema DeliveryManager si basa principalmente su operazioni che richiedono:

- Accesso prioritario agli elementi (gestito dalle code con priorità)
- Memorizzazione di collezioni di oggetti (gestita dagli array dinamici)
- Rappresentazione di percorsi e risultati di algoritmi (gestita dalle liste concatenate)

Queste operazioni non richiedono naturalmente l'uso di pile, che sono ottimizzate per operazioni LIFO (Last In, First Out).

### 2. Uso Interno nel Grafo

Sebbene non sia utilizzata direttamente nelle funzionalità principali, la pila è inclusa nel sistema perché potrebbe essere utilizzata internamente nell'implementazione di alcuni algoritmi sui grafi, come la visita DFS ricorsiva.

### 3. Potenziale Uso Futuro

La pila è stata mantenuta nel sistema per possibili estensioni future che potrebbero richiedere operazioni LIFO, come:

- Implementazione di algoritmi di backtracking per l'ottimizzazione dei percorsi
- Gestione di annullamenti di operazioni (undo)
- Implementazione di algoritmi ricorsivi iterativi

## Conclusioni

Le modifiche apportate agli ADT di base sono state guidate dall'obiettivo di creare un sistema flessibile, efficiente e ben integrato. In particolare:

1. **Integrazione dei Dati**: L'aggiunta di campi `data` nelle strutture di base permette di associare direttamente le entità del dominio alle strutture dati.

2. **Flessibilità**: Le modifiche rendono le strutture dati più adattabili a diverse esigenze, consentendo l'estensione del sistema con nuove funzionalità.

3. **Efficienza**: L'implementazione di algoritmi efficienti e la scelta delle strutture dati appropriate per ciascuna operazione garantiscono buone prestazioni anche con grandi volumi di dati.

4. **Modularità**: Le strutture dati di base sono progettate per essere modulari e riutilizzabili, facilitando la manutenzione e l'estensione del sistema.

Le liste concatenate svolgono un ruolo fondamentale come strutture di supporto per algoritmi sui grafi e rappresentazione di percorsi, mentre le pile, sebbene presenti, non sono attivamente utilizzate nelle funzionalità principali del sistema a causa della natura delle operazioni richieste.
