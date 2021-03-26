#ifndef ARVORE_H
#define ARVORE_H

template <typename TIPO>
struct TNo {
    int chave;
    int frequencia = 0;
    TIPO dado;
    TNo* direita;
    TNo* esquerda;
};

template <typename TIPO>
struct TArvore {
    TNo<TIPO>* raiz;
};

template <typename TIPO>
void inicializa(TArvore<TIPO>& a) {
    a.raiz = nullptr;
}

template <typename TIPO>
void insere(TNo<TIPO>*& no, int dado, int frequencia) {
    if (no == nullptr) {
        TNo<TIPO>* aux = new TNo<TIPO>();
        no = aux;
        no->dado = dado;
        no->frequencia = frequencia;
        no->direita = nullptr;
        no->esquerda = nullptr;
    }
    else {
        if (dado > no->dado) {
            insere(no->direita, dado, frequencia);
        }
        else {
            if (dado < no->dado) {
                insere(no->esquerda, dado, frequencia);
            }
        }
    }
}

template <typename TIPO>
void procura_remove(
    TNo<TIPO>*& no,
    int chave) {
    if (no != nullptr) {
        if (no->chave == chave) {
            remover(no);
        }
        else {
            if (chave > no->chave) {
                procura_remove(
                    no->dir, chave);
            }
            else {
                procura_remove(
                    no->esq, chave);
            }
        }
    }
}

template <typename TIPO>
void remover(TNo<TIPO>*& no) {
    TNo<TIPO>* apagar;
    TNo<TIPO>* maior = no->esquerda;
    if (maior == nullptr) {
        apagar = no;
        no = no->direita;
        delete apagar;
        return;
    }
    TNo<TIPO>* pai = nullptr;
    while (maior->direita != nullptr) {
        pai = maior;
        maior = maior->direita;
    }
    maior->direita = no->direita;
    if (pai != nullptr) {
        pai->direita = maior->esquerda;
        maior->esquerda = no->esquerda;
    }
    apagar = no;
    no = maior;
    delete apagar;
}

template <typename TIPO>
int altura(TArvore<TIPO> a) {
    return altura(a.raiz);
}

template <typename TIPO>
int altura(TNo<TIPO>* no) {
    if (no != nullptr) {
        int he = 0, hd = 0;
        he = altura(no->esquerda);
        hd = altura(no->direita);

        if (he > hd)
            return he + 1;
        else
            return hd + 1;
    }
    return 0;
}

#endif // ARVORE_H
