#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// --- Configurações do Exercício ---
#define NUM_PAGINAS_VIRTUAIS 16
#define NUM_MOLDURAS_FISICAS 8
#define MAX_ACESSOS 25

// Variável global que rastreia a posição do "ponteiro do relógio"
int ponteiro_clock = 0; 
// Array para rastrear qual página virtual está em qual moldura (chave para o algoritmo)
int moldura_para_pv[NUM_MOLDURAS_FISICAS]; 

// --- Estrutura para a Tabela de Páginas ---
typedef struct {
    int moldura_id;     // Número da Moldura de Página (MP). -1 se ausente.
    bool presente;      // Bit Presente/Ausente.
    bool modificada;    // Bit Modificada (M).
    bool referenciada;  // Bit Referenciada (R).
} EntradaTabelaPagina;

// --- Estrutura para a Sequência de Acessos ---
typedef struct {
    int pagina_virtual;
    char tipo_acesso; // 'R' para Referência, 'M' para Modificação
} Acesso;

// --- Estado Inicial da Simulação ---
// Mapeamento PV -> MP (da figura) e R=1, M=0 para todas as páginas mapeadas
void inicializar_tabela(EntradaTabelaPagina tabela[]) {
    // Inicializa todas as páginas como ausentes
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        tabela[i] = (EntradaTabelaPagina){-1, false, false, false};
    }
    // Inicializa o array de mapeamento de molduras (Moldura -> PV)
    for (int i = 0; i < NUM_MOLDURAS_FISICAS; i++) {
        moldura_para_pv[i] = -1;
    }
    
    // Mapeamento inicial da figura (R=1, M=0)
    // O ponteiro do relógio (ponteiro_clock) deve iniciar na moldura da página mais antiga
    // Assumindo a ordem de entrada: 3(MP 5), 1(MP 1), 0(MP 3), 4(MP 4), 9(MP 6), 2(MP 0), 11(MP 7), 6(MP 2)
    
    tabela[3] = (EntradaTabelaPagina){5, true, false, true}; moldura_para_pv[5] = 3;
    tabela[1] = (EntradaTabelaPagina){1, true, false, true}; moldura_para_pv[1] = 1;
    tabela[0] = (EntradaTabelaPagina){3, true, false, true}; moldura_para_pv[3] = 0;
    tabela[4] = (EntradaTabelaPagina){4, true, false, true}; moldura_para_pv[4] = 4;
    tabela[9] = (EntradaTabelaPagina){6, true, false, true}; moldura_para_pv[6] = 9;
    tabela[2] = (EntradaTabelaPagina){0, true, false, true}; moldura_para_pv[0] = 2;
    tabela[11] = (EntradaTabelaPagina){7, true, false, true}; moldura_para_pv[7] = 11;
    tabela[6] = (EntradaTabelaPagina){2, true, false, true}; moldura_para_pv[2] = 6;
    
    // O ponteiro_clock inicia na Moldura 5 (PV 3), que é a mais antiga na ordem FIFO.
    ponteiro_clock = 5; 
}

// --- Função para selecionar a moldura a ser substituída (Relógio - Clock) ---
int selecionar_moldura_clock(EntradaTabelaPagina tabela[]) {
    int pv_a_substituir = -1;
    int moldura_liberada = -1;

    // Loop infinito até que uma página seja encontrada para substituição
    while (true) {
        // Encontra a PV que está na moldura apontada pelo ponteiro
        int pv_atual = moldura_para_pv[ponteiro_clock];

        // 1. Verificar o bit R
        if (tabela[pv_atual].referenciada == true) {
            // R = 1: Dá a segunda chance (zera R e avança o ponteiro)
            tabela[pv_atual].referenciada = false;
            printf("    -> Moldura %d (PV %d): R=1. Zerando R e avançando ponteiro.\n", 
                   ponteiro_clock, pv_atual);
        } else {
            // R = 0: Substituir esta página
            pv_a_substituir = pv_atual;
            moldura_liberada = ponteiro_clock;
            
            // 2. Simular escrita no disco se M=1
            if (tabela[pv_a_substituir].modificada) {
                printf("    -> Escrita no disco (M=1) da PV %d (Moldura %d).\n", 
                       pv_a_substituir, moldura_liberada);
            }
            
            // Limpar a entrada da página antiga
            tabela[pv_a_substituir] = (EntradaTabelaPagina){-1, false, false, false};
            moldura_para_pv[moldura_liberada] = -1;

            // 3. O ponteiro avança *antes* de retornar a moldura liberada
            ponteiro_clock = (ponteiro_clock + 1) % NUM_MOLDURAS_FISICAS;

            printf("    -> PV %d substituída. Moldura %d liberada. Novo Ponteiro: %d.\n", pv_a_substituir, moldura_liberada, ponteiro_clock);
            return moldura_liberada;
        }

        // Avança o ponteiro do relógio para a próxima moldura (Circularidade)
        ponteiro_clock = (ponteiro_clock + 1) % NUM_MOLDURAS_FISICAS;
    }
}

// --- Função Principal de Simulação ---
void simular_clock() {
    EntradaTabelaPagina tabela[NUM_PAGINAS_VIRTUAIS];
    inicializar_tabela(tabela);

    // Sequência de acesso do exercício
    const Acesso acessos[MAX_ACESSOS] = {
        {0, 'R'}, {1, 'R'}, {2, 'M'}, {6, 'R'}, {7, 'M'}, {1, 'M'}, {7, 'R'}, {6, 'R'},
        {2, 'R'}, {3, 'R'}, {0, 'M'}, {4, 'R'}, {0, 'R'}, {6, 'M'}, {1, 'R'}, {8, 'R'},
        {12, 'R'}, {8, 'M'}, {2, 'R'}, {15, 'R'}, {6, 'R'}, {0, 'M'}, {3, 'R'}, {5, 'R'},
        {0, 'R'}
    };

    int hit_count = 0;
    int miss_count = 0;

    printf("--- Simulação de Gerenciamento de Memória - Algoritmo Relógio (Clock) ---\n");
    printf("Molduras Fisicas: %d | Paginas Virtuais: %d\n", NUM_MOLDURAS_FISICAS, NUM_PAGINAS_VIRTUAIS);
    printf("Ponteiro Inicial (Moldura Mais Antiga): %d (PV %d)\n\n", ponteiro_clock, moldura_para_pv[ponteiro_clock]);

    for (int i = 0; i < MAX_ACESSOS; i++) {
        int pv = acessos[i].pagina_virtual;
        char tipo = acessos[i].tipo_acesso;

        printf("Acesso %2d: (%c) PV %2d | ", i + 1, tipo, pv);

        // 1. Verificar Tabela de Páginas (Hit ou Miss)
        if (tabela[pv].presente) {
            // --- HIT ---
            hit_count++;
            printf("HIT. Moldura %d.\n", tabela[pv].moldura_id);

            // Atualizar bits de controle (R sempre, M se necessário)
            tabela[pv].referenciada = true;
            if (tipo == 'M') {
                tabela[pv].modificada = true;
            }

        } else {
            // --- MISS ---
            miss_count++;
            printf("MISS. Falta de Pagina.\n");
            
            // 2. Substituição de Página (Clock)
            int moldura_livre = selecionar_moldura_clock(tabela);

            // 3. Carregar Nova Página na Moldura
            tabela[pv].moldura_id = moldura_livre;
            tabela[pv].presente = true;
            tabela[pv].referenciada = true; // R=1
            tabela[pv].modificada = (tipo == 'M');
            
            // Atualizar o mapeamento da moldura
            moldura_para_pv[moldura_livre] = pv;

            printf("    -> PV %d carregada na Moldura %d.\n", pv, moldura_livre);
        }
    }

    printf("\n--- Resultados Finais (Relógio - Clock) ---\n");
    printf("Total de Acessos: %d\n", MAX_ACESSOS);
    printf("Hits (acessos mapeados): %d\n", hit_count);
    printf("Miss (substituições): %d\n", miss_count);
    printf("Taxa de Miss: %.2f%%\n", (float)miss_count / MAX_ACESSOS * 100);
}

// --- Função main ---
int main() {
    simular_clock();
    return 0;
}
