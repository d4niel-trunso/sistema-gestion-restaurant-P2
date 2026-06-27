#include <iostream>
#include <cstring>
#include "archivoMozo.h"
#include "mozo.h"
#include "mozoManager.h"
#include "rlutil.h"

using namespace std;

MozoManager :: MozoManager()
{
    setCantidadOpciones(7);
}

void MozoManager :: mostrarOpciones()
{
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU DE MOZOS --------" << endl;
    cout << "1. ALTA DE MOZO" << endl;
    cout << "2. MODIFICAR MOZO" << endl;
    cout << "3. BAJA DE MOZO" << endl;
    cout << "4. LISTAR POR APELLIDO" << endl;
    cout << "5. LISTAR POR TURNO" << endl;
    cout << "6. CONSULTAR POR DNI" << endl;
    cout << "7. CONSULTAR POR TURNO" << endl;
    cout << "0. VOLVER" << endl;
    cout << "-------------------------------" << endl;
}

void MozoManager :: ejecutarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        altaMozo();
        break;
    case 2:
        modificarMozo();
        break;
    case 3:
        bajaMozo();
        break;
    case 4:
        listarPorApellido();
        break;
    case 5:
        listarPorTurno();
        break;
    case 6:
        consultarPorDni();
        break;
    case 7:
        consultaPorTurno();
        break;
    case 0:
        cout << "Volviendo al menu principal..." << endl;
        break;
    }
}

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

void MozoManager :: modificarMozo()
{
    ArchivoMozo objArchivoMozo;
    Mozo objMozo;
    int idMozo;

    cout << "INGRESE ID DEL MOZO A MODIFICAR: ";
    cin >> idMozo;

    int pos = objArchivoMozo.buscar(idMozo);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO EL MOZO." << endl;
        return;
    }

    objMozo = objArchivoMozo.leer(pos);
    if(!objMozo.getEstado())
    {
        cout << "EL MOZO ESTA DADO DE BAJA." << endl;
        return;
    }

    cout << "DATOS ACTUALES:" << endl;
    objMozo.mostrar();

    objMozo.cargar();
    objMozo.setIdMozo(idMozo);

    if(objArchivoMozo.guardar(objMozo, pos))
    {
        cout << "!! SE MODIFICO CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO MODIFICAR !!" << endl;
    }
}

void MozoManager :: bajaMozo()
{
    ArchivoMozo objArchivoMozo;
    Mozo objMozo;
    int idMozo;

    cout << "INGRESE ID DEL MOZO A DAR DE BAJA: ";
    cin >> idMozo;

    int pos = objArchivoMozo.buscar(idMozo);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO EL MOZO." << endl;
        return;
    }

    objMozo = objArchivoMozo.leer(pos);
    if(!objMozo.getEstado())
    {
        cout << "EL MOZO YA ESTA DADO DE BAJA." << endl;
        return;
    }

    objMozo.setEstado(false);
    if(objArchivoMozo.guardar(objMozo, pos))
    {
        cout << "!! SE DIO DE BAJA CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO DAR DE BAJA !!" << endl;
    }
}

void MozoManager :: listarPorApellido()
{
    ArchivoMozo objArchivoMozo;
    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();
    int mostrados = 0;

    if(cantidadRegistros == 0)
    {
        cout << "NO HAY MOZOS REGISTRADOS." << endl;
        return;
    }

    Mozo *vec = new Mozo[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoMozo.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int k = i + 1; k < cantidadRegistros; k++)
        {
            if(strcmp(vec[i].getApellido(),vec[k].getApellido()) > 0)
            {
                Mozo aux = vec[i];
                vec[i] = vec[k];
                vec[k] = aux;
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
        cout << "NO HAY MOZOS ACTIVOS." << endl;
    }

    delete[]vec;
}

void MozoManager :: listarPorTurno()
{
    ArchivoMozo objArchivoMozo;
    Mozo objMozo;
    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();
    int mostrados = 0;

    cout << "-- TURNO MANIANA --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMozo = objArchivoMozo.leer(i);
        if(objMozo.getEstado() && objMozo.getTurno() == 1)
        {
            objMozo.mostrar();
            mostrados++;
        }
    }

    cout << "-- TURNO TARDE --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMozo = objArchivoMozo.leer(i);
        if(objMozo.getEstado() && objMozo.getTurno() == 2)
        {
            objMozo.mostrar();
            mostrados++;
        }
    }

    cout << "-- TURNO NOCHE --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMozo = objArchivoMozo.leer(i);
        if(objMozo.getEstado() && objMozo.getTurno() == 3)
        {
            objMozo.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY MOZOS ACTIVOS." << endl;
    }
}

void MozoManager :: consultarPorDni()
{
    ArchivoMozo objArchivoMozo;
    Mozo objMozo;
    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();
    char dni[15];

    cout << "INGRESE SU DNI : ";
    cin >> dni;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMozo = objArchivoMozo.leer(i);
        if(objMozo.getEstado() && strcmp(objMozo.getDni(),dni)==0)
        {
            objMozo.mostrar();
            return;
        }
    }

    cout << "NO SE ENCONTRO EL DNI..." << endl;
}

void MozoManager :: consultaPorTurno()
{
    ArchivoMozo objArchivoMozo;
    Mozo objMozo;
    int cantidadRegistros = objArchivoMozo.getCantidadRegistros();
    int turno;
    int mostrados = 0;

    cout << "SELECCIONE EL TURNO.. " << endl;
    cout << "1/ Maniana" << endl;
    cout << "2/ Tarde" << endl;
    cout << "3/ Noche" << endl;
    cout << "/// : ";
    cin >> turno;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMozo = objArchivoMozo.leer(i);
        if(objMozo.getEstado() && turno == objMozo.getTurno())
        {
            objMozo.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO SE ENCONTRARON MOZOS PARA ESE TURNO." << endl;
    }
}
