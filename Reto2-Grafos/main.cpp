#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Variables globales: tamano del grafo, colores disponibles, Matriz de adyacencia, asignacion actual y primera solucion encontrada
int n, k;
int matriz_ady[20][20];
int color[20];
int primera_solucion[20];
long long total_soluciones = 0;
bool primera_guardada = false;

// Reinicia el estado global entre ejecuciones de distintos grafos
void reset_estado() {
    total_soluciones = 0;
    primera_guardada = false;
    for (int i = 0; i < 20; i++) color[i] = 0;
}

// Retorna true si el color c puede asignarse al vertice v sin conflictos.
bool es_seguro(int v, int c) {
    for (int u = 0; u < n; u++) {
        if (matriz_ady[v][u] == 1 && color[u] == c)
            return false;
    }
    return true;
}

// Backtracking: asigna colores vertice a vertice podando ramas con conflicto.
void bt(int v) {
    if (v == n) {
        total_soluciones++;
        if (!primera_guardada) {
            for (int i = 0; i < n; i++) primera_solucion[i] = color[i];
            primera_guardada = true;
        }
        return;
    }
    for (int c = 1; c <= k; c++) {
        if (es_seguro(v, c)) {
            color[v] = c;
            bt(v + 1);
            color[v] = 0; // backtrack
        }
    }
}

// Fuerza bruta: prueba las k^n combinaciones posibles y cuenta las validas.
long long fuerza_bruta() {
    long long conteo = 0;
    long long total_comb = (long long)pow(k, n);

    for (long long i = 0; i < total_comb; i++) {
        // Decodifica i en base k para obtener una asignacion de colores
        vector<int> intento(n);
        long long temp = i;
        for (int j = 0; j < n; j++) {
            intento[j] = (temp % k) + 1;
            temp /= k;
        }
        bool valida = true;
        for (int u = 0; u < n && valida; u++) {
            for (int v = u + 1; v < n && valida; v++) {
                if (matriz_ady[u][v] == 1 && intento[u] == intento[v])
                    valida = false;
            }
        }
        if (valida) conteo++;
    }
    return conteo;
}

struct Resultado {
    long long soluciones_bt;
    long long soluciones_fb;
    double tiempo_bt_us;
    double tiempo_fb_us;
};

// Carga el grafo, ejecuta ambos enfoques midiendo tiempos y reporta resultados
Resultado ejecutar_grafo(const string& nombre,
                         int _n, int _k,
                         int datos[][20],
                         bool imprimir_primera = true) {
    n = _n; k = _k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matriz_ady[i][j] = datos[i][j];

    cout << "=== " << nombre << " (n=" << n << ", k=" << k << ") ===" << endl;

    reset_estado();
    auto t0 = high_resolution_clock::now();
    bt(0);
    auto t1 = high_resolution_clock::now();
    long long sol_bt = total_soluciones;
    double us_bt = duration_cast<nanoseconds>(t1 - t0).count() / 1.0;

    if (sol_bt == 0) {
        cout << "No existe una " << k << "-coloracion valida (Backtracking)" << endl;
    } else {
        cout << "Total de " << k << "-coloraciones (Backtracking): " << sol_bt << endl;
        if (imprimir_primera) {
            cout << "Primera solucion: ";
            for (int i = 0; i < n; i++)
                cout << "color[" << i << "]=" << primera_solucion[i] << " ";
            cout << endl;
        }
    }

    auto t2 = high_resolution_clock::now();
    long long sol_fb = fuerza_bruta();
    auto t3 = high_resolution_clock::now();
    double us_fb = duration_cast<nanoseconds>(t3 - t2).count() / 1.0;

    cout << "Fuerza Bruta confirma: " << sol_fb << endl;
    cout << endl;

    return {sol_bt, sol_fb, us_bt, us_fb};
}

int main() {
    // Grafo 1: ciclo C4, numero cromatico = 2
    int g1[20][20] = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    auto r1 = ejecutar_grafo("Grafo 1: ciclo C4", 4, 3, g1);

    // Grafo 2: completo K5, numero cromatico = 5
    int g2[20][20] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };
    auto r2 = ejecutar_grafo("Grafo 2: completo K5", 5, 5, g2);

    cout << "\n--------------------------------------------------------\n";
    cout << "        TABLA COMPARATIVA DE TIEMPOS\n";
    cout << "--------------------------------------------------------\n";
    cout << "  Grafo          | Soluciones | BT (ns)    | FB (ns)\n";
    cout << "-----------------|------------|------------|------------\n";
    printf("  %-15s| %10lld | %10.2f | %10.2f\n", "C4 (n=4,k=3)", r1.soluciones_bt, r1.tiempo_bt_us, r1.tiempo_fb_us);
    printf("  %-15s| %10lld | %10.2f | %10.2f\n", "K5 (n=5,k=5)", r2.soluciones_bt, r2.tiempo_bt_us, r2.tiempo_fb_us);
    cout << "--------------------------------------------------------\n";

    return 0;
}
