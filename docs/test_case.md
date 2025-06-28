# Casi di Test per DeliveryManager

Questo documento descrive una serie di casi di test per verificare il corretto funzionamento del sistema DeliveryManager. I test sono organizzati per componenti e funzionalità, con esempi di codice e risultati attesi.

## Test 1: Creazione dell'Infrastruttura di Base

### Descrizione

Questo test verifica la corretta creazione dell'infrastruttura di base del sistema: zone logistiche, punti di consegna e collegamenti stradali.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager
    DeliveryManager manager = createManager();
    if (manager == NULL) {
        printf("Errore nella creazione del manager\n");
        return 1;
    }

    // Creazione delle zone logistiche
    int result;
    result = createZonaLogistica(manager, "Centro Storico");
    printf("Creazione zona 'Centro Storico': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createZonaLogistica(manager, "Zona Industriale");
    printf("Creazione zona 'Zona Industriale': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createZonaLogistica(manager, "Periferia Nord");
    printf("Creazione zona 'Periferia Nord': %s\n", result == 0 ? "OK" : "ERRORE");

    // Creazione dei punti di consegna
    result = createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");
    printf("Creazione punto 'Farmacia Centrale': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createPuntoConsegna(manager, "Hotel Roma", 3, 1000, TIPO_STANDARD, "Centro Storico");
    printf("Creazione punto 'Hotel Roma': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createPuntoConsegna(manager, "Magazzino Tech", 2, 1100, TIPO_REFRIGERATO, "Zona Industriale");
    printf("Creazione punto 'Magazzino Tech': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createPuntoConsegna(manager, "Villa Verde", 5, 830, TIPO_STANDARD, "Periferia Nord");
    printf("Creazione punto 'Villa Verde': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createPuntoConsegna(manager, "Supermercato Sigma", 1, 1030, TIPO_REFRIGERATO, "Periferia Nord");
    printf("Creazione punto 'Supermercato Sigma': %s\n", result == 0 ? "OK" : "ERRORE");

    // Creazione dei collegamenti stradali
    result = addCollegamento(manager, "Farmacia Centrale", "Magazzino Tech", 15);
    printf("Collegamento 'Farmacia Centrale' -> 'Magazzino Tech': %s\n", result == 0 ? "OK" : "ERRORE");

    result = addCollegamento(manager, "Magazzino Tech", "Villa Verde", 20);
    printf("Collegamento 'Magazzino Tech' -> 'Villa Verde': %s\n", result == 0 ? "OK" : "ERRORE");

    result = addCollegamento(manager, "Farmacia Centrale", "Villa Verde", 25);
    printf("Collegamento 'Farmacia Centrale' -> 'Villa Verde': %s\n", result == 0 ? "OK" : "ERRORE");

    result = addCollegamento(manager, "Hotel Roma", "Supermercato Sigma", 30);
    printf("Collegamento 'Hotel Roma' -> 'Supermercato Sigma': %s\n", result == 0 ? "OK" : "ERRORE");

    result = addCollegamento(manager, "Villa Verde", "Supermercato Sigma", 10);
    printf("Collegamento 'Villa Verde' -> 'Supermercato Sigma': %s\n", result == 0 ? "OK" : "ERRORE");

    // Pulizia
    destroyManager(&manager);
    printf("Distruzione manager: %s\n", manager == NULL ? "OK" : "ERRORE");

    return 0;
}
```

### Risultati Attesi

```
Creazione zona 'Centro Storico': OK
Creazione zona 'Zona Industriale': OK
Creazione zona 'Periferia Nord': OK
Creazione punto 'Farmacia Centrale': OK
Creazione punto 'Hotel Roma': OK
Creazione punto 'Magazzino Tech': OK
Creazione punto 'Villa Verde': OK
Creazione punto 'Supermercato Sigma': OK
Collegamento 'Farmacia Centrale' -> 'Magazzino Tech': OK
Collegamento 'Magazzino Tech' -> 'Villa Verde': OK
Collegamento 'Farmacia Centrale' -> 'Villa Verde': OK
Collegamento 'Hotel Roma' -> 'Supermercato Sigma': OK
Collegamento 'Villa Verde' -> 'Supermercato Sigma': OK
Distruzione manager: OK
```

## Test 2: Gestione dei Veicoli

### Descrizione

Questo test verifica la corretta registrazione e gestione dei veicoli nel sistema.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager
    DeliveryManager manager = createManager();

    // Registrazione dei veicoli
    int result;
    result = createVeicolo(manager, "VCL-101", 100);
    printf("Registrazione veicolo 'VCL-101': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createVeicolo(manager, "VCL-202", 150);
    printf("Registrazione veicolo 'VCL-202': %s\n", result == 0 ? "OK" : "ERRORE");

    result = createVeicolo(manager, "VCL-303", 80);
    printf("Registrazione veicolo 'VCL-303': %s\n", result == 0 ? "OK" : "ERRORE");

    // Tentativo di registrazione di un veicolo con targa duplicata
    result = createVeicolo(manager, "VCL-101", 120);
    printf("Registrazione veicolo con targa duplicata: %s\n", result != 0 ? "OK (errore rilevato)" : "ERRORE");

    // Verifica dello stato dei veicoli
    Veicolo veicolo = getVeicoloByTarga(manager, "VCL-101");
    if (veicolo != NULL) {
        printf("Veicolo 'VCL-101' trovato: OK\n");
        printf("Capacità: %d kg\n", veicolo_get_capacita(veicolo));
        printf("Stato: %s\n", veicolo_get_stato_string(veicolo));
    } else {
        printf("Veicolo 'VCL-101' non trovato: ERRORE\n");
    }

    // Cambio dello stato di un veicolo
    veicolo_set_stato(veicolo, STATO_VEICOLO_IN_VIAGGIO);
    printf("Cambio stato veicolo 'VCL-101': %s\n", veicolo_get_stato(veicolo) == STATO_VEICOLO_IN_VIAGGIO ? "OK" : "ERRORE");

    // Pulizia
    destroyManager(&manager);

    return 0;
}
```

### Risultati Attesi

```
Registrazione veicolo 'VCL-101': OK
Registrazione veicolo 'VCL-202': OK
Registrazione veicolo 'VCL-303': OK
Registrazione veicolo con targa duplicata: OK (errore rilevato)
Veicolo 'VCL-101' trovato: OK
Capacità: 100 kg
Stato: Disponibile
Cambio stato veicolo 'VCL-101': OK
```

## Test 3: Gestione dei Carichi e dei Centri di Smistamento

### Descrizione

Questo test verifica la corretta gestione dei carichi e dei centri di smistamento, inclusa la creazione di carichi e l'accodamento nei centri di smistamento.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager e dell'infrastruttura di base
    DeliveryManager manager = createManager();
    createZonaLogistica(manager, "Centro Storico");
    createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");

    // Creazione di un centro di smistamento
    int result;
    result = createCentroSmistamento(manager, "Centro Principale");
    printf("Creazione centro 'Centro Principale': %s\n", result == 0 ? "OK" : "ERRORE");

    // Creazione di carichi
    int id_carico1 = insertCarico(manager, 20, CARICO_STANDARD, "Farmacia Centrale", 3, "Centro Principale");
    printf("Inserimento carico 1: %s (ID: %d)\n", id_carico1 >= 0 ? "OK" : "ERRORE", id_carico1);

    int id_carico2 = insertCarico(manager, 15, CARICO_FRAGILE, "Farmacia Centrale", 5, "Centro Principale");
    printf("Inserimento carico 2: %s (ID: %d)\n", id_carico2 >= 0 ? "OK" : "ERRORE", id_carico2);

    int id_carico3 = insertCarico(manager, 30, CARICO_REFRIGERATO, "Farmacia Centrale", 4, "Centro Principale");
    printf("Inserimento carico 3: %s (ID: %d)\n", id_carico3 >= 0 ? "OK" : "ERRORE", id_carico3);

    // Verifica dei carichi
    Carico carico = getCaricoById(manager, id_carico1);
    if (carico != NULL) {
        printf("Carico %d trovato: OK\n", id_carico1);
        printf("Peso: %d kg\n", carico_get_peso(carico));
        printf("Priorità: %d\n", carico_get_priorita(carico));
        printf("Tipologia: %d\n", carico_get_tipologia(carico));
    } else {
        printf("Carico %d non trovato: ERRORE\n", id_carico1);
    }

    // Verifica del centro di smistamento
    CentroSmistamento centro = getCentroSmistamentoByNome(manager, "Centro Principale");
    if (centro != NULL) {
        printf("Centro 'Centro Principale' trovato: OK\n");
        printf("Numero carichi disponibili: %d\n", centrosmistamento_get_num_carichi(centro));
    } else {
        printf("Centro 'Centro Principale' non trovato: ERRORE\n");
    }

    // Pulizia
    destroyManager(&manager);

    return 0;
}
```

### Risultati Attesi

```
Creazione centro 'Centro Principale': OK
Inserimento carico 1: OK (ID: 0)
Inserimento carico 2: OK (ID: 1)
Inserimento carico 3: OK (ID: 2)
Carico 0 trovato: OK
Peso: 20 kg
Priorità: 3
Tipologia: 0
Centro 'Centro Principale' trovato: OK
Numero carichi disponibili: 3
```

## Test 4: Assegnazione e Gestione delle Missioni

### Descrizione

Questo test verifica il processo di assegnazione automatica delle missioni e la registrazione degli esiti.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager e dell'infrastruttura di base
    DeliveryManager manager = createManager();
    createZonaLogistica(manager, "Centro Storico");
    createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");
    createCentroSmistamento(manager, "Centro Principale");

    // Creazione di veicoli e carichi
    createVeicolo(manager, "VCL-101", 100);
    insertCarico(manager, 20, CARICO_STANDARD, "Farmacia Centrale", 3, "Centro Principale");
    insertCarico(manager, 15, CARICO_FRAGILE, "Farmacia Centrale", 5, "Centro Principale");

    // Accodamento di un veicolo
    int result = addVeicoloToCoda(manager, "VCL-101", "Centro Principale");
    printf("Accodamento veicolo 'VCL-101': %s\n", result == 0 ? "OK" : "ERRORE");

    // Assegnazione automatica di una missione
    Missione missione = addAutoTask(manager, "Centro Principale");
    if (missione != NULL) {
        int id_missione = missione_get_id(missione);
        printf("Assegnazione missione: OK (ID: %d)\n", id_missione);

        // Verifica dello stato della missione
        printf("Stato missione: %s\n", missione_get_stato_string(missione));

        // Verifica del veicolo associato
        Veicolo veicolo = missione_get_veicolo(missione);
        printf("Veicolo associato: %s\n", veicolo_get_targa(veicolo));
        printf("Stato veicolo: %s\n", veicolo_get_stato_string(veicolo));

        // Verifica dei carichi associati
        int num_carichi = missione_get_num_carichi(missione);
        printf("Numero carichi associati: %d\n", num_carichi);

        // Registrazione dell'esito della missione
        result = registraEsitoMissione(manager, id_missione, STATO_MISSIONE_COMPLETATA, "Consegna completata con successo");
        printf("Registrazione esito missione: %s\n", result == 0 ? "OK" : "ERRORE");

        // Verifica dello stato aggiornato
        missione = getMissioneById(manager, id_missione);
        if (missione != NULL) {
            printf("Stato missione aggiornato: %s\n", missione_get_stato_string(missione));
            printf("Nota missione: %s\n", missione_get_nota(missione));

            // Verifica dello stato del veicolo
            veicolo = missione_get_veicolo(missione);
            printf("Stato veicolo aggiornato: %s\n", veicolo_get_stato_string(veicolo));
        } else {
            printf("Missione non trovata dopo l'aggiornamento: ERRORE\n");
        }
    } else {
        printf("Assegnazione missione: ERRORE\n");
    }

    // Pulizia
    destroyManager(&manager);

    return 0;
}
```

### Risultati Attesi

```
Accodamento veicolo 'VCL-101': OK
Assegnazione missione: OK (ID: 0)
Stato missione: In corso
Veicolo associato: VCL-101
Stato veicolo: In viaggio
Numero carichi associati: 2
Registrazione esito missione: OK
Stato missione aggiornato: Completata
Nota missione: Consegna completata con successo
Stato veicolo aggiornato: Disponibile
```

## Test 5: Calcolo del Percorso Più Breve

### Descrizione

Questo test verifica il corretto funzionamento dell'algoritmo di calcolo del percorso più breve tra due punti.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager e dell'infrastruttura di base
    DeliveryManager manager = createManager();

    // Creazione delle zone logistiche
    createZonaLogistica(manager, "Centro Storico");
    createZonaLogistica(manager, "Zona Industriale");
    createZonaLogistica(manager, "Periferia Nord");

    // Creazione dei punti di consegna
    createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");
    createPuntoConsegna(manager, "Hotel Roma", 3, 1000, TIPO_STANDARD, "Centro Storico");
    createPuntoConsegna(manager, "Magazzino Tech", 2, 1100, TIPO_REFRIGERATO, "Zona Industriale");
    createPuntoConsegna(manager, "Villa Verde", 5, 830, TIPO_STANDARD, "Periferia Nord");
    createPuntoConsegna(manager, "Supermercato Sigma", 1, 1030, TIPO_REFRIGERATO, "Periferia Nord");

    // Creazione dei collegamenti stradali
    addCollegamento(manager, "Farmacia Centrale", "Hotel Roma", 5);
    addCollegamento(manager, "Hotel Roma", "Magazzino Tech", 15);
    addCollegamento(manager, "Magazzino Tech", "Villa Verde", 20);
    addCollegamento(manager, "Villa Verde", "Supermercato Sigma", 10);
    addCollegamento(manager, "Farmacia Centrale", "Villa Verde", 25);

    // Calcolo del percorso più breve
    char** percorso = getPercorsoBreve(manager, "Farmacia Centrale", "Supermercato Sigma");

    if (percorso != NULL) {
        printf("Percorso trovato:\n");
        int i = 0;
        while (percorso[i] != NULL) {
            printf("%d. %s\n", i + 1, percorso[i]);
            i++;
        }

        // Liberazione della memoria del percorso
        i = 0;
        while (percorso[i] != NULL) {
            free(percorso[i]);
            i++;
        }
        free(percorso);
    } else {
        printf("Percorso non trovato\n");
    }

    // Pulizia
    destroyManager(&manager);

    return 0;
}
```

### Risultati Attesi

```
Percorso trovato:
1. Farmacia Centrale
2. Villa Verde
3. Supermercato Sigma
```

## Test 6: Generazione di Statistiche

### Descrizione

Questo test verifica la corretta generazione di statistiche sul sistema.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager e dell'infrastruttura di base
    DeliveryManager manager = createManager();

    // Creazione delle zone logistiche e punti di consegna
    createZonaLogistica(manager, "Centro Storico");
    createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");
    createPuntoConsegna(manager, "Hotel Roma", 3, 1000, TIPO_STANDARD, "Centro Storico");

    createZonaLogistica(manager, "Zona Industriale");
    createPuntoConsegna(manager, "Magazzino Tech", 2, 1100, TIPO_REFRIGERATO, "Zona Industriale");

    // Creazione di un centro di smistamento
    createCentroSmistamento(manager, "Centro Principale");

    // Creazione di veicoli
    createVeicolo(manager, "VCL-101", 100);
    createVeicolo(manager, "VCL-202", 150);

    // Creazione di carichi
    insertCarico(manager, 20, CARICO_STANDARD, "Farmacia Centrale", 3, "Centro Principale");
    insertCarico(manager, 15, CARICO_FRAGILE, "Hotel Roma", 5, "Centro Principale");
    insertCarico(manager, 30, CARICO_REFRIGERATO, "Magazzino Tech", 4, "Centro Principale");

    // Accodamento di veicoli
    addVeicoloToCoda(manager, "VCL-101", "Centro Principale");
    addVeicoloToCoda(manager, "VCL-202", "Centro Principale");

    // Assegnazione di missioni
    Missione missione1 = addAutoTask(manager, "Centro Principale");
    Missione missione2 = addAutoTask(manager, "Centro Principale");

    // Simulazione del completamento delle missioni
    sleep(1); // Attesa di 1 secondo per simulare il tempo di consegna
    registraEsitoMissione(manager, missione_get_id(missione1), STATO_MISSIONE_COMPLETATA, "Consegna completata con successo");

    sleep(2); // Attesa di 2 secondi per simulare il tempo di consegna
    registraEsitoMissione(manager, missione_get_id(missione2), STATO_MISSIONE_COMPLETATA, "Consegna completata con successo");

    // Generazione e visualizzazione delle statistiche
    printf("Statistiche generali del sistema:\n");
    getStatistics(manager);

    printf("\nTempi medi di consegna per tipologia:\n");
    double* tempi_medi = getTempiMediPerTipologia(manager);
    if (tempi_medi != NULL) {
        printf("Standard: %.2f secondi\n", tempi_medi[CARICO_STANDARD]);
        printf("Fragile: %.2f secondi\n", tempi_medi[CARICO_FRAGILE]);
        printf("Refrigerato: %.2f secondi\n", tempi_medi[CARICO_REFRIGERATO]);
        free(tempi_medi);
    }

    printf("\nCarico medio per veicolo:\n");
    double carico_medio = getCaricoMedioPerVeicolo(manager);
    printf("Media: %.2f kg\n", carico_medio);

    printf("\nNumero di consegne per zona logistica:\n");
    int* num_consegne = getNumConsegnePerZona(manager);
    if (num_consegne != NULL) {
        ZonaLogistica zona;
        for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
            dynamic_array_get_at(manager->zone_logistiche, i, (void**)&zona);
            printf("%s: %d consegne\n", zonalogistica_get_nome(zona), num_consegne[i]);
        }
        free(num_consegne);
    }

    // Pulizia
    destroyManager(&manager);

    return 0;
}
```

### Risultati Attesi

```
Statistiche generali del sistema:
Numero totale di missioni: 2
Numero di missioni completate: 2
Numero di missioni fallite: 0
Numero totale di carichi: 3
Numero di carichi consegnati: 3
Numero di carichi non consegnati: 0

Tempi medi di consegna per tipologia:
Standard: 1.00 secondi
Fragile: 1.00 secondi
Refrigerato: 2.00 secondi

Carico medio per veicolo:
Media: 32.50 kg

Numero di consegne per zona logistica:
Centro Storico: 2 consegne
Zona Industriale: 1 consegne
```

## Test 7: Funzionalità Personalizzata - Calcolo dell'Efficienza dei Veicoli

### Descrizione

Questo test verifica il funzionamento della funzionalità personalizzata F8, che calcola un punteggio di efficienza per ogni veicolo.

### Codice di Test

```c
#include <stdio.h>
#include "DeliveryManager.h"

int main() {
    // Creazione del manager e dell'infrastruttura di base
    DeliveryManager manager = createManager();

    // Creazione delle zone logistiche e punti di consegna
    createZonaLogistica(manager, "Centro Storico");
    createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");

    // Creazione di un centro di smistamento
    createCentroSmistamento(manager, "Centro Principale");

    // Creazione di veicoli
    createVeicolo(manager, "VCL-101", 100);
    createVeicolo(manager, "VCL-202", 150);
    createVeicolo(manager, "VCL-303", 80);

    // Creazione di carichi
    insertCarico(manager, 20, CARICO_STANDARD, "Farmacia Centrale", 3, "Centro Principale");
    insertCarico(manager, 15, CARICO_FRAGILE, "Farmacia Centrale", 5, "Centro Principale");
    insertCarico(manager, 30, CARICO_REFRIGERATO, "Farmacia Centrale", 4, "Centro Principale");
    insertCarico(manager, 25, CARICO_STANDARD, "Farmacia Centrale", 2, "Centro Principale");

    // Simulazione di missioni per il primo veicolo
    addVeicoloToCoda(manager, "VCL-101", "Centro Principale");
    Missione missione1 = addAutoTask(manager, "Centro Principale");
    sleep(1);
    registraEsitoMissione(manager, missione_get_id(missione1), STATO_MISSIONE_COMPLETATA, "Consegna completata con successo");

    // Simulazione di missioni per il secondo veicolo
    addVeicoloToCoda(manager, "VCL-202", "Centro Principale");
    Missione missione2 = addAutoTask(manager, "Centro Principale");
    sleep(2);
    registraEsitoMissione(manager, missione_get_id(missione2), STATO_MISSIONE_FALLITA, "Problemi durante la consegna");

    // Il terzo veicolo non effettua missioni

    // Calcolo dell'efficienza dei veicoli
    printf("Efficienza dei veicoli:\n");
    double* efficienza = calcolaEfficienzaVeicoli(manager);
    if (efficienza != NULL) {
        printf("VCL-101: %.2f\n", efficienza[0]);
        printf("VCL-202: %.2f\n", efficienza[1]);
        printf("VCL-303: %.2f\n", efficienza[2]);
        free(efficienza);
    }

    // Pulizia
    destroyManager(&manager);

    return 0;
}
```

### Risultati Attesi

```
Efficienza dei veicoli:
VCL-101: 85.00
VCL-202: 40.00
VCL-303: 0.00
```

## Conclusioni

I casi di test presentati coprono le principali funzionalità del sistema DeliveryManager:

1. Creazione dell'infrastruttura di base
2. Gestione dei veicoli
3. Gestione dei carichi e dei centri di smistamento
4. Assegnazione e gestione delle missioni
5. Calcolo del percorso più breve
6. Generazione di statistiche
7. Funzionalità personalizzata (calcolo dell'efficienza dei veicoli)

Questi test possono essere utilizzati per verificare il corretto funzionamento del sistema e per identificare eventuali problemi. È importante notare che i risultati attesi possono variare leggermente a seconda dell'implementazione specifica delle funzioni e delle strutture dati.
