/*
 * main.c
 *
 * Programma principale per la simulazione di una rete urbana di consegne autonome
 * utilizzando l'ADT DeliveryManager.
 * 
 * Implementa il menu testuale richiesto nell'esercizio 4 dell'esame.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "DeliveryManager.h"

// Dimensioni massime per buffer di input
#define MAX_INPUT_SIZE 100
#define MAX_NOTA_SIZE 200

// Funzione per pulire il buffer di input
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funzione per visualizzare il menu principale
void display_menu() {
  
    printf("██████╗░███████╗██╗░░░░░██╗██╗░░░██╗███████╗██████╗░██╗░░░██╗\n");
    printf("██╔══██╗██╔════╝██║░░░░░██║██║░░░██║██╔════╝██╔══██╗╚██╗░██╔╝\n");
    printf("██║░░██║█████╗░░██║░░░░░██║╚██╗░██╔╝█████╗░░██████╔╝░╚████╔╝░\n");
    printf("██║░░██║██╔══╝░░██║░░░░░██║░╚████╔╝░██╔══╝░░██╔══██╗░░╚██╔╝░░\n");
    printf("██████╔╝███████╗███████╗██║░░╚██╔╝░░███████╗██║░░██║░░░██║░░░\n");
    printf("╚═════╝░╚══════╝╚══════╝╚═╝░░░╚═╝░░░╚══════╝╚═╝░░╚═╝░░░╚═╝░░░\n");

    printf("███╗░░░███╗░█████╗░███╗░░██╗░█████╗░░██████╗░███████╗██████╗░\n");
    printf("████╗░████║██╔══██╗████╗░██║██╔══██╗██╔════╝░██╔════╝██╔══██╗\n");
    printf("██╔████╔██║███████║██╔██╗██║███████║██║░░██╗░█████╗░░██████╔╝\n");
    printf("██║╚██╔╝██║██╔══██║██║╚████║██╔══██║██║░░╚██╗██╔══╝░░██╔══██╗\n");
    printf("██║░╚═╝░██║██║░░██║██║░╚███║██║░░██║╚██████╔╝███████╗██║░░██║\n");
    printf("╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚═╝░░╚═╝\n");
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║                        MENU PRINCIPALE                        ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf(" 1. 🚗  Registrare un nuovo veicolo                            \n");
    printf(" 2. 🗺️  Visualizzare zone logistiche e punti di consegna       \n");
    printf(" 3. 📦  Inserire un nuovo carico da spedire                    \n");
    printf(" 4. 🅿️  Accodare un veicolo al centro di smistamento           \n");
    printf(" 5. 🚚  Assegnare e avviare una missione                       \n");
    printf(" 6. ✅  Registrare l'esito di una missione                     \n");
    printf(" 7. 📊  Visualizzare statistiche aggiornate                    \n");
    printf(" 8. ⚡   Visualizzare efficienza dei veicoli                   \n");
    printf(" 9. ❌  Uscire                                                \n");
    printf("\nSeleziona un'opzione (1-9): ");
}

// Funzione per registrare un nuovo veicolo
void register_new_vehicle(DeliveryManager manager) {
    char targa[MAX_INPUT_SIZE];
    int capacita;
    
    printf("\n=== REGISTRAZIONE NUOVO VEICOLO ===\n");
    printf("Inserisci targa del veicolo: ");
    scanf("%s", targa);
    clear_input_buffer();
    
    printf("Inserisci capacità massima (kg): ");
    scanf("%d", &capacita);
    clear_input_buffer();
    
    int result = createVeicolo(manager, targa, capacita);
    
    switch (result) {
        case 0:
            printf("Veicolo %s registrato con successo!\n", targa);
            break;
        case 2:
            printf("Errore: targa %s già presente nel sistema.\n", targa);
            break;
        case 3:
            printf("Errore: spazio insufficiente per registrare il veicolo.\n");
            break;
        default:
            printf("Errore durante la registrazione del veicolo.\n");
    }
}

// Funzione per visualizzare zone logistiche e punti di consegna
void display_zones_and_points(DeliveryManager manager) {
    printf("\n=== ZONE LOGISTICHE E PUNTI DI CONSEGNA ===\n");
    
    ZonaLogistica* zone = getZoneLogistiche(manager);
    int num_zone = getNumZoneLogistiche(manager);
    
    if (zone == NULL || num_zone <= 0) {
        printf("Nessuna zona logistica registrata.\n");
        return;
    }
    
    for (int i = 0; i < num_zone; i++) {
        ZonaLogistica zona = zone[i];
        printf("\nZONA: %s\n", zona_logistica_get_nome(zona));
        printf("----------------------------\n");
        
        int num_punti = zona_logistica_get_num_punti_consegna(zona);
        if (num_punti <= 0) {
            printf("Nessun punto di consegna in questa zona.\n");
            continue;
        }
        
        printf("%-20s | %-10s | %-12s | %-10s\n", "Nome", "Priorità", "Tipo", "Orario");
        printf("---------------------------------------------------------------\n");
        
        for (int j = 0; j < num_punti; j++) {
            PuntoConsegna punto = zona_logistica_get_punto_consegna(zona, j);
            if (punto == NULL) continue;
            
            int orario = punto_consegna_get_orario(punto);
            int ora = orario / 100;
            int minuti = orario % 100;
            
            printf("%-20s | %-10d | %-12s | %02d:%02d\n", 
                   punto_consegna_get_nome(punto),
                   punto_consegna_get_priorita(punto),
                   punto_consegna_tipo_to_string(punto_consegna_get_tipo(punto)),
                   ora, minuti);
        }
    }
}

// Funzione per inserire un nuovo carico
void register_new_cargo(DeliveryManager manager) {
    char punto_consegna[MAX_INPUT_SIZE];
    char centro_smistamento[MAX_INPUT_SIZE];
    int peso, priorita;
    int tipologia_int;
    TipoCarico tipologia;
    
    printf("\n=== INSERIMENTO NUOVO CARICO ===\n");
    
    printf("Inserisci peso del carico (kg): ");
    scanf("%d", &peso);
    clear_input_buffer();
    
    printf("Inserisci tipologia (1=Standard, 2=Refrigerato, 3=Fragile): ");
    scanf("%d", &tipologia_int);
    clear_input_buffer();
    
    if (tipologia_int < 1 || tipologia_int > 3) {
        printf("Tipologia non valida. Utilizzo tipologia standard.\n");
        tipologia = CARICO_STANDARD;
    } else {
        tipologia = (TipoCarico)tipologia_int;
    }
    
    printf("Inserisci nome del punto di consegna: ");
    fgets(punto_consegna, MAX_INPUT_SIZE, stdin);
    punto_consegna[strcspn(punto_consegna, "\n")] = '\0'; // Rimuove il newline
    
    printf("Inserisci priorità (1-5, dove 5 è la più alta): ");
    scanf("%d", &priorita);
    clear_input_buffer();
    
    if (priorita < 1 || priorita > 5) {
        printf("Priorità non valida. Utilizzo priorità 1.\n");
        priorita = 1;
    }
    
    printf("Inserisci nome del centro di smistamento: ");
    fgets(centro_smistamento, MAX_INPUT_SIZE, stdin);
    centro_smistamento[strcspn(centro_smistamento, "\n")] = '\0'; // Rimuove il newline
    
    int result = insertCarico(manager, peso, tipologia, punto_consegna, priorita, centro_smistamento);
    
    switch (result) {
        case 0:
            printf("Carico inserito con successo!\n");
            break;
        case 2:
            printf("Errore: punto di consegna '%s' non trovato.\n", punto_consegna);
            break;
        case 3:
            printf("Errore: centro di smistamento '%s' non trovato.\n", centro_smistamento);
            break;
        case 4:
            printf("Errore: spazio insufficiente per inserire il carico.\n");
            break;
        default:
            printf("Errore durante l'inserimento del carico.\n");
    }
}

// Funzione per accodare un veicolo al centro di smistamento
void queue_vehicle(DeliveryManager manager) {
    char targa[MAX_INPUT_SIZE];
    char centro_smistamento[MAX_INPUT_SIZE];
    
    printf("\n=== ACCODAMENTO VEICOLO ===\n");
    
    printf("Inserisci targa del veicolo: ");
    fgets(targa, MAX_INPUT_SIZE, stdin);
    targa[strcspn(targa, "\n")] = '\0'; // Rimuove il newline
    
    printf("Inserisci nome del centro di smistamento: ");
    fgets(centro_smistamento, MAX_INPUT_SIZE, stdin);
    centro_smistamento[strcspn(centro_smistamento, "\n")] = '\0'; // Rimuove il newline
    
    int result = addVeicoloToCoda(manager, targa, centro_smistamento);
    
    switch (result) {
        case 0:
            printf("Veicolo %s accodato con successo al centro di smistamento %s!\n", 
                   targa, centro_smistamento);
            break;
        case 2:
            printf("Errore: veicolo con targa '%s' non trovato.\n", targa);
            break;
        case 3:
            printf("Errore: centro di smistamento '%s' non trovato.\n", centro_smistamento);
            break;
        case 4:
            printf("Errore: il veicolo non è disponibile.\n");
            break;
        default:
            printf("Errore durante l'accodamento del veicolo.\n");
    }
}

// Funzione per assegnare e avviare una missione
void assign_mission(DeliveryManager manager) {
    char centro_smistamento[MAX_INPUT_SIZE];
    
    printf("\n=== ASSEGNAZIONE MISSIONE ===\n");
    
    printf("Inserisci nome del centro di smistamento: ");
    fgets(centro_smistamento, MAX_INPUT_SIZE, stdin);
    centro_smistamento[strcspn(centro_smistamento, "\n")] = '\0'; // Rimuove il newline
    
    Missione missione = addAutoTask(manager, centro_smistamento);
    
    if (missione == NULL) {
        printf("Impossibile assegnare una missione. Verifica che ci siano veicoli disponibili e carichi da consegnare.\n");
        return;
    }
    
    Veicolo veicolo = missione_get_veicolo(missione);
    
    printf("\nMissione #%d assegnata con successo!\n", missione_get_id(missione));
    printf("Veicolo: %s\n", veicolo_get_targa(veicolo));
    printf("Stato: %s\n", missione_stato_to_string(missione_get_stato(missione)));
    printf("Carichi assegnati: %d\n", missione_get_num_carichi(missione));
    
    // Dettagli sui carichi
    printf("\nDettaglio carichi:\n");
    printf("%-5s | %-10s | %-12s | %-20s\n", "ID", "Peso (kg)", "Tipologia", "Destinazione");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < missione_get_num_carichi(missione); i++) {
        Carico carico = missione_get_carico(missione, i);
        if (carico == NULL) continue;
        
        printf("%-5d | %-10d | %-12s | %-20s\n", 
               carico_get_id(carico),
               carico_get_peso(carico),
               carico_tipo_to_string(carico_get_tipologia(carico)),
               "Punto di consegna"); // Qui idealmente si dovrebbe mostrare il nome del punto di consegna
    }
}

// Funzione per registrare l'esito di una missione
void register_mission_outcome(DeliveryManager manager) {
    int id_missione;
    int stato_int;
    StatoMissione stato;
    char nota[MAX_NOTA_SIZE];
    
    printf("\n=== REGISTRAZIONE ESITO MISSIONE ===\n");
    
    printf("Inserisci ID della missione: ");
    scanf("%d", &id_missione);
    clear_input_buffer();
    
    printf("Inserisci stato (2=Completata, 3=Fallita): ");
    scanf("%d", &stato_int);
    clear_input_buffer();
    
    if (stato_int != 2 && stato_int != 3) {
        printf("Stato non valido. Utilizzo stato 'Completata'.\n");
        stato = STATO_MISSIONE_COMPLETATA;
    } else {
        stato = (StatoMissione)stato_int;
    }
    
    printf("Inserisci nota (max 200 caratteri): ");
    fgets(nota, MAX_NOTA_SIZE, stdin);
    nota[strcspn(nota, "\n")] = '\0'; // Rimuove il newline finale
    
    int result = registraEsitoMissione(manager, id_missione, stato, nota);
    
    switch (result) {
        case 0:
            printf("Esito della missione #%d registrato con successo!\n", id_missione);
            break;
        case 2:
            printf("Errore: missione #%d non trovata.\n", id_missione);
            break;
        default:
            printf("Errore durante la registrazione dell'esito della missione.\n");
    }
}

// Funzione per visualizzare le statistiche
void display_statistics(DeliveryManager manager) {
    printf("\n=== STATISTICHE ===\n");
    
    // Tempi medi per tipologia
    double* tempi_medi = getTempiMediPerTipologia(manager);
    if (tempi_medi != NULL) {
        printf("\nTempi medi di consegna per tipologia:\n");
        printf("Standard: %.2f minuti\n", tempi_medi[0]);
        printf("Refrigerato: %.2f minuti\n", tempi_medi[1]);
        printf("Fragile: %.2f minuti\n", tempi_medi[2]);
        free(tempi_medi);
    } else {
        printf("\nNessun dato disponibile sui tempi medi di consegna.\n");
    }
    
    // Carico medio per veicolo
    double carico_medio = getCaricoMedioPerVeicolo(manager);
    if (carico_medio >= 0) {
        printf("\nCarico medio per veicolo: %.2f kg\n", carico_medio);
    } else {
        printf("\nNessun dato disponibile sul carico medio per veicolo.\n");
    }
    
    // Numero consegne per zona
    int* consegne_per_zona = getNumConsegnePerZona(manager);
    ZonaLogistica* zone = getZoneLogistiche(manager);
    int num_zone = getNumZoneLogistiche(manager);
    
    if (consegne_per_zona != NULL && zone != NULL && num_zone > 0) {
        printf("\nNumero di consegne per zona logistica:\n");
        for (int i = 0; i < num_zone; i++) {
            printf("%s: %d consegne\n", zona_logistica_get_nome(zone[i]), consegne_per_zona[i]);
        }
        free(consegne_per_zona);
    } else {
        printf("\nNessun dato disponibile sulle consegne per zona.\n");
    }
}

// Funzione personalizzata (F8): visualizzazione efficienza dei veicoli
void display_vehicle_efficiency(DeliveryManager manager) {
    printf("\n=== EFFICIENZA DEI VEICOLI ===\n");
    
    double* efficienza = calcolaEfficienzaVeicoli(manager);
    Veicolo* veicoli = getVeicoli(manager);
    int num_veicoli = getNumVeicoli(manager);
    
    if (efficienza == NULL || veicoli == NULL || num_veicoli <= 0) {
        printf("Nessun dato disponibile sull'efficienza dei veicoli.\n");
        return;
    }
    
    printf("%-10s | %-15s | %-15s\n", "Targa", "Stato", "Efficienza (%)");
    printf("------------------------------------------\n");
    
    for (int i = 0; i < num_veicoli; i++) {
        printf("%-10s | %-15s | %-15.2f\n", 
               veicolo_get_targa(veicoli[i]),
               veicolo_stato_to_string(veicolo_get_stato_operativo(veicoli[i])),
               efficienza[i]);
    }
    
    free(efficienza);
}

// Funzione per inizializzare dati di esempio
void initialize_sample_data(DeliveryManager manager) {
    // Creazione zone logistiche
    createZonaLogistica(manager, "Centro Storico");
    createZonaLogistica(manager, "Zona Industriale");
    createZonaLogistica(manager, "Periferia Nord");
    
    // Creazione punti di consegna
    createPuntoConsegna(manager, "Farmacia Centrale", 4, 900, TIPO_FRAGILE, "Centro Storico");
    createPuntoConsegna(manager, "Hotel Roma", 3, 1000, TIPO_STANDARD, "Centro Storico");
    createPuntoConsegna(manager, "Magazzino Tech", 2, 1100, TIPO_REFRIGERATO, "Zona Industriale");
    createPuntoConsegna(manager, "Villa Verde", 5, 830, TIPO_STANDARD, "Periferia Nord");
    createPuntoConsegna(manager, "Supermercato Sigma", 1, 1030, TIPO_REFRIGERATO, "Periferia Nord");
    
    // Creazione centro di smistamento
    createCentroSmistamento(manager, "Centro Principale");
    
    // Creazione veicoli
    createVeicolo(manager, "VCL-101", 100);
    createVeicolo(manager, "VCL-202", 150);
    createVeicolo(manager, "VCL-303", 80);
    
    // Aggiunta collegamenti tra zone
    ZonaLogistica centro = getZonaLogisticaByNome(manager, "Centro Storico");
    ZonaLogistica industriale = getZonaLogisticaByNome(manager, "Zona Industriale");
    ZonaLogistica periferia = getZonaLogisticaByNome(manager, "Periferia Nord");
    
    if (centro && industriale && periferia) {
        PuntoConsegna farmacia = getPuntoConsegnaByNome(manager, "Farmacia Centrale");
        PuntoConsegna hotel = getPuntoConsegnaByNome(manager, "Hotel Roma");
        PuntoConsegna magazzino = getPuntoConsegnaByNome(manager, "Magazzino Tech");
        PuntoConsegna villa = getPuntoConsegnaByNome(manager, "Villa Verde");
        PuntoConsegna supermercato = getPuntoConsegnaByNome(manager, "Supermercato Sigma");
        
        if (farmacia && hotel && magazzino && villa && supermercato) {
            // Aggiungi collegamenti tra i punti di consegna
            addCollegamento(manager, "Farmacia Centrale", "Hotel Roma", 5);
            addCollegamento(manager, "Hotel Roma", "Magazzino Tech", 15);
            addCollegamento(manager, "Magazzino Tech", "Villa Verde", 20);
            addCollegamento(manager, "Villa Verde", "Supermercato Sigma", 10);
            addCollegamento(manager, "Farmacia Centrale", "Villa Verde", 25);
        }
    }
    
    // Inserimento carichi di esempio
    insertCarico(manager, 20, CARICO_STANDARD, "Hotel Roma", 3, "Centro Principale");
    insertCarico(manager, 15, CARICO_FRAGILE, "Farmacia Centrale", 4, "Centro Principale");
    insertCarico(manager, 30, CARICO_REFRIGERATO, "Magazzino Tech", 2, "Centro Principale");
    insertCarico(manager, 10, CARICO_STANDARD, "Villa Verde", 5, "Centro Principale");
    insertCarico(manager, 25, CARICO_REFRIGERATO, "Supermercato Sigma", 1, "Centro Principale");
    
    printf("Dati di esempio inizializzati con successo!\n");
}

int main() {
    DeliveryManager manager = createManager();
    if (manager == NULL) {
        printf("Errore: impossibile creare il gestore della rete logistica.\n");
        return 1;
    }
    
    // Inizializzazione dati di esempio
    initialize_sample_data(manager);
    
    int choice = 0;
    do {
        display_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                register_new_vehicle(manager);
                break;
            case 2:
                display_zones_and_points(manager);
                break;
            case 3:
                register_new_cargo(manager);
                break;
            case 4:
                queue_vehicle(manager);
                break;
            case 5:
                assign_mission(manager);
                break;
            case 6:
                register_mission_outcome(manager);
                break;
            case 7:
                display_statistics(manager);
                break;
            case 8:
                display_vehicle_efficiency(manager);
                break;
            case 9:
                printf("\nUscita in corso...\n");
                break;
            default:
                printf("\nScelta non valida. Riprova.\n");
        }
        
        if (choice != 9) {
            printf("\nPremi INVIO per continuare...");
            getchar();
        }
        
    } while (choice != 9);
    
    destroyManager(&manager);
    printf("Grazie per aver utilizzato DeliveryManager!\n");
    
    return 0;
} 