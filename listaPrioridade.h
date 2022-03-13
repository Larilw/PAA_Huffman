#ifndef LISTAPRIORIDADE_H
#define LISTAPRIORIDADE_H

#include "estruturas.h"
#include "constantes.h"
#include "arquivo.h"

class ListaPrioridade{
    public:
        No no;
        ListaPrioridade *prox;
        ListaPrioridade(No no);
        ~ListaPrioridade();
        No obterNo();
        No *obterProx();
        void inserirOrdenado(No no);
};

#endif