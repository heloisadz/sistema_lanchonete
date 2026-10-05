#ifndef PILHA_H
#define PILHA_H

#include "pedido.h"

typedef struct{
    No *topo;
} Pilha;

void iniciar_pilha(Pilha *pilha);
int pilha_vazia(Pilha *pilha);
void adicionar_pilha(Pilha *pilha, Pedido *pedido);
void consultar_topo(Pilha *pilha);
int remover_topo_pilha(Pilha *pilha, Pedido *pedido);
void limpar_pilha(Pilha *pilha);
void mostrar_pilha(Pilha *pilha);
void consultar_por_id(Pilha *pilha, int numero);

#endif