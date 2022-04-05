#include "menu.h"

void lerNomeArquivo(string *path, bool operacao){
    cout<<"Insira o caminho do arquivo sem a extensao" << endl;
    ifstream original_file;
    std::string arq;
    cin >> *path;
    if(operacao == false){
        arq = *path + ".txt";
    }
    else{
        arq = *path + ".bin";
    }
    original_file.open(arq);

    while(!original_file){
        cout<<"Arquivo nao encontrado, insira o caminho novamente."<<endl;
        cin >>*path;
        if(operacao == false){
            arq = *path + ".txt";
        }
        else{
            arq = *path + ".bin";
        }
        original_file.open(arq);
    }
    original_file.close();
}


void imprimirOpcaoSelecionada(int pos, int posImprimir, string mensagem){
    if(pos == posImprimir){
        cout<<"* ";
    }
    cout<<mensagem<<endl;
}

int obterPosicao(){
    int ex;
    while(true){
        ex = getch();
        ex = tolower(ex);
        if(ex == KEY_UP){
            return 1;
        }
        else if(ex == KEY_DOWN){
            return 2;
        }
        else if(ex == KEY_ENTER){
            return 3;
        }
    }
}

void gerarMenuPrincipal(int pos){
    system("cls");
    cout<<"---------------------------------------------------"<<endl;
    cout<<"MENU PRINCIPAL"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"Selecione a opcao desejada:"<<endl;
    imprimirOpcaoSelecionada(0, pos, "Comprimir arquivo");
    imprimirOpcaoSelecionada(1, pos, "Descomprimir arquivo");
    imprimirOpcaoSelecionada(2, pos, "Sair");
}

void gerarMenuCompressao(int pos){
    system("cls");
    cout<<"---------------------------------------------------"<<endl;
    cout<<"COMPRESSAO DE ARQUIVO"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"Selecione a opcao desejada:"<<endl;
    imprimirOpcaoSelecionada(0, pos, "Comprimir por caracteres");
    imprimirOpcaoSelecionada(1, pos, "Comprimir por palavras");
    imprimirOpcaoSelecionada(2, pos, "Voltar");
}

void gerarMenuDescompressao(int pos){
    system("cls");
    cout<<"---------------------------------------------------"<<endl;
    cout<<"DESCOMPRESSAO DE ARQUIVO"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"Selecione a opcao desejada:"<<endl;
    imprimirOpcaoSelecionada(0, pos, "Descomprimir por caracteres");
    imprimirOpcaoSelecionada(1, pos, "Descomprimir por palavras");
    imprimirOpcaoSelecionada(2, pos, "Voltar");
}

void tratarMenuCompressao(){
    int pos, posMenu = 0;
    std::string path;
    while(true){
        gerarMenuCompressao(posMenu);
        pos = obterPosicao();
        if(pos == 1){
            if(posMenu > 0){
                posMenu--;
            }
        }
        else if(pos == 2){
            if(posMenu < 2){
                posMenu++;
            }
        }
        else if(pos == 3){
            if(posMenu == 0){
                cout<<"Comprimir por caractere"<<endl;
                auto begin = std::chrono::high_resolution_clock::now();
                lerNomeArquivo(&path, false);
                menu_compressao(path, false);
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                cout<<"Tempo de compressao: "<<elapsed.count() * 1e-9<<" segundo(s)"<<endl;
                break;
            }
            else if(posMenu == 1){
                cout<<"Comprimir por palavra"<<endl;
                auto begin = std::chrono::high_resolution_clock::now();
                lerNomeArquivo(&path, false);
                menu_compressao(path, true);
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                cout<<"Tempo de compressao: "<<elapsed.count() * 1e-9<<" segundo(s)"<<endl;
                break;
            }
            else if(posMenu == 2){
                break;
            }
        }
    }

}

void tratarMenuDescompressao(){
    int pos, posMenu = 0;
    std::string path;
    while(true){
        gerarMenuDescompressao(posMenu);
        pos = obterPosicao();
        if(pos == 1){
            if(posMenu > 0){
                posMenu--;
            }
        }
        else if(pos == 2){
            if(posMenu < 2){
                posMenu++;
            }
        }
        else if(pos == 3){
            if(posMenu == 0){
                cout<<"Descomprimir por caractere"<<endl;
                auto begin = std::chrono::high_resolution_clock::now();
                lerNomeArquivo(&path, true);
                menu_descompressao(path, false);
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                cout<<"Tempo de descompressao: "<<elapsed.count() * 1e-9<<" segundo(s)"<<endl;
                break;
            }
            else if(posMenu == 1){
                cout<<"Descomprimir por palavra"<<endl;
                auto begin = std::chrono::high_resolution_clock::now();
                lerNomeArquivo(&path, true);
                menu_descompressao(path, true);
                auto end = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
                cout<<"Tempo de descompressao: "<<elapsed.count() * 1e-9<<" segundo(s)"<<endl;
                break;
            }
            else if(posMenu == 2){
                break;
            }
        }
    }

}

void tratarMenuPrincipal(){
    int pos, posMenu = 0;
    while(true){
        gerarMenuPrincipal(posMenu);
        pos = obterPosicao();
        if(pos == 1){
            if(posMenu > 0){
                posMenu--;
            }
        }
        else if(pos == 2){
            if(posMenu < 2){
                posMenu++;
            }
        }
        else if(pos == 3){
            if(posMenu == 0){
                tratarMenuCompressao();
                system("pause");
            }
            else if(posMenu == 1){
                tratarMenuDescompressao();
                system("pause");
            }
            else if(posMenu == 2){
                cout<<"Encerrando......"<<endl;
                break;
            }
        }
    }
}
