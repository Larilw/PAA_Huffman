#include "arquivo.h"

Simbolo::Simbolo(){
    this->nAparicoes = 0;
    this->simbolo = "";
}

Simbolo::~Simbolo(){

}

void removerNulos(Simbolo simbolos[], No nos[], int tam, int *n){
    int i = 0, j = 0;
    while(i < tam){
        if(simbolos[i].nAparicoes != 0){
            nos[j].conteudo = simbolos[i].simbolo;
            nos[j].frequencia = simbolos[i].nAparicoes;
            nos[j].dir = NULL;
            nos[j].esq = NULL;
            j++;
        }
        i++;
    }
    *n = j;
}

void ordenarSimbolos(No nos[], int tam){
    int i, j;
    No x;
    for(i = 1 ; i < tam ; i++){
        x = nos[i];
        j = i - 1;
        while(j >= 0 && x.frequencia < nos[j].frequencia){
            nos[j+1] = nos[j];
            j--;
        }
        nos[j+1] = x;
    }
}

Arquivo::Arquivo(){

}

Arquivo::~Arquivo(){

}

void Arquivo::contarAparicoes(string conteudoArq, Simbolo simbolos[], bool tipoCodificacao){
    int i;
    //Contagem por caractere
    if(tipoCodificacao == false){
        for(i = 0 ; i < conteudoArq.length() ; i++){
            int pos;
            pos = (unsigned char)conteudoArq[i];
            simbolos[pos].simbolo = char(pos);
            simbolos[pos].nAparicoes++;
        }
    }
}

void Arquivo::gerarNos(No nos[], int *tamNos, bool tipoCodificacao){
    Simbolo simbolos[TAMANHO_ASCII];
    string arquivo;
    arquivo = "abacaxi nao";
    contarAparicoes(arquivo, simbolos, tipoCodificacao);
    removerNulos(simbolos, nos, TAMANHO_ASCII, tamNos);
    ordenarSimbolos(nos, *tamNos);
}
