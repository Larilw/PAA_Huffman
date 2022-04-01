#include "arquivo.h"

// #include "Huffman.cpp"

int encontrarPalavra(Simbolo simbolos[], string palavra)
{
    int i;
    for (int i = 0; i < TAMANHO_PALAVRAS ; i++) {
        if (simbolos[i].simbolo == palavra) {
            return i;
        }
    }

    return -1;
}

int ultimaPosicao(Simbolo simbolos[])
{
    int i;
    while (simbolos[i].simbolo.length() > 0) {
        i++;
    }

    return i;
}

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

Arquivo::Arquivo()
{
    this->arq.open("aloha.txt");
}

Arquivo::~Arquivo()
{
}

void Arquivo::escreverCodificacao(std::vector<Codigo> codes)
{
    // int i;
    // string arquivo = "abacaxi nao";

    // for (int i=0; i < arquivo.length(); i++) {
        // this->arq << findCodigo(codes, arquivo[i]);
    // }

    // for (auto it = begin (codes); it != end (codes); ++it) {
        // cout << it->getCodigo() << endl;
        // i = findCodigo(codes, it->getConteudo());
    // }
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

void Arquivo::contarPalavras(string conteudoArq, Simbolo simbolos[]) {
    string word;
 
    stringstream iss(conteudoArq);
 
    while (iss >> word) {
        int i;
        i = encontrarPalavra(simbolos, word);
        if ( i >= 0 ) {
            simbolos[i].simbolo = word;
            simbolos[i].nAparicoes++;
        } else {
            int pos = ultimaPosicao(simbolos);
            simbolos[pos].simbolo = word;
            simbolos[pos].nAparicoes++;
        }
    }
}

void Arquivo::gerarNos(No nos[], int *tamNos, bool tipoCodificacao, string texto){
    Simbolo simbolos[TAMANHO_ASCII];
    // string arquivo;
    // arquivo = "um texto um pouco maior para ver se a avore gerada eh a mesma";
    contarAparicoes(texto, simbolos, tipoCodificacao);
    removerNulos(simbolos, nos, TAMANHO_ASCII, tamNos);
    ordenarSimbolos(nos, *tamNos);
}
