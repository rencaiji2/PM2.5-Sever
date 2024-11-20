#include "DrawCurve.h"
#include "ui_DrawCurve.h"
#include <WindowsManager.h>

DrawCurve::DrawCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DrawCurve)
{
    ui->setupUi(this);

    m_customPlot = new QCustomPlot(this);
    m_customPlot->setParent(ui->widget_customplot);
    m_customPlot->resize(900,460);
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持
    m_customPlot->xAxis->setRange(QDateTime::currentSecsSinceEpoch()-10,QDateTime::currentSecsSinceEpoch()+10);
    m_customPlot->yAxis->setRange(0,1000);

    m_qCPGraph_1 = m_customPlot->addGraph();
     m_qCPGraph_1->setPen(QPen(Qt::blue));
    m_qCPGraph_2 = m_customPlot->addGraph();
     m_qCPGraph_2->setPen(QPen(Qt::red));
    m_qCPGraph_3 = m_customPlot->addGraph();
     m_qCPGraph_3->setPen(QPen(Qt::yellow));
    m_qCPGraph_4 = m_customPlot->addGraph();
     m_qCPGraph_4->setPen(QPen(Qt::black));

     m_intToQCPGraph.insert(1,m_qCPGraph_1);
     m_intToQCPGraph.insert(2,m_qCPGraph_2);
     m_intToQCPGraph.insert(3,m_qCPGraph_3);
     m_intToQCPGraph.insert(4,m_qCPGraph_4);

     ui->checkBox_1->setChecked(true);
     ui->checkBox_2->setChecked(true);
     ui->checkBox_3->setChecked(true);
     ui->checkBox_4->setChecked(true);

     QVector<double> temporarily_doublevector;
     QList<QVector<double>> l1;
     l1.append(temporarily_doublevector);
     l1.append(temporarily_doublevector);
     m_drawData.insert(1,l1);
     m_drawData.insert(2,l1);
     m_drawData.insert(3,l1);
     m_drawData.insert(4,l1);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
    dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
    m_customPlot->xAxis->setTicker(dateTicker);//设置X轴为时间轴

    connect(TcpServer::getInstance(),&TcpServer::sendClientData,this,&DrawCurve::clientDataRcevice);
    m_isCanRefensh = true;
    connect(&m_timer, &QTimer::timeout,this,&DrawCurve::on_timer_slot);
    m_timer.start(10000);
    ui->comboBox->setCurrentIndex(2);
}

DrawCurve::~DrawCurve()
{
    delete ui;
}

void DrawCurve::clientDataRcevice(ClientData data)
{
    static int dataMax = 0;
    dataMax = (data.result > dataMax) ? data.result : dataMax;
    if(m_intToQCPGraph.contains(data.deviceNum))
    {
        m_drawData[data.deviceNum][0].push_back(QDateTime::currentSecsSinceEpoch());
        m_drawData[data.deviceNum][1].push_back(data.result);
        m_intToQCPGraph.value(data.deviceNum)->setData(m_drawData[data.deviceNum][0],m_drawData[data.deviceNum][1]);
        m_customPlot->xAxis->setRangeUpper(QDateTime::currentSecsSinceEpoch()+10);
        m_customPlot->yAxis->setRangeUpper(dataMax + 5);
    }
}

void DrawCurve::on_timer_slot()
{
    Replot();
}

void DrawCurve::on_checkBox_1_clicked(bool checked)
{
    m_qCPGraph_1->setVisible(checked);
    m_customPlot->replot();
}

void DrawCurve::on_checkBox_2_clicked(bool checked)
{
    m_qCPGraph_2->setVisible(checked);
    m_customPlot->replot();
}

void DrawCurve::on_checkBox_3_clicked(bool checked)
{
    m_qCPGraph_3->setVisible(checked);
    m_customPlot->replot();
}

void DrawCurve::on_checkBox_4_clicked(bool checked)
{
    m_qCPGraph_4->setVisible(checked);
    m_customPlot->replot();
}

void DrawCurve::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            m_timer.start(1000);
            m_isCanRefensh = true;
            break;
        case 1:
            m_timer.start(5000);
            m_isCanRefensh = true;
            break;
        case 2:
            m_timer.start(10000);
            m_isCanRefensh = true;
            break;
        case 3:
            m_isCanRefensh = false;
            break;
    }
}

void DrawCurve::Replot()
{
    if(m_isCanRefensh)
    {
        m_customPlot->replot();
    }
}
