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

    ui->labelDescripcion->setVisible(false);
    ui->labelDescripcion->setWordWrap(true);

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
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
    // Regresa al MENÚ, no a la página de pedido donde ya estás
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);

    // Limpia solo los datos que guardaste en el vector 'labels'
    for (int i = 0; i < contadores.size(); i++){ // esto lo hago para que todos los contadores de los productos se reinicien a 0
        contadores[i] = 0;  //los contadores pa calcular el pago
        labels[i]->setText("0");    // y los Labels de los contadores
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
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
    QMessageBox::information(this, "Pago", "¡Pagó con éxito!");
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
    for (int i = 0; i < contadores.size(); i++){ // esto lo hago para que todos los contadores de los productos se reinicien a 0
        contadores[i] = 0; //los contadores pa calcular el pago
        labels[i]->setText("0"); // y los Labels de los contadores
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
}


MainWindow::~MainWindow() {// en si es para la memoria, se elimina a si mismo cuando se cierra el programa
    delete ui;
}

void MainWindow::on_comboBox_activated(int index) {

    QPoint topLeftPosition(10, 50); // Coordenadas donde se mueve el seleccionado

    // Ocultar todos los widgets antes que nada
    ui->frAmericano->setVisible(false);
    ui->frCapuccino->setVisible(false);
    ui->frCaramelo->setVisible(false);
    ui->frFrappe->setVisible(false);
    ui->frLatte->setVisible(false);
    ui->frMocha->setVisible(false);

    // Ocultar el label de descripción por defecto


    QWidget *posicion = nullptr;

    switch (index) {
    case 0: // Opción "Todos"
        // ====== TUS POSICIONES ORIGINALES ======
        // Fila 1
        ui->frMocha->move(10, 50);        // CAFFE MOCHA
        ui->frCaramelo->move(250, 50);    // CARAMEL MACCHIATO
        ui->frLatte->move(490, 50);       // LATTE

        // Fila 2
        ui->frCapuccino->move(10, 190);   // CAPPUCCINO
        ui->frFrappe->move(250, 190);     // FRAPPE
        ui->frAmericano->move(490, 190);  // AMERICANO

        // Mostrar todos
        ui->frAmericano->setVisible(true);
        ui->frCapuccino->setVisible(true);
        ui->frCaramelo->setVisible(true);
        ui->frFrappe->setVisible(true);
        ui->frLatte->setVisible(true);
        ui->frMocha->setVisible(true);

        ui->labelDescripcion->setVisible(false);
        break;

    case 1: // Opción "Mocha"
    {
        ui->frMocha->setVisible(true);
        posicion = ui->frMocha;

        QString textoDescripcion =
            "Caffe Macchiato: \n\n"
            " El caffè macchiato, que significa \"manchado\" en italiano, "
            " nació en los años 80 para diferenciar un espresso solo "
            " de uno con un toque de leche. Es una pequeña y potente "
            " bebida que equilibra un espresso con una mancha de "
            " espuma de leche, ideal para la tarde, a diferencia "
            " del capuchino.";

        ui->labelDescripcion->setText(textoDescripcion);
        ui->labelDescripcion->setVisible(true);
        ui->labelDescripcion->setWordWrap(true);
        break;
    }

    case 2: // Opción "Capuccino"
    {
        ui->frCapuccino->setVisible(true);
        posicion = ui->frCapuccino;

        QString textoDescripcion =
            "Caffe Capuccino: \n\n"
            " El café capuchino debe su nombre al color del hábito de los monjes "
            " capuchinos (franciscanos), ya que al añadir leche al café intenso, "
            " la mezcla resultaba en un marrón rojizo claro similar a sus túnicas. "
            " Aunque es un ícono italiano, la leyenda sitúa su origen en Viena, "
            " Austria, tras la batalla de 1683.";

        ui->labelDescripcion->setText(textoDescripcion);
        ui->labelDescripcion->setVisible(true);

        break;
    }

    case 3: // Opción "Caramelo"
    {
        ui->frCaramelo->setVisible(true);
        posicion = ui->frCaramelo;

        QString textoDescripcion =
            "Caffe Carmelo: \n\n"
            " El nombre Carmelo proviene del hebreo Karmel o Karm-Ēl, que significa "
            " «jardín», «huerto» o «viñedo de Dios». Hace referencia a la exuberante "
            " vegetación del Monte Carmelo en Israel, lugar donde se originó la orden "
            " religiosa en el siglo XII, buscando vivir en oración contemplativa.";

        ui->labelDescripcion->setText(textoDescripcion);
        ui->labelDescripcion->setVisible(true);
        break;
    }

    case 4: // Opción "Frappe"
    {
        ui->frFrappe->setVisible(true);
        posicion = ui->frFrappe;

        QString textoDescripcion =
            "Caffe Frappe: \n\n"
            " El café frappé se inventó por accidente en 1957 durante la "
            " Feria Internacional de Tesalónica en Grecia. Dimitris Vakondios, "
            " un representante de Nestlé, no encontró agua caliente para su "
            " café soluble y decidió mezclarlo con agua fría y cubitos de "
            " hielo en una coctelera, creando así la famosa bebida espumosa.";

        ui->labelDescripcion->setText(textoDescripcion);
        ui->labelDescripcion->setVisible(true);
        break;
    }

    case 5: // Opción "Latte"
    {
        ui->frLatte->setVisible(true);
        posicion = ui->frLatte;

        QString textoDescripcion =
            "Caffe Latte: \n\n"
            " Aunque la palabra latte proviene del italiano \"caffè latte\" "
            " (café con leche), la versión moderna y popular del latte con "
            " espuma cremosa se popularizó en Seattle, Estados Unidos, durante "
            " la década de 1980. Además, es conocido por ser una bebida donde "
            " la leche predomina sobre el café, llevando más leche vaporizada "
            " que un cappuccino.";

        ui->labelDescripcion->setText(textoDescripcion);
        ui->labelDescripcion->setVisible(true);
        break;
    }

    case 6: // Opción "Americano"
    {
        ui->frAmericano->setVisible(true);
        posicion = ui->frAmericano;

        QString textoDescripcion =
            "Caffe Americano: \n\n"
            " Un dato curioso de Estados Unidos es que, a pesar de ser la "
            " cuna del inglés, no tiene un idioma oficial establecido a "
            " nivel federal por ley. Aunque más del 78% habla inglés, el "
            " país se caracteriza por su gran diversidad lingüística y "
            " cultural. Además, los estadounidenses devoran unos 350 "
            " porciones de pizza cada segundo.";

        ui->labelDescripcion->setText(textoDescripcion);
        ui->labelDescripcion->setVisible(true);
        break;
    }
    }

    if (posicion != nullptr) {
        posicion->move(topLeftPosition);
        posicion->raise();
    }
}
