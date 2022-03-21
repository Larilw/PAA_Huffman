#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "estruturas.h"
#include "constantes.h"
#include <string>
#include <iostream>
#include <string.h>
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

        Arquivo();
        ~Arquivo();
        void contarAparicoes(string conteudoArq, Simbolo simbolos[], bool tipoCodificacao);
        void gerarNos(No nos[], int *tamNos, bool tipoCodificacao);
        
};

#endif