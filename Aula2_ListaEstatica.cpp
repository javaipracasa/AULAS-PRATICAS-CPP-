// Pratica reconstruida com base na Aula 2: lista estatica em array.
// Posicoes informadas pelo usuario comecam em 1; indices do array em 0.
#include <iostream>
#include <string>
using namespace std;
class ListaEstatica {
    static const int CAPACIDADE = 10;
    int dados[CAPACIDADE]{};
    int tamanho = 0;
public:
    bool Vazia() const { return tamanho == 0; }
    int Tamanho() const { return tamanho; }
    bool Inserir(int valor, int posicao) {
        if (tamanho == CAPACIDADE || posicao < 1 || posicao > tamanho + 1) return false;
        int indice = posicao - 1;
        // Desloca da direita para a esquerda para nao sobrescrever valores.
        for (int i = tamanho; i > indice; i--) dados[i] = dados[i - 1];
        dados[indice] = valor;
        tamanho++;
        return true;
    }
    bool Excluir(int posicao) {
        if (posicao < 1 || posicao > tamanho) return false;
        for (int i = posicao - 1; i < tamanho - 1; i++) dados[i] = dados[i + 1];
        tamanho--;
        return true;
    }
    int Buscar(int valor) const {
        for (int i = 0; i < tamanho; i++) if (dados[i] == valor) return i + 1;
        return -1;
    }
    void Imprimir() const {
        if (Vazia()) cout << "Lista vazia";
        for (int i = 0; i < tamanho; i++) cout << dados[i] << ' ';
        cout << '\n';
    }
};
void Demonstrar() {
    ListaEstatica l;
    l.Inserir(10, 1); l.Inserir(30, 2); l.Inserir(20, 2);
    cout << "Insercao no meio: "; l.Imprimir();
    cout << "Posicao do 20: " << l.Buscar(20) << '\n';
    l.Excluir(2); cout << "Exclusao do meio: "; l.Imprimir();
    cout << "Posicao invalida aceita? " << l.Excluir(8) << '\n';
    l.Excluir(1); l.Excluir(1); l.Imprimir();
}
int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") { Demonstrar(); return 0; }
    ListaEstatica l;
    int opc, valor, pos;
    cout << "AULA 2 - LISTA ESTATICA (capacidade 10)\n";
    while (true) {
        cout << "\n1 Inserir | 2 Imprimir | 3 Buscar | 4 Excluir por posicao\n5 Tamanho/vazia | 6 Demonstracao | 0 Sair\nOpcao: ";
        if (!(cin >> opc) || opc == 0) break;
        if (opc == 1) {
            cout << "Valor e posicao: "; if (!(cin >> valor >> pos)) break;
            cout << (l.Inserir(valor, pos) ? "Inserido\n" : "Lista cheia ou posicao invalida\n");
        } else if (opc == 2) l.Imprimir();
        else if (opc == 3) {
            cout << "Valor: "; if (!(cin >> valor)) break;
            cout << "Posicao (-1 se ausente): " << l.Buscar(valor) << '\n';
        } else if (opc == 4) {
            cout << "Posicao: "; if (!(cin >> pos)) break;
            cout << (l.Excluir(pos) ? "Excluido\n" : "Posicao invalida\n");
        } else if (opc == 5) cout << "Tamanho: " << l.Tamanho() << "; vazia: " << l.Vazia() << '\n';
        else if (opc == 6) Demonstrar();
        else cout << "Opcao invalida\n";
    }
}
