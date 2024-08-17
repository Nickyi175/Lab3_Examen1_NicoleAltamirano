#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDateEdit>
#include <QTimeEdit>
#include <QSpinBox>
#include <QTextEdit>
#include "mesas.h"
#include "reserva.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_menuPersonal_clicked();

    void on_btn_menuCliente_clicked();

    void on_btn_salir_clicked();

    void on_btn_reservar_clicked();

    void on_btn_aceptarReserva_clicked();

    void on_btn_numMesas_clicked();

    void on_btn_cancelarReserva_clicked();

private:
    Ui::MainWindow *ui;
    QVector<Mesas> mesas;
    void inicializarMesas(int cantidad);
};
#endif // MAINWINDOW_H
