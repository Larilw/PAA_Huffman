#include "arquivo.h"

/**
 * Procura um simbolo no vetor de simbolos dado uma string
 * Entrada: Vetor de simbolos, string palavra
 */
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

/**
 * Retorna a última posição do vetor de Símbolos
 * Entrada: Vetor de simbolos
 */
int ultimaPosicao(Simbolo simbolos[])
{
    int i;
    while (simbolos[i].simbolo.length() > 0) {
        i++;
    }

    return i;
}

/**
 * Construtor da classe Simbolo
 */
Simbolo::Simbolo(){
    this->nAparicoes = 0;
    this->simbolo = "";
}

/**
 * Destrutor da classe Simbolo
 */
Simbolo::~Simbolo(){

}

/**
 * Percorre o vetor de simbolos preenchendo o vetor de nos quando o numero de aparicoes do simbolo nao e nulo
 * Entrada: Vetor de simbolos, vetor de nos, tamanho do vetor de simbolos, ponteiro para o tamanho do vetor de nos
 */
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

/**
 * Ordena o vetor de nos de acordo com o numero de aparicoes de cada caractere, em ordem crescente
 * Entrada: Vetor de nos e tamanho do vetor de nos
 */
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

/**
 * Construtor da classe Arquivo
 */
Arquivo::Arquivo()
{
}

/**
 * Destrutor da classe Arquivo
 */
Arquivo::~Arquivo()
{
}

/**
 * Percorre uma string preenchendo um vetor de simbolos com os caracteres e seu numero de aparicoes na string
 * Entrada: String com o conteudo a ser analisado, vetor de simbolos
 */
void Arquivo::contarAparicoes(string conteudoArq, Simbolo simbolos[]){
    int i;
    for(i = 0 ; i < conteudoArq.length() ; i++){
        int pos;
        pos = (unsigned char)conteudoArq[i];
        simbolos[pos].simbolo = char(pos);
        simbolos[pos].nAparicoes++;
    }
}

/**
 * Percorre uma string preenchendo o vetor de símbolos, contando a frequência de cada símbolo
 * Entrada: String com o conteudo a ser analisado, vetor de simbolos e um ponteiro para guardar a quantidade de símbolos no vetor
 */
void contarPalavras(string conteudoArq, Simbolo simbolos[], int *n) {
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
                (*n)++;
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
            (*n)++;
        }
    }
}

/**
 * Gera todos os nós para montar a árvore binária de codificação
 * Entrada: Vetor de nós, ponteiro para guardar tamanho do vetor de nós, tipo de codificação e string com conteúdo do arquivo original
 */
void Arquivo::gerarNos(No nos[], int *tamNos, bool tipoCodificacao, string texto){

    int tam;
    if ( tipoCodificacao == false ) {
        tam = TAMANHO_ASCII;
    } else {
        tam = TAMANHO_PALAVRAS;
    }

    Simbolo simbolos[tam];
    int n = 0;

    if ( tipoCodificacao == false ) {
        contarAparicoes(texto, simbolos);

    } else {
        contarPalavras(texto, simbolos, &n);
    }

    if ( n == 0 ) {
        n = TAMANHO_ASCII;
    }

    removerNulos(simbolos, nos, n, tamNos);
    ordenarSimbolos(nos, *tamNos);
}
