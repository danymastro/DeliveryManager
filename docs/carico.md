# Carico - Documentazione Dettagliata

## Descrizione

L'ADT `Carico` rappresenta un pacco da consegnare nel sistema DeliveryManager. Ogni carico è caratterizzato da un identificativo univoco, un peso, una tipologia, una destinazione, una priorità e altre informazioni relative alla sua gestione e tracciamento.

## Struttura Interna

```c
typedef enum {
    CARICO_STANDARD,
    CARICO_FRAGILE,
    CARICO_REFRIGERATO
} TipoCarico;

typedef enum {
    STATO_CARICO_IN_ATTESA,
    STATO_CARICO_ASSEGNATO,
    STATO_CARICO_IN_CONSEGNA,
    STATO_CARICO_CONSEGNATO,
    STATO_CARICO_FALLITO
} StatoCarico;

struct _carico {
    int id;                       // Identificativo univoco
    int peso;                     // Peso in kg
    TipoCarico tipologia;         // Tipologia (standard, fragile, refrigerato)
    PuntoConsegna destinazione;   // Punto di consegna di destinazione
    int priorita;                 // Priorità (1-5, dove 5 è la più alta)
    Missione missione;            // Missione associata al carico
    CentroSmistamento centro;     // Centro di smistamento di origine
    StatoCarico stato;            // Stato attuale del carico
    time_t data_creazione;        // Data di creazione del carico
    time_t data_consegna;         // Data di consegna del carico
};
```

## Modifiche Rispetto alle Specifiche Originali

### Aggiunta di Stati Dettagliati

Nelle specifiche originali, non era prevista una gestione esplicita dello stato del carico. È stata aggiunta l'enumerazione `StatoCarico` per tracciare il ciclo di vita del carico:

- `STATO_CARICO_IN_ATTESA`: Il carico è in attesa di essere assegnato a un veicolo
- `STATO_CARICO_ASSEGNATO`: Il carico è stato assegnato a un veicolo ma non è ancora in consegna
- `STATO_CARICO_IN_CONSEGNA`: Il carico è in fase di consegna
- `STATO_CARICO_CONSEGNATO`: Il carico è stato consegnato con successo
- `STATO_CARICO_FALLITO`: La consegna del carico è fallita

**Motivazione:** L'aggiunta di stati dettagliati permette di monitorare con precisione il ciclo di vita del carico, facilitando la generazione di statistiche e il tracciamento delle consegne.

### Aggiunta di Timestamp

Sono stati aggiunti i campi `data_creazione` e `data_consegna` per registrare i tempi di creazione e consegna del carico.

**Motivazione:** Questi timestamp consentono di calcolare statistiche precise sui tempi di consegna, valutare l'efficienza del sistema e monitorare il rispetto delle scadenze.

### Puntatori Diretti alle Entità Associate

Invece di utilizzare semplici identificativi, sono stati aggiunti puntatori diretti alle entità associate:

- `PuntoConsegna destinazione` invece di un semplice ID
- `Missione missione` invece di un semplice ID
- `CentroSmistamento centro` invece di un semplice ID

**Motivazione:** Questa modifica facilita l'accesso alle entità associate senza dover eseguire ricerche ripetute, migliorando l'efficienza e la leggibilità del codice.

## Funzionalità Principali

### Gestione del Ciclo di Vita

- **`Carico createCarico(int _id, int _peso, TipoCarico _tipologia, PuntoConsegna _destinazione, int _priorita)`**: Crea un nuovo carico con i parametri specificati.
- **`void destroyCarico(Carico* _carico)`**: Distrugge il carico e libera la memoria associata.

### Accesso alle Proprietà

- **`int carico_get_id(Carico _carico)`**: Restituisce l'ID del carico.
- **`int carico_get_peso(Carico _carico)`**: Restituisce il peso del carico in kg.
- **`TipoCarico carico_get_tipologia(Carico _carico)`**: Restituisce la tipologia del carico.
- **`PuntoConsegna carico_get_destinazione(Carico _carico)`**: Restituisce il punto di consegna di destinazione.
- **`int carico_get_priorita(Carico _carico)`**: Restituisce la priorità del carico.
- **`Missione carico_get_missione(Carico _carico)`**: Restituisce la missione associata al carico.
- **`CentroSmistamento carico_get_centro(Carico _carico)`**: Restituisce il centro di smistamento di origine.
- **`StatoCarico carico_get_stato(Carico _carico)`**: Restituisce lo stato attuale del carico.
- **`time_t carico_get_data_creazione(Carico _carico)`**: Restituisce la data di creazione del carico.
- **`time_t carico_get_data_consegna(Carico _carico)`**: Restituisce la data di consegna del carico.

### Modifica delle Proprietà

- **`void carico_set_missione(Carico _carico, Missione _missione)`**: Associa una missione al carico.
- **`void carico_set_centro(Carico _carico, CentroSmistamento _centro)`**: Associa un centro di smistamento al carico.
- **`void carico_set_stato(Carico _carico, StatoCarico _stato)`**: Aggiorna lo stato del carico.
- **`void carico_set_data_consegna(Carico _carico, time_t _data_consegna)`**: Imposta la data di consegna del carico.

### Funzionalità Avanzate

- **`int carico_is_consegnato(Carico _carico)`**: Verifica se il carico è stato consegnato.
- **`int carico_is_in_consegna(Carico _carico)`**: Verifica se il carico è in fase di consegna.
- **`int carico_is_in_attesa(Carico _carico)`**: Verifica se il carico è in attesa di assegnazione.
- **`int carico_get_tempo_consegna(Carico _carico)`**: Calcola il tempo di consegna in secondi.
- **`char* carico_get_tipologia_string(Carico _carico)`**: Restituisce una stringa rappresentante la tipologia del carico.
- **`char* carico_get_stato_string(Carico _carico)`**: Restituisce una stringa rappresentante lo stato del carico.

## Gestione delle Priorità

La priorità del carico è un valore intero compreso tra 1 e 5, dove 5 rappresenta la priorità più alta. La priorità influisce sull'ordine in cui i carichi vengono assegnati ai veicoli nei centri di smistamento.

Nei centri di smistamento, i carichi vengono ordinati in base alla priorità utilizzando una coda con priorità. Quando un veicolo richiede carichi da consegnare, riceve prima quelli con priorità più alta.

## Stati del Carico

Il ciclo di vita di un carico attraversa i seguenti stati:

1. **IN_ATTESA**: Il carico è stato registrato nel sistema e si trova in un centro di smistamento in attesa di essere assegnato a un veicolo.

2. **ASSEGNATO**: Il carico è stato assegnato a un veicolo ma la missione di consegna non è ancora iniziata.

3. **IN_CONSEGNA**: Il carico è in fase di consegna, il veicolo associato è in viaggio verso la destinazione.

4. **CONSEGNATO**: Il carico è stato consegnato con successo alla destinazione.

5. **FALLITO**: La consegna del carico è fallita per qualche motivo (es. indirizzo errato, danneggiamento, ecc.).

## Utilizzo nel Sistema DeliveryManager

Nel contesto del sistema DeliveryManager, l'ADT Carico viene utilizzato per:

1. **Registrazione di Nuovi Carichi**: Quando un nuovo carico viene inserito nel sistema, viene creata un'istanza di `Carico` e aggiunta al centro di smistamento specificato.

2. **Assegnazione ai Veicoli**: I carichi vengono assegnati ai veicoli in base alla loro priorità e compatibilità.

3. **Tracciamento delle Consegne**: Il sistema monitora lo stato di ciascun carico per verificare il completamento delle consegne.

4. **Generazione di Statistiche**: I dati dei carichi vengono utilizzati per generare statistiche sui tempi di consegna, sul carico medio per veicolo, ecc.

## Esempio di Utilizzo

```c
// Creazione di un carico
PuntoConsegna destinazione = getPuntoConsegnaByNome(manager, "Farmacia Centrale");
Carico carico = createCarico(1, 20, CARICO_STANDARD, destinazione, 3);

// Associazione a un centro di smistamento
CentroSmistamento centro = getCentroSmistamentoByNome(manager, "Centro Principale");
carico_set_centro(carico, centro);

// Verifica dello stato
printf("Stato carico: %s\n", carico_get_stato_string(carico));

// Assegnazione a una missione
Missione missione = getMissioneById(manager, 1);
carico_set_missione(carico, missione);
carico_set_stato(carico, STATO_CARICO_ASSEGNATO);

// Inizio della consegna
carico_set_stato(carico, STATO_CARICO_IN_CONSEGNA);

// Completamento della consegna
carico_set_stato(carico, STATO_CARICO_CONSEGNATO);
carico_set_data_consegna(carico, time(NULL));

// Calcolo del tempo di consegna
int tempo_consegna = carico_get_tempo_consegna(carico);
printf("Tempo di consegna: %d secondi\n", tempo_consegna);

// Pulizia
destroyCarico(&carico);
```

## Considerazioni sulla Progettazione

1. **Tracciamento Temporale**: L'aggiunta dei timestamp permette di calcolare statistiche precise sui tempi di consegna e valutare l'efficienza del sistema.

2. **Gestione dello Stato**: L'implementazione di stati dettagliati consente di monitorare il ciclo di vita dei carichi e generare report accurati.

3. **Riferimenti Diretti**: L'uso di puntatori diretti alle entità associate migliora l'efficienza e la leggibilità del codice.

4. **Flessibilità**: La struttura dell'ADT Carico è stata progettata per essere flessibile e adattabile a diverse esigenze, consentendo l'aggiunta di nuove funzionalità in futuro.

## Conclusioni

Le modifiche apportate all'ADT Carico rispetto alle specifiche originali sono state guidate dall'obiettivo di creare un sistema più informativo e tracciabile. L'aggiunta di stati dettagliati, timestamp e riferimenti diretti hanno contribuito a creare un sistema più completo e utilizzabile in scenari reali.
