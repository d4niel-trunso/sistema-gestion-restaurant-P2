#include <iostream>
#include <cstdio>
#include "facturaArchivo.h"

using namespace std;

FacturaArchivo::FacturaArchivo(){
    _ruta = "Facturas.dat";
}

FacturaArchivo::FacturaArchivo(std::string ruta){
    _ruta = ruta;
}

bool FacturaArchivo::guardar(Factura reg){
    FILE *pFile = fopen(_ruta.c_str(), "ab");

    if(pFile == NULL){
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    bool pudoEscribir = fwrite(&reg, sizeof(Factura), 1, pFile);
    fclose(pFile);

    return pudoEscribir;
}

bool FacturaArchivo::guardar(Factura reg, int pos){
    FILE *pFile = fopen(_ruta.c_str(), "rb+");

    if(pFile == NULL){
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    fseek(pFile, pos * sizeof(Factura), SEEK_SET);
    bool pudoEscribir = fwrite(&reg, sizeof(Factura), 1, pFile);
    fclose(pFile);

    return pudoEscribir;
}

Factura FacturaArchivo::leer(int pos){
    Factura aux;
    FILE *pFile = fopen(_ruta.c_str(), "rb");

    if(pFile == NULL){
        return aux;
    }

    fseek(pFile, pos * sizeof(Factura), SEEK_SET);
    fread(&aux, sizeof(Factura), 1, pFile);
    fclose(pFile);

    return aux;
}

int FacturaArchivo::getCantidadRegistros(){
    FILE *pFile = fopen(_ruta.c_str(), "rb");

    if(pFile == NULL){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / sizeof(Factura);
}

int FacturaArchivo::buscarPosicion(int idFactura){
    int i;
    int cantidadRegistros = getCantidadRegistros();
    Factura aux;

    for(i = 0; i < cantidadRegistros; i++){
        aux = leer(i);
        if(aux.getIdFactura() == idFactura){
            return i;
        }
    }
    return -1;
}
