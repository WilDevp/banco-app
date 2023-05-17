#include <iostream>
#include "string"
#include <queue>
#include <stack>

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
    void agregar_cliente() {
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
    void modificar_cliente() {
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

    // Metodo para cambiar el estado de un cliente
    void cambiar_estado_cliente() {
        int id;
        cout << "Ingrese la identificación del cliente a cambiar de estado: ";
        cin >> id;

        Cliente *cliente = cabeza;
        while (cliente != nullptr && cliente->ID != id) {
            cliente = cliente->ligader;
        }

        if (cliente == nullptr) {
            cout << "No se encontró un cliente con la identificación proporcionada." << endl;
            return;
        }

        cliente->activo = !cliente->activo;
        cout << "El estado del cliente ha sido cambiado." << endl;
    }

    // Metodo para encolar los registros de los clientes de la ciudad de Cali que son estrato cuatro o superior
    void encolar_clientes_cali() {
        queue<Cliente*> clientesCali;
        Cliente* actual = cabeza;
        while (actual != NULL) {
            if (actual->ciudad == "Cali" && actual->estrato >= 4) {
                clientesCali.push(actual);
            }
            actual = actual->ligader;
        }
        // Imprimir los clientes de la cola
        while (!clientesCali.empty()) {
            Cliente* cliente = clientesCali.front();
            cout << cliente->ID << " | " << cliente->nombre << " | " << cliente->estrato << " | " << cliente->ciudad << " | " << (cliente->activo ? "Sí" : "No") << endl;
            clientesCali.pop();
        }
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

    // Metodo para cambiar el estadode una cuenta
    void cambiar_estado_cuenta() {
        int numCuenta;
        cout << "Ingrese el número de la cuenta a cambiar de estado: ";
        cin >> numCuenta;

        Cuenta *cuenta = cabezaCuentas;
        while (cuenta != nullptr && cuenta->numeroDeCuenta != numCuenta) {
            cuenta = cuenta->siguiente;
        }

        if (cuenta == nullptr) {
            cout << "No se encontró una cuenta con el número proporcionado." << endl;
            return;
        }

        cuenta->activo = !cuenta->activo;
        cout << "El estado de la cuenta ha sido cambiado." << endl;
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
    void agregar_operacion() {
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
    void imprimir_operaciones() {
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

    // Metodo para apilar las cuentas cuyo saldo es mayor de 5000000 pesos
    void apilar_cuentas_saldo_alto() {
        stack<Cuenta*> cuentasSaldoAlto;
        Cuenta* actual = cabezaCuentas;
        while (actual != NULL) {
            if (actual->saldoInicial > 5000000) {
                cuentasSaldoAlto.push(actual);
            }
            actual = actual->siguiente;
        }
        // Imprimir las cuentas de la pila
        while (!cuentasSaldoAlto.empty()) {
            Cuenta* cuenta = cuentasSaldoAlto.top();
            cout << "\nNúmero de cuenta: " << cuenta->numeroDeCuenta
                 << "\nIdentificación del cliente: " << cuenta->identificacionCliente
                 << "\nSaldo: " << cuenta->saldoInicial
                 << "\nActivo: " << (cuenta->activo ? "Sí" : "No") << ::endl;
            cuentasSaldoAlto.pop();
        }
    }

    // Metodo para mostrar la suma de todas las cuentas
    void mostrar_suma_cuentas() {
        int suma = 0;
        Cuenta* actual = cabezaCuentas;
        while (actual != NULL) {
            suma += actual->saldoInicial;
            actual = actual->siguiente;
        }
        cout << "La suma de todas las cuentas es: " << suma << endl;
    }

    // Método para el menú de clientes, su aplica la misma logica inicial
    void menu_clientes() {
        int op;
        do {
            cout << "\n1. Agregar un cliente" << endl;
            cout << "2. Modificar un cliente" << endl;
            cout << "3. Cambiar el estado de un cliente" << endl;
            cout << "4. Mostrar cola de clientes de Cali estrato 4 o superior" << endl;
            cout << "5. Mostrar la lista de clientes" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese la opción que desea realizar: ";
            cin >> op;
            switch (op) {
                case 1:
                    agregar_cliente();
                    break;
                case 2:
                    modificar_cliente();
                    break;
                case 3:
                    cambiar_estado_cliente();
                    break;
                case 4:
                    encolar_clientes_cali();
                    break;
                case 5:
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

    // Método para el menú de cuentas, su aplica la misma logica inicial
    void menu_cuentas() {
        int op;
        do {
            cout << "\n1. Agregar una cuenta" << endl;
            cout << "2. Cambiar el estado de una cuenta" << endl;
            cout << "3. Mostrar la lista de cuentas" << endl;
            cout << "4. Mostrar pila de cuentas con el saldo mayor a 5000000 pesos" << endl;
            cout << "5. Ver la suma total de las cuentas" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese la opción que desea realizar: ";
            cin >> op;
            switch (op) {
                case 1:
                    agregar_cuenta();
                    break;
                case 2:
                    cambiar_estado_cuenta();
                    break;
                case 3:
                    imprimir_cuentas();
                    break;
                case 4:
                    apilar_cuentas_saldo_alto();
                    break;
                case 5:
                    mostrar_suma_cuentas();
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opción inválida." << endl;
            }
        } while (op != 0);
    }

    // Método para el menú de cuentas, su aplica la misma logica inicial
    void menu_operaciones() {
        int op;
        do {
            cout << "1. Crear una nueva operación" << endl;
            cout << "2. Imprimir las operaciones" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese la opción que desea realizar: ";
            cin >> op;
            switch (op) {
                case 1:
                    agregar_operacion();
                    break;
                case 2:
                    imprimir_operaciones();
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opción inválida." << endl;
            }
        } while (op != 0);
    }

    // Se crea un meno globla para evitar acoplar este codigo dentro del main
    void menu(){
        int opcion;
        do {
            cout << "\n1. Ver menú clientes\n"
                 << "2. Ver menú cuentas\n"
                 << "3. Ver menú operaciones\n"
                 << "4. Salir\n"
                 << "Ingrese una opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    // Llama a la función del menu de clientes
                    menu_clientes();
                    break;
                case 2:
                    // Llama a la función del menu de cuentas
                    menu_cuentas();
                    break;
                case 3:
                    // Llama a la función del menu de operaciones
                    menu_operaciones();
                    break;
                case 4:
                    std::cout << "Saliendo del programa.\n";
                    break;
                default:
                    std::cout << "Opción no válida. Por favor intente de nuevo.\n";
            }
        } while (opcion != 4);
    }
};

int main() {
    // Se crea una instancia de Banco
    Banco banco;

    // Se utilizan los métodos de la instancia de Banco
    banco.menu();

    return 0;
};