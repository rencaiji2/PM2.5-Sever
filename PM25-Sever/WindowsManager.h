#ifndef WINDOWSMANAGER_H
#define WINDOWSMANAGER_H
#include "MainWindow.h"
#include "HomePage.h"
#include "DrawCurve.h"
#include "ExportData.h"

class WindowsManager
{
public:
    WindowsManager();

    void ShowUC(UCKeys key);

    QWidget * GetUC(UCKeys key);

    static WindowsManager* getInstance() {
            if (!instance) {
                if (!instance) {
                    instance = new WindowsManager();
                }
            }
            return instance;
        }

public:
    QWidget* m_UCParent;

private:
    static WindowsManager* instance; // 静态指针，保存单例实例

    HomePage  *m_homePage;
    DrawCurve *m_drawCurve;
    ExportData *m_exportData;
};

#endif // WINDOWSMANAGER_H
