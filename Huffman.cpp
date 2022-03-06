#include "Huffman.h"

No::No(string conteudo, No *esq, No *dir){
    this->conteudo = conteudo;
    this->esq = esq;
    this->dir = dir;
}

No::~No(){

}

Arvore::Arvore(No *raiz){
    this->raiz = raiz;
}

Arvore::~Arvore(){

}

Simbolo::Simbolo(){
    this->nAparicoes = 0;
    this->simbolo = "";
}

Simbolo::~Simbolo(){

}

string formatarString(string conteudoArq){
    int i;
    int j = 0;
    string novaString;
    for(i = 0 ; i < conteudoArq.length() ; i++){
        if((conteudoArq[i] != '\n') && (conteudoArq[i] != ' ') && (conteudoArq[i] != '\t') && (conteudoArq[i] != '\r')){ 
            novaString.insert(j, conteudoArq, i, 1);
            j++;
        }
    }
    return novaString;
}


void Huffman::contarAparicoes(string conteudoArq, Simbolo simbolos[256]){
    int i;
    //Contagem por caractere
    if(this->tipoCodificacao == false){
        string conteudoFormatado = formatarString(conteudoArq);
        for(i = 0 ; i < conteudoFormatado.length() ; i++){
            int pos;
            pos = 256-(256-conteudoFormatado[i]);
            simbolos[pos].nAparicoes++;
        }

    }
}

int main(){
    string teste = "Ola meu nome e larissa \n Hoje e domingo \t oioioio \r feee";
    Huffman novo;
    Simbolo simbolos[256];
    novo.contarAparicoes(teste, simbolos);
    int i = 0;
    while(i <= 256){
        if(simbolos[i].nAparicoes != 0){
            cout<<(char)i<<" "<<simbolos[i].nAparicoes<<endl;
        }
        i++;
    }
}
