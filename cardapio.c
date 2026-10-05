#include <stdio.h>
#include "cardapio.h"

void mostrar_cardapio(Item cardapio[], int total_itens_cardapio) {

    printf("\n===== CARDAPIO =====\n");

    for (int i = 0; i < total_itens_cardapio; i++) {
        printf("%d - %s - R$ %.2f\n",
               cardapio[i].codigo,
               cardapio[i].nome,
               cardapio[i].preco);
    }

    printf("====================\n");
}