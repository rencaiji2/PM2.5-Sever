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


    QVector<double> time(200), value(200);
        for(int i = 0; i < time.count(); i++)
        {
            time[i] = QDateTime::currentSecsSinceEpoch() + i;//方法1：以此刻的时间做X轴（总秒数），一秒一个值
            //time[i] = QDateTime::currentMsecsSinceEpoch() / 1000.0 + i;//方法2
            value[i] = qrand() % 10 - 5;//[-5, 5]随机数做y值
        }//生成模拟数据

        m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持
        m_customPlot->addGraph();
        m_customPlot->graph(0)->setData(time, value);//设置数据源
        m_customPlot->graph(0)->rescaleAxes();

        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("yy-MM-dd hh:mm:ss");//日期格式(可参考QDateTime::fromString()函数)
        m_customPlot->xAxis->setTicker(dateTicker);//设置X轴为时间轴
     m_customPlot->resize(900,460);

     // 重绘图表
     m_customPlot->replot();
}

DrawCurve::~DrawCurve()
{
    delete ui;
}
