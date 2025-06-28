# Coda con Priorità - Documentazione Dettagliata

## Descrizione

L'ADT `queue` implementa una coda con priorità, una struttura dati che mantiene gli elementi ordinati in base a una priorità associata. Nel sistema DeliveryManager, questa struttura è utilizzata principalmente nei centri di smistamento per gestire i carichi in attesa di essere assegnati ai veicoli, garantendo che i carichi con priorità più alta vengano processati per primi.

## Struttura Interna

```c
struct _queue_item {
    int priority;       // Priorità dell'elemento (più alto = maggiore priorità)
    int value;          // Valore intero associato all'elemento
    void* data;         // Dati aggiuntivi associati all'elemento
};

struct _queue {
    struct _queue_item* items;  // Array di elementi
    int size;                   // Numero di elementi attualmente nella coda
    int capacity;               // Capacità massima attuale
};
```

## Modifiche Rispetto all'Implementazione Standard

### Aggiunta del Campo `data`

La modifica principale rispetto a un'implementazione standard di una coda con priorità è l'aggiunta del campo `void* data` nella struttura dell'elemento. Questo permette di associare dati arbitrari a ciascun elemento della coda.

**Motivazione:** Nel contesto del DeliveryManager, questo campo è utilizzato per memorizzare puntatori a strutture come `Carico` o `Veicolo`, consentendo di accodare e recuperare facilmente queste entità in base alla loro priorità.

### Funzioni di Accesso ai Dati

Sono state aggiunte funzioni specifiche per accedere ai dati associati agli elementi della coda:

- `void* queue_peek_data(queue _queue)`
- `int queue_dequeue_with_data(queue _queue, int* _value_out, void** _data_out)`
- `int queue_enqueue_with_data(queue _queue, int _value, int _priority, void* _data)`

**Motivazione:** Queste funzioni consentono di manipolare i dati associati agli elementi in modo sicuro e controllato, facilitando l'integrazione della coda con il resto del sistema.

### Gestione Dinamica della Capacità

La coda è implementata con un array dinamico che si espande automaticamente quando necessario, consentendo di gestire un numero variabile di elementi senza conoscere a priori la dimensione massima.

**Motivazione:** Questa modifica rende la coda più flessibile e adatta a scenari reali dove il numero di carichi può variare significativamente nel tempo.

## Funzionalità Principali

### Gestione del Ciclo di Vita

- **`queue queue_create(int _initial_capacity)`**: Crea una nuova coda con la capacità iniziale specificata.
- **`void queue_destroy(queue* _queue)`**: Distrugge la coda e libera la memoria associata.

### Operazioni di Base

- **`int queue_enqueue(queue _queue, int _value, int _priority)`**: Inserisce un elemento nella coda con la priorità specificata.
- **`int queue_dequeue(queue _queue, int* _value_out)`**: Rimuove l'elemento con la priorità più alta dalla coda e restituisce il suo valore.
- **`int queue_peek(queue _queue, int* _value_out)`**: Restituisce il valore dell'elemento con la priorità più alta senza rimuoverlo dalla coda.

### Operazioni con Dati Associati

- **`int queue_enqueue_with_data(queue _queue, int _value, int _priority, void* _data)`**: Inserisce un elemento nella coda con la priorità e i dati specificati.
- **`int queue_dequeue_with_data(queue \_queue, int\* \_value_out, void** \_data_out)`\*\*: Rimuove l'elemento con la priorità più alta dalla coda e restituisce il suo valore e i dati associati.
- **`void* queue_peek_data(queue _queue)`**: Restituisce i dati associati all'elemento con la priorità più alta senza rimuoverlo dalla coda.

### Operazioni di Informazione

- **`int queue_size(queue _queue)`**: Restituisce il numero di elementi nella coda.
- **`int queue_is_empty(queue _queue)`**: Verifica se la coda è vuota.
- **`int queue_is_full(queue _queue)`**: Verifica se la coda ha raggiunto la sua capacità massima.

## Algoritmo di Ordinamento per Priorità

La coda implementa un algoritmo di ordinamento basato sulla priorità degli elementi:

1. Quando un nuovo elemento viene inserito nella coda (`queue_enqueue` o `queue_enqueue_with_data`), viene posizionato in modo da mantenere l'ordine decrescente di priorità.

2. L'inserimento utilizza un algoritmo di ricerca binaria per trovare la posizione corretta in O(log n), seguito da uno spostamento degli elementi per fare spazio al nuovo elemento in O(n).

3. Le operazioni di rimozione (`queue_dequeue` o `queue_dequeue_with_data`) estraggono sempre l'elemento in testa alla coda (quello con la priorità più alta) in O(1), seguito da uno spostamento degli elementi rimanenti in O(n).

**Miglioramento:** Rispetto a un'implementazione standard che potrebbe richiedere di riordinare l'intera coda dopo ogni inserimento, questa implementazione mantiene la coda sempre ordinata, ottimizzando le operazioni di estrazione.

## Utilizzo nel Sistema DeliveryManager

Nel contesto del sistema DeliveryManager, la coda con priorità è utilizzata principalmente in due scenari:

### 1. Gestione dei Carichi nei Centri di Smistamento

Ogni centro di smistamento mantiene una coda di carichi ordinati per priorità:

```c
// Nel centro di smistamento
queue carichi_disponibili = queue_create(INITIAL_CAPACITY);

// Aggiunta di un carico
queue_enqueue_with_data(carichi_disponibili, carico_get_id(carico), carico_get_priorita(carico), carico);

// Estrazione del carico con priorità più alta
int id_carico;
Carico carico;
queue_dequeue_with_data(carichi_disponibili, &id_carico, (void**)&carico);
```

La priorità dei carichi è determinata da diversi fattori:

1. La priorità intrinseca del carico (da 1 a 5)
2. La priorità del punto di consegna
3. L'orario di consegna richiesto

### 2. Gestione dei Veicoli in Attesa

I centri di smistamento possono anche mantenere code di veicoli in attesa di essere assegnati a missioni:

```c
// Nel centro di smistamento
queue veicoli_in_attesa = queue_create(INITIAL_CAPACITY);

// Aggiunta di un veicolo (priorità basata sulla capacità)
queue_enqueue_with_data(veicoli_in_attesa, veicolo_get_id(veicolo), veicolo_get_capacita(veicolo), veicolo);

// Estrazione del veicolo con la maggiore capacità
int id_veicolo;
Veicolo veicolo;
queue_dequeue_with_data(veicoli_in_attesa, &id_veicolo, (void**)&veicolo);
```

In questo caso, la priorità è basata sulla capacità del veicolo, in modo da assegnare prima i veicoli più capienti per ottimizzare il numero di carichi per missione.

## Esempio di Utilizzo

```c
// Creazione della coda
queue coda_priorita = queue_create(10);

// Inserimento di elementi con priorità e dati associati
Carico carico1 = createCarico(1, 20, CARICO_STANDARD, punto_consegna1, 3);
Carico carico2 = createCarico(2, 15, CARICO_FRAGILE, punto_consegna2, 5);
Carico carico3 = createCarico(3, 30, CARICO_REFRIGERATO, punto_consegna3, 4);

queue_enqueue_with_data(coda_priorita, 1, 3, carico1);  // Priorità 3
queue_enqueue_with_data(coda_priorita, 2, 5, carico2);  // Priorità 5
queue_enqueue_with_data(coda_priorita, 3, 4, carico3);  // Priorità 4

// Estrazione degli elementi in ordine di priorità
int id;
Carico carico;

// Primo elemento estratto: carico2 (priorità 5)
queue_dequeue_with_data(coda_priorita, &id, (void**)&carico);
printf("ID: %d, Priorità: %d\n", id, carico_get_priorita(carico));

// Secondo elemento estratto: carico3 (priorità 4)
queue_dequeue_with_data(coda_priorita, &id, (void**)&carico);
printf("ID: %d, Priorità: %d\n", id, carico_get_priorita(carico));

// Terzo elemento estratto: carico1 (priorità 3)
queue_dequeue_with_data(coda_priorita, &id, (void**)&carico);
printf("ID: %d, Priorità: %d\n", id, carico_get_priorita(carico));

// Pulizia
queue_destroy(&coda_priorita);
```

## Considerazioni sulla Progettazione

1. **Efficienza**: L'implementazione attuale offre un buon compromesso tra efficienza di inserimento e di estrazione. L'inserimento richiede O(n) nel caso peggiore, ma l'estrazione è sempre O(1) per il valore con la priorità più alta.

2. **Flessibilità**: L'aggiunta del campo `data` rende la coda molto flessibile, permettendo di gestire qualsiasi tipo di dato senza modificare la struttura interna.

3. **Gestione della Memoria**: La coda gestisce automaticamente l'espansione della memoria quando necessario, ma non si occupa di liberare la memoria dei dati associati agli elementi. Questa responsabilità è lasciata al chiamante.

4. **Integrazione con il Sistema**: La coda è stata progettata per integrarsi facilmente con il resto del sistema DeliveryManager, fornendo funzioni specifiche per la gestione dei dati associati agli elementi.

## Possibili Miglioramenti

1. **Implementazione con Heap**: Una possibile ottimizzazione sarebbe l'utilizzo di un heap binario per rappresentare la coda con priorità, riducendo la complessità dell'inserimento a O(log n).

2. **Supporto per la Rimozione Arbitraria**: Aggiungere funzioni per rimuovere elementi specifici dalla coda, non solo quello con la priorità più alta.

3. **Callback per la Liberazione dei Dati**: Implementare un sistema di callback per la liberazione automatica dei dati associati agli elementi quando vengono rimossi dalla coda o quando la coda viene distrutta.

## Conclusioni

Le modifiche apportate all'ADT `queue` rispetto a un'implementazione standard di una coda con priorità sono state guidate dall'obiettivo di creare una struttura dati flessibile e potente, in grado di gestire efficacemente i carichi e i veicoli nel sistema DeliveryManager. L'aggiunta del supporto per dati arbitrari associati agli elementi e l'implementazione di un algoritmo di ordinamento efficiente hanno contribuito a creare una struttura dati ben integrata con il resto del sistema e adatta alle esigenze specifiche della gestione delle consegne.
