// reapso_codigo_2do_parcail.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class PersonaManager {
private:
    string nombre;
    int id;
    int edad;

public:
    PersonaManager(string n, int i, int e) : nombre(n), id(i), edad(e) {}

    void guardarEnArchivo() {
        ofstream archivo("personas.txt", ios::app);
        if (archivo.is_open()) {
            archivo << id << " " << nombre << " " << edad << endl;
            archivo.close();
            cout << "Persona agregada exitosamente.\n";
        }
        else {
            cout << "Error al abrir el archivo.\n";
        }
    }

    static void leerDesdeArchivo() {
        ifstream archivo("personas.txt");
        int id, edad;
        string nombre;

        if (archivo.is_open()) {
            cout << "\n--- LISTADO DE PERSONAS ---" << endl;
            while (archivo >> id >> nombre >> edad) {
                cout << "ID: " << id << " | Nombre: " << nombre << " | Edad: " << edad << endl;
            }
            archivo.close();
        }
        else {
            cout << "Error al abrir el archivo o no existen registros.\n";
        }
    }

    static void actualizarPersona(int idBuscar, string nuevoNombre, int nuevaEdad) {
        ifstream archivo("personas.txt");
        ofstream temp("temp.txt");
        int id, edad;
        string nombre;
        bool encontrado = false;

        if (archivo.is_open() && temp.is_open()) {
            while (archivo >> id >> nombre >> edad) {
                if (id == idBuscar) {
                    temp << id << " " << nuevoNombre << " " << nuevaEdad << endl;
                    encontrado = true;
                }
                else {
                    temp << id << " " << nombre << " " << edad << endl;
                }
            }
            archivo.close();
            temp.close();
            remove("personas.txt");
            rename("temp.txt", "personas.txt");

            if (encontrado) {
                cout << "Persona actualizada exitosamente.\n";
            }
            else {
                cout << "Persona no encontrada.\n";
            }
        }
        else {
            cout << "Error al abrir los archivos.\n";
        }
    }

    static void eliminarPersona(int idEliminar) {
        ifstream archivo("personas.txt");
        ofstream temp("temp.txt");
        int id, edad;
        string nombre;
        bool eliminado = false;

        if (archivo.is_open() && temp.is_open()) {
            while (archivo >> id >> nombre >> edad) {
                if (id == idEliminar) {
                    eliminado = true;
                }
                else {
                    temp << id << " " << nombre << " " << edad << endl;
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
    int opcion;

    do {
        cout << "\n=== MENU DE GESTION ===" << endl;
        cout << "1. Agregar persona" << endl;
        cout << "2. Mostrar personas" << endl;
        cout << "3. Actualizar persona" << endl;
        cout << "4. Eliminar persona" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            int id, edad;

            cout << "Ingrese ID: ";
            cin >> id;
            cout << "Ingrese Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese Edad: ";
            cin >> edad;

            PersonaManager nueva(nombre, id, edad);
            nueva.guardarEnArchivo();

        }
        else if (opcion == 2) {
            PersonaManager::leerDesdeArchivo();

        }
        else if (opcion == 3) {
            int id, edad;
            string nombre;

            cout << "Ingrese ID de la persona a actualizar: ";
            cin >> id;
            cout << "Ingrese nuevo nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Ingrese nueva edad: ";
            cin >> edad;

            PersonaManager::actualizarPersona(id, nombre, edad);

        }
        else if (opcion == 4) {
            int id;

            cout << "Ingrese ID de la persona a eliminar: ";
            cin >> id;

            PersonaManager::eliminarPersona(id);

        }
        else if (opcion == 5) {
            cout << "Saliendo del sistema...\n";

        }
        else {
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
