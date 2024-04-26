#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char *nombre_archivo = "notas.dat";

struct Estudiante {
    int id;
    char nombres[50];
    char apellidos[50];
    float notas[4];
    float promedio;
    bool aprobado;
};

void Leer() {
    ifstream archivo(nombre_archivo, ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    Estudiante estudiante;
    int id = 0; // Índice o posición del registro (fila) dentro del archivo
    cout << "________________________________________________" << endl;
    cout << "ID" << "|" << "Nombres" << "|" << "Apellidos" << "|" << "Nota1" << "|" << "Nota2" << "|" << "Nota3" << "|" << "Nota4" << "|" << "Promedio" << "|" << "Resultado" << endl;
    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        cout << id << "|" << estudiante.nombres << "|" << estudiante.apellidos << "|" << estudiante.notas[0] << "|" << estudiante.notas[1] << "|" << estudiante.notas[2] << "|" << estudiante.notas[3] << "|" << estudiante.promedio << "|" << (estudiante.aprobado ? "Aprobado" : "Reprobado") << endl;
        id += 1;
    }
    archivo.close();
}

void Crear() {
    ofstream archivo(nombre_archivo, ios::binary | ios::app);
    char res;
    Estudiante estudiante;
    do {
        cout << "Ingrese el ID del estudiante: ";
        cin >> estudiante.id;
        cin.ignore();

        cout << "Ingrese los nombres del estudiante: ";
        cin.getline(estudiante.nombres, 50);

        cout << "Ingrese los apellidos del estudiante: ";
        cin.getline(estudiante.apellidos, 50);

        cout << "Ingrese las notas del estudiante (Nota1 Nota2 Nota3 Nota4): ";
        for (int i = 0; i < 4; ++i) {
            cin >> estudiante.notas[i];
        }

        // Calcular el promedio
        float suma = 0;
        for (int i = 0; i < 4; ++i) {
            suma += estudiante.notas[i];
        }
        estudiante.promedio = suma / 4;

        // Determinar si el estudiante aprobó o reprobó
        estudiante.aprobado = (estudiante.promedio >= 60);

        archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));

        cout << "Desea ingresar otro estudiante (s/S para sí): ";
        cin >> res;
    } while (res == 's' || res == 'S');
    archivo.close();
    Leer(); // Mostrar el contenido después de crear
}

void Actualizar() {
    fstream archivo(nombre_archivo, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    int id;
    cout << "Ingrese el ID del estudiante que desea actualizar: ";
    cin >> id;
    cin.ignore();

    archivo.seekg(id * sizeof(Estudiante), ios::beg);
    Estudiante estudiante;
    archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));

    cout << "Ingrese los nombres del estudiante: ";
    cin.getline(estudiante.nombres, 50);

    cout << "Ingrese los apellidos del estudiante: ";
    cin.getline(estudiante.apellidos, 50);

    cout << "Ingrese las notas del estudiante (Nota1 Nota2 Nota3 Nota4): ";
    for (int i = 0; i < 4; ++i) {
        cin >> estudiante.notas[i];
    }

    // Calcular el promedio
    float suma = 0;
    for (int i = 0; i < 4; ++i) {
        suma += estudiante.notas[i];
    }
    estudiante.promedio = suma / 4;

    // Determinar si el estudiante aprobó o reprobó
    estudiante.aprobado = (estudiante.promedio >= 60);

    archivo.seekp(id * sizeof(Estudiante), ios::beg);
    archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));

    archivo.close();
    Leer(); // Mostrar el contenido después de actualizar
}

void Borrar() {
    fstream archivo(nombre_archivo, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    fstream archivo_temp("temp.dat", ios::binary | ios::out);
    if (!archivo_temp) {
        cout << "No se pudo abrir el archivo temporal." << endl;
        return;
    }
    int id;
    cout << "Ingrese el ID del estudiante que desea borrar: ";
    cin >> id;

    archivo.seekg(0, ios::beg);
    while (!archivo.eof()) {
        Estudiante estudiante;
        archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        if (estudiante.id != id && !archivo.eof()) {
            archivo_temp.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        }
    }

    archivo.close();
    archivo_temp.close();

    remove(nombre_archivo);
    rename("temp.dat", nombre_archivo);

    Leer(); // Mostrar el contenido después de borrar
}

int main() {
    char opcion;
    do {
        cout << "\nSeleccione una opcion:" << endl;
        cout << "1. Crear estudiante" << endl;
        cout << "2. Leer estudiantes" << endl;
        cout << "3. Actualizar estudiante" << endl;
        cout << "4. Borrar estudiante" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case '1':
                Crear();
                break;
            case '2':
                Leer();
                break;
            case '3':
                Actualizar();
                break;
            case '4':
                Borrar();
                break;
            case '5':
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != '5');

    return 0;
}

