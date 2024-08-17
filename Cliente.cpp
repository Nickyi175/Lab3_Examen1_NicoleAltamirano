#include "Cliente.h"

// Cliente::Cliente() {}
void Cliente::setNombreCliente(const QString& nombre) {
    nombreCliente = nombre;
}

void Cliente::setTelefono(int telefono) {
    numTelefono = telefono;
}

void Cliente::setComensales(int comensales) {
    numComensales = comensales;
}

void Cliente::setFecha(const QDate& fecha) {
    fechaReserva = fecha;
}

void Cliente::setHora(const QTime& hora) {
    horaReserva = hora;
}
