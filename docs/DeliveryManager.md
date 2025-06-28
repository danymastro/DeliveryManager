# DeliveryManager - Documentazione Dettagliata

## Descrizione

L'ADT DeliveryManager rappresenta il componente principale del sistema di gestione delle consegne automatizzate. Coordina tutte le operazioni tra i vari componenti (zone logistiche, punti di consegna, veicoli, carichi, missioni) e fornisce un'interfaccia unificata per la gestione dell'intero sistema.

## Struttura Interna

```c
struct DeliveryManager {
    weighted_direct_graph area_metropolitana;  // Grafo rappresentante la rete stradale
    dynamic_array missioni;                    // Array di tutte le missioni
    dynamic_array carichi;                     // Array di tutti i carichi
    dynamic_array veicoli;                     // Array di tutti i veicoli
    dynamic_array zone_logistiche;             // Array di tutte le zone logistiche
    dynamic_array centri_smistamento;          // Array di tutti i centri di smistamento
    int next_id_zona;                          // ID progressivo per le zone logistiche
    int next_id_punto;                         // ID progressivo per i punti di consegna
    int next_id_carico;                        // ID progressivo per i carichi
    int next_id_missione;                      // ID progressivo per le missioni
    int next_id_centro;                        // ID progressivo per i centri di smistamento
};
```

## Modifiche Rispetto alle Specifiche Originali

### Aggiunta di Contatori per ID Progressivi

Sono stati aggiunti i seguenti campi:

- `next_id_zona`
- `next_id_punto`
- `next_id_carico`
- `next_id_missione`
- `next_id_centro`

**Motivazione:** Questi contatori permettono la generazione automatica di ID univoci per le varie entità del sistema, evitando conflitti e semplificando la gestione. L'utente non deve preoccuparsi di assegnare ID univoci manualmente.

### Utilizzo di Array Dinamici per Tutte le Collezioni

Tutte le collezioni di entità (missioni, carichi, veicoli, zone logistiche, centri di smistamento) sono implementate come array dinamici.

**Motivazione:** Gli array dinamici offrono un buon compromesso tra efficienza di accesso e flessibilità nella gestione della memoria. Permettono di aggiungere e rimuovere elementi senza conoscere a priori la dimensione massima delle collezioni.

## Funzionalità Implementate

### Gestione di Base

- **`DeliveryManager createManager()`**: Crea una nuova istanza del gestore della rete logistica.
- **`void destroyManager(DeliveryManager* _manager)`**: Distrugge il gestore e libera tutta la memoria associata.

### Gestione Zone Logistiche e Punti di Consegna

- **`int createZonaLogistica(DeliveryManager manager, char* nome)`**: Crea una nuova zona logistica con il nome specificato.
- **`int createPuntoConsegna(DeliveryManager manager, char* nome, int priorita, int orario, TipoPuntoConsegna tipo, char* zona_logistica)`**: Crea un nuovo punto di consegna all'interno di una zona logistica esistente.
- **`int addCollegamento(DeliveryManager manager, char* partenza, char* arrivo, int tempo)`**: Aggiunge un collegamento tra due punti con un tempo di percorrenza specificato.
- **`char** getPercorsoBreve(DeliveryManager manager, char* partenza, char* arrivo)`\*\*: Calcola il percorso più breve tra due punti.

### Gestione Veicoli

- **`int createVeicolo(DeliveryManager manager, char* targa, int capacita)`**: Registra un nuovo veicolo nella flotta.
- **`int addVeicoloToCoda(DeliveryManager manager, char* targa, char* centro_smistamento)`**: Aggiunge un veicolo alla coda di un centro di smistamento.

### Gestione Carichi e Centri di Smistamento

- **`int createCentroSmistamento(DeliveryManager manager, char* nome)`**: Crea un nuovo centro di smistamento.
- **`int insertCarico(DeliveryManager manager, int peso, TipoCarico tipologia, char* punto_consegna, int priorita, char* centro_smistamento)`**: Inserisce un nuovo carico da consegnare.

### Gestione Missioni

- **`int addTask(DeliveryManager manager, Veicolo veicolo, Carico carico)`**: Assegna manualmente un carico a un veicolo.
- **`Missione addAutoTask(DeliveryManager manager, char* centro_smistamento)`**: Assegna automaticamente una missione a un veicolo disponibile.
- **`int registraEsitoMissione(DeliveryManager manager, int id_missione, StatoMissione stato, const char* nota)`**: Registra l'esito di una missione di consegna.

### Statistiche e Reporting

- **`void getStatistics(DeliveryManager manager)`**: Stampa a video le statistiche generali del sistema.
- **`double* getTempiMediPerTipologia(DeliveryManager manager)`**: Calcola i tempi medi di consegna per ciascuna tipologia di carico.
- **`double getCaricoMedioPerVeicolo(DeliveryManager manager)`**: Calcola il carico medio gestito da ciascun veicolo.
- **`int* getNumConsegnePerZona(DeliveryManager manager)`**: Calcola il numero di consegne per ciascuna zona logistica.

### Funzionalità Personalizzata (F8)

- **`double* calcolaEfficienzaVeicoli(DeliveryManager manager)`**: Calcola un punteggio di efficienza per ogni veicolo.

**Motivazione:** Questa funzionalità è stata aggiunta per fornire un modo di valutare le prestazioni dei veicoli basandosi su diversi fattori come il numero di consegne completate, il tempo medio di consegna, il carico medio trasportato e il rapporto tra consegne riuscite e fallite.

### Funzioni di Accesso (Aggiunte)

- **`Veicolo getVeicoloByTarga(DeliveryManager manager, char* targa)`**: Ottiene un veicolo data la sua targa.
- **`Carico getCaricoById(DeliveryManager manager, int id)`**: Ottiene un carico dato il suo ID.
- **`Missione getMissioneById(DeliveryManager manager, int id)`**: Ottiene una missione dato il suo ID.
- **`ZonaLogistica getZonaLogisticaByNome(DeliveryManager manager, char* nome)`**: Ottiene una zona logistica dato il suo nome.
- **`CentroSmistamento getCentroSmistamentoByNome(DeliveryManager manager, char* nome)`**: Ottiene un centro di smistamento dato il suo nome.
- **`PuntoConsegna getPuntoConsegnaByNome(DeliveryManager manager, char* nome)`**: Ottiene un punto di consegna dato il suo nome.

**Motivazione:** Queste funzioni di accesso facilitano il recupero delle entità del sistema in base ai loro identificativi, migliorando la leggibilità e la manutenibilità del codice.

## Algoritmi Chiave

### Assegnazione Automatica delle Missioni

L'algoritmo di assegnazione automatica delle missioni (`addAutoTask`) segue questi passaggi:

1. Verifica la disponibilità di veicoli e carichi nel centro di smistamento
2. Seleziona il veicolo con la maggiore capacità disponibile
3. Seleziona i carichi in ordine di priorità
4. Assegna i carichi al veicolo rispettando i vincoli di capacità
5. Crea una nuova missione e registra l'orario di inizio
6. Aggiorna lo stato del veicolo a "in viaggio"

**Miglioramento:** L'algoritmo originale è stato esteso per supportare l'assegnazione di più carichi a una singola missione, ottimizzando l'utilizzo dei veicoli.

### Calcolo del Percorso Più Breve

Il calcolo del percorso più breve (`getPercorsoBreve`) utilizza l'algoritmo di Dijkstra implementato nel grafo orientato pesato per:

1. Identificare i nodi di partenza e arrivo nel grafo
2. Calcolare il percorso più breve tra i due nodi
3. Convertire il percorso in una sequenza di nomi di punti di consegna

**Miglioramento:** L'implementazione utilizza liste concatenate per rappresentare i percorsi, consentendo una gestione efficiente dei risultati.

## Gestione degli Errori

Il DeliveryManager implementa un sistema robusto di gestione degli errori:

1. Controllo di validità dei parametri di input
2. Verifica dell'esistenza delle entità prima di operare su di esse
3. Controllo dei vincoli di capacità e compatibilità
4. Restituzione di codici di errore specifici per facilitare il debugging

**Miglioramento:** Il sistema di gestione degli errori è stato reso più dettagliato rispetto alle specifiche originali, fornendo informazioni precise sulla natura degli errori.

## Esempi di Utilizzo

```c
// Creazione del manager
DeliveryManager manager = createManager();

// Creazione di zone logistiche e punti di consegna
createZonaLogistica(manager, "Centro Storico");
createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");

// Registrazione di un veicolo
createVeicolo(manager, "VCL-101", 100);

// Inserimento di un carico
insertCarico(manager, 20, CARICO_STANDARD, "Farmacia Centrale", 3, "Centro Principale");

// Accodamento di un veicolo
addVeicoloToCoda(manager, "VCL-101", "Centro Principale");

// Assegnazione automatica di una missione
Missione missione = addAutoTask(manager, "Centro Principale");

// Registrazione dell'esito di una missione
registraEsitoMissione(manager, missione_get_id(missione), STATO_MISSIONE_COMPLETATA, "Consegna completata con successo");

// Visualizzazione delle statistiche
getStatistics(manager);

// Pulizia finale
destroyManager(&manager);
```

## Considerazioni sulla Progettazione

1. **Modularità**: Il DeliveryManager è progettato per essere modulare, delegando le operazioni specifiche ai rispettivi ADT (veicolo, carico, missione, ecc.).

2. **Gestione degli Errori**: Tutte le funzioni restituiscono codici di errore specifici per facilitare il debugging e la gestione delle eccezioni.

3. **Flessibilità**: Il sistema può essere facilmente esteso con nuove funzionalità grazie alla struttura modulare.

4. **Efficienza**: L'uso di strutture dati appropriate (grafi per la rete stradale, code con priorità per i carichi) garantisce prestazioni ottimali anche con grandi volumi di dati.

5. **Generazione Automatica di ID**: L'implementazione di contatori progressivi semplifica la gestione delle entità e garantisce l'unicità degli identificativi.

## Conclusioni

Le modifiche apportate all'ADT DeliveryManager rispetto alle specifiche originali sono state guidate dall'obiettivo di creare un sistema più robusto, flessibile ed efficiente. L'aggiunta di contatori per la generazione automatica di ID, l'implementazione di funzioni di accesso avanzate e l'estensione delle funzionalità di base hanno contribuito a creare un sistema più completo e utilizzabile in scenari reali.
