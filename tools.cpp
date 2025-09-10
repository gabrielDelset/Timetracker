#include "tools.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QTimer>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QModelIndex>


void setRowBackground(const QBrush &brush, QAbstractItemModel *model, int row, const QModelIndex &parent)
{
    if (!model || row < 0 || row >= model->rowCount(parent))
        return;

    if (parent.isValid() && parent.model() != model)
        return;

    for (int i = 0; i < model->columnCount(parent); ++i) {
        model->setData(model->index(row, i, parent), brush, Qt::BackgroundRole);
    }
}

//c'est dans le noms
QString ConvertIntTimestamp(int seconds)
{
    int h = seconds / 3600;
    int m = seconds % 3600 / 60;
    int s = seconds % 60;

    QString timeStr = QString("%1:%2:%3")
                          .arg(h, 2, 10, QChar('0'))
                          .arg(m, 2, 10, QChar('0'))
                          .arg(s, 2, 10, QChar('0'));

    return timeStr;
}

QJsonArray loadTasksFromFile() {
    QFile file("tasks.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Fichier non trouvé.";
        return {};  // ✅ retourne un QJsonArray vide
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (!jsonDoc.isArray()) {
        qDebug() << "Fichier JSON invalide.";
        return {};  // ✅ retourne aussi un tableau vide ici
    }

    return jsonDoc.array();  // ✅ direct, pas besoin de variable intermédiaire
}

