#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <iostream>
using namespace std;

class No{
    public:
        string conteudo;
        int frequencia;
        No *esq;
        No *dir;

        No(string conteudo, int frequencia, No *esq, No *dir);
        No();
        ~No();
        bool ehFolha();
};

class Arvore{
    // private:

    public:
        No *raiz;
        Arvore(No *raiz);
        ~Arvore();
};

class Codigo {
    public:
        string codigo;
        string conteudo;
};

#endif