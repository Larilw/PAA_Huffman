#include "estruturas.h"

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


