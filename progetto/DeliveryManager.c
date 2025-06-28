#include "DeliveryManager.h"
#include "dynamic_array.h"
#include "weighted_directed_graph.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Struttura interna del DeliveryManager
struct DeliveryManager {
    weighted_direct_graph area_metropolitana;
    dynamic_array missioni;        // Array di Missione
    dynamic_array carichi;         // Array di Carico
    dynamic_array veicoli;         // Array di Veicolo
    dynamic_array zone_logistiche; // Array di ZonaLogistica
    dynamic_array centri_smistamento; // Array di CentroSmistamento
    int next_carico_id;
    int next_missione_id;
};

// Funzioni di supporto per confronti
static int compare_veicoli_by_targa(const void* a, const void* b) {
    Veicolo v1 = *(Veicolo*)a;
    Veicolo v2 = *(Veicolo*)b;
    return strcmp(veicolo_get_targa(v1), veicolo_get_targa(v2));
}

static int compare_carichi_by_id(const void* a, const void* b) {
    Carico c1 = *(Carico*)a;
    Carico c2 = *(Carico*)b;
    int id1 = carico_get_id(c1);
    int id2 = carico_get_id(c2);
    return (id1 > id2) - (id1 < id2);
}

static int compare_missioni_by_id(const void* a, const void* b) {
    Missione m1 = *(Missione*)a;
    Missione m2 = *(Missione*)b;
    int id1 = missione_get_id(m1);
    int id2 = missione_get_id(m2);
    return (id1 > id2) - (id1 < id2);
}

static int compare_zone_by_nome(const void* a, const void* b) {
    ZonaLogistica z1 = *(ZonaLogistica*)a;
    ZonaLogistica z2 = *(ZonaLogistica*)b;
    return strcmp(zona_logistica_get_nome(z1), zona_logistica_get_nome(z2));
}

static int compare_centri_by_nome(const void* a, const void* b) {
    CentroSmistamento c1 = *(CentroSmistamento*)a;
    CentroSmistamento c2 = *(CentroSmistamento*)b;
    return strcmp(centro_smistamento_get_nome(c1), centro_smistamento_get_nome(c2));
}

// F0. Creare un nuovo gestore della rete logistica
DeliveryManager createManager() {
    DeliveryManager manager = malloc(sizeof(struct DeliveryManager));
    if (!manager) return NULL;
    
    manager->area_metropolitana = weighted_direct_graph_create();
    manager->missioni = dynamic_array_create(10, sizeof(Missione));
    manager->carichi = dynamic_array_create(20, sizeof(Carico));
    manager->veicoli = dynamic_array_create(10, sizeof(Veicolo));
    manager->zone_logistiche = dynamic_array_create(5, sizeof(ZonaLogistica));
    manager->centri_smistamento = dynamic_array_create(5, sizeof(CentroSmistamento));
    manager->next_carico_id = 1;
    manager->next_missione_id = 1;
    
    // Verifica che tutte le allocazioni siano riuscite
    if (!manager->area_metropolitana || !manager->missioni || !manager->carichi || 
        !manager->veicoli || !manager->zone_logistiche || !manager->centri_smistamento) {
        destroyManager(&manager);
        return NULL;
    }
    
    return manager;
}

// Distruggere il gestore della rete logistica
void destroyManager(DeliveryManager* _manager) {
    if (!_manager || !*_manager) return;
    
    DeliveryManager manager = *_manager;
    
    // Libera gli array dinamici
    if (manager->veicoli) {
        for (int i = 0; i < dynamic_array_size(manager->veicoli); i++) {
            Veicolo* v = (Veicolo*)dynamic_array_get_at(manager->veicoli, i);
            if (v && *v) veicolo_destroy(v);
        }
        dynamic_array_destroy(&manager->veicoli, NULL);
    }
    
    if (manager->carichi) {
        for (int i = 0; i < dynamic_array_size(manager->carichi); i++) {
            Carico* c = (Carico*)dynamic_array_get_at(manager->carichi, i);
            if (c && *c) carico_destroy(c);
        }
        dynamic_array_destroy(&manager->carichi, NULL);
    }
    
    if (manager->missioni) {
        for (int i = 0; i < dynamic_array_size(manager->missioni); i++) {
            Missione* m = (Missione*)dynamic_array_get_at(manager->missioni, i);
            if (m && *m) missione_destroy(m);
        }
        dynamic_array_destroy(&manager->missioni, NULL);
    }
    
    if (manager->zone_logistiche) {
        for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
            ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
            if (z && *z) zona_logistica_destroy(z);
        }
        dynamic_array_destroy(&manager->zone_logistiche, NULL);
    }
    
    if (manager->centri_smistamento) {
        for (int i = 0; i < dynamic_array_size(manager->centri_smistamento); i++) {
            CentroSmistamento* c = (CentroSmistamento*)dynamic_array_get_at(manager->centri_smistamento, i);
            if (c && *c) centro_smistamento_destroy(c);
        }
        dynamic_array_destroy(&manager->centri_smistamento, NULL);
    }
    
    if (manager->area_metropolitana) {
        weighted_direct_graph_destroy(&manager->area_metropolitana);
    }
    
    free(manager);
    *_manager = NULL;
}

// F1. Aggiungere una nuova zona logistica
int createZonaLogistica(DeliveryManager manager, char* nome) {
    if (!manager || !nome) return 1;
    
    // Verifica che il nome non sia già presente
    for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
        if (z && *z && strcmp(zona_logistica_get_nome(*z), nome) == 0) {
            return 2; // Nome già presente
        }
    }
    
    // Genera un ID per la zona logistica
    int id = dynamic_array_size(manager->zone_logistiche) + 1;
    
    ZonaLogistica zona = zona_logistica_create(id, nome);
    if (!zona) return 1;
    
    if (dynamic_array_append(manager->zone_logistiche, &zona) != DYN_ARRAY_SUCCESS) {
        zona_logistica_destroy(&zona);
        return 3; // Non c'è più spazio
    }
    
    return 0;
}

// Creare un nuovo punto di consegna
int createPuntoConsegna(DeliveryManager manager, char* nome, int priorita, int orario, TipoPuntoConsegna tipo, char* zona_logistica_nome) {
    if (!manager || !nome || !zona_logistica_nome) return 1;
    
    // Trova la zona logistica
    ZonaLogistica zona = NULL;
    for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
        if (z && *z && strcmp(zona_logistica_get_nome(*z), zona_logistica_nome) == 0) {
            zona = *z;
            break;
        }
    }
    
    if (!zona) return 3; // Zona logistica non esiste
    
    // Verifica che il nome del punto non sia già presente
    PuntoConsegna punto_esistente = getPuntoConsegnaByNome(manager, nome);
    if (punto_esistente) return 2; // Nome già presente
    
    // Crea un nodo nel grafo per il punto di consegna
    weighted_direct_graph_node_id nodo_id = weighted_direct_graph_add_node(manager->area_metropolitana, 0, NULL);
    if (nodo_id < 0) return 1;
    
    Node nodo = weighted_direct_graph_get_node(manager->area_metropolitana, nodo_id);
    
    // Genera un ID per il punto di consegna
    int id = 0;
    for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
        if (z && *z) {
            id += zona_logistica_get_num_punti_consegna(*z);
        }
    }
    id += 1;
    
    // Crea il punto di consegna
    PuntoConsegna punto = punto_consegna_create(id, nome, priorita, orario, tipo, nodo, zona);
    if (!punto) return 1;
    
    // Aggiunge il punto alla zona logistica
    if (zona_logistica_add_punto_consegna(zona, punto) != 0) {
        punto_consegna_destroy(&punto);
        return 4; // Non c'è più spazio
    }
    
    return 0;
}

// Creare un nuovo centro di smistamento
int createCentroSmistamento(DeliveryManager manager, char* nome) {
    if (!manager || !nome) return 1;
    
    // Verifica che il nome non sia già presente
    for (int i = 0; i < dynamic_array_size(manager->centri_smistamento); i++) {
        CentroSmistamento* c = (CentroSmistamento*)dynamic_array_get_at(manager->centri_smistamento, i);
        if (c && *c && strcmp(centro_smistamento_get_nome(*c), nome) == 0) {
            return 2; // Nome già presente
        }
    }
    
    // Crea un nodo nel grafo per il centro di smistamento
    weighted_direct_graph_node_id nodo_id = weighted_direct_graph_add_node(manager->area_metropolitana, 0, NULL);
    if (nodo_id < 0) return 1;
    
    Node nodo = weighted_direct_graph_get_node(manager->area_metropolitana, nodo_id);
    
    // Genera un ID per il centro di smistamento
    int id = dynamic_array_size(manager->centri_smistamento) + 1;
    
    CentroSmistamento centro = centro_smistamento_create(id, nome, nodo);
    if (!centro) return 1;
    
    if (dynamic_array_append(manager->centri_smistamento, &centro) != DYN_ARRAY_SUCCESS) {
        centro_smistamento_destroy(&centro);
        return 3; // Non c'è più spazio
    }
    
    return 0;
}

// F2. Registrare un nuovo veicolo nella flotta
int createVeicolo(DeliveryManager manager, char* targa, int capacita) {
    if (!manager || !targa) return 1;
    
    // Verifica che la targa non sia già presente
    for (int i = 0; i < dynamic_array_size(manager->veicoli); i++) {
        Veicolo* v = (Veicolo*)dynamic_array_get_at(manager->veicoli, i);
        if (v && *v && strcmp(veicolo_get_targa(*v), targa) == 0) {
            return 2; // Targa già presente
        }
    }
    
    Veicolo veicolo = veicolo_create(targa, capacita);
    if (!veicolo) return 1;
    
    if (dynamic_array_append(manager->veicoli, &veicolo) != DYN_ARRAY_SUCCESS) {
        veicolo_destroy(&veicolo);
        return 3; // Non c'è più spazio
    }
    
    return 0;
}

// F3. Inserire un nuovo carico da consegnare
int insertCarico(DeliveryManager manager, int peso, TipoCarico tipologia, char* punto_consegna_nome, int priorita, char* centro_smistamento_nome) {
    if (!manager || !punto_consegna_nome || !centro_smistamento_nome) return 1;
    
    // Trova il punto di consegna
    PuntoConsegna punto = getPuntoConsegnaByNome(manager, punto_consegna_nome);
    if (!punto) return 2; // Punto di consegna non esiste
    
    // Trova il centro di smistamento
    CentroSmistamento centro = getCentroSmistamentoByNome(manager, centro_smistamento_nome);
    if (!centro) return 3; // Centro di smistamento non esiste
    
    // Ottiene i nodi del grafo
    Node nodo_destinazione = punto_consegna_get_nodo(punto);
    Node nodo_centro = centro_smistamento_get_nodo(centro);
    
    // Crea il carico
    Carico carico = carico_create(manager->next_carico_id++, peso, tipologia, nodo_destinazione, priorita, nodo_centro);
    if (!carico) return 1;
    
    // Aggiunge il carico al manager
    if (dynamic_array_append(manager->carichi, &carico) != DYN_ARRAY_SUCCESS) {
        carico_destroy(&carico);
        return 4; // Non c'è più spazio
    }
    
    // Aggiunge il carico alla coda del centro di smistamento
    if (centro_smistamento_add_carico(centro, carico, priorita) != 0) {
        // Rimuove il carico dal manager se non può essere aggiunto al centro
        dynamic_array_remove_at(manager->carichi, dynamic_array_size(manager->carichi) - 1, NULL);
        carico_destroy(&carico);
        return 1;
    }
    
    return 0;
}

// F4. Mettere un veicolo in coda per il carico
int addVeicoloToCoda(DeliveryManager manager, char* targa, char* centro_smistamento_nome) {
    if (!manager || !targa || !centro_smistamento_nome) return 1;
    
    // Trova il veicolo
    Veicolo veicolo = getVeicoloByTarga(manager, targa);
    if (!veicolo) return 2; // Veicolo non esiste
    
    // Verifica che il veicolo sia disponibile
    if (veicolo_get_stato_operativo(veicolo) != STATO_DISPONIBILE) {
        return 4; // Veicolo non disponibile
    }
    
    // Trova il centro di smistamento
    CentroSmistamento centro = getCentroSmistamentoByNome(manager, centro_smistamento_nome);
    if (!centro) return 3; // Centro di smistamento non esiste
    
    // Aggiunge il veicolo alla coda del centro
    if (centro_smistamento_add_veicolo(centro, veicolo) != 0) {
        return 1;
    }
    
    return 0;
}

// Assegnare una missione ad un veicolo
int addTask(DeliveryManager manager, Veicolo veicolo, Carico carico) {
    if (!manager) return 1;
    if (!veicolo) return 2;
    if (!carico) return 3;
    
    // Crea la missione
    Missione missione = missione_create(manager->next_missione_id++, veicolo);
    if (!missione) return 1;
    
    // Aggiunge il carico alla missione
    if (missione_add_carico(missione, carico) != 0) {
        missione_destroy(&missione);
        return 1;
    }
    
    // Imposta la missione per il carico
    if (carico_set_missione(carico, missione) != 0) {
        missione_destroy(&missione);
        return 1;
    }
    
    // Aggiunge il carico al veicolo
    if (veicolo_add_carico(veicolo, carico) != 0) {
        carico_set_missione(carico, NULL);
        missione_destroy(&missione);
        return 1;
    }
    
    // Aggiunge la missione al manager
    if (dynamic_array_append(manager->missioni, &missione) != DYN_ARRAY_SUCCESS) {
        veicolo_remove_carico(veicolo, carico);
        carico_set_missione(carico, NULL);
        missione_destroy(&missione);
        return 1;
    }
    
    // Imposta il veicolo come in viaggio
    veicolo_set_stato_operativo(veicolo, STATO_IN_VIAGGIO);
    
    return 0;
}

// F5. Assegnare automaticamente una missione a un veicolo disponibile
Missione addAutoTask(DeliveryManager manager, char* centro_smistamento_nome) {
    if (!manager || !centro_smistamento_nome) return NULL;
    
    // Trova il centro di smistamento
    CentroSmistamento centro = getCentroSmistamentoByNome(manager, centro_smistamento_nome);
    if (!centro) return NULL;
    
    // Prende il prossimo veicolo dalla coda
    Veicolo veicolo = NULL;
    if (centro_smistamento_get_next_veicolo(centro, (void**)&veicolo) != 0 || !veicolo) {
        return NULL;
    }
    
    // Prende il prossimo carico dalla coda
    Carico carico = NULL;
    if (centro_smistamento_get_next_carico(centro, (void**)&carico) != 0 || !carico) {
        return NULL;
    }
    
    // Verifica compatibilità di peso
    if (carico_get_peso(carico) > veicolo_get_capacita(veicolo)) {
        // Rimette il carico in coda se non compatibile
        centro_smistamento_add_carico(centro, carico, carico_get_priorita(carico));
        return NULL;
    }
    
    // Crea la missione
    Missione missione = missione_create(manager->next_missione_id++, veicolo);
    if (!missione) return NULL;
    
    // Aggiunge il carico alla missione
    if (missione_add_carico(missione, carico) != 0) {
        missione_destroy(&missione);
        return NULL;
    }
    
    // Imposta la missione per il carico
    if (carico_set_missione(carico, missione) != 0) {
        missione_destroy(&missione);
        return NULL;
    }
    
    // Aggiunge il carico al veicolo
    if (veicolo_add_carico(veicolo, carico) != 0) {
        carico_set_missione(carico, NULL);
        missione_destroy(&missione);
        return NULL;
    }
    
    // Aggiunge la missione al manager
    if (dynamic_array_append(manager->missioni, &missione) != DYN_ARRAY_SUCCESS) {
        veicolo_remove_carico(veicolo, carico);
        carico_set_missione(carico, NULL);
        missione_destroy(&missione);
        return NULL;
    }
    
    // Imposta il veicolo come in viaggio
    veicolo_set_stato_operativo(veicolo, STATO_IN_VIAGGIO);
    
    // Imposta data inizio missione
    missione_set_data_inizio(missione, time(NULL));
    
    return missione;
}

// F6. Registrare l'esito di una missione di consegna
int registraEsitoMissione(DeliveryManager manager, int id_missione, StatoMissione stato, const char* nota) {
    if (!manager) return 1;
    
    // Trova la missione
    Missione missione = getMissioneById(manager, id_missione);
    if (!missione) return 2; // Missione non esiste
    
    // Imposta lo stato della missione
    missione_set_stato(missione, stato);
    
    // Aggiunge la nota se fornita
    if (nota) {
        missione_set_nota(missione, nota);
    }
    
    // Imposta data fine missione
    missione_set_data_fine(missione, time(NULL));
    
    // Libera il veicolo
    Veicolo veicolo = missione_get_veicolo(missione);
    if (veicolo) {
        veicolo_set_stato_operativo(veicolo, STATO_DISPONIBILE);
    }
    
    return 0;
}

// F7. Calcolare e restituire statistiche
void getStatistics(DeliveryManager manager) {
    if (!manager) {
        printf("Manager non valido\n");
        return;
    }
    
    printf("\n=== STATISTICHE DELIVERY MANAGER ===\n");
    printf("Numero totale veicoli: %d\n", getNumVeicoli(manager));
    printf("Numero totale carichi: %d\n", getNumCarichi(manager));
    printf("Numero totale missioni: %d\n", getNumMissioni(manager));
    printf("Numero zone logistiche: %d\n", getNumZoneLogistiche(manager));
    printf("Numero centri smistamento: %d\n", getNumCentriSmistamento(manager));
    
    // Tempi medi per tipologia
    double* tempi = getTempiMediPerTipologia(manager);
    if (tempi) {
        printf("\nTempi medi di consegna per tipologia:\n");
        printf("- STANDARD: %.2f ore\n", tempi[0]);
        printf("- REFRIGERATO: %.2f ore\n", tempi[1]);
        printf("- FRAGILE: %.2f ore\n", tempi[2]);
        free(tempi);
    }
    
    // Carico medio per veicolo
    double carico_medio = getCaricoMedioPerVeicolo(manager);
    if (carico_medio >= 0) {
        printf("\nCarico medio per veicolo: %.2f kg\n", carico_medio);
    }
    
    // Consegne per zona
    int* consegne = getNumConsegnePerZona(manager);
    if (consegne) {
        printf("\nConsegne per zona logistica:\n");
        for (int i = 0; i < getNumZoneLogistiche(manager); i++) {
            ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
            if (z && *z) {
                printf("- %s: %d consegne\n", zona_logistica_get_nome(*z), consegne[i]);
            }
        }
        free(consegne);
    }
    
    printf("=====================================\n\n");
}

// Ottenere i tempi medi di consegna per tipologia di carico
double* getTempiMediPerTipologia(DeliveryManager manager) {
    if (!manager) return NULL;
    
    double* tempi = calloc(3, sizeof(double)); // STANDARD, REFRIGERATO, FRAGILE
    int* contatori = calloc(3, sizeof(int));
    
    if (!tempi || !contatori) {
        free(tempi);
        free(contatori);
        return NULL;
    }
    
    // Scorre tutte le missioni completate
    for (int i = 0; i < dynamic_array_size(manager->missioni); i++) {
        Missione* m = (Missione*)dynamic_array_get_at(manager->missioni, i);
        if (m && *m && missione_get_stato(*m) == STATO_MISSIONE_COMPLETATA) {
            time_t inizio = missione_get_data_inizio(*m);
            time_t fine = missione_get_data_fine(*m);
            
            if (inizio > 0 && fine > 0) {
                double ore = difftime(fine, inizio) / 3600.0; // Converti in ore
                
                // Per ogni carico nella missione
                for (int j = 0; j < missione_get_num_carichi(*m); j++) {
                    Carico carico = missione_get_carico(*m, j);
                    if (carico) {
                        TipoCarico tipo = carico_get_tipologia(carico);
                        if (tipo >= CARICO_STANDARD && tipo <= CARICO_FRAGILE) {
                            tempi[tipo-1] += ore;
                            contatori[tipo-1]++;
                        }
                    }
                }
            }
        }
    }
    
    // Calcola le medie
    for (int i = 0; i < 3; i++) {
        if (contatori[i] > 0) {
            tempi[i] /= contatori[i];
        }
    }
    
    free(contatori);
    return tempi;
}

// Ottenere il carico medio per veicolo
double getCaricoMedioPerVeicolo(DeliveryManager manager) {
    if (!manager) return -1;
    
    int num_veicoli = dynamic_array_size(manager->veicoli);
    if (num_veicoli == 0) return 0;
    
    double peso_totale = 0;
    int num_carichi_totali = 0;
    
    // Scorre tutti i veicoli
    for (int i = 0; i < num_veicoli; i++) {
        Veicolo* v = (Veicolo*)dynamic_array_get_at(manager->veicoli, i);
        if (v && *v) {
            // Per ogni carico nel veicolo
            for (int j = 0; j < veicolo_get_num_carichi(*v); j++) {
                Carico carico = veicolo_get_carico(*v, j);
                if (carico) {
                    peso_totale += carico_get_peso(carico);
                    num_carichi_totali++;
                }
            }
        }
    }
    
    return num_carichi_totali > 0 ? peso_totale / num_veicoli : 0;
}

// Ottenere il numero di consegne per zona logistica
int* getNumConsegnePerZona(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int num_zone = dynamic_array_size(manager->zone_logistiche);
    int* consegne = calloc(num_zone, sizeof(int));
    
    if (!consegne) return NULL;
    
    // Scorre tutte le missioni completate
    for (int i = 0; i < dynamic_array_size(manager->missioni); i++) {
        Missione* m = (Missione*)dynamic_array_get_at(manager->missioni, i);
        if (m && *m && missione_get_stato(*m) == STATO_MISSIONE_COMPLETATA) {
            // Per ogni carico nella missione
            for (int j = 0; j < missione_get_num_carichi(*m); j++) {
                Carico carico = missione_get_carico(*m, j);
                if (carico) {
                    Node nodo_destinazione = carico_get_destinazione(carico);
                    
                    // Cerca il punto di consegna corrispondente al nodo
                    for (int k = 0; k < num_zone; k++) {
                        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, k);
                        if (z && *z) {
                            for (int l = 0; l < zona_logistica_get_num_punti_consegna(*z); l++) {
                                PuntoConsegna punto = zona_logistica_get_punto_consegna(*z, l);
                                if (punto && punto_consegna_get_nodo(punto) == nodo_destinazione) {
                                    consegne[k]++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return consegne;
}

// Ottenere il percorso più breve tra due punti
char** getPercorsoBreve(DeliveryManager manager, char* partenza, char* arrivo) {
    if (!manager || !partenza || !arrivo) return NULL;
    
    // Trova i punti di consegna
    PuntoConsegna punto_partenza = getPuntoConsegnaByNome(manager, partenza);
    PuntoConsegna punto_arrivo = getPuntoConsegnaByNome(manager, arrivo);
    
    if (!punto_partenza || !punto_arrivo) return NULL;
    
    // Ottieni i nodi del grafo
    Node nodo_partenza = punto_consegna_get_nodo(punto_partenza);
    Node nodo_arrivo = punto_consegna_get_nodo(punto_arrivo);
    
    if (!nodo_partenza || !nodo_arrivo) return NULL;
    
    // Calcola il percorso più breve
    weighted_direct_graph_node_id id_partenza = weighted_direct_graph_get_node_id(nodo_partenza);
    weighted_direct_graph_node_id id_arrivo = weighted_direct_graph_get_node_id(nodo_arrivo);
    
    linked_list percorso = weighted_direct_graph_shortest_path(manager->area_metropolitana, id_partenza, id_arrivo);
    
    if (!percorso) return NULL;
    
    // Converti il percorso in array di stringhe
    int lunghezza = linked_list_size(percorso);
    char** nomi = malloc((lunghezza + 1) * sizeof(char*));
    
    if (!nomi) {
        linked_list_destroy(&percorso);
        return NULL;
    }
    
    // Riempi l'array con i nomi dei punti
    for (int i = 0; i < lunghezza; i++) {
        int node_id_value;
        if (linked_list_get_at(percorso, i, &node_id_value) != LINKED_LIST_SUCCESS) continue;
        
        weighted_direct_graph_node_id node_id = (weighted_direct_graph_node_id)node_id_value;
        
        // Trova il punto corrispondente al nodo
        char* nome_punto = "Punto Sconosciuto";
        for (int j = 0; j < dynamic_array_size(manager->zone_logistiche); j++) {
            ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, j);
            if (z && *z) {
                for (int k = 0; k < zona_logistica_get_num_punti_consegna(*z); k++) {
                    PuntoConsegna punto = zona_logistica_get_punto_consegna(*z, k);
                    if (punto) {
                        Node nodo = punto_consegna_get_nodo(punto);
                        if (nodo && weighted_direct_graph_get_node_id(nodo) == node_id) {
                            nome_punto = (char*)punto_consegna_get_nome(punto);
                            break;
                        }
                    }
                }
            }
        }
        
        nomi[i] = malloc(strlen(nome_punto) + 1);
        if (nomi[i]) {
            strcpy(nomi[i], nome_punto);
        }
    }
    
    nomi[lunghezza] = NULL; // Terminatore
    
    linked_list_destroy(&percorso);
    return nomi;
}

// Aggiungere un collegamento tra due punti
int addCollegamento(DeliveryManager manager, char* partenza, char* arrivo, int tempo) {
    if (!manager || !partenza || !arrivo) return 1;
    
    // Trova i punti di consegna
    PuntoConsegna punto_partenza = getPuntoConsegnaByNome(manager, partenza);
    PuntoConsegna punto_arrivo = getPuntoConsegnaByNome(manager, arrivo);
    
    if (!punto_partenza) return 2; // Punto di partenza non esiste
    if (!punto_arrivo) return 3;   // Punto di arrivo non esiste
    
    // Ottieni i nodi del grafo
    Node nodo_partenza = punto_consegna_get_nodo(punto_partenza);
    Node nodo_arrivo = punto_consegna_get_nodo(punto_arrivo);
    
    if (!nodo_partenza || !nodo_arrivo) return 1;
    
    // Aggiunge l'arco al grafo
    weighted_direct_graph_node_id id_partenza = weighted_direct_graph_get_node_id(nodo_partenza);
    weighted_direct_graph_node_id id_arrivo = weighted_direct_graph_get_node_id(nodo_arrivo);
    
    if (weighted_direct_graph_add_edge(manager->area_metropolitana, id_partenza, id_arrivo, tempo) != WDG_SUCCESS) {
        return 1;
    }
    
    return 0;
}

// Funzioni getter per gli array
Veicolo* getVeicoli(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int size = dynamic_array_size(manager->veicoli);
    Veicolo* veicoli = malloc(size * sizeof(Veicolo));
    
    if (!veicoli) return NULL;
    
    for (int i = 0; i < size; i++) {
        Veicolo* v = (Veicolo*)dynamic_array_get_at(manager->veicoli, i);
        veicoli[i] = v ? *v : NULL;
    }
    
    return veicoli;
}

Carico* getCarichi(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int size = dynamic_array_size(manager->carichi);
    Carico* carichi = malloc(size * sizeof(Carico));
    
    if (!carichi) return NULL;
    
    for (int i = 0; i < size; i++) {
        Carico* c = (Carico*)dynamic_array_get_at(manager->carichi, i);
        carichi[i] = c ? *c : NULL;
    }
    
    return carichi;
}

Missione* getMissioni(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int size = dynamic_array_size(manager->missioni);
    Missione* missioni = malloc(size * sizeof(Missione));
    
    if (!missioni) return NULL;
    
    for (int i = 0; i < size; i++) {
        Missione* m = (Missione*)dynamic_array_get_at(manager->missioni, i);
        missioni[i] = m ? *m : NULL;
    }
    
    return missioni;
}

ZonaLogistica* getZoneLogistiche(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int size = dynamic_array_size(manager->zone_logistiche);
    ZonaLogistica* zone = malloc(size * sizeof(ZonaLogistica));
    
    if (!zone) return NULL;
    
    for (int i = 0; i < size; i++) {
        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
        zone[i] = z ? *z : NULL;
    }
    
    return zone;
}

CentroSmistamento* getCentriSmistamento(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int size = dynamic_array_size(manager->centri_smistamento);
    CentroSmistamento* centri = malloc(size * sizeof(CentroSmistamento));
    
    if (!centri) return NULL;
    
    for (int i = 0; i < size; i++) {
        CentroSmistamento* c = (CentroSmistamento*)dynamic_array_get_at(manager->centri_smistamento, i);
        centri[i] = c ? *c : NULL;
    }
    
    return centri;
}

// Funzioni di ricerca
Veicolo getVeicoloByTarga(DeliveryManager manager, char* targa) {
    if (!manager || !targa) return NULL;
    
    for (int i = 0; i < dynamic_array_size(manager->veicoli); i++) {
        Veicolo* v = (Veicolo*)dynamic_array_get_at(manager->veicoli, i);
        if (v && *v && strcmp(veicolo_get_targa(*v), targa) == 0) {
            return *v;
        }
    }
    
    return NULL;
}

Carico getCaricoById(DeliveryManager manager, int id) {
    if (!manager) return NULL;
    
    for (int i = 0; i < dynamic_array_size(manager->carichi); i++) {
        Carico* c = (Carico*)dynamic_array_get_at(manager->carichi, i);
        if (c && *c && carico_get_id(*c) == id) {
            return *c;
        }
    }
    
    return NULL;
}

Missione getMissioneById(DeliveryManager manager, int id) {
    if (!manager) return NULL;
    
    for (int i = 0; i < dynamic_array_size(manager->missioni); i++) {
        Missione* m = (Missione*)dynamic_array_get_at(manager->missioni, i);
        if (m && *m && missione_get_id(*m) == id) {
            return *m;
        }
    }
    
    return NULL;
}

ZonaLogistica getZonaLogisticaByNome(DeliveryManager manager, char* nome) {
    if (!manager || !nome) return NULL;
    
    for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
        if (z && *z && strcmp(zona_logistica_get_nome(*z), nome) == 0) {
            return *z;
        }
    }
    
    return NULL;
}

CentroSmistamento getCentroSmistamentoByNome(DeliveryManager manager, char* nome) {
    if (!manager || !nome) return NULL;
    
    for (int i = 0; i < dynamic_array_size(manager->centri_smistamento); i++) {
        CentroSmistamento* c = (CentroSmistamento*)dynamic_array_get_at(manager->centri_smistamento, i);
        if (c && *c && strcmp(centro_smistamento_get_nome(*c), nome) == 0) {
            return *c;
        }
    }
    
    return NULL;
}

PuntoConsegna getPuntoConsegnaByNome(DeliveryManager manager, char* nome) {
    if (!manager || !nome) return NULL;
    
    // Cerca in tutte le zone logistiche
    for (int i = 0; i < dynamic_array_size(manager->zone_logistiche); i++) {
        ZonaLogistica* z = (ZonaLogistica*)dynamic_array_get_at(manager->zone_logistiche, i);
        if (z && *z) {
            for (int j = 0; j < zona_logistica_get_num_punti_consegna(*z); j++) {
                PuntoConsegna punto = zona_logistica_get_punto_consegna(*z, j);
                if (punto && strcmp(punto_consegna_get_nome(punto), nome) == 0) {
                    return punto;
                }
            }
        }
    }
    
    return NULL;
}

// Funzioni per ottenere i contatori
int getNumVeicoli(DeliveryManager manager) {
    if (!manager) return -1;
    return dynamic_array_size(manager->veicoli);
}

int getNumCarichi(DeliveryManager manager) {
    if (!manager) return -1;
    return dynamic_array_size(manager->carichi);
}

int getNumMissioni(DeliveryManager manager) {
    if (!manager) return -1;
    return dynamic_array_size(manager->missioni);
}

int getNumZoneLogistiche(DeliveryManager manager) {
    if (!manager) return -1;
    return dynamic_array_size(manager->zone_logistiche);
}

int getNumCentriSmistamento(DeliveryManager manager) {
    if (!manager) return -1;
    return dynamic_array_size(manager->centri_smistamento);
}

// F8. Funzione personalizzata: Calcola l'efficienza dei veicoli
double* calcolaEfficienzaVeicoli(DeliveryManager manager) {
    if (!manager) return NULL;
    
    int num_veicoli = dynamic_array_size(manager->veicoli);
    if (num_veicoli == 0) return NULL;
    
    double* efficienze = calloc(num_veicoli, sizeof(double));
    if (!efficienze) return NULL;
    
    // Calcola l'efficienza per ogni veicolo
    for (int i = 0; i < num_veicoli; i++) {
        Veicolo* v = (Veicolo*)dynamic_array_get_at(manager->veicoli, i);
        if (v && *v) {
            int missioni_completate = 0;
            double tempo_totale = 0;
            double peso_totale = 0;
            int num_carichi = 0;
            
            // Conta le missioni completate per questo veicolo
            for (int j = 0; j < dynamic_array_size(manager->missioni); j++) {
                Missione* m = (Missione*)dynamic_array_get_at(manager->missioni, j);
                if (m && *m && missione_get_veicolo(*m) == *v) {
                    if (missione_get_stato(*m) == STATO_MISSIONE_COMPLETATA) {
                        missioni_completate++;
                        
                        time_t inizio = missione_get_data_inizio(*m);
                        time_t fine = missione_get_data_fine(*m);
                        
                        if (inizio > 0 && fine > 0) {
                            tempo_totale += difftime(fine, inizio) / 3600.0; // in ore
                        }
                        
                        // Somma il peso dei carichi
                        for (int k = 0; k < missione_get_num_carichi(*m); k++) {
                            Carico carico = missione_get_carico(*m, k);
                            if (carico) {
                                peso_totale += carico_get_peso(carico);
                                num_carichi++;
                            }
                        }
                    }
                }
            }
            
            // Calcola il punteggio di efficienza
            // Formula: (missioni_completate * peso_medio) / (tempo_medio + 1)
            // Il +1 evita divisioni per zero
            if (missioni_completate > 0) {
                double peso_medio = peso_totale / num_carichi;
                double tempo_medio = tempo_totale / missioni_completate;
                efficienze[i] = (missioni_completate * peso_medio) / (tempo_medio + 1.0);
            } else {
                efficienze[i] = 0.0;
            }
        }
    }
    
    return efficienze;
} 