#ifndef DELIVERY_MANAGER_H
#define DELIVERY_MANAGER_H

#include <stdlib.h>
#include "zonalogistica.h"
#include "puntoconsegna.h"
#include "missione.h"
#include "veicolo.h"
#include "carico.h"
#include "centrosmistamento.h"

typedef struct DeliveryManager* DeliveryManager;

/*
 * Funzione per creare un nuovo gestore della rete logistica
 * @params nessun parametro
 * @return un puntatore al gestore della rete logistica
 */
DeliveryManager createManager();

/*
 * Funzione per distruggere il gestore della rete logistica
 * @params un puntatore che punta al gestore della rete logistica
 * @return nessun valore
 */
void destroyManager(DeliveryManager* _manager);

/*
 * Funzione per creare una nuova zona logistica
 * @params un puntatore al gestore della rete logistica, il nome della zona logistica
 * @return 0 se la creazione è avvenuta con successo
 *         1 se la creazione non è avvenuta con successo
 *         2 se il nome della zona logistica è già presente
 *         3 se non è presente più spazio per la creazione della zona logistica
 */
int createZonaLogistica(DeliveryManager manager, char* nome);

/*
 * Funzione per creare un nuovo punto di consegna
 * @params un puntatore al gestore della rete logistica, il nome del punto di consegna, la priorità, l'orario, il tipo, il nome della zona logistica
 * @return 0 se la creazione è avvenuta con successo
 *         1 se la creazione non è avvenuta con successo
 *         2 se il nome del punto di consegna è già presente
 *         3 se la zona logistica non esiste
 *         4 se non è presente più spazio per la creazione del punto di consegna
 */
int createPuntoConsegna(DeliveryManager manager, char* nome, int priorita, int orario, TipoPuntoConsegna tipo, char* zona_logistica);

/*
 * Funzione per creare un nuovo centro di smistamento
 * @params un puntatore al gestore della rete logistica, il nome del centro di smistamento
 * @return 0 se la creazione è avvenuta con successo
 *         1 se la creazione non è avvenuta con successo
 *         2 se il nome del centro di smistamento è già presente
 *         3 se non è presente più spazio per la creazione del centro di smistamento
 */
int createCentroSmistamento(DeliveryManager manager, char* nome);

/*
 * Funzione per creare un nuovo veicolo
 * @params un puntatore al gestore della rete logistica, la targa del veicolo, la capacità del veicolo
 * @return 0 se la creazione è avvenuta con successo
 *         1 se la creazione non è avvenuta con successo
 *         2 se la targa del veicolo è già presente
 *         3 se non è presente più spazio per la creazione del veicolo
 */
int createVeicolo(DeliveryManager manager, char* targa, int capacita);

/*
 * Funzione per inserire un nuovo carico
 * @params un puntatore al gestore della rete logistica, il peso del carico, la tipologia del carico, il nome del punto di consegna, la priorità del carico, il nome del centro di smistamento
 * @return 0 se l'inserimento è avvenuto con successo
 *         1 se l'inserimento non è avvenuto con successo
 *         2 se il punto di consegna non esiste
 *         3 se il centro di smistamento non esiste
 *         4 se lo spazio disponibile non è sufficiente
 */
int insertCarico(DeliveryManager manager, int peso, TipoCarico tipologia, char* punto_consegna, int priorita, char* centro_smistamento);

/*
 * Funzione per aggiungere un veicolo alla coda di un centro di smistamento
 * @params un puntatore al gestore della rete logistica, la targa del veicolo, il nome del centro di smistamento
 * @return 0 se l'aggiunta è avvenuta con successo
 *         1 se l'aggiunta non è avvenuta con successo
 *         2 se il veicolo non esiste
 *         3 se il centro di smistamento non esiste
 *         4 se il veicolo non è disponibile
 */
int addVeicoloToCoda(DeliveryManager manager, char* targa, char* centro_smistamento);

/*
 * Funzione per assegnare una missione ad un veicolo
 * @params un puntatore al gestore della rete logistica, puntatore al veicolo, puntatore al carico
 * @return 0 se l'aggiunta è avvenuta con successo
 *         1 se l'aggiunta non è avvenuta con successo
 *         2 se il veicolo non è valido
 *         3 se il carico non è valido
 */
int addTask(DeliveryManager manager, Veicolo veicolo, Carico carico);

/*
 * Funzione per assegnare una missione ad un veicolo automaticamente
 * @params un puntatore al gestore della rete logistica, il nome del centro di smistamento
 * @return puntatore alla missione creata, oppure NULL in caso di errore
 */
Missione addAutoTask(DeliveryManager manager, char* centro_smistamento);

/*
 * Funzione per registrare l'esito di una missione
 * @params un puntatore al gestore della rete logistica, l'ID della missione, lo stato della missione, una nota testuale
 * @return 0 se la registrazione è avvenuta con successo
 *         1 se la registrazione non è avvenuta con successo
 *         2 se la missione non esiste
 */
int registraEsitoMissione(DeliveryManager manager, int id_missione, StatoMissione stato, const char* nota);

/*
 * Funzione per ottenere le statistiche della rete logistica
 * @params un puntatore al gestore della rete logistica
 * @return nessun valore (le statistiche vengono stampate a video)
 */
void getStatistics(DeliveryManager manager);

/*
 * Funzione per ottenere i tempi medi di consegna per tipologia di carico
 * @params un puntatore al gestore della rete logistica
 * @return un array di double con i tempi medi per ogni tipologia, oppure NULL in caso di errore
 */
double* getTempiMediPerTipologia(DeliveryManager manager);

/*
 * Funzione per ottenere il carico medio per veicolo
 * @params un puntatore al gestore della rete logistica
 * @return un double con il carico medio, oppure -1 in caso di errore
 */
double getCaricoMedioPerVeicolo(DeliveryManager manager);

/*
 * Funzione per ottenere il numero di consegne per zona logistica
 * @params un puntatore al gestore della rete logistica
 * @return un array di int con il numero di consegne per ogni zona, oppure NULL in caso di errore
 */
int* getNumConsegnePerZona(DeliveryManager manager);

/*
 * Funzione per ottenere il percorso più breve tra due punti
 * @params un puntatore al gestore della rete logistica, il nome del punto di partenza, il nome del punto di arrivo
 * @return una lista di nomi di punti che rappresentano il percorso, oppure NULL in caso di errore
 */
char** getPercorsoBreve(DeliveryManager manager, char* partenza, char* arrivo);

/*
 * Funzione per aggiungere un collegamento tra due punti
 * @params un puntatore al gestore della rete logistica, il nome del punto di partenza, il nome del punto di arrivo, il tempo di percorrenza in minuti
 * @return 0 se l'aggiunta è avvenuta con successo
 *         1 se l'aggiunta non è avvenuta con successo
 *         2 se il punto di partenza non esiste
 *         3 se il punto di arrivo non esiste
 */
int addCollegamento(DeliveryManager manager, char* partenza, char* arrivo, int tempo);

/*
 * Funzione per ottenere tutti i veicoli registrati
 * @params un puntatore al gestore della rete logistica
 * @return un array di puntatori ai veicoli, oppure NULL in caso di errore
 */
Veicolo* getVeicoli(DeliveryManager manager);

/*
 * Funzione per ottenere tutti i carichi registrati
 * @params un puntatore al gestore della rete logistica
 * @return un array di puntatori ai carichi, oppure NULL in caso di errore
 */
Carico* getCarichi(DeliveryManager manager);

/*
 * Funzione per ottenere tutte le missioni registrate
 * @params un puntatore al gestore della rete logistica
 * @return un array di puntatori alle missioni, oppure NULL in caso di errore
 */
Missione* getMissioni(DeliveryManager manager);

/*
 * Funzione per ottenere tutte le zone logistiche registrate
 * @params un puntatore al gestore della rete logistica
 * @return un array di puntatori alle zone logistiche, oppure NULL in caso di errore
 */
ZonaLogistica* getZoneLogistiche(DeliveryManager manager);

/*
 * Funzione per ottenere tutti i centri di smistamento registrati
 * @params un puntatore al gestore della rete logistica
 * @return un array di puntatori ai centri di smistamento, oppure NULL in caso di errore
 */
CentroSmistamento* getCentriSmistamento(DeliveryManager manager);

/*
 * Funzione per ottenere un veicolo dato il suo ID
 * @params un puntatore al gestore della rete logistica, la targa del veicolo
 * @return un puntatore al veicolo, oppure NULL se non trovato
 */
Veicolo getVeicoloByTarga(DeliveryManager manager, char* targa);

/*
 * Funzione per ottenere un carico dato il suo ID
 * @params un puntatore al gestore della rete logistica, l'ID del carico
 * @return un puntatore al carico, oppure NULL se non trovato
 */
Carico getCaricoById(DeliveryManager manager, int id);

/*
 * Funzione per ottenere una missione dato il suo ID
 * @params un puntatore al gestore della rete logistica, l'ID della missione
 * @return un puntatore alla missione, oppure NULL se non trovata
 */
Missione getMissioneById(DeliveryManager manager, int id);

/*
 * Funzione per ottenere una zona logistica dato il suo nome
 * @params un puntatore al gestore della rete logistica, il nome della zona logistica
 * @return un puntatore alla zona logistica, oppure NULL se non trovata
 */
ZonaLogistica getZonaLogisticaByNome(DeliveryManager manager, char* nome);

/*
 * Funzione per ottenere un centro di smistamento dato il suo nome
 * @params un puntatore al gestore della rete logistica, il nome del centro di smistamento
 * @return un puntatore al centro di smistamento, oppure NULL se non trovato
 */
CentroSmistamento getCentroSmistamentoByNome(DeliveryManager manager, char* nome);

/*
 * Funzione per ottenere un punto di consegna dato il suo nome
 * @params un puntatore al gestore della rete logistica, il nome del punto di consegna
 * @return un puntatore al punto di consegna, oppure NULL se non trovato
 */
PuntoConsegna getPuntoConsegnaByNome(DeliveryManager manager, char* nome);

/*
 * Funzione per ottenere il numero di veicoli registrati
 * @params un puntatore al gestore della rete logistica
 * @return il numero di veicoli, oppure -1 in caso di errore
 */
int getNumVeicoli(DeliveryManager manager);

/*
 * Funzione per ottenere il numero di carichi registrati
 * @params un puntatore al gestore della rete logistica
 * @return il numero di carichi, oppure -1 in caso di errore
 */
int getNumCarichi(DeliveryManager manager);

/*
 * Funzione per ottenere il numero di missioni registrate
 * @params un puntatore al gestore della rete logistica
 * @return il numero di missioni, oppure -1 in caso di errore
 */
int getNumMissioni(DeliveryManager manager);

/*
 * Funzione per ottenere il numero di zone logistiche registrate
 * @params un puntatore al gestore della rete logistica
 * @return il numero di zone logistiche, oppure -1 in caso di errore
 */
int getNumZoneLogistiche(DeliveryManager manager);

/*
 * Funzione per ottenere il numero di centri di smistamento registrati
 * @params un puntatore al gestore della rete logistica
 * @return il numero di centri di smistamento, oppure -1 in caso di errore
 */
int getNumCentriSmistamento(DeliveryManager manager);

/*
 * Funzione personalizzata: Calcola l'efficienza dei veicoli
 * Questa funzione calcola un punteggio di efficienza per ogni veicolo
 * basato sul numero di consegne completate, il tempo medio di consegna
 * e il carico medio trasportato.
 * @params un puntatore al gestore della rete logistica
 * @return un array di double con i punteggi di efficienza, oppure NULL in caso di errore
 */
double* calcolaEfficienzaVeicoli(DeliveryManager manager);

#endif /* DELIVERY_MANAGER_H */



