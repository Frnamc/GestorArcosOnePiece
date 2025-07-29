#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "arcsmanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mostrarArcos();
    void crearMomento();     // crear momento nuevo
    void actualizarMomento();// actualizar = agregar más momentos
    void eliminarMomento();
    void volverMenu();

private:
    QWidget *central;
    QVBoxLayout *layout;
    ArcsManager manager;
};

#endif // MAINWINDOW_H
