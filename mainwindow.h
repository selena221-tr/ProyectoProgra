#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include <QPushButton>

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

    void on_InicioDia_clicked();
    void on_iniciarPedido_clicked();
    void on_btnAgregar_clicked();
    void on_btnVolver_clicked();
    void on_btnPagar_clicked();
    void on_btnCancelar_clicked();
    void botonPresionado();
    void guardarDatosArchivo();

    //void on_comboBox_2_activated(int index);

private:
    Ui::MainWindow *ui;

    QVector<int> contadores;                 // cantidades por producto
    QVector<QLabel*> labels;                  // labels de cantidades
    QVector<QPushButton*> botonesMenos;
    void actualizarFactura();
};
#endif // MAINWINDOW_H
