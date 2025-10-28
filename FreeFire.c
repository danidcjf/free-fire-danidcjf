#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//definicoes de constantes
#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

//itens mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int numItens = 0;

//limpar buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void menu() {
    printf("\n=== Menu de Itens da Mochila ===\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Sair\n");
    printf("Escolha uma opcao: ");
}

//adicionar item
void newItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n[ERRO] Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    
    printf("\nDigite o nome do item: ");
    limparBuffer();
    fgets(novoItem.nome, TAM_NOME, stdin);//uso de fgets eviitar problemas do scanf
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';
    
    printf("Digite o tipo do item: ");
    fgets(novoItem.tipo, TAM_TIPO, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';
    
    printf("Digite a quantidade do item: ");
    scanf("%d", &novoItem.quantidade);

    mochila[numItens++] = novoItem;
    printf("\n[SUCESSO] Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

//remover item
void removeItem() {
    if (numItens == 0) {
        printf("\n[AVISO] Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    //lista itens atuais antes de remover
    char nomeItem[TAM_NOME];
    printf("\nDigite o nome do item a ser removido: ");
    limparBuffer();
    fgets(nomeItem, TAM_NOME, stdin);
    nomeItem[strcspn(nomeItem, "\n")] = '\0';

    //procura e remove item
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeItem) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("\n[SUCESSO] Item '%s' removido com sucesso!\n", nomeItem);
            return;
        }
    }
    printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeItem);
}

//listar itens
void listItems() {
    if (numItens == 0) {
        printf("\n[AVISO] Mochila vazia! Nao ha itens para listar.\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    printf("%-25s %-20s %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("----------------------------------------------------------------\n");
    //exibe itens
    for (int i = 0; i < numItens; i++) {
        printf("%-25s %-20s %d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }
    printf("================================================================\n");
    printf("Total de itens: %d/%d\n", numItens, MAX_ITENS);
}

int main() {
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                newItem();
                break;
            case 2:
                removeItem();
                break;
            case 3:
                listItems();
                break;
            case 4:
                printf("\nSaindo... Boa sorte na ilha!\n\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
