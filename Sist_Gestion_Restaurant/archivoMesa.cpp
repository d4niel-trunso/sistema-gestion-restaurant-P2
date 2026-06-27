#include <iostream>
#include <cstring>
using namespace std;
#include "archivoMesa.h"
#include "mesa.h"

ArchivoMesa :: ArchivoMesa()
{
    strcpy(_nombreArchivo,"mesa.dat");
}

int ArchivoMesa :: getCantidadRegistros()
{
    FILE *p = fopen(_nombreArchivo,"rb");

    if(p == nullptr)
    {
        return 0;
    }

    fseek(p,0,SEEK_END);

    int cantidad = ftell(p) / sizeof(Mesa);

    fclose(p);

    return cantidad;

}
bool ArchivoMesa :: guardar(Mesa obj)
{

    FILE* p = fopen(_nombreArchivo,"ab");

    if(p == nullptr)
    {
        return false;
    }

    bool escribio = fwrite(&obj,sizeof(Mesa),1,p);

    fclose(p);

    return escribio;

}
bool ArchivoMesa :: guardar(Mesa obj, int pos)
{

    FILE* p = fopen(_nombreArchivo,"rb+");

    if(p == nullptr)
    {
        return false;
    }

    fseek(p,sizeof(Mesa)*pos,SEEK_SET);

    bool escribio = fwrite(&obj,sizeof(Mesa),1,p);

    fclose(p);

    return escribio;

}
Mesa ArchivoMesa :: leer(int pos)
{

    Mesa obj;

    FILE* p = fopen(_nombreArchivo,"rb");

    if(p == nullptr)
    {
        return obj;
    }

    fseek(p,sizeof(Mesa)*pos,SEEK_SET);

    fread(&obj,sizeof(Mesa),1,p);

    fclose(p);

    return obj;

}

int ArchivoMesa :: buscar(int numeroMesa)
{
    int cantidadRegistros = getCantidadRegistros();
    Mesa obj;

    for(int i = 0; i < cantidadRegistros; i++)
    {
        obj = leer(i);
        if(obj.getNumeroMesa() == numeroMesa)
        {
            return i;
        }
    }

    return -1;
}
