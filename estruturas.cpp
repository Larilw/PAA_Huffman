#include "estruturas.h"
#include <vector>
#include <algorithm>

No::No(string conteudo, int frequencia, No *esq, No *dir){
    this->conteudo = conteudo;
    this->frequencia = frequencia;
    this->esq = esq;
    this->dir = dir;
}

No::No(){
    this->conteudo = "";
    this->frequencia = -1;
    this->esq = NULL;
    this->dir = NULL;
}

No::~No(){

}

bool No::ehFolha(){
    return this->esq == NULL && this->dir == NULL;
}

Arvore::Arvore(No *raiz){
    this->raiz = raiz;
}

Arvore::~Arvore(){

}

std::string Codigo::getCodigo() const
{
    return this->codigo;
}

std::string Codigo::getConteudo() const
{
    return this->conteudo;
}

// int findCodigo(std::vector<Codigo> codes, std::string conteudo)
// {
//     auto it = std::find_if(codes.begin(), codes.end(), [&conteudo](const Codigo& obj) {return obj.getConteudo() == conteudo;});
//     if (it != codes.end())
//     {
//         return std::distance(codes.begin(), it);
//     }

//     return 0;
// }


