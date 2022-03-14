#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <iostream>
using namespace std;
#include "listaPrioridade.h"

class Huffman{
    public:
        No *gerarArvore(ListaPrioridade *lista);
};

#endif