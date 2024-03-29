#include "listaPrioridade.h"

/**
 * Construtor da classe ListaPrioridade
 */
ListaPrioridade::ListaPrioridade(No *no){
    this->no = new No(no->conteudo, no->frequencia, no->esq, no->dir);
    this->prox = NULL;
}
/**
 * Destrutor da classe ListaPrioridade
 */
ListaPrioridade::~ListaPrioridade(){
    delete this->no;
}

/**
 * Verifica se a lista de prioridade e vazia
 */
bool ListaPrioridade::ehVazia(){
    return this->no->frequencia == -1;
}

/**
 * Obtem o tamanho da lista de prioridade
 */
int ListaPrioridade::obterTamanho(){
    if(this->ehVazia()){
        return 0;
    }
    ListaPrioridade *aux;
    int tamanho = 0;
    for(aux = this ; aux != NULL ; aux = aux->prox){
        tamanho++;
    }
    return tamanho;
}

/**
 * Remove o primeiro elemento da lista de prioridade
 */
No *ListaPrioridade::extrairPrimeiro(){
    No *primeiro;
    primeiro = new No();
    ListaPrioridade *aux;
    primeiro->conteudo = this->no->conteudo;
    primeiro->esq = this->no->esq;
    primeiro->dir = this->no->dir;
    primeiro->frequencia = this->no->frequencia;
    if(this->prox != NULL){
        this->no->conteudo = this->prox->no->conteudo;
        this->no->esq = this->prox->no->esq;
        this->no->dir = this->prox->no->dir;
        this->no->frequencia = this->prox->no->frequencia;
        aux = this->prox;
        this->prox = this->prox->prox;
        delete aux;
    }
    else{
        this->no->frequencia = -1;
    }
    return primeiro;
}

/**
 * Insere um novo elemento na lista de prioridade de forma ordenada
 * Entrada: Ponteiro para o no do elemento a ser inserido
 */
void ListaPrioridade::inserirOrdenado(No *no){
    ListaPrioridade *novoNo, *aux, *anterior;
    if(!this->ehVazia()){
        for(aux = this ; aux != NULL ; aux = aux->prox){
            if(aux->no->frequencia > no->frequencia){
                novoNo = new ListaPrioridade(aux->no);
                novoNo->prox = aux->prox;
                aux->no = no;
                aux->prox = novoNo;
                break;
            }
            anterior = aux;
        }
        if(aux == NULL){
            novoNo = new ListaPrioridade(no);
            anterior->prox = novoNo;
        }
    }
    else{
        this->no->conteudo = no->conteudo;
        this->no->frequencia = no->frequencia;
        this->no->esq = no->esq;
        this->no->dir = no->dir;
    }
}

