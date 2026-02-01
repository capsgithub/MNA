// SolucionSumaArreglosParalela.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <omp.h>    // Librería para OpenMP

#define N 80000
#define chunk 200
#define mostrar 15


void imprimeArreglo(float* d);
using namespace std;

int main() {
    cout << "Suma de Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;
    double inicio, fin;


    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;

    inicio = omp_get_wtime();   // Tiempo de inicio

#pragma omp parallel for \
    shared(a, b, c, pedazos) private (i) \
schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(a);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
    imprimeArreglo(b);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
    imprimeArreglo(c);


    fin = omp_get_wtime();   // Tiempo de finalización

    // Mostrar número de hilos utilizados
#pragma omp parallel
    {
#pragma omp single
        {
            cout << "\nThreads utilizados: " << omp_get_num_threads() << endl;
            cout << "Tiempo de ejecucion (segundos): " << fin - inicio << endl;
        }
    }
}
    void imprimeArreglo(float* d)
    {
        for (int x = 0; x < mostrar; x++)
            cout << d[x] << " - ";
        cout << endl;
    }
    // Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
