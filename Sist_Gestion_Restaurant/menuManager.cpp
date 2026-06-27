#include <iostream>
#include <cstdio>
#include "menuManager.h"
#include "rlutil.h"

using namespace std;

MenuManager::MenuManager(){
    setCantidadOpciones(6);
}

void MenuManager::mostrarBienvenida(){
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();
    rlutil::locate(30, 9);
    cout << "¡¡¡¡BIENVENIDOS!!!!" << endl << endl << endl;
    system("pause");

}

void MenuManager::mostrarOpciones(){
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU PRINCIPAL --------" << endl;
    cout << "                                " << endl;
    cout << "1. MOZOS                        " << endl;
    cout << "2. CLIENTES                     " << endl;
    cout << "3. MESAS                        " << endl;
    cout << "4. PLATOS                       " << endl;
    cout << "5. RESERVAS                     " << endl;
    cout << "6. FACTURAS                     " << endl;
    cout << "                                " << endl;
    cout << "0. SALIR                        " << endl;
    cout << "                                " << endl;
    cout << "--------------------------------" << endl;
}

void MenuManager::ejecutarOpcion(int opcion){
    system("cls");

    switch(opcion){
    case 1:
        cout << "FUNCIONANDO..." << endl;
        break;
    case 2:
        cout << "FUNCIONANDO..." << endl;
        break;
    case 3:
        cout << "FUNCIONANDO..." << endl;
        break;
    case 4:
        cout << "FUNCIONANDO..." << endl;
        break;
    case 5:
        _reservaManager.menuReserva();
        break;
    case 6:
        _facturaManager.menuFacturacion();
        break;
    case 0:
        cout << "Gracias por usar la app...." << endl;
        break;
    }
}
