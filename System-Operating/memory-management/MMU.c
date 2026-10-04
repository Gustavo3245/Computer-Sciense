#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Configurações do Exercício ---
#define NUM_PAGINAS_VIRTUAIS 16 // 64KB / 4KB
#define NUM_MOLDURAS_FISICAS 8  // 32KB / 4KB
#define MAX_ACESSOS 25

// --- Estrutura para a Tabela de Páginas ---
typedef struct {
    int moldura_id;          // Número da Moldura de Página (MP). -1 se ausente.
    bool presente;           // Bit Presente/Ausente.
    bool modificada;         // Bit Modificada (M).
    bool referenciada;       // Bit Referenciada (R).
    int tempo_entrada;       // Usado para FIFO: marca a ordem de entrada na MP.
} EntradaTabelaPagina;

// --- Estrutura para a Sequência de Acessos ---
typedef struct {
    int pagina_virtual;
    char tipo_acesso; // 'R' para Referência, 'M' para Modificação
} Acesso;

// --- Estado Inicial da Simulação (Baseado na figura e na ordem 3, 1, 0, 5, 4, 9, 2, 11) ---
// Páginas de 0 (mais abaixo) a 15 (mais acima)
// Molduras de 0 (mais abaixo) a 7 (mais acima)
void inicializar_tabela(EntradaTabelaPagina tabela[]) {
    // 1. Inicializa todas as páginas como ausentes
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        tabela[i].moldura_id = -1;
        tabela[i].presente = false;
        tabela[i].modificada = false;
        tabela[i].referenciada = false;
        tabela[i].tempo_entrada = -1; // Não na memória
    }

    // 2. Mapeamento inicial (Páginas Virtuais -> Molduras Físicas)
    // Sequência de acesso inicial: 3, 1, 0, 5, 4, 9, 2, 11 (usada para determinar a ordem de entrada)
    // Mapeamento dado pela figura (PV -> MP): 2->0, 1->1, 6->2, 0->3, 4->4, 3->5, 9->6, 11->7
    
    // O tempo_entrada vai de 1 (mais antigo) a 8 (mais recente)
    // O algoritmo FIFO usará este valor para decidir quem sai.
    
    // PV 3 -> MP 5 (Ordem 1)
    tabela[3] = (EntradaTabelaPagina){5, true, false, true, 1};
    // PV 1 -> MP 1 (Ordem 2)
    tabela[1] = (EntradaTabelaPagina){1, true, false, true, 2};
    // PV 0 -> MP 3 (Ordem 3)
    tabela[0] = (EntradaTabelaPagina){3, true, false, true, 3};
    // PV 5 -> MP -1 (Ordem 4, mas 5 não está mapeada segundo a figura, a PV 5 está em 36K-40K e vai para MP 6 na ordem inicial. O mapeamento da figura é diferente da ordem inicial.
    // Vamos seguir o mapeamento visual da figura para o estado INICIAL e usar a ordem inicial (3, 1, 0, 5, 4, 9, 2, 11) para determinar o tempo_entrada (FIFO).
    
    // Reajustando o mapeamento inicial com a ordem de entrada correta (mais antigo primeiro):
    // Ordem de acesso: 3, 1, 0, 5, 4, 9, 2, 11
    
    // PV 3 -> MP 5 (Tempo 1)
    tabela[3] = (EntradaTabelaPagina){5, true, false, true, 1};
    // PV 1 -> MP 1 (Tempo 2)
    tabela[1] = (EntradaTabelaPagina){1, true, false, true, 2};
    // PV 0 -> MP 3 (Tempo 3)
    tabela[0] = (EntradaTabelaPagina){3, true, false, true, 3};
    // PV 5 -> MP 6 (Tempo 4) *Assumindo que a PV 5, 40K-44K, foi mapeada para MP 6 em 24K-28K, como a ordem de acesso implica preenchimento.*
    // ATENÇÃO: A figura mapeia: 2->0, 1->1, 6->2, 0->3, 4->4, 3->5, 9->6, 11->7.
    // E a ordem de acesso é: 3, 1, 0, 5, 4, 9, 2, 11.
    // Vamos usar a MOLDURA OCUPADA na figura, mas ajustar o tempo de entrada (FIFO) de acordo com a ordem.

    // Moldura 0: PV 2
    tabela[2] = (EntradaTabelaPagina){0, true, false, true, 7}; // PV 2 acessada em 7º lugar.
    // Moldura 1: PV 1
    tabela[1] = (EntradaTabelaPagina){1, true, false, true, 2}; // PV 1 acessada em 2º lugar.
    // Moldura 2: PV 6
    tabela[6] = (EntradaTabelaPagina){2, true, false, true, 0}; // PV 6 não está na ordem 3,1,0,5,4,9,2,11, assumiremos tempo 0 (mais antigo).
    // Moldura 3: PV 0
    tabela[0] = (EntradaTabelaPagina){3, true, false, true, 3}; // PV 0 acessada em 3º lugar.
    // Moldura 4: PV 4
    tabela[4] = (EntradaTabelaPagina){4, true, false, true, 5}; // PV 4 acessada em 5º lugar.
    // Moldura 5: PV 3
    tabela[3] = (EntradaTabelaPagina){5, true, false, true, 1}; // PV 3 acessada em 1º lugar.
    // Moldura 6: PV 9 (36K-40K, segundo o mapeamento)
    tabela[9] = (EntradaTabelaPagina){6, true, false, true, 6}; // PV 9 acessada em 6º lugar.
    // Moldura 7: PV 11 (44K-48K, segundo o mapeamento)
    tabela[11] = (EntradaTabelaPagina){7, true, false, true, 8}; // PV 11 acessada em 8º lugar.
    
    // A PV 5 é acessada em 4º lugar, mas não está mapeada na figura, ignoramos a entrada no FIFO inicial para páginas não mapeadas.
    // A PV 6 está mapeada na figura mas não está na ordem de acesso inicial.

    // A regra será: A página com o menor 'tempo_entrada' é a primeira a sair.
}


// --- Função para selecionar a moldura a ser substituída (FIFO) ---
int selecionar_moldura_fifo(EntradaTabelaPagina tabela[]) {
    int menor_tempo = -1;
    int moldura_a_substituir = -1;
    int pv_a_substituir = -1;

    // Encontrar a página na memória com o menor 'tempo_entrada'
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        if (tabela[i].presente) {
            // Se for o primeiro presente encontrado OU se o tempo atual for menor
            if (pv_a_substituir == -1 || tabela[i].tempo_entrada < menor_tempo) {
                menor_tempo = tabela[i].tempo_entrada;
                pv_a_substituir = i;
                moldura_a_substituir = tabela[i].moldura_id;
            }
        }
    }

    if (pv_a_substituir != -1) {
        // "Limpar" a página antiga: resetar seus bits e marcar como ausente
        if (tabela[pv_a_substituir].modificada) {
            // Simular a escrita no disco (se modificada)
        }
        tabela[pv_a_substituir].moldura_id = -1;
        tabela[pv_a_substituir].presente = false;
        tabela[pv_a_substituir].modificada = false;
        tabela[pv_a_substituir].referenciada = false;
        tabela[pv_a_substituir].tempo_entrada = -1;
    }

    return moldura_a_substituir; // Retorna o ID da Moldura liberada
}


// --- Função Principal de Simulação ---
void simular_fifo() {
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
    int tempo_global = 8; // Começa após o tempo de entrada inicial (1 a 8)

    printf("--- Simulação de Gerenciamento de Memória - Algoritmo FIFO ---\n");
    printf("Molduras Fisicas: %d | Paginas Virtuais: %d\n\n", NUM_MOLDURAS_FISICAS, NUM_PAGINAS_VIRTUAIS);

    for (int i = 0; i < MAX_ACESSOS; i++) {
        int pv = acessos[i].pagina_virtual;
        char tipo = acessos[i].tipo_acesso;

        printf("Acesso %2d: (%c) Pagina Virtual %2d | ", i + 1, tipo, pv);

        // 1. Verificar Tabela de Páginas (Hit ou Miss)
        if (tabela[pv].presente) {
            // --- HIT ---
            hit_count++;
            printf("HIT. Moldura %d\n", tabela[pv].moldura_id);

            // Atualizar bits de controle (R sempre, M se necessário)
            tabela[pv].referenciada = true;
            if (tipo == 'M') {
                tabela[pv].modificada = true;
            }

        } else {
            // --- MISS ---
            miss_count++;
            printf("MISS. Falta de Pagina.\n");
            
            // 2. Substituição de Página (FIFO)
            int moldura_livre = selecionar_moldura_fifo(tabela);

            // 3. Carregar Nova Página na Moldura
            tabela[pv].moldura_id = moldura_livre;
            tabela[pv].presente = true;
            tabela[pv].referenciada = true; // Acabou de ser referenciada
            tabela[pv].modificada = (tipo == 'M');
            
            // 4. Atualizar o tempo de entrada (FIFO)
            tempo_global++;
            tabela[pv].tempo_entrada = tempo_global;

            printf("    -> PV %d carregada na Moldura %d. (FIFO)\n\n", pv, moldura_livre);
        }
    }

    printf("\n--- Resultados Finais (FIFO) ---\n");
    printf("Total de Acessos: %d\n", MAX_ACESSOS);
    printf("Hits (acessos mapeados): %d\n", hit_count);
    printf("Miss (substituições): %d\n", miss_count); 
    printf("Taxa de Miss: %.2f%%\n", (float)miss_count / MAX_ACESSOS * 100);
}

// --- Função main ---
int main() {
    simular_fifo();
    return 0;
}
