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
    int linhasB, colunasB;
    
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
        preencherMatrizAleatoria(A, linhas, colunas);

        if (opcao == 5) {
            printf("Informe o número de linhas da segunda matriz: ");
            scanf("%d", &linhasB);
            printf("Informe o número de colunas da segunda matriz: ");
            scanf("%d", &colunasB);
            
            if (colunas != linhasB) {
                printf("Não é possível multiplicar matrizes com essas dimensões!\n");
                liberarMatriz(A, linhas);
                continue;
            }
            
            B = alocarMatriz(linhasB, colunasB);
            resultado = alocarMatriz(linhas, colunasB);
            preencherMatrizAleatoria(B, linhasB, colunasB);
            multiplicarMatrizes(A, B, resultado, linhas, colunas, colunasB);
        } else {
            B = alocarMatriz(linhas, colunas);
            resultado = alocarMatriz(linhas, colunas);
            preencherMatrizAleatoria(B, linhas, colunas);
        }

        printf("Matriz A:\n");
        imprimirMatriz(A, linhas, colunas);
        if (opcao != 3) {
            printf("Matriz B:\n");
            imprimirMatriz(B, (opcao == 5) ? linhasB : linhas, (opcao == 5) ? colunasB : colunas);
        }
        printf("Resultado:\n");
        imprimirMatriz(resultado, (opcao == 3) ? linhas : linhas, (opcao == 5) ? colunasB : colunas);
        
        liberarMatriz(A, linhas);
        liberarMatriz(B, (opcao == 5) ? linhasB : linhas);
        liberarMatriz(resultado, (opcao == 3) ? linhas : linhas);
        
    } while (1);
    
    printf("Programa encerrado!\n");
    return 0;
}
