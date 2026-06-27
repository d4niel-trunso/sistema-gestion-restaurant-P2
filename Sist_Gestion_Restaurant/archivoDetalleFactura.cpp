#include <iostream>
#include <cstring>
using namespace std;
#include "ArchivoDetalleFactura.h"
#include "DetalleFactura.h"

ArchivoDetalleFactura :: ArchivoDetalleFactura(){
    strcpy(_nombreArchivo,"detalles.dat");
}

int ArchivoDetalleFactura :: getCantidadRegistros(){

    FILE* p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return 0;
    }

    fseek(p,0,SEEK_END);

    int cantidad = ftell(p) / sizeof(DetalleFactura);

    fclose(p);

    return cantidad;
}
bool ArchivoDetalleFactura :: guardar(DetalleFactura obj){

    FILE* p = fopen(_nombreArchivo,"ab");

    if(p == nullptr){
        return false;
    }

    bool escribio = fread(&obj,sizeof(DetalleFactura),1,p);

    fclose(p);

    return escribio;

}
DetalleFactura ArchivoDetalleFactura :: leer(int pos){

    DetalleFactura obj;

    FILE* p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return obj;
    }

    fseek(p,pos * sizeof(DetalleFactura),SEEK_SET);

    fread(&obj,sizeof(DetalleFactura),1,p);

    fclose(p);

    return obj;

}
