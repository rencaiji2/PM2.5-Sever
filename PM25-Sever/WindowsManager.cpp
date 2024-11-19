#include "WindowsManager.h"

WindowsManager* WindowsManager::instance = nullptr;

WindowsManager::WindowsManager()
{
    m_homePage = new HomePage;
    m_drawCurve = new DrawCurve;
}

void WindowsManager::ShowUC(UCKeys key)
{
    QWidget * widget = GetUC(key);
    if(widget != nullptr)
    {
        for (QObject *child : m_UCParent->children()) {
            QWidget *childWidget = qobject_cast<QWidget*>(child);
            if (childWidget) {
                childWidget->hide();
            }
        }
        widget->setParent(m_UCParent);
        widget->show();
    }
}

QWidget * WindowsManager::GetUC(UCKeys key)
{
    switch (key)
    {
        case HomePageKey:
            return m_homePage;
            break;
        case DrawCurveKey:
            return m_drawCurve;
            break;
        default:
            return nullptr;
            break;
    }
}
