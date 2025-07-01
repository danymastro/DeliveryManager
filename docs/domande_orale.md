# Domande e Risposte per l'Esame Orale – Progetto DeliveryManager

---

## 1. **Come sono state modellate le principali entità del sistema?**

**Risposta:**

- Ogni entità (ZonaLogistica, PuntoConsegna, Veicolo, Carico, Missione, CentroSmistamento) è rappresentata da una struttura dati dedicata, con campi specifici e relazioni tramite puntatori.
- Le relazioni tra entità (es. carico → punto di consegna, missione → veicolo) sono gestite tramite puntatori.

---

## 2. **Come viene gestita la memoria dinamica?**

**Risposta:**

- Tutte le strutture dati principali sono allocate dinamicamente con `malloc`/`calloc`.
- La liberazione della memoria avviene tramite funzioni di distruzione dedicate (es. `destroyManager`, `missione_destroy`, ecc.).
- Le strutture dati generiche (array dinamici, code) accettano puntatori a funzione per liberare correttamente gli elementi.

---

## 3. **Come funziona la coda di priorità? Perché è generica?**

**Risposta:**

- La coda di priorità è implementata in modo generico usando `void*` e puntatori a funzione di confronto.
- Può gestire qualsiasi tipo di elemento (carichi, veicoli, ecc.) e l'ordinamento è determinato dalla funzione di confronto passata dall'utente.
- Nel progetto viene usata per gestire i carichi nei centri di smistamento, ordinandoli per priorità.

---

## 4. **Come viene rappresentata la rete stradale?**

**Risposta:**

- La rete è modellata come un grafo orientato pesato, implementato tramite matrice di adiacenza.
- Ogni nodo rappresenta una zona o un punto di consegna; gli archi hanno come peso il tempo di percorrenza.
- Sono implementate funzioni per aggiungere nodi, archi e calcolare percorsi minimi (Dijkstra).

---

## 5. **Come vengono gestiti gli orari e i tempi?**

**Risposta:**

- Gli orari dei punti di consegna sono gestiti come interi (formato HHMM), come richiesto nelle istruzioni.
- Le date/tempi delle missioni sono gestite con `time_t` (libreria `<time.h>`), per registrare l'istante di inizio/fine e calcolare la durata reale delle missioni.

---

## 6. **Come funziona l'assegnazione automatica delle missioni?**

**Risposta:**

- Il sistema seleziona un veicolo disponibile e i carichi compatibili (per peso, tipologia, priorità) dal centro di smistamento.
- Crea una missione, assegna i carichi e aggiorna lo stato del veicolo e dei carichi.
- Registra l'istante di inizio missione con `time(NULL)`.

---

## 7. **Come vengono gestite le statistiche?**

**Risposta:**

- Le statistiche sono calcolate scorrendo lo storico delle missioni completate (array dinamico).
- Si calcolano: tempi medi di consegna per tipologia, carico medio per veicolo, numero di consegne per zona.
- I tempi sono calcolati usando la differenza tra `data_fine` e `data_inizio` delle missioni.

---

## 8. **Come viene gestito lo storico delle missioni?**

**Risposta:**

- Tutte le missioni (completate e non) sono memorizzate in un array dinamico.
- Ogni missione contiene informazioni su veicolo, carichi, stato, tempi, note.
- Lo storico permette di ricavare statistiche e filtrare le missioni per vari criteri.

---

## 9. **Come vengono gestiti gli errori?**

**Risposta:**

- Le funzioni restituiscono codici di errore (0=successo, >0=errore specifico).
- Gli input dell'utente sono validati (es. priorità, tipologia, esistenza di entità).
- In caso di errori di memoria o dati non trovati, il sistema mostra messaggi chiari.

---

## 10. **Come è organizzato il progetto a livello di file?**

**Risposta:**

- Ogni entità ha il suo file `.h` e `.c`.
- Le strutture dati generiche (array dinamico, coda, grafo) sono in file separati e riutilizzabili.
- Il file `main.c` contiene il menu testuale e la logica di interazione con l'utente.

---

## 11. **Come funziona la funzionalità personalizzata (F8)?**

**Risposta:**

- Nel progetto è stata implementata la visualizzazione dell'efficienza dei veicoli.
- L'efficienza è calcolata in base al numero di missioni completate, peso trasportato e durata delle missioni.
- I risultati sono mostrati in una tabella riepilogativa.

---

## 12. **Come si compila e si esegue il progetto?**

**Risposta:**

- Si compilano tutti i file `.c` in file oggetto `.o` e poi si linkano per creare l'eseguibile `DeliveryManager`.
- Esempio:
  ```bash
  gcc -c *.c
  gcc *.o -o DeliveryManager
  ./DeliveryManager
  ```

---

## 13. **Come si gestiscono i puntatori a funzione nelle strutture dati generiche?**

**Risposta:**

- Si usano per permettere alla struttura dati di operare su tipi diversi senza conoscere la loro struttura interna.
- Ad esempio, la coda usa una funzione di confronto per ordinare gli elementi e una di distruzione per liberarli.

---

## 14. **Come si garantisce la modularità e la riusabilità del codice?**

**Risposta:**

- Separando le entità e le strutture dati in moduli indipendenti.
- Usando interfacce (header file) chiare e funzioni generiche dove possibile.

---

## 15. **Quali sono i possibili miglioramenti futuri?**

**Risposta:**

- Gestione di date e orari più avanzata (es. fusi orari, date reali).
- Interfaccia grafica o API web.
- Ottimizzazione degli algoritmi di assegnazione missioni.
- Maggiore robustezza nella gestione degli errori e dei dati persistenti.

---

## 16. **Cosa succede se due carichi hanno la stessa priorità?**

**Risposta:**

- Se la funzione di confronto restituisce 0 (stessa priorità), l'ordine di estrazione dipende dall'implementazione della coda (tipicamente FIFO tra pari priorità).

---

## 17. **Come si collega un carico al suo punto di consegna?**

**Risposta:**

- Ogni carico ha un puntatore al nodo del grafo che rappresenta il punto di consegna.
- Questo permette di calcolare percorsi e statistiche per zona/punto.

---

## 18. **Come si gestisce lo stato dei veicoli e delle missioni?**

**Risposta:**

- Gli stati sono rappresentati da interi o enum (es. disponibile, in viaggio, in manutenzione per i veicoli; in corso, completata, fallita per le missioni).
- Le funzioni di gestione aggiornano lo stato in base alle operazioni svolte.

---

## 19. **Come si aggiunge una nuova zona logistica o un nuovo punto di consegna?**

**Risposta:**

- Si usano le funzioni `createZonaLogistica` e `createPuntoConsegna`, che allocano e collegano le nuove entità al grafo e agli array dinamici.

---

## 20. **Come si calcola il percorso più breve tra due zone?**

**Risposta:**

- Si usa la funzione di shortest path del grafo pesato (algoritmo di Dijkstra), passando i nodi di partenza e arrivo.
- Il percorso e il tempo totale sono restituiti come lista di nodi e somma dei pesi degli archi.

---

_Questo file è pensato per il ripasso rapido e la preparazione all'esame orale sul progetto DeliveryManager._
