#ifndef PEDIDO_H
#define PEDIDO_H

typedef struct{
    int codigo;
    char nome[50];
    float preco;
} Item;

typedef struct{
    Item item;
    int quantidade;
} ItemPedido;

typedef struct{
    int numero;
    char cliente[50];

    ItemPedido itens[10];
    int quantidade_itens;

    float total;
} Pedido;

typedef struct No{
    Pedido pedido;
    struct No *proximo;
} No;

#endif