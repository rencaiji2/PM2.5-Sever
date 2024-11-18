#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WindowsManager::getInstance()->m_UCParent = ui->widget_main;
    TcpServer::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_main_clicked()
{
    WindowsManager::getInstance()->ShowUC(UCKeys::HomePageKey);  //显示主页面
}
