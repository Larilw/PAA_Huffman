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
    private:
        No *raiz;

    public:
        Arvore(No *raiz);
        ~Arvore();
};

#endif