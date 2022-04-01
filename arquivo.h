#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "estruturas.h"
#include "constantes.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


class Simbolo{
    public:
        string simbolo;
        int nAparicoes;

        Simbolo();
        ~Simbolo();
};

class Arquivo{
    public:
        ofstream arq;
        Arquivo();
        ~Arquivo();
        void contarAparicoes(string conteudoArq, Simbolo simbolos[], bool tipoCodificacao);
        void gerarNos(No nos[], int *tamNos, bool tipoCodificacao, string texto);
        void contarPalavras(string conteudoArq, Simbolo simbolos[]);
        void escreverCodificacao(std::vector<Codigo> codes);
};

#endif