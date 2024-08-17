#ifndef MESAS_H
#define MESAS_H
#include <QDate>
#include <QTime>
#include <QVector>
#include <QPair>

class Mesas {
public:
    Mesas(int id) : id(id) {}

    bool estaDisponible(const QDate &fecha, const QTime &hora) const {
        for (const auto &reserva : reservas) {
            if (reserva.first == fecha && reserva.second == hora) {
                return false;
            }
        }
        return true;
    }

    void reservar(const QDate &fecha, const QTime &hora) {
        reservas.append(qMakePair(fecha, hora));
    }

private:
    int id;
    QVector<QPair<QDate, QTime>> reservas;
};
#endif // MESAS_H
