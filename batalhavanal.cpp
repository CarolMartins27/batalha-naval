#include <stdio.h>
#include <stdlib.h>  // Necessário para a função abs()

#define TAM 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // Tamanho da matriz das habilidades

void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = 0;
}

int posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha < 0 || linha >= TAM || coluna < 0 || coluna + TAM_NAVIO > TAM) {
        printf("Coordenadas do navio HORIZONTAL são inválidas.\n");
        return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0) {
            printf("Sobreposição detectada no navio HORIZONTAL.\n");
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;  // Marca a posição do navio
    }

    printf("Navio HORIZONTAL posicionado com sucesso!\n");
    return 1;
}

int posicionarNavioVertical(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (coluna < 0 || coluna >= TAM || linha < 0 || linha + TAM_NAVIO > TAM) {
        printf("Coordenadas do navio VERTICAL são inválidas.\n");
        return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0) {
            printf("Sobreposição detectada no navio VERTICAL.\n");
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;  // Marca a posição do navio
    }

    printf("Navio VERTICAL posicionado com sucesso!\n");
    return 1;
}

int posicionarNavioDiagonalPrincipal(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha < 0 || coluna < 0 || linha + TAM_NAVIO > TAM || coluna + TAM_NAVIO > TAM) {
        printf("Coordenadas do navio DIAGONAL PRINCIPAL são inválidas.\n");
        return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != 0) {
            printf("Sobreposição detectada no navio DIAGONAL PRINCIPAL.\n");
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3;  // Marca a posição do navio
    }

    printf("Navio DIAGONAL PRINCIPAL posicionado com sucesso!\n");
    return 1;
}

int posicionarNavioDiagonalSecundaria(int tabuleiro[TAM][TAM], int linha, int coluna) {
    if (linha < 0 || coluna >= TAM || linha + TAM_NAVIO > TAM || coluna - TAM_NAVIO + 1 < 0) {
        printf("Coordenadas do navio DIAGONAL SECUNDÁRIA são inválidas.\n");
        return 0;
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != 0) {
            printf("Sobreposição detectada no navio DIAGONAL SECUNDÁRIA.\n");
            return 0;
        }
    }

    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 3;  // Marca a posição do navio
    }

    printf("Navio DIAGONAL SECUNDÁRIA posicionado com sucesso!\n");
    return 1;
}

void aplicarHabilidadeCone(int tabuleiro[TAM][TAM], int origem_linha, int origem_coluna) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = -i; j <= i; j++) {
            int linha = origem_linha + i;
            int coluna = origem_coluna + j;
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && tabuleiro[linha][coluna] == 0)
                tabuleiro[linha][coluna] = 5;
        }
    }
}

void aplicarHabilidadeCruz(int tabuleiro[TAM][TAM], int origem_linha, int origem_coluna) {
    for (int i = -2; i <= 2; i++) {
        if (origem_linha + i >= 0 && origem_linha + i < TAM && tabuleiro[origem_linha + i][origem_coluna] == 0)
            tabuleiro[origem_linha + i][origem_coluna] = 5;
        if (origem_coluna + i >= 0 && origem_coluna + i < TAM && tabuleiro[origem_linha][origem_coluna + i] == 0)
            tabuleiro[origem_linha][origem_coluna + i] = 5;
    }
}

void aplicarHabilidadeOctaedro(int tabuleiro[TAM][TAM], int origem_linha, int origem_coluna) {
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            if (abs(i) + abs(j) <= 2) {  // Aqui é onde a função abs() é usada
                int linha = origem_linha + i;
                int coluna = origem_coluna + j;
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM && tabuleiro[linha][coluna] == 0)
                    tabuleiro[linha][coluna] = 5;
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n   ");
    for (int i = 0; i < TAM; i++)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0)
                printf("~ ");  // Água
            else if (tabuleiro[i][j] == 3)
                printf("N ");  // Navio
            else if (tabuleiro[i][j] == 5)
                printf("* ");  // Área afetada pela habilidade
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    int linha, coluna;

    // Navios
    do {
        printf("Digite a coordenada do navio HORIZONTAL (linha coluna): ");
        scanf("%d %d", &linha, &coluna);
    } while (!posicionarNavioHorizontal(tabuleiro, linha, coluna));

    do {
        printf("Digite a coordenada do navio VERTICAL (linha coluna): ");
        scanf("%d %d", &linha, &coluna);
    } while (!posicionarNavioVertical(tabuleiro, linha, coluna));

    do {
        printf("Digite a coordenada do navio DIAGONAL PRINCIPAL (linha coluna): ");
        scanf("%d %d", &linha, &coluna);
    } while (!posicionarNavioDiagonalPrincipal(tabuleiro, linha, coluna));

    do {
        printf("Digite a coordenada do navio DIAGONAL SECUNDÁRIA (linha coluna): ");
        scanf("%d %d", &linha, &coluna);
    } while (!posicionarNavioDiagonalSecundaria(tabuleiro, linha, coluna));

    // Aplicar habilidades
    aplicarHabilidadeCone(tabuleiro, 2, 2);
    aplicarHabilidadeCruz(tabuleiro, 5, 5);
    aplicarHabilidadeOctaedro(tabuleiro, 7, 7);

    // Mostrar resultado
    exibirTabuleiro(tabuleiro);

    return 0;
}

