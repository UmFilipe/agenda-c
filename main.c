#include <stdio.h>
#include <stdlib.h>

struct _data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minuto;
};
typedef struct _data Data;

struct _evento {
   int codigo;
   Data dataEvento;
   float duracao;
   char descricao[100];
   struct _evento *proximo;
};
typedef struct _evento Evento;

struct _agenda {
   Evento *inicio;
   Evento *fim;
};
typedef struct _agenda Agenda;

Evento *incluirEvento(int codigo, Data dataEvento, float duracao, char descricao[100]){
    Evento *evento = (Evento*) malloc(sizeof(Evento));
    evento->codigo = codigo;
    evento->dataEvento = dataEvento;
    evento->duracao = duracao;
    strcpy(evento->descricao, descricao);
    evento->proximo = NULL;
    return evento;
}


void main(){
    printf("Hello world");
}