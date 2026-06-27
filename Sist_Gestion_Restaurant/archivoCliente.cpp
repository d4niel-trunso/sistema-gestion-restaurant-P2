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
bool ArchivoCliente :: guardar(Cliente obj, int pos){

    FILE *p = fopen(_nombreArchivo,"rb+");

    if(p == nullptr){
        return false;
    }

    fseek(p, sizeof(Cliente) * pos,SEEK_SET);

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

int ArchivoCliente :: buscar(int id){

    int cantidadRegistros = getCantidadRegistros();
    Cliente obj;

    for(int i = 0; i < cantidadRegistros; i++){
        obj = leer(i);
        if(obj.getIdCliente() == id){
            return i;
        }
    }

    return -1;
}
