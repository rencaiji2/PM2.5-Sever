#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "TcpServer.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    int acquisitionInterval(QWidget *widget);

private slots:
    void clientDataRcevice(ClientData data);

    void on_pushButton_one_clicked();

    void on_pushButton_two_clicked();

    void on_checkBox_startSet_clicked(bool checked);

private:
    TcpServer *m_tcpsever;
    QByteArray m_arr;
    bool m_isStartSet;
    std::vector<uint8_t> m_uint8Vector;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
