#include <iostream>
#include <cstring>
using namespace std;
#include "cliente.h"
#include "archivoCliente.h"

ArchivoCliente :: ArchivoCliente(){
    strcpy(_nombreArchivo,"clientes.dat");
}

int ArchivoCliente :: getCantidadRegistros(){

    FILE *p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return 0;
    }

    fseek(p,0,SEEK_END);
    int cantidad = ftell(p) / sizeof(Cliente);

    fclose(p);

    return cantidad;
}
bool ArchivoCliente :: guardar(Cliente obj){

    FILE *p = fopen(_nombreArchivo,"ab");

    if(p == nullptr){
        return false;
    }

    bool escribio = fwrite(&obj, sizeof(Cliente),1,p);

    fclose(p);

    return escribio;

}
Cliente ArchivoCliente :: leer(int pos){

    Cliente obj;

    FILE *p = fopen(_nombreArchivo,"rb");

    if(p == nullptr){
        return obj;
    }

    fseek(p, sizeof(Cliente) * pos,SEEK_SET);

    fread(&obj, sizeof(Cliente),1,p);

    fclose(p);

    return obj;

}
