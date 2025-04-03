// ConsoleApplication1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class PersonaManager {
private:
    struct Persona {
        int id;
        string nombre;
        int edad;
    };

public:
    void agregarPersona() {
        ofstream archivo("personas.txt", ios::app);
        Persona p;

        cout << "Ingrese ID: ";
        cin >> p.id;
        cin.ignore();

        cout << "Ingrese Nombre: ";
        getline(cin, p.nombre);

        cout << "Ingrese Edad: ";
        cin >> p.edad;

        if (archivo.is_open()) {
            archivo << p.id << "," << p.nombre << "," << p.edad << endl;
            archivo.close();
            cout << "Persona agregada exitosamente.\n";
        }
        else {
            cout << "Error al abrir el archivo.\n";
        }
    }

    static void mostrarPersonas() {
        ifstream archivo("personas.txt");
        string linea;

        if (archivo.is_open()) {
            cout << "\n--- LISTADO DE PERSONAS ---" << endl;
            while (getline(archivo, linea)) {
                size_t pos1 = linea.find(",");
                size_t pos2 = linea.find(",", pos1 + 1);

                string id = linea.substr(0, pos1);
                string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                string edad = linea.substr(pos2 + 1);

                cout << "ID: " << id << " | Nombre: " << nombre << " | Edad: " << edad << endl;
            }
            archivo.close();
        }
        else {
            cout << "Error al abrir el archivo o no existen registros.\n";
        }
    }

    static void buscarPersona(int idBuscado) {
        ifstream archivo("personas.txt");
        string linea;
        bool encontrado = false;

        while (getline(archivo, linea)) {
            size_t pos1 = linea.find(",");
            int id = stoi(linea.substr(0, pos1));

            if (id == idBuscado) {
                size_t pos2 = linea.find(",", pos1 + 1);
                string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                string edad = linea.substr(pos2 + 1);

                cout << "\nREGISTRO ENCONTRADO:" << endl;
                cout << "ID: " << id << endl;
                cout << "Nombre: " << nombre << endl;
                cout << "Edad: " << edad << endl;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Persona no encontrada.\n";
        }
        archivo.close();
    }

    static void eliminarPersona(int idEliminar) {
        ifstream archivo("personas.txt");
        ofstream temp("temp.txt");
        string linea;
        bool eliminado = false;

        if (archivo.is_open() && temp.is_open()) {
            while (getline(archivo, linea)) {
                size_t pos1 = linea.find(",");
                int id = stoi(linea.substr(0, pos1));

                if (id != idEliminar) {
                    temp << linea << endl;
                }
                else {
                    eliminado = true;
                }
            }

            archivo.close();
            temp.close();

            remove("personas.txt");
            rename("temp.txt", "personas.txt");

            if (eliminado) {
                cout << "Persona eliminada exitosamente.\n";
            }
            else {
                cout << "Persona no encontrada.\n";
            }
        }
        else {
            cout << "Error al abrir los archivos.\n";
        }
    }
};

int main() {
    PersonaManager manager;
    int opcion, id;

    do {
        cout << "\n=== GESTION DE PERSONAS ===" << endl;
        cout << "1. Agregar persona" << endl;
        cout << "2. Mostrar personas" << endl;
        cout << "3. Buscar persona" << endl;
        cout << "4. Eliminar persona" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            manager.agregarPersona();
            break;
        case 2:
            PersonaManager::mostrarPersonas();
            break;
        case 3:
            cout << "Ingrese ID a buscar: ";
            cin >> id;
            PersonaManager::buscarPersona(id);
            break;
        case 4:
            cout << "Ingrese ID a eliminar: ";
            cin >> id;
            PersonaManager::eliminarPersona(id);
            break;
        case 5:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
