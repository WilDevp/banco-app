#include <iostream>

using namespace std;


struct Cliente {
    int ID;
    string nombre;
    int estrato;
    string ciudad;
    int activo;
    Cliente *ligaizq;
    Cliente *ligader;
    Cliente *Anterior;
    Cliente *Sig;
}; // Se considera refactorizar a una clase

typedef struct Cliente *Registro;
Registro cabeza, anterior;

int Id = 001;

void crear_Cliente() {

    string opc;
    string Ciudad;
    int Estrato;

    Registro Apuntador = new(struct Cliente);

    cabeza = Apuntador;
    anterior = Apuntador;
    Apuntador->ligader = NULL;
    Apuntador->ligaizq = NULL;


    Registro ultimo = NULL;
    Registro primero = NULL;
    Registro tope = NULL;

    do {

        Registro nuevoCliente = new(struct Cliente);

        nuevoCliente->ligader = NULL;
        anterior->ligaizq = nuevoCliente;
        anterior = nuevoCliente;

        nuevoCliente->ID = Id;
        Id++;

        cout << endl;

        cout << "\tIngrese su nombre: ";
        cin >> nuevoCliente->nombre;

        cout << endl;

        cout << "\tIngrese su estrato social: ";
        cin >> nuevoCliente->estrato;

        cout << endl;

        cout << "\tIngrese la ciudad donde reside: ";
        cin >> nuevoCliente->ciudad;

        cout << endl;

        cout << "\tIngrese el monto: ";
        cin >> nuevoCliente->activo;

        cout << endl;
        cout << endl;

        if ((Ciudad == "Cali" || Ciudad == "cali") && Estrato >= 4) {

            //ultimo = creaerfdghjhgfjh

            if (primero == NULL)

                primero = ultimo;

        }

        cout << "Para ingresar un nuevo registro, ingrese Si. De lo contrario, ingrese No: ";
        cin >> opc;

        while (opc != "Si" && opc != "No" && opc != "no" && opc != "si") {

            cout << "Opción inválida. Intentelo de nuevo." << endl;
            cout << "\nPara ingresar un nuevo registro, ingrese Si. De lo contrario, ingrese No: ";
            cin >> opc;

        }

    } while (opc != "No" && opc != "no");

    cout << "\n\t¡Los datos se han ingresado exitosamente!" << endl;

} //funciona

void mostrar_Lista() {

    if (cabeza == NULL) {

        cout << "La lista se encuentra vacía." << endl;

    } else {

        Registro p = cabeza->ligaizq;
        cout << endl;

        cout << "ID\tNombre\tEstrato\tCiudad\tActivo" << endl;

        while (p != NULL) {

            cout << p->ID << " | " << p->nombre << " | " << p->estrato << " | " << p->ciudad << " | " << p->activo
                 << endl;
            p = p->ligaizq;

        }

    }

} //funciona

void menu_Clientes() {

    int op;
    string opc;

    do {

        cout << endl;
        cout << "Menú clientes:" << endl;
        cout << "1. Agregar un cliente" << endl;
        cout << "2. Mostrar la lista de clientes" << endl;
        cout << "0. Salir del ciclo." << endl;
        cout << "Ingrese la opción que desea realizar: ";
        cin >> op;

        switch (op) {

            case 1:

                cout << endl;
                cout << endl;
                cout << "Almacenando clientes..." << endl;
                crear_Cliente();
                cout << endl;

                break;

            case 2:

                cout << endl;
                cout << endl;
                cout << "Imprimiendo lista..." << endl;
                cout << endl;
                mostrar_Lista();
                cout << endl;

                break;

            case 0:

                cout << endl;
                cout << "Saliendo del programa..." << endl;
                cout << endl;

                break;

            default:

                cout << "Opción inválida." << endl;

        }

    } while (op != 0);

}

int main() {

    int Sel;
    string opc;

    Registro ultimo = NULL;
    Registro primero = NULL;
    Registro tope = NULL;

    do {

        cout << endl;
        cout << "MENÚ CENTRAL:" << endl;
        cout << "1. Clientes." << endl;
        cout << "2. Cuentas." << endl;
        cout << "3. Operaciones." << endl;
        cout << "4. Mostar cola." << endl;
        cout << "5. Mostrar pila." << endl;
        cout << "0. Salir." << endl;
        cout << "Ingrese la opción que desea realizar: ";
        cin >> Sel;

        switch (Sel) {

            case 1:

                cout << endl;
                cout << endl;
                cout << "\t\t\tIngresando a MENÚ CLIENTES..." << endl << endl;
                menu_Clientes();
                cout << endl;

                break;

            case 2:

                cout << endl;
                cout << "\t\t\tIngresando a MENÚ CUENTAS..." << endl << endl;
                menu_Clientes();
                cout << endl;

                break;

            case 3:

                cout << endl;
                cout << "\t\t\tIngresando a MENÚ OPERACIONES..." << endl << endl;
                menu_Clientes();
                cout << endl;

                break;

            case 4:

                cout << endl;
                cout << "\t\t\tClientes de la ciudad de Cali de estrato 4 o superior..." << endl << endl;
                menu_Clientes();
                cout << endl;

                break;

            case 5:

                cout << endl;
                cout << "\t\t\tCuentas con saldo mayor a $5'000.000..." << endl << endl;
                menu_Clientes();
                cout << endl;

                break;

            case 0:

                cout << endl;
                cout << "Saliendo del programa..." << endl;
                cout << endl;

                break;

            default:

                cout << "Opción inválida." << endl;

        }

    } while (Sel != 0);

}