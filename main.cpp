/*
 * Este es el enunciado del ejercicio:
- Crear una lista doblemente ligada que simule los clientes de un banco (identificacién (no puede existir mas de una vez), nombre, estrato social, ciudad y activo)

- Crear una lista ligada simple que simule las cuentas de un banco
(ntimero de cuenta (no se puede repetir), identificacion del
cliente (debe existir en la lista anterior y se puede repetir),
saldo inicial que no puede ser menor a 50000 pesos y activo)

- Crear una tercera lista ligada que simule las operaciones (la
cuenta debe existir) del banco (consignacién (se debe aumentar
la cantidad al saldo la cantidad consignada) y retiro de dinero
(solo se puede retirar si hay saldo suficiente)), los campos son:
consecutivo, numero de cuenta, fecha, valor, tipo de
transaccion y activo)
- Crear un menu que me permita manejar cualquiera de las tres operaciones (clientes, cuentas y operaciones)
-  La información de los clientes se debe poder ingresar, modificar
y anular/desanular registros
 - Las cuentas se deben poder adicionar, anular o desanular un
registro
- Las consultas se deben manejar en pilas y colas y son las
siguientes:
- Encolar los registros de los clientes de la ciudad de Cali que son
estrato cuatro o superior
- Apilar Las cuentas cuyo saldo es mayor de 5000000 pesos
+ Mostrar la suma de todas cuentas
 */
#include <iostream>
#include "string"

using namespace std;

//Refaactor clase Cliente
class Cliente {
public:
    int ID;
    string nombre;
    int estrato;
    string ciudad;
    int activo;
    Cliente *ligaizq;
    Cliente *ligader;
    Cliente *Anterior;
    Cliente *Sig;
};

/* Como el ejercicio indica en el enunciado que vamos a gestionar funcionalidades de un Banco
 * incialmente clientes debemos seguir con ese estandard
 * */

class Banco {
    Cliente* cabeza = nullptr;
    Cliente* cola = nullptr;
public:
    Banco() {}

    // Metodo para agregar a un nuevo cliente
    void agregar_Cliente() {
        Cliente* nuevoCliente = new Cliente;

        nuevoCliente->ID = 01;

        cout << "Ingrese su nombre hermoso  : ";
        cin >> nuevoCliente->nombre;
        cout << "Ingrese su estrato social: ";
        cin >> nuevoCliente->estrato;
        cout << "Ingrese la ciudad donde vive: ";
        cin >> nuevoCliente->ciudad;
        cout << "Ingrese el monto: ";
        cin >> nuevoCliente->activo;
        if (cabeza == nullptr) {
            // Si la lista está vacía, el nuevo cliente es tanto la cabeza como la cola
            cabeza = nuevoCliente;
            cola = nuevoCliente;
        } else {
            // Si la lista no está vacía, agregamos el nuevo cliente al final
            cola->ligader = nuevoCliente;
            nuevoCliente->ligaizq = cola;
            cola = nuevoCliente;
        }
    }

    void imprimirClientes() {
        Cliente* temp = cabeza;

        while (temp != nullptr) {
            cout << temp->ID << " | " << temp->nombre << " | " << temp->estrato << " | " << temp->ciudad << " | " << temp->activo << endl;
            temp = temp->ligader;
        }
    }

    // Método para el menú de clientes, su aplica la misma logica inicial
    void menu_Clientes() {
        int op;
        do {
            cout << "1. Agregar un cliente" << endl;
            cout << "2. Mostrar la lista de clientes" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese la opción que desea realizar: ";
            cin >> op;
            switch (op) {
                case 1:
                    agregar_Cliente();
                    break;
                case 2:
                    imprimirClientes();
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opción inválida." << endl;
            }
        } while (op != 0);
    }
};

int main() {
    // Se crea una instancia de Banco
    Banco banco;

    // Se utilizan los métodos de la instancia de Banco
    banco.menu_Clientes();

    return 0;
}