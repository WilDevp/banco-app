/*
 * Este es el enunciado del ejercicio:
- Crear una lista doblemente ligada que simule los clientes de un banco (identificacién (no puede existir mas de una vez), nombre, estrato social, ciudad y activo)

- Crear una lista ligada simple que simule las cuentas de un banco
(número de cuenta (no se puede repetir), identificacion del
cliente (debe existir en la lista anterior y se puede repetir),
saldo inicial que no puede ser menor a 50000 pesos y activo)

- Crear una tercera lista ligada que simule las operaciones (la
cuenta debe existir) del banco (consignacion (se debe aumentar
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

// Clase Cliente
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

// Struct de cuenta
struct Cuenta {
    int numeroDeCuenta;
    int identificacionCliente;
    int saldoInicial;
    int activo;
    Cuenta *siguiente;
};

// Clase Operacion
class Operacion {
public:
    int consecutivo;
    int numeroDeCuenta;
    string fecha;
    int valor;
    string tipoTransaccion;
    int activo;
    Operacion *siguiente;

    Operacion() {
        siguiente = nullptr;
    }
};


/* Como el ejercicio indica en el enunciado que vamos a gestionar funcionalidades de un Banco
 * incialmente clientes debemos seguir con ese estandard
 * */

class Banco {
    Cliente *cabeza = nullptr;
    Cliente *cola = nullptr;
    Cuenta *cabezaCuentas = NULL;
    Operacion *cabezaOperaciones = nullptr;

public:
    Banco() {}

    // Metodo para agregar a un nuevo cliente
    void agregar_Cliente() {
        string respuesta;
        do {
            Cliente *nuevoCliente = new Cliente;

            // Configuración inicial
            nuevoCliente->ligader = NULL;
            nuevoCliente->ligaizq = NULL;

            // Ingreso de datos del cliente
            cout << "Ingrese la identificación del cliente: ";
            cin >> nuevoCliente->ID;

            // Verificación de la identificación que sea unica
            Cliente *actual = cabeza;
            while (actual != NULL) {
                if (actual->ID == nuevoCliente->ID) {
                    cout << "La identificación ingresada ya existe. Intente de nuevo." << endl;
                    delete nuevoCliente; // Liberamos la memoria asignada para evitar fugas de memoria.
                    return;
                }
                actual = actual->ligader;
            }

            cout << "Ingrese su nombre: ";
            cin >> nuevoCliente->nombre;

            cout << "Ingrese su estrato social: ";
            cin >> nuevoCliente->estrato;

            cout << "Ingrese la ciudad donde vive: ";
            cin >> nuevoCliente->ciudad;

            cout << "¿Desea activar el cliente? (1 para Sí, 0 para No): ";
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

            cout << "¿Desea agregar otro cliente? (Si/No): ";
            cin >> respuesta;

        } while (respuesta == "Si" || respuesta == "si");
    }

    // Metodo para modificar un cliente
    void modificarCliente() {
        int id;
        cout << "Ingrese la identificación del cliente a modificar: ";
        cin >> id;

        Cliente *cliente = cabeza;
        while (cliente != nullptr && cliente->ID != id) {
            cliente = cliente->ligader;
        }

        if (cliente == nullptr) {
            cout << "No se encontró un cliente con la identificación proporcionada." << endl;
            return;
        }

        string nombre;
        int estrato;
        string ciudad;

        cout << "Ingrese el nuevo nombre del cliente: ";
        cin >> nombre;
        cliente->nombre = nombre;

        cout << "Ingrese el nuevo estrato del cliente: ";
        cin >> estrato;
        cliente->estrato = estrato;

        cout << "Ingrese la nueva ciudad del cliente: ";
        cin >> ciudad;
        cliente->ciudad = ciudad;
    }

    // Metodo para imprimir todos los clientes
    void imprimir_clientes() {
        Cliente *temp = cabeza;

        while (temp != nullptr) {
            cout << temp->ID << " | " << temp->nombre << " | " << temp->estrato << " | " << temp->ciudad << " | "
                 << (temp->activo ? "Sí" : "No") << endl;
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
                    imprimir_clientes();
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opción inválida." << endl;
            }
        } while (op != 0);
    }

    //Metodo para agregar cuentas
    void agregar_cuenta() {
        Cuenta *nuevaCuenta = new Cuenta;
        nuevaCuenta->siguiente = NULL;

        cout << "Ingresa el número de cuenta: ";
        cin >> nuevaCuenta->numeroDeCuenta;

        //Verificamos que el número de cuenta no se repita
        Cuenta *actualCuenta = cabezaCuentas;
        while (actualCuenta != NULL) {
            if (actualCuenta->numeroDeCuenta == nuevaCuenta->numeroDeCuenta) {
                cout << "El número de cuenta ya existe. Intente de nuevo." << endl;
                delete nuevaCuenta;
                return;
            }
            actualCuenta = actualCuenta->siguiente;
        }

        cout << "Ingrese la identificación del cliente: ";
        cin >> nuevaCuenta->identificacionCliente;

        // Verificar que la identificación del cliente existe en la lista de clientes
        Cliente *actualCliente = cabeza;
        bool clienteExiste = false;
        while (actualCliente != NULL) {
            if (actualCliente->ID == nuevaCuenta->identificacionCliente) {
                clienteExiste = true;
                break;
            }
            actualCliente = actualCliente->ligader;
        }

        if (!clienteExiste) {
            cout << "La identificación del cliente no existe. Intente de nuevo." << endl;
            delete nuevaCuenta;
            return;
        }

        cout << "Ingrese el saldo inicial: ";
        cin >> nuevaCuenta->saldoInicial;

        // Verificar que el saldo inicial es al menos 50.000
        if (nuevaCuenta->saldoInicial < 50000) {
            cout << "El saldo inicial no puede ser menor a 50.000. Intente de nuevo." << endl;
            delete nuevaCuenta;
            return;
        }

        cout << "Ingrese el estado de la cuenta (activo = 1, inactivo = 0): ";
        cin >> nuevaCuenta->activo;

        // Agregar la cuenta a la lista
        if (cabezaCuentas == NULL) {
            cabezaCuentas = nuevaCuenta;
        } else {
            Cuenta *temporal = cabezaCuentas;
            while (temporal->siguiente != NULL) {
                temporal = temporal->siguiente;
            }
            temporal->siguiente = nuevaCuenta;
        }

        cout << "Cuenta agregada exitosamente." << endl;
    }

    // Metodo para imprimir cuentas
    void imprimir_cuentas() {
        Cuenta *cuentaActual = cabezaCuentas;

        if (this->cabeza == nullptr) {
            cout << "No hay cuentas en la lista." << std::endl;
        } else {
            while (cuentaActual != nullptr) {
                cout << "\nNúmero de cuenta: " << cuentaActual->numeroDeCuenta
                     << "\nIdentificación del cliente: " << cuentaActual->identificacionCliente
                     << "\nSaldo: " << cuentaActual->saldoInicial
                     << "\nActivo: " << (cuentaActual->activo ? "Sí" : "No") << ::endl;
                cuentaActual = cuentaActual->siguiente;
            }
        }

    }

    // Metodo para hacer las operaciones bancarias
    void agregarOperacion() {
        Operacion *nuevaOperacion = new Operacion;

        cout << "Ingrese el número consecutivo de la operación: ";
        cin >> nuevaOperacion->consecutivo;

        cout << "Ingrese el número de cuenta: ";
        cin >> nuevaOperacion->numeroDeCuenta;

        // Verificamos que la cuenta exista
        Cuenta *cuentaActual = cabezaCuentas;
        while (cuentaActual != NULL) {
            if (cuentaActual->numeroDeCuenta == nuevaOperacion->numeroDeCuenta) {
                break;
            }
            cuentaActual = cuentaActual->siguiente;
        }
        if (cuentaActual == NULL) {
            cout << "La cuenta no existe." << endl;
            delete nuevaOperacion;
            return;
        }

        cout << "Ingrese la fecha de la operación (YYYY-MM-DD): ";
        cin >> nuevaOperacion->fecha;

        cout << "Ingrese el tipo de transacción (consignacion/retiro): ";
        cin >> nuevaOperacion->tipoTransaccion;

        cout << "Ingrese el valor de la operación: ";
        cin >> nuevaOperacion->valor;

        if (nuevaOperacion->tipoTransaccion == "retiro" && cuentaActual->saldoInicial < nuevaOperacion->valor) {
            cout << "Saldo insuficiente para el retiro." << endl;
            delete nuevaOperacion;
            return;
        }

        if (nuevaOperacion->tipoTransaccion == "consignacion") {
            cuentaActual->saldoInicial += nuevaOperacion->valor;
        } else if (nuevaOperacion->tipoTransaccion == "retiro") {
            cuentaActual->saldoInicial -= nuevaOperacion->valor;
        }

        cout << "Ingrese el estado de la operación (activo = 1, inactivo = 0): ";
        cin >> nuevaOperacion->activo;

        // Agregar la operación a la lista
        if (cabezaOperaciones == NULL) {
            cabezaOperaciones = nuevaOperacion;
        } else {
            Operacion *temporal = cabezaOperaciones;
            while (temporal->siguiente != NULL) {
                temporal = temporal->siguiente;
            }
            temporal->siguiente = nuevaOperacion;
        }

        cout << "Operación agregada exitosamente." << endl;
    }

    // Metodo para imprimir las operaciones
    void imprimirOperaciones() {
        Operacion *operacionActual = cabezaOperaciones;

        if (operacionActual == nullptr) {
            cout << "No hay operaciones en la lista." << endl;
        } else {
            while (operacionActual != nullptr) {
                cout << "\nConsecutivo: " << operacionActual->consecutivo
                     << "\nNúmero de cuenta: " << operacionActual->numeroDeCuenta
                     << "\nFecha: " << operacionActual->fecha
                     << "\nValor: " << operacionActual->valor
                     << "\nTipo de transacción: " << operacionActual->tipoTransaccion
                     << "\nActivo: " << (operacionActual->activo ? "Sí" : "No") << ::endl;
                operacionActual = operacionActual->siguiente;
            }
        }
    }
};

int main() {
    // Se crea una instancia de Banco
    Banco banco;

    // Se utilizan los métodos de la instancia de Banco
    //banco.menu_Clientes();

    int opcion;
    do {
        cout << "\n1. Agregar cliente\n"
             << "2. Agregar cuenta\n"
             << "3. Agregar operación\n"
             << "4. Mostrar clientes\n"
             << "5. Mostrar cuentas\n"
             << "6. Mostrar operaciones\n"
             << "7. Salir\n"
             << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                // Llama a la función para agregar cliente
                banco.menu_Clientes();
                break;
            case 2:
                // Llama a la función para agregar cuenta
                banco.agregar_cuenta();
                break;
            case 3:
                // Llama a la función para agregar operación
                banco.agregarOperacion();
                break;
            case 4:
                // Llama a la función para mostrar clientes
                banco.imprimir_clientes();
                break;
            case 5:
                // Llama a la función para mostrar cuentas
                banco.imprimir_cuentas();
                break;
            case 6:
                // Llama a la función para mostrar operaciones
                banco.imprimirOperaciones();
                break;
            case 7:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción no válida. Por favor intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
};