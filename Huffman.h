#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;
#include "listaPrioridade.h"

class Huffman{
    public:
        No *gerarArvore(ListaPrioridade *lista);
        void codificar_recursiva(No *raiz, std::string codigo, std::vector<Codigo> &codes);
        std::vector<Codigo> codificar(No *raiz, std::vector<Codigo> &codes);
        std::string decodificar(No *raiz, std::string texto_codificado, bool tipo_decodificacao);
};

#endif