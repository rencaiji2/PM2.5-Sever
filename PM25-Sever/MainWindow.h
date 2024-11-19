#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "TcpServer.h"
#include "WindowsManager.h"
#include "PublicStruct.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_main_clicked();

    void on_btn_draw_clicked();

    void on_btn_export_clicked();

private:
    void homeBtnStatusChange(int num);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
