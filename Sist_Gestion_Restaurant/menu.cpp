#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "menu.h"
#include "inputUtils.h"

using namespace std;

Menu::Menu(){
    setCantidadOpciones(0);
}

void Menu::iniciar(){
    int opcion;

    do{
        system("cls");
        antesDeMostrar();
        mostrarOpciones();
        opcion = seleccionarOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        despuesDeEjecutar(opcion);
    }while(opcion != 0);
}

int Menu::seleccionarOpcion(){
    int opcion;

    do{
        opcion = leerEntero("Ingrese opcion: ");

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

void Menu::antesDeMostrar(){
}

void Menu::despuesDeEjecutar(int opcion){
    if(opcion != 0){
        cout << endl;
        system("pause");
    }
}
