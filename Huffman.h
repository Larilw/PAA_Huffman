#include <string>
#include <iostream>
using namespace std;

class No{
    public:
        string conteudo;
        No *esq;
        No *dir;

        No(string conteudo, No *esq, No *dir);
        ~No();
};

class Arvore{
    private:
        No *raiz;

    public:
        Arvore(No *raiz);
        ~Arvore();
};

class Simbolo{
    public:
        string simbolo;
        int nAparicoes;

        Simbolo();
        ~Simbolo();
};

class Huffman{
    public:

        bool tipoCodificacao;

        void contarAparicoes(string conteudoArq, Simbolo simbolos[256]);
        
};