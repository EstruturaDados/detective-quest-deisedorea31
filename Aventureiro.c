#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------- Estrutura da Árvore -------- */

typedef struct No {
    char pista[50];
    struct No *esq;
    struct No *dir;
} No;

/* -------- Função para criar um novo nó -------- */

No* criarNo(char pista[]) {
    No* novo = (No*) malloc(sizeof(No));
    strcpy(novo->pista, pista);
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/* -------- Inserção na BST (ordem alfabética) -------- */

No* inserir(No* raiz, char pista[]) {
    if (raiz == NULL) {
        return criarNo(pista);
    }

    // Comparação de strings (ordem alfabética)
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esq = inserir(raiz->esq, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->dir = inserir(raiz->dir, pista);
    }
    // Se for igual, não insere duplicado

    return raiz;
}

/* -------- Busca de uma pista -------- */

int buscar(No* raiz, char pista[]) {
    if (raiz == NULL) {
        return 0;
    }

    if (strcmp(pista, raiz->pista) == 0) {
        return 1;
    }

    if (strcmp(pista, raiz->pista) < 0) {
        return buscar(raiz->esq, pista);
    }

    return buscar(raiz->dir, pista);
}

/* -------- Listagem em ordem alfabética -------- */

void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->dir);
    }
}

/* -------- Simulação de visita a salas -------- */

No* visitarSala(No* raiz, int sala) {
    switch (sala) {
        case 1:
            printf("\nVocê encontrou a pista: 'Chave Antiga'\n");
            raiz = inserir(raiz, "Chave Antiga");
            break;

        case 2:
            printf("\nVocê encontrou a pista: 'Mapa Rasgado'\n");
            raiz = inserir(raiz, "Mapa Rasgado");
            break;

        case 3:
            printf("\nVocê encontrou a pista: 'Bilhete Secreto'\n");
            raiz = inserir(raiz, "Bilhete Secreto");
            break;

        default:
            printf("\nSala vazia. Nenhuma pista encontrada.\n");
    }

    return raiz;
}

/* -------- Menu -------- */

void menu() {
    printf("\n===== SISTEMA DE PISTAS =====\n");
    printf("1 - Visitar sala\n");
    printf("2 - Buscar pista\n");
    printf("3 - Listar pistas (ordem alfabética)\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

/* -------- Programa Principal -------- */

int main() {
    No* raiz = NULL;
    int opcao, sala;
    char pistaBusca[50];

    do {
        menu();
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                printf("Digite o número da sala (1 a 3): ");
                scanf("%d", &sala);
                raiz = visitarSala(raiz, sala);
                break;

            case 2:
                printf("Digite o nome da pista para buscar: ");
                fgets(pistaBusca, 50, stdin);
                pistaBusca[strcspn(pistaBusca, "\n")] = '\0';

                if (buscar(raiz, pistaBusca)) {
                    printf("Pista encontrada!\n");
                } else {
                    printf("Pista não encontrada.\n");
                }
                break;

            case 3:
                printf("\nPistas encontradas:\n");
                emOrdem(raiz);
                break;

            case 0:
                printf("\nEncerrando jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}