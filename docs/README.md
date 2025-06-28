# DeliveryManager - Sistema di Gestione Consegne Automatizzate

## Panoramica del Sistema

DeliveryManager è un sistema software per la gestione di una flotta di veicoli autonomi impiegati per la consegna automatizzata di pacchi in ambito urbano. Il sistema permette di gestire zone logistiche, punti di consegna, veicoli, carichi e missioni di consegna, offrendo funzionalità per l'assegnazione automatica delle missioni, il monitoraggio dello stato delle consegne e la generazione di statistiche.

## Struttura del Progetto

Il sistema è organizzato secondo un'architettura modulare basata su Abstract Data Types (ADT), dove ogni componente è definito da un'interfaccia (.h) e un'implementazione (.c) separate:

```
DeliveryManager/
├── docs/                      # Documentazione
├── progetto/                  # Codice sorgente
│   ├── DeliveryManager.h      # ADT principale
│   ├── DeliveryManager.c      # Implementazione dell'ADT principale
│   ├── carico.h/c             # ADT per la gestione dei carichi
│   ├── centrosmistamento.h/c  # ADT per la gestione dei centri di smistamento
│   ├── missione.h/c           # ADT per la gestione delle missioni
│   ├── puntoconsegna.h/c      # ADT per la gestione dei punti di consegna
│   ├── veicolo.h/c            # ADT per la gestione dei veicoli
│   ├── zonalogistica.h/c      # ADT per la gestione delle zone logistiche
│   ├── dynamic_array.h/c      # ADT per array dinamici
│   ├── linked_list.h/c        # ADT per liste concatenate
│   ├── list_queue.h/c         # ADT per code basate su liste
│   ├── list_stack.h/c         # ADT per pile basate su liste (non utilizzato attivamente)
│   ├── queue.h/c              # ADT per code con priorità
│   ├── weighted_directed_graph.h/c # ADT per grafi orientati pesati
│   └── main.c                 # Programma principale con interfaccia utente
```

## Componenti Principali

### DeliveryManager

Il componente centrale che coordina tutte le operazioni del sistema. Gestisce la creazione e l'organizzazione di zone logistiche, punti di consegna, veicoli, carichi e missioni.

### Zone Logistiche e Punti di Consegna

L'area metropolitana è suddivisa in zone logistiche (es. "Centro Storico", "Zona Industriale"), ciascuna contenente uno o più punti di consegna. Ogni punto di consegna ha caratteristiche specifiche come priorità, orario di consegna e tipologia.

### Veicoli

I veicoli autonomi sono caratterizzati da una targa univoca, una capacità massima e uno stato operativo (disponibile, in viaggio, in manutenzione). Ogni veicolo può trasportare più carichi compatibili.

### Carichi

I carichi rappresentano i pacchi da consegnare. Ogni carico ha un peso, una tipologia (standard, refrigerato, fragile), un punto di destinazione e una priorità.

### Missioni

Le missioni rappresentano l'assegnazione di uno o più carichi a un veicolo per la consegna. Il sistema tiene traccia dello stato delle missioni (in corso, completate, fallite).

### Centri di Smistamento

I centri di smistamento gestiscono code di carichi e veicoli. I carichi vengono ordinati per priorità e assegnati ai veicoli disponibili.

## Funzionalità Principali

1. **Registrazione di veicoli**: Aggiunta di nuovi veicoli alla flotta
2. **Gestione zone logistiche**: Visualizzazione e gestione delle zone e dei punti di consegna
3. **Inserimento carichi**: Registrazione di nuovi carichi da consegnare
4. **Accodamento veicoli**: Inserimento di veicoli nelle code dei centri di smistamento
5. **Assegnazione missioni**: Creazione automatica di missioni di consegna
6. **Registrazione esiti**: Tracciamento dei risultati delle missioni
7. **Statistiche**: Generazione di dati aggregati su consegne, carichi e veicoli
8. **Calcolo efficienza**: Valutazione delle prestazioni dei veicoli

## Strutture Dati Utilizzate

- **Array Dinamici**: Per la gestione di collezioni di oggetti (veicoli, carichi, missioni)
- **Code con Priorità**: Per la gestione dei carichi nei centri di smistamento
- **Grafi Orientati Pesati**: Per rappresentare la rete stradale e calcolare percorsi
- **Liste Concatenate**: Utilizzate come struttura di supporto per implementare algoritmi sui grafi e gestire percorsi

## Modifiche Principali Rispetto alle Specifiche Originali

### DeliveryManager

- Aggiunta di contatori automatici per la generazione di ID univoci per carichi, missioni e altre entità
- Implementazione di funzioni di ricerca avanzate per accedere facilmente alle entità per nome o ID

### Missione

- Supporto per gestire più carichi in una singola missione tramite array dinamico
- Aggiunta di timestamp per tracciare con precisione la durata delle missioni
- Campo nota per memorizzare informazioni testuali sull'esito della missione

### Carico

- Aggiunta di timestamp per tracciare i tempi di creazione e consegna
- Implementazione di stati dettagliati per monitorare il ciclo di vita del carico

### CentroSmistamento

- Aggiunta di contatori per carichi gestiti, consegnati e falliti
- Implementazione di algoritmi di priorità avanzati per ottimizzare l'assegnazione dei carichi

### Veicolo

- Aggiunta di campi per tracciare statistiche operative
- Implementazione di funzioni per calcolare l'efficienza dei veicoli

## Motivazioni delle Modifiche

1. **Miglioramento della robustezza**: Generazione automatica di ID, gestione degli errori
2. **Implementazione di funzionalità avanzate**: Statistiche dettagliate, calcolo dell'efficienza
3. **Ottimizzazione delle operazioni**: Gestione di più carichi per missione, prioritizzazione basata su diversi fattori
4. **Tracciamento temporale**: Aggiunta di timestamp per calcolare statistiche precise sui tempi di consegna
5. **Gestione dello stato**: Implementazione di stati dettagliati per monitorare il ciclo di vita delle entità

Per una documentazione dettagliata di ciascun componente e delle modifiche apportate, consultare i file specifici nella directory `docs/`.
