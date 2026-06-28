#include <iostream>
#include <cstring>
#include "archivoMesa.h"
#include "mesa.h"
#include "mesaManager.h"
#include "rlutil.h"
#include "utilidades.h"

using namespace std;

MesaManager :: MesaManager()
{
    setCantidadOpciones(7);
}

void MesaManager :: mostrarOpciones()
{
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU DE MESAS --------" << endl;
    cout << "1. ALTA DE MESA" << endl;
    cout << "2. MODIFICAR MESA" << endl;
    cout << "3. BAJA DE MESA" << endl;
    cout << "4. LISTAR POR NUMERO" << endl;
    cout << "5. LISTAR POR UBICACION" << endl;
    cout << "6. CONSULTAR POR NUMERO" << endl;
    cout << "7. CONSULTAR POR UBICACION" << endl;
    cout << "0. VOLVER" << endl;
    cout << "-------------------------------" << endl;
}

void MesaManager :: ejecutarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        altaMesa();
        break;
    case 2:
        modificarMesa();
        break;
    case 3:
        bajaMesa();
        break;
    case 4:
        listadoPorNumeroMesa();
        break;
    case 5:
        listadoPorUbicacion();
        break;
    case 6:
        consultaPorNumeroMesa();
        break;
    case 7:
        consultaPorUbicacion();
        break;
    case 0:
        cout << "Volviendo al menu principal..." << endl;
        break;
    }
}

void MesaManager :: altaMesa()
{
    ArchivoMesa objArchivoMesa;
    Mesa objMesa;

    objMesa.cargar();

    if(objArchivoMesa.buscar(objMesa.getNumeroMesa()) >= 0)
    {
        cout << "YA EXISTE UNA MESA CON ESE NUMERO." << endl;
        return;
    }

    if(objArchivoMesa.guardar(objMesa))
    {
        cout << "!! SE GUARDO CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE GUARDO CORRECTAMENTE !!" << endl;
    }
}

void MesaManager :: modificarMesa()
{
    ArchivoMesa objArchivoMesa;
    Mesa objMesa;
    int nroMesa;

    nroMesa = leerEntero("INGRESE EL NUMERO DE MESA A MODIFICAR: ");

    int pos = objArchivoMesa.buscar(nroMesa);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO LA MESA." << endl;
        return;
    }

    objMesa = objArchivoMesa.leer(pos);
    if(!objMesa.getEstado())
    {
        cout << "LA MESA ESTA DADA DE BAJA." << endl;
        return;
    }

    cout << "DATOS ACTUALES:" << endl;
    objMesa.mostrar();

    objMesa.cargar();
    objMesa.setNumeroMesa(nroMesa);

    if(objArchivoMesa.guardar(objMesa, pos))
    {
        cout << "!! SE MODIFICO CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO MODIFICAR !!" << endl;
    }
}

void MesaManager :: bajaMesa()
{
    ArchivoMesa objArchivoMesa;
    Mesa objMesa;
    int nroMesa;

    nroMesa = leerEntero("INGRESE EL NUMERO DE MESA A DAR DE BAJA: ");

    int pos = objArchivoMesa.buscar(nroMesa);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO LA MESA." << endl;
        return;
    }

    objMesa = objArchivoMesa.leer(pos);
    if(!objMesa.getEstado())
    {
        cout << "LA MESA YA ESTA DADA DE BAJA." << endl;
        return;
    }

    objMesa.setEstado(false);
    if(objArchivoMesa.guardar(objMesa, pos))
    {
        cout << "!! SE DIO DE BAJA CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO DAR DE BAJA !!" << endl;
    }
}

void MesaManager :: listadoPorNumeroMesa()
{
    ArchivoMesa objArchivoMesa;
    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();
    int mostrados = 0;

    if(cantidadRegistros == 0)
    {
        cout << "NO HAY MESAS REGISTRADAS." << endl;
        return;
    }

    Mesa *vec = new Mesa[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoMesa.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int j = i + 1; j < cantidadRegistros; j++)
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
        if(vec[i].getEstado())
        {
            vec[i].mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY MESAS ACTIVAS." << endl;
    }

    delete[]vec;
}

void MesaManager :: listadoPorUbicacion()
{
    ArchivoMesa objArchivoMesa;
    Mesa objMesa;
    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();
    int mostrados = 0;

    cout << "UBICACION : INTERIOR " << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMesa = objArchivoMesa.leer(i);
        if(objMesa.getEstado() && objMesa.getUbicacion() == 1)
        {
            objMesa.mostrar();
            mostrados++;
        }
    }

    cout << endl;
    cout << "UBICACION : TERRAZA " << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMesa = objArchivoMesa.leer(i);
        if(objMesa.getEstado() && objMesa.getUbicacion() == 2)
        {
            objMesa.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY MESAS ACTIVAS." << endl;
    }
}

void MesaManager :: consultaPorNumeroMesa()
{
    ArchivoMesa objArchivoMesa;
    Mesa objMesa;
    int nroMesa;

    nroMesa = leerEntero("INGRESE EL NUMERO DE MESA : ");

    int pos = objArchivoMesa.buscar(nroMesa);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO LA MESA." << endl;
        return;
    }

    objMesa = objArchivoMesa.leer(pos);
    if(objMesa.getEstado())
    {
        objMesa.mostrar();
    }
    else
    {
        cout << "LA MESA ESTA DADA DE BAJA." << endl;
    }
}

void MesaManager :: consultaPorUbicacion()
{
    ArchivoMesa objArchivoMesa;
    Mesa objMesa;
    int cantidadRegistros = objArchivoMesa.getCantidadRegistros();
    int ubicacion;
    int mostrados = 0;

    ubicacion = leerEnteroEnRango("INGRESE LA UBICACION (1-INTERIOR / 2-TERRAZA): ", 1, 2);

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objMesa = objArchivoMesa.leer(i);
        if(objMesa.getEstado() && objMesa.getUbicacion() == ubicacion)
        {
            objMesa.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO SE ENCONTRARON MESAS PARA ESA UBICACION." << endl;
    }
}
