#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato* prox;
} Contato;

Contato* tabelaHash[TABLE_SIZE];

int funcaoHash(const char* nome) {
    int hash = 0;
    while (*nome) {
        hash += *nome;
        nome++;
    }
    return hash % TABLE_SIZE;
}

void adicionarContato() {
    char nome[50], telefone[15];
    printf("Nome: ");
    scanf("%s", nome);
    printf("Telefone: ");
    scanf("%s", telefone);

    int indice = funcaoHash(nome);

    Contato* novo = (Contato*)malloc(sizeof(Contato));
    strcpy(novo->nome, nome);
    strcpy(novo->telefone, telefone);
    novo->prox = NULL;

    if (tabelaHash[indice] == NULL) {
        tabelaHash[indice] = novo;
    } else {
        Contato* atual = tabelaHash[indice];
        while (atual->prox) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato() {
    char nome[50];
    printf("Nome: ");
    scanf("%s", nome);

    int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];

    clock_t inicio = clock();
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            clock_t fim = clock();
            double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
            printf("Telefone de %s: %s (tempo de busca: %.2f ms)\n", atual->nome, atual->telefone, tempo);
            return;
        }
        atual = atual->prox;
    }

    printf("Contato nao encontrado.\n");
}

void removerContato() {
    char nome[50];
    printf("Nome: ");
    scanf("%s", nome);

    int indice = funcaoHash(nome);
    Contato* atual = tabelaHash[indice];
    Contato* anterior = NULL;

    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {

            if (anterior == NULL) {
                tabelaHash[indice] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Contato nao encontrado.\n");
}

void exibirContatos() {
    printf("Lista de contatos:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato* atual = tabelaHash[i];
        if (atual) {
            printf("Indice %d:\n", i);
            while (atual) {
                printf("  Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
                atual = atual->prox;
            }
        }
    }
}

int main() {
    int opcao;

    for (int i = 0; i < TABLE_SIZE; i++) {
        tabelaHash[i] = NULL;
    }

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                buscarContato();
                break;
            case 3:
                removerContato();
                break;
            case 4:
                exibirContatos();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < TABLE_SIZE; i++) {
        Contato* atual = tabelaHash[i];
        while (atual) {
            Contato* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    return 0;
}
