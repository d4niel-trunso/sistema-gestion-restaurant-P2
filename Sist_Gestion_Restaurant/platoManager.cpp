#include <iostream>
#include <cstring>
#include "archivoPlato.h"
#include "platoManager.h"
#include "plato.h"
#include "rlutil.h"

using namespace std;

PlatoManager :: PlatoManager()
{
    setCantidadOpciones(8);
}

void PlatoManager :: mostrarOpciones()
{
    rlutil::setBackgroundColor(rlutil::GREEN);
    rlutil::setColor(rlutil::WHITE);
    rlutil::cls();

    cout << "-------- MENU DE PLATOS --------" << endl;
    cout << "1. ALTA DE PLATO" << endl;
    cout << "2. MODIFICAR PLATO" << endl;
    cout << "3. BAJA DE PLATO" << endl;
    cout << "4. LISTAR POR NOMBRE" << endl;
    cout << "5. LISTAR POR CATEGORIA" << endl;
    cout << "6. LISTAR POR PRECIO" << endl;
    cout << "7. CONSULTAR POR CATEGORIA" << endl;
    cout << "8. CONSULTAR POR RANGO DE PRECIOS" << endl;
    cout << "0. VOLVER" << endl;
    cout << "-------------------------------" << endl;
}

void PlatoManager :: ejecutarOpcion(int opcion)
{
    switch(opcion)
    {
    case 1:
        altaPlato();
        break;
    case 2:
        modificarPlato();
        break;
    case 3:
        bajaPlato();
        break;
    case 4:
        listadoPorNombre();
        break;
    case 5:
        listadoPorCategoria();
        break;
    case 6:
        listadoPorPrecio();
        break;
    case 7:
        consultaPorCategoria();
        break;
    case 8:
        consultaPorRangoDePrecios();
        break;
    case 0:
        cout << "Volviendo al menu principal..." << endl;
        break;
    }
}

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

void PlatoManager :: modificarPlato()
{
    ArchivoPlato objArchivoPlato;
    Plato objPlato;
    int idPlato;

    cout << "INGRESE ID DEL PLATO A MODIFICAR: ";
    cin >> idPlato;

    int pos = objArchivoPlato.buscar(idPlato);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO EL PLATO." << endl;
        return;
    }

    objPlato = objArchivoPlato.leer(pos);
    if(!objPlato.getEstado())
    {
        cout << "EL PLATO ESTA DADO DE BAJA." << endl;
        return;
    }

    cout << "DATOS ACTUALES:" << endl;
    objPlato.mostrar();

    objPlato.cargar();
    objPlato.setIdPlato(idPlato);

    if(objArchivoPlato.guardar(objPlato, pos))
    {
        cout << "!! SE MODIFICO CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO MODIFICAR !!" << endl;
    }
}

void PlatoManager :: bajaPlato()
{
    ArchivoPlato objArchivoPlato;
    Plato objPlato;
    int idPlato;

    cout << "INGRESE ID DEL PLATO A DAR DE BAJA: ";
    cin >> idPlato;

    int pos = objArchivoPlato.buscar(idPlato);
    if(pos < 0)
    {
        cout << "NO SE ENCONTRO EL PLATO." << endl;
        return;
    }

    objPlato = objArchivoPlato.leer(pos);
    if(!objPlato.getEstado())
    {
        cout << "EL PLATO YA ESTA DADO DE BAJA." << endl;
        return;
    }

    objPlato.setEstado(false);
    if(objArchivoPlato.guardar(objPlato, pos))
    {
        cout << "!! SE DIO DE BAJA CORRECTAMENTE !!" << endl;
    }
    else
    {
        cout << "!! ERROR , NO SE PUDO DAR DE BAJA !!" << endl;
    }
}

void PlatoManager :: listadoPorNombre()
{
    ArchivoPlato objArchivoPlato;
    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();
    int mostrados = 0;

    if(cantidadRegistros == 0)
    {
        cout << "NO HAY PLATOS REGISTRADOS." << endl;
        return;
    }

    Plato* vec = new Plato[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoPlato.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int k = i + 1; k < cantidadRegistros; k++)
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
        if(vec[i].getEstado())
        {
            vec[i].mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY PLATOS ACTIVOS." << endl;
    }

    delete[]vec;
}

void PlatoManager :: listadoPorCategoria()
{
    ArchivoPlato objArchivoPlato;
    Plato objPlato;
    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();
    int mostrados = 0;

    cout << "-- CATEGORIA : ENTRADA --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objPlato = objArchivoPlato.leer(i);
        if(objPlato.getEstado() && objPlato.getCategoria() == 1)
        {
            objPlato.mostrar();
            mostrados++;
        }
    }

    cout << "-- CATEGORIA : PLATO PRINCIPAL --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objPlato = objArchivoPlato.leer(i);
        if(objPlato.getEstado() && objPlato.getCategoria() == 2)
        {
            objPlato.mostrar();
            mostrados++;
        }
    }

    cout << "-- CATEGORIA : POSTRE --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objPlato = objArchivoPlato.leer(i);
        if(objPlato.getEstado() && objPlato.getCategoria() == 3)
        {
            objPlato.mostrar();
            mostrados++;
        }
    }

    cout << "-- CATEGORIA : BEBIDA --" << endl;
    for(int i = 0; i < cantidadRegistros; i++)
    {
        objPlato = objArchivoPlato.leer(i);
        if(objPlato.getEstado() && objPlato.getCategoria() == 4)
        {
            objPlato.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO HAY PLATOS ACTIVOS." << endl;
    }
}

void PlatoManager :: listadoPorPrecio()
{
    ArchivoPlato objArchivoPlato;
    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();
    int mostrados = 0;

    if(cantidadRegistros == 0)
    {
        cout << "NO HAY PLATOS REGISTRADOS." << endl;
        return;
    }

    Plato *vec = new Plato[cantidadRegistros];

    for(int i = 0; i < cantidadRegistros; i++)
    {
        vec[i] = objArchivoPlato.leer(i);
    }

    for(int i = 0; i < cantidadRegistros - 1; i++)
    {
        for(int j = i + 1; j < cantidadRegistros; j++)
        {
            if(vec[i].getPrecio() > vec[j].getPrecio())
            {
                Plato aux = vec[i];
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
        cout << "NO HAY PLATOS ACTIVOS." << endl;
    }

    delete[]vec;
}

void PlatoManager :: consultaPorCategoria()
{
    ArchivoPlato objArchivoPlato;
    Plato objPlato;
    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();
    int categoria;
    int mostrados = 0;

    cout << "INGRESE LA CATEGORIA : " << endl;
    cout << "1/ ENTRADA" << endl;
    cout << "2/ PRINCIPAL" << endl;
    cout << "3/ POSTRE" << endl;
    cout << "4/ BEBIDA" << endl;
    cin >> categoria;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objPlato = objArchivoPlato.leer(i);
        if(objPlato.getEstado() && categoria == objPlato.getCategoria())
        {
            objPlato.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO SE ENCONTRARON PLATOS PARA ESA CATEGORIA." << endl;
    }
}

void PlatoManager :: consultaPorRangoDePrecios()
{
    ArchivoPlato objArchivoPlato;
    Plato objPlato;
    int cantidadRegistros = objArchivoPlato.getCantidadRegistros();
    float desde;
    float hasta;
    int mostrados = 0;

    cout << "INGRESE DESDE CUANTO : ";
    cin >> desde;
    cout << "INGRESE HASTA CUANTO : ";
    cin >> hasta;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        objPlato = objArchivoPlato.leer(i);
        if(objPlato.getEstado() && objPlato.getPrecio() >= desde && objPlato.getPrecio() <= hasta )
        {
            objPlato.mostrar();
            mostrados++;
        }
    }

    if(mostrados == 0)
    {
        cout << "NO SE ENCONTRARON PLATOS EN ESE RANGO." << endl;
    }
}
