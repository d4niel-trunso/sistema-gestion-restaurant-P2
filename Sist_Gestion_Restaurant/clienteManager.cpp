#include <iostream>
#include <cstring>
using namespace std;
#include "archivoCliente.h"
#include "cliente.h"
#include "clienteManager.h"

void ClienteManager :: altaCliente()
{

    Cliente objCliente;
    ArchivoCliente objArchivoCliente;

    objCliente.cargar();
    objCliente.setIdCliente(objArchivoCliente.getCantidadRegistros() + 1);

    if(objArchivoCliente.guardar(objCliente))
    {
        cout << "!! SE GUARDO CORRECTAMENTE EL CLIENTE !!"<<endl;
    }
    else
    {
        cout << "!! ERROR , NO SE GUARDO CORRECTAMENTE !!"<< endl;
    }
}

void ClienteManager :: listadoPorApellido()
{

    ArchivoCliente objArchivoCliente;

    int cantidadRegistros = objArchivoCliente.getCantidadRegistros();

    Cliente* vec = new Cliente[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoCliente.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int j = 0; j < cantidadRegistros; j++)
        {
            if(strcmp(vec[i].getApellido(),vec[j].getApellido()) > 0)
            {
                Cliente aux = vec[i];
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

void ClienteManager :: listadoPorVips()
{

    ArchivoCliente objArchivoCliente;
    Cliente objCliente;

    int cantidadRegistros = objArchivoCliente.getCantidadRegistros();

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objCliente = objArchivoCliente.leer(i);

        if(objCliente.getEsVip())
        {
            objCliente.mostrar();
        }
    }

}

void ClienteManager :: consultaPorDni() /// modificar que no reciba por parametro el dni, sino que lo pida en la funcion
{

    ArchivoCliente objArchivoCliente;
    Cliente objCliente;

    int cantidadRegistros = objArchivoCliente.getCantidadRegistros();

    char dni[15];

    cout << "INGRESE EL DNI : ";
    cin >> dni;

    for(int i = 0; i < cantidadRegistros; i++)
    {

        objCliente = objArchivoCliente.leer(i);

        if(strcmp(objCliente.getDni(),dni)==0)
        {
            cout << "CLIENTE ENCONTRADO." << endl;
            objCliente.mostrar();
            return;
        }
    }

    cout << "NO SE ENCONTRO EL DNI..." << endl;
}
void ClienteManager :: consultaPorVip()
{
    ArchivoCliente objArchivoCliente; /// modificar los nombres objArchivoClientes
    Cliente objCliente;

    char dni[15];

    cout << "INGRESE EL DNI: ";
    cin >> dni;

    int cant = objArchivoCliente.getCantidadRegistros();

    for(int i = 0; i < cant; i++)
    {

        objCliente = objArchivoCliente.leer(i);

        if(strcmp(objCliente.getDni(), dni) == 0)
        {

            cout << "CLIENTE ENCONTRADO" << endl;

            if(objCliente.getEsVip())
            {
                cout << "ES VIP" << endl;
            }
            else
            {
                cout << "NO ES VIP" << endl;
            }

            return;
        }
    }

    cout << "NO SE ENCONTRO EL CLIENTE." << endl;
}
