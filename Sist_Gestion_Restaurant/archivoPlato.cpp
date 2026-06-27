#include <iostream>
#include <cstring>
using namespace std;
#include "archivoPlato.h"
#include "plato.h"

ArchivoPlato :: ArchivoPlato(){
    strcpy(_nombreArchivo,"platos.dat");
}

int ArchivoPlato :: getCantidadRegistros(){

    FILE *p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return 0;
    }

    fseek(p,0,SEEK_END);

    int cantidad = ftell(p)/ sizeof(Plato);

    fclose(p);

    return cantidad;
}
bool ArchivoPlato :: guardar(Plato obj){

    FILE *p = fopen(_nombreArchivo,"ab");

    if(p == nullptr){
        return false;
    }

    bool escribio = fwrite(&obj, sizeof(Plato),1,p);

    fclose(p);

    return escribio;

}
Plato ArchivoPlato :: leer(int pos){

    Plato obj;

    FILE *p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return obj;
    }

    fseek(p,sizeof(Plato)*pos,SEEK_SET);

    fread(&obj,sizeof(Plato),1,p);

    fclose(p);

    return obj;

}
