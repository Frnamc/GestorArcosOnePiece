#ifndef ARCSMANAGER_H
#define ARCSMANAGER_H

#include <QString>
#include <QVector>
#include <QPair>
#include <QMap>

class ArcsManager {
public:
    ArcsManager();
    QStringList getArcos() const;
    QVector<QPair<QString, QString>> getMomentos(const QString &arco);
    void agregarMomento(const QString &arco, const QString &momento, const QString &url);
    void eliminarMomento(const QString &arco, const QString &momento);

private:
    QMap<QString, QVector<QPair<QString, QString>>> datos;
    void cargarArchivo();
    void guardarArchivo();
};

#endif // ARCSMANAGER_H
