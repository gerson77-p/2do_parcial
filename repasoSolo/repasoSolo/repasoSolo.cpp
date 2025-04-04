// repasoSolo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>   // Para entrada/salida estándar (cin, cout)
#include <fstream>    // Para manejo de archivos (ifstream, ofstream)
#include <string>     // Para usar el tipo string
using namespace std;

class Persona {
private:
    string nombre;
    int id;
    int edad;

public:
    // Constructor que inicializa los atributos
    Persona(string n, int i, int e) : nombre(n), id(i), edad(e) {}

    // Guarda los datos de la persona en el archivo
    void guardarEnArchivo() {
        ofstream archivo("personas.txt", ios::app); // Abre en modo append
        if (archivo.is_open()) {
            archivo << id << " " << nombre << " " << edad << endl;
            archivo.close();
            cout << "Persona agregada correctamente" << endl;
        }
        else {
            cout << "Error al abrir el archivo" << endl;
        }
    }

    // Muestra todas las personas registradas
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
            cout << "Error al abrir el archivo o no hay registros" << endl;
        }
    }

    // Actualiza los datos de una persona por su ID
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
                cout << "Persona actualizada correctamente" << endl;
            }
            else {
                cout << "Persona no encontrada" << endl;
            }
        }
        else {
            cout << "Error al abrir los archivos" << endl;
        }
    }

    // Elimina una persona por su ID
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
                cout << "Persona eliminada exitosamente" << endl;
            }
            else {
                cout << "Persona no encontrada" << endl;
            }
        }
        else {
            cout << "Error al abrir los archivos" << endl;
        }
    }
};

int main() {
    int opcion;

    do {
        // Menú principal
        cout << "\n=== MENU DE GESTION ===" << endl;
        cout << "1. Agregar persona" << endl;
        cout << "2. Mostrar personas" << endl;
        cout << "3. Actualizar persona" << endl;
        cout << "4. Eliminar persona" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
        case 1: { // Agregar nueva persona
            int id, edad;
            string nombre;

            cout << "Ingrese ID: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese Nombre: ";
            getline(cin, nombre);
            cout << "Ingrese Edad: ";
            cin >> edad;

            Persona nueva(nombre, id, edad);
            nueva.guardarEnArchivo();
            break;
        }
        case 2: // Mostrar todas las personas
            Persona::leerDesdeArchivo();
            break;

        case 3: { // Actualizar persona
            int id, edad;
            string nombre;

            cout << "Ingrese ID de la persona a actualizar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nuevo nombre: ";
            getline(cin, nombre);
            cout << "Ingrese nueva edad: ";
            cin >> edad;

            Persona::actualizarPersona(id, nombre, edad);
            break;
        }
        case 4: { // Eliminar persona
            int id;
            cout << "Ingrese ID de la persona a eliminar: ";
            cin >> id;

            Persona::eliminarPersona(id);
            break;
        }
        case 5: // Salir
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida" << endl;
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
