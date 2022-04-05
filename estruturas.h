#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <iostream>
using namespace std;

/**
 * Definicao da classe No, com seus construtores e rotina de verificacao se o no e folha
 */
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

/**
 * Definicao da classe Arvore 
 */
class Arvore{

    public:
        No *raiz;
        Arvore(No *raiz);
        ~Arvore();
};

/**
 * Definicao da classe Codigo
 */
class Codigo {
    public:
        string codigo;
        string conteudo;

        std::string getCodigo() const;
        std::string getConteudo() const;
};

#endif