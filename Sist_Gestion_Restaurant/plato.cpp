#include <iostream>
#include <cstring>
using namespace std;
#include "plato.h"
#include "inputUtils.h"

Plato :: Plato(){

    _idPlato = 0;
    strcpy(_nombre,"");
    _categoria = 0;
    _precio = 0;
    _estado = false;

}

/// SETTERS
void Plato :: setIdPlato(int id){
    _idPlato = id;
}
void Plato :: setNombre(char* nombre){
    strcpy(_nombre,nombre);
}
void Plato :: setCategoria(int categoria){
    _categoria = categoria;
}
void Plato :: setPrecio(float precio){
    _precio = precio;
}
void Plato :: setEstado(bool estado){
    _estado = estado;
}

/// GETTERS

int Plato :: getIdPlato(){
    return _idPlato;
}
char* Plato :: getNombre(){
    return _nombre;
}
int Plato :: getCategoria(){
    return _categoria;
}
float Plato :: getPrecio(){
    return _precio;
}
bool Plato :: getEstado(){
    return _estado;
}

///
void Plato :: cargar(){
    char nombre[50];
    int categoria;
    float precio;

    cout << "INGRESE LA INFORMACION DEL PLATO.." << endl;

    leerCadena("NOMBRE : ", nombre, 50);

    cout << "CATEGORIA.. " << endl;
    cout << "1/ ENTRADA" << endl;
    cout << "2/ PRINCIPAL" << endl;
    cout << "3/ POSTRE" << endl;
    cout << "4/ BEBIDA" << endl;
    categoria = leerEnteroEnRango("INGRESE : ", 1, 4);

    precio = leerFloatMinimo("PRECIO : ", 0.01f);


    setCategoria(categoria);
    setNombre(nombre);
    setPrecio(precio);
    setEstado(true);
}
void Plato :: mostrar(){

    cout << "-----------------------------------------" << endl;
    cout << "ID PLATO : " << _idPlato << endl;
    cout << "NOMBRE : " << _nombre << endl;
    cout << "PRECIO : " << _precio << endl;
    cout << "CATEGORIA : ";
    switch(_categoria){
        case 1 : cout << "ENTRADA";
        break;
        case 2 : cout << "PRINCIPAL";
        break;
        case 3 : cout << "POSTRE";
        break;
        case 4 : cout << "BEBIDA";
        break;
    }
    cout << endl;
    cout << "ESTADO : " << (_estado ? "ACTIVO" : "INACTIVO") << endl;
}
