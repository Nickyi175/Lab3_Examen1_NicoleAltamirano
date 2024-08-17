#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include "Reserva.h"
#include <QDate>
#include <QTime>
#include "Mesas.h"
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inicializarMesas(5);
    QRegularExpression idRegex("\\d+");
    QRegularExpressionValidator *idValidator = new QRegularExpressionValidator(idRegex, this);
    ui->lE_id->setValidator(idValidator);
    QRegularExpression telRegex("\\d{8}");
    QRegularExpressionValidator *telValidator = new QRegularExpressionValidator(telRegex, this);
    ui->lE_numTel->setValidator(telValidator);
    ui->dateEdit_fechaReserva->setDate(QDate::currentDate());
    ui->timeEdit_horaReserva->setTime(QTime::currentTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_menuPersonal_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_menuCliente_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_salir_clicked()
{
    QApplication::quit();
}


void MainWindow::on_btn_reservar_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}
void MainWindow::inicializarMesas(int cantidad) {
    mesas.clear();
    for (int i = 0; i < cantidad; ++i) {
        mesas.append(Mesas(i));
    }
}

void MainWindow::on_btn_aceptarReserva_clicked()
{
    int id = ui->lE_id->text().toInt();
    QString nombre = ui->lE_nombreReserva->text();
    int telefono = ui->lE_numTel->text().toInt();
    int comensales = ui->spinBox_numComensales->value();
    QDate fecha = ui->dateEdit_fechaReserva->date();
    QTime hora = ui->timeEdit_horaReserva->time();
    int numeroMesa = Reserva::obtenerNumeroMesaAsignado(fecha, hora);

    if (Reserva::verificarDisponibilidad(fecha, hora)) {
        Reserva *reserva = new Reserva(id, nombre, telefono, comensales, fecha, hora);
        reserva->setMesaAsignada(numeroMesa);
        Reserva::agregarReserva(reserva);
        ui->tE_Reservas->setPlainText(Reserva::obtenerReservas());
        ui->lE_id->clear();
        ui->lE_nombreReserva->clear();
        ui->lE_numTel->clear();
        ui->spinBox_numComensales->setValue(1);
        ui->dateEdit_fechaReserva->setDate(QDate::currentDate());
        ui->timeEdit_horaReserva->setTime(QTime::currentTime());
    } else {
        QMessageBox::warning(this, "Sin Disponibilidad",
                             "No hay mesas disponibles para la fecha y hora seleccionadas.");
    }
}


void MainWindow::on_btn_numMesas_clicked()
{
    int cantidadMesas = ui->spinBox_numMesas->value();

    Reserva::mesasDisponibles = cantidadMesas;
    inicializarMesas(cantidadMesas);
    QMessageBox::information(this, "Éxito", "Cantidad de mesas establecida con éxito.");
}


void MainWindow::on_btn_cancelarReserva_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Cancelar Reserva", "Ingrese el ID de la reserva a cancelar:", 0, 0, 10000, 1, &ok);

    if (ok) {
        QVector<Reserva*> reservasBajoId = Reserva::obtenerReservasPorId(id);

        if (!reservasBajoId.isEmpty()) {
            QString reservasTexto;
            for (const auto &reserva : reservasBajoId) {
                reservasTexto += reserva->getInfo() + "\n";
            }

            QMessageBox::information(this, "Reservas Encontradas (Elija la reserva que desea cancelar)", reservasTexto);


            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmar Cancelación", "¿Desea cancelar la reserva(s) con el ID proporcionado?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                Reserva::eliminarReserva(id);
                ui->tE_Reservas->setPlainText(Reserva::obtenerReservas());
                QMessageBox::information(this, "Reserva Cancelada", "La reserva ha sido cancelada exitosamente.");
            }
        } else {
            QMessageBox::warning(this, "Reserva No Encontrada", "No se encontraron reservas con el ID proporcionado.");
        }
    }
}


void MainWindow::on_btn_cancelarReserva_2_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Cancelar Reserva", "Ingrese el ID de la reserva a cancelar:", 0, 0, 10000, 1, &ok);

    if (ok) {
        QVector<Reserva*> reservasBajoId = Reserva::obtenerReservasPorId(id);

        if (!reservasBajoId.isEmpty()) {
            QString reservasTexto;
            for (const auto &reserva : reservasBajoId) {
                reservasTexto += reserva->getInfo() + "\n";
            }

            QMessageBox::information(this, "Reservas Encontradas (Elija la reserva que desea cancelar)", reservasTexto);


            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmar Cancelación", "¿Desea cancelar la reserva(s) con el ID proporcionado?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                Reserva::eliminarReserva(id);
                ui->tE_Reservas->setPlainText(Reserva::obtenerReservas());
                QMessageBox::information(this, "Reserva Cancelada", "La reserva ha sido cancelada exitosamente.");
            }
        } else {
            QMessageBox::warning(this, "Reserva No Encontrada", "No se encontraron reservas con el ID proporcionado.");
        }
    }
}


void MainWindow::on_btn_cantMesas_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}


void MainWindow::on_btn_regresarMenu_2_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_regresarMenu_1_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_btn_regresarPersonal_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_btn_regresarCliente_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}


void MainWindow::on_btn_disponibilidadCliente_clicked()
{
    ui->tabWidget->setCurrentIndex(5);
}


void MainWindow::on_btn_regresarCliente_5_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

