#ifndef FILA_H
#define FILA_H

#include "pedido.h"

typedef struct{
    No *inicio;
    No *fim;
} Fila;

void iniciar_fila(Fila *fila);
int fila_vazia(Fila *fila);
void adicionar_fila(Fila *fila, Pedido pedido);
void consultar_proximo(Fila *fila);
int remover_proximo_fila(Fila *fila, Pedido *pedido);
void limpar_fila(Fila *fila);
void mostrar_fila(Fila *fila);
#endif