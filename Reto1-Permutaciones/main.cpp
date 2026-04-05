#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

// Almacena el conteo de permutaciones generadas, validas y el tiempo de ejecucion
struct Resultado {
    long long total_generadas;
    long long total_validas;
    double tiempo_ms;
};

// Genera todas las n! permutaciones de A, filtra las validas y mide el tiempo.
Resultado resolverPermutaciones(vector<int> A, bool imprimir_listado) {
    sort(A.begin(), A.end()); // ordena para comenzar desde la permutacion menor

    long long total_generadas = 0;
    long long total_validas = 0;

    auto inicio = chrono::high_resolution_clock::now();

    do {
        total_generadas++;
        bool valida = true;

        // Verifica la restriccion P[i] <= 2 * P[i+1] para toda la permutacion
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

    auto fin = chrono::high_resolution_clock::now();
    double tiempo_ms = chrono::duration<double, milli>(fin - inicio).count();

    cout << "total_generadas = " << total_generadas << "\n";
    cout << "total_validas   = " << total_validas << "\n";
    cout << "Tiempo: " << tiempo_ms << " ms\n\n";

    return {total_generadas, total_validas, tiempo_ms};
}

int main() {
    // Ejemplo base del enunciado
    vector<int> A = {1, 3, 4};
    cout << "Entrada: n = " << A.size() << ", A = {1, 3, 4}\n \n";
    resolverPermutaciones(A, true);

    // Medicion experimental con distintos valores de n
    cout << "Medicion experimental de tiempos\n";
    vector<int> valores_n = {5, 8, 10, 11, 12, 13};
    vector<Resultado> resultados;

    for (int n : valores_n) {
        vector<int> conjunto(n);
        for (int i = 0; i < n; i++) conjunto[i] = i + 1;

        long long fact = 1;
        for (int i = 1; i <= n; i++) fact *= i;
        cout << "\nn = " << n << " (n! = " << fact << ")\n";

        resultados.push_back(resolverPermutaciones(conjunto, false));
    }

    // Tabla resumen de tiempos para cada valor de n
    cout << "\n------------------------------------------\n";
    cout << "          TABLA RESUMEN DE TIEMPOS        \n";
    cout << "------------------------------------------\n";
    cout << "  n  | Permutaciones |  Validas | Tiempo (ms)\n";
    cout << "-----|---------------|----------|------------\n";
    for (size_t i = 0; i < valores_n.size(); i++) {
        printf("  %-2d | %13lld | %8lld | %10.2f\n",
               valores_n[i],
               resultados[i].total_generadas,
               resultados[i].total_validas,
               resultados[i].tiempo_ms);
    }
    cout << "------------------------------------------\n";

    return 0;
}
