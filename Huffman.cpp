#include "Huffman.h"
#include <fstream>

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

std::vector<Codigo> Huffman::codificar(No *raiz)
{
    std::vector<Codigo> codes;
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
/*
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
        // cout << "Meu print:" << endl;
        // No *teste;
        // teste = result;
        // for (i=0; i < 3; i++) {
        //     cout << "alo:" << endl;
        //     cout << teste->conteudo << endl;
        //     teste = teste->dir;
        // }
        // printArvore(result);
        arv.codificar(result);
        escreveNo(result, out);
    }
}
*/