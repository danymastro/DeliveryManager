# Centro di Smistamento - Documentazione Dettagliata

## Descrizione

L'ADT `CentroSmistamento` rappresenta un centro logistico nel sistema DeliveryManager dove i carichi vengono raccolti e assegnati ai veicoli per la consegna. Ogni centro di smistamento gestisce code di carichi e veicoli, ottimizzando l'assegnazione in base a priorità e capacità.

## Struttura Interna

```c
struct _centro_smistamento {
    int id;                       // Identificativo univoco
    char* nome;                   // Nome del centro di smistamento
    queue carichi_disponibili;    // Coda con priorità dei carichi disponibili
    queue veicoli_in_attesa;      // Coda con priorità dei veicoli in attesa
    struct _weighted_direct_graph_node* nodo;  // Nodo nel grafo dell'area metropolitana
    int carichi_gestiti;          // Contatore dei carichi totali gestiti
    int carichi_consegnati;       // Contatore dei carichi consegnati con successo
    int carichi_falliti;          // Contatore dei carichi con consegna fallita
};
```

## Modifiche Rispetto alle Specifiche Originali

### Aggiunta di Code Separate per Carichi e Veicoli

Nelle specifiche originali, era prevista solo una coda per i carichi disponibili. Nella versione implementata, sono state aggiunte due code distinte:

- `queue carichi_disponibili` per i carichi in attesa di assegnazione
- `queue veicoli_in_attesa` per i veicoli in attesa di ricevere carichi

**Motivazione:** La separazione delle code permette una gestione più flessibile e ottimizzata dell'assegnazione dei carichi ai veicoli, consentendo di implementare algoritmi di matching avanzati.

### Aggiunta di Contatori Statistici

Sono stati aggiunti i seguenti contatori:

- `carichi_gestiti` per tracciare il numero totale di carichi processati
- `carichi_consegnati` per tracciare il numero di carichi consegnati con successo
- `carichi_falliti` per tracciare il numero di carichi con consegna fallita

**Motivazione:** Questi contatori consentono di generare statistiche in tempo reale sull'efficienza operativa del centro di smistamento, senza dover ricalcolare i dati ogni volta.

### Riferimento Diretto al Nodo del Grafo

È stato aggiunto un puntatore diretto al nodo del grafo (`struct _weighted_direct_graph_node* nodo`) invece di utilizzare un semplice identificativo.

**Motivazione:** Questa modifica facilita l'accesso alla posizione del centro di smistamento nella rete stradale, migliorando l'efficienza del calcolo dei percorsi e dell'assegnazione delle missioni.

## Funzionalità Principali

### Gestione del Ciclo di Vita

- **`CentroSmistamento createCentroSmistamento(int _id, const char* _nome)`**: Crea un nuovo centro di smistamento con l'ID e il nome specificati.
- **`void destroyCentroSmistamento(CentroSmistamento* _centro)`**: Distrugge il centro di smistamento e libera la memoria associata.

### Accesso alle Proprietà

- **`int centrosmistamento_get_id(CentroSmistamento _centro)`**: Restituisce l'ID del centro di smistamento.
- **`const char* centrosmistamento_get_nome(CentroSmistamento _centro)`**: Restituisce il nome del centro di smistamento.
- **`struct _weighted_direct_graph_node* centrosmistamento_get_nodo(CentroSmistamento _centro)`**: Restituisce il nodo del grafo associato al centro di smistamento.
- **`int centrosmistamento_get_carichi_gestiti(CentroSmistamento _centro)`**: Restituisce il numero di carichi gestiti dal centro.
- **`int centrosmistamento_get_carichi_consegnati(CentroSmistamento _centro)`**: Restituisce il numero di carichi consegnati con successo.
- **`int centrosmistamento_get_carichi_falliti(CentroSmistamento _centro)`**: Restituisce il numero di carichi con consegna fallita.

### Modifica delle Proprietà

- **`void centrosmistamento_set_nodo(CentroSmistamento _centro, struct _weighted_direct_graph_node* _nodo)`**: Associa un nodo del grafo al centro di smistamento.
- **`void centrosmistamento_increment_carichi_gestiti(CentroSmistamento _centro)`**: Incrementa il contatore dei carichi gestiti.
- **`void centrosmistamento_increment_carichi_consegnati(CentroSmistamento _centro)`**: Incrementa il contatore dei carichi consegnati.
- **`void centrosmistamento_increment_carichi_falliti(CentroSmistamento _centro)`**: Incrementa il contatore dei carichi falliti.

### Gestione dei Carichi

- **`int centrosmistamento_add_carico(CentroSmistamento _centro, Carico _carico)`**: Aggiunge un carico alla coda del centro di smistamento.
- **`Carico centrosmistamento_get_next_carico(CentroSmistamento _centro)`**: Ottiene il prossimo carico disponibile (con la priorità più alta).
- **`int centrosmistamento_get_num_carichi(CentroSmistamento _centro)`**: Restituisce il numero di carichi disponibili nel centro.
- **`int centrosmistamento_has_carichi(CentroSmistamento _centro)`**: Verifica se ci sono carichi disponibili nel centro.

### Gestione dei Veicoli

- **`int centrosmistamento_add_veicolo(CentroSmistamento _centro, Veicolo _veicolo)`**: Aggiunge un veicolo alla coda del centro di smistamento.
- **`Veicolo centrosmistamento_get_next_veicolo(CentroSmistamento _centro)`**: Ottiene il prossimo veicolo disponibile (con la capacità più alta).
- **`int centrosmistamento_get_num_veicoli(CentroSmistamento _centro)`**: Restituisce il numero di veicoli in attesa nel centro.
- **`int centrosmistamento_has_veicoli(CentroSmistamento _centro)`**: Verifica se ci sono veicoli in attesa nel centro.

### Funzionalità Avanzate

- **`double centrosmistamento_get_efficienza(CentroSmistamento _centro)`**: Calcola un punteggio di efficienza per il centro di smistamento.
- **`int centrosmistamento_get_carico_medio(CentroSmistamento _centro)`**: Calcola il peso medio dei carichi gestiti dal centro.
- **`Carico* centrosmistamento_get_carichi_compatibili(CentroSmistamento _centro, Veicolo _veicolo, int* _num_carichi)`**: Ottiene un array di carichi compatibili con un veicolo specifico.

## Algoritmi di Assegnazione

### Assegnazione Basata su Priorità e Capacità

Il centro di smistamento implementa un algoritmo di assegnazione che ottimizza l'utilizzo dei veicoli e rispetta le priorità dei carichi:

1. I carichi sono ordinati per priorità nella coda `carichi_disponibili`
2. I veicoli sono ordinati per capacità nella coda `veicoli_in_attesa`
3. Quando un veicolo richiede carichi, l'algoritmo seleziona i carichi con la priorità più alta che possono essere trasportati dal veicolo, rispettando i vincoli di capacità

### Ottimizzazione del Carico

L'algoritmo di assegnazione cerca di ottimizzare l'utilizzo della capacità dei veicoli, assegnando più carichi a un singolo veicolo quando possibile:

```c
Veicolo veicolo = centrosmistamento_get_next_veicolo(centro);
int capacita_residua = veicolo_get_capacita(veicolo);
dynamic_array carichi_assegnati = dynamic_array_create();

while (centrosmistamento_has_carichi(centro) && capacita_residua > 0) {
    Carico carico = centrosmistamento_get_next_carico(centro);

    if (carico_get_peso(carico) <= capacita_residua) {
        dynamic_array_append(carichi_assegnati, carico);
        capacita_residua -= carico_get_peso(carico);
    } else {
        // Rimetti il carico nella coda se non può essere trasportato
        centrosmistamento_add_carico(centro, carico);
        break;
    }
}

// Crea una missione con i carichi assegnati
Missione missione = createMissione(next_id_missione++, veicolo);
for (int i = 0; i < dynamic_array_size(carichi_assegnati); i++) {
    Carico carico;
    dynamic_array_get_at(carichi_assegnati, i, (void**)&carico);
    missione_add_carico(missione, carico);
}

dynamic_array_destroy(&carichi_assegnati);
```

## Utilizzo nel Sistema DeliveryManager

Nel contesto del sistema DeliveryManager, l'ADT CentroSmistamento viene utilizzato per:

1. **Raccolta dei Carichi**: I carichi da consegnare vengono registrati e accodati nei centri di smistamento.

2. **Accodamento dei Veicoli**: I veicoli disponibili si registrano presso i centri di smistamento per ricevere carichi da consegnare.

3. **Assegnazione delle Missioni**: Il sistema utilizza i centri di smistamento per creare missioni di consegna, assegnando carichi ai veicoli in base a priorità e capacità.

4. **Monitoraggio delle Prestazioni**: I contatori statistici dei centri di smistamento vengono utilizzati per valutare l'efficienza operativa e generare report.

## Esempio di Utilizzo

```c
// Creazione di un centro di smistamento
CentroSmistamento centro = createCentroSmistamento(1, "Centro Principale");

// Associazione a un nodo del grafo
struct _weighted_direct_graph_node* nodo = /* ... */;
centrosmistamento_set_nodo(centro, nodo);

// Aggiunta di carichi
Carico carico1 = createCarico(1, 20, CARICO_STANDARD, destinazione1, 3);
Carico carico2 = createCarico(2, 15, CARICO_FRAGILE, destinazione2, 5);
centrosmistamento_add_carico(centro, carico1);
centrosmistamento_add_carico(centro, carico2);
centrosmistamento_increment_carichi_gestiti(centro);
centrosmistamento_increment_carichi_gestiti(centro);

// Aggiunta di veicoli
Veicolo veicolo1 = createVeicolo("VCL-101", 100);
Veicolo veicolo2 = createVeicolo("VCL-202", 150);
centrosmistamento_add_veicolo(centro, veicolo1);
centrosmistamento_add_veicolo(centro, veicolo2);

// Verifica della disponibilità
if (centrosmistamento_has_carichi(centro) && centrosmistamento_has_veicoli(centro)) {
    printf("Pronto per l'assegnazione di missioni\n");
}

// Ottenimento del prossimo veicolo e carico
Veicolo veicolo = centrosmistamento_get_next_veicolo(centro);
Carico carico = centrosmistamento_get_next_carico(centro);

// Aggiornamento delle statistiche
centrosmistamento_increment_carichi_consegnati(centro);

// Visualizzazione delle statistiche
printf("Carichi gestiti: %d\n", centrosmistamento_get_carichi_gestiti(centro));
printf("Carichi consegnati: %d\n", centrosmistamento_get_carichi_consegnati(centro));
printf("Efficienza: %.2f%%\n", centrosmistamento_get_efficienza(centro) * 100);

// Pulizia
destroyCentroSmistamento(&centro);
```

## Considerazioni sulla Progettazione

1. **Separazione delle Code**: La separazione delle code per carichi e veicoli permette una gestione più flessibile e ottimizzata dell'assegnazione.

2. **Contatori Statistici**: L'aggiunta di contatori statistici consente di monitorare le prestazioni del centro in tempo reale.

3. **Riferimenti Diretti**: L'uso di puntatori diretti alle entità associate migliora l'efficienza e la leggibilità del codice.

4. **Algoritmi di Ottimizzazione**: Gli algoritmi di assegnazione sono progettati per ottimizzare l'utilizzo dei veicoli e rispettare le priorità dei carichi.

## Conclusioni

Le modifiche apportate all'ADT CentroSmistamento rispetto alle specifiche originali sono state guidate dall'obiettivo di creare un sistema più efficiente e informativo. L'aggiunta di code separate per carichi e veicoli, contatori statistici e riferimenti diretti hanno contribuito a creare un sistema più completo e ottimizzato per la gestione delle consegne.
