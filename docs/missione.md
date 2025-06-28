# Missione - Documentazione Dettagliata

## Descrizione

L'ADT Missione rappresenta un'attività di consegna assegnata a un veicolo nel sistema DeliveryManager. Una missione può contenere uno o più carichi da consegnare e tiene traccia dello stato della consegna, dei tempi di inizio e fine, e di eventuali note sull'esito.

## Struttura Interna

```c
typedef enum {
    STATO_MISSIONE_IN_CORSO,
    STATO_MISSIONE_COMPLETATA,
    STATO_MISSIONE_FALLITA
} StatoMissione;

struct _missione {
    int id;                  // Identificativo univoco
    Veicolo veicolo;         // Veicolo assegnato alla missione
    dynamic_array carichi;   // Array dinamico dei carichi associati
    StatoMissione stato;     // Stato attuale della missione
    time_t data_inizio;      // Data di inizio della missione
    time_t data_fine;        // Data di fine della missione
    char* nota;              // Nota testuale sulla missione
};
```

## Modifiche Rispetto alle Specifiche Originali

### Supporto per Più Carichi

Nelle specifiche originali, una missione era associata a un singolo carico. Nella versione implementata, è stato aggiunto un array dinamico (`dynamic_array carichi`) per gestire più carichi in una singola missione.

**Motivazione:** Questa modifica ottimizza l'utilizzo dei veicoli permettendo di consegnare più carichi con una sola missione, riducendo il numero di viaggi necessari e migliorando l'efficienza complessiva del sistema.

### Aggiunta di Timestamp

Sono stati aggiunti i campi `data_inizio` e `data_fine` per tracciare con precisione i tempi di inizio e fine della missione.

**Motivazione:** Questi timestamp permettono di calcolare statistiche precise sui tempi di consegna, valutare l'efficienza dei veicoli e monitorare il rispetto delle scadenze.

### Campo Nota

È stato aggiunto il campo `nota` per memorizzare informazioni testuali sull'esito della missione.

**Motivazione:** Questo campo consente di registrare dettagli specifici sull'esito della missione, come problemi incontrati durante la consegna o informazioni aggiuntive utili per l'analisi successiva.

## Funzionalità Principali

### Gestione del Ciclo di Vita

- **`Missione createMissione(int _id, Veicolo _veicolo)`**: Crea una nuova missione con l'ID e il veicolo specificati.
- **`void destroyMissione(Missione* _missione)`**: Distrugge la missione e libera la memoria associata.

### Accesso alle Proprietà

- **`int missione_get_id(Missione _missione)`**: Restituisce l'ID della missione.
- **`Veicolo missione_get_veicolo(Missione _missione)`**: Restituisce il veicolo associato alla missione.
- **`StatoMissione missione_get_stato(Missione _missione)`**: Restituisce lo stato attuale della missione.
- **`time_t missione_get_data_inizio(Missione _missione)`**: Restituisce la data di inizio della missione.
- **`time_t missione_get_data_fine(Missione _missione)`**: Restituisce la data di fine della missione.
- **`const char* missione_get_nota(Missione _missione)`**: Restituisce la nota associata alla missione.
- **`dynamic_array missione_get_carichi(Missione _missione)`**: Restituisce l'array dei carichi associati alla missione.

### Modifica delle Proprietà

- **`void missione_set_stato(Missione _missione, StatoMissione _stato)`**: Aggiorna lo stato della missione.
- **`void missione_set_data_fine(Missione _missione, time_t _data_fine)`**: Imposta la data di fine della missione.
- **`void missione_set_nota(Missione _missione, const char* _nota)`**: Imposta la nota associata alla missione.

### Gestione dei Carichi

- **`int missione_add_carico(Missione _missione, Carico _carico)`**: Aggiunge un carico alla missione.
- **`int missione_remove_carico(Missione _missione, Carico _carico)`**: Rimuove un carico dalla missione.
- **`int missione_get_num_carichi(Missione _missione)`**: Restituisce il numero di carichi associati alla missione.
- **`Carico missione_get_carico_at(Missione _missione, int _index)`**: Restituisce il carico all'indice specificato.

### Funzionalità Avanzate

- **`int missione_is_completata(Missione _missione)`**: Verifica se la missione è stata completata.
- **`int missione_is_fallita(Missione _missione)`**: Verifica se la missione è fallita.
- **`int missione_is_in_corso(Missione _missione)`**: Verifica se la missione è in corso.
- **`int missione_get_durata(Missione _missione)`**: Calcola la durata della missione in secondi.
- **`int missione_get_peso_totale(Missione _missione)`**: Calcola il peso totale dei carichi della missione.
- **`char* missione_get_stato_string(Missione _missione)`**: Restituisce una stringa rappresentante lo stato della missione.

## Stati della Missione

La missione può trovarsi in uno dei seguenti stati:

1. **IN_CORSO**: La missione è stata assegnata e il veicolo è in viaggio per consegnare i carichi.
2. **COMPLETATA**: Tutti i carichi sono stati consegnati con successo.
3. **FALLITA**: La missione non è stata completata per qualche motivo.

## Utilizzo nel Sistema DeliveryManager

Nel contesto del sistema DeliveryManager, l'ADT Missione viene utilizzato per:

1. **Assegnazione di Carichi**: Quando un veicolo viene accodato a un centro di smistamento, può ricevere una missione con uno o più carichi da consegnare.

2. **Tracciamento delle Consegne**: Il sistema monitora lo stato di ciascuna missione per verificare il completamento delle consegne.

3. **Registrazione degli Esiti**: Quando una missione viene completata o fallisce, il sistema registra l'esito e aggiorna le statistiche.

4. **Generazione di Statistiche**: I dati delle missioni vengono utilizzati per generare statistiche sui tempi di consegna, sull'efficienza dei veicoli, ecc.

## Esempio di Utilizzo

```c
// Creazione di una missione
Veicolo veicolo = getVeicoloByTarga(manager, "VCL-101");
Missione missione = createMissione(1, veicolo);

// Aggiunta di carichi alla missione
Carico carico1 = getCaricoById(manager, 1);
Carico carico2 = getCaricoById(manager, 2);
missione_add_carico(missione, carico1);
missione_add_carico(missione, carico2);

// Inizio della missione
missione_set_stato(missione, STATO_MISSIONE_IN_CORSO);

// Completamento della missione
missione_set_stato(missione, STATO_MISSIONE_COMPLETATA);
missione_set_data_fine(missione, time(NULL));
missione_set_nota(missione, "Consegna completata con successo");

// Calcolo della durata
int durata = missione_get_durata(missione);
printf("La missione è durata %d secondi\n", durata);

// Pulizia
destroyMissione(&missione);
```

## Considerazioni sulla Progettazione

1. **Supporto per Più Carichi**: La modifica più significativa rispetto alle specifiche originali è il supporto per più carichi in una singola missione, che ottimizza l'utilizzo dei veicoli.

2. **Tracciamento Temporale**: L'aggiunta dei timestamp permette di calcolare statistiche precise sui tempi di consegna e valutare l'efficienza del sistema.

3. **Gestione dello Stato**: L'implementazione di stati dettagliati consente di monitorare il ciclo di vita delle missioni e generare report accurati.

4. **Flessibilità**: La struttura dell'ADT Missione è stata progettata per essere flessibile e adattabile a diverse esigenze, consentendo l'aggiunta di nuove funzionalità in futuro.

## Conclusioni

Le modifiche apportate all'ADT Missione rispetto alle specifiche originali sono state guidate dall'obiettivo di creare un sistema più efficiente e informativo. L'aggiunta del supporto per più carichi, dei timestamp e del campo nota hanno contribuito a creare un sistema più completo e utilizzabile in scenari reali.
