#include <stdio.h>
#include "functions.h"

int main() {
    int opcao;

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
                liberarAgenda();
                printf("Encerrando o programa.\n");
                break;
            case 1:
                incluirCompromisso();
                break;
            case 2:
                consultarCompromissoData();
                break;
            case 3:
                consultarCompromissoDataHora();
                break;
            case 4:
                alterarCompromisso();
                break;
            case 5:
                excluirCompromisso();
                break;
            case 6:
                listarCompromissos();
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
