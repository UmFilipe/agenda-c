#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// -1 - primeira data maior que a segunda
// 0 - datas iguais
// 1 - segunda data maior que a primeira
int compararDataHora(Data dataHora1, Data dataHora2) {
    if (dataHora1.ano != dataHora2.ano) {
        return (dataHora1.ano < dataHora2.ano) ? -1 : 1; 
    } else if (dataHora1.mes != dataHora2.mes) {
        return (dataHora1.mes < dataHora2.mes) ? -1 : 1;
    } else if (dataHora1.dia != dataHora2.dia) {
        return (dataHora1.dia < dataHora2.dia) ? -1 : 1;
    } else if (dataHora1.hora != dataHora2.hora) {
        return (dataHora1.hora < dataHora2.hora) ? -1 : 1;
    } else if (dataHora1.minuto != dataHora2.minuto) {
        return (dataHora1.minuto < dataHora2.minuto) ? -1 : 1;
    } else {
        return 0;
    }
}

// Inserir evento criado no local certo na árvore
Evento *inserirEvento(Evento *raiz, Evento *novoEvento) {
    if (raiz == NULL) {
        return novoEvento;
    }

    if (compararDataHora(novoEvento->dataEvento, raiz->dataEvento) < 0) {
        raiz->esquerda = inserirEvento(raiz->esquerda, novoEvento);
    } else {
        raiz->direita = inserirEvento(raiz->direita, novoEvento);
    }

    return raiz;
}

Evento *criarEvento(Evento *raiz) {
    Evento *novoEvento = (Evento*)malloc(sizeof(Evento));
    printf("Digite o código do evento: ");
    scanf("%d", &(novoEvento->codigo));

    // Verifica se o evento já existe na agenda
    Evento *atual = raiz;
    while (atual != NULL) {
        if (compararDataHora(novoEvento->dataEvento, atual->dataEvento) == 0) {
            printf("Já existe um evento para a mesma data e hora.\n");
            free(novoEvento);
            return raiz;
        }
        atual = (compararDataHora(novoEvento->dataEvento, atual->dataEvento) < 0) ? atual->esquerda : atual->direita;
    }
    int dia, mes, ano, hora, minuto;
    printf("Digite o dia do evento a ser criado (dd): ");
    scanf("%d", &(novoEvento->dataEvento.dia));
    printf("Digite o mês do evento a ser criado (mm): ");
    scanf("%d", &(novoEvento->dataEvento.mes));
    printf("Digite o ano do evento a ser criado (aaaa): ");
    scanf("%d", &(novoEvento->dataEvento.ano));
    printf("Digite a hora do evento a ser criado (hh): ");
    scanf("%d", &(novoEvento->dataEvento.hora));
    printf("Digite o minuto do evento a ser criado (mm): ");
    scanf("%d", &(novoEvento->dataEvento.minuto));
    printf("Digite a duração do evento (em horas): ");
    scanf("%f", &(novoEvento->duracao));
    printf("Digite a descrição do evento: ");
    scanf(" %[^\n]s", novoEvento->descricao);

    raiz = inserirEvento(raiz, novoEvento);

    printf("Evento incluído com sucesso!\n");
    return raiz;
}

Evento *buscarEvento(Evento* raiz, int dia, int mes, int ano, int hora, int minuto) {
    if (raiz == NULL) {
        return NULL;
    }

    Data dataHora = {dia, mes, ano, hora, minuto};
    int comparacao = compararDataHora(dataHora, raiz->dataEvento);

    if (comparacao == 0) {
        return raiz;
    } else if (comparacao < 0) {
        return buscarEvento(raiz->esquerda, dia, mes, ano, hora, minuto);
    } else {
        return buscarEvento(raiz->direita, dia, mes, ano, hora, minuto);
    }
}

void consultarEventoData(Evento *raiz) {
    int dia, mes, ano;
    printf("Digite p dia do evento: ");
    scanf("%d", &dia);
    printf("Digite o mês do evento: ");
    scanf("%d", &mes);
    printf("Digite o ano do evento: ");
    scanf("%d", &ano);

    // Buscar compromissos na data especificada
    Evento* atual = raiz;
    int encontrou = 0;

    while (atual != NULL) {
        if (atual->dataEvento.dia == dia && atual->dataEvento.mes == mes && atual->dataEvento.ano == ano) {
            printf("Código: %d\n", atual->codigo);
            printf("Data: %02d/%02d/%04d\n", atual->dataEvento.dia, atual->dataEvento.mes, atual->dataEvento.ano);
            printf("Hora: %02d:%02d\n", atual->dataEvento.hora, atual->dataEvento.minuto);
            printf("Duração: %.2f horas\n", atual->duracao);
            printf("Descrição: %s\n\n", atual->descricao);
            encontrou = 1;
        }

        if (atual->codigo >= dia) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    if (!encontrou) {
        printf("Agenda vazia ou não foram encontrados compromissos para a data especificada.\n");
    }
}

void consultarEventoDataHora(Evento *raiz) {
    int dia, mes, ano, hora, minuto;
    printf("Digite o ano do evento: ");
    scanf("%d", &ano);
    printf("Digite o mês do evento: ");
    scanf("%d", &mes);
    printf("Digite o dia do evento: ");
    scanf("%d", &dia);
    printf("Digite a hora do evento: ");
    scanf("%d", &hora);
    printf("Digite o minuto do evento: ");
    scanf("%d", &minuto);

    // Buscar evento na data e hora especificadas
    Evento* evento = buscarEvento(raiz, dia, mes, ano, hora, minuto);

    if (evento != NULL) {
        printf("Código: %d\n", evento->codigo);
        printf("Data: %02d/%02d/%04d\n", evento->dataEvento.dia, evento->dataEvento.mes, evento->dataEvento.ano);
        printf("Hora: %02d:%02d\n", evento->dataEvento.hora, evento->dataEvento.minuto);
        printf("Duração: %.2f horas\n", evento->duracao);
        printf("Descrição: %s\n\n", evento->descricao);
    } else {
        printf("Agenda vazia ou não foi encontrado evento para a data e hora especificadas.\n");
    }
}

Evento* encontrarMenor(Evento *raiz) {
    if (raiz == NULL)
        return NULL;
    while (raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

Evento* removerEvento(Evento *raiz) {
    int dia, mes, ano, hora, minuto;
    printf("Digite o dia do evento a ser removido (dd): ");
    scanf("%d", &dia);
    printf("Digite o mês do evento a ser removido (mm): ");
    scanf("%d", &mes);
    printf("Digite o ano do evento a ser removido (aaaa): ");
    scanf("%d", &ano);
    printf("Digite a hora do evento a ser removido (hh): ");
    scanf("%d", &hora);
    printf("Digite o minuto do evento a ser removido (mm): ");
    scanf("%d", &minuto);


    Evento* evento = buscarEvento(raiz, dia, mes, ano, hora, minuto);

    if (evento != NULL) {
        // Caso 1: nó folha
        if (evento->esquerda == NULL && evento->direita == NULL) {
            free(evento);
            return NULL;
        }

        // Caso 2: nó com apenas um filho
        if (evento->esquerda == NULL) {
            Evento *temp = evento->direita;
            free(evento);
            return temp;
        } else if (evento->direita == NULL) {
            Evento *temp = evento->esquerda;
            free(evento);
            return temp;
        }

        // Caso 3: nó com dois filhos
        Evento *temp = encontrarMenor(evento->direita);
        evento->codigo = temp->codigo;
        evento->dataEvento = temp->dataEvento;
        evento->duracao = temp->duracao;
        strcpy(evento->descricao, temp->descricao);
        evento->direita = removerEvento(evento->direita);
    } else {
        printf("Compromisso não encontrado.\n");
    }

    return raiz;
}

void alterarEvento(Evento *raiz) {
    int dia, mes, ano, hora, minuto;
    printf("Digite o dia do evento: ");
    scanf("%d", &dia);
    printf("Digite o mês do evento: ");
    scanf("%d", &mes);
    printf("Digite o ano do evento: ");
    scanf("%d", &ano);
    printf("Digite a hora do evento: ");
    scanf("%d", &hora);
    printf("Digite o minuto do evento: ");
    scanf("%d", &minuto);

    Evento* evento = buscarEvento(raiz, dia, mes, ano, hora, minuto);

    if (evento != NULL) {
        printf("Digite a nova descrição do evento: ");
        scanf(" %[^\n]s", evento->descricao);
        printf("Digite a nova duração do evento (em horas): ");
        scanf("%f", &(evento->duracao));
        printf("Compromisso alterado com sucesso!\n");
    } else {
        printf("Compromisso não encontrado.\n");
    }
}

void listarEventos(Evento *raiz) {
    if (raiz == NULL) {
        printf("Agenda vazia.\n");
    } else {
        printf("Código: %d\n", raiz->codigo);
        printf("Data: %02d/%02d/%04d\n", raiz->dataEvento.dia, raiz->dataEvento.mes, raiz->dataEvento.ano);
        printf("Hora: %02d:%02d\n", raiz->dataEvento.hora, raiz->dataEvento.minuto);
        printf("Duração: %.2f horas\n", raiz->duracao);
        printf("Descrição: %s\n\n", raiz->descricao);
        
        if(raiz->esquerda != NULL){
            listarEventos(raiz->esquerda);
        }
        if(raiz->direita != NULL){
            listarEventos(raiz->direita);
        }
    }
}