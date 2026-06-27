#pragma once

#include "fecha.h"
#include "factura.h"
#include "reserva.h"

void configurarConsola();
void leerCadena(const char* mensaje, char* destino, int tamanio);
int leerEntero(const char* mensaje);
int leerEnteroEnRango(const char* mensaje, int minimo, int maximo);
float leerFloatMinimo(const char* mensaje, float minimo);
bool leerSiNo(const char* mensaje);
Fecha leerFecha(const char* mensaje);
void ordenarFacturasPorFecha(Factura *facturas, int cantidad);
void ordenarFacturasPorMesa(Factura *facturas, int cantidad);
void ordenarReservasPorFecha(Reserva *reservas, int cantidad);
void ordenarReservasPorEstado(Reserva *reservas, int cantidad);
