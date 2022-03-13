#include "listaPrioridade.h"

ListaPrioridade::ListaPrioridade(No no){
    this->no = no;
    this->prox = NULL;
}

ListaPrioridade::~ListaPrioridade(){
}

No ListaPrioridade::*obterProx(){

}

void ListaPrioridade::inserirOrdenado(No no){
    ListaPrioridade *novoNo, *aux, *anterior;
    for(aux = this ; aux != NULL ; aux = aux->prox){
        if(aux->no.frequencia > no.frequencia){
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

int main(){
    No nos[TAMANHO_ASCII];
    int tamanho;
    Arquivo arq;
    arq.gerarNos(nos, &tamanho, false);
    ListaPrioridade *lista;
    lista = new ListaPrioridade(nos[0]);
    int i;
    for(i = 1; i < tamanho; i++){
        lista->inserirOrdenado(nos[i]);
    }
    ListaPrioridade *aux;
    for( aux = lista; aux != NULL ; aux = aux->prox){
        cout<<"LISTA:\nCONTEUDO: "<<aux->no.conteudo<<"\nFREQUENCIA: "<<aux->no.frequencia<<"\n\n";
    }
}