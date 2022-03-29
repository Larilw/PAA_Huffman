#include "Huffman.h"
#include <fstream>
#include <algorithm>

bool levelOrder(No *no, int level){
    if(no == NULL){
        return false;
    }
    if(level == 1){
        if(no->conteudo.empty()){
            cout<<no->frequencia<<" ";
        }
        else{
            cout<<no->conteudo<<" ";
        }
        return true;
    }
    bool left = levelOrder(no->esq, level-1);
    bool right = levelOrder(no->dir, level-1);
    return left || right;
}

void printArvore(No *no){
    int level = 1;
    while(levelOrder(no, level)){
        level++;
        cout<<endl;
    }
}

void imprimir(No *no){
    if(no->esq != NULL){
        imprimir(no->esq);
    }
    if(no->dir != NULL){
        imprimir(no->dir);
    }
    if(no->conteudo.empty()){
        cout<<no->frequencia<<" ";
    }
    else{
        cout<<no->conteudo<<" ";
    }
}

void escreveNo(No *raiz, ostream &out)
{
    if (raiz->ehFolha()) {
        // escreve "#"
        out << "# ";
    } else {
        // escreve estrutura
        out << raiz->conteudo << ";";
        out << raiz->frequencia << " ";
        escreveNo(raiz->esq, out);
        escreveNo(raiz->dir, out);
    }
}

int findCodigo(std::vector<Codigo> codes, std::string conteudo)
{
    auto it = std::find_if(codes.begin(), codes.end(), [&conteudo](const Codigo& obj) {
        return obj.getConteudo() == conteudo;
    });

    if (it != codes.end())
    {
        return std::distance(codes.begin(), it);
    }
    
    return -1;
}

/**
*
*
**/
void escreveArvore(Arvore *tree, ostream &out)
{
    escreveNo(tree->raiz, out);
}

No *Huffman::gerarArvore(ListaPrioridade *lista){
    for(; lista->obterTamanho() > 1 ;){
        No *novoNo;
        novoNo = new No();
        novoNo->esq = lista->extrairPrimeiro();
        novoNo->dir = lista->extrairPrimeiro();
        novoNo->frequencia = novoNo->esq->frequencia + novoNo->dir->frequencia;
        lista->inserirOrdenado(novoNo);
    }
    return lista->extrairPrimeiro();
}

std::vector<Codigo> Huffman::codificar(No *raiz, std::vector<Codigo> &codes)
{
    // std::vector<Codigo> codes;
    codificar_recursiva(raiz, "", codes);

    return codes;
}

void Huffman::codificar_recursiva(No *raiz, std::string codigo, std::vector<Codigo> &codes)
{
    // Se o nó for folha, pega o conteúdo do nó e seta no array com seu código de identificação
    if ( raiz->ehFolha() ) {
        Codigo *code = new Codigo;
        code->codigo = codigo;
        code->conteudo = raiz->conteudo;
        codes.push_back(*code);

        return;

    } else {
    // Chama função para esquerda, adicionando um 0 em uma string
        codificar_recursiva(raiz->esq, codigo + "0", codes);
    // Chama função para direita
        codificar_recursiva(raiz->dir, codigo + "1", codes);
    }
}

/**
*
*   Function to call from menu
*
**/
void codificar_menu(Huffman arv, No* raiz, std::vector<Codigo> &codes)
{
    // Codifica a lista e guarda todos os códigos no array codes
    arv.codificar(raiz, codes);

    // Escreve o texto codificado no corpo do arquivo

}

void escreverCodificacao(std::vector<Codigo> codes, ofstream &out)
{
    int i;
    std::string str = "abacaxi nao";

    // Move para o final do arquivo
    out.seekp(0, ios::end);
    
    // Escreve \n
    out << endl;

    for (int i=0; i < str.length(); i++) {
        string s(1, str[i]);
        int index = findCodigo(codes, s);
        if ( index != -1 ) {
            out << codes[index].getCodigo();
        }
    }
}

void printCodigos(std::vector<Codigo> codes)
{
    for (auto it = begin (codes); it != end (codes); ++it) {
        cout << "Caractere: " << it->getConteudo();
        cout << "Código: " << it->getCodigo() << endl;
    }
}

int main() {
    ofstream out;
    out.open("test.txt");

    No nos[TAMANHO_ASCII];
    int tamanho;
    Arquivo arq;
    Huffman arv;
    No *result;
    arq.gerarNos(nos, &tamanho, false);
    ListaPrioridade *lista;
    if(tamanho >= 1){
        lista = new ListaPrioridade(&nos[0]);
        int i;
        for(i = 1 ; i < tamanho; i++){
            lista->inserirOrdenado(&nos[i]);
        }
        result = arv.gerarArvore(lista);
        // printArvore(result);

        escreveNo(result, arq.arq);

        // Codificação
        std::vector<Codigo> codes;
        arv.codificar(result, codes);
        // Escreve codificação no arquivo
        escreverCodificacao(codes, arq.arq);
        // arq.escreverCodificacao(codes);

        // Decodificação
        

        printCodigos(codes);
    }
}