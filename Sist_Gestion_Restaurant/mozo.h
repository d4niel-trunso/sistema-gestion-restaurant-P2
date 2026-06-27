#pragma once

#include "persona.h"
#include "fecha.h"

class Mozo : public Persona {

private :

    int _idMozo;
    char _email [50];
    int _turno;
    Fecha _fechaNacimiento;

public :

    mozo();

    /// SETTERS
    void setIdMozo(int idMozo);
    void setEmail(char* email);
    void setTurno(int valor);
    void setFechaNacimiento(int dia, int mes, int anio);

    /// GETTERS
    Fecha getFechaNacimiento();
    int getIdMozo();
    int getTurno();
    char* getEmail();

    ///
    void cargar();
    void mostrar();

};
