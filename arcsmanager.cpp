#include "arcsmanager.h"
#include <QFile>
#include <QTextStream>

ArcsManager::ArcsManager() {
    cargarArchivo();

    // Si el archivo estaba vacío, cargamos arcos por defecto
    if (datos.isEmpty()) {
        datos["East Blue"] = {
            {"Luffy vs Arlong", "https://www.youtube.com/watch?v=iB_RzGuxgeI"},
            {"Zoro promete no perder", "https://www.youtube.com/watch?v=JS4BpGrJVHw"},
            {"Sanji se despide de Zeff", "https://www.youtube.com/watch?v=2m3o1RX5qSM&t=3s"}
        };
        datos["Alabasta"] = {
            {"Luffy vs Crocodile", "https://www.youtube.com/watch?v=rmRzTBY-8EY"},
            {"Zoro Derrota a Daz Bones", "https://www.youtube.com/watch?v=ITatLlvp0z4"},
            {"La despedida de la princesa", "https://www.youtube.com/watch?v=6BB17oRT-PQ"}
        };
        datos["Skypiea"] = {
            {"Campana de oro", "https://www.youtube.com/shorts/OPeSXceSOLA"},
            {"Luffy vs Enel", "https://www.youtube.com/watch?v=n8lQIWvwe3Q"},
            {"Historia de Norland", "https://www.youtube.com/watch?v=FsbhvKphaiY"}
        };
        datos["Water 7"] = {
            {"Robin dice 'quiero vivir'", "https://www.youtube.com/watch?v=2leHqjkd_PU"},
            {"Usopp vs Luffy", "https://www.youtube.com/watch?v=VJ9521PZcr4"},
            {"luffy vs Blueno", "https://www.youtube.com/watch?v=MJ1WaTY_SbU"}
        };
        datos["Enies Lobby"] = {
            {"Luffy vs Lucci", "https://www.youtube.com/watch?v=RUxuVimWMfw"},
            {"Declaración de guerra", "https://www.youtube.com/watch?v=lkQjMr_VA6w"},
            {"Despedida del Go merry GO", "https://www.youtube.com/watch?v=lDuvtzrfVyg"}
        };
        datos["Thriller Bark"] = {
            {"Aqui no a pasado NADA", "https://www.youtube.com/watch?v=dEIMltfRaKc"},
            {"El sake de Binks", "https://www.youtube.com/watch?v=q81b5h6GB-Y"},
            {"Nightmare Luffy", "https://www.youtube.com/watch?v=VPUaT9ByViU"}
        };
        datos["Sabaody"] = {
            {"Luffy golpea al Tenryuubito", "https://www.youtube.com/watch?v=lXOMptbjYHE"},
            {"2Y3D", "https://www.youtube.com/watch?v=Ya3mxdIdHZ8"},
            {"¿La muerte de los sombrero de paja?", "https://www.youtube.com/watch?v=goq_wwUiiJc&list=RDgoq_wwUiiJc&start_radio=1"}
        };
        datos["Marineford"] = {
            {"Muerte de Ace", "https://www.youtube.com/watch?v=rsxNxoYIvfc"},
            {"El ONE PIECE EXISTE  ", "https://www.youtube.com/watch?v=ihMR-pNpgmE"},
            {"Garp duda entre deber y amor", "https://www.youtube.com/watch?v=70zwfRkI3zc"}
        };
        datos["Post-Marineford"] = {
            {"Mensaje con sombreros", "https://www.youtube.com/watch?v=CXEqHy4bVNg"},
            {"Entrenamiento de los mugiwaras", "https://www.youtube.com/watch?v=q5IU9XrRWKk"},
            {"Jimbe Luffy ¿Que tienes aun?", "https://www.youtube.com/watch?v=qTA8v8mbb0g"}
        };
        datos["Dressrosa"] = {
            {"Luffy vs Doflamingo", "https://www.youtube.com/watch?v=39zwuFF7aVU"},
            {"Pasado de Law", "https://www.youtube.com/watch?v=PqF9qdIiXnY"},
            {"Sabo gana la mera mera", "https://www.youtube.com/watch?v=5a1Z71E7Rcs"}
        };
        datos["Whole Cake"] = {
            {"Sanji llora por Luffy", "https://www.youtube.com/watch?v=lik4GPBli5o"},
            {"Luffy vs Katakuri", "https://www.youtube.com/watch?v=6icKB4Mqi3o"},
            {"Brook vs Big Mom", "https://www.youtube.com/watch?v=m1aL0l7ejbM"}
        };
        datos["Wano"] = {
            {"Luffy vs Kaido", "https://www.youtube.com/watch?v=tKRNOM0VsSc"},
            {"Muerte de Oden", "https://www.youtube.com/watch?v=7-pp_R6ef7o"},
            {"Zoro usa Enma", "https://www.youtube.com/watch?v=4xfXAtj9ge4"}
        };
        datos["Egghead"] = {
            {"Luffy Gear 5", "https://www.youtube.com/watch?v=scPBmrzdD0g"},
            {"Vegapunk revela verdades", "https://www.youtube.com/watch?v=7tC2zpmh1ks"},
            {"Aparicion de Saturn", "https://www.youtube.com/watch?v=kpp2PlC2Dg4"}
        };
        guardarArchivo();
    }
}

QStringList ArcsManager::getArcos() const {
    return datos.keys();
}

QVector<QPair<QString, QString>> ArcsManager::getMomentos(const QString &arco) {
    return datos.value(arco);
}

void ArcsManager::agregarMomento(const QString &arco, const QString &momento, const QString &url) {
    datos[arco].append({momento, url});
    guardarArchivo();
}

void ArcsManager::eliminarMomento(const QString &arco, const QString &momento) {
    auto &lista = datos[arco];
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i].first == momento) {
            lista.remove(i);
            break;
        }
    }
    guardarArchivo();
}

void ArcsManager::cargarArchivo() {
    QFile file("arcos.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList partes = linea.split("|");
        if (partes.size() == 3) {
            datos[partes[0]].append({partes[1], partes[2]});
        }
    }
    file.close();
}

void ArcsManager::guardarArchivo() {
    QFile file("arcos.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    for (auto arco : datos.keys()) {
        for (auto momento : datos[arco]) {
            out << arco << "|" << momento.first << "|" << momento.second << "\n";
        }
    }
    file.close();
}
