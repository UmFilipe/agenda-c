#include <stdio.h>
#include "functions.h"

int main() {
    int opcao, dia, mes, ano, hora, minuto;
    Evento *raiz = NULL;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Incluir compromisso\n");
        printf("2. Consultar compromisso por data\n");
        printf("3. Consultar compromisso por data e hora\n");
        printf("4. Alterar compromisso\n");
        printf("5. Excluir compromisso\n");
        printf("6. Listar todos os compromissos\n");
        printf("0. Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 0:
                printf("Encerrando o programa.\n");
                break;
            case 1:
                raiz = criarEvento(raiz);
                break;
            case 2:
                consultarEventoData(raiz);
                break;
            case 3:
                consultarEventoDataHora(raiz);
                break;
            case 4:
                alterarEvento(raiz);
                break;
            case 5:
                removerEvento(raiz);
                break;
            case 6:
                listarEventos(raiz);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
