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
