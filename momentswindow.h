#ifndef MOMENTSWINDOW_H
#define MOMENTSWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QString>

class MomentsWindow : public QDialog {
    Q_OBJECT

public:
    explicit MomentsWindow(const QString &arc,
                           const QVector<QPair<QString, QString>> &moments,
                           QWidget *parent = nullptr);

private:
    QString arcName;
    QVector<QPair<QString, QString>> momentsRef;
    QVBoxLayout *layout;

    void buildUI();
    void addMomentUI(const QString &title, const QString &link);
};

#endif // MOMENTSWINDOW_H
