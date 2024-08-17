#ifndef CLIENTE_H
#define CLIENTE_H
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include "Mesas.h"

class Cliente
{
protected:
    int id;
    QString nombreCliente;
    int numTelefono;
    int numComensales;
    QDate fechaReserva;
    QTime horaReserva;

public:
    Cliente(const int &id, const QString &nombreCliente, const int &numTelefono,
             int numComensales, const QDate &fechaReserva, const QTime &horaReserva)
        : id(id), nombreCliente(nombreCliente), numTelefono(numTelefono),
        numComensales(numComensales), fechaReserva(fechaReserva), horaReserva(horaReserva) {}

    virtual ~Cliente() = default;
    int getId() const { return id; }
    virtual QString getInfo() const {
        return QString("Nombre: "+ nombreCliente + "\nNúmero de identidad: "+ QString::number(id)+
                       "\nNúmero de Comensales: "+QString::number(numComensales)+
                       "\nNúmero de Contacto: "+QString::number(numTelefono)+"\nFecha: "+fechaReserva.toString("dd/MM/yyyy")+
                       "\nHora: "+horaReserva.toString("HH:mm")+"\n");
    }
    void setNombreCliente(const QString& nombre);
    void setTelefono(int telefono);
    void setComensales(int comensales);
    void setFecha(const QDate& fecha);
    void setHora(const QTime& hora);
};

#endif // CLIENTE_H
