#include "menu.h"

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
                //comprimir por caractere
                break;
            }
            else if(posMenu == 1){
                cout<<"Comprimir por palavra"<<endl;
                //comprimir por palavra
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
                //descomprimir por caractere
                break;
            }
            else if(posMenu == 1){
                cout<<"Descomprimir por palavra"<<endl;
                //descomprimir por palavra 
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

int main(){
    tratarMenuPrincipal();
}