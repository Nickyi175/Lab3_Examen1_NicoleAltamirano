#ifndef RESERVA_H
#define RESERVA_H

#include "cliente.h"
#include <QVector>
#include <QPair>
#include <QDebug>
#include <QMessageBox>

class Reserva : public Cliente {
public:

    Reserva(int id, const QString &nombreCliente, int numTelefono, int numComensales, const QDate &fechaReserva, const QTime &horaReserva);

    QString getNombreCliente() const { return nombreCliente; }
    int getTelefono() const { return numTelefono; }
    int getComensales() const { return numComensales; }
    QDate getFecha() const { return fechaReserva; }
    QTime getHora() const { return horaReserva; }
    void mostrarDatos() const;
    QString getInfo() const override;
    void setMesaAsignada(int mesa) { mesaAsignada = mesa; }
    static int obtenerMesasDisponibles(const QDate &fecha, const QTime &hora);
    static bool verificarDisponibilidad(const QDate &fecha, const QTime &hora);
    static void agregarReserva(Reserva *reserva);
    static void eliminarReserva(int id);
    static QString obtenerReservas();
    //static int obtenerNumeroReservas();

    static int mesasDisponibles;

    static QVector<Reserva*> obtenerReservasPorId(int id) {
        QVector<Reserva*> reservasEncontradas;
        for (const auto &reserva : reservas) {
            if (reserva->getId() == id) {
                reservasEncontradas.append(reserva);
            }
        }
        return reservasEncontradas;
    }
    //static const QVector<Reserva*>& obtenerReservass();
    static int obtenerNumeroMesaAsignado(const QDate &fecha, const QTime &hora);
    static const QVector<Reserva*>& getReservasList() {
        return reservas;
    }

private:

    static QVector<Reserva*> reservas;

    int mesaAsignada;
};


#endif // RESERVA_H
