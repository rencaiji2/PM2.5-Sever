#include "ExportData.h"
#include "ui_ExportData.h"
#include <WindowsManager.h>

ExportData::ExportData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportData)
{
    ui->setupUi(this);

    connect(TcpServer::getInstance(),&TcpServer::sendClientData,this,&ExportData::clientDataRcevice);

    QVector<QString> temporarily_stringvector;
    QList<QVector<QString>> l1;
    l1.append(temporarily_stringvector);
    l1.append(temporarily_stringvector);
    m_exportData.insert(1,l1);
    m_exportData.insert(2,l1);
    m_exportData.insert(3,l1);
    m_exportData.insert(4,l1);
    m_deviceNum = 1;
}

ExportData::~ExportData()
{
    delete ui;
}

void ExportData::clientDataRcevice(ClientData data)
{
    if(m_exportData.contains(data.deviceNum))
    {
        m_exportData[data.deviceNum][0].push_back(QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss"));
        m_exportData[data.deviceNum][1].push_back(QString::number(data.result));
    }
}

void ExportData::on_btn_export_clicked()
{
    ui->btn_export->setEnabled(false);
    exportData(m_deviceNum,m_exportData[m_deviceNum]);
    m_exportData[m_deviceNum][0].clear();
    m_exportData[m_deviceNum][1].clear();
    QTimer::singleShot(10000, this, [this]()
    {
        ui->btn_export->setEnabled(true);
    });
}

void ExportData::on_comboBox_currentIndexChanged(int index)
{
    m_deviceNum = index + 1;
}

void ExportData::exportData(int devNum,QList<QVector<QString>> data)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int year = currentDateTime.date().year();
    int month = currentDateTime.date().month();
    int day = currentDateTime.date().day();

    QString programDir = QCoreApplication::applicationDirPath();

    QString yearDir = programDir + "/" + QString::number(year);
    createDirectoryIfNotExists(yearDir);

    QString monthDir = yearDir + "/" + QString("%1").arg(month, 2, 10, QChar('0')); // Ensure two digits with leading zero if needed
    createDirectoryIfNotExists(monthDir);

    QString dayDir = monthDir + "/" + QString("%1").arg(day, 2, 10, QChar('0')); // Ensure two digits with leading zero if needed
    createDirectoryIfNotExists(dayDir);
    //这个注释上面是创建年月日的文件夹

    QString fileName = QString("%1年%2月%3日%4时%5分%6秒-设备"+QString::number(m_deviceNum)+".csv")
                               .arg(year).arg(month, 2, 10, QChar('0')).arg(day, 2, 10, QChar('0'))
                               .arg(currentDateTime.time().hour(), 2, 10, QChar('0'))
                               .arg(currentDateTime.time().minute(), 2, 10, QChar('0'))
                               .arg(currentDateTime.time().second(), 2, 10, QChar('0'));
    QString filePath = dayDir + "/" + fileName;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "result"<<",";
        out << "time\n";
        for(int i=0;i<data[0].size();i++)
        {
            out << (data[1].at(i))<<",";
            out << (data[0].at(i)+"\n");
        }
        file.close();
    } else {
        exit(1);
    }
}

void ExportData::createDirectoryIfNotExists(const QString &path) {
    QDir dir;
    if (!dir.exists(path)) {
        if (dir.mkdir(path)) {
            qDebug() << "Created directory: " << path;
        } else {
            exit(1);
        }
    }
}

