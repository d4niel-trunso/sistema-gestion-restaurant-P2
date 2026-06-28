#include <iostream>
#include "detalleFacturaManager.h"
#include "utilidades.h"

using namespace std;

int DetalleFacturaManager::generarID(int desplazamiento){
    return _archivo.getCantidadRegistros() + 1 + desplazamiento;
}

bool DetalleFacturaManager::platoActivo(int idPlato, Plato &plato){
    int pos = _archivoPlato.buscar(idPlato);

    if(pos < 0){
        return false;
    }

    plato = _archivoPlato.leer(pos);
    return plato.getEstado();
}

bool DetalleFacturaManager::cargarDetallesFactura(int idFactura, DetalleFactura *&detalles, int &cantidadDetalles, float &importeTotal){
    int continuar = 1;
    int idPlato;
    int cantidad;
    int capacidad = 4;
    Plato plato;

    delete[] detalles;
    detalles = new DetalleFactura[capacidad];
    cantidadDetalles = 0;
    importeTotal = 0;

    while(continuar == 1){
        idPlato = leerEntero("ID Plato: ");

        if(!platoActivo(idPlato, plato)){
            cout << "No existe un plato activo con ese ID." << endl;
        }else{
            cantidad = leerEnteroEnRango("Cantidad: ", 1, 1000);

            DetalleFactura detalle;
            detalle.setIdDetalle(generarID(cantidadDetalles));
            detalle.setIdFactura(idFactura);
            detalle.setIdPlato(idPlato);
            detalle.setCantidad(cantidad);
            detalle.setPrecioUnitario(plato.getPrecio());
            detalle.setEstado(true);

            if(cantidadDetalles == capacidad){
                int nuevaCapacidad = capacidad * 2;
                DetalleFactura *detallesAux = new DetalleFactura[nuevaCapacidad];

                for(int i = 0; i < cantidadDetalles; i++){
                    detallesAux[i] = detalles[i];
                }

                delete[] detalles;
                detalles = detallesAux;
                capacidad = nuevaCapacidad;
            }

            detalles[cantidadDetalles] = detalle;
            cantidadDetalles++;
            importeTotal += cantidad * plato.getPrecio();

            cout << "Detalle agregado. Subtotal: $" << cantidad * plato.getPrecio() << endl;
        }

        continuar = leerEnteroEnRango("Agregar otro plato? (1-SI / 0-NO): ", 0, 1);
    }

    return cantidadDetalles > 0;
}

bool DetalleFacturaManager::guardarDetalles(DetalleFactura *detalles, int cantidadDetalles){
    for(int i = 0; i < cantidadDetalles; i++){
        if(!_archivo.guardar(detalles[i])){
            return false;
        }
    }

    return true;
}

void DetalleFacturaManager::listarPorFactura(int idFactura){
    int cantidad = _archivo.getCantidadRegistros();
    bool encontro = false;

    for(int i = 0; i < cantidad; i++){
        DetalleFactura detalle = _archivo.leer(i);
        if(detalle.getEstado() && detalle.getIdFactura() == idFactura){
            Plato plato;
            cout << "-----------------------------------------" << endl;
            cout << "Detalle #" << detalle.getIdDetalle() << endl;
            cout << "Plato: ";
            if(platoActivo(detalle.getIdPlato(), plato)){
                cout << plato.getNombre() << " (ID " << detalle.getIdPlato() << ")";
            }else{
                cout << "No encontrado (ID " << detalle.getIdPlato() << ")";
            }
            cout << endl;
            cout << "Cantidad: " << detalle.getCantidad() << endl;
            cout << "Precio unitario: $" << detalle.getPrecioUnitario() << endl;
            cout << "Subtotal: $" << detalle.getCantidad() * detalle.getPrecioUnitario() << endl;
            encontro = true;
        }
    }

    if(!encontro){
        cout << "No hay detalles activos para esa factura." << endl;
    }
}

void DetalleFacturaManager::listarTodos(){
    int cantidad = _archivo.getCantidadRegistros();

    if(cantidad == 0){
        cout << "No hay detalles registrados." << endl;
        return;
    }

    for(int i = 0; i < cantidad; i++){
        DetalleFactura detalle = _archivo.leer(i);
        if(detalle.getEstado()){
            detalle.mostrar();
        }
    }
}

void DetalleFacturaManager::anularDetallesFactura(int idFactura){
    int cantidad = _archivo.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++){
        DetalleFactura detalle = _archivo.leer(i);
        if(detalle.getEstado() && detalle.getIdFactura() == idFactura){
            detalle.setEstado(false);
            _archivo.guardar(detalle, i);
        }
    }
}
