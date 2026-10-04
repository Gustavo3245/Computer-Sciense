#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- Configurações do Exercício ---
#define NUM_PAGINAS_VIRTUAIS 16
#define NUM_MOLDURAS_FISICAS 8
#define MAX_ACESSOS 25

// --- Estrutura para a Tabela de Páginas ---
typedef struct {
    int moldura_id;          // Número da Moldura de Página (MP). -1 se ausente.
    bool presente;           // Bit Presente/Ausente.
    bool modificada;         // Bit Modificada (M).
    bool referenciada;       // Bit Referenciada (R). (Usado para o MRU)
    int ultima_referencia;   // Tempo do último acesso (valor mais ALTO = mais recente)
} EntradaTabelaPagina;

// --- Estrutura para a Sequência de Acessos ---
typedef struct {
    int pagina_virtual;
    char tipo_acesso; // 'R' para Referência, 'M' para Modificação
} Acesso;

// --- Estado Inicial da Simulação ---
// Mapeamento PV -> MP (da figura) e R=1, M=0 para todas as páginas mapeadas
void inicializar_tabela(EntradaTabelaPagina tabela[], int *tempo_global) {
    // Inicializa todas as páginas como ausentes
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        tabela[i] = (EntradaTabelaPagina){-1, false, false, false, 0};
    }
    
    // Mapeamento inicial com tempo de referência (baseado na ordem 3, 1, 0, 5, 4, 9, 2, 11)
    // Usamos a ordem para determinar o "tempo" inicial (1 a 8)
    
    // PV 3: Ordem 1
    tabela[3] = (EntradaTabelaPagina){5, true, false, true, 1}; 
    // PV 1: Ordem 2
    tabela[1] = (EntradaTabelaPagina){1, true, false, true, 2}; 
    // PV 0: Ordem 3
    tabela[0] = (EntradaTabelaPagina){3, true, false, true, 3}; 
    // PV 4: Ordem 4
    tabela[4] = (EntradaTabelaPagina){4, true, false, true, 4}; 
    // PV 9: Ordem 5
    tabela[9] = (EntradaTabelaPagina){6, true, false, true, 5}; 
    // PV 2: Ordem 6
    tabela[2] = (EntradaTabelaPagina){0, true, false, true, 6}; 
    // PV 11: Ordem 7
    tabela[11] = (EntradaTabelaPagina){7, true, false, true, 7}; 
    // PV 6: Ordem 8 (Mais recente no estado inicial)
    tabela[6] = (EntradaTabelaPagina){2, true, false, true, 8}; 
    
    // O tempo global de referência começa após a inicialização
    *tempo_global = 8;
}

// --- Função para selecionar a moldura a ser substituída (MRU) ---
int selecionar_moldura_mru(EntradaTabelaPagina tabela[]) {
    int maior_tempo = -1;
    int moldura_a_substituir = -1;
    int pv_a_substituir = -1;

    // Encontrar a página na memória com o MAIOR 'ultima_referencia' (Mais Recentemente Usada)
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        if (tabela[i].presente) {
            // Se for o primeiro presente encontrado OU se o tempo atual for maior
            if (tabela[i].ultima_referencia > maior_tempo) {
                maior_tempo = tabela[i].ultima_referencia;
                pv_a_substituir = i;
                moldura_a_substituir = tabela[i].moldura_id;
            }
        }
    }

    if (pv_a_substituir != -1) {
        printf("    -> PV %d escolhida (Tempo: %d). M=1: %s. Moldura %d liberada.\n", 
               pv_a_substituir, 
               maior_tempo,
               tabela[pv_a_substituir].modificada ? "Sim" : "Não",
               moldura_a_substituir);
               
        // Simular a escrita no disco (se modificada)
        if (tabela[pv_a_substituir].modificada) {
            // ... (simulação de escrita)
        }

        // Limpar a entrada da página antiga
        tabela[pv_a_substituir] = (EntradaTabelaPagina){-1, false, false, false, 0};
    }

    return moldura_a_substituir; // Retorna o ID da Moldura liberada
}

// --- Função Principal de Simulação ---
void simular_mru() {
    EntradaTabelaPagina tabela[NUM_PAGINAS_VIRTUAIS];
    int tempo_global;
    inicializar_tabela(tabela, &tempo_global);

    // Sequência de acesso do exercício
    const Acesso acessos[MAX_ACESSOS] = {
        {0, 'R'}, {1, 'R'}, {2, 'M'}, {6, 'R'}, {7, 'M'}, {1, 'M'}, {7, 'R'}, {6, 'R'},
        {2, 'R'}, {3, 'R'}, {0, 'M'}, {4, 'R'}, {0, 'R'}, {6, 'M'}, {1, 'R'}, {8, 'R'},
        {12, 'R'}, {8, 'M'}, {2, 'R'}, {15, 'R'}, {6, 'R'}, {0, 'M'}, {3, 'R'}, {5, 'R'},
        {0, 'R'}
    };

    int hit_count = 0;
    int miss_count = 0;

    printf("--- Simulação de Gerenciamento de Memória - Algoritmo MRU (Mais Recentemente Usada) ---\n");
    printf("Molduras Fisicas: %d | Paginas Virtuais: %d\n\n", NUM_MOLDURAS_FISICAS, NUM_PAGINAS_VIRTUAIS);

    for (int i = 0; i < MAX_ACESSOS; i++) {
        int pv = acessos[i].pagina_virtual;
        char tipo = acessos[i].tipo_acesso;
        tempo_global++; // Avança o tempo a cada acesso

        printf("Acesso %2d: (%c) PV %2d | ", i + 1, tipo, pv);

        // 1. Verificar Tabela de Páginas (Hit ou Miss)
        if (tabela[pv].presente) {
            // --- HIT ---
            hit_count++;
            printf("HIT. Moldura %d. ", tabela[pv].moldura_id);

            // Atualizar bits de controle e tempo de referência
            tabela[pv].referenciada = true;
            if (tipo == 'M') {
                tabela[pv].modificada = true;
            }
            tabela[pv].ultima_referencia = tempo_global;
            printf("Tempo atualizado para %d.\n", tempo_global);

        } else {
            // --- MISS ---
            miss_count++;
            printf("MISS. Falta de Pagina.\n");
            
            // 2. Substituição de Página (MRU)
            int moldura_livre = selecionar_moldura_mru(tabela);

            // 3. Carregar Nova Página na Moldura
            tabela[pv].moldura_id = moldura_livre;
            tabela[pv].presente = true;
            tabela[pv].referenciada = true; // R=1
            tabela[pv].modificada = (tipo == 'M');
            tabela[pv].ultima_referencia = tempo_global;

            printf("    -> PV %d carregada na Moldura %d. Tempo %d.\n", pv, moldura_livre, tempo_global);
        }
    }

    printf("\n--- Resultados Finais (MRU) ---\n");
    printf("Total de Acessos: %d\n", MAX_ACESSOS);
    printf("Hits (acessos mapeados): %d\n", hit_count);
    printf("Miss (substituições): %d\n", miss_count);
    printf("Taxa de Miss: %.2f%%\n", (float)miss_count / MAX_ACESSOS * 100);
}

// --- Função main ---
int main() {
    simular_mru();
    return 0;
}
