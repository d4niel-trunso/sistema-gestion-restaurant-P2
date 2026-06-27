#include <iostream>
#include <cstdio>
#include "menuManager.h"

using namespace std;

Menu::Menu(){
    setCantidadOpciones(0);
}

void Menu::iniciar(){
    int opcion;
    MenuManager menuMan;
    menuMan.mostrarBienvenida();

    do{
        system("cls");
        mostrarOpciones();
        opcion = seleccionarOpcion();
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

int Menu::seleccionarOpcion(){
    int opcion;

    do{
        cout << "Ingrese opcion: ";
        cin >> opcion;

        if(opcion < 0 || opcion > getCantidadOpciones()){
            cout << " > Opcion invalida..." << endl;
        }
    }while(opcion < 0 || opcion > getCantidadOpciones());

    return opcion;
}

void Menu::setCantidadOpciones(int cantidad){
    _cantidadOpciones = cantidad;
}

int Menu::getCantidadOpciones(){
    return _cantidadOpciones;
}
