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
            if((conteudoArq[i] == '\n') || (conteudoArq[i] == '\t') || (conteudoArq[i] == '\r') || (conteudoArq[i] == '\f')){
                if(conteudoArq[i] == '\n'){
                    simbolos[256].nAparicoes++;
                    simbolos[256].simbolo.assign("nl");
                }
                else if(conteudoArq[i] == '\t'){
                    simbolos[257].nAparicoes++;
                    simbolos[257].simbolo.assign("ht");
                }
                //problema \r e \f
                else if(conteudoArq[i] == '\r'){
                    simbolos[258].nAparicoes++;
                    simbolos[258].simbolo.assign("cr");
                }
            }
            else{
                    int pos;
                    pos = 256-(256-conteudoArq[i]);
                    simbolos[pos].simbolo = char(pos);
                    simbolos[pos].nAparicoes++;
            }
        }

    }

}

void Arquivo::gerarNos(No nos[], int *tamNos, bool tipoCodificacao){
    Simbolo simbolos[TAMANHO_ASCII];
    string arquivo;
    arquivo = "abacaxi nao ";
    contarAparicoes(arquivo, simbolos, tipoCodificacao);
    removerNulos(simbolos, nos, TAMANHO_ASCII, tamNos);
    ordenarSimbolos(nos, *tamNos);
}
