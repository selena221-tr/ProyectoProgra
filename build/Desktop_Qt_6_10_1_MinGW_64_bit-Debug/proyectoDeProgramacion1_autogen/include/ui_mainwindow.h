/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page_inicioSistema;
    QFrame *frame_4;
    QFrame *frame;
    QLabel *label;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QWidget *page_inicioPedido;
    QFrame *frame_2;
    QFrame *frame_3;
    QPushButton *iniciarPedido;
    QWidget *menu;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 30, 751, 391));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page_inicioSistema = new QWidget();
        page_inicioSistema->setObjectName("page_inicioSistema");
        page_inicioSistema->setStyleSheet(QString::fromUtf8("background: url(:/imagenes/imagenpedido.png);\n"
""));
        frame_4 = new QFrame(page_inicioSistema);
        frame_4->setObjectName("frame_4");
        frame_4->setGeometry(QRect(-10, 0, 771, 401));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        frame = new QFrame(frame_4);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(80, 40, 631, 311));
        frame->setStyleSheet(QString::fromUtf8("background:rgba(0, 0, 0, 90); \n"
""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 50, 421, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Book Antiqua")});
        font.setPointSize(48);
        font.setBold(false);
        font.setItalic(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: white; "));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 120, 81, 81));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Sylfaen")});
        font1.setPointSize(28);
        font1.setBold(false);
        font1.setItalic(false);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: white; \n"
""));
        textBrowser = new QTextBrowser(frame);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(250, 150, 231, 31));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(240, 210, 151, 61));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Script MT")});
        font2.setPointSize(18);
        font2.setBold(true);
        pushButton->setFont(font2);
        pushButton->setStyleSheet(QString::fromUtf8("border-radius: 22px; \n"
"background: rgb(210, 150, 95);\n"
"color: rgb(40, 25, 20);"));
        stackedWidget->addWidget(page_inicioSistema);
        page_inicioPedido = new QWidget();
        page_inicioPedido->setObjectName("page_inicioPedido");
        page_inicioPedido->setStyleSheet(QString::fromUtf8("background-image: url(:/imagenes/Imagen2.png);\n"
"background-repeat: no-repeat;\n"
"background-position: center;\n"
"background-size: cover;"));
        frame_2 = new QFrame(page_inicioPedido);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(-40, -20, 791, 451));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(470, 240, 231, 61));
        frame_3->setStyleSheet(QString::fromUtf8("background: rgba(0, 0, 0, 50);\n"
"border-radius: 22px; \n"
""));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        iniciarPedido = new QPushButton(frame_3);
        iniciarPedido->setObjectName("iniciarPedido");
        iniciarPedido->setGeometry(QRect(10, 0, 221, 51));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Rockwell")});
        font3.setPointSize(14);
        font3.setUnderline(true);
        iniciarPedido->setFont(font3);
        iniciarPedido->setStyleSheet(QString::fromUtf8("color: rgb(40, 25, 20);\n"
"border-radius: 20px; \n"
"background: rgb(198, 165, 132); \n"
""));
        stackedWidget->addWidget(page_inicioPedido);
        menu = new QWidget();
        menu->setObjectName("menu");
        menu->setStyleSheet(QString::fromUtf8("background: white; \n"
""));
        label_3 = new QLabel(menu);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(-10, 30, 771, 41));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Roman")});
        font4.setPointSize(28);
        font4.setBold(true);
        label_3->setFont(font4);
        label_3->setStyleSheet(QString::fromUtf8("border: 2px solid rgb(0, 0, 0); \n"
""));
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        pushButton_2 = new QPushButton(menu);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(80, 90, 141, 101));
        pushButton_3 = new QPushButton(menu);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(310, 90, 141, 101));
        pushButton_4 = new QPushButton(menu);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(530, 90, 141, 101));
        pushButton_5 = new QPushButton(menu);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(80, 240, 141, 101));
        pushButton_6 = new QPushButton(menu);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(310, 240, 141, 101));
        pushButton_7 = new QPushButton(menu);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(530, 240, 141, 101));
        label_4 = new QLabel(menu);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(80, 200, 141, 20));
        label_5 = new QLabel(menu);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(80, 350, 141, 20));
        label_6 = new QLabel(menu);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(310, 200, 141, 20));
        label_7 = new QLabel(menu);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(310, 350, 141, 20));
        label_8 = new QLabel(menu);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(540, 350, 141, 20));
        label_9 = new QLabel(menu);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(530, 200, 141, 20));
        stackedWidget->addWidget(menu);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "BIENVENIDO", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "D\303\255a: ", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Empecemos", nullptr));
        iniciarPedido->setText(QCoreApplication::translate("MainWindow", "INICIAR PEDIDO", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "MEN\303\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
