#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    contadores = {0, 0, 0, 0, 0, 0};

    labels = {
        ui->lbMochaCont,
        ui->lbLatteCont,
        ui->lbCapuccinoCont,
        ui->lbAmericanoCont,
        ui->lbCarameloCont,
        ui->lbFrappeCont
    };

    botonesMenos = {
        ui->btnMenosMocha,
        ui->btnMenosLatte,
        ui->btnMenosCapuccino,
        ui->btnMenosAmericano,
        ui->btnMenosCaramelo,
        ui->btnMenosFrappe
    };

    ui->btnMasMocha->setProperty("labelID", 0);
    ui->btnMasLatte->setProperty("labelID", 1);
    ui->btnMasCapuccino->setProperty("labelID", 2);
    ui->btnMasAmericano->setProperty("labelID", 3);
    ui->btnMasCaramelo->setProperty("labelID", 4);
    ui->btnMasFrappe->setProperty("labelID", 5);

    ui->btnMenosMocha->setProperty("labelID", 0);
    ui->btnMenosLatte->setProperty("labelID", 1);
    ui->btnMenosCapuccino->setProperty("labelID", 2);
    ui->btnMenosAmericano->setProperty("labelID", 3);
    ui->btnMenosCaramelo->setProperty("labelID", 4);
    ui->btnMenosFrappe->setProperty("labelID", 5);

    ui->btnMasMocha->setProperty("accion", 0);
    ui->btnMasLatte->setProperty("accion", 0);
    ui->btnMasCapuccino->setProperty("accion", 0);
    ui->btnMasAmericano->setProperty("accion", 0);
    ui->btnMasCaramelo->setProperty("accion", 0);
    ui->btnMasFrappe->setProperty("accion", 0);

    ui->btnMenosMocha->setProperty("accion", 1);
    ui->btnMenosLatte->setProperty("accion", 1);
    ui->btnMenosCapuccino->setProperty("accion", 1);
    ui->btnMenosAmericano->setProperty("accion", 1);
    ui->btnMenosCaramelo->setProperty("accion", 1);
    ui->btnMenosFrappe->setProperty("accion", 1);

    connect(ui->btnMasMocha,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMasLatte,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMasCapuccino,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMasAmericano,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMasCaramelo,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMasFrappe,  &QPushButton::clicked, this, &MainWindow::botonPresionado);

    connect(ui->btnMenosMocha,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMenosLatte,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMenosCapuccino,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMenosAmericano,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMenosCaramelo,  &QPushButton::clicked, this, &MainWindow::botonPresionado);
    connect(ui->btnMenosFrappe,  &QPushButton::clicked, this, &MainWindow::botonPresionado);


}



void MainWindow::on_InicioDia_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QMessageBox::information(this, "Importante", "Ingrese una fecha antes de continuar");
    } else {
       ui->stackedWidget->setCurrentIndex(1);
    }

}

void MainWindow::on_iniciarPedido_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_btnAgregar_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::botonPresionado()
{
    QPushButton *boton = qobject_cast<QPushButton*>(sender());
    if (!boton) return;

    int id = boton->property("labelID").toInt();
    int accion = boton->property("accion").toInt(); // 0 = + , 1 = -

    if (accion == 0) {
        contadores[id]++;
    } else {
        if (contadores[id] > 0) {
            contadores[id]--;
        }
    }

    // Actualizar label
    labels[id]->setText(QString::number(contadores[id]));

    // Habilitar / deshabilitar botón menos
    botonesMenos[id]->setEnabled(contadores[id] > 0);
}



MainWindow::~MainWindow()
{
    delete ui;
}




