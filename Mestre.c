#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =====================================================
   CONSTANTES
===================================================== */

#define TAM_HASH 10      // Tamanho da tabela hash
#define MAX_NOME 50

/* =====================================================
   STRUCT DO NÓ DA TABELA HASH
   Cada nó representa uma associação:
   pista -> suspeito
===================================================== */
typedef struct Nodo {
    char pista[MAX_NOME];
    char suspeito[MAX_NOME];
    struct Nodo *prox;
} Nodo;

/* =====================================================
   TABELA HASH (ARRAY DE LISTAS)
===================================================== */
Nodo* tabelaHash[TAM_HASH];

/* =====================================================
   FUNÇÃO HASH SIMPLES
   Baseada na soma ASCII dos caracteres da pista
===================================================== */
int funcaoHash(char *pista) {
    int soma = 0;

    for (int i = 0; pista[i] != '\0'; i++) {
        soma += pista[i];
    }

    return soma % TAM_HASH;
}

/* =====================================================
   INSERIR NA TABELA HASH
   Relaciona pista -> suspeito
===================================================== */
void inserirNaHash(char *pista, char *suspeito) {
    int indice = funcaoHash(pista);

    // Cria novo nó
    Nodo* novo = (Nodo*) malloc(sizeof(Nodo));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = NULL;

    // Insere no início da lista (encadeamento)
    novo->prox = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

/* =====================================================
   EXIBIR TODAS AS ASSOCIAÇÕES PISTA -> SUSPEITO
===================================================== */
void exibirAssociacoes() {
    printf("\n--- Associações Pista -> Suspeito ---\n");

    for (int i = 0; i < TAM_HASH; i++) {
        Nodo* atual = tabelaHash[i];

        if (atual != NULL) {
            printf("\nÍndice %d:\n", i);
            while (atual != NULL) {
                printf("  Pista: %-20s | Suspeito: %s\n",
                       atual->pista, atual->suspeito);
                atual = atual->prox;
            }
        }
    }
}

/* =====================================================
   CONTAR QUANTAS VEZES CADA SUSPEITO FOI CITADO
   E EXIBIR O MAIS CITADO
===================================================== */
void suspeitoMaisCitado() {
    char suspeitos[50][MAX_NOME];
    int contagem[50];
    int total = 0;

    // Inicializa contadores
    for (int i = 0; i < 50; i++)
        contagem[i] = 0;

    // Percorre a tabela hash
    for (int i = 0; i < TAM_HASH; i++) {
        Nodo* atual = tabelaHash[i];

        while (atual != NULL) {
            int encontrado = -1;

            // Verifica se o suspeito já foi registrado
            for (int j = 0; j < total; j++) {
                if (strcmp(suspeitos[j], atual->suspeito) == 0) {
                    encontrado = j;
                    break;
                }
            }

            // Se não existir, adiciona
            if (encontrado == -1) {
                strcpy(suspeitos[total], atual->suspeito);
                contagem[total] = 1;
                total++;
            }
            // Se já existir, incrementa
            else {
                contagem[encontrado]++;
            }

            atual = atual->prox;
        }
    }

    // Determina o suspeito mais citado
    int max = 0;
    char culpado[MAX_NOME] = "";

    for (int i = 0; i < total; i++) {
        if (contagem[i] > max) {
            max = contagem[i];
            strcpy(culpado, suspeitos[i]);
        }
    }

    // Exibe o resultado final
    if (max > 0) {
        printf("\n🏆 Suspeito mais citado:\n");
        printf("Nome: %s\n", culpado);
        printf("Quantidade de pistas: %d\n", max);
    } else {
        printf("\nNenhum suspeito encontrado.\n");
    }
}

/* =====================================================
   FUNÇÃO PRINCIPAL
===================================================== */
int main() {

    // Inicializa a tabela hash com NULL
    for (int i = 0; i < TAM_HASH; i++)
        tabelaHash[i] = NULL;

    /* -------- INSERÇÃO DE PISTAS E SUSPEITOS -------- */
    inserirNaHash("Luvas ensanguentadas", "Sr. Black");
    inserirNaHash("Pegadas no jardim", "Sra. White");
    inserirNaHash("Carta rasgada", "Sr. Black");
    inserirNaHash("Relógio quebrado", "Sr. Green");
    inserirNaHash("Chave dourada", "Sr. Black");
    inserirNaHash("Janela aberta", "Sra. White");

    /* -------- EXIBIÇÃO DAS ASSOCIAÇÕES -------- */
    exibirAssociacoes();

    /* -------- ANÁLISE FINAL -------- */
    suspeitoMaisCitado();

    return 0;
}