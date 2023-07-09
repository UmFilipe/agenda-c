#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

Evento* criarEvento(int codigo, Data data, float duracao, char* descricao) {
    Evento* novoEvento = (Evento*)malloc(sizeof(Evento));
    novoEvento->codigo = codigo;
    novoEvento->dataEvento = data;
    novoEvento->duracao = duracao;
    strcpy(novoEvento->descricao, descricao);
    novoEvento->esquerda = NULL;
    novoEvento->direita = NULL;
    return novoEvento;
}

Evento* inserirEvento(Evento* raiz, Evento* novoEvento) {
    if (raiz == NULL) {
        return novoEvento;
    }

    if (novoEvento->codigo < raiz->codigo) {
        raiz->esquerda = inserirEvento(raiz->esquerda, novoEvento);
    } else if (novoEvento->codigo > raiz->codigo) {
        raiz->direita = inserirEvento(raiz->direita, novoEvento);
    }

    return raiz;
}

void incluirCompromisso() {
    Evento* novoCompromisso = (Evento*)malloc(sizeof(Evento));
    printf("Digite o código do compromisso: ");
    scanf("%d", &(novoCompromisso->codigo));
    printf("Digite a data do compromisso (DD MM AAAA HH MM): ");
    scanf("%d %d %d %d %d", &(novoCompromisso->dataEvento.dia), &(novoCompromisso->dataEvento.mes),
          &(novoCompromisso->dataEvento.ano), &(novoCompromisso->dataEvento.hora), &(novoCompromisso->dataEvento.minuto));

    // Verificar se o compromisso já existe na agenda
    Evento* atual = agenda;
    while (atual != NULL) {
        if (atual->codigo == novoCompromisso->codigo) {
            printf("Já existe um compromisso com o mesmo código.\n");
            free(novoCompromisso);
            return;
        }
        atual = (novoCompromisso->codigo < atual->codigo) ? atual->esquerda : atual->direita;
    }

    printf("Digite a duração do compromisso (em horas): ");
    scanf("%f", &(novoCompromisso->duracao));
    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]s", novoCompromisso->descricao);

    agenda = inserirEvento(agenda, novoCompromisso);

    printf("Compromisso incluído com sucesso!\n");
}

Evento* buscarEvento(Evento* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo == codigo) {
        return raiz;
    }

    if (codigo < raiz->codigo) {
        return buscarEvento(raiz->esquerda, codigo);
    } else {
        return buscarEvento(raiz->direita, codigo);
    }
}

void consultarCompromissoData() {
    int dia, mes, ano;
    printf("Digite a data para consulta (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    // Buscar compromissos na data especificada
    Evento* atual = agenda;
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

void consultarCompromissoDataHora() {
    int dia, mes, ano, hora, minuto;
    printf("Digite a data e hora para consulta (DD MM AAAA HH MM): ");
    scanf("%d %d %d %d %d", &dia, &mes, &ano, &hora, &minuto);

    // Buscar compromisso na data e hora especificadas
    Evento* atual = agenda;
    int encontrou = 0;

    while (atual != NULL) {
        if (atual->dataEvento.dia == dia && atual->dataEvento.mes == mes && atual->dataEvento.ano == ano &&
            atual->dataEvento.hora == hora && atual->dataEvento.minuto == minuto) {
            printf("Código: %d\n", atual->codigo);
            printf("Data: %02d/%02d/%04d\n", atual->dataEvento.dia, atual->dataEvento.mes, atual->dataEvento.ano);
            printf("Hora: %02d:%02d\n", atual->dataEvento.hora, atual->dataEvento.minuto);
            printf("Duração: %.2f horas\n", atual->duracao);
            printf("Descrição: %s\n\n", atual->descricao);
            encontrou = 1;
            break;
        }

        if (atual->dataEvento.ano > ano ||
            (atual->dataEvento.ano == ano && (atual->dataEvento.mes > mes ||
                                              (atual->dataEvento.mes == mes && (atual->dataEvento.dia > dia ||
                                                                                  (atual->dataEvento.dia == dia &&
                                                                                   (atual->dataEvento.hora > hora ||
                                                                                    (atual->dataEvento.hora == hora &&
                                                                                     atual->dataEvento.minuto > minuto)))))))) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    if (!encontrou) {
        printf("Agenda vazia ou não foi encontrado compromisso para a data e hora especificadas.\n");
    }
}


Evento* buscarMenor(Evento* raiz) {
   Evento* atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Evento* removerEvento(Evento* raiz, int codigo) {
    if (raiz == NULL) {
        return raiz;
    }

    if (codigo < raiz->codigo) {
        raiz->esquerda = removerEvento(raiz->esquerda, codigo);
    } else if (codigo > raiz->codigo) {
        raiz->direita = removerEvento(raiz->direita, codigo);
    } else {
        if (raiz->esquerda == NULL) {
            Evento* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Evento* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Evento* temp = buscarMenor(raiz->direita);
        raiz->codigo = temp->codigo;
        raiz->dataEvento = temp->dataEvento;
        raiz->duracao = temp->duracao;
        strcpy(raiz->descricao, temp->descricao);
        raiz->direita = removerEvento(raiz->direita, temp->codigo);
    }

    return raiz;
}

void excluirCompromisso() {
    int codigo;
    printf("Digite o código do compromisso a ser excluído: ");
    scanf("%d", &codigo);

    // Remover o compromisso da agenda
    Evento* compromisso = buscarEvento(agenda, codigo);

    if (compromisso != NULL) {
        agenda = removerEvento(agenda, codigo);
        printf("Compromisso excluído com sucesso!\n");
    } else {
        printf("Compromisso não encontrado.\n");
    }
}

void alterarCompromisso() {
    int codigo;
    printf("Digite o código do compromisso a ser alterado: ");
    scanf("%d", &codigo);

    Evento* compromisso = buscarEvento(agenda, codigo);

    if (compromisso != NULL) {
        printf("Digite a nova descrição do compromisso: ");
        scanf(" %[^\n]s", compromisso->descricao);
        printf("Digite a nova duração do compromisso (em horas): ");
        scanf("%f", &(compromisso->duracao));
        printf("Compromisso alterado com sucesso!\n");
    } else {
        printf("Compromisso não encontrado.\n");
    }
}

void listarCompromissosAux(Evento* raiz) {
    if (raiz != NULL) {
        listarCompromissosAux(raiz->esquerda);
        printf("Código: %d\n", raiz->codigo);
        printf("Data: %02d/%02d/%04d\n", raiz->dataEvento.dia, raiz->dataEvento.mes, raiz->dataEvento.ano);
        printf("Hora: %02d:%02d\n", raiz->dataEvento.hora, raiz->dataEvento.minuto);
        printf("Duração: %.2f horas\n", raiz->duracao);
        printf("Descrição: %s\n\n", raiz->descricao);
        listarCompromissosAux(raiz->direita);
    }
}

void listarCompromissos() {
    if (agenda == NULL) {
        printf("Agenda vazia.\n");
    } else {
        listarCompromissosAux(agenda);
    }
}

void liberarAgendaAux(Evento* raiz) {
    if (raiz != NULL) {
        liberarAgendaAux(raiz->esquerda);
        liberarAgendaAux(raiz->direita);
        free(raiz);
    }
}

void liberarAgenda() {
    liberarAgendaAux(agenda);
    agenda = NULL;
}
#include "structs.h"

Evento* agenda = NULL;

Evento* criarEvento(int codigo, Data data, float duracao, char* descricao) {
    Evento* novoEvento = (Evento*)malloc(sizeof(Evento));
    novoEvento->codigo = codigo;
    novoEvento->dataEvento = data;
    novoEvento->duracao = duracao;
    strcpy(novoEvento->descricao, descricao);
    novoEvento->esquerda = NULL;
    novoEvento->direita = NULL;
    return novoEvento;
}

Evento* inserirEvento(Evento* raiz, Evento* novoEvento) {
    if (raiz == NULL) {
        return novoEvento;
    }

    if (novoEvento->codigo < raiz->codigo) {
        raiz->esquerda = inserirEvento(raiz->esquerda, novoEvento);
    } else if (novoEvento->codigo > raiz->codigo) {
        raiz->direita = inserirEvento(raiz->direita, novoEvento);
    }

    return raiz;
}

void incluirCompromisso() {
    Evento* novoCompromisso = (Evento*)malloc(sizeof(Evento));
    printf("Digite o código do compromisso: ");
    scanf("%d", &(novoCompromisso->codigo));
    printf("Digite a data do compromisso (DD MM AAAA HH MM): ");
    scanf("%d %d %d %d %d", &(novoCompromisso->dataEvento.dia), &(novoCompromisso->dataEvento.mes),
          &(novoCompromisso->dataEvento.ano), &(novoCompromisso->dataEvento.hora), &(novoCompromisso->dataEvento.minuto));

    // Verificar se o compromisso já existe na agenda
    Evento* atual = agenda;
    while (atual != NULL) {
        if (atual->codigo == novoCompromisso->codigo) {
            printf("Já existe um compromisso com o mesmo código.\n");
            free(novoCompromisso);
            return;
        }
        atual = (novoCompromisso->codigo < atual->codigo) ? atual->esquerda : atual->direita;
    }

    printf("Digite a duração do compromisso (em horas): ");
    scanf("%f", &(novoCompromisso->duracao));
    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]s", novoCompromisso->descricao);

    agenda = inserirEvento(agenda, novoCompromisso);

    printf("Compromisso incluído com sucesso!\n");
}

Evento* buscarEvento(Evento* raiz, int codigo) {
    if (raiz == NULL || raiz->codigo == codigo) {
        return raiz;
    }

    if (codigo < raiz->codigo) {
        return buscarEvento(raiz->esquerda, codigo);
    } else {
        return buscarEvento(raiz->direita, codigo);
    }
}

void consultarCompromissoData() {
    int dia, mes, ano;
    printf("Digite a data para consulta (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    // Buscar compromissos na data especificada
    Evento* atual = agenda;
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

void consultarCompromissoDataHora() {
    int dia, mes, ano, hora, minuto;
    printf("Digite a data e hora para consulta (DD MM AAAA HH MM): ");
    scanf("%d %d %d %d %d", &dia, &mes, &ano, &hora, &minuto);

    // Buscar compromisso na data e hora especificadas
    Evento* atual = agenda;
    int encontrou = 0;

    while (atual != NULL) {
        if (atual->dataEvento.dia == dia && atual->dataEvento.mes == mes && atual->dataEvento.ano == ano &&
            atual->dataEvento.hora == hora && atual->dataEvento.minuto == minuto) {
            printf("Código: %d\n", atual->codigo);
            printf("Data: %02d/%02d/%04d\n", atual->dataEvento.dia, atual->dataEvento.mes, atual->dataEvento.ano);
            printf("Hora: %02d:%02d\n", atual->dataEvento.hora, atual->dataEvento.minuto);
            printf("Duração: %.2f horas\n", atual->duracao);
            printf("Descrição: %s\n\n", atual->descricao);
            encontrou = 1;
            break;
        }

        if (atual->dataEvento.ano > ano ||
            (atual->dataEvento.ano == ano && (atual->dataEvento.mes > mes ||
                                              (atual->dataEvento.mes == mes && (atual->dataEvento.dia > dia ||
                                                                                  (atual->dataEvento.dia == dia &&
                                                                                   (atual->dataEvento.hora > hora ||
                                                                                    (atual->dataEvento.hora == hora &&
                                                                                     atual->dataEvento.minuto > minuto)))))))) {
            atual = atual->esquerda;
        } else {
            atual = atual->direita;
        }
    }

    if (!encontrou) {
        printf("Agenda vazia ou não foi encontrado compromisso para a data e hora especificadas.\n");
    }
}


Evento* buscarMenor(Evento* raiz) {
   Evento* atual = raiz;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

Evento* removerEvento(Evento* raiz, int codigo) {
    if (raiz == NULL) {
        return raiz;
    }

    if (codigo < raiz->codigo) {
        raiz->esquerda = removerEvento(raiz->esquerda, codigo);
    } else if (codigo > raiz->codigo) {
        raiz->direita = removerEvento(raiz->direita, codigo);
    } else {
        if (raiz->esquerda == NULL) {
            Evento* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Evento* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        Evento* temp = buscarMenor(raiz->direita);
        raiz->codigo = temp->codigo;
        raiz->dataEvento = temp->dataEvento;
        raiz->duracao = temp->duracao;
        strcpy(raiz->descricao, temp->descricao);
        raiz->direita = removerEvento(raiz->direita, temp->codigo);
    }

    return raiz;
}

void excluirCompromisso() {
    int codigo;
    printf("Digite o código do compromisso a ser excluído: ");
    scanf("%d", &codigo);

    // Remover o compromisso da agenda
    Evento* compromisso = buscarEvento(agenda, codigo);

    if (compromisso != NULL) {
        agenda = removerEvento(agenda, codigo);
        printf("Compromisso excluído com sucesso!\n");
    } else {
        printf("Compromisso não encontrado.\n");
    }
}

void alterarCompromisso() {
    int codigo;
    printf("Digite o código do compromisso a ser alterado: ");
    scanf("%d", &codigo);

    Evento* compromisso = buscarEvento(agenda, codigo);

    if (compromisso != NULL) {
        printf("Digite a nova descrição do compromisso: ");
        scanf(" %[^\n]s", compromisso->descricao);
        printf("Digite a nova duração do compromisso (em horas): ");
        scanf("%f", &(compromisso->duracao));
        printf("Compromisso alterado com sucesso!\n");
    } else {
        printf("Compromisso não encontrado.\n");
    }
}

void listarCompromissosAux(Evento* raiz) {
    if (raiz != NULL) {
        listarCompromissosAux(raiz->esquerda);
        printf("Código: %d\n", raiz->codigo);
        printf("Data: %02d/%02d/%04d\n", raiz->dataEvento.dia, raiz->dataEvento.mes, raiz->dataEvento.ano);
        printf("Hora: %02d:%02d\n", raiz->dataEvento.hora, raiz->dataEvento.minuto);
        printf("Duração: %.2f horas\n", raiz->duracao);
        printf("Descrição: %s\n\n", raiz->descricao);
        listarCompromissosAux(raiz->direita);
    }
}

void listarCompromissos() {
    if (agenda == NULL) {
        printf("Agenda vazia.\n");
    } else {
        listarCompromissosAux(agenda);
    }
}

void liberarAgendaAux(Evento* raiz) {
    if (raiz != NULL) {
        liberarAgendaAux(raiz->esquerda);
        liberarAgendaAux(raiz->direita);
        free(raiz);
    }
}

void liberarAgenda() {
    liberarAgendaAux(agenda);
    agenda = NULL;
}