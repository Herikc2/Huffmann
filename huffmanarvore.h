#ifndef HUFFMANARVORE_H
#define HUFFMANARVORE_H

#include <iostream>
#include "stdlib.h"

#include "encadeadalista.h"

using namespace std;

struct Node {
    char dado;
    unsigned frequencia;
    Node *esquerda, *direita;
};

struct MinHeap {
    unsigned tamanho;
    unsigned capacidade;
    struct Node** lista;
};

// ---------------------------------------------------- HUFFMAN TABLE -----------------------------------------------

struct tabelaHuffmanEncadeada{
    char c;
    int codigo;
};

// ---------------------------------------------------- HUFFMAN TABLE -----------------------------------------------

// ---------------------------------------------------- CHAR IN LIST ------------------------------------------------

struct charInList{
    char c;
    int frequencia;
};

struct TabelaHuffman
{
    char c;
    TListaEncadeada<int> code;
};

template <typename T1>
TElementoEncadeada<T1>* criarNovoElemento(T1 dado) {
    TElementoEncadeada<T1> *N = new TElementoEncadeada<T1>();
    N->dado = dado;
    N->prox = nullptr;
    return N;
}

bool verificaExisteEncadeada(TListaEncadeada<charInList> l, char c){
    for (TElementoEncadeada<charInList>* nav = l.inicio; nav != nullptr; nav = nav->prox)
        if(nav->dado.c == c)
            return true;
        else
            continue;
    return false;
}

TElementoEncadeada<charInList>* obtemDado(TListaEncadeada<charInList> l, char c){
    for (TElementoEncadeada<charInList>* nav = l.inicio; nav != nullptr; nav = nav->prox)
        if (nav->dado.c == c)
            return nav;
}

template <typename T>
T obtemDadoIndice(TListaEncadeada<T> l, int pos) {
    if (pos == 0)
        return l.inicio->dado;
    else {
        TElementoEncadeada<T>* atual = l.inicio;
        int indice = 0;
        while (atual != nullptr && indice < pos - 1) {
            atual = atual->prox;
            indice++;
        }
        if (atual->prox != nullptr)
            return atual->prox->dado;
    }
}

template <typename T1>
bool insereListaEncadeada(TListaEncadeada<T1> &l, T1 dado, int pos) {
    if (pos == 0) {
        TElementoEncadeada<T1> *novo = criarNovoElemento<T1>(dado);
        novo->prox = l.inicio;
        l.inicio = novo;
        return true;
    }
    else {
        TElementoEncadeada<T1> *nav = l.inicio;
        int i = 0;
        while (nav != nullptr && i < pos - 1) {
            nav = nav->prox;
            i++;
        }
        if (nav == nullptr) {
            return false;
        }
        else {
            TElementoEncadeada<T1> *novo = criarNovoElemento<T1>(dado);
            novo->prox = nav->prox;
            nav->prox = novo;
            return true;
        }
    }
}

void ImprimirElementoEncadeada(char c, int frequencia){
    cout << c << " - " << frequencia << endl;
}

void ImprimirListaEncadeada(TListaEncadeada<charInList> l) {
    for (TElementoEncadeada<charInList>* nav = l.inicio; nav != nullptr; nav = nav->prox)
        ImprimirElementoEncadeada(nav->dado.c, nav->dado.frequencia);
}

void BubbleSortEncadeada(TListaEncadeada<charInList> &l) {
    int quantidade = quantidadeElementosListaEncadeada(l);
    for (int i = 0; i < quantidade - 1; i++) {
        for (TElementoEncadeada<charInList>* nav = l.inicio; nav != nullptr && nav->prox != nullptr; nav = nav->prox) {
            if (nav->dado.frequencia > nav->prox->dado.frequencia) {
                char charAtual = nav->dado.c;
                int frequenciaAtual = nav->dado.frequencia;

                nav->dado.c = nav->prox->dado.c;
                nav->dado.frequencia = nav->prox->dado.frequencia;

                nav->prox->dado.c = charAtual;
                nav->prox->dado.frequencia = frequenciaAtual;
            }
        }
    }
}
// ------------------------------------------------------------------------------------------------------------------

Node* novoNo(char dado, unsigned frequencia) {
    Node* auxiliar = new Node();
    auxiliar->esquerda = auxiliar->direita = NULL;
    auxiliar->dado = dado;
    auxiliar->frequencia = frequencia;

    return auxiliar;
}

void preOrdem(Node* node){
    if(node != nullptr){
        cout << node->dado << " - " << node->frequencia << ", ";
        preOrdem(node->esquerda);
        preOrdem(node->direita);
    }
}

void posOrdem(Node* node){
    if(node != nullptr){
        preOrdem(node->esquerda);
        preOrdem(node->direita);
        cout << node->dado << " - " << node->frequencia << ", ";
    }
}

MinHeap* criarMinHeap(unsigned capacidade) {

    MinHeap* minHeap = new MinHeap();
    minHeap->tamanho = 0;
    minHeap->capacidade = capacidade;
    minHeap->lista = new Node*[minHeap->capacidade];
    return minHeap;
}

void trocaEntreMinHeap(Node** a, Node** b) {
    Node* aux = *a;
    *a = *b;
    *b = aux;
}

void mainHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->tamanho &&
            minHeap->lista[left]->frequencia < minHeap->lista[smallest]->frequencia)
        smallest = left;

    if (right < minHeap->tamanho &&
            minHeap->lista[right]->frequencia < minHeap->lista[smallest]->frequencia)
        smallest = right;

    if (smallest != idx) {
        trocaEntreMinHeap(&minHeap->lista[smallest], &minHeap->lista[idx]);
        mainHeapify(minHeap, smallest);
    }
}

int defineTamanhoUm(MinHeap* minHeap) {

    return (minHeap->tamanho == 1);
}

Node* extratorMinimo(MinHeap* minHeap) {

    Node* auxiliar = minHeap->lista[0];
    minHeap->lista[0] = minHeap->lista[minHeap->tamanho - 1];

    --minHeap->tamanho;
    mainHeapify(minHeap, 0);

    return auxiliar;
}

void insereMinHeap(MinHeap* minHeap, Node* minHeapNode) {
    ++minHeap->tamanho;
    int i = minHeap->tamanho - 1;

    while (i && minHeapNode->frequencia < minHeap->lista[(i - 1) / 2]->frequencia) {
        minHeap->lista[i] = minHeap->lista[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->lista[i] = minHeapNode;
}

void constroiMinHeap(MinHeap* minHeap) {
    int n = minHeap->tamanho - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        mainHeapify(minHeap, i);
}

void printLista(int lista[], int j) {
    int i;
    for (i = 0; i < j; ++i)
        cout<< lista[i];

    cout<<"\n";
}

int verificaSeFolha(Node* root) {

    return !(root->esquerda) && !(root->direita);
}

MinHeap* criaMinHeap(TListaEncadeada<charInList> l, int tamanho) {
    MinHeap* minHeap = criarMinHeap(tamanho);

    for (int i = 0; i < tamanho; ++i)
        minHeap->lista[i] = novoNo(obtemDadoIndice(l, i).c, obtemDadoIndice(l, i).frequencia);

    minHeap->tamanho = tamanho;
    constroiMinHeap(minHeap);

    return minHeap;
}

Node* constroiArvoreHuffman(TListaEncadeada<charInList> l, int tamanho) {
    Node *esquerda, *direita, *topo;
    MinHeap* minHeap = criaMinHeap(l, tamanho);

    while (!defineTamanhoUm(minHeap)) {

        esquerda = extratorMinimo(minHeap);
        direita = extratorMinimo(minHeap);

        topo = novoNo('+', esquerda->frequencia + direita->frequencia);

        topo->esquerda = esquerda;
        topo->direita = direita;

        insereMinHeap(minHeap, topo);
    }

    return extratorMinimo(minHeap);
}

void imprimeCodigos(Node* root, int lista[], int topo) {
    if (root->esquerda) {
        lista[topo] = 0;
        imprimeCodigos(root->esquerda, lista, topo + 1);
    }

    if (root->direita) {
        lista[topo] = 1;
        imprimeCodigos(root->direita, lista, topo + 1);
    }

    if (verificaSeFolha(root)) {
        cout << root->dado << " : ";
        printLista(lista, topo);
    }
}

void HuffmannCodigo(Node* root, TabelaHuffman* HuffmanTabela, TListaEncadeada<int>& codigos, int topo){
    static size_t i = 0;

    if(root->esquerda){
        insereListaEncadeada(codigos, 0, topo);
        HuffmannCodigo(root->esquerda, HuffmanTabela, codigos, topo + 1);
    }

    if(root->direita){
        insereListaEncadeada(codigos, 1, topo);
        HuffmannCodigo(root->direita, HuffmanTabela, codigos, topo + 1);
    }

    if(verificaSeFolha(root)) {
        HuffmanTabela[i].c = root->dado;
        for(int j = 0; j < topo; j++){
            insereListaEncadeada(HuffmanTabela[i].code, obtemDadoIndice(codigos, j),
                                 quantidadeElementosListaEncadeada(HuffmanTabela[i].code));
        }
        i++;
    }
}

void inicializaTabelaHuffmann(TabelaHuffman* codigos, int tamanho)
{
    for (size_t i = 0; i < tamanho; i++)
    {
        inicializaListaEncadeada(codigos[i].code);
    }
}

void pegaCodigo(TListaEncadeada<int>& hcode, TListaEncadeada<int>& ncode, TabelaHuffman* htable, int size, string text)
{
    for (size_t i = 0; i < text.length(); i++) {
        insereListaEncadeada(ncode, (int)text.at(i), quantidadeElementosListaEncadeada(ncode));
        for (size_t j = 0; j < size; j++) {
            if (text.at(i) == htable[j].c) {
                for (size_t k = 0; k < quantidadeElementosListaEncadeada(htable[j].code); k++) {
                    insereListaEncadeada(hcode, obtemDadoIndice(htable[j].code, k),
                                         quantidadeElementosListaEncadeada(hcode));
                }
                break;
            }
        }

    }
}

void imprimeCodigo(TListaEncadeada<int> code)
{
    for (size_t i = 0; i < quantidadeElementosListaEncadeada(code); i++)
        cout << obtemDadoIndice(code, i);
}

string decodificacao(Node* root, TListaEncadeada<int> code){
    Node* rootOriginal;
    rootOriginal = root;
    int dado;
    string normalText = "";

    for (size_t i = 0; i < quantidadeElementosListaEncadeada(code) + 1; i++){
        if(verificaSeFolha(root)){
            normalText += root->dado;
            root = rootOriginal;
        }

        dado = obtemDadoIndice(code, i);
        if(dado == 0) // Esquerda
            root = root->esquerda;
        else if(dado == 1) // Direita
            root = root->direita;
    }
    return normalText;
}

#endif // HUFFMANARVORE_H
