<div align="center">

# UNIVERSIDAD EAFIT
## ANÁLISIS Y DISEÑO DE ALGORITMOS
### PRIMER TRABAJO PRÁCTICO

**Trabajo Práctico: Ejercicios de Fuerza Bruta y Backtracking en C++**

---
</div>

## Reto 1 — Permutaciones con Restricciones (fuerza bruta)

Dado un conjunto de **n** elementos distintos (enteros positivos), se desea generar todas las permutaciones posibles del conjunto que satisfagan la siguiente restricción: ningún elemento en la posición **i** puede ser mayor que el doble del elemento en la posición **i+1** (para **i = 0** hasta **n-2**). Es decir, para toda permutación válida **P** debe cumplirse:

<div align="center">

**P[i] <= 2 * P[i+1] para todo i en {0, 1, ..., n-2}**

</div>

El programa debe:

* **(a)** Generar **TODAS** las permutaciones del conjunto mediante fuerza bruta (enumeración exhaustiva mediante el factorial de permutaciones).
* **(b)** Filtrar las que cumplen la restricción.
* **(c)** Reportar el total de permutaciones generadas y el total de permutaciones válidas, y listar estas últimas.

---

**Pseudocodigo**

```text
Ordenar(A)
    
total_generadas = 0
total_validas = 0

Hacer:
    total_generadas = total_generadas + 1
    valida = Verdadero
        
    Para i desde 0 hasta longitud(A) - 2:
        Si A[i] > 2 * A[i+1]:
            valida = Falso
            Romper ciclo
        
    Si valida es Verdadero:
        total_validas = total_validas + 1
        Si imprimir_listado es Verdadero:
            Para cada elemento x en A:
                Imprimir x
            Imprimir nueva línea
                
Mientras siguiente_permutacion(A) sea Verdadero

Imprimir total_generadas
Imprimir total_validas
```

---

**1. Implementar la generación de todas las permutaciones usando la función next_permutation de la STL o un algoritmo propio basado en fuerza bruta recursiva. Justificar brevemente la elección.**

Escogimos `next_permutation` ya que, al ser parte de la biblioteca estándar de C++, su implementación está mejor optimizada de lo que estaría una función recursiva realizada por nosotros mismos. Es más limpia y organizada que una función recursiva primitiva y garantiza el recorrido y creación de todas las permutaciones posibles, las cuales son necesarias para el enfoque de Fuerza Bruta.

---

**2. Aplicar el filtro de restricción P[i] <= 2 * P[i + 1] a cada permutación generada e imprimir solo las válidas.**

```cpp
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
```

---

**3. Reportar: el total de permutaciones generadas (¡debe ser n!), el total de permutaciones válidas y el listado de estas.**

```cpp
cout << "total_generadas = " << total_generadas << "\n";
cout << "total_validas   = " << total_validas << "\n";
```

### Ejemplo de Ejecución

**Entrada:** n = 6, A = {1, 2, 3, 5, 8, 13}

**Listado de permutaciones válidas:**

```text
1 2 3 5 8 13 
1 2 3 5 13 8 
1 2 3 8 5 13 
1 2 3 13 8 5 
1 2 5 3 8 13 
1 2 5 3 13 8 
1 2 8 5 3 13 
1 2 13 8 5 3 
1 3 2 5 8 13 
1 3 2 5 13 8 
1 3 2 8 5 13 
1 3 2 13 8 5 
1 5 3 2 8 13 
1 5 3 2 13 8 
1 8 5 3 2 13 
1 13 8 5 3 2 
2 1 3 5 8 13 
2 1 3 5 13 8 
2 1 3 8 5 13 
2 1 3 13 8 5 
2 1 5 3 8 13 
2 1 5 3 13 8 
2 1 8 5 3 13 
2 1 13 8 5 3 
3 2 1 5 8 13 
3 2 1 5 13 8 
3 2 1 8 5 13 
3 2 1 13 8 5 
5 3 2 1 8 13 
5 3 2 1 13 8 
8 5 3 2 1 13 
13 8 5 3 2 1
```
Estadísticas finales:
- Total generadas: 720
- Total válidas: 32
- Tiempo de ejecución: 0.1345 ms

---

**4. Explicar por qué este enfoque se clasifica como Fuerza Bruta y no como Backtracking.**

Este enfoque se clasifica como **Fuerza Bruta** porque el algoritmo **genera por completo todas soluciones posibles**, pese a que algunas no sean validas. Solamente se evalua si funcionan o no **después** de generar una permutación por completo, sin importar si a medio camino se encontro que no era valida.

Si fuera **Backtracking**, el algoritmo iría generando la permutación elemento por elemento. En el momento en que se inserta un número en la posición **i+1** y se detecta que **P[i] > 2 * P[i+1]**, el algoritmo podaría esa rama y no seguiría agregando elementos para completar esa permutación.

---

**5. Analizar la complejidad temporal y espacial del algoritmo implementado.**

**Complejidad Temporal: O(n * n!)**

El ciclo `do-while` se ejecuta exactamente **n!** veces (el factorial del número de elementos). Dentro del ciclo, el bucle `for` que verifica la condición recorre hasta **n-1** elementos en el peor de los casos. Por lo tanto, el tiempo de ejecución crece a una tasa de **n * n!**.

**Complejidad Espacial: O(n)**

El algoritmo requiere un espacio de **n** en memoria, siendo **n** la cantidad de elementos del arreglo que vamos a permutar, puesto que cada iteración de las permutaciones que generamos con `next_permutation` no se almacenan en memoria, sino que trabaja siempre con el mismo vector.

---

**Medida de tiempos experimentales**

| n | Permutaciones | Validas | Tiempo (ms) |
| :--- | :--- | :--- | :--- |
| 5 | 120 | 36 | 0.05 |
| 8 | 40320 | 2880 | 11.52 |
| 10 | 3628800 | 86400 | 353.37 |
| 11 | 39916800 | 518400 | 3541.45 |
| 12 | 479001600 | 3628800 | 42901.46 |
| 13 | 6227020800 | 25401600 | 554606.25 |

Basándonos en los resultados obtenidos hasta n = 13, y con ayuda del agente de IA Gemini, llegamos a la conclusión de que comenzaría a ser inviable alrededor de n = 14 (tardando aproximadamente 2.15 horas) o n = 15 (tardando alrededor de 32.3 horas).

---

**Preguntas guia**

**¿Qué ocurre con la proporción de permutaciones válidas respecto al total a medida que n crece?**

A medida que n crece, la proporción de permutaciones válidas respecto al total disminuye drásticamente, acercándose a cero. Esto se debe a que el total de permutaciones crece de forma factorial, mientras que la restricción P[i] <= 2 * P[i+1] debe cumplirse en los n-1 pares consecutivos de cada permutación: basta con que un solo par la viole para que toda la permutación sea inválida, y con más elementos y pares a verificar, la probabilidad de que todos se cumplan simultáneamente se vuelve cada vez menor.

**Mejora con Backtracking (poda temprana) y construcción del árbol**

Si se diseñara una solución con Backtracking, el árbol de búsqueda no se construiría generando arreglos completos al final, sino que se iría construyendo de forma incremental.

La validación ocurriría justo en el momento de intentar insertar un nuevo candidato en la posición i+1:

* Hay un número en la posición i.
* Ponemos un número que no hayamos usado aún en la posición i+1.
* Antes de continuar con i+2, verificamos si P[i] <= 2 * P[i+1].
* Si la condición no se cumple, se poda esa rama, descartando futuras permutaciones que vayan a tener esa combinación y no generando ramas hijas, retrocediendo y probando otro número disponible.

**¿Por qué se garantiza que next_permutation genera exactamente n! permutaciones si el arreglo está ordenado inicialmente?**

La función `next_permutation` de C++ opera bajo el principio de orden lexicográfico. Al ordenar el arreglo de forma ascendente antes de empezar, nos aseguramos de comenzar en la permutación más pequeña posible. Cada vez que se llama a `next_permutation`, el algoritmo reorganiza los elementos para formar la siguiente permutación inmediatamente más grande.

Como el algoritmo recorre todas las combinaciones sin saltarse ninguna, y se detiene automáticamente al llegar a la permutación más grande posible (es decir, el arreglo en orden descendente), se garantiza que pasará por cada uno de los n! estados únicos que tiene un conjunto de n elementos distintos.

---

## Reto 2 — Coloración de Grafos con k Colores (Backtracking)

La coloración de grafos es un problema clásico de teoría de grafos con aplicaciones reales en asignación de frecuencias de radio, horarios de exámenes, registro de variables en compiladores, entre otros. Dado un grafo no dirigido **G = (V, E)** con **n** vértices y **m** aristas, y un número entero **k** de colores disponibles, se desea determinar si existe una asignación de colores a los vértices tal que ningún par de vértices adyacentes comparta el mismo color. A esto se le llama una **k-coloración válida**.

La representación del grafo se realizará mediante una matriz de adyacencia. Los vértices se numeran de **0** a **n-1** y los colores de **1** a **k**.

---

**Pseudocodigo**

```text
Funcion es_seguro(v, c):
    Para u desde 0 hasta n - 1:
        Si matriz_ady[v][u] es igual a 1 y color[u] es igual a c:
            Retornar Falso
    Retornar Verdadero

Funcion backtracking(v):
    Si v es igual a n:
        total_soluciones = total_soluciones + 1
        Si primera_guardada es Falso:
            Para i desde 0 hasta n - 1:
                primera_solucion[i] = color[i]
            primera_guardada = Verdadero
        Retornar

    Para c desde 1 hasta k:
        Si es_seguro(v, c) es Verdadero:
            color[v] = c
            backtracking(v + 1)
            color[v] = 0
```

---

**1. Implementar el algoritmo de Backtracking que intenta asignar colores uno a uno a cada vértice, podando la búsqueda cuando se detecta un conflicto (dos vértices adyacentes con el mismo color).**

```cpp
bool es_seguro(int v, int c) {
    for (int u = 0; u < n; u++) {
        if (matriz_ady[v][u] == 1 && color[u] == c)
            return false;
    }
    return true;
}

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
            color[v] = 0;
        }
    }
}
```

---

**2. Imprimir la primera coloración válida encontrada (si existe), en el formato: "color[v] = c" para cada vértice v.**

```cpp
if (total_soluciones == 0) {
    cout << "No existe una " << k << "-coloracion valida" << endl;
} else {
    cout << "Total de " << k << "-coloraciones: " << total_soluciones << endl;
    cout << "Primera solucion:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "color[" << i << "]=" << primera_solucion[i] << " ";
    }
    cout << endl;
}
```

---

**3. Contar e imprimir el número total de k-coloraciones válidas distintas del grafo.**

```cpp
if (v == n) {
    total_soluciones++;
    if (!primera_guardada) {
        for (int i = 0; i < n; i++) primera_solucion[i] = color[i];
        primera_guardada = true;
    }
    return;
}

cout << "Total de " << k << "-coloraciones: " << total_soluciones << endl;
```

---

**4. Implementar e imprimir la solución por Fuerza Bruta (probar las k^n combinaciones posibles) y verificar que ambas arrojen el mismo conteo total.**

```cpp
long long fuerza_bruta() {
    long long conteo = 0;
    long long total_comb = pow(k, n);
    
    for (long long i = 0; i < total_comb; i++) {
        vector<int> intento(n);
        long long temp = i;
        
        for (int j = 0; j < n; j++) {
            intento[j] = (temp % k) + 1;
            temp /= k;
        }

        bool valida = true;
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) {
                if (matriz_ady[u][v] == 1 && intento[u] == intento[v]) {
                    valida = false;
                    break;
                }
            }
            if (!valida) break;
        }
        if (valida) conteo++;
    }
    return conteo;
}

cout << "Fuerza Bruta confirma: " << fuerza_bruta() << endl;
```

---

**5. Comparar el tiempo de ejecución de ambos enfoques (Backtracking vs Fuerza Bruta) en al menos 2 grafos distintos. Presentar una tabla con los resultados.**

**TABLA COMPARATIVA DE TIEMPOS**

| Grafo | Soluciones | Backtracking (ns) | Fuerza Bruta (ns) |
| :--- | :--- | :--- | :--- |
| C4 (n=4, k=3) | 18 | 3323.00 | 37076.00 |
| K5 (n=5, k=5) | 120 | 36152.00 | 661498.00 |

---

**6. Analizar la complejidad temporal y espacial de ambos enfoques y elaborar conclusiones sobre la efectividad de la poda**

---

**Preguntas Guia**

**¿Cuántos nodos explora el Backtracking vs la Fuerza Bruta en el ejemplo anterior? Justifique.**

En el ejemplo del ciclo C4 (n=4, k=3):

* **Fuerza Bruta:** Explora exactamente k^n = 3^4 = 81 combinaciones. No importa si el grafo tiene muchas aristas o ninguna; la fuerza bruta siempre revisa todas las posibilidades hasta el final para ver si son válidas.
* **Backtracking:** Explora significativamente menos de 81 nodos, porque el Backtracking funciona con poda. Por ejemplo, si al nodo 0 le asigna el color 1 y al nodo 1 (adyacente) también le asigna el 1, el algoritmo detecta el conflicto inmediatamente y no intenta colorear los nodos 2 y 3 para esa rama. Esto elimina 9 combinaciones (3^2) de un solo golpe.

**¿Qué tipo de grafo maximizaría el efecto de la poda en el Backtracking? ¿Y cuál lo minimizaría?**

La efectividad de la poda depende totalmente de la **densidad del grafo** (número de aristas):

* **Maximiza la poda:** En un grafo donde todos están conectados con todos, los conflictos aparecen muy rápido y muy arriba en el árbol de decisión. El Backtracking descarta ramas enteras casi de inmediato.
* **Minimiza la poda:** En un grafo sin aristas (grafo nulo), no existe ninguna restricción de coloración ya que ningún par de vértices es adyacente. Por eso, cualquier asignación de colores es válida y la función `es_seguro` retorna `true` en todo momento. El Backtracking nunca encuentra un conflicto que justifique podar una rama, por lo que recorre el árbol completo de decisión sin descartar ningún camino, explorando las k^n combinaciones posibles, comportándose de forma idéntica a la Fuerza Bruta.

**¿Qué cambio se debe hacer al algoritmo si solo se quiere saber si existe al menos una k-coloración, sin contar todas?**

Para que esto funcione en la lógica de Backtracking, se debe implementar una **cadena de confirmación**:

* **Condición de Salida:** Cuando el algoritmo colorea el último vértice con éxito, en lugar de solo sumar 1, envía un mensaje avisando que la solución es valida.
* **Verificación en Cascada:** Cada nivel de la recursión debe estar atento a ese mensaje.
    * **Si el vértice v+1 responde con una solucion valida**, el vértice v deja de probar otros colores y envía el mismo mensaje a su propio "padre".
    * **Si el vértice v+1 responde con una solución no valida**, el vertice v continúa probando el siguiente color disponible.

---
