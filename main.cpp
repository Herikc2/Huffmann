#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "encadeadalista.h"
#include "arvore.h"
#include "huffmanarvore.h"
#include "controle.h"

#define CODIFICACAO 1
#define DECODIFICACAO 2

using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Controle controle;
    int* vetor;
    int op;

    op = imprimeMenu();
    inicializaListas(controle);
    system("cls");

    // Codificação de texto informado
    if(op == CODIFICACAO){
        cout << "TEXTO INFORMADO: " << endl << endl;
        controle.text = leituraTextoPorFrequencia(controle.vectorSize, controle.charPorFrequencia);
        vetor = new int[controle.vectorSize];

        // INCIALIZA TABELA HUFFMANN
        inicializaHuffman(controle.tabelaHuffman, controle.tamanho, controle.charPorFrequencia);

        // CONSTROI ARVORE
        controle.root = constroiArvoreHuffman(controle.charPorFrequencia, controle.tamanho);
        HuffmannCodigo(controle.root, controle.tabelaHuffman, controle.codigosAuxiliares, 0);

        cout << endl << endl << "CHARACTERS DESORDENADOS: " << endl;
        ImprimirListaEncadeada(controle.charPorFrequencia);

        BubbleSortEncadeada(controle.charPorFrequencia);
        cout << endl << endl << "CARACTERES ORDENADOS: " << endl;
        ImprimirListaEncadeada(controle.charPorFrequencia);

        cout << endl << "TABELA DE HUFFMAN: " << endl;
        imprimeCodigos(controle.root, vetor, 0);

        cout << endl << "HUFFMANN CODIGO: " << endl;
        pegaCodigo(controle.codigoDeHuffman, controle.codigoNormal, controle.tabelaHuffman, controle.tamanho, controle.text);
        imprimeCodigo(controle.codigoDeHuffman);
        cout << endl << endl;

        cout << "FRASE ORIGINAL DECODIFICADA" << endl;
        cout << decodificacao(controle.root, controle.codigoDeHuffman);

        // PREORDEM E POS ORDEM
        cout << endl << endl << "POS-ORDEM:" << endl;
        preOrdem(controle.root);
        cout << endl << endl << "PRE-ORDEM:" << endl;
        posOrdem(controle.root);
        cout << endl << endl;
    }else if(op == DECODIFICACAO){
        leituraCodigoExterno(controle.tabelaHuffmanEncadeada_, controle.codigoExternoTamanho);
        controle.root = arvoreExterno(controle.root, controle.tabelaHuffmanEncadeada_);

        cout << endl << "HUFFMANN CODIGO: " << endl;
        pegaCodigoExterno(controle.codigoDeHuffman);
        imprimeCodigo(controle.codigoDeHuffman);
        cout << endl << endl;

        cout << "FRASE ORIGINAL DECODIFICADA" << endl;
        string normalText = decodificacao(controle.root, controle.codigoDeHuffman);
        cout << normalText;
        cout << endl << endl;

        leituraTextoPorFrequenciaExterno(controle.charPorFrequencia, normalText);

        controle.root = nullptr;
        // INCIALIZA TABELA HUFFMANN
        inicializaHuffman(controle.tabelaHuffman, controle.tamanho, controle.charPorFrequencia);

        // CONSTROI ARVORE
        controle.root = constroiArvoreHuffman(controle.charPorFrequencia, controle.tamanho);
        HuffmannCodigo(controle.root, controle.tabelaHuffman, controle.codigosAuxiliares, 0);

        // PREORDEM E POS ORDEM
        cout << "POS-ORDEM:" << endl;
        preOrdem(controle.root);
        cout << endl << endl << "PRE-ORDEM:" << endl;
        posOrdem(controle.root);
        cout << endl << endl;
    }

    return 0;
}
