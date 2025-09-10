#ifndef TOOLS_H
#define TOOLS_H



#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QModelIndex>

//fonction pour load les fichier
QJsonArray loadTasksFromFile();

//fonction de convertion
QString ConvertIntTimestamp(int seconds);

//fonction de colorbnackground
void setRowBackground(const QBrush &brush, QAbstractItemModel *model, int row, const QModelIndex &parent = QModelIndex());


#endif // TOOLS_H
