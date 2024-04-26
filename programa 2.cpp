#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
    int id;
    string nombres;
    string apellidos;
    float notas[4];
    float promedio;
    bool aprobado;
};

void ingresarEstudiantes(Estudiante* estudiantes, int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        cout << "Ingrese el ID del estudiante " << i + 1 << ": ";
        cin >> (estudiantes + i)->id;
        cin.ignore(); // Limpiar el buffer del teclado
        cout << "Ingrese los nombres del estudiante " << i + 1 << ": ";
        getline(cin, (estudiantes + i)->nombres);
        cout << "Ingrese los apellidos del estudiante " << i + 1 << ": ";
        getline(cin, (estudiantes + i)->apellidos);
        cout << "Ingrese las notas del estudiante " << i + 1 << " (Nota1 Nota2 Nota3 Nota4): ";
        for (int j = 0; j < 4; ++j) {
            cin >> (estudiantes + i)->notas[j];
        }
        // Calcular el promedio
        float suma = 0;
        for (int j = 0; j < 4; ++j) {
            suma += (estudiantes + i)->notas[j];
        }
        (estudiantes + i)->promedio = suma / 4;

        // Determinar si el estudiante aprobó o reprobó
        if ((estudiantes + i)->promedio >= 60) {
            (estudiantes + i)->aprobado = true;
        } else {
            (estudiantes + i)->aprobado = false;
        }
    }
}

void mostrarResultados(Estudiante* estudiantes, int cantidad) {
    cout << "\nResultados:\n";
    for (int i = 0; i < cantidad; ++i) {
        cout << "Estudiante " << i + 1 << ": " << (estudiantes + i)->nombres << " " << (estudiantes + i)->apellidos << endl;
        cout << "Promedio: " << (estudiantes + i)->promedio << endl;
        if ((estudiantes + i)->aprobado) {
            cout << "Estado: Aprobado" << endl;
        } else {
            cout << "Estado: Reprobado" << endl;
        }
        cout << endl;
    }
}

int main() {
    int N;
    cout << "Ingrese el número de estudiantes: ";
    cin >> N;

    Estudiante* estudiantes = new Estudiante[N];

    ingresarEstudiantes(estudiantes, N);
    mostrarResultados(estudiantes, N);

    // Liberar memoria
    delete[] estudiantes;

    return 0;
}
