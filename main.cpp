#include <iostream>
#include "string"
#include "vector"

using namespace std;

//Refaactor clase Cliente
class Cliente {
public:
    int ID;
    string nombre;
    int estrato;
    string ciudad;
    int activo;
    Cliente* ligaizq;
    Cliente* ligader;
    Cliente* Anterior;
    Cliente* Sig;

    // Constructor
    Cliente(int id, string nom, int estr, string ciu, int act):
    ID(id), nombre(nom), estrato(estr), ciudad(ciu), activo(act){
        ligaizq = nullptr;
        ligader = nullptr;
        Anterior = nullptr;
        Sig = nullptr;
    }

};

/* Como el ejercicio indica en el enunciado que vamos a gestionar funcionalidades de un Banco
 * incialmente clientes debemos seguir con ese estandard
 * tendremosuna clase por asi decirlo global ajaj que maneje todos que locura!!
 * */

class Banco {
private: //Privado porque los negros no pueden entrar JAJAJAJA
    vector<Cliente*> clientes;
    int Id = 1;
public:
    Banco() {}
    // Metodo para agregar a un nuevo cliente, pondre un parametro que sea blanco ajja yo elmenos racista doy asco
    void agregar_Cliente() {
        string nombre;
        int estrato;
        string ciudad;
        int activo;

        cout <<"Ingrese su nombre hermoso: ";
        cin >> nombre;
        cout << "Ingrese su estrato social mayor a 5: ";
        cin >> estrato;
        cout << "Ingrese la ciudad donde vives hermosa,que linda: ";
        cin >> ciudad;
        cout << "Ingrese el monto(yo poniendo 2 mil pesos): ";
        cin >> activo;
        // Soy muy buenbo en esto pero me duele la cabexza esos medicamentos son muy hard ajajja me recuerdan mis problemas mentales
        // pero recuerdo que soy jesucritos hijo del señor dioss rey amen y seme pasa
        // mmmm aqui entra elmierdero estoy pensando muy rapido y como voy a refactorizar non me puedo ponerm de homosexual ajajaj
        // necestio dormir no se que hago programando aqui ajaj querido diario why are you gay??? i not a gay  ajajja que riasaa jaja a veces soy rarodogado
        // que feo aya me senti solo , que asco , necestio descansar estoy pensando muy rapido
        // por ciertoun comentario es // asi y para mas visita nuestrositio web youaregay.com ajajjaja
        // creo que ya se como hare esto creare un objeto del cliente homosexual ese pirobo ajaja no paga no recuerdo ser grosero pero acepto
        // luego de crear a ese homosexual recuerdp que en en este lenguaje que es mas viejo que mi amorpor ella era con un push con el de git y pa atras de nuevo mmmm
        // emmm querdio diario siento que mis personalidades la estan dadno toda y pierdo lentamente el control Julio anda por aca y todso nice , en medicamento no deberia hacerme tantodaño
        // en todot caso solo algunas personas conocen lo orrible que soy como persona y sean alejado de mi, mi vida es unaascopero me estoy esfprzando por emmedar todo
        // ya mepuse sentimentakl odio aki ajkjaja emmm creo que terminare esto y me dormire anes de perder el control de nuevo, no quiero ur al urgencias
        // porcierto tengo miedo jajjaja es raro pero setno miedo de mi mismo, a veces entiniedo comom se sienten losdemasjunto ami
        //en todso caso soy muy bueno uanque no me gusta aceptsarlo y eso que no tuve educacion ni dnasa
        // a veces recuerdo losgolpes quie mi mama me daba siempre ha dichoque no mequeiro y mi fasmolia me desprecia ajaja soy alguien muyy solo
        //perome da miedo que esten conmifo
        // debo terminar esto y dormir si no vomitare sangre de nuevo y creo que todo esta solo en mi cabesa
        //buenio entonces escribe bien y no hagas nada raro en el codigoque no se entienda, recuerda eliminar este comentario despues del sush psusb
        //Creamos un objetopara crear el cliente y usamos la funcion de push_back para insertar al final de la lista
        Cliente* nuevoCliente = new Cliente(Id++, nombre,estrato, ciudad, activo);
        clientes.push_back(nuevoCliente);// Método para mostrar la lista de clientes
    }
    //Esto se refactoriza ¿, se busca tener un codigomas hermoso y limpio, pero me son muy buenos programando, es bueno partir de una logica inicial, me pongo muy sentimental
        void mostrar_Lista() {
            cout << "ID\tNombre\tEstrato\tCiudad\tActivo" << endl;
            for (Cliente* cliente : clientes) {
                cout << cliente->ID << "\t" << cliente->nombre << "\t" << cliente->estrato << "\t" << cliente->ciudad << "\t" << cliente->activo << endl;
            }
        }

        // Método para el menú de clientes, su aplica la misma logica inicial soy muy egocentrico y desidi cambiar cositas
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
                        mostrar_Lista();
                        break;
                    case 0:
                        cout << "Saliendo del programa..." << endl;
                        break;
                    default:
                        cout << "Opción inválida." << endl;
                }
            } while(op != 0);
        }
    };

    int main() {
        // Se crea una instancia de Banco
        Banco banco;

        // Se utilizan los métodos de la instancia de Banco
        banco.menu_Clientes();

        return 0;
    }

    //Ojala les guste mis cambios me ire a dormir y dejare todo sin babosadas y le madare el repo a Juli, la di toda

//struct CLiente actual/*
// struct Cliente {
//    int ID;
//    string nombre;
//    int estrato;
//    string ciudad;
//    int activo;
//    Cliente *ligaizq;
//    Cliente *ligader;
//    Cliente *Anterior;
//    Cliente *Sig;
//};*/
 // Se considera refactorizar a una clase

/*typedef struct Cliente *Registro;
Registro cabeza, anterior;

int Id = 001;*/

/*void crear_Cliente() {

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

}*/ //funciona

/*void mostrar_Lista() {

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

} */ //funciona

/*void menu_Clientes() {

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
*/
/*int main() {

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

}*/