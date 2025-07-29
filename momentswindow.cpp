#include "momentswindow.h"
#include <QDesktopServices>
#include <QUrl>

MomentsWindow::MomentsWindow(const QString &arc,
                             const QVector<QPair<QString, QString>> &moments,
                             QWidget *parent)
    : QDialog(parent), arcName(arc), momentsRef(moments)
{
    setWindowTitle("Momentos de " + arcName);
    resize(500, 400);
    layout = new QVBoxLayout(this);
    buildUI();
}

void MomentsWindow::buildUI()
{
    QLabel *label = new QLabel("Momentos de " + arcName, this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 18px; font-weight: bold;");
    layout->addWidget(label);

    for (const auto &moment : momentsRef) {
        addMomentUI(moment.first, moment.second);
    }
}

void MomentsWindow::addMomentUI(const QString &title, const QString &link)
{
    QPushButton *btn = new QPushButton(title, this);
    btn->setStyleSheet("font-size: 16px;");
    btn->setMinimumHeight(40);
    connect(btn, &QPushButton::clicked, [=]() {
        QDesktopServices::openUrl(QUrl(link));
    });
    layout->addWidget(btn);
}
