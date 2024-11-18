#include "WindowsManager.h"

WindowsManager* WindowsManager::instance = nullptr;

WindowsManager::WindowsManager()
{
    m_homePage = new HomePage;
}

void WindowsManager::ShowUC(UCKeys key)
{
    QWidget * widget = GetUC(key);
    if(widget != nullptr)
    {
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
        default:
            return nullptr;
            break;
    }
}
