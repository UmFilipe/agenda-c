#include <stdio.h>
#include "functions.h"

int main() {
    int opcao, opcaoConsulta, dia, mes, ano, hora, minuto;
    Evento *raiz = NULL;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Incluir evento\n");
        printf("2. Consultar evento\n");
        printf("3. Alterar evento\n");
        printf("4. Excluir evento\n");
        printf("5. Listar todos os eventos\n");
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
                printf("Deseja consultar por:\n");
                printf("1. Data\n");
                printf("2. Data e hora\n");
                scanf("%d", &opcaoConsulta);
                if(opcaoConsulta == 1){
                    consultarEventoData(raiz);
                } else if(opcaoConsulta == 2){
                    consultarEventoDataHora(raiz);
                }
                break;
            case 3:
                alterarEvento(raiz);
                break;
            case 4:
                raiz = removerEvento(&raiz);
                break;
            case 5:
                listarEventos(raiz);
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
