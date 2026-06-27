#include <iostream>
#include <cstring>
using namespace std;
#include "archivoPlato.h"
#include "platoManager.h"
#include "plato.h"

void PlatoManager :: altaPlato()
{

    ArchivoPlato objArchivoPlato;
    Plato objPlato;

    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();

    objPlato.cargar();
    objPlato.setIdPlato(cantidadRegistros + 1);

    if(objArchivoPlato.guardar(objPlato))
    {

        cout << "!! SE GUARDO CORRECTAMENTE !!" << endl;

    }
    else
    {

        cout << "!! ERROR , NO SE PUDO GUARDAR !!" << endl;

    }

}

void PlatoManager :: listadoPorNombre()
{

    ArchivoPlato objArchivoPlato;

    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();

    Plato* vec = new Plato[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoPlato.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int k = 0; k < cantidadRegistros; k++)
        {
            if(strcmp(vec[i].getNombre(),vec[k].getNombre()) > 0)
            {
                Plato aux = vec[i];
                vec[i] = vec[k];
                vec[k] = aux;
            }
        }
    }

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i].mostrar();
    }

    delete[]vec;

}
void PlatoManager :: listadoPorCategoria()
{

    ArchivoPlato objArchivoPlato;
    Plato objPlato;

    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();

    Plato *vec = new Plato[cantidadRegistros];

    cout << "-- CATEGORIA : ENTRADA --" << endl;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objPlato = objArchivoPlato.leer(i);

        if(objPlato.getCategoria() == 1)
        {

            objPlato.mostrar();

        }

    }

    cout << "-- CATEGORIA : PLATO PRINCPIAL --" << endl;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objPlato = objArchivoPlato.leer(i);

        if(objPlato.getCategoria() == 2)
        {

            objPlato.mostrar();

        }

    }

    cout << "-- CATEGORIA : POSTRE --" << endl;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objPlato = objArchivoPlato.leer(i);

        if(objPlato.getCategoria() == 3)
        {

            objPlato.mostrar();

        }

    }

    cout << "-- CATEGORIA : BEBIDA --" << endl;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objPlato = objArchivoPlato.leer(i);

        if(objPlato.getCategoria() == 4)
        {

            objPlato.mostrar();

        }

    }

    delete[]vec;


}
void PlatoManager :: listadoPorPrecio()
{

    ArchivoPlato objArchivoPlato;
    Plato objPlato;

    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();

    Plato *vec = new Plato[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {

        vec[i] = objArchivoPlato.leer(i);

    }

    for(int i = 0; i < cantidadRegistros; i++)
    {

        for(int j = 0; j < cantidadRegistros - 1; j++)
        {

            if(vec[i].getPrecio() < vec[j].getPrecio() )
            {
                Plato aux = vec[i];
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

void PlatoManager :: consultaPorCategoria()
{

    ArchivoPlato objArchivoPlato;
    Plato objPlato;

    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();

    int categoria;

    cout << "INGRESE LA CATEGORIA : ";
    cout << "1/ ENTRADA" << endl;
    cout << "2/ PRINCIPAL" << endl;
    cout << "3/ POSTRE" << endl;
    cout << "4/ BEBIDA" << endl;
    cin >> categoria;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objPlato = objArchivoPlato.leer(i);

        if(categoria == objPlato.getCategoria())
        {

            objPlato.mostrar();

        }

    }


}
void PlatoManager :: consultaPorRangoDePrecios()
{

    ArchivoPlato objArchivoPlato;
    Plato objPlato;

    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();

    float desde;
    float hasta;

    cout << "INGRESE DESDE CUANTO : ";
    cin >> desde;
    cout << "INGRESE HASTA CUANTO : ";
    cin >> hasta;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objPlato = objArchivoPlato.leer(i);

        if(objPlato.getPrecio() >= desde && objPlato.getPrecio() <= hasta )
        {
            objPlato.mostrar();
        }

    }

}
