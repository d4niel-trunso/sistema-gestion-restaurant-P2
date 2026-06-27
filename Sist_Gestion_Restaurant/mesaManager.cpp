#include <iostream>
using namespace std;
#include <cstring>
#include "ArchivoMesa.h"
#include "Mesa.h"
#include "MesaManager.h"

void MesaManager :: altaMesa()
{

    ArchivoMesa objArchivoMesa;
    Mesa objMesa;

    objMesa.cargar();

    if(objArchivoMesa.guardar(objMesa))
    {
        cout << "!! SE GUARDO CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE GUARDO CORRECTAMENTE !!" << endl;
    }

}

void MesaManager :: listadoPorNumeroMesa()
{

    ArchivoMesa objArchivoMesa;
    Mesa objMesa;

    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();

    Mesa *vec = new Mesa[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoMesa.leer(i);
    }

    for(int i = 0; i < cantidadRegistros; i++)
    {

        for(int j = 0; j < cantidadRegistros - 1; j++)
        {

            if(vec[i].getNumeroMesa() > vec[j].getNumeroMesa())
            {

                Mesa aux = vec[i];
                vec[i] = vec[j];
                vec[j] = aux;

            }

        }

    }

    for(int i = 0; i < cantidadRegistros; i++)
    {

        vec[i].mostrar();

    }

    delete[]vec;

}
void MesaManager :: listadoPorUbicacion()
{

    ArchivoMesa objArchivoMesa;
    Mesa objMesa;

    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();

    cout << "UBICACION : INTERIOR " << endl;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objMesa = objArchivoMesa.leer(i);

        if(objMesa.getUbicacion() == 1)
        {
            objMesa.mostrar();
        }

    }

    cout << endl;
    cout << "UBICACION : EXTERIOR " << endl;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objMesa = objArchivoMesa.leer(i);

        if(objMesa.getUbicacion() == 2)
        {
            objMesa.mostrar();
        }

    }

}

void MesaManager :: consultaPorNumeroMesa()
{

    ArchivoMesa objArchivoMesa;
    Mesa objMesa;

    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();
    int nroMesa;

    cout << "INGRESE EL NUMERO DE MESA : " << endl;
    cin >> nroMesa;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objMesa = objArchivoMesa.leer(i);
        if(objMesa.getNumeroMesa() == nroMesa)
        {

            objMesa.mostrar();

        }

    }

}
void MesaManager :: consultaPorUbicacion()
{

    ArchivoMesa objArchivoMesa;
    Mesa objMesa;

    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();
    int ubicacion;

    cout << "INGRESE LA UBICACION : ";
    cin >> ubicacion;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objMesa = objArchivoMesa.leer(i);
        if(objMesa.getUbicacion() == ubicacion)
        {
            objMesa.mostrar();
        }

    }

}
