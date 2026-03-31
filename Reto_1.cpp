#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void resolverPermutaciones(vector<int> A, bool imprimir_listado) {
    sort(A.begin(), A.end());
    
    long long total_generadas = 0;
    long long total_validas = 0;

    do {
        total_generadas++;
        bool valida = true;
        
        for (size_t i = 0; i < A.size() - 1; ++i) {
            if (A[i] > 2 * A[i+1]) {
                valida = false;
                break;
            }
        }
        
        if (valida) {
            total_validas++;
            if (imprimir_listado) {
                for (int x : A) {
                    cout << x << " ";
                }
                cout << "\n";
            }
        }
    } while (next_permutation(A.begin(), A.end()));

    cout << "total_generadas = " << total_generadas << "\n";
    cout << "total_validas   = " << total_validas << "\n";
}

int main() {
    vector<int> A = {1, 3, 4};
    cout << "Entrada: n = " << A.size() << ", A = {1, 3, 4}\n";
    resolverPermutaciones(A, true);
    
    return 0;
}