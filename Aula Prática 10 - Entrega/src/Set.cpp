#include "../include/Set.hpp"

StringSet::StringSet(int tamanho) {
    tamanhoOriginal = tamanho;
    tamanhoTabela = tamanho;
    tamanhoConjunto = 0;
    tabela = new ElementoTabela[tamanhoTabela];
    for (int i = 0; i < tamanhoTabela; ++i) {
        tabela[i].vazio = true;
        tabela[i].retirada = false;
    }
}

StringSet::~StringSet() {
    delete[] tabela;
}

void StringSet::Inserir(string s) {
    if (!Pertence(s)){
        if (tamanhoConjunto >= tamanhoTabela / 2) {
            Resize(tamanhoTabela * 2);
        }
        int pos = Hash(s);
        while (!tabela[pos].vazio && !tabela[pos].retirada) {
            if (tabela[pos].dado == s) {
                return;
            }
            pos = (pos + 1) % tamanhoTabela;
        }
        tabela[pos].dado = s;
        tabela[pos].vazio = false;
        tabela[pos].retirada = false;
        tamanhoConjunto++;
    }
}

void StringSet::Remover(string s) {
    int pos = Hash(s);
    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada && tabela[pos].dado == s) {
            tabela[pos].retirada = true;
            tamanhoConjunto--;
            if (tamanhoConjunto <= tamanhoTabela / 8) {
                Resize(tamanhoTabela / 2);
            }
            return;
        }
        pos = (pos + 1) % tamanhoTabela;
    }
}

bool StringSet::Pertence(string s) {
    int pos = Hash(s);
    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada && tabela[pos].dado == s) {
            return true;
        }
        pos = (pos + 1) % tamanhoTabela;
    }
    return false;
}
        
StringSet* StringSet::Intersecao(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoOriginal);
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada && S->Pertence(tabela[i].dado)) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    return resultado;
}

StringSet* StringSet::Uniao(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoOriginal);
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; ++i) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado;
}

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {
    StringSet* resultado = new StringSet(tamanhoOriginal);
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada && !S->Pertence(tabela[i].dado)) {
            resultado->Inserir(tabela[i].dado);
        }
    }
    for (int i = 0; i < S->tamanhoTabela; ++i) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada && !Pertence(S->tabela[i].dado)) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }
    return resultado;
}

void StringSet::Imprimir() {
    bool conjuntoVazio = true;
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            conjuntoVazio = false;
            break;
        }
    }

    cout << (conjuntoVazio ? "{ " : "{ ") << flush;

    bool primeiro = true; 
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            if (!primeiro) {
                cout << ", ";
            }
            cout << tabela[i].dado;
            primeiro = false;
        }
    }

    cout << " }" << endl; 
}

int StringSet::Hash(string s) {
    int hash = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        hash = (hash * 31 + s[i]) % tamanhoTabela;
    }
    return hash;
}

void StringSet::Rehash(int pos) {
    string s = tabela[pos].dado;
    tabela[pos].retirada = true;
    tamanhoConjunto--;
    Inserir(s);
}


void StringSet::Resize(size_t tamanho) {
    ElementoTabela* novaTabela = new ElementoTabela[tamanho];
    for (size_t i = 0; i < tamanho; ++i) {
        novaTabela[i].vazio = true;
        novaTabela[i].retirada = false;
    }
    for (int i = 0; i < tamanhoTabela; ++i) {
        if (!tabela[i].vazio && !tabela[i].retirada) {
            int pos = Hash(tabela[i].dado);
            while (!novaTabela[pos].vazio) {
                pos = (pos + 1) % tamanho;
            }
            novaTabela[pos].dado = tabela[i].dado;
            novaTabela[pos].vazio = false;
            novaTabela[pos].retirada = false;
        }
    }
    delete[] tabela;
    tabela = novaTabela;
    tamanhoTabela = tamanho;
}