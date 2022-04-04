#include "Huffman.h"
#include <fstream>
#include <algorithm>
#include <bitset>

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
    out << endl << ";;--;;--;;" << endl;
}

void leNo_recursiva(ifstream &file, No *&no)
{
    if (file.eof()) {
        return;
    }

    char c;
    int qtd = -1;
    file.read((char*) &c, sizeof(char));
    if ( c == '\n'  ) {
        qtd--;
        file.read((char*) &c, sizeof(char));
        if ( c == ';' ) {
            file.seekg(-2, std::ios::cur);
            return;
        }
    }

    file.seekg(qtd, std::ios::cur);

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

    file.seekg(0, file.beg);
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

string Huffman::decodificar(No *raiz, std::string texto_codificado, bool tipo_decodificacao)
{
    std::string texto_decodificado;
    texto_codificado += ";";

    std::string aux = texto_codificado;
    No *noAux = raiz;

    std::string::size_type i = 0;

    while ( i < aux.size() ) {
        if ( noAux->ehFolha() ) {
            texto_decodificado += noAux->conteudo;
            noAux = raiz;

            if ( tipo_decodificacao == true ) {
                texto_decodificado += " ";
            }

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

uint8_t ucharToBitArray(char bits[8], uint8_t c)
{
   for(uint8_t i=0; i<8; i++)
   {
     if(c & (1<<i))
     {
       bits[7-i] = '1';
     }
     else
     {
       bits[7-i] = '0';
     }
   }

   return c;
}

void escreverCodificacao(std::vector<Codigo> codes, ofstream &out, string str, bool tipoCodificacao)
{
    int i;

    // Move para o final do arquivo
    out.seekp(0, ios::end);
    
    // Escreve \n
    // out << endl;

    std::string texto_codificado;

    // Codificação por caractere
    if ( tipoCodificacao == false ) {
        for (int i=0; i < str.length(); i++) {
            string s(1, str[i]);
            int index = findCodigo(codes, s);
            if ( index != -1 ) {
                // out << codes[index].getCodigo();
                texto_codificado += codes[index].getCodigo();
                // cout << "CÓDIGO: " << codigo << endl;
                // cout << "ENTROUUU!!!! " << endl;
                // for (int j=0; j < codigo.length(); j++) {
                //     char bin = codigo[j];
                //     // Write in binary
                //     cout << "CÓDIGO: " << bin << endl;
                //     out.write((char *) &bin, 1);
                // }
            }
        }
    // Codificação por palavra
    } else {
        string word;
 
        stringstream iss(str);
 
        while (iss >> word) {
            int index = findCodigo(codes, word);
            if ( index != -1 ) {
                // cout << "código:" << codes[index].getCodigo() << endl;
                out << codes[index].getCodigo();
            }
        }
    }

    int j = 0;
    std::string bits;
    for ( int i=0; i < texto_codificado.length(); i++) {
        // unsigned char byte;
        // char bits[8];
        // bits[j] = texto_codificado[i];
        if ( i % 8 == 0 && i != 0 ) {
            // byte = ucharToBitArray(bits, byte);
            // bits[0] = 0;
            // cout << "byte: " << byte << endl;
            // j=0;
            cout << "bits: " << bits << endl;
            std::bitset<8> byte(bits);
            unsigned char n = byte.to_ulong();
            // cout << "texto codificado:" << texto_codificado << endl;
            // cout << "alo:" << (int) n << endl;
            out.write(reinterpret_cast<const char*>(&n), sizeof(n));
            bits = "";
        }
        bits += texto_codificado[i];
    }
}

void escreverCodificacao2(std::vector<Codigo> codes, ofstream &out, string str, bool tipoCodificacao)
{
    int i;

    // Move para o final do arquivo
    out.seekp(0, ios::end);
    
    // Escreve \n
    // out << endl;

    // Codificação por caractere
    if ( tipoCodificacao == false ) {
        for (int i=0; i < str.length(); i++) {
            string s(1, str[i]);
            int index = findCodigo(codes, s);
            if ( index != -1 ) {
                out << codes[index].getCodigo();
            }
        }
    // Codificação por palavra
    } else {

        std::string line;
        std::stringstream ss(str);

        while(std::getline(ss, line)) {
            string word;
            stringstream iss(line);
    
            while (iss >> word) {
                int index = findCodigo(codes, word);
                if ( index != -1 ) {
                    // cout << "código:" << codes[index].getCodigo() << endl;
                    out << codes[index].getCodigo();
                }
            }

            int index = findCodigo(codes, "\n");
            if ( index != -1 ) {
                out << codes[index].getCodigo();
            }
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

string leConteudo(ifstream &input)
{
    string tp;
    string content;
    while(getline(input, tp)) {
        content += tp;
        content += '\n';
    }

    return content;
}

string leCodificacao(ifstream &file)
{
    string tp = "";
    string content;
    // Skiping to encoded content
    while (tp != ";;--;;--;;") {
        getline(file, tp);
    }
    // Reading encoded content
    // while(getline(file, tp)) {
    //     content += tp;
    // }
    while (!file.eof()) {
        std::bitset<8> byte;
        unsigned char n;
        file.read( reinterpret_cast<char*>(&n), sizeof(n) );
        cout << "n: " << n << endl;
        byte = n;

        content += byte.to_string();
    }

    // cout << "Content:" << content << endl;

    return content;
}

void menu_compressao(bool tipo_algoritmo = false)
{
    // Recebe o path do arquivo a comprimir
    cout << "Insira o path do arquivo a ser comprimido." << endl;
    std::string path;
    ifstream original_file;
    cin >> path;
    original_file.open(path);
    // Abre o arquivo
    while (!original_file) {
        cout << "Arquivo não encontrado, insira o nome novamente." << endl;
        cin >> path;
        original_file.open(path);
    }

    std::string texto;
    texto = leConteudo(original_file);
    // Carregar texto do arquivo

    // Gera a árvore binária a partir da string carregada
    No nos[TAMANHO_ASCII];
    int tamanho;
    Arquivo arq;
    Huffman arv;
    No *result;
    arq.gerarNos(nos, &tamanho, tipo_algoritmo, texto);
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
    ofstream file("compactado.bin", ios::out | ios::binary);
 
    escreveArvore(result, file); // Salvar a árvore no arquivo codificado
    escreverCodificacao(codes, file, texto, tipo_algoritmo); // Escreve o texto codificado no arquivo
    printArvore(result);

    file.close();
    if (!file.good()) {
        cout << "deu ruim!" << endl;
    }
}

void menu_descompressao(bool tipo_algoritmo = false)
{
    Huffman huff;
    ifstream ifile("compactado.bin", ios::out | ios::binary);
    if ( !ifile.is_open() ) {
        cout << "Arquivo não encontrado." << endl;
        return;
    }

    No *arvore;
    arvore = new No();

    arvore = carregaArvore(ifile);
    std::string texto_codificado = leCodificacao(ifile);

    ifile.close();
    if (!ifile.good()) {
        cout << "deu ruim!" << endl;
    }

    ofstream outfile("descompactado.txt", ios::out | ios::binary);

    outfile << huff.decodificar(arvore, texto_codificado, tipo_algoritmo);
}

int main() {
    menu_compressao(false);
    menu_descompressao(false);
    return 0;
}