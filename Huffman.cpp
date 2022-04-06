#include "Huffman.h"
#include <fstream>
#include <algorithm>
#include <bitset>

/**
*   @param No *no
*   @param ostream &out
*
*   Escreve cada nó em bits no arquivo de saída
**/
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

/**
*   @param No *raiz
*   @param ostream &out
*
*   Escreve a árvore inteira no arquivo de saída
**/
void escreveArvore(No *raiz, ostream &out)
{
    escreveNo_recursiva(raiz, out);
    out << endl << ";;--;;--;;" << endl;
}

/**
*   @param ifstream &file
*   @param ostream No *&no
*
*   Lê cada nó da árvore no arquivo comprimido de entrada
**/
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
        // Verifica se é o final da leitura da árvore 
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

/**
*   @param ifstream &file
*   @return No* raiz da árvore   
*
*   Carrega a árvore do arquivo
**/
No* carregaArvore(ifstream &file)
{
    No *raiz;
    raiz = new No();

    file.seekg(0, file.beg);
    leNo_recursiva(file, raiz);

    return raiz;
}

/**
*   @param const & s
*   @param char delim delimitador
*   @return vector<string>
*
*   Separa uma string pelo delimitador e retorna em um array
**/
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

/**
*   @param vector<Codigo> vetor de códigos
*   @param string conteudo
*   @return integer Index do código encontrado no array
*
*   Procura pelo código no array de códigos
**/
int findCodigo(std::vector<Codigo> codes, std::string conteudo)
{
    // Percorre vetor de códigos procurando pela string conteudo no conteúdo de cada objeto código
    auto it = std::find_if(codes.begin(), codes.end(), [&conteudo](const Codigo& obj) {
        return obj.getConteudo() == conteudo;
    });

    if (it != codes.end())
    {
        // Caso achou, retorna o número de index
        return std::distance(codes.begin(), it);
    }
    
    // Caso não encontrou, retorna -1
    return -1;
}

/**
*   @param ListaPrioridade *lista ponteiro
*   @return No* raiz da árvore gerada
*
*   Gera uma árvore a partir de uma lista de prioridade
**/
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

/**
*   @param No *raiz ponteiro para raiz da árvore
*   @param vector<Codigo> &codes
*   @return vector<Codigo>
*
*   Codifica todos os símbolos e insere em um array de códigos
**/
std::vector<Codigo> Huffman::codificar(No *raiz, std::vector<Codigo> &codes)
{
    codificar_recursiva(raiz, "", codes);

    return codes;
}

/**
*   @param No *raiz ponteiro para raiz da árvore
*   @param vector<Codigo> &codes
*   @return vector<Codigo>
*
*   Codifica todos os símbolos e insere em um array de códigos
**/
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
*   @param No *raiz ponteiro para raiz da árvore
*   @param string texto_codificado
*   @param bool tipo_decodificacao caso false é a decoficação por caractere, caso true é por palavras
*   @return string texto_decodificado
*
*   Recebe o texto codificado e retorna uma string com o texto decodificado, utilizando a árvore com os códigos para decodificação
**/
string Huffman::decodificar(No *raiz, std::string texto_codificado, bool tipo_decodificacao)
{
    std::string texto_decodificado;
    texto_codificado += ";";

    std::string aux = texto_codificado;
    No *noAux = raiz;

    std::string::size_type i = 0;

    // Percorre todo o texto codificado
    while ( i < aux.size() ) {
        if ( noAux->ehFolha() ) {
            texto_decodificado += noAux->conteudo;
          
            noAux = raiz;

            if ( tipo_decodificacao == true && texto_decodificado.back() != '\n') {
                texto_decodificado += " ";
            }

        } else {
            std::string s;
            s = aux[i];
            // o caracter, noAux recebe filho da direita
            if ( s == "1" ) {
                noAux = noAux->dir;

            } else {
            // Caso 0, recebe filho da esquerda
                noAux = noAux->esq;
            }

            i++;
        }
    }

    return texto_decodificado;
}

/**
*   @param vector<Codigo> codes Vetor de códigos por símbolo
*   @param ofstream &out Ponteiro para o arquivo de saída
*   @param string str String do texto do arquivo original, string que será codificada
*   @param bool tipoCodificacao Tipo de codificação, caso true por palavra, caso false por caractere
*
*   Recebe o texto codificado e retorna uma string com o texto decodificado, utilizando a árvore com os códigos para decodificação
**/
void escreverCodificacao(std::vector<Codigo> codes, ofstream &out, string str, bool tipoCodificacao)
{
    int i;

    // Move o ponteiro para o final do arquivo
    out.seekp(0, ios::end);
    
    std::string texto_codificado;

    // Codificação por caractere
    if ( tipoCodificacao == false ) {
        for (int i=0; i < str.length(); i++) {
            string s(1, str[i]);
            int index = findCodigo(codes, s);
            if ( index != -1 ) {
                // Itera na string texto_codificado o código de codificação do símbolo
                texto_codificado += codes[index].getCodigo();
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
                    texto_codificado += codes[index].getCodigo();
                }
            }

            int index = findCodigo(codes, "\n");
            if ( index != -1 ) {
                texto_codificado += codes[index].getCodigo();
            }
        }
    }

    int j = 0;
    std::string bits;

    // Escreve bit por bit no arquivo de saída da codificação
    for ( int i=0; i < texto_codificado.length(); i++) {

        if ( i % 8 == 0 && i != 0 ) {
            std::bitset<8> byte(bits);
            unsigned char n = byte.to_ulong();
            out.write(reinterpret_cast<const char*>(&n), sizeof(n));
            bits = "";

        } else if ( i == texto_codificado.length() -1 ) {
            out << "FOC";
            for (int j = 0; j < bits.length(); j++) {
                out << bits[j];
            }
        }

        bits += texto_codificado[i];
    }

    out << "EOC";
}

/**
*   @param vector<Codigo> codes Vetor de códigos por símbolo
*
*   Printa código de todos os símbolos registrados no vetor de códigos
**/
void printCodigos(std::vector<Codigo> codes)
{
    for (auto it = begin (codes); it != end (codes); ++it) {
        cout << "Caractere: " << it->getConteudo() << " ";
        cout << "Código: " << it->getCodigo() << endl;
    }
}

/**
*   @param No *raiz
*
*   Printa a árvore
**/
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

/**
*   @param ifstream &input arquivo original
*   @return string String que armazena todo o conteúdo do arquivo
*
*   Lê conteudo contido no árquivo original
**/
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

/**
*   @param ifstream &file Endereço do arquivo de entrada da compressão
*   @return bool true se for o final do texto comprimido
*
*   Verifica se é o final da string de compressão no arquivo
**/
bool is_OFC(ifstream &file)
{
    unsigned char n;
    file.read( reinterpret_cast<char*>(&n), sizeof(n) );
    if ( n == 'O' ) {
        file.read( reinterpret_cast<char*>(&n), sizeof(n) );
        if ( n == 'C' ) {
            return true;
        }
    }

    file.seekg(-1, std::ios::cur);
    return false;
}

/**
*   @param ifstream &file Endereço do arquivo de entrada da compressão
*   @return string Conteúdo do final da string de compressão
*
*   Obtém e retorna o final da string de compressão no arquivo
**/
string getOFC(ifstream &file)
{
    std::string str = "";
    unsigned char n;
    while (!file.eof()) {
        file.read( reinterpret_cast<char*>(&n), sizeof(n) );
        if ( n == 'E' ) {
            if ( is_OFC(file) ) {
                break;
            }
        }
        str += n;
    }

    return str;
}

/**
*   @param ifstream &file Endereço do arquivo de entrada da compressão
*   @return string Conteúdo codificado
*
*   Lê o arquivo codificado e retorna todo o conteúdo codificado em uma string
**/
string leCodificacao(ifstream &file)
{
    string tp = "";
    string content;

    // Skiping to encoded content
    while (tp != ";;--;;--;;") {
        getline(file, tp);
    }

    while (!file.eof()) {
        std::bitset<8> byte;
        unsigned char n;
        file.read( reinterpret_cast<char*>(&n), sizeof(n) );
        byte = n;

        if ( n == 'F' ) {
            if ( is_OFC(file) ) {
                content += getOFC(file);
                break;
            }
        }

        if ( n == 'E' ) {
            if ( is_OFC(file) ) {
                break;
            }
        }

        content += byte.to_string();
    }

    return content;
}

/**
*   @param bool tipo_algoritmo Caso true utiliza o algoritmo por palavra, caso false utiliza por caractere
*
*   Função que realiza a compressão, chamada do menu
**/
void menu_compressao(bool tipo_algoritmo = false)
{
    ifstream original_file;
    std::string path_original = path_arquivo;
    std::string path_compactado = path_arquivo;
    path_arquivo += ".txt";
    path_compactado += "-compactado.bin";
    original_file.open(path_arquivo);

    cout << "Compactacao iniciada" << endl;

    std::string texto;
    texto = leConteudo(original_file);
    // Carregar texto do arquivo
    int tam;
    if ( tipo_algoritmo == false ) {
        tam = TAMANHO_ASCII;
    } else {
        tam = TAMANHO_PALAVRAS;
    }
    // Gera a árvore binária a partir da string carregada
    No nos[tam];
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
    ofstream file(path_compactado, ios::out | ios::binary);

    escreveArvore(result, file); // Salvar a árvore no arquivo codificado
    escreverCodificacao(codes, file, texto, tipo_algoritmo); // Escreve o texto codificado no arquivo

    file.close();
    if (!file.good()) {
        // cout << "deu ruim!" << endl;
    }

    cout << "Arquivo compactado com sucesso." << endl;
}

/**
*   @param bool tipo_algoritmo Caso true utiliza o algoritmo por palavra, caso false utiliza por caractere
*
*   Função que realiza a descompressão, chamada do menu
**/
void menu_compressao(std::string path_arquivo, bool tipo_algoritmo)
{
    cout << "Descompactacao iniciada" << endl;

    std::string path_compactado;
    std::string path_descompactado;
    path_compactado = path_arquivo;
    path_compactado += ".bin";

    ifstream compressed_file(path_compactado, ios::out | ios::binary);

    Huffman huff;

    No *arvore;
    arvore = new No();

    arvore = carregaArvore(compressed_file);
    std::string texto_codificado = leCodificacao(compressed_file);

    compressed_file.close();

    path_descompactado = path_arquivo;
    path_descompactado += "-descompactado.txt";

    ofstream outfile(path_descompactado, ios::out | ios::binary);

    outfile << huff.decodificar(arvore, texto_codificado, tipo_algoritmo);

    outfile.close();

    cout << "Arquivo descompactado com sucesso" << endl;
}