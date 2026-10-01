// Pratica reconstruida com base na Aula 1: modularizacao e recursividade.
// Compilar: g++ -std=c++17 Aula1_Recursividade.cpp -o aula1
#include <iostream>
#include <string>
using namespace std;

// Caso base: 0! = 1. Passo recursivo: n! = n * (n-1)!.
long long Fatorial(int n) {
    if (n == 0) return 1;
    return n * Fatorial(n - 1);
}
long long SomaN(int n) {
    if (n == 0) return 0;
    return n + SomaN(n - 1);
}
// n e a QUANTIDADE de pares positivos: n=5 soma 2+4+6+8+10.
long long SomaPrimeirosPares(int n) {
    if (n == 0) return 0;
    return 2LL * n + SomaPrimeirosPares(n - 1);
}
long long SomaXY(int x, int y) {
    if (y == 0) return x;
    if (y > 0) return 1 + SomaXY(x, y - 1);
    return SomaXY(x, y + 1) - 1;
}
// O vetor deve estar ordenado. Retorna indice (base zero) ou -1.
int BuscaBinaria(const int v[], int inicio, int fim, int x) {
    if (inicio > fim) return -1;
    int meio = inicio + (fim - inicio) / 2;
    if (v[meio] == x) return meio;
    if (x < v[meio]) return BuscaBinaria(v, inicio, meio - 1, x);
    return BuscaBinaria(v, meio + 1, fim, x);
}
void Demonstrar() {
    int v[] = {2, 4, 6, 8, 10, 12};
    cout << "Fatorial(4): " << Fatorial(4) << '\n';
    cout << "SomaN(5): " << SomaN(5) << '\n';
    cout << "Soma dos 5 primeiros pares: " << SomaPrimeirosPares(5) << '\n';
    cout << "SomaXY(4, 5): " << SomaXY(4, 5) << '\n';
    cout << "Indice do 8: " << BuscaBinaria(v, 0, 5, 8) << '\n';
    cout << "Busca de 9 (ausente): " << BuscaBinaria(v, 0, 5, 9) << '\n';
}
int main(int argc, char* argv[]) {
    if (argc > 1 && string(argv[1]) == "--demo") { Demonstrar(); return 0; }
    cout << "AULA 1 - RECURSIVIDADE\n";
    Demonstrar();
    int opc, n, x, y;
    while (true) {
        cout << "\n1 Fatorial | 2 Soma de 1 a n | 3 Primeiros n pares\n"
             << "4 Soma de x e y | 5 Busca binaria | 0 Sair\nOpcao: ";
        if (!(cin >> opc) || opc == 0) break;
        if (opc >= 1 && opc <= 3) {
            cout << "n: "; if (!(cin >> n)) break;
            // Limites para evitar estouro do fatorial e recursao muito profunda.
            if (n < 0 || n > (opc == 1 ? 20 : 1000)) {
                cout << "n fora do intervalo permitido.\n"; continue;
            }
            if (opc == 1) cout << Fatorial(n) << '\n';
            if (opc == 2) cout << SomaN(n) << '\n';
            if (opc == 3) cout << SomaPrimeirosPares(n) << '\n';
        } else if (opc == 4) {
            cout << "x e y: "; if (!(cin >> x >> y)) break;
            if (y < -1000 || y > 1000) { cout << "Use y entre -1000 e 1000.\n"; continue; }
            cout << SomaXY(x, y) << '\n';
        } else if (opc == 5) {
            int v[] = {2, 4, 6, 8, 10, 12};
            cout << "Vetor: 2 4 6 8 10 12. Valor: "; if (!(cin >> x)) break;
            cout << "Indice (-1 se ausente): " << BuscaBinaria(v, 0, 5, x) << '\n';
        } else cout << "Opcao invalida.\n";
    }
}
