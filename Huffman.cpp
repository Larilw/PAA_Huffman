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

// void escreveNo(No *raiz, ostream &out)
// {
//     if (raiz->ehFolha()) {
//         // escreve "#"
//         if ( !raiz->conteudo.empty() ) {
//             out << raiz->conteudo << ";";
//             out << raiz->frequencia << " ";

//         } else {
//             out << "# ";
//         }

//     } else {
//         // escreve estrutura
//         // cout << "conteúdo: " << raiz->conteudo << endl;
//         out << raiz->conteudo << ";";
//         out << raiz->frequencia << " ";
//         escreveNo(raiz->esq, out);
//         escreveNo(raiz->dir, out);
//     }
// }

void escreveNo_recursiva(No *no, ostream &out)
{
    int size = no->conteudo.length();

    out.write((char *) &no->frequencia, sizeof(int));
    out.write(reinterpret_cast<char *>(&size), sizeof(int));
    out.write(no->conteudo.c_str(), size);
    // out.write((char *) &no->conteudo, sizeof(string));
    if ( no->conteudo.empty() ) {
        escreveNo_recursiva(no->esq, out);
        escreveNo_recursiva(no->dir, out);
    }
}

void escreveArvore(No *raiz, ostream &out)
{
    escreveNo_recursiva(raiz, out);
}

void leNo_recursiva(ifstream &file, No *&no)
{
    if (file.eof()) {
        return;
    }

    No *novoNo;
    novoNo = new No();

    int size;

    file.read((char*) &novoNo->frequencia, sizeof(int));

    char *buf;
    file.read(reinterpret_cast<char *>(&size), sizeof(int));
    buf = new char[size];
	file.read(buf, size);
	string str = "";
	str.append(buf, size);

    novoNo->conteudo = str;
    no = novoNo;
    
    if ( novoNo->conteudo.empty() ) {
        leNo_recursiva(file, novoNo->esq);
        leNo_recursiva(file, novoNo->dir);
    }
}

No* carregaArvore(ifstream &file)
{
    No *raiz;
    raiz = new No();

    leNo_recursiva(file, raiz);

    return raiz;
}

std::vector<std::string> explode(std::string const & s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
    {
        result.push_back(std::move(token));
    }

    return result;
}

int findDelimiter(string str, char del)
{
    int i = 0;
    for (char c : str) {
        if ( c == del ) {
            return i;
        }
        i++;
    }

    return -1;
}

// void carregaArvore_recursiva(No *arvore, vector<No*>::iterator current, vector<No*>::iterator end)
// {
//     No* novoNo;
//     novoNo = new No();
//     novoNo->conteudo = (*current)->conteudo;
//     novoNo->frequencia = (*current)->frequencia;
//     // cout << "conteúdo: " << (*current)->frequencia << endl;

//     if ( current == end ) {
//         return;
//     }
//     current++;

//     if ( novoNo->conteudo.empty() ) {
//         carregaArvore_recursiva(novoNo->esq, current, end);
//         // *current++;
//         carregaArvore_recursiva(novoNo->dir, current, end);
//     }
//     arvore = novoNo;

//     return;

//     cout << (*current)->frequencia << endl;

//     // carregaArvore_recursiva(arvore, current, end);
// }

// No* leNo()
// {
//     No *raiz, *noAux;
//     string str_arvore = ";6 ;2 a;1 s;1 ;4 e;2 t;2 ";
//     std::vector<std::string> nos;
//     std::vector<No*> nos_extraidos;

//     nos = explode(str_arvore, ' ');
//     for (std::string str : nos) {
//         // cout << "index: " << str << endl;
//         std::string conteudo = "";
//         std::string frequencia = "";
//         int del = findDelimiter(str, ';');
//         if ( del > 0 ) {
//             int i;
//             for (i = 0; i < del; i++ ) {
//                 conteudo += str[i];
//             }
//             for (i+=1; i < str.length(); i++ ) {
//                 frequencia += str[i];
//             }
//         } else {
//             if ( del != -1 ) {
//                 str.erase(remove(str.begin(), str.end(), ';'), str.end());
//                 // cout << "Frequência: " << str << endl;
//                 frequencia = str;
//             }
//         }

//         No *novoNo;
//         novoNo = new No();

//         novoNo->conteudo = conteudo;
//         novoNo->frequencia = std::stoi(frequencia);

//         nos_extraidos.push_back(novoNo);

//         // cout << "Conteúdo: " << conteudo;
//         // cout << " Frequência: " << frequencia << endl;
//     }

//     No *arvore;
//     carregaArvore_recursiva(arvore, nos_extraidos.begin(), nos_extraidos.end());
//     return arvore;
// }

/**
*   Encontra o código no array de códigos a partir do conteúdo
*
**/
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

string Huffman::decodificar(No *raiz)
{
    std::string texto_decodificado;
    std::string texto_codificado = "111001111000";
    texto_codificado += ";";

    std::string aux = texto_codificado;
    No *noAux = raiz;

    std::string::size_type i = 0;

    while ( i < aux.size() ) {
        if ( noAux->ehFolha() ) {
            texto_decodificado += noAux->conteudo;
            noAux = raiz;

        } else {
            std::string s;
            s = aux[i];
            // o caracter, noAux recebe filho da direita
            if ( s == "1" ) {
                noAux = noAux->dir;
                // } else if ( s == "0" ) {

            } else {
            // Caso 0, recebe filho da esquerda
                noAux = noAux->esq;
            }

            i++;
        }
    }

    return texto_decodificado;
}

void escreverCodificacao(std::vector<Codigo> codes, ofstream &out)
{
    int i;
    std::string str = "um texto um pouco maior para ver se a avore gerada eh a mesma";

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
        cout << "Caractere: " << it->getConteudo() << " ";
        cout << "Código: " << it->getCodigo() << endl;
    }
}

void printArvore2(No *raiz)
{
    if (raiz == NULL) {
        return;
    }
    printArvore2(raiz->esq);
    cout << "Conteúdo: " << raiz->conteudo << endl;
    cout << "Frequência: " << raiz->frequencia << endl << endl;
    printArvore2(raiz->dir);
}

void menu_compressao()
{
    // Receber o path do arquivo a comprimir
    cout << "Insira o path do arquivo a ser comprimido." << endl;
    std::string path;
    ifstream original_file;
    cin >> path;
    original_file.open(path);
    // Abrir o arquivo
    while (!original_file) {
        cout << "Arquivo não encontrado, insira o nome novamente." << endl;
        cin >> path;
        original_file.open(path);
    }

    std::string texto;
    // Carregar texto do arquivo
    texto = "um texto um pouco maior para ver se a avore gerada eh a mesma";

    // Gerar a árvore binária a partir da string carregada
    No nos[TAMANHO_ASCII];
    int tamanho;
    Arquivo arq;
    Huffman arv;
    No *result;
    arq.gerarNos(nos, &tamanho, false, texto);
    ListaPrioridade *lista;
    if (tamanho >= 1) {
        lista = new ListaPrioridade(&nos[0]);
        int i;
        for(i = 1 ; i < tamanho; i++){
            lista->inserirOrdenado(&nos[i]);
        }
        result = arv.gerarArvore(lista);
    }

    // Codificar a partir da árvore binária
    std::vector<Codigo> codes;
    arv.codificar(result, codes);
    // Abrir o arquivo codificado
    ofstream file("comprimido.bin", ios::out | ios::binary);
    // if (!file) {
    //     cout << "Não abriu..." << endl;
    //     return 0;
    // }
    escreveArvore(result, file); // Salvar a árvore no arquivo codificado
    escreverCodificacao(codes, file);
    
    printArvore(result);
    cout << endl;
    // file.close();
    // if (!file.good()) {
    //     cout << "deu ruim!" << endl;
    // }
    
    // escreverCodificacao(codes, arq.arq); // Salvar o código de codificação no arquivo codificado
}

int main() {
    menu_compressao();
    return 0;
    ofstream out;
    out.open("test.txt");

    No nos[TAMANHO_ASCII];
    int tamanho;
    Arquivo arq;
    Huffman arv;
    No *result;
    arq.gerarNos(nos, &tamanho, false, "um texto um pouco maior para ver se a avore gerada eh a mesma");
    ListaPrioridade *lista;
    if(tamanho >= 1){
        lista = new ListaPrioridade(&nos[0]);
        int i;
        for(i = 1 ; i < tamanho; i++){
            lista->inserirOrdenado(&nos[i]);
        }
        result = arv.gerarArvore(lista);

        // escreveNo(result, arq.arq);

        // Codificação
        std::vector<Codigo> codes;
        arv.codificar(result, codes);
        // Escreve codificação no arquivo
        escreverCodificacao(codes, arq.arq);
        // arq.escreverCodificacao(codes);

        // Decodificação
        cout << "Resultado decodificado: " << arv.decodificar(result) << endl;

        // printCodigos(codes);
        printArvore(result);
        // printArvore(teste);
        // printArvore2(result);

        // file.open("file.bin");

        ofstream file("file.dat", ios::out | ios::binary);
        if (!file) {
            cout << "Não abriu..." << endl;
            return -1;
        }
        escreveArvore(result, file);
        file.close();
        if (!file.good()) {
            cout << "deu ruim!" << endl;
        }

        ifstream rfile("file.dat", ios::out | ios::binary);
        if (!rfile) {
            cout << "Não abriu..." << endl;
            return -1;
        }
        No *arvoreCarregada;
        arvoreCarregada = new No();
        arvoreCarregada = carregaArvore(rfile);
        rfile.close();
        if ( !rfile.good() ) {
            cout << "deu ruim!" << endl;
        }
        printArvore(arvoreCarregada);
    }
}