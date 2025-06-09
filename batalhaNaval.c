#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Necessário para a função abs() usada no octaedro

// --- Constantes do Jogo ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// --- Constantes de Visualização ---
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5 // Novo valor para a área de efeito

// --- Constantes das Habilidades ---
#define TAMANHO_HABILIDADE 7 // Tamanho das matrizes de habilidade (usei 7x7 para um efeito maior)
#define AFETADO 1
#define NAO_AFETADO 0

// --- Protótipos das Funções ---
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void gerarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void gerarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void gerarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna);

int main() {
    // 1. Definir o Tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    printf("--- Batalha Naval Nível Mestre: Habilidades Especiais ---\n\n");

    // Inicializa o tabuleiro com água
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
    printf("Tabuleiro 10x10 inicializado.\n");

    // Posiciona um navio para referência
    printf("Posicionando navio de referência...\n");
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[1][1 + i] = NAVIO; // Navio horizontal em (1,1)
    }

    // 2. Criar Matrizes de Habilidade
    int habilidade_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidade_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    printf("Gerando matrizes de habilidade...\n");
    gerarMatrizCone(habilidade_cone);
    gerarMatrizCruz(habilidade_cruz);
    gerarMatrizOctaedro(habilidade_octaedro);
    printf("Matrizes de habilidade geradas com sucesso.\n\n");

    // 3. Integrar Habilidades ao Tabuleiro
    // Define o ponto de origem para cada habilidade no tabuleiro
    int origem_cone_l = 2, origem_cone_c = 6;
    int origem_cruz_l = 6, origem_cruz_c = 2;
    int origem_octaedro_l = 6, origem_octaedro_c = 7;

    // Aplica as habilidades no tabuleiro
    printf("Aplicando habilidade CONE no ponto (%d, %d)\n", origem_cone_l, origem_cone_c);
    aplicarHabilidade(tabuleiro, habilidade_cone, origem_cone_l, origem_cone_c);

    printf("Aplicando habilidade CRUZ no ponto (%d, %d)\n", origem_cruz_l, origem_cruz_c);
    aplicarHabilidade(tabuleiro, habilidade_cruz, origem_cruz_l, origem_cruz_c);
    
    printf("Aplicando habilidade OCTAEDRO no ponto (%d, %d)\n", origem_octaedro_l, origem_octaedro_c);
    aplicarHabilidade(tabuleiro, habilidade_octaedro, origem_octaedro_l, origem_octaedro_c);

    // 4. Exibir o Tabuleiro Final
    exibirTabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Gera uma matriz 7x7 representando uma área de efeito em CONE.
 * @param matriz A matriz 7x7 a ser preenchida.
 */
void gerarMatrizCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Cria um triângulo/cone apontando para baixo a partir do topo
            if (i >= centro && j >= centro - (i - centro) && j <= centro + (i - centro)) {
                matriz[i][j] = AFETADO;
            } else {
                matriz[i][j] = NAO_AFETADO;
            }
        }
    }
}


/**
 * @brief Gera uma matriz 7x7 representando uma área de efeito em CRUZ.
 * @param matriz A matriz 7x7 a ser preenchida.
 */
void gerarMatrizCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Afeta a linha central OU a coluna central
            if (i == centro || j == centro) {
                matriz[i][j] = AFETADO;
            } else {
                matriz[i][j] = NAO_AFETADO;
            }
        }
    }
}

/**
 * @brief Gera uma matriz 7x7 representando a área de efeito de um OCTAEDRO (losango).
 * @param matriz A matriz 7x7 a ser preenchida.
 */
void gerarMatrizOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILidade; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Usa a "distância de Manhattan" do centro para formar um losango
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = AFETADO;
            } else {
                matriz[i][j] = NAO_AFETADO;
            }
        }
    }
}

/**
 * @brief Sobrepõe uma matriz de habilidade no tabuleiro principal.
 * @param tabuleiro O tabuleiro principal do jogo.
 * @param habilidade A matriz de habilidade (cone, cruz, etc.).
 * @param origem_linha A linha do tabuleiro onde o centro da habilidade será aplicado.
 * @param origem_coluna A coluna do tabuleiro onde o centro da habilidade será aplicado.
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origem_linha, int origem_coluna) {
    int centro_habilidade = TAMANHO_HABILIDADE / 2;

    // Itera sobre a matriz de habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Verifica se a posição atual na matriz de habilidade é uma área de efeito
            if (habilidade[i][j] == AFETADO) {
                // Calcula a posição correspondente no tabuleiro principal
                int linha_no_tabuleiro = origem_linha - centro_habilidade + i;
                int coluna_no_tabuleiro = origem_coluna - centro_habilidade + j;

                // CONDIÇÃO DE SEGURANÇA: Verifica se a posição calculada está DENTRO dos limites do tabuleiro
                if (linha_no_tabuleiro >= 0 && linha_no_tabuleiro < TAMANHO_TABULEIRO &&
                    coluna_no_tabuleiro >= 0 && coluna_no_tabuleiro < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro como afetada pela habilidade
                    tabuleiro[linha_no_tabuleiro][coluna_no_tabuleiro] = AREA_AFETADA;
                }
            }
        }
    }
}

/**
 * @brief Exibe o tabuleiro do jogo no console com caracteres especiais.
 * @param tabuleiro A matriz 2D que representa o tabuleiro.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO FINAL COM HABILIDADES ===\n");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo = '?';
            switch (tabuleiro[i][j]) {
                case AGUA:         simbolo = '~'; break; // Água
                case NAVIO:        simbolo = 'N'; break; // Navio
                case AREA_AFETADA: simbolo = '*'; break; // Área de Efeito
            }
            printf("%c ", simbolo);
        }
        printf("\n");
    }
}
