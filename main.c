#include <stdio.h>
#include "fila.h"
#include "pilha.h"
#include "cardapio.h"

void criar_pedido(Pedido *pedido, Item *cardapio, int total_itens_cardapio, int *proximoNumeroPedido) {

    if (total_itens_cardapio == 0) {
        printf("\nNao ha itens cadastrados no cardapio.\n");
        return;
    }

    pedido->numero = *proximoNumeroPedido;
    (*proximoNumeroPedido)++;

    pedido->quantidade_itens = 0;
    pedido->total = 0;

    printf("\n========== NOVO PEDIDO ==========\n");

    printf("Nome do cliente: ");
    scanf(" %49[^\n]", pedido->cliente);

    while (pedido->quantidade_itens < 10) {

        int codigo;
        int encontrado = -1;
        int quantidade;

        printf("\n");
        mostrar_cardapio(cardapio, total_itens_cardapio);

        printf("\nDigite o codigo do item (0 para finalizar): ");
        scanf("%d", &codigo);

        if (codigo == 0) {
            break;
        }

        for (int i = 0; i < total_itens_cardapio; i++) {
            if (cardapio[i].codigo == codigo) {
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1) {
            printf("Codigo de item invalido.\n");
            continue;
        }

        printf("Quantidade: ");
        scanf("%d", &quantidade);

        if (quantidade <= 0) {
            printf("Quantidade invalida.\n");
            continue;
        }

        pedido->itens[pedido->quantidade_itens].item = cardapio[encontrado];

        pedido->itens[pedido->quantidade_itens].quantidade = quantidade;

        pedido->total += cardapio[encontrado].preco * quantidade;

        pedido->quantidade_itens++;
    }

    if (pedido->quantidade_itens == 0) {
        printf("\nPedido cancelado: nenhum item foi adicionado.\n");
        return;
    }

    printf("\nPedido %d criado com sucesso!\n", pedido->numero);
    printf("Cliente: %s\n", pedido->cliente);
    printf("Total: R$ %.2f\n", pedido->total);
}


int main() {

    Fila fila;
    Pilha pilha;

    Item cardapio[] = {
        {1, "X-Burguer", 12.00},
        {2, "X-Salada", 14.50},
        {3, "X-Bacon", 16.00},
        {4, "Batata Frita", 10.00},
        {5, "Refrigerante", 6.00},
        {6, "Suco", 7.00}
    };

    int total_itens_cardapio = sizeof(cardapio) / sizeof(cardapio[0]);

    int proximoNumeroPedido = 1;

    int opcao;

    iniciar_fila(&fila);
    iniciar_pilha(&pilha);

    do {
        printf("\n========== LANCHONETE ==========\n");
        printf("1 - Adicionar pedido a fila\n");
        printf("2 - Consultar proximo pedido\n");
        printf("3 - Preparar proximo pedido\n");
        printf("4 - Consultar ultimo pedido preparado\n");
        printf("5 - Consultar historico por ID\n");
        printf("6 - Remover ultimo do historico\n");
        printf("7 - Mostrar fila de espera\n");
        printf("8 - Mostrar historico\n");
        printf("9 - Mostrar cardapio\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Pedido pedido;

                criar_pedido(
                    &pedido,
                    cardapio,
                    total_itens_cardapio,
                    &proximoNumeroPedido
                );

                if (pedido.quantidade_itens > 0) {
                    adicionar_fila(&fila, pedido);
                    printf("Pedido adicionado a fila de espera!\n");
                }

                break;
            }

            case 2:
                consultar_proximo(&fila);
                break;

            case 3: {
                Pedido pedido;

                if (remover_proximo_fila(&fila, &pedido)) {

                    adicionar_pilha(&pilha, &pedido);

                    printf("\nPedido %d preparado com sucesso!\n", pedido.numero);
                    printf("Cliente: %s\n", pedido.cliente);
                    printf("Total: R$ %.2f\n", pedido.total);
                }

                break;
            }

            case 4:
                consultar_topo(&pilha);
                break;

            case 5: {
                int numero;

                printf("\nDigite o numero do pedido: ");
                scanf("%d", &numero);

                consultar_por_id(&pilha, numero);

                break;
            }

            case 6: {
                Pedido pedido;

                remover_topo_pilha(&pilha, &pedido);

                break;
            }

            case 7:
                mostrar_fila(&fila);
                break;

            case 8:
                mostrar_pilha(&pilha);
                break;

            case 9:
                mostrar_cardapio(cardapio, total_itens_cardapio);
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 0);

    limpar_fila(&fila);
    limpar_pilha(&pilha);

    return 0;
}
