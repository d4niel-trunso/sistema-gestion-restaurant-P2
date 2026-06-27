#include <iostream>
#include <cstdio>
#include "reservaArchivo.h"

using namespace std;

ReservaArchivo::ReservaArchivo(){
    _ruta = "Reservas.dat";
}

ReservaArchivo::ReservaArchivo(std::string ruta){
    _ruta = ruta;
}

int ReservaArchivo::getCantidadRegistros(){
    FILE *pFile = fopen(_ruta.c_str(), "rb");

    if(pFile == NULL){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    int bytes = ftell(pFile);
    fclose(pFile);

    return bytes / sizeof(Reserva);
}

bool ReservaArchivo::guardar(Reserva reg){
    FILE *pFile = fopen(_ruta.c_str(), "ab");

    if(pFile == NULL){
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    bool pudoEscribir = fwrite(&reg, sizeof(Reserva), 1, pFile);
    fclose(pFile);

    return pudoEscribir;
}

bool ReservaArchivo::guardar(Reserva reg, int posicionAReemplazar){
    FILE *pFile = fopen(_ruta.c_str(), "rb+");

    if(pFile == NULL){
        cout << "Error al abrir el archivo." << endl;
        return false;
    }

    fseek(pFile, posicionAReemplazar * sizeof(Reserva), SEEK_SET);
    bool pudoEscribir = fwrite(&reg, sizeof(Reserva), 1, pFile);
    fclose(pFile);

    return pudoEscribir;
}

Reserva ReservaArchivo::leer(int nroRegistro){
    Reserva aux;
    FILE *pFile = fopen(_ruta.c_str(), "rb");

    if(pFile == NULL){
        return aux;
    }

    fseek(pFile, nroRegistro * sizeof(Reserva), SEEK_SET);
    fread(&aux, sizeof(Reserva), 1, pFile);
    fclose(pFile);

    return aux;
}

void ReservaArchivo::leer(Reserva *vec, int cantidadRegistrosALeer){
    FILE *pFile = fopen(_ruta.c_str(), "rb");

    if(pFile == NULL){
        cout << "Error no se pudo abrir el archivo." << endl;
        return;
    }

    fread(vec, sizeof(Reserva), cantidadRegistrosALeer, pFile);
    fclose(pFile);
}

int ReservaArchivo::buscar(int ID){
    int i;
    int cantidadRegistros = getCantidadRegistros();
    Reserva aux;

    for(i = 0; i < cantidadRegistros; i++){
        aux = leer(i);
        if(aux.getIdReserva() == ID){
            return i;
        }
    }
    return -1;
}

void ReservaArchivo::vaciar(){
    FILE *pFile = fopen(_ruta.c_str(), "wb");

    if(pFile == NULL){
        cout << "Error al vaciar el archivo." << endl;
        return;
    }

    fclose(pFile);
}
