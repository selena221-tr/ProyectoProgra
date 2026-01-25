#include <QMainWindow>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>  // ← AGREGADO (para mostrar los mensajes)
#include <QPushButton>  // ← AGREGADO (para qobject_cast<QPushButton*>)
#include <QLabel>       // ← AGREGADO (para los labels)
#include <QLineEdit>    // ← AGREGADO (para ui->lineEdit)
#include <QDate>        // ← AGREGADO (para mostrar fecha actual)
#include <QFile>        //Para incluir archivos


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    contadores = {0, 0, 0, 0, 0, 0};

    // PARA CAMBIAR COLORES DE LA 'page_inicioPedido' ya sea botón o label
    QPalette palette1 = ui->inicioPedido->palette();
    palette1.setColor(QPalette::WindowText, Qt::black);  // Color del texto
    ui->inicioPedido->setPalette(palette1);

    ui->LsumaPagar->setStyleSheet("color: black;");


    // PARA CAMBIAR COLORES DE LA 'page_menu' ya sea botón o label conf de la pag
    QPalette palette2 = ui->inicioPagMenu->palette();
    palette2.setColor(QPalette::WindowText, Qt::black);
    ui->inicioPagMenu->setPalette(palette2);

    ui->btnAgregar->setStyleSheet("color: black;");


    // PARA HACER TRANSPARTENTE DE LA 'page_pedido' FRAME 5
    ui->frame_2->setStyleSheet("background-color: transparent;");

    QPalette paletteBtn1 = ui->btnCancelar->palette();
    paletteBtn1.setColor(QPalette::ButtonText, Qt::black);  // ← CAMBIADO
    ui->btnCancelar->setPalette(paletteBtn1);

    QPalette paletteBtn2 = ui->btnPagar->palette();
    paletteBtn2.setColor(QPalette::ButtonText, Qt::black);  // ← CAMBIADO
    ui->btnPagar->setPalette(paletteBtn2);

    QPalette paletteBtn3 = ui->btnVolver->palette();
    paletteBtn3.setColor(QPalette::ButtonText, Qt::black);  // ← CAMBIADO
    ui->btnVolver->setPalette(paletteBtn3);


    // PARA HACER TRANSPARTENTE DE LA 'page_inicioSistema' FRAME 5
    ui->frame_4->setStyleSheet("background-color: transparent;");

    // BOTONES Y ACCIONES
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

void MainWindow::on_InicioDia_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
}


//ESTO VA A SER LA EDICIÓN DE LA SEGUNDA PESTAÑA ******* 'page_inicioPedido' *******
void MainWindow::on_iniciarPedido_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}


//ESTO VA A SER LA EDICIÓN DE LA TERCERA PESTAÑA ******* 'page_menu' *******
void MainWindow::on_btnAgregar_clicked(){
    actualizarFactura(); //se llama a la funcion antes de cambiar de página
    bool encontrado=false;
    for (int i=0; i<contadores.size(); i++){
        if (contadores[i]!=0){
            encontrado=true;
        }
    }
    if (!encontrado){
        QMessageBox::information(this, "Importante", "Agregue productos para continuar");
    } else {
        ui->stackedWidget->setCurrentWidget(ui->page_Pedido);
    }

}


//ESTO VA A SER LA EDICIÓN DE LA CUARTA PESTAÑA ******* 'page_pedido' *******
void MainWindow::on_btnVolver_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

void MainWindow::on_btnCancelar_clicked() {
    contadores = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < contadores.size(); i++) {
        labels[i]->setText(QString::number(contadores[i]));
    }
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
}


//ESTO ES PARA TODO EL MainWindow, Y ES PARA TODOS LO BOTONES QUE SON APLASTADOS
void MainWindow::botonPresionado() { // cuando cualquiera de los botones es presionado
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

void MainWindow::actualizarFactura(){
    //primero la tabla se limpia para que no se repitan los datos
    ui->facturaTabla->setRowCount(0);

    //se declaran los datos que usamos para llenar la tabla(los productos del menu y sus precios, ya establecidos)
    QVector<QString> nombres = {"Mocha","Latte","Capuccino","Americano","Caramelo","Frappe"};
    QVector<double> precios = {3.50, 3.00, 3.50, 2.50, 4.00, 4.50};
    double totalFinal = 0;

    //con un for recorremos los contadores para ver que productos si mostrar
    for(int i = 0; i<contadores.size();i++){
        if(contadores[i]>0){ //Si hay algo, se procedera a calcular su precio(subtotal).
            double subtotal = contadores[i]*precios[i];
            double iva = subtotal*1.12; //hacemos que se calcule el iva
            totalFinal += iva; //con esta operacion logramos el total final, final.

            int fila = ui->facturaTabla->rowCount();
            ui->facturaTabla->insertRow(fila);

            //con lo siguiente se llenan las columnas: cantidad, producto, precio, subtotal
            ui->facturaTabla->setItem(fila, 0, new QTableWidgetItem(QString::number(contadores[i])));
            ui->facturaTabla->setItem(fila, 1, new QTableWidgetItem(nombres[i]));
            ui->facturaTabla->setItem(fila, 2, new QTableWidgetItem("$"+QString::number(precios[i], 'f', 2)));
            ui->facturaTabla->setItem(fila, 3, new QTableWidgetItem("$"+QString::number(subtotal, 'f', 2)));
        }                                                                                       //fuerza a que salgan 2 decimales, lo estandar para dinero
    }

    //actualizamos el label del total final para que muestre el monto total
    ui->label_5->setText("$"+QString::number(totalFinal, 'f',2));
    ui->label_5->setStyleSheet("color: black; font-weight: bold;");
    // Esto quita bordes negros y asegura que el fondo sea limpio
}

void MainWindow::guardarDatosArchivo(){

    QFile archivo("factura.txt");     //fstream archivo(ruta)
    if (!archivo.open(QIODevice::Append|QIODevice::Text)){   //Si el archivo no se abre(en modo agregar lineas, no reescribir y considerado un texto plano)
        qDebug()<<"Registro no encontrado"; //Uso qDebug que es un objeto parte de la clase QDebug, equivale a un cerr/cout en c++
        return;
        //QFile solo maneja bits, QTextstream sabe transformar esos bits en texto y QIODevice es como ios:: en c++
    }
    QTextStream agregar(&archivo); // esta es la parte donde se agrega el texto al archivo, asignare poniendo agregar<<
    int filas = ui->facturaTabla->rowCount();
    int columnas = ui->facturaTabla->columnCount();

    for (int i = 0; i < filas; i++) {
        agregar<<ui->Dia->date().toString("yyyy-MM-dd") << ";"; // saco la fecha del dateEdit en forma de cadena con un formato
        for (int j = 0; j < columnas; j++) {
            QTableWidgetItem *item = ui->facturaTabla->item(i, j);
            //QTable WidgetItem es un objeto que representa una celda de la tabla, guarda TODA la info de la celda (color, alineación, texto)
            //item es un puntero  a una celda, guarda la direccion de memoria de una celda en una posicion i, j de la tabla
            //(usamos puntero porque en esta posicion puede estar vacia)
            if (item) {  //si item no esta vacio
                QString dato = item->text(); //Variable string dato que contiene el texto del item
                agregar<<dato;
            }
            if (j < columnas - 1){
                agregar<<";";
            }
        }
        agregar<<"\n";
    }
    archivo.close();
}

void MainWindow::on_btnPagar_clicked() {
    guardarDatosArchivo();
    contadores = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < contadores.size(); i++) {
        labels[i]->setText(QString::number(contadores[i]));
    }
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
    QMessageBox::information(this, "Pago", "¡Pagó con éxito!");
}


MainWindow::~MainWindow() // en si es para la memoria, se elimina a si mismo cuando se cierra el programa
{
    delete ui;
}

