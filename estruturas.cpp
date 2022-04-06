#include "estruturas.h"
#include <vector>
#include <algorithm>


/**
 * Construtor da classe No
 * Entrada: string com conteudo do no, frequencia de aparicoes do conteudo e ponteiros para esquerda e direita do no
 */
No::No(string conteudo, int frequencia, No *esq, No *dir){
    this->conteudo = conteudo;
    this->frequencia = frequencia;
    this->esq = esq;
    this->dir = dir;
}

/**
 * Construtor da classe No
 */
No::No(){
    this->conteudo = "";
    this->frequencia = -1;
    this->esq = NULL;
    this->dir = NULL;
}

/**
 * Destrutor da classe No
 */
No::~No(){

}

/**
 * Verifica se o no e folha
 */
bool No::ehFolha(){
    return this->esq == NULL && this->dir == NULL;
}

/**
 * Construtor da classe Arvore
 * Entrada: Ponteiro para a raiz
 */
Arvore::Arvore(No *raiz){
    this->raiz = raiz;
}

/**
 * Destrutor da classe Arvore
 */
Arvore::~Arvore(){

}

/**
 * Retorna o código registrado
 */
std::string Codigo::getCodigo() const
{
    return this->codigo;
}

/**
 * Retorna o conteudo registrado
 */
std::string Codigo::getConteudo() const
{
    return this->conteudo;
}



