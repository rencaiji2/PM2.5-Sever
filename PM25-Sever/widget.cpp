#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(TcpServer::getInstance(),&TcpServer::sendClientData,this,&Widget::clientDataRcevice);
    m_isStartSet = false;
    m_uint8Vector = {0xea,0xea,0,0,0,0,0,0xeb,0xeb};
}

Widget::~Widget()
{
    delete ui;
}

void Widget::clientDataRcevice(ClientData data)
{
    if(data.deviceNum == 1)
    {
        ui->label_one_result->setText(QString::number(data.result)+"μg");
        if(!m_isStartSet)
        {
            ui->checkBox_one_isWork->setChecked(data.isNowConcentration);
            ui->comboBox_one_acquisitionInterval->setCurrentIndex(data.acquisitionInterval-1);
        }
    }
    else if(data.deviceNum == 2)
    {
        ui->label_two_result->setText(QString::number(data.result)+"μg");
        if(!m_isStartSet)
        {
            ui->checkBox_two_isWork->setChecked(data.isNowConcentration);
            ui->comboBox_two_acquisitionInterval->setCurrentIndex(data.acquisitionInterval-1);
        }
    }
}

int Widget::acquisitionInterval(QWidget *widget)
{
    if(widget->inherits("QComboBox"))
    {
        QComboBox *cb = (QComboBox*)widget;
        int result;
        switch (cb->currentIndex())
        {
            case 0:
                result = 1;
                break;
            case 1:
                result = 2;
                break;
            case 2:
                result = 3;
                break;
            default:
                result = 1;
                break;
        }
        return result;
    }
    return -1;
}

void Widget::on_pushButton_one_clicked()
{
    SendToClient senddata;
    senddata.deviceNum_send = 1;
    senddata.isNowConcentration_send = ui->checkBox_one_isWork->isChecked();

    senddata.acquisitionInterval_send = acquisitionInterval(ui->comboBox_one_acquisitionInterval);

    m_uint8Vector[2] = senddata.deviceNum_send;
    m_uint8Vector[3] = senddata.isNowConcentration_send;
    m_uint8Vector[4] = senddata.acquisitionInterval_send;

    TcpServer::getInstance()->sendData(m_uint8Vector,8081);
}

void Widget::on_pushButton_two_clicked()
{
    SendToClient senddata;
    senddata.deviceNum_send = 2;
    senddata.isNowConcentration_send = ui->checkBox_two_isWork->isChecked();

    senddata.acquisitionInterval_send = acquisitionInterval(ui->comboBox_two_acquisitionInterval);

    m_uint8Vector[2] = senddata.deviceNum_send;
    m_uint8Vector[3] = senddata.isNowConcentration_send;
    m_uint8Vector[4] = senddata.acquisitionInterval_send;

    TcpServer::getInstance()->sendData(m_uint8Vector,8082);
}

void Widget::on_checkBox_startSet_clicked(bool checked)
{
    m_isStartSet = checked;
}
