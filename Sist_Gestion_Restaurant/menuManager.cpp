#include <iostream>
#include <cstdio>
#include "menuManager.h"
#include "rlutil.h"

using namespace std;

MenuManager::MenuManager(){
    setCantidadOpciones(7);
}

void MenuManager::mostrarBienvenida(){
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();
    rlutil::locate(30, 9);
    cout << "BIENVENIDOS!!!!" << endl << endl << endl;
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
    cout << "7. INFORMES                     " << endl;
    cout << "                                " << endl;
    cout << "0. SALIR                        " << endl;
    cout << "                                " << endl;
    cout << "--------------------------------" << endl;
}

void MenuManager::ejecutarOpcion(int opcion){
    switch(opcion){
    case 1:
        _mozoManager.iniciar();
        break;
    case 2:
        _clienteManager.iniciar();
        break;
    case 3:
        _mesaManager.iniciar();
        break;
    case 4:
        _platoManager.iniciar();
        break;
    case 5:
        _reservaManager.iniciar();
        break;
    case 6:
        _facturaManager.iniciar();
        break;
    case 7:
        _informeManager.iniciar();
        break;
    case 0:
        cout << "Gracias por usar la app...." << endl;
        break;
    }
}
