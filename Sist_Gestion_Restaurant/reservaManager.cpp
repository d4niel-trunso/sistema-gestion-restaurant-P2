#include <iostream>
#include "reservaManager.h"
#include "rlutil.h"

using namespace std;

void ReservaManager::menuReserva()
{
    int opcion;

    do
    {
        rlutil::setBackgroundColor(rlutil::GREEN);
        rlutil::setColor(rlutil::WHITE);
        rlutil::cls();

        cout << "-------- MENU DE RESERVAS --------" << endl;
        cout << "                                  " << endl;
        cout << "1. NUEVA RESERVA                  " << endl;
        cout << "2. LISTAR TODAS LAS RESERVAS      " << endl;
        cout << "3. BUSCAR POR ID                  " << endl;
        cout << "4. CANCELAR RESERVA               " << endl;
        cout << "                                  " << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL       " << endl;
        cout << "                                  " << endl;
        cout << "----------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::cls();

        switch(opcion)
        {
        case 1:
            cout << "=== RESERVAS ===" << endl;
            cargar();
            break;
        case 2:
            cout << "=== LISTADO DE RESERVAS ===" << endl;
            listar();
            break;
        case 3:
            cout << "En construccion..." << endl;
            break;
        case 4:
            cout << "En construccion..." << endl;
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion incorrecta!!!" << endl;
            break;
        }

        if (opcion != 0) {
            cout << endl;
            system("pause");
        }

    }
    while(opcion != 0);
}

void ReservaManager::cargar()
{
    int idReserva;
    int idCliente;
    int numeroMesa;
    int dia, mes, anio;
    int horaReserva;
    int cantidadComensales;
    int estadoReserva;
    bool estado;

    cout << "Ingrese los detalles de la reserva:" << endl;

    idReserva = generarID();

    cout << "ID Reserva: " << idReserva << endl;

    cout << "ID Cliente: ";
    cin >> idCliente;

    cout << "Numero Mesa: ";
    cin >> numeroMesa;

    cout << "Fecha de la Reserva: ";
    cin >> dia;
    cin >> mes;
    cin >> anio;

    Fecha f(dia, mes, anio);

    cout << "Hora de la Reserva (ej. 21 para 21:00hs): ";
    cin >> horaReserva;

    cout << "Cantidad de Comensales: ";
    cin >> cantidadComensales;

    estadoReserva = 1;
    estado = true;

    Reserva reserva(idReserva, idCliente, numeroMesa, f, horaReserva, cantidadComensales, estadoReserva, estado);

    if(_archivo.guardar(reserva)){
        cout << "Reserva generada y guardada exitosamente!" << endl;
    }else{
        cout << "Error al intentar acceder al archivo reservas.dat." << endl;
    }
}

void ReservaManager::listar()
{
    int cantidad = _archivo.getCantidadRegistros();

    if (cantidad == 0) {
        cout << "No hay reservas registradas en el sistema." << endl;
        return;
    }

    for(int i = 0; i < cantidad; i++)
    {
        Reserva reg = _archivo.leer(i);
        reg.mostrar();
    }
}


bool ReservaManager::existeID(int id)
{
    return _archivo.buscar(id) >= 0;
}

int ReservaManager::generarID()
{
    return _archivo.getCantidadRegistros() + 1;
}
