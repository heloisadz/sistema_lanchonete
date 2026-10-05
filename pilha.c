#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"
#include "pedido.h"

void iniciar_pilha(Pilha *pilha) {
    pilha->topo = NULL;
}
int pilha_vazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

void adicionar_pilha(Pilha *pilha, Pedido *pedido) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro: nao foi possivel alocar memoria.\n");
        return;
    }

    novo->pedido = *pedido;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}
void consultar_topo(Pilha *pilha) {

    if (pilha_vazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return;
    }

    Pedido *pedido = &pilha->topo->pedido;

    printf("\n========== ULTIMO PEDIDO PREPARADO ==========\n");

    printf("Pedido: %d\n", pedido->numero);
    printf("Cliente: %s\n", pedido->cliente);

    printf("Itens:\n");

    for (int i = 0; i < pedido->quantidade_itens; i++) {

        printf("- %s x%d - R$ %.2f\n",
               pedido->itens[i].item.nome,
               pedido->itens[i].quantidade,
               pedido->itens[i].item.preco * pedido->itens[i].quantidade);
    }

    printf("Total: R$ %.2f\n", pedido->total);
}
int remover_topo_pilha(Pilha *pilha, Pedido *pedido) {
    if (pilha_vazia(pilha)) {
        printf("A pilha esta vazia. Nao ha pedido para remover.\n");
        return 0;
    }

    No *removido = pilha->topo;

    *pedido = removido->pedido;

    pilha->topo = removido->proximo;

    free(removido);
    

    return 1;
}
void limpar_pilha(Pilha *pilha) {
    No *atual;

    while (pilha->topo != NULL) {
        atual = pilha->topo;
        pilha->topo = pilha->topo->proximo;
        free(atual);
    }
}
void mostrar_pilha(Pilha *pilha) {

    if (pilha_vazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return;
    }

    Pilha temporaria;
    iniciar_pilha(&temporaria);

    Pedido pedido;

    printf("\n========== HISTORICO DE PEDIDOS ==========\n");

    while (!pilha_vazia(pilha)) {

        remover_topo_pilha(pilha, &pedido);

        printf("\nPedido: %d\n", pedido.numero);
        printf("Cliente: %s\n", pedido.cliente);

        printf("Itens:\n");

        for (int i = 0; i < pedido.quantidade_itens; i++) {

            printf("- %s x%d - R$ %.2f\n",
                   pedido.itens[i].item.nome,
                   pedido.itens[i].quantidade,
                   pedido.itens[i].item.preco * pedido.itens[i].quantidade);
        }

        printf("Total: R$ %.2f\n", pedido.total);

        printf("------------------------------------------\n");

        adicionar_pilha(&temporaria, &pedido);
    }

    while (!pilha_vazia(&temporaria)) {

        remover_topo_pilha(&temporaria, &pedido);

        adicionar_pilha(pilha, &pedido);
    }
}

void consultar_por_id(Pilha *pilha, int numero) {

    if (pilha_vazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return;
    }

    Pilha temporaria;
    iniciar_pilha(&temporaria);

    Pedido pedido;
    int encontrado = 0;

    while (!pilha_vazia(pilha)) {

        remover_topo_pilha(pilha, &pedido);

        if (pedido.numero == numero) {

            printf("\n========== PEDIDO ENCONTRADO ==========\n");

            printf("Pedido: %d\n", pedido.numero);
            printf("Cliente: %s\n", pedido.cliente);

            printf("Itens:\n");

            for (int i = 0; i < pedido.quantidade_itens; i++) {

                printf("-%s (%dx): R$ %.2f\n",
                       pedido.itens[i].item.nome,
                       pedido.itens[i].quantidade,
                       pedido.itens[i].item.preco *
                       pedido.itens[i].quantidade);
            }

            printf("Total: R$ %.2f\n", pedido.total);

            printf("---------------------------------------\n");

            encontrado = 1;
        }

        adicionar_pilha(&temporaria, &pedido);
    }

    while (!pilha_vazia(&temporaria)) {

        remover_topo_pilha(&temporaria, &pedido);

        adicionar_pilha(pilha, &pedido);
    }

    if (!encontrado) {
        printf("Pedido %d nao encontrado no historico.\n", numero);
    }
}