#include "../include/heap.hpp"

Heap::Heap(int maxsize){
    this->tamanho = 0;
    this->data = new int[maxsize];
}

Heap::~Heap(){
    delete[] this->data;
}

void Heap::Inserir(int x){
    this->data[this->tamanho] = x;
    this->HeapifyPorCima(this->tamanho);
    this->tamanho++;
}

int Heap::Remover(){
    int removido = this->data[0];
    this->data[0] = this->data[this->tamanho-1];
    this->tamanho--;
    this->HeapifyPorBaixo(0);
    return removido;
}

bool Heap::Vazio(){
    return this->tamanho == 0;
}

int Heap::GetAncestral(int posicao){
    return (posicao-1)/2;
}

int Heap::GetSucessorEsq(int posicao){
    return 2*posicao+1;
}

int Heap::GetSucessorDir(int posicao){
    return 2*posicao+2;
}

void Heap::HeapifyPorBaixo(int posicao) {
    int esq = GetSucessorEsq(posicao);
    int dir = GetSucessorDir(posicao);
    int maior = posicao;
    if (esq < this->tamanho && this->data[esq] < this->data[maior]) {
        maior = esq;
    }
    if (dir < this->tamanho && this->data[dir] < this->data[maior]) {
        maior = dir;
    }
    if (maior != posicao) {
        std::swap(this->data[posicao], this->data[maior]);
        HeapifyPorBaixo(maior);
    }
}

void Heap::HeapifyPorCima(int posicao) {
    int ancestral = GetAncestral(posicao);
    if (ancestral >= 0 && this->data[posicao] < this->data[ancestral]) {
        std::swap(this->data[posicao], this->data[ancestral]);
        HeapifyPorCima(ancestral);
    }
}