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
    ui->timeEdit_horaReserva->setDisplayFormat("HH:mm");
    ui->timeEdit->setDisplayFormat("HH:mm");
    ui->timeEdit_2->setDisplayFormat("HH:mm");
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit->setDate(QDate::currentDate());
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
    hora = QTime(hora.hour(), hora.minute());
    qDebug()<<hora;
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
                             "No hay mesas disponibles para la fecha y hora seleccionadas");
    }
}


void MainWindow::on_btn_numMesas_clicked()
{
    int cantidadMesas = ui->spinBox_numMesas->value();

    Reserva::mesasDisponibles = cantidadMesas;
    inicializarMesas(cantidadMesas);
    QMessageBox::information(this, "Éxito", "Cantidad de mesas establecida");
}


void MainWindow::on_btn_cancelarReserva_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Cancelar Reserva", "Ingrese su ID para cancelar la reserva:", 0, 0, 10000, 1, &ok);

    if (ok) {
        QVector<Reserva*> reservasBajoId = Reserva::obtenerReservasPorId(id);

        if (!reservasBajoId.isEmpty()) {
            QString reservasTexto;
            for (const auto &reserva : reservasBajoId) {
                reservasTexto += reserva->getInfo() + "\n";
            }

            QMessageBox::information(this, "Reservas Encontradas (Elija la reserva que desea cancelar)", reservasTexto);


            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmar Cancelación", "¿Desea cancelar la reserva con ese ID ?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                Reserva::eliminarReserva(id);
                ui->tE_Reservas->setPlainText(Reserva::obtenerReservas());
                QMessageBox::information(this, "Reserva Cancelada", "La reserva ha sido cancelada");
            }
        } else {
            QMessageBox::warning(this, "Reserva No Encontrada", "No se encontraron reservas con ese ID");
        }
    }
}


void MainWindow::on_btn_cancelarReserva_2_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Cancelar Reserva", "Ingrese su ID para cancelar la reserva: ", 0, 0, 10000, 1, &ok);

    if (ok) {
        QVector<Reserva*> reservasBajoId = Reserva::obtenerReservasPorId(id);

        if (!reservasBajoId.isEmpty()) {
            QString reservasTexto;
            for (const auto &reserva : reservasBajoId) {
                reservasTexto += reserva->getInfo() + "\n";
            }

            QMessageBox::information(this, "Reservas Encontradas (Elija la reserva que desea cancelar)", reservasTexto);


            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirmar Cancelación", "¿Desea cancelar la reserva con ligado a ese ID?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                Reserva::eliminarReserva(id);
                ui->tE_Reservas->setPlainText(Reserva::obtenerReservas());
                QMessageBox::information(this, "Reserva Cancelada", "La reserva ha sido cancelada");
            }
        } else {
            QMessageBox::warning(this, "Reserva No Encontrada", "No se encontraron reservas con ese ID.");
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


void MainWindow::on_btn_regresarCliente_2_clicked()
{

}


void MainWindow::on_btn_modificarCliente_clicked()
{

    bool ok;
    int id = QInputDialog::getInt(this, "Modificar Reserva", "Ingrese su ID para identificar la reserva:", 0, 0, 100000, 1, &ok);
    if (!ok) {
        return;
    }

    QStringList reservasList;
    for (const auto &reserva : Reserva::getReservasList()) {
        if (reserva->getId() == id) {
            reservasList << reserva->getInfo();
        }
    }

    if (reservasList.isEmpty()) {
        QMessageBox::information(this, "Sin Reservas", "No se encontraron reservas ligadas con su ID");
        return;
    }

    bool selectedOk;
    QString selectedReserva = QInputDialog::getItem(this, "Reservas Encontradas (Elija una para modificar)",
                                                    "Reservas:", reservasList, 0, false, &selectedOk);
    if (!selectedOk || selectedReserva.isEmpty()) {
        return;
    }

    for (const auto &reserva : Reserva::getReservasList()) {
        if (reserva->getInfo() == selectedReserva) {
            ui->lE_id_2->setText(QString::number(reserva->getId()));
            ui->lE_nombreReserva_3->setText(reserva->getNombreCliente());
            ui->lE_numTel_2->setText(QString::number(reserva->getTelefono()));
            ui->spinBox_numComensales_2->setValue(reserva->getComensales());
            ui->dateEdit_fechaReserva_2->setDate(reserva->getFecha());
            ui->timeEdit_horaReserva_2->setTime(reserva->getHora());

            ui->tabWidget->setCurrentIndex(6);
            break;
        }
    }
}


void MainWindow::on_btn_regresarCliente_3_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}



void MainWindow::on_btn_modificar_clicked()
{
    bool found = false;
    int id = ui->lE_id_2->text().toInt();

    for (auto& reserva : Reserva::getReservasList()) {
        if (reserva->getId() == id) {
            reserva->setNombreCliente(ui->lE_nombreReserva_3->text());
            reserva->setTelefono(ui->lE_numTel_2->text().toInt());
            reserva->setComensales(ui->spinBox_numComensales_2->value());
            reserva->setFecha(ui->dateEdit_fechaReserva_2->date());
            reserva->setHora(ui->timeEdit_horaReserva_2->time());
            ui->tE_Reservas->setPlainText(Reserva::obtenerReservas());
            QMessageBox::information(this, "Modificación Exitosa", "La reserva ha sido modificada");
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::warning(this, "Reserva no encontrada", "No se encontraron reservas ligadas con su ID");
    }
}


void MainWindow::on_btn_modificarCliente_2_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Modificar Reserva", "Ingrese su ID para identificar la reserva:", 0, 0, 100000, 1, &ok);
    if (!ok) {
        return;
    }

    QStringList reservasList;
    for (const auto &reserva : Reserva::getReservasList()) {
        if (reserva->getId() == id) {
            reservasList << reserva->getInfo();
        }
    }

    if (reservasList.isEmpty()) {
        QMessageBox::information(this, "Sin Reservas", "No se encontraron reservas ligadas con su ID");
        return;
    }

    bool selectedOk;
    QString selectedReserva = QInputDialog::getItem(this, "Reservas Encontradas (Elija una para modificar)",
                                                    "Reservas:", reservasList, 0, false, &selectedOk);
    if (!selectedOk || selectedReserva.isEmpty()) {
        return;
    }

    for (const auto &reserva : Reserva::getReservasList()) {
        if (reserva->getInfo() == selectedReserva) {
            ui->lE_id_2->setText(QString::number(reserva->getId()));
            ui->lE_nombreReserva_3->setText(reserva->getNombreCliente());
            ui->lE_numTel_2->setText(QString::number(reserva->getTelefono()));
            ui->spinBox_numComensales_2->setValue(reserva->getComensales());
            ui->dateEdit_fechaReserva_2->setDate(reserva->getFecha());
            ui->timeEdit_horaReserva_2->setTime(reserva->getHora());

            ui->tabWidget->setCurrentIndex(6);
            break;
        }
    }
}


void MainWindow::on_btn_disponibilidad_clicked()
{
    QDate fecha = ui->dateEdit->date();
    QTime hora = ui->timeEdit->time();
    hora = QTime(hora.hour(), hora.minute());

    qDebug()<< hora<<Qt::endl;
    qDebug()<< Reserva::obtenerMesasDisponibles(fecha, hora);
    int mesasDisponibles = Reserva::obtenerMesasDisponibles(fecha, hora);
    QString mensaje;
    if (mesasDisponibles > 0) {
        mensaje = QString("Hay %1 mesas disponibles para la fecha y hora seleccionadas.").arg(mesasDisponibles);
    } else {
        mensaje = "No hay mesas disponibles para la fecha y hora seleccionadas.";
    }

    QMessageBox::information(this, "Disponibilidad de Mesas", mensaje);
}


void MainWindow::on_btn_disponibilidadCliente_2_clicked()
{
    ui->tabWidget->setCurrentIndex(7);
}


void MainWindow::on_btn_regresarCliente_6_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}




void MainWindow::on_btn_disponibilidad_3_clicked()
{
    QDate fecha = ui->dateEdit_2->date();
    QTime hora = ui->timeEdit_2->time();
    hora = QTime(hora.hour(), hora.minute());

    qDebug()<< hora<<Qt::endl;
    qDebug()<< Reserva::obtenerMesasDisponibles(fecha, hora);
    int mesasDisponibles = Reserva::obtenerMesasDisponibles(fecha, hora);
    QString mensaje;
    if (mesasDisponibles > 0) {
        mensaje = QString("Hay %1 mesas disponibles para la fecha y hora seleccionadas.").arg(mesasDisponibles);
    } else {
        mensaje = "No hay mesas disponibles para la fecha y hora seleccionadas.";
    }

    QMessageBox::information(this, "Disponibilidad de Mesas", mensaje);
}

