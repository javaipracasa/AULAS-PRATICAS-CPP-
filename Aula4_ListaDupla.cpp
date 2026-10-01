// Pratica reconstruida com base na Aula 4: lista duplamente encadeada.
// Aqui inicio e fim apontam para elementos reais (nao ha no sentinela).
#include <iostream>
#include <string>
using namespace std;
struct No { int info; No* ant; No* prox; };
class ListaDupla {
    No* inicio = nullptr;
    No* fim = nullptr;
    int tamanho = 0;
    void Desligar(No* atual) {
        if (atual->ant != nullptr) atual->ant->prox = atual->prox;
        else inicio = atual->prox;
        if (atual->prox != nullptr) atual->prox->ant = atual->ant;
        else fim = atual->ant;
        delete atual;
        tamanho--;
    }
    void ImprimirRec(No* p) const {
        if (p == nullptr) { cout << '\n'; return; }
        cout << p->info << ' ';
        ImprimirRec(p->prox);
    }
public:
    ListaDupla() = default;
    ListaDupla(const ListaDupla&) = delete;
    ListaDupla& operator=(const ListaDupla&) = delete;
    ~ListaDupla() { while (inicio != nullptr) Desligar(inicio); }
    int Tamanho() const { return tamanho; }
    bool Vazia() const { return inicio == nullptr; }
    No* Buscar(int valor) const {
        No* p = inicio;
        while (p != nullptr && p->info != valor) p = p->prox;
        return p;
    }
    void InserirInicio(int valor) {
        No* novo = new No{valor, nullptr, inicio};
        if (inicio != nullptr) inicio->ant = novo;
        else fim = novo;
        inicio = novo; tamanho++;
    }
    void InserirFim(int valor) {
        No* novo = new No{valor, fim, nullptr};
        if (fim != nullptr) fim->prox = novo;
        else inicio = novo;
        fim = novo; tamanho++;
    }
    bool InserirAntes(int referencia, int valor) {
        No* atual = Buscar(referencia);
        if (atual == nullptr) return false;
        if (atual == inicio) { InserirInicio(valor); return true; }
        No* novo = new No{valor, atual->ant, atual};
        atual->ant->prox = novo;
        atual->ant = novo;
        tamanho++; return true;
    }
    bool InserirDepois(int referencia, int valor) {
        No* atual = Buscar(referencia);
        if (atual == nullptr) return false;
        if (atual == fim) { InserirFim(valor); return true; }
        No* novo = new No{valor, atual, atual->prox};
        atual->prox->ant = novo;
        atual->prox = novo;
        tamanho++; return true;
    }
    bool ExcluirPosicao(int posicao) {
        if (posicao < 1 || posicao > tamanho) return false;
        No* atual = inicio;
        for (int i = 1; i < posicao; i++) atual = atual->prox;
        Desligar(atual); return true;
    }
    void Imprimir() const { if (Vazia()) cout << "Lista vazia"; ImprimirRec(inicio); }
    void ImprimirReverso() const {
        for (No* p = fim; p != nullptr; p = p->ant) cout << p->info << ' ';
        cout << '\n';
    }
};
void Demonstrar() {
    ListaDupla l;
    l.InserirInicio(20); l.InserirInicio(10); l.InserirFim(40);
    l.InserirAntes(40, 30); l.InserirDepois(20, 25);
    cout << "Lista: "; l.Imprimir();
    cout << "Reverso: "; l.ImprimirReverso();
    cout << "Encontrou 30? " << (l.Buscar(30) != nullptr) << '\n';
    l.ExcluirPosicao(3); cout << "Excluiu posicao 3: "; l.Imprimir();
    l.ExcluirPosicao(1); l.ExcluirPosicao(l.Tamanho());
    cout << "Excluiu inicio e fim: "; l.Imprimir();
    while (!l.Vazia()) l.ExcluirPosicao(1);
    l.Imprimir(); cout << "Excluir em vazia: " << l.ExcluirPosicao(1) << '\n';
}
int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") { Demonstrar(); return 0; }
    ListaDupla l; int opc, valor, ref, pos;
    cout << "AULA 4 - LISTA DUPLA\n";
    while (true) {
        cout << "\n1 Inserir inicio | 2 Inserir fim | 3 Inserir antes | 4 Inserir depois\n"
             << "5 Imprimir | 6 Buscar | 7 Excluir posicao | 8 Reverso\n"
             << "9 Tamanho | 10 Demonstracao | 0 Sair\nOpcao: ";
        if (!(cin >> opc) || opc == 0) break;
        if (opc == 1 || opc == 2 || opc == 6) {
            cout << "Valor: "; if (!(cin >> valor)) break;
            if (opc == 1) l.InserirInicio(valor);
            if (opc == 2) l.InserirFim(valor);
            if (opc == 6) cout << (l.Buscar(valor) ? "Encontrado\n" : "Ausente\n");
        } else if (opc == 3 || opc == 4) {
            cout << "Valor de referencia e novo valor: "; if (!(cin >> ref >> valor)) break;
            bool ok = opc == 3 ? l.InserirAntes(ref, valor) : l.InserirDepois(ref, valor);
            cout << (ok ? "Inserido\n" : "Referencia ausente\n");
        } else if (opc == 5) l.Imprimir();
        else if (opc == 7) {
            cout << "Posicao: "; if (!(cin >> pos)) break;
            cout << (l.ExcluirPosicao(pos) ? "Excluido\n" : "Posicao invalida\n");
        } else if (opc == 8) l.ImprimirReverso();
        else if (opc == 9) cout << "Tamanho: " << l.Tamanho() << '\n';
        else if (opc == 10) Demonstrar();
        else cout << "Opcao invalida\n";
    }
}
