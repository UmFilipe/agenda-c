// Arquivo com as estruturas utilizadas no projeto

typedef struct _data Data;
typedef struct _evento Evento;

struct _data {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};

struct _evento {
    int codigo;
    Data dataEvento;
    float duracao;
    char descricao[100];
    struct _evento* esquerda;
    struct _evento* direita;
};