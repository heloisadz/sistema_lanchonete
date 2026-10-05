#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void iniciar_fila(Fila *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
}

int fila_vazia(Fila *fila){
    return fila->inicio == NULL;
}

void adicionar_fila(Fila *fila, Pedido pedido){
    No *novo = malloc(sizeof(No));

    if (novo == NULL){
        printf("Erro: nao foi possivel alocar memoria.\n");
        return;
    }

    novo->pedido = pedido;
    novo->proximo = NULL;

    if (fila_vazia(fila)){
        fila->inicio = novo;
        fila->fim = novo;
    } else{
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
}

void consultar_proximo(Fila *fila){

    if (fila_vazia(fila)){
        printf("A fila esta vazia.\n");
        return;
    }

    printf("\n========== PROXIMO PEDIDO ==========\n");

    printf("Pedido: %d\n", fila->inicio->pedido.numero);
    printf("Cliente: %s\n", fila->inicio->pedido.cliente);

    printf("Itens:\n");

    for (int i = 0; i < fila->inicio->pedido.quantidade_itens; i++){

        printf("-%s (%dx): R$ %.2f\n",
               fila->inicio->pedido.itens[i].item.nome,
               fila->inicio->pedido.itens[i].quantidade,
               fila->inicio->pedido.itens[i].item.preco *
               fila->inicio->pedido.itens[i].quantidade);
    }

    printf("Total: R$ %.2f\n", fila->inicio->pedido.total);

    printf("------------------------------------\n");
}

int remover_proximo_fila(Fila *fila, Pedido *pedido){
    if (fila_vazia(fila)){
        printf("Fila vazia!\n");
        return 0;
    }

    No *removido = fila->inicio;

    *pedido = removido->pedido;

    fila->inicio = removido->proximo;

    if (fila->inicio == NULL){
        fila->fim = NULL;
    }

    free(removido);
    

    return 1;
}

void limpar_fila(Fila *fila){
    No *atual;

    while (fila->inicio != NULL){
        atual = fila->inicio;
        fila->inicio = fila->inicio->proximo;
        free(atual);
    }

    fila->fim = NULL;
}

void mostrar_fila(Fila *fila){

    if (fila_vazia(fila)){
        printf("A fila esta vazia.\n");
        return;
    }

    No *atual = fila->inicio;

    printf("\n========== FILA DE ESPERA ==========\n");

    while (atual != NULL){

        printf("\nPedido: %d\n", atual->pedido.numero);
        printf("Cliente: %s\n", atual->pedido.cliente);

        printf("Itens:\n");

        for (int i = 0; i < atual->pedido.quantidade_itens; i++){

            printf("-%s (%dx): R$ %.2f\n",
                   atual->pedido.itens[i].item.nome,
                   atual->pedido.itens[i].quantidade,
                   atual->pedido.itens[i].item.preco * atual->pedido.itens[i].quantidade);
        }

        printf("Total: R$ %.2f\n", atual->pedido.total);

        printf("------------------------------------\n");

        atual = atual->proximo;
    }
}