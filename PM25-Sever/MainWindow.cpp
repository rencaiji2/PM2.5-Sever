#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WindowsManager::getInstance()->m_UCParent = ui->widget_main;
    TcpServer::getInstance();
    on_btn_main_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_main_clicked()
{
    homeBtnStatusChange(1);
    WindowsManager::getInstance()->ShowUC(UCKeys::HomePageKey);  //显示主页面
}

void MainWindow::on_btn_draw_clicked()
{
    homeBtnStatusChange(2);
    WindowsManager::getInstance()->ShowUC(UCKeys::DrawCurveKey);  //显示曲线
}

void MainWindow::on_btn_export_clicked()
{
    homeBtnStatusChange(3);
    WindowsManager::getInstance()->ShowUC(UCKeys::ExportDataKey);
}

void MainWindow::homeBtnStatusChange(int num)
{
    QString checkd = "background-color:rgb(51, 153, 255); color: white;font-size: 20pt;";
    QString noCheckd = "font-size: 20pt;";
    ui->btn_main->setStyleSheet(num==1 ? checkd : noCheckd);
    ui->btn_draw->setStyleSheet(num==2 ? checkd : noCheckd);
    ui->btn_export->setStyleSheet(num==3 ? checkd : noCheckd);
}
