#include <iostream>
#include <cstring>
using namespace std;
#include "archivoMozo.h"
#include "mozo.h"
#include "mozoManager.h"
void MozoManager :: altaMozo()
{

    ArchivoMozo objArchivoMozo;
    Mozo objMozo;

    objMozo.cargar();
    objMozo.setIdMozo(objArchivoMozo.getCantidadRegistros() + 1);

    if(objArchivoMozo.guardar(objMozo))
    {
        cout << "!! SE GUARDO CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE GUARDO CORRECTAMENTE !!" << endl;
    }

}

void MozoManager :: listarPorApellido()
{

    ArchivoMozo objArchivoMozo;
    Mozo objMozo;

    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();

    Mozo *vec = new Mozo[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoMozo.leer(i);
    }

    for(int i = 0; i < cantidadRegistros-1; i++)
    {

        for(int k = 0; k < cantidadRegistros; k++)
        {

            if(strcmp(vec[i].getApellido(),vec[k].getApellido()) > 0)
            {

                Mozo aux = vec[i];
                vec[i] = vec[k];
                vec[k] = aux;

            }
        }
    }

    for(int i = 0; i < cantidadRegistros; i++){
        vec[i].mostrar();
    }

    delete[]vec;

}
void MozoManager :: listarPorTurno(){

    ArchivoMozo objArchivoMozo;
    Mozo objMozo;

    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();

    Mozo *vec = new Mozo[cantidadRegistros];

    cout << "-- TURNO MANIANA --" << endl;

    for(int i = 0; i < cantidadRegistros; i++){

        objMozo = objArchivoMozo.leer(i);

        if(objMozo.getTurno() == 1){

            objMozo.mostrar();

        }

    }

    cout << "-- TURNO TARDE --" << endl;

    for(int i = 0; i < cantidadRegistros; i++){

        objMozo = objArchivoMozo.leer(i);

        if(objMozo.getTurno() == 2){

            objMozo.mostrar();

        }

    }

    cout << "-- TURNO NOCHE --" << endl;

    for(int i = 0; i < cantidadRegistros; i++){

        objMozo = objArchivoMozo.leer(i);

        if(objMozo.getTurno() == 3){

            objMozo.mostrar();

        }

    }

    delete[]vec;

}

void MozoManager :: consultarPorDni(){

    ArchivoMozo objArchivoMozo;
    Mozo objMozo;

    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();
    char dni[15];

    cout << "INGRESE SU DNI : ";
    cin >> dni;

    for(int i = 0; i < cantidadRegistros; i++){

        objMozo = objArchivoMozo.leer(i);

        if(strcmp(objMozo.getDni(),dni)==0){

            objMozo.mostrar();

        }

    }

}
void MozoManager :: consultaPorTurno(){

    ArchivoMozo objArchivoMozo;
    Mozo objMozo;

    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();
    int turno;

    cout << "SELECCIONE EL TURNO.. ";
    cout << "1/ Maniana" << endl;
    cout << "2/ Tarde" << endl;
    cout << "3/ Noche" << endl;
    cout << "/// : ";
    cin >> turno;

    for(int i = 0; i < cantidadRegistros; i++){

        objMozo = objArchivoMozo.leer(i);

        if(turno == objMozo.getTurno()){

            objMozo.mostrar();
        }

    }

}
