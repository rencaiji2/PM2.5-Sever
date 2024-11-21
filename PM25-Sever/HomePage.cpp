#include "HomePage.h"
#include "ui_HomePage.h"
#include <WindowsManager.h>

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    m_maxData = 0;
    ui->checkBox_isWork->setChecked(true);
    ui->btn_set->setStyleSheet("QPushButton {"
                               "    background-color: lightgray;font-size: 20pt;" // 默认背景颜色
                               "}"
                               "QPushButton:pressed {"
                               "    background-color: blue;font-size: 20pt;" // 按下时的背景颜色
                               "}");
    m_isCheckSet = false;

    for(int i=1; i<9; i++)
    {
        m_isAllOnline.insert(i,false);
    }
    connect(&m_timer, &QTimer::timeout,this,&HomePage::on_timer_slot);
    m_timer.start(30000);

    connect(TcpServer::getInstance(),&TcpServer::sendClientData,this,&HomePage::clientDataRcevice);

    init();


    m_uint8Vector = {0xea,0xea,0,0,0,0,0,0xeb,0xeb};

}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::init()
{
    m_customPlot = new QCustomPlot(this);
    m_customPlot->setParent(ui->widget_curve);
    m_customPlot->resize(ui->widget_curve->size());

    m_keyAxis = m_customPlot->xAxis;
    m_valueAxis = m_customPlot->yAxis;
    m_fossil = new QCPBars(m_keyAxis, m_valueAxis);  // 使用xAxis作为柱状图的key轴，yAxis作为value轴

    m_fossilData << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;

    m_fossil->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    m_fossil->setName("Fossil fuels"); // 设置柱状图的名字，可在图例中显示
    m_fossil->setPen(QPen(QColor(0, 168, 140).lighter(130))); // 设置柱状图的边框颜色
    m_fossil->setBrush(QColor(0, 168, 140));  // 设置柱状图的画刷颜色

    // 为柱状图设置一个文字类型的key轴，ticks决定了轴的范围，而labels决定了轴的刻度文字的显示
    QVector<QString> labels;
    m_ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
    labels << "设备1" << "设备2" << "设备3" << "设备4" << "设备5" << "设备6" << "设备7" << "设备8";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(m_ticks, labels);

    m_keyAxis->setTicker(textTicker);        // 设置为文字轴

    //m_keyAxis->setTickLabelRotation(60);     // 轴刻度文字旋转60度
    m_keyAxis->setSubTicks(false);           // 不显示子刻度
    m_keyAxis->setTickLength(0, 4);          // 轴内外刻度的长度分别是0,4,也就是轴内的刻度线不显示
    m_keyAxis->setRange(0, 9);               // 设置范围
    m_keyAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    m_valueAxis->setRange(0, 12.1);
    m_valueAxis->setPadding(35);             // 轴的内边距，可以到QCustomPlot之开始（一）看图解
    m_valueAxis->setLabel("PM2.5浓度(μg/m³)");
    m_valueAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    m_fossil->setData(m_ticks, m_fossilData);

    // 设置横轴和纵轴标签的字体大小
    QFont labelFont("Arial", 12); // 设置字体为 Arial，大小为 12
    m_customPlot->xAxis->setLabelFont(labelFont);
    m_customPlot->yAxis->setLabelFont(labelFont);

    // 设置横轴和纵轴刻度标签的字体大小
    QFont tickLabelFont("Arial", 10); // 设置字体为 Arial，大小为 10
    m_customPlot->xAxis->setTickLabelFont(tickLabelFont);
    m_customPlot->yAxis->setTickLabelFont(tickLabelFont);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    for(int i=0; i<8; i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));

        ui->tableWidget->setRowHeight(i, 50); //设置行高
    }

}


void HomePage::on_btn_set_clicked()
{
    QTimer::singleShot(50000, this, [this]()
    {
        ui->btn_set->setEnabled(true);
    });
    SendToClient senddata;
    senddata.deviceNum_send = ui->comboBox_devNum->currentIndex()+1;
    senddata.isNowConcentration_send = ui->checkBox_isWork->isChecked();
    senddata.acquisitionInterval_send = ui->comboBox_acquisitionInterval->currentIndex()+1;;
    m_uint8Vector[2] = senddata.deviceNum_send;
    m_uint8Vector[3] = senddata.isNowConcentration_send;
    m_uint8Vector[4] = senddata.acquisitionInterval_send;

    TcpServer::getInstance()->sendData(m_uint8Vector,8080 + senddata.deviceNum_send);
}

void HomePage::clientDataRcevice(ClientData data)
{
    m_maxData = (data.result > m_maxData) ? data.result : m_maxData;
    m_valueAxis->setRangeUpper(m_maxData+10);
    m_fossilData[data.deviceNum - 1] = data.result;
    m_fossil->setData(m_ticks, m_fossilData);
    m_customPlot->replot();

    if(m_isAllOnline.contains(data.deviceNum))
    {
        m_isAllOnline[data.deviceNum] = true;
    }

    QTableWidgetItem *_result = new QTableWidgetItem(QString::number(data.result));
    _result->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  //居中显示
    ui->tableWidget->setItem(data.deviceNum-1,1,_result);

    QTableWidgetItem *_isWork = new QTableWidgetItem(data.isNowConcentration ? "是" : "否");
    _isWork->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  //居中显示
    ui->tableWidget->setItem(data.deviceNum-1,2,_isWork);

    QTableWidgetItem *acquisitionInterval = new QTableWidgetItem(QString::number(data.acquisitionInterval)+"s");
    acquisitionInterval->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  //居中显示
    ui->tableWidget->setItem(data.deviceNum-1,3,acquisitionInterval);

    QTableWidgetItem *_isOnline = new QTableWidgetItem("设备已上线");
    _isOnline->setForeground(Qt::red);
    _isOnline->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  //居中显示
    ui->tableWidget->setItem(data.deviceNum-1,4,_isOnline);
}


void HomePage::on_timer_slot()
{
    m_maxData = 0;
    for(int i=0; i<8; i++)
    {
        QString text = "";
        if(ui->tableWidget->item(i, 4) != 0)
        {
            text = ui->tableWidget->item(i, 4)->text();
        }
        if(m_isAllOnline[i+1] == true)
        {
            m_isAllOnline[i+1] = false;
        }
        else if(text == "设备已上线" && m_isAllOnline[i+1] == false)
        {
            QTableWidgetItem *_isOnline = new QTableWidgetItem("设备已下线！");
            _isOnline->setForeground(Qt::gray);
            _isOnline->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  //居中显示
            ui->tableWidget->setItem(i,4,_isOnline);
        }
    }
}


void HomePage::on_tableWidget_cellClicked(int row, int column)
{
    ui->comboBox_devNum->setCurrentIndex(row);
}
