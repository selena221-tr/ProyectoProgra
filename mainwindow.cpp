#include <QMainWindow>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>  // ← AGREGADO (para qobject_cast<QPushButton*>)
#include <QLabel>       // ← AGREGADO (para los labels)
#include <QLineEdit>    // ← AGREGADO (para ui->lineEdit)
#include <QDate>        // ← AGREGADO (para mostrar fecha actual)


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
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

//ESTO VA A SER LA EDICIÓN DE LA PRIMERA PESTAÑA ******* 'page_inicioSistema' *******
void MainWindow::on_InicioDia_clicked() {

    if(ui->IngresoDelDia->text().isEmpty()){
        QMessageBox::information(this, "Importante", "Ingrese una fecha antes de continuar");
    } else {
        ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
    }
}



//ESTO VA A SER LA EDICIÓN DE LA SEGUNDA PESTAÑA ******* 'page_inicioPedido' *******
void MainWindow::on_iniciarPedido_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}



//ESTO VA A SER LA EDICIÓN DE LA TERCERA PESTAÑA ******* 'page_menu' *******
void MainWindow::on_btnAgregar_clicked(){
    int Vacio = 0;
    for (int i = 0; i < contadores.size(); i++){
        Vacio += contadores[i];
    }
    if (Vacio == 0){
        QMessageBox::warning(this, "Error", "No existe ningún producto seleccionado");
        return;
    }else{
        ui->stackedWidget->setCurrentWidget(ui->page_Pedido);
    }
}



//ESTO VA A SER LA EDICIÓN DE LA CUARTA PESTAÑA ******* 'page_pedido' *******
void MainWindow::on_btnVolver_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

void MainWindow::on_btnCancelar_clicked() {
    // Regresa al MENÚ, no a la página de pedido donde ya estás
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);

    // Limpia solo los datos que guardaste en el vector 'labels'
    for (int i = 0; i < contadores.size(); i++){ // esto lo hago para que todos los contadores de los productos se reinicien a 0
        contadores[i] = 0;  //los contadores pa calcular el pago
        labels[i]->setText("0");    // y los Labels de los contadores
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
}


void MainWindow::on_btnPagar_clicked() {
    QMessageBox::information(this, "Pago", "¡Pagó con éxito!");
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
    for (int i = 0; i < contadores.size(); i++){ // esto lo hago para que todos los contadores de los productos se reinicien a 0
        contadores[i] = 0; //los contadores pa calcular el pago
        labels[i]->setText("0"); // y los Labels de los contadores
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
}

//ESTO ES PARA TODO EL MainWindow, Y ES PARA TODOS LO BOTONES QUE SON APLASTADOS
void MainWindow::botonPresionado() { // cuando cualquiera de los botones es precionado
    QPushButton *boton = qobject_cast<QPushButton*>(sender()); // sender() devuelve el objeto que emitió la señal
                                                               // *buton es para decir cuál es el botón que aplastamos
    if (!boton) return; // si por alguna razón aplasta en algo que no sea botón se sale para evitar errores

    int id = boton->property("labelID").toInt(); //para que haga lo que yo le diga que haga el botón
    int accion = boton->property("accion").toInt(); // 0 = + , 1 = -; saber si suma o resta

    if (accion == 0) {
        contadores[id]++;
    } else {
        if (contadores[id] > 0) {
            contadores[id]--;
        }else{
            QMessageBox::information(this, "Importante", "No se puede colocar una unidad menor a 0");
        }
    }

    // Actualizar label
    labels[id]->setText(QString::number(contadores[id])); //[id] para encontar el correcto
                                                          // Qstring::number(..) convierte int a texto
                                                          // setText para que muetsre por pantalla

    // Habilitar / deshabilitar botón menos
    //botonesMenos[id]->setEnabled(contadores[id] > 0); //si es 0 desactivado, y si es > 0 activado :)

    if(contadores[id] > 0){
        labels[id]->setStyleSheet("color: black;");
    }else{
        labels[id]->setStyleSheet("color: white;");
    }
}


MainWindow::~MainWindow() // en si es para la memoria, se elimina a si mismo cuando se cierra el programa
{
    delete ui;
}

void MainWindow::on_comboBox_2_activated(int index) {

    QPoint topLeftPosition(10, 10); // Coordenadas X=10, Y=10

    //para ocultar todos los widgets antes que nada.
    ui->frAmericano->setVisible(false);
    ui->frCapuccino->setVisible(false);
    ui->frCaramelo->setVisible(false);
    ui->frFrappe->setVisible(false);
    ui->frLatte->setVisible(false);
    ui->frMocha->setVisible(false);

    QWidget *posicion = nullptr; // el * es el puntero
                                     // 'posicion' es mi variable
                                 // el 'nullptr' es para que se declare con un valor en nulo

    switch (index) {
    case 0: // Opción "Todos"
        ui->frAmericano->setVisible(true);
        ui->frCapuccino->setVisible(true);
        ui->frCaramelo->setVisible(true);
        ui->frFrappe->setVisible(true);
        ui->frLatte->setVisible(true);
        ui->frMocha->setVisible(true);
        break;
    case 1: // Opción "Mocha"
        ui->frMocha->setVisible(true);
        break;
    case 2: // Opción "Capuccino"
        ui->frCapuccino->setVisible(true);
        break;
    case 3: // Opción "Macchiato"
        ui->frCaramelo->setVisible(true);
        break;
        // Puedes añadir más casos aquí para otros índices (ej: case 3:)
    }
}


// pa que o que?
void MainWindow::on_pushButton_clicked() {
    QMessageBox::information(this, "Sistema Cafetería", "Fecha ingresada correctamente. ¡Bienvenido!");
}







