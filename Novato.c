#include <stdio.h>
#include <stdlib.h>

/* =====================================================
   ESTRUTURA DO NÓ DA ÁRVORE (SALA DA MANSÃO)
===================================================== */
typedef struct Sala {
    char nome[50];            // Nome da sala
    struct Sala *esq;         // Ponteiro para a sala à esquerda
    struct Sala *dir;         // Ponteiro para a sala à direita
} Sala;

/* =====================================================
   FUNÇÃO: CRIAR UMA SALA (NÓ DA ÁRVORE)
   Aloca memória e inicializa os campos
===================================================== */
Sala* criarSala(char nome[]) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));

    // Copia o nome para a sala
    snprintf(nova->nome, sizeof(nova->nome), "%s", nome);

    // Inicializa os filhos como NULL
    nova->esq = NULL;
    nova->dir = NULL;

    return nova;
}

/* =====================================================
   FUNÇÃO: EXPLORAR A MANSÃO
   Permite navegação interativa pela árvore
===================================================== */
void explorarSalas(Sala* atual) {
    char opcao;

    while (atual != NULL) {

        // Exibe a sala atual
        printf("\nVocê está em: %s\n", atual->nome);

        // Verifica se é uma sala folha
        if (atual->esq == NULL && atual->dir == NULL) {
            printf("Fim do caminho! Esta é uma sala final.\n");
            return;
        }

        // Exibe as opções disponíveis
        printf("Escolha um caminho:\n");
        if (atual->esq != NULL)
            printf("e - Ir para a esquerda\n");
        if (atual->dir != NULL)
            printf("d - Ir para a direita\n");
        printf("s - Sair da exploração\n");
        printf("Opção: ");

        scanf(" %c", &opcao);

        // Processa a escolha do jogador
        if (opcao == 'e' && atual->esq != NULL) {
            atual = atual->esq;
        }
        else if (opcao == 'd' && atual->dir != NULL) {
            atual = atual->dir;
        }
        else if (opcao == 's') {
            printf("\nExploração encerrada.\n");
            return;
        }
        else {
            printf("\nOpção inválida! Tente novamente.\n");
        }
    }
}

/* =====================================================
   FUNÇÃO PRINCIPAL
===================================================== */
int main() {

    /* -------- CRIAÇÃO DA ÁRVORE -------- */

    // Raiz da árvore
    Sala* hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esq = criarSala("Sala de Estar");
    hall->dir = criarSala("Biblioteca");

    // Nível 2
    hall->esq->esq = criarSala("Cozinha");
    hall->esq->dir = criarSala("Jardim");

    hall->dir->esq = criarSala("Escritório");
    hall->dir->dir = criarSala("Quarto");

    /* -------- INÍCIO DA EXPLORAÇÃO -------- */

    printf("🏰 Bem-vindo à Mansão Misteriosa!\n");
    explorarSalas(hall);

    return 0;
}