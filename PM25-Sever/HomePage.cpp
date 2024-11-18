#include "HomePage.h"
#include "ui_HomePage.h"
#include <WindowsManager.h>

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    ui->btn_set->setStyleSheet("font-size: 20pt; color: white;background-color: gray;");
    m_isCheckSet = false;

    connect(TcpServer::getInstance(),&TcpServer::sendClientData,this,&HomePage::clientDataRcevice);

    m_numToString_hash.insert(1,"one");
    m_numToString_hash.insert(2,"two");
    m_numToString_hash.insert(3,"three");
    m_numToString_hash.insert(4,"four");
    m_numToString_hash.insert(5,"five");
    m_numToString_hash.insert(6,"six");
    m_numToString_hash.insert(7,"seven");
    m_numToString_hash.insert(8,"eight");

    m_stringToInt_hash.insert("btn_set_one",1);
    m_stringToInt_hash.insert("btn_set_two",2);
    m_stringToInt_hash.insert("btn_set_three",3);
    m_stringToInt_hash.insert("btn_set_four",4);
    m_stringToInt_hash.insert("btn_set_five",5);
    m_stringToInt_hash.insert("btn_set_six",6);
    m_stringToInt_hash.insert("btn_set_seven",7);
    m_stringToInt_hash.insert("btn_set_eight",8);

    ui->btn_set_one->setEnabled(false);
    connect(ui->btn_set_one,&QPushButton::clicked, this, &HomePage::on_setbtn_clicked);
    m_uint8Vector = {0xea,0xea,0,0,0,0,0,0xeb,0xeb};
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_btn_set_clicked()
{
    if(m_isCheckSet == false)
    {
        m_isCheckSet = true;
        ui->btn_set_one->setEnabled(true);
        ui->btn_set->setStyleSheet("font-size: 20pt; color: black;background-color: rgb(51, 153, 255);");
    }
    else
    {
        m_isCheckSet = false;
        ui->btn_set_one->setEnabled(false);
        ui->btn_set->setStyleSheet("font-size: 20pt; color: white;background-color: gray;");
    }
}

void HomePage::clientDataRcevice(ClientData data)
{
    QString numEnglish = m_numToString_hash.value(data.deviceNum);
    if(numEnglish != NULL)
    {
        this->findChild<QLabel*>("label_result_"+numEnglish)->setText(QString::number(data.result)+"μg/m³");
        if(!m_isCheckSet)
        {
            this->findChild<QCheckBox*>("checkBox_isWork_"+numEnglish)->setChecked(data.isNowConcentration);
            this->findChild<QComboBox*>("comboBox_acquisitionInterval_"+numEnglish)->setCurrentIndex(data.acquisitionInterval-1);
        }
    }
}

void HomePage::on_setbtn_clicked()
{
    SendToClient senddata;
    QObject *senderObj = sender();
    if (senderObj)
    {
       QPushButton *button = qobject_cast<QPushButton*>(senderObj);
       if (button)
       {
           senddata.deviceNum_send = m_stringToInt_hash.value(button->objectName());
           senddata.isNowConcentration_send = this->findChild<QCheckBox*>("checkBox_isWork_"+ m_numToString_hash.value(m_stringToInt_hash.value(button->objectName())))->isChecked();
           senddata.acquisitionInterval_send = this->findChild<QComboBox*>("comboBox_acquisitionInterval_"+ m_numToString_hash.value(m_stringToInt_hash.value(button->objectName())))->currentIndex()+1;
           m_uint8Vector[2] = senddata.deviceNum_send;
           m_uint8Vector[3] = senddata.isNowConcentration_send;
           m_uint8Vector[4] = senddata.acquisitionInterval_send;

           TcpServer::getInstance()->sendData(m_uint8Vector,8080 + senddata.deviceNum_send);
       }
    }
}
