#include <iostream>
#include <cstring>
using namespace std;
#include "ArchivoMozo.h"
#include "Mozo.h"

ArchivoMozo :: ArchivoMozo(){
    strcpy(_nombreArchivo,"mozos.dat");
}

int ArchivoMozo :: getCantidadRegistros(){

    FILE *p = fopen(_nombreArchivo,"rb");

    if( p == nullptr){
        return 0;
    }

    fseek(p,0,SEEK_END);

    int cantidad = ftell(p) / sizeof(Mozo);

    fclose(p);

    return cantidad;

}
bool ArchivoMozo :: guardar(Mozo obj){

    FILE *p = fopen(_nombreArchivo,"ab");

    if(p == nullptr){
        return false;
    }

    bool escribio = fwrite(&obj,sizeof(Mozo),1,p);

    fclose(p);

    return escribio;

}
Mozo ArchivoMozo :: leer(int pos){

    Mozo obj;

    FILE *p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return obj;
    }

    fseek(p,pos * sizeof(Mozo),SEEK_SET);

    fread(&obj,sizeof(Mozo),1,p);

    fclose(p);

    return obj;

}
