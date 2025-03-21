#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double** alocarMatriz(int linhas, int colunas) {
    double** matriz = (double**)malloc(linhas * sizeof(double*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (double*)malloc(colunas * sizeof(double));
    }
    return matriz;
}

void liberarMatriz(double** matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void preencherMatrizAleatoria(double** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = (rand() % 100) / 10.0;
        }
    }
}

void imprimirMatriz(double** matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%.2lf\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void somarMatrizes(double** A, double** B, double** resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtrairMatrizes(double** A, double** B, double** resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[i][j] = A[i][j] - B[i][j];
        }
    }
}

void identidade(double** resultado, int ordem) {
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            resultado[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void transposta(double** A, double** resultado, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            resultado[j][i] = A[i][j];
        }
    }
}

void multiplicarMatrizes(double** A, double** B, double** resultado, int linhasA, int colunasA, int colunasB) {
    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            resultado[i][j] = 0;
            for (int k = 0; k < colunasA; k++) {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int opcao, linhas, colunas;
    double **A, **B, **resultado;
    int colunasB = 0;
    
    do {
        printf("\nMenu de Operações:\n");
        printf("1. Somar Matrizes\n2. Subtrair Matrizes\n3. Matriz Identidade\n4. Transposta\n5. Multiplicação\n6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 6) break;

        printf("Informe o número de linhas: ");
        scanf("%d", &linhas);
        printf("Informe o número de colunas: ");
        scanf("%d", &colunas);
        
        A = alocarMatriz(linhas, colunas);
        if (opcao != 3) {
            B = alocarMatriz(linhas, colunas);
            resultado = alocarMatriz(linhas, colunas);
        } else {
            resultado = alocarMatriz(linhas, linhas);
        }

        if (opcao != 3) {
            printf("Preenchendo matrizes com valores aleatórios...\n");
            preencherMatrizAleatoria(A, linhas, colunas);
            preencherMatrizAleatoria(B, linhas, colunas);
        }

        switch (opcao) {
            case 1:
                somarMatrizes(A, B, resultado, linhas, colunas);
                break;
            case 2:
                subtrairMatrizes(A, B, resultado, linhas, colunas);
                break;
            case 3:
                identidade(resultado, linhas);
                break;
            case 4:
                transposta(A, resultado, linhas, colunas);
                break;
            case 5:
                printf("Informe o número de colunas da segunda matriz: ");
                scanf("%d", &colunasB);
                B = alocarMatriz(colunas, colunasB);
                resultado = alocarMatriz(linhas, colunasB);
                preencherMatrizAleatoria(B, colunas, colunasB);
                multiplicarMatrizes(A, B, resultado, linhas, colunas, colunasB);
                break;
            default:
                printf("Opção inválida!\n");
        }

        printf("Matriz A:\n");
        imprimirMatriz(A, linhas, colunas);
        if (opcao != 3) {
            printf("Matriz B:\n");
            imprimirMatriz(B, (opcao == 5) ? colunas : linhas, (opcao == 5) ? colunasB : colunas);
        }
        printf("Resultado:\n");
        imprimirMatriz(resultado, (opcao == 3) ? linhas : linhas, (opcao == 5) ? colunasB : colunas);
        
        liberarMatriz(A, linhas);
        if (opcao != 3) liberarMatriz(B, linhas);
        liberarMatriz(resultado, (opcao == 3) ? linhas : linhas);
        
    } while (1);
    
    printf("Programa encerrado!\n");
    return 0;
}
