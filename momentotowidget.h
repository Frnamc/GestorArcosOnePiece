#ifndef MOMENTOTOWIDGET_H
#define MOMENTOTOWIDGET_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMap>
#include <QString>
#include <QWidget>

class MomentosWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mostrarMomentos(const QString &arco);

private:
    QWidget *central;
    QVBoxLayout *mainLayout;
    QMap<QString, QStringList> momentosPorArco;
    QMap<QString, QStringList> urlsPorArco;
    void crearBotones();
};

#endif // MOMENTOTOWIDGET_H
