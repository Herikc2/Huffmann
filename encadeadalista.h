#ifndef ENCADEADALISTA_H
#define ENCADEADALISTA_H

#include <iostream>
#include "string"

#include "arvore.h"

using namespace std;

template<typename T>
struct TElementoEncadeada {
    T dado;
    TElementoEncadeada *prox;
};

template<typename T>
struct TListaEncadeada {
    TElementoEncadeada<T> *inicio;
};

template<typename T>
void verificaExisteEncadeada(TListaEncadeada<T> l, T* dado);
template<typename T>
TElementoEncadeada<T>* navegadorEncadeadaAnterior(TListaEncadeada<T> l, int pos);
template<typename T>
int descobreIndiceEncadeada(TListaEncadeada<T> l, TElementoEncadeada<T> e);

template<typename T>
TElementoEncadeada<T>* criarNovoElementoEncadeada(char dado) {
    TElementoEncadeada<T> *N = new TElementoEncadeada<T>();
    N->prox = nullptr;
    N->dado = dado;
    return N;
}

template<typename T>
int quantidadeElementosListaEncadeada(TListaEncadeada<T> l) {
    int cont = 0;
    TElementoEncadeada<T> *nav = l.inicio;
    while (true) {
        if (nav == nullptr)
            return cont;
        nav = nav->prox;
        cont++;
    }
}

template<typename T>
TElementoEncadeada<T>* navegadorEncadeadaAnterior(TListaEncadeada<T> l, int pos) {
    if (pos >= 0) {
        TElementoEncadeada<T> *nav = l.inicio;
        int i = 0;
        while (nav != nullptr && i < pos - 1) {
            nav = nav->prox;
            i++;
        }
        return nav;
    }
    return NULL;
}

template<typename T>
TElementoEncadeada<T>* navegadorEncadeadaAtual(TListaEncadeada<T> l, int pos) {
    if (pos >= 0) {
        TElementoEncadeada<T> *nav = l.inicio;
        for (int i = 0; i < pos; i++)
            nav = nav->prox;
        return nav;
    }
    return NULL;
}

template<typename T>
void inicializaListaEncadeada(TListaEncadeada<T> &l) {
    l.inicio = nullptr;
}

template<typename T>
bool removeListaEncadeada(TListaEncadeada<T> &l, int pos) {
    if (pos == 0)
    {
        TElementoEncadeada<T> *removido = l.inicio;
        l.inicio = removido->prox;
        delete removido;
        removido = nullptr;
    }
    else
    {
        TElementoEncadeada<T> *nav = navegadorEncadeadaAnterior(l, pos);
        if (nav == nullptr)
            return false;
        else {
            TElementoEncadeada<T> *removido = nav->prox;
            nav->prox = removido->prox;
            delete removido;
            removido = nullptr;
        }
    }
}

template<typename T>
bool verificaExisteEncadeada(TListaEncadeada<T> l, T dado) {
    return verificaExisteEncadeada(l, dado);
}

template<typename T>
int descobreIndiceEncadeada(TListaEncadeada<T> l, TElementoEncadeada<T> e) {
    int i = 0;
    for (TElementoEncadeada<T>* nav = l.inicio; nav != nullptr; nav = nav->prox, i++)
        if (verificaExisteEncadeada(*nav, e))
            return i;
    return -1;
}

#endif // ENCADEADALISTA_H
