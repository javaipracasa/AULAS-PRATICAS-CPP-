// Pratica reconstruida com base na Aula 5: arvore binaria de busca.
// Exercicio do PDF: catalogo em memoria, ordenado pelo nome do arquivo.
// As exclusoes removem registros do catalogo, nao arquivos do computador.
#include <iostream>
#include <string>
using namespace std;
struct No {
    string nome;
    int data; // Inteiro AAAAMMDD: 20260930 representa 30/09/2026.
    No* esq;
    No* dir;
};
bool NomeValido(const string& nome) {
    if (nome.empty() || nome.size() > 8) return false;
    for (unsigned char c : nome) {
        // ASCII imprimivel sem espacos nem acentos.
        if (c < 33 || c > 126) return false;
    }
    return true;
}
bool DataValida(int data) {
    int ano = data / 10000, mes = data / 100 % 100, dia = data % 100;
    if (ano < 1 || ano > 9999 || mes < 1 || mes > 12) return false;
    int dias[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) dias[2] = 29;
    return dia >= 1 && dia <= dias[mes];
}
No* Inserir(No* raiz, const string& nome, int data) {
    if (raiz == nullptr) return new No{nome, data, nullptr, nullptr};
    if (nome < raiz->nome) raiz->esq = Inserir(raiz->esq, nome, data);
    else if (nome > raiz->nome) raiz->dir = Inserir(raiz->dir, nome, data);
    else raiz->data = data; // Nome repetido atualiza a data; nao cria duplicata.
    return raiz;
}
No* Buscar(No* raiz, const string& nome) {
    if (raiz == nullptr || raiz->nome == nome) return raiz;
    if (nome < raiz->nome) return Buscar(raiz->esq, nome);
    return Buscar(raiz->dir, nome);
}
void Mostrar(No* p) { cout << p->nome << " (" << p->data << ") "; }
void PreOrdem(No* r) {
    if (r == nullptr) return;
    Mostrar(r); PreOrdem(r->esq); PreOrdem(r->dir);
}
void EmOrdem(No* r) {
    if (r == nullptr) return;
    EmOrdem(r->esq); Mostrar(r); EmOrdem(r->dir);
}
void PosOrdem(No* r) {
    if (r == nullptr) return;
    PosOrdem(r->esq); PosOrdem(r->dir); Mostrar(r);
}
No* Excluir(No* r, const string& nome) {
    if (r == nullptr) return nullptr;
    if (nome < r->nome) r->esq = Excluir(r->esq, nome);
    else if (nome > r->nome) r->dir = Excluir(r->dir, nome);
    else {
        // Zero ou um filho: o filho existente ocupa o lugar do no removido.
        if (r->esq == nullptr) {
            No* filho = r->dir; delete r; return filho;
        }
        if (r->dir == nullptr) {
            No* filho = r->esq; delete r; return filho;
        }
        // Dois filhos: copia o menor da direita (sucessor) e remove o original.
        No* sucessor = r->dir;
        while (sucessor->esq != nullptr) sucessor = sucessor->esq;
        r->nome = sucessor->nome;
        r->data = sucessor->data;
        r->dir = Excluir(r->dir, r->nome);
    }
    return r;
}
No* ExcluirAnteriores(No* r, int limite) {
    if (r == nullptr) return nullptr;
    // Pos-ordem: trata os filhos primeiro para nao acessar um no ja liberado.
    r->esq = ExcluirAnteriores(r->esq, limite);
    r->dir = ExcluirAnteriores(r->dir, limite);
    if (r->data < limite) {
        string nome = r->nome;
        return Excluir(r, nome);
    }
    return r;
}
int Tamanho(No* r) {
    if (r == nullptr) return 0;
    return 1 + Tamanho(r->esq) + Tamanho(r->dir);
}
// Altura em arestas: arvore vazia=-1; folha=0.
int Altura(No* r) {
    if (r == nullptr) return -1;
    int e = Altura(r->esq), d = Altura(r->dir);
    return 1 + (e > d ? e : d);
}
void Liberar(No* r) {
    if (r == nullptr) return;
    Liberar(r->esq); Liberar(r->dir); delete r;
}
void Demonstrar() {
    No* raiz = nullptr;
    raiz = Inserir(raiz, "notas", 20260930);
    raiz = Inserir(raiz, "aula", 20260801);
    raiz = Inserir(raiz, "video", 20260920);
    raiz = Inserir(raiz, "foto", 20260901);
    raiz = Inserir(raiz, "texto", 20260701);
    raiz = Inserir(raiz, "zeta", 20260925);
    cout << "Em ordem: "; EmOrdem(raiz); cout << '\n';
    cout << "Pre-ordem: "; PreOrdem(raiz); cout << '\n';
    cout << "Pos-ordem: "; PosOrdem(raiz); cout << '\n';
    cout << "Tamanho: " << Tamanho(raiz) << "; altura: " << Altura(raiz) << '\n';
    cout << "Busca foto: " << (Buscar(raiz, "foto") != nullptr) << '\n';
    // Remove raiz com dois filhos, depois registro com um filho e uma folha.
    raiz = Excluir(raiz, "notas");
    raiz = Excluir(raiz, "aula");
    raiz = Excluir(raiz, "zeta");
    cout << "Depois das exclusoes por nome: "; EmOrdem(raiz); cout << '\n';
    raiz = ExcluirAnteriores(raiz, 20260901);
    cout << "Mantidos a partir de 20260901 (inclusive): "; EmOrdem(raiz); cout << '\n';
    raiz = ExcluirAnteriores(raiz, 20270101);
    cout << "Depois de remover todos: tamanho=" << Tamanho(raiz) << '\n';
    Liberar(raiz);
}
int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") { Demonstrar(); return 0; }
    No* raiz = nullptr; int opc, data; string nome;
    cout << "AULA 5 - CATALOGO EM ARVORE BINARIA DE BUSCA\n";
    while (true) {
        cout << "\n1 Inserir/atualizar | 2 Em ordem | 3 Pre-ordem | 4 Pos-ordem\n"
             << "5 Buscar | 6 Excluir por nome | 7 Excluir anteriores a data\n"
             << "8 Tamanho/altura | 9 Demonstracao | 0 Sair\nOpcao: ";
        if (!(cin >> opc) || opc == 0) break;
        if (opc == 1) {
            cout << "Nome (ate 8 caracteres) e data AAAAMMDD: ";
            if (!(cin >> nome >> data)) break;
            if (!NomeValido(nome) || !DataValida(data)) cout << "Nome ou data invalida\n";
            else raiz = Inserir(raiz, nome, data);
        } else if (opc >= 2 && opc <= 4) {
            if (raiz == nullptr) cout << "Catalogo vazio";
            if (opc == 2) EmOrdem(raiz);
            if (opc == 3) PreOrdem(raiz);
            if (opc == 4) PosOrdem(raiz);
            cout << '\n';
        } else if (opc == 5 || opc == 6) {
            cout << "Nome: "; if (!(cin >> nome)) break;
            No* p = Buscar(raiz, nome);
            if (p == nullptr) cout << "Ausente\n";
            else if (opc == 5) { Mostrar(p); cout << '\n'; }
            else { raiz = Excluir(raiz, nome); cout << "Excluido\n"; }
        } else if (opc == 7) {
            cout << "Data limite AAAAMMDD: "; if (!(cin >> data)) break;
            if (!DataValida(data)) { cout << "Data invalida\n"; continue; }
            int antes = Tamanho(raiz);
            raiz = ExcluirAnteriores(raiz, data);
            cout << "Registros removidos: " << antes - Tamanho(raiz) << '\n';
        } else if (opc == 8) cout << "Tamanho: " << Tamanho(raiz) << "; altura: " << Altura(raiz) << '\n';
        else if (opc == 9) Demonstrar();
        else cout << "Opcao invalida\n";
    }
    Liberar(raiz);
}
