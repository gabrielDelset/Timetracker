#include "mainwindow.h"
#include "tools.h"
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


void MainWindow::Starting() {

   QJsonArray jsonArray  = loadTasksFromFile();

            QWidget* pWidget = new QWidget();
            QPushButton* btn_edit = new QPushButton();
            btn_edit->setText("Start/Stop");
            QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(btn_edit);
            pLayout->setAlignment(Qt::AlignCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
          //  ui->TaskTable->setCellWidget(row, 2, pWidget);

            for(int row =0; row < jsonArray.size() ; row++)
            {
                //colonne 0 -> nom de la tache
                ui->TaskTable->insertRow(row);
                QJsonObject obj = jsonArray[row].toObject();
                QString name = obj["name"].toString();
                int seconds = obj["seconds"].toInt();
                bool running = obj["running"].toBool();

                //colonne 0 -> boutton
                ui->TaskTable->setItem(row,0,new QTableWidgetItem(name));

                QTableWidgetItem *timeItem = new QTableWidgetItem("00:00:00");
               // taskSeconds[seconds];
                QString timeStr = ConvertIntTimestamp(seconds);

                //colonne 1 -> temps
                ui->TaskTable->setItem(row, 1, new QTableWidgetItem(timeStr));



                QTimer *timer = new QTimer(this);
                taskTimers[row] = timer;
                taskSeconds[row] = seconds;



                //colonne 2 -> boutton
                QPushButton* btn_edit = new QPushButton(running ? "Pause" : "Start");

                // Ajout du bouton à la cellule
                ui->TaskTable->setCellWidget(row, 2, btn_edit);

                // Connexion du bouton au timer
                if (running) {
                    taskTimers[row]->start(1000);
                    btn_edit->setText("Pause");
                    setRowBackground(QBrush(QColor(148, 252, 134)), ui->TaskTable->model(), row);
                } else {
                    taskTimers[row]->stop();
                    btn_edit->setText("Start");
                    setRowBackground(QBrush(QColor(182, 189, 181)), ui->TaskTable->model(), row);
                }

                // conection bouton
                connect(btn_edit, &QPushButton::clicked, this, [=]() {
                    if (taskTimers[row]->isActive()) {
                        taskTimers[row]->stop();
                        btn_edit->setText("Start");
                        setRowBackground(QBrush(QColor(182, 189, 181)), ui->TaskTable->model(), row);
                    } else {
                        taskTimers[row]->start(1000);
                        btn_edit->setText("Pause");
                        setRowBackground(QBrush(QColor(148, 252, 134)), ui->TaskTable->model(), row);
                    }
                });

                ui->TaskTable->setCellWidget(row,2, btn_edit); //ajout du boutton




            // Mise à jour de l'affichage chaque seconde
            connect(timer, &QTimer::timeout, this, [this, row]() {
                taskSeconds[row]++;
                QString timeStr = ConvertIntTimestamp(taskSeconds[row]);
                ui->TaskTable->item(row, 1)->setText(timeStr);
                });



                qDebug() << "row :" << row;
                qDebug() << "Tâche :" << name;
                qDebug() << "Temps :" << seconds;
                qDebug() << "En cours ?" << running;
                qDebug() << "----------------------------";

            }

       // QMessageBox::information(this, "Chargement", "Tâches lues depuis le fichier !");    pop up qu'on utilise plus
}





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QStringList headers ={"Tache", "Temps","Action"};
    ui->TaskTable->setHorizontalHeaderLabels(headers);
    ui->TaskTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    Starting();




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
                    btn_edit->setText("Stop");

                    setRowBackground(QBrush(QColor(148,252,134)),ui->TaskTable->model(),row);
                }
            });

            // Mise à jour de l'affichage chaque seconde
            connect(timer, &QTimer::timeout, this, [this, row]() {
                taskSeconds[row]++;
                QString timeStr = ConvertIntTimestamp(taskSeconds[row]);
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
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible d’ouvrir le fichier pour écrire.");
        }

    });

    connect(ui->LoadTask, &QPushButton::clicked, this, [this]() {
        loadTasksFromFile(); //on l'a déclaré en haut
    });
    }




MainWindow::~MainWindow()
{

    delete ui;
}


