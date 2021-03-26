#ifndef CONTROLE_H
#define CONTROLE_H

#include <iomanip>
#include <fstream>

#include "encadeadalista.h"
#include "arvore.h"
#include "huffmanarvore.h"

struct Controle {
    Node* root = nullptr;
    TListaEncadeada<charInList> charPorFrequencia;
    TListaEncadeada<tabelaHuffmanEncadeada> tabelaHuffmanEncadeada_;
    TabelaHuffman* tabelaHuffman;
    TListaEncadeada<int> codigoDeHuffman;
    TListaEncadeada<int> codigoNormal;
    TListaEncadeada<int> codigosAuxiliares;
    string text = "";
    int tamanho;
    int vectorSize = 0;
    int codigoExternoTamanho = 0;
};

void inicializaListas(Controle& c){
    inicializaListaEncadeada(c.charPorFrequencia);
    inicializaListaEncadeada(c.tabelaHuffmanEncadeada_);
    inicializaListaEncadeada(c.codigoDeHuffman);
    inicializaListaEncadeada(c.codigoNormal);
    inicializaListaEncadeada(c.codigosAuxiliares);
}

void inicializaHuffman(TabelaHuffman*& tabela, int& tamanho, TListaEncadeada<charInList> charPorFrequencia){
    tamanho = quantidadeElementosListaEncadeada(charPorFrequencia);
    tabela = new TabelaHuffman[tamanho];
    inicializaTabelaHuffmann(tabela, tamanho);
}

string leituraTextoPorFrequencia(int& vectorSize, TListaEncadeada<charInList>& charPorFrequencia){
    string textReturn ="";
    ifstream txtFile;
    char ch;
    int position = 0;

    txtFile.open("C:/Users/herik/OneDrive/Documents/desbugaPORFAVOR/textDesc.txt");

    while(txtFile.get(ch)){
        if(!verificaExisteEncadeada(charPorFrequencia, ch)){
            charInList novo;
            novo.c = ch;
            novo.frequencia = 1;
            insereListaEncadeada(charPorFrequencia, novo, position);
            position++;
            vectorSize++;
         }
        else
            obtemDado(charPorFrequencia, ch)->dado.frequencia++;
        cout << ch;
        textReturn += ch;
    }
    txtFile.close();
    return textReturn;
}

void leituraCodigoExterno(TListaEncadeada<tabelaHuffmanEncadeada>& tabelaHuffmanEncadeada_, int& codigoExternoTamanho){
    ifstream txtFile;
    txtFile.open("C:/Users/herik/OneDrive/Documents/desbugaPORFAVOR/codigo.txt");
    char ch;
    int position = 0;
    string codigo = "";

    while(txtFile.get(ch)){
        tabelaHuffmanEncadeada novo;
        novo.c = ch;
        while(txtFile.get(ch)){
            if(ch == '\n')
                break;
            codigo += ch;
        }
        novo.codigo = atoi(codigo.c_str());
        codigo = "";
        insereListaEncadeada(tabelaHuffmanEncadeada_, novo, position);
        position++;
        codigoExternoTamanho++;
    }
    cout << "TABELA DE HUFFMAN: " << endl << endl;
    for(TElementoEncadeada<tabelaHuffmanEncadeada>* nav = tabelaHuffmanEncadeada_.inicio; nav!= nullptr;
        nav = nav->prox)
         cout << nav->dado.c << " - " << nav->dado.codigo << endl;
    txtFile.close();
}

void pegaCodigoExterno(TListaEncadeada<int>& codigoDeHuffman){
    ifstream txtFile;
    txtFile.open("C:/Users/herik/OneDrive/Documents/desbugaPORFAVOR/textCrip.txt");
    char ch;
    int posicao = 0;

    while(txtFile.get(ch)){
        insereListaEncadeada(codigoDeHuffman, (int)ch - 48, posicao);
        posicao++;
    }
    txtFile.close();
}

void leituraTextoPorFrequenciaExterno(TListaEncadeada<charInList>& charPorFrequencia, string normalText){
    char ch;
    int position = 0;
    for(int i = 0; i < normalText.size();i++){
        ch = normalText.at(i);
        if(!verificaExisteEncadeada(charPorFrequencia, ch)){
            charInList novo;
            novo.c = ch;
            novo.frequencia = 1;
            insereListaEncadeada(charPorFrequencia, novo, position);
            position++;
         }
        else
            obtemDado(charPorFrequencia, ch)->dado.frequencia++;
    }
}

Node* arvoreExterno(Node*& root, TListaEncadeada<tabelaHuffmanEncadeada>& tabelaHuffmanEncadeada_){
    Node* nodeAtual = new Node();
    Node* raiz = new Node();
    string codigoStr;
    int contadorStr = 0;
    string tempStr;

    nodeAtual = root;
    nodeAtual = novoNo('R', 0); // DEFINE RAIZ
    raiz = nodeAtual;
    for(TElementoEncadeada<tabelaHuffmanEncadeada>* nav = tabelaHuffmanEncadeada_.inicio; nav != nullptr
        ; nav = nav->prox){
        codigoStr = to_string(nav->dado.codigo);
        contadorStr = codigoStr.size();

        for(int i = 0; i < contadorStr; i++){
            tempStr = codigoStr.at(i);
            if(tempStr == "0"){ // 0 = Esquerda
                if(nodeAtual->esquerda == nullptr){
                    if(i + 1 == contadorStr){
                        nodeAtual->esquerda = novoNo(nav->dado.c, 1);
                    }else{
                        nodeAtual->esquerda = novoNo('+', 1);
                    }
                }
                nodeAtual = nodeAtual->esquerda;
            }else{ // 1 = Direita
                if(nodeAtual->direita == nullptr){
                    if(i + 1 == contadorStr){
                        nodeAtual->direita = novoNo(nav->dado.c, 2);
                    }else{
                        nodeAtual->direita = novoNo('+', 2);
                    }
                }
                nodeAtual = nodeAtual->direita;
            }
        }
        nodeAtual = raiz;
    }
    nodeAtual = raiz;
    return nodeAtual;
}

// ------------------------------------- MENU ---------------------------------------------

int imprimeMenu(){
    int op;
    cout << "ESCOLHA UMA OPCAO: " << endl;
    cout << "1 - Codificar" << endl;
    cout << "2 - Descodificar" << endl;
    cout << "Obs: Para o caso de codificacao o texto deve estar no arquivo \"text\"."
            " Para decodificacao deve se ter o codigo no arquivo \"codigo\"" << endl;
    cout << "Opcao: ";
    cin >> op;
    return op;
}

// ----------------------------------------------------------------------------------------

#endif // CONTROLE_H
