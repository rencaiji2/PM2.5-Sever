#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "PublicStruct.h"
#include "QTimer"
#include "qcustomplot.h"

namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    void on_btn_set_clicked();
    void on_timer_slot();

    void on_tableWidget_cellClicked(int row, int column);

private:
    void clientDataRcevice(ClientData data);
    void init();

private:
    Ui::HomePage *ui;

    bool m_isCheckSet;
    std::vector<uint8_t> m_uint8Vector;
    QTimer m_timer;
    QHash <int,bool>m_isAllOnline;   //判断所有设备上线下线
    QCustomPlot *m_customPlot;
    QCPAxis *m_keyAxis;
    QCPAxis *m_valueAxis;
    QCPBars *m_fossil;
    QVector<double> m_fossilData;
    QVector<double> m_ticks;
    int m_maxData;
};

#endif // HOMEPAGE_H
