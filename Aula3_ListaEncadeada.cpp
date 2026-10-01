// Pratica reconstruida com base na Aula 3: lista encadeada simples.
#include <iostream>
#include <string>
using namespace std;
struct No { int info; No* prox; };
class ListaEncadeada {
    No* inicio = nullptr;
    int tamanho = 0;
public:
    // Proibe copias rasas que fariam duas listas possuirem os mesmos nos.
    ListaEncadeada() = default;
    ListaEncadeada(const ListaEncadeada&) = delete;
    ListaEncadeada& operator=(const ListaEncadeada&) = delete;
    ~ListaEncadeada() { Limpar(); }
    bool Vazia() const { return inicio == nullptr; }
    int Tamanho() const { return tamanho; }
    void InserirInicio(int valor) {
        No* novo = new No{valor, inicio};
        inicio = novo;
        tamanho++;
    }
    void InserirFim(int valor) {
        No* novo = new No{valor, nullptr};
        if (Vazia()) inicio = novo;
        else {
            No* p = inicio;
            while (p->prox != nullptr) p = p->prox;
            p->prox = novo;
        }
        tamanho++;
    }
    No* Buscar(int valor) const {
        No* p = inicio;
        while (p != nullptr && p->info != valor) p = p->prox;
        return p;
    }
    bool Excluir(int valor) {
        No* atual = inicio;
        No* anterior = nullptr;
        while (atual != nullptr && atual->info != valor) {
            anterior = atual;
            atual = atual->prox;
        }
        if (atual == nullptr) return false;
        if (anterior == nullptr) inicio = atual->prox;
        else anterior->prox = atual->prox;
        delete atual;
        tamanho--;
        return true;
    }
    void Imprimir() const {
        if (Vazia()) cout << "Lista vazia";
        for (No* p = inicio; p != nullptr; p = p->prox) cout << p->info << ' ';
        cout << '\n';
    }
    void Limpar() {
        while (inicio != nullptr) {
            No* aux = inicio;
            inicio = inicio->prox;
            delete aux;
        }
        tamanho = 0;
    }
};
void Demonstrar() {
    ListaEncadeada l;
    l.InserirInicio(20); l.InserirInicio(10); l.InserirFim(30);
    cout << "Lista: "; l.Imprimir();
    cout << "Encontrou 20? " << (l.Buscar(20) != nullptr) << '\n';
    l.Excluir(20); cout << "Removido 20: "; l.Imprimir();
    l.Excluir(10); l.Excluir(30);
    cout << "Depois de remover inicio e fim: "; l.Imprimir();
    cout << "Exclusao de ausente: " << l.Excluir(99) << '\n';
    l.InserirFim(40); l.Limpar();
    cout << "Tamanho depois de limpar: " << l.Tamanho() << '\n';
}
int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") { Demonstrar(); return 0; }
    ListaEncadeada l; int opc, valor;
    cout << "AULA 3 - LISTA ENCADEADA SIMPLES\n";
    while (true) {
        cout << "\n1 Inserir inicio | 2 Inserir fim | 3 Imprimir | 4 Buscar\n5 Excluir valor | 6 Tamanho/vazia | 7 Limpar | 8 Demonstracao | 0 Sair\nOpcao: ";
        if (!(cin >> opc) || opc == 0) break;
        if (opc == 1 || opc == 2 || opc == 4 || opc == 5) {
            cout << "Valor: "; if (!(cin >> valor)) break;
            if (opc == 1) l.InserirInicio(valor);
            if (opc == 2) l.InserirFim(valor);
            if (opc == 4) cout << (l.Buscar(valor) ? "Encontrado\n" : "Ausente\n");
            if (opc == 5) cout << (l.Excluir(valor) ? "Excluido\n" : "Ausente\n");
        } else if (opc == 3) l.Imprimir();
        else if (opc == 6) cout << "Tamanho: " << l.Tamanho() << "; vazia: " << l.Vazia() << '\n';
        else if (opc == 7) l.Limpar();
        else if (opc == 8) Demonstrar();
        else cout << "Opcao invalida\n";
    }
}
