#include <QMainWindow>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>  // ← AGREGADO (para mostrar los mensajes)
#include <QPushButton>  // ← AGREGADO (para qobject_cast<QPushButton*>)
#include <QLabel>       // ← AGREGADO (para los labels)
#include <QDate>        // ← AGREGADO (para mostrar fecha actual)
#include <QFile>        //Para incluir archivos
#include <QLineEdit>    //Para que el usuario pueda escribir
#include <QInputDialog> //Para que salga la alerta con diálogo


MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this); // para que salgan las cosas, botones, labels y todo eso
    ui->Dia->setDate(QDate::currentDate());
    contadores = {0, 0, 0, 0, 0, 0};

    ui->labelDescripcion->setVisible(false); // para que no se vea al inicializar
    ui->labelDescripcion->setWordWrap(true); // para activar el salto automático de cada línea dentro del label


    nombres = {"Mocha","Latte","Capuccino","Americano","Caramelo","Frappe"};

    labels = {
        ui->lbMochaCont,
        ui->lbLatteCont,
        ui->lbCapuccinoCont,
        ui->lbAmericanoCont,
        ui->lbCarameloCont,
        ui->lbFrappeCont
    };

    frames = {
        ui->frMocha,
        ui->frLatte,
        ui->frCapuccino,
        ui->frAmericano,
        ui->frCaramelo,
        ui->frFrappe
    };


    botonesMenos = {
        ui->btnMenosMocha,
        ui->btnMenosLatte,
        ui->btnMenosCapuccino,
        ui->btnMenosAmericano,
        ui->btnMenosCaramelo,
        ui->btnMenosFrappe
    };

    botonesMas = {
        ui->btnMasMocha,
        ui->btnMasLatte,
        ui->btnMasCapuccino,
        ui->btnMasAmericano,
        ui->btnMasCaramelo,
        ui->btnMasFrappe
    };

    for (int i =0; i<botonesMenos.size(); i++){
        botonesMenos[i]->setProperty("labelID", i);
        botonesMas[i]->setProperty("labelID", i);
        botonesMas[i]->setProperty("accion", 0);
        botonesMenos[i]->setProperty("accion",1);
        connect(botonesMas[i], &QPushButton::clicked, this, &MainWindow::botonPresionado);
        connect(botonesMenos[i], &QPushButton::clicked, this, &MainWindow::botonPresionado);
    }
}

//está en la página 0, va a la 1
void MainWindow::on_InicioDia_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
}


//Va de la segunda pestaña "Iniciar Pedido" a la pestaña del menú (1 a 2)
void MainWindow::on_iniciarPedido_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}


//Va del menú a la página de la factura, controla que exista un pedido (2 a 3)
void MainWindow::on_btnAgregar_clicked(){
    actualizarFactura(); // Llamo a la función actualizo antes de todo.
    bool encontrar = false;
    for(int i = 0; i < contadores.size(); i++){
        if(contadores[i] != 0){
            encontrar = true;
        }
    }
    if(!encontrar){
        QMessageBox::information(this, "Error", "No se aceptan valores vacíos");
    }else{
        ui->stackedWidget->setCurrentWidget(ui->page_Pedido);
    }
}


//está en la pagina 3 y vuele a la 2 para seguir agregando (3 a 2)
void MainWindow::on_btnVolver_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_menu);
}

//está en la página 3 y va a la 1, cancela el pedido. Limpia todo  (3 a 1)
void MainWindow::on_btnCancelar_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);

    for (int i = 0; i < contadores.size(); i++){ // esto lo hago limpiar todo
        contadores[i] = 0;  //todos los contadores a 0
        labels[i]->setText("0");    // los Labels de los contadores a 0
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
}


//Esto es la lógica que aplicamos a los botones de más y menos en la página de menú
void MainWindow::botonPresionado() { // cuando cualquiera de los botones es presionado
    QPushButton *boton = qobject_cast<QPushButton *> (sender()); // sender() devuelve el objeto que emitió la señal
                                                                 // *buton es el puntero que indica qué botón que aplastamos
    if (!boton) return; // si por alguna razón aplasta en algo que no sea botón se sale para evitar errores

    int id = boton->property("labelID").toInt(); //sabiendo que botón fue aplastado, me dice a que label le corresponde
    int accion = boton->property("accion").toInt(); //saber si el boton aplastado tiene la funcion de suma o resta

    if (accion == 0) {
        if (contadores[id] >= 15){ // si es que están más de 15 salta esto, cuenta desde 0, por eso es >=
            QMessageBox::warning(this, "Error", "No se pueden colocar más de 15 productos");
            return;
        }
        contadores[id]++;
    } else {
        if (contadores[id] > 0) {
            contadores[id]--;
        }else{
            QMessageBox::information(this, "Importante", "No se puede colocar una unidad menor a 0");
        }
    }

    labels[id]->setText(QString::number(contadores[id])); // Actualizar label

    //Cambiar el color para simular el habilitado o deshabilitado
    if(contadores[id] > 0){
        labels[id]->setStyleSheet("color: black;");
    }else{
        labels[id]->setStyleSheet("color: white;");
    }
}

void MainWindow::actualizarFactura(){
    //primero la tabla se limpia para que no se repitan los datos
    ui->facturaTabla->setRowCount(0);

    //se declaran los datos que usamos para llenar la tabla( precios, ya establecidos)
    QVector<double> precios = {3.50, 3.00, 3.50, 2.50, 4.00, 4.50};
    double totalFinal = 0;

    //con un for recorremos los contadores para ver que productos si mostrar
    for(int i = 0; i<contadores.size();i++){
        if(contadores[i]>0){ //Si hay algo, se procedera a calcular su precio(subtotal).
            double subtotal = contadores[i]*precios[i];
            double iva = subtotal*1.12; //hacemos que se calcule el iva
            totalFinal += iva; //con esta operacion logramos el total final, final.

            int fila = ui->facturaTabla->rowCount(); // asignar la columnas correctas
            ui->facturaTabla->insertRow(fila); // Row = fila

            //con lo siguiente se llenan las columnas: cantidad, producto, precio, subtotal
            ui->facturaTabla->setItem(fila, 0, new QTableWidgetItem(nombres[i]));
            ui->facturaTabla->setItem(fila, 1, new QTableWidgetItem(QString::number(contadores[i])));
            ui->facturaTabla->setItem(fila, 2, new QTableWidgetItem("$"+QString::number(precios[i], 'f', 2)));
            ui->facturaTabla->setItem(fila, 3, new QTableWidgetItem("$"+QString::number(subtotal, 'f', 2)));
        }                  // ' f ' fuerza a que salgan 2 decimales, lo estandar para dinero
    }

    //actualizamos el label del total final para que muestre el monto total
    ui->label_5->setText("$"+QString::number(totalFinal, 'f',2));
}

void MainWindow::guardarDatosArchivo(){

    QFile archivo("factura.txt");     //fstream archivo(ruta!!)
    if (!archivo.open(QIODevice::Append|QIODevice::Text)){   //Si el archivo no se abre(en modo agregar lineas, no reescribir y considerado un texto plano)
        qDebug()<<"Registro no encontrado"; //Uso qDebug que es un objeto parte de la clase QDebug, equivale a un cerr/cout en c++
        return;
        //QFile solo maneja bits, QTextstream sabe transformar esos bits en texto y QIODevice es como ios:: en c++
    }
    QTextStream agregar(&archivo); // esta es la parte donde se agrega el texto al archivo, asignare poniendo agregar<<
    int filas = ui->facturaTabla->rowCount();
    int columnas = ui->facturaTabla->columnCount();

    for (int i = 0; i < filas; i++) {
        agregar<<ui->Dia->date().toString("yyyy-MM-dd") << ";";     // saco la fecha del dateEdit en forma de cadena con un formato
        for (int j = 0; j < columnas; j++) {
            QTableWidgetItem *item = ui->facturaTabla->item(i, j);
            //QTable WidgetItem es un objeto que representa una celda de la tabla, guarda TODA la info de la celda (color, alineación, texto)
            //item es un puntero  a una celda, guarda la direccion de memoria de una celda en una posicion i, j de la tabla
            //(usamos puntero porque en esta posicion puede estar vacia)
            if (item) {  //si item no esta vacio
                QString dato = item->text(); //Variable string dato que contiene el texto del item, coge text pa poner
                agregar << dato;
            }
            if (j < columnas - 1){ // para que al final no se ponga un ";"
                agregar<<";";
            }
        }
        agregar<<"\n"; // dar un "enter" para la siguiente fila
    }
    archivo.close(); // cerrar para que no consuma más recursos de la compu
}

void MainWindow::on_btnPagar_clicked() {
    guardarDatosArchivo();
    QMessageBox::information(this, "Pago", "¡Pagó realizado con éxito!");
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);
    for (int i = 0; i < contadores.size(); i++){ // esto lo hago para que todos los contadores de los productos se reinicien a 0
        contadores[i] = 0; //los contadores pa calcular el pago
        labels[i]->setText("0"); // y los Labels de los contadores
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
}


void MainWindow::on_comboBox_activated(int menu) {

    QPoint topLeftPosition(10, 50); // Coordenadas donde se mueve el seleccionado

    // Ocultar todos los widgets antes que nada
    for (int h=0; h<frames.size(); h++){
        frames[h]->setVisible(false);
    }

    // Ocultar el label de descripción por defecto

    QWidget *posicion = nullptr; // el * es el puntero
                                 // 'posicion' es mi variable
                                 // el 'nullptr' es para que se declare con un valor en nulo
                                 // Inicializando para que se inicie en nulo.

    switch (menu) {
    case 0: // Opción "ninguno"
        // POSICIONES ORIGINALES
        // Fila 1
        ui->frMocha->move(10, 50);        // CAFFE MOCHA
        ui->frCaramelo->move(250, 50);    // CARAMEL MACCHIATO
        ui->frLatte->move(490, 50);       // LATTE

        // Fila 2
        ui->frCapuccino->move(10, 190);   // CAPPUCCINO
        ui->frFrappe->move(250, 190);     // FRAPPE
        ui->frAmericano->move(490, 190);  // AMERICANO

        // Mostrar todos
        for (int l=0; l<frames.size(); l++){
            frames[l]->setVisible(true);
        }

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
        ui->frAmericano->setVisible(true); // pone para que se vea el frame
        posicion = ui->frAmericano; // Para ponerle en una posición

        QString textoDescripcion = // crear un texto
            "Caffe Americano: \n\n"
            " Un dato curioso de Estados Unidos es que, a pesar de ser la "
            " cuna del inglés, no tiene un idioma oficial establecido a "
            " nivel federal por ley. Aunque más del 78% habla inglés, el "
            " país se caracteriza por su gran diversidad lingüística y "
            " cultural. Además, los estadounidenses devoran unos 350 "
            " porciones de pizza cada segundo.";

        ui->labelDescripcion->setText(textoDescripcion); // asignamos el texto creado con antelación
        ui->labelDescripcion->setVisible(true); // que se pueda ver el labelDescripción, ya asignado el texto obviamente
        break;
    }
    }

    if (posicion != nullptr) { // como ya el valor del posición no es nulo se ejecuta
        posicion->move(topLeftPosition); // mueve a la posición delcara con antelación (10, 50) x,y
        posicion->raise(); // hace que el label se ponga por encima de todos los elementos que estén
    }
}

void MainWindow::resumen(){
    float total=0;
    contadoresInforme = QVector<int>(nombres.size(), 0);


    QFile archivo("factura.txt");
    if (!archivo.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }
    QTextStream leer(&archivo);
    if (leer.atEnd()) {
        QMessageBox::information(this, "Resumen", "No se han registrado productos");
        archivo.close();
        return;
    }

    while (!leer.atEnd()){
        QString linea= leer.readLine();
        QStringList datos = linea.split(";");
        if (datos.size()<5) continue;

        total=total+datos[4].remove("$").toFloat();
        for (int i=0; i<nombres.size(); i++){
            if (datos[1]==nombres[i]){
                contadoresInforme[i]+=datos[2].toInt();
                break;
            }
        }

    }
    archivo.close();

    int Mejor=contadoresInforme[0];
    int indice=0;
    QString info1 ="";

    for (int j=1; j<contadoresInforme.size(); j++){
        if (contadoresInforme[j]>Mejor){
            Mejor=contadoresInforme[j];
            indice=j;
            info1 ="";
        } else if (contadoresInforme[j]==Mejor){
            info1+= "/" +nombres[j];
        }
    }


    QString info= "Producto mejor vendido en el día: " + nombres[indice] + info1 + "\n"
                                                                                    "Total recaudado: $" + QString::number(total, 'f', 2);
    QMessageBox::information(this, "Resumen", info);


}

void MainWindow::on_btnRegresar_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_inicioPedido);

    // Limpia solo los datos que guardaste en el vector 'labels'
    for (int i = 0; i < contadores.size(); i++){ // esto lo hago para que todos los contadores de los productos se reinicien a 0
        contadores[i] = 0;  //los contadores pa calcular el pago
        labels[i]->setText("0");    // y los Labels de los contadores
        labels[i]->setStyleSheet("color: white;"); // regreso a blanco por estética :)
    }
}


void MainWindow::on_btnapagar_clicked() {
    bool ok;
    QMessageBox::StandardButton respuesta; // es un tipo de dato para que el usuario pueda escoger entre si o no
    QString password = QInputDialog::getText(this, "Acceso", "Ingrese la contraseña:", QLineEdit::Password, "", &ok);
    if (ok) {
        if (password == "1234") {
            respuesta = QMessageBox::question(this, "Informe", "¿Desea ver el informe?", QMessageBox::Yes | QMessageBox::No);
            if (respuesta == QMessageBox::Yes) {
                resumen();
            }
        } else {
            QMessageBox::warning(this, "Error", "Contraseña incorrecta");
            return;
        }
    QMessageBox::warning(this, "Saliendo", "Muchas gracias...");
    qApp->quit(); // cierra la aplicación
    }
}

MainWindow::~MainWindow() {// en si es para el rendimiento de la memoria, se elimina a si mismo cuando se
    delete ui;             //cierra el programa
}

