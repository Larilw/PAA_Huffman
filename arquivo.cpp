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
}

Arquivo::~Arquivo()
{
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

void contarPalavras2(string conteudoArq, Simbolo simbolos[]) {
    std::string buf;
    std::stringstream ss(conteudoArq);

    std::vector<std::string> tokens;

    while(std::getline(ss, buf)) {

        string word;
        stringstream iss(buf);
 
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

        int i;
        i = encontrarPalavra(simbolos, "\n");
        if ( i >= 0 ) {
            simbolos[i].simbolo = "\n";
            simbolos[i].nAparicoes++;
        } else {
            int pos = ultimaPosicao(simbolos);
            simbolos[pos].simbolo = "\n";
            simbolos[pos].nAparicoes++;
        }
    }

    // for ( int i = 0; i < 1000; i++ ) {
    //     cout << "simbolo: " << simbolos[i].simbolo << endl;
    // }
}

void Arquivo::contarPalavras(string conteudoArq, Simbolo simbolos[]) {
    string line;
    stringstream ss(conteudoArq);

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

    int tam;
    if ( tipoCodificacao == false ) {
        tam = TAMANHO_ASCII;
    } else {
        tam = TAMANHO_PALAVRAS;
    }

    Simbolo simbolos[tam];

    if ( tipoCodificacao == false ) {
        contarAparicoes(texto, simbolos, tipoCodificacao);

    } else {
        contarPalavras2(texto, simbolos);
    }

    removerNulos(simbolos, nos, TAMANHO_ASCII, tamNos);
    ordenarSimbolos(nos, *tamNos);
}
