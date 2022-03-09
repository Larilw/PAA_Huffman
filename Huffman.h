#include <string>
#include <iostream>
using namespace std;

class Simbolo{
    public:
        string simbolo;
        int nAparicoes;

        Simbolo();
        ~Simbolo();
};

class No{
    public:
        Simbolo conteudo;
        No *esq;
        No *dir;

        No(Simbolo conteudo, No *esq, No *dir);
        ~No();
        bool ehFolha();
};

class Arvore{
    private:
        No *raiz;

    public:
        Arvore(No *raiz);
        ~Arvore();
};


class Huffman{
    public:

        bool tipoCodificacao;

        void contarAparicoes(string conteudoArq, Simbolo simbolos[256]);
        
};