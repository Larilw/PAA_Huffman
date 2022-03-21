#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "estruturas.h"
#include "constantes.h"
#include <string>
#include <iostream>
<<<<<<< HEAD
#include <string.h>
=======
#include <sstream>
>>>>>>> f7f18832876d1c9c54e5f099ca7b79635965d10b
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
        void contarPalavras(string conteudoArq, Simbolo simbolos[]);
};

#endif