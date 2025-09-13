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

#include "tools.h"
#include <windows.h>
#include <psapi.h>
#include <tchar.h>

struct WindowEnumContext {
    QSet<QString>* processes;
    QStringList* excluded;
};

QSet<QString> getVisibleWindowProcesses() {
    QSet<QString> visibleProcesses;
    QStringList excluded = {
        "explorer.exe",
        "textinputhost.exe",
        "applicationframehost.exe",
        "protonvpn.client.exe",
        "windscribe.exe",
        "overwolf.exe",
        "ms-teams.exe",
        "systemsettings.exe",
        "microsoft.media.player.exe"
    };

    // On prépare le contexte à passer au callback
    WindowEnumContext context = { &visibleProcesses, &excluded };

    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        WindowEnumContext* ctx = reinterpret_cast<WindowEnumContext*>(lParam);

        if (!IsWindowVisible(hwnd))
            return TRUE;

        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);

        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
        if (hProcess) {
            TCHAR exeName[MAX_PATH];
            if (GetModuleBaseName(hProcess, NULL, exeName, MAX_PATH)) {
                QString processName = QString::fromWCharArray(exeName).toLower();

                // Ne pas ajouter si présent dans la liste d'exclusion
                if (!ctx->excluded->contains(processName)) {
                    ctx->processes->insert(processName);
                }
            }
            CloseHandle(hProcess);
        }
        return TRUE;
    }, reinterpret_cast<LPARAM>(&context));

    return visibleProcesses;
}



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

