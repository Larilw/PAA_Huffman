#include "Huffman.h"

No::No(Simbolo conteudo, No *esq, No *dir){
    this->conteudo.nAparicoes = conteudo.nAparicoes;
    this->conteudo.simbolo = conteudo.simbolo;
    this->esq = esq;
    this->dir = dir;
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

Simbolo::Simbolo(){
    this->nAparicoes = 0;
    this->simbolo = "";
}

Simbolo::~Simbolo(){

}

void removerNulos(Simbolo simbolos[], Simbolo simbNovo[], int tam, int *n){
    int i = 0, j = 0;
    while(i <= tam){
        if(simbolos[i].nAparicoes != 0){
            simbNovo[j] = simbolos[i];
            j++;
        }
        i++;
    }
    *n = j;
}

void ordenarSimbolos(Simbolo simbolos[], int tam){
    int i, j;
    Simbolo x;
    for(i = 1 ; i < tam ; i++){
        x = simbolos[i];
        j = i - 1;
        while(j >= 0 && x.nAparicoes < simbolos[j].nAparicoes){
            simbolos[j+1] = simbolos[j];
            j--;
        }
        simbolos[j+1] = x;
    }
}

void Huffman::contarAparicoes(string conteudoArq, Simbolo simbolos[259]){
    int i;
    //Contagem por caractere
    if(this->tipoCodificacao == false){
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
                else if(conteudoArq[i] == '\r'){
                    simbolos[258].nAparicoes++;
                    simbolos[258].simbolo.assign("cr");
                }
                    /*
                    else if(conteudoArq[i] == '\f'){
                        simbolos[259].nAparicoes++;
                        simbolos[259].simbolo.assign("np");
                    }*/
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

void montaArvore(Simbolo simbolos[], int tam){

}


int main(){
    string teste = "Ola meu nome e larissa \r \rHoje \t e domingo oioioio  eee";
    Huffman novo;
    Simbolo simbolos[259];
    Simbolo simbNovo[259];
    int nSimbolos;
    novo.contarAparicoes(teste, simbolos);
    removerNulos(simbolos, simbNovo, 259, &nSimbolos);
    ordenarSimbolos(simbNovo, 18);
    int i = 0;
    while(i < 18){
        cout<<simbNovo[i].simbolo<<" "<<simbNovo[i].nAparicoes<<endl;
        i++;
    }
}
