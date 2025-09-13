#include "windows.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <QSet>
#include <QString>
#include <QDebug>

windows::windows() {



 /*   QSet<QString> getVisibleWindowProcesses() {
        QSet<QString> visibleProcesses;

        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            if (!IsWindowVisible(hwnd))
                return TRUE;

            DWORD pid;
            GetWindowThreadProcessId(hwnd, &pid);

            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
            if (hProcess) {
                TCHAR exeName[MAX_PATH];
                if (GetModuleBaseName(hProcess, NULL, exeName, MAX_PATH)) {
                    QString processName = QString::fromWCharArray(exeName).toLower();
                    reinterpret_cast<QSet<QString>*>(lParam)->insert(processName);
                }
                CloseHandle(hProcess);
            }
            return TRUE;
        }, reinterpret_cast<LPARAM>(&visibleProcesses));

        return visibleProcesses;
    }*/

}
