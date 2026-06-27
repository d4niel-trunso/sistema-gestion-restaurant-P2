#pragma once

#include "fecha.h"

void configurarConsola();
void leerCadena(const char* mensaje, char* destino, int tamanio);
int leerEntero(const char* mensaje);
int leerEnteroEnRango(const char* mensaje, int minimo, int maximo);
float leerFloatMinimo(const char* mensaje, float minimo);
bool leerSiNo(const char* mensaje);
Fecha leerFecha(const char* mensaje);
