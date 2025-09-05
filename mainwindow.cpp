#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QTimer>
#include <QMap>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>



static void setRowBackground(const QBrush &brush, QAbstractItemModel *model, int row, const QModelIndex &parent = QModelIndex());

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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QStringList headers ={"Tache", "Temps","Action"};
    ui->TaskTable->setHorizontalHeaderLabels(headers);
    ui->TaskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);





    connect(ui->Addtask, &QPushButton::clicked, this, [this](){
        //demander le nom de la task
        bool ok;
        QString taskName = QInputDialog::getText(
            this,
            "Nouvelle tâche",
            "Nom de la tâche :",
            QLineEdit::Normal,
            "",
            &ok
            );
        if(ok && !taskName.trimmed().isEmpty()){
            int row = ui ->TaskTable->rowCount();
            ui->TaskTable->insertRow(row);

            //colonne 0 -> nom de la tache
            QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
            ui->TaskTable->setItem(row, 0, nameItem);

            //colonne 1 -> temps iniitalisé a 00:00
            QTableWidgetItem *timeItem = new QTableWidgetItem("00:00:00");
            ui->TaskTable->setItem(row, 1, timeItem);

            //colonne 2 -> Bouton de start/stop
            QWidget* pWidget = new QWidget();
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Start/Stop");
            QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(btn_edit);
            pLayout->setAlignment(Qt::AlignCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            ui->TaskTable->setCellWidget(row, 2, pWidget);

            QTimer *timer = new QTimer(this);
            taskTimers[row] = timer;
            taskSeconds[row] = 0;

            connect(btn_edit, &QPushButton::clicked, this, [this, row, btn_edit]() {
                if (taskTimers[row]->isActive()) {
                    // Met en pause
                    taskTimers[row]->stop();
                    btn_edit->setText("Start");
                    setRowBackground(QBrush(QColor(182,189,181)), ui->TaskTable->model(), row);

                } else {
                    // Démarre le timer
                    taskTimers[row]->start(1000);
                    btn_edit->setText("Pause");

                    setRowBackground(QBrush(QColor(148,252,134)),ui->TaskTable->model(),row);
                }
            });

            // Mise à jour de l'affichage chaque seconde
            connect(timer, &QTimer::timeout, this, [this, row]() {
                taskSeconds[row]++;

                int h = taskSeconds[row] / 3600;
                int m = (taskSeconds[row] % 3600) / 60;
                int s = taskSeconds[row] % 60;

                QString timeStr = QString("%1:%2:%3")
                                      .arg(h, 2, 10, QChar('0'))
                                      .arg(m, 2, 10, QChar('0'))
                                      .arg(s, 2, 10, QChar('0'));
                ui->TaskTable->item(row, 1)->setText(timeStr);
            });

        }
    });





    connect(ui->DeleteTask, &QPushButton::clicked, this, [this](){
        //permet de supprimer la tache choisis
        if( ui->TaskTable->currentRow() == -1)
        {
            //rien n'est selectionné
            QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une tâche !");

        }else{
            ui->TaskTable->removeRow(ui->TaskTable->currentRow());
        }
    });

    connect(ui->Renametask, &QPushButton::clicked, this, [this](){
        //permet de supprimer la tache choisis

        if( ui->TaskTable->currentRow() == -1)
        {
            //rien n'est selectionné
            QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une tâche !");

        }else{
            bool ok;
            QString taskName = QInputDialog::getText(
                this,
                "Entre le nouveau nom",
                "Nom de la tache :",
                QLineEdit::Normal,
                "",
                &ok
                );
            if(ok && !taskName.trimmed().isEmpty()){
                 ui->TaskTable->currentItem()->setText(taskName);
            }
        }
    });

    connect(ui->SaveTask, &QPushButton::clicked, this, [this]() {
        QJsonArray taskArray;  // Le tableau final

        int rowCount = ui->TaskTable->rowCount();
        for (int i = 0; i < rowCount; ++i) {
            QJsonObject taskObject;

            // Nom de la tâche (colonne 0)
            QString taskName = ui->TaskTable->item(i, 0)->text();
            taskObject["name"] = taskName;

            // Temps écoulé (en secondes)
            taskObject["seconds"] = taskSeconds[i];

            // État du timer
            taskObject["running"] = taskTimers[i]->isActive();

            // Ajout dans le tableau
            taskArray.append(taskObject);
        }

        QJsonDocument doc(taskArray);  // Convertir le tableau en document JSON
        QFile file("tasks.json");      // Crée un fichier (dans le dossier de l'exe)

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(doc.toJson(QJsonDocument::Indented));  // Écriture avec indentation
            file.close();
            QMessageBox::information(this, "Sauvegarde", "Tâches sauvegardées avec succès !");
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible d’ouvrir le fichier pour écrire.");
        }


        QMessageBox::information(this, "Sauvegarde", "Tâches préparées pour sauvegarde !");
    });


    }


MainWindow::~MainWindow()
{

    delete ui;
}
