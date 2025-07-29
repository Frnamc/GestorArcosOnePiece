#include "mainwindow.h"
#include "momentswindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    central = new QWidget(this);
    layout = new QVBoxLayout(central);

    central->setStyleSheet("background-color: #d2b48c;"); // café claro

    QLabel *titulo = new QLabel("Gestor de arcos de One Piece", this);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("font-size: 22px; font-weight: bold; margin: 20px;");
    layout->addWidget(titulo);

    // Opciones CRUD
    QStringList opciones = {
        "Mostrar los arcos registrados",
        "Crear un nuevo momento",
        "Actualizar (agregar) un momento",
        "Eliminar un momento",
        "Volver al menú principal"
    };

    QList<void(MainWindow::*)()> funciones = {
        &MainWindow::mostrarArcos,
        &MainWindow::crearMomento,
        &MainWindow::actualizarMomento,
        &MainWindow::eliminarMomento,
        &MainWindow::volverMenu
    };

    for (int i = 0; i < opciones.size(); i++) {
        QPushButton *btn = new QPushButton(opciones[i], this);
        btn->setMinimumHeight(40);
        btn->setStyleSheet("background-color: #5c4033; color: white; font-size: 16px;");
        connect(btn, &QPushButton::clicked, this, funciones[i]);
        layout->addWidget(btn);
    }

    setCentralWidget(central);
}

MainWindow::~MainWindow() {}

void MainWindow::mostrarArcos() {
    QStringList arcos = manager.getArcos();
    bool ok;
    QString arco = QInputDialog::getItem(this, "Arcos", "Selecciona un arco:", arcos, 0, false, &ok);
    if (ok && !arco.isEmpty()) {
        QVector<QPair<QString, QString>> momentos = manager.getMomentos(arco);
        MomentsWindow *mw = new MomentsWindow(arco, momentos, this);
        mw->exec();
    }
}

void MainWindow::crearMomento() {
    // Selecciona arco
    QStringList arcos = manager.getArcos();
    bool ok;
    QString arco = QInputDialog::getItem(this, "Nuevo momento", "Selecciona el arco:", arcos, 0, false, &ok);

    if (ok && !arco.isEmpty()) {
        QString momento = QInputDialog::getText(this, "Nuevo momento", "Título:");
        QString link = QInputDialog::getText(this, "Nuevo link", "URL:");
        if (!momento.isEmpty() && !link.isEmpty()) {
            manager.agregarMomento(arco, momento, link);
            QMessageBox::information(this, "Éxito", "Momento agregado correctamente al arco " + arco);
        }
    }
}

void MainWindow::actualizarMomento() {
    // Igual que crear, pero pensado como agregar más momentos
    crearMomento();
}

void MainWindow::eliminarMomento() {
    QStringList arcos = manager.getArcos();
    bool ok;
    QString arco = QInputDialog::getItem(this, "Eliminar", "Selecciona el arco:", arcos, 0, false, &ok);
    if (ok && !arco.isEmpty()) {
        QVector<QPair<QString, QString>> momentos = manager.getMomentos(arco);
        QStringList nombres;
        for (auto &m : momentos) nombres << m.first;
        QString momento = QInputDialog::getItem(this, "Eliminar momento", "Selecciona:", nombres, 0, false, &ok);
        if (ok && !momento.isEmpty()) {
            manager.eliminarMomento(arco, momento);
            QMessageBox::information(this, "Eliminado", "Momento borrado.");
        }
    }
}

void MainWindow::volverMenu() {
    QMessageBox::information(this, "Menú", "Ya estás en el menú principal.");
}
