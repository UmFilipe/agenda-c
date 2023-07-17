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

    int comparacao = compararDataHora(novoEvento->dataEvento, raiz->dataEvento);

    if (comparacao == 0) {
        // inserir à esquerda para manter a ordem crescente.
        raiz->esquerda = inserirEvento(raiz->esquerda, novoEvento);
    } else if (comparacao < 0) {
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
    printf("Digite o dia do evento (dd): ");
    scanf("%d", &dia);
    printf("Digite o mês do evento (mm): ");
    scanf("%d", &mes);
    printf("Digite o ano do evento (aaaa): ");
    scanf("%d", &ano);

    // Busca eventos na data especificada
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

    if (atual->dataEvento.ano >= ano && atual->dataEvento.mes >= mes && atual->dataEvento.dia >= dia) {
        atual = atual->esquerda;
    } else {
        atual = atual->direita;
    }
}
    if (!encontrou) {
        printf("Agenda vazia ou não foram encontrados eventos para a data especificada.\n");
    }
}

void consultarEventoDataHora(Evento *raiz) {
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

    // Busca evento na data e hora especificadas
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

Evento *encontrarMenorEvento(Evento **raiz) {
    if ((*raiz)->esquerda == NULL) {
        Evento* temp = *raiz;
        *raiz = (*raiz)->direita;
        return temp;
    }
    return encontrarMenorEvento(&(*raiz)->esquerda);
}

Evento* removerEventoAux(Evento* evento) {
    // Remoção de nó sem filhos
    if (evento->esquerda == NULL && evento->direita == NULL) {
        free(evento);
        return NULL;
    }
    // Remoção de nó com apenas um filho
    else if (evento->esquerda == NULL) {
        Evento* temp = evento->direita;
        free(evento);
        return temp;
    } else if (evento->direita == NULL) {
        Evento* temp = evento->esquerda;
        free(evento);
        return temp;
    }
    // Remoçãod de nó com dois filhos
    else {
        Evento* temp = encontrarMenorEvento(&evento->direita);
        evento->codigo = temp->codigo;
        evento->dataEvento = temp->dataEvento;
        evento->duracao = temp->duracao;
        strcpy(evento->descricao, temp->descricao);
        evento->direita = removerEventoAux(evento->direita);
        return evento;
    }
}

Evento* removerEvento(Evento **raiz) {
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

    Evento* pai = NULL;
    Evento* atual = *raiz;

    // Encontra o evento a ser removido e seu nó pai
    while (atual != NULL) {
        if (atual->dataEvento.ano == ano && atual->dataEvento.mes == mes && atual->dataEvento.dia == dia &&
            atual->dataEvento.hora == hora && atual->dataEvento.minuto == minuto) {
            break;
        }
        pai = atual;
        if (atual->dataEvento.ano >= ano && atual->dataEvento.mes >= mes && atual->dataEvento.dia >= dia &&
            atual->dataEvento.hora >= hora && atual->dataEvento.minuto >= minuto) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    if (atual != NULL) {
        if (pai == NULL) {
            *raiz = removerEventoAux(atual);
        } else if (pai->esquerda == atual) {
            pai->esquerda = removerEventoAux(atual);
        } else {
            pai->direita = removerEventoAux(atual);
        }
    } else {
        printf("Evento não encontrado.\n");
    }

    return *raiz;
}


void alterarEvento(Evento* raiz) {
    int dia, mes, ano, hora, minuto, diaEdicao, mesEdicao, anoEdicao, horaEdicao, minutoEdicao;
    char descricaoEdicao[100];
    float duracaoEdicao;
    
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
        printf("Digite o novo dia do evento (digite -1 caso queira manter igual): ");
        scanf("%d", &diaEdicao);
        printf("Digite o novo mês do evento (digite -1 caso queira manter igual): ");
        scanf("%d", &mesEdicao);
        printf("Digite o novo ano do evento (digite -1 caso queira manter igual): ");
        scanf("%d", &anoEdicao);
        printf("Digite a nova hora do evento (digite -1 caso queira manter igual): ");
        scanf("%d", &horaEdicao);
        printf("Digite o novo minuto do evento (digite -1 caso queira manter igual): ");
        scanf("%d", &minutoEdicao);
        printf("Digite a nova descrição do evento (digite -1 caso queira manter igual): ");
        scanf(" %[^\n]s", descricaoEdicao);
        printf("Digite a nova duração do evento (digite -1 caso queira manter igual): ");
        scanf("%f", &duracaoEdicao);

        if (diaEdicao != -1) {
            evento->dataEvento.dia = diaEdicao;
        }
        if (mesEdicao != -1) {
            evento->dataEvento.mes = mesEdicao;
        }
        if (anoEdicao != -1) {
            evento->dataEvento.ano = anoEdicao;
        }
        if (horaEdicao != -1) {
            evento->dataEvento.hora = horaEdicao;
        }
        if (minutoEdicao != -1) {
            evento->dataEvento.minuto = minutoEdicao;
        }
        if (strcmp(descricaoEdicao, "-1") != 0) {
            strcpy(evento->descricao, descricaoEdicao);
        }
        if (duracaoEdicao != -1) {
            evento->duracao = duracaoEdicao;
        }

        printf("Evento alterado com sucesso!\n");
    } else {
        printf("Evento não encontrado.\n");
    }
}


void listarEventos(Evento *raiz) {
    if (raiz == NULL) {
        printf("Agenda vazia.\n");
    } else {
        if (raiz->esquerda != NULL) {
            listarEventos(raiz->esquerda);
        }

        printf("Código: %d\n", raiz->codigo);
        printf("Data: %02d/%02d/%04d\n", raiz->dataEvento.dia, raiz->dataEvento.mes, raiz->dataEvento.ano);
        printf("Hora: %02d:%02d\n", raiz->dataEvento.hora, raiz->dataEvento.minuto);
        printf("Duração: %.2f horas\n", raiz->duracao);
        printf("Descrição: %s\n\n", raiz->descricao);

        if (raiz->direita != NULL) {
            listarEventos(raiz->direita);
        }
    }
}
