#include <iostream>
#include <cstring>
#include "archivoCliente.h"
#include "cliente.h"
#include "clienteManager.h"
#include "rlutil.h"

using namespace std;

ClienteManager :: ClienteManager()
{
    setCantidadOpciones(7);
}

void ClienteManager :: mostrarOpciones()
{
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU DE CLIENTES --------" << endl;
    cout << "1. ALTA DE CLIENTE" << endl;
    cout << "2. MODIFICAR CLIENTE" << endl;
    cout << "3. BAJA DE CLIENTE" << endl;
    cout << "4. LISTAR POR APELLIDO" << endl;
    cout << "5. LISTAR CLIENTES VIP" << endl;
    cout << "6. CONSULTAR POR DNI" << endl;
    cout << "7. CONSULTAR VIP POR DNI" << endl;
    cout << "0. VOLVER" << endl;
    cout << "----------------------------------" << endl;
}

void ClienteManager :: ejecutarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        altaCliente();
        break;
    case 2:
        modificarCliente();
        break;
    case 3:
        bajaCliente();
        break;
    case 4:
        listadoPorApellido();
        break;
    case 5:
        listadoPorVips();
        break;
    case 6:
        consultaPorDni();
        break;
    case 7:
        consultaPorVip();
        break;
    case 0:
        cout << "Volviendo al menu principal..." << endl;
        break;
    }
}

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

void ClienteManager :: modificarCliente()
{
    Cliente objCliente;
    ArchivoCliente objArchivoCliente;
    int idCliente;

    cout << "INGRESE ID DEL CLIENTE A MODIFICAR: ";
    cin >> idCliente;

    int pos = objArchivoCliente.buscar(idCliente);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO EL CLIENTE." << endl;
        return;
    }

    objCliente = objArchivoCliente.leer(pos);
    if(!objCliente.getEstado())
    {
        cout << "EL CLIENTE ESTA DADO DE BAJA." << endl;
        return;
    }

    cout << "DATOS ACTUALES:" << endl;
    objCliente.mostrar();

    objCliente.cargar();
    objCliente.setIdCliente(idCliente);

    if(objArchivoCliente.guardar(objCliente, pos))
    {
        cout << "!! SE MODIFICO CORRECTAMENTE EL CLIENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO MODIFICAR !!" << endl;
    }
}

void ClienteManager :: bajaCliente()
{
    Cliente objCliente;
    ArchivoCliente objArchivoCliente;
    int idCliente;

    cout << "INGRESE ID DEL CLIENTE A DAR DE BAJA: ";
    cin >> idCliente;

    int pos = objArchivoCliente.buscar(idCliente);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO EL CLIENTE." << endl;
        return;
    }

    objCliente = objArchivoCliente.leer(pos);
    if(!objCliente.getEstado())
    {
        cout << "EL CLIENTE YA ESTA DADO DE BAJA." << endl;
        return;
    }

    objCliente.setEstado(false);
    if(objArchivoCliente.guardar(objCliente, pos))
    {
        cout << "!! SE DIO DE BAJA CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO DAR DE BAJA !!" << endl;
    }
}

void ClienteManager :: listadoPorApellido()
{
    ArchivoCliente objArchivoCliente;
    int cantidadRegistros = objArchivoCliente.getCantidadRegistros();
    int mostrados = 0;

    if(cantidadRegistros == 0)
    {
        cout << "NO HAY CLIENTES REGISTRADOS." << endl;
        return;
    }

    Cliente* vec = new Cliente[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoCliente.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int j = i + 1; j < cantidadRegistros; j++)
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
        if(vec[i].getEstado())
        {
            vec[i].mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY CLIENTES ACTIVOS." << endl;
    }

    delete[]vec;
}

void ClienteManager :: listadoPorVips()
{
    ArchivoCliente objArchivoCliente;
    Cliente objCliente;
    int cantidadRegistros = objArchivoCliente.getCantidadRegistros();
    int mostrados = 0;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objCliente = objArchivoCliente.leer(i);
        if(objCliente.getEstado() && objCliente.getEsVip())
        {
            objCliente.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY CLIENTES VIP ACTIVOS." << endl;
    }
}

void ClienteManager :: consultaPorDni()
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
        if(objCliente.getEstado() && strcmp(objCliente.getDni(),dni)==0)
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
    ArchivoCliente objArchivoCliente;
    Cliente objCliente;
    char dni[15];
    int cant = objArchivoCliente.getCantidadRegistros();

    cout << "INGRESE EL DNI: ";
    cin >> dni;

    for(int i = 0; i < cant; i++)
    {
        objCliente = objArchivoCliente.leer(i);
        if(objCliente.getEstado() && strcmp(objCliente.getDni(), dni) == 0)
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
