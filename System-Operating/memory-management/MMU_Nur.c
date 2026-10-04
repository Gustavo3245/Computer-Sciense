#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Configurações do Exercício ---
#define NUM_PAGINAS_VIRTUAIS 16
#define NUM_MOLDURAS_FISICAS 8
#define MAX_ACESSOS 25
#define INTERVALO_RESET 5 // Define o intervalo para zerar o bit R (Exemplo: a cada 5 acessos)

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
// Mapeamento dado pela figura (PV -> MP) e R=1, M=0 para todas as páginas mapeadas[cite: 4, 5].
// PV 0 (MP 3), PV 1 (MP 1), PV 2 (MP 0), PV 3 (MP 5), PV 4 (MP 4), PV 6 (MP 2), PV 9 (MP 6), PV 11 (MP 7)
void inicializar_tabela(EntradaTabelaPagina tabela[]) {
    // 1. Inicializa todas as páginas como ausentes
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        tabela[i] = (EntradaTabelaPagina){-1, false, false, false};
    }

    // 2. Mapeamento inicial (R=1, M=0)
    tabela[2] = (EntradaTabelaPagina){0, true, false, true};
    tabela[1] = (EntradaTabelaPagina){1, true, false, true};
    tabela[6] = (EntradaTabelaPagina){2, true, false, true};
    tabela[0] = (EntradaTabelaPagina){3, true, false, true};
    tabela[4] = (EntradaTabelaPagina){4, true, false, true};
    tabela[3] = (EntradaTabelaPagina){5, true, false, true};
    tabela[9] = (EntradaTabelaPagina){6, true, false, true};
    tabela[11] = (EntradaTabelaPagina){7, true, false, true};
}

// --- Função para zerar o Bit R (NUR - Periodicidade) ---
void zerar_bit_r(EntradaTabelaPagina tabela[]) {
    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        if (tabela[i].presente) {
            tabela[i].referenciada = false;
        }
    }
    printf("    -> **Bit R ZERADO** (NUR). Páginas agora na Classe 0 ou 1.\n");
}

// --- Função para selecionar a moldura a ser substituída (NUR) ---
int selecionar_moldura_nur(EntradaTabelaPagina tabela[]) {
    // Inicializa a melhor classe para substituição como a pior (Classe 3)
    int melhor_classe_encontrada = 4;
    int pv_a_substituir = -1;
    int moldura_a_substituir = -1;

    for (int i = 0; i < NUM_PAGINAS_VIRTUAIS; i++) {
        if (tabela[i].presente) {
            int r = tabela[i].referenciada;
            int m = tabela[i].modificada;
            int classe = (r * 2) + m; // Calcula a classe (00, 01, 10, 11)

            if (classe < melhor_classe_encontrada) {
                melhor_classe_encontrada = classe;
                pv_a_substituir = i;
                moldura_a_substituir = tabela[i].moldura_id;

                // Otimização: Se encontrarmos a Classe 0 (ideal), podemos parar
                if (melhor_classe_encontrada == 0) {
                    break;
                }
            }
        }
    }

    if (pv_a_substituir != -1) {
        printf("    -> PV %d escolhida. Classe (%d,%d). Moldura %d liberada.\n", 
               pv_a_substituir, 
               tabela[pv_a_substituir].referenciada, 
               tabela[pv_a_substituir].modificada,
               moldura_a_substituir);
               
        if (tabela[pv_a_substituir].modificada) {
            // Se M=1, simula a escrita da página de volta no disco
            printf("    -> Conteúdo da PV %d (Moldura %d) salvo no disco (M=1).\n", pv_a_substituir, moldura_a_substituir);
        }

        // Limpar a entrada da página antiga
        tabela[pv_a_substituir] = (EntradaTabelaPagina){-1, false, false, false};
    }

    return moldura_a_substituir; // Retorna o ID da Moldura liberada
}

// --- Função Principal de Simulação ---
void simular_nur() {
    EntradaTabelaPagina tabela[NUM_PAGINAS_VIRTUAIS];
    inicializar_tabela(tabela);

    const Acesso acessos[MAX_ACESSOS] = {
        {0, 'R'}, {1, 'R'}, {2, 'M'}, {6, 'R'}, {7, 'M'}, {1, 'M'}, {7, 'R'}, {6, 'R'},
        {2, 'R'}, {3, 'R'}, {0, 'M'}, {4, 'R'}, {0, 'R'}, {6, 'M'}, {1, 'R'}, {8, 'R'},
        {12, 'R'}, {8, 'M'}, {2, 'R'}, {15, 'R'}, {6, 'R'}, {0, 'M'}, {3, 'R'}, {5, 'R'},
        {0, 'R'}
    };

    int hit_count = 0;
    int miss_count = 0;

    printf("--- Simulação de Gerenciamento de Memória - Algoritmo NUR ---\n");
    printf("Molduras: %d | Paginas: %d | Reset R a cada %d acessos.\n\n", NUM_MOLDURAS_FISICAS, NUM_PAGINAS_VIRTUAIS, INTERVALO_RESET);

    for (int i = 0; i < MAX_ACESSOS; i++) {
        int pv = acessos[i].pagina_virtual;
        char tipo = acessos[i].tipo_acesso;

        // 0. RESET PERIÓDICO DO BIT R (Simulação do clock)
        if (i > 0 && (i % INTERVALO_RESET == 0)) {
             zerar_bit_r(tabela);
        }

        printf("Acesso %2d: (%c) PV %2d | ", i + 1, tipo, pv);

        // 1. Verificar Tabela de Páginas (Hit ou Miss)
        if (tabela[pv].presente) {
            // --- HIT ---
            hit_count++;
            printf("HIT. Moldura %d.\n", tabela[pv].moldura_id);

            // Atualizar bits R e M
            tabela[pv].referenciada = true;
            if (tipo == 'M') {
                tabela[pv].modificada = true;
            }

        } else {
            // --- MISS ---
            miss_count++;
            printf("MISS. Falta de Pagina.\n");
            
            // 2. Substituição de Página (NUR)
            int moldura_livre = selecionar_moldura_nur(tabela);

            // 3. Carregar Nova Página na Moldura
            tabela[pv].moldura_id = moldura_livre;
            tabela[pv].presente = true;
            tabela[pv].referenciada = true; // Acabou de ser referenciada (R=1)
            tabela[pv].modificada = (tipo == 'M'); // M=1 se for acesso de Modificação
            
            printf("    -> PV %d carregada na Moldura %d.\n", pv, moldura_livre);
        }
    }

    printf("\n--- Resultados Finais (NUR) ---\n");
    printf("Total de Acessos: %d\n", MAX_ACESSOS);
    printf("Hits (acessos mapeados): %d\n", hit_count);
    printf("Miss (substituições): %d\n", miss_count);
    printf("Taxa de Miss: %.2f%%\n", (float)miss_count / MAX_ACESSOS * 100);
}

// --- Função main ---
int main() {
    simular_nur();
    return 0;
}
