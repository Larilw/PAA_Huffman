#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "estruturas.h"
#include "constantes.h"
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

/**
 * Definicao da classe Simbolo
 */
class Simbolo{
    public:
        string simbolo;
        int nAparicoes;

        Simbolo();
        ~Simbolo();
};

/**
 * Definicao da classe Arquivo, com as rotinas de gerar nos e escrever a codificacao
 */
class Arquivo{
    public:
        ofstream arq;
        Arquivo();
        ~Arquivo();
        void contarAparicoes(string conteudoArq, Simbolo simbolos[]);
        void gerarNos(No nos[], int *tamNos, bool tipoCodificacao, string texto);
        void escreverCodificacao(std::vector<Codigo> codes);
};

#endif