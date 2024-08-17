#include "Reserva.h"
#include <QMessageBox>

QVector<Reserva*> Reserva::reservas;
int Reserva::mesasDisponibles = 5;

Reserva::Reserva(int id, const QString &nombre, int telefono, int comensales, const QDate &fecha, const QTime &hora)
    : Cliente(id, nombre, telefono, comensales, fecha, hora) {
}

void Reserva::mostrarDatos() const {
    qDebug() << "ID:" << id << "Nombre:" << nombreCliente << "Telefono:" << numTelefono << "Comensales:" << numComensales << "Fecha:" << fechaReserva << "Hora:" << horaReserva;
}

bool Reserva::verificarDisponibilidad(const QDate &fecha, const QTime &hora) {
    int mesasOcupadas = 0;
    for (const auto &reserva : reservas) {
        if (reserva->fechaReserva == fecha && reserva->horaReserva == hora) {
            mesasOcupadas++;
        }
    }
    return mesasOcupadas < mesasDisponibles;
}

int Reserva::obtenerMesasDisponibles(const QDate &fecha, const QTime &hora) {
    int mesasOcupadas = 0;

    for (const auto &reserva : reservas) {
        if (reserva->fechaReserva == fecha && reserva->horaReserva == hora) {
            mesasOcupadas++;
        }
    }

    int mesasTotales = 5;
    return mesasTotales - mesasOcupadas;
}

// const QVector<Reserva*>& Reserva::obtenerReservass() {
//     return reservas;
// }

void Reserva::agregarReserva(Reserva *reserva) {
    if (verificarDisponibilidad(reserva->fechaReserva, reserva->horaReserva)) {
        reservas.append(reserva);
        int numeroMesa = obtenerNumeroMesaAsignado(reserva->fechaReserva, reserva->horaReserva);
        QMessageBox::information(nullptr, "Reserva Confirmada",
                                 QString("Reserva realizada exitosamente para el ID: %1\nNúmero de mesa asignado: %2")
                                     .arg(reserva->getId())
                                     .arg(numeroMesa));
    } else {
        QMessageBox::warning(nullptr, "Sin Disponibilidad",
                             "No hay mesas disponibles para la fecha y hora seleccionadas.");
    }
}

int Reserva::obtenerNumeroMesaAsignado(const QDate &fecha, const QTime &hora) {
    int mesaAsignada = -1;

    int mesasOcupadas = 0;
    for (const auto &reserva : reservas) {
        if (reserva->fechaReserva == fecha && reserva->horaReserva == hora) {
            mesasOcupadas++;
        }
    }
    if (mesasOcupadas < mesasDisponibles) {
        mesaAsignada = mesasOcupadas;
    }else{
        mesaAsignada = mesasDisponibles;
    }

    return mesaAsignada;
}

void Reserva::eliminarReserva(int id) {
    for (int i = 0; i < reservas.size(); ++i) {
        if (reservas[i]->getId() == id) {
            delete reservas[i];
            reservas.remove(i);
            return;
        }
    }
}

QString Reserva::getInfo() const  {
    return Cliente::getInfo() + "Mesa Asignada: " + QString::number(mesaAsignada + 1) + "\n";
}

QString Reserva::obtenerReservas() {
    QString lista;
    for (const auto &reserva : reservas) {
        lista += QString("ID: %1 \nNombre: %2 \nTelefono: %3 \nNúmero de Comensales: %4 \nFecha: %5 \nHora: %6\n")
        .arg(reserva->getId())
            .arg(reserva->nombreCliente)
            .arg(reserva->numTelefono)
            .arg(reserva->numComensales)
            .arg(reserva->fechaReserva.toString())
            .arg(reserva->horaReserva.toString());
    }
    return lista;
}
