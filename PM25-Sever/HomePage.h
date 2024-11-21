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
    void on_setbtn_clicked();
    void on_timer_slot();

private:
    void clientDataRcevice(ClientData data);
    void btnSetEnable(bool bl);
    void init();

private:
    Ui::HomePage *ui;

    bool m_isCheckSet;
    QHash <int,QString>m_numToString_hash;
    QHash <QString,int>m_stringToInt_hash;
    std::vector<uint8_t> m_uint8Vector;
    QTimer m_timer;
    QHash <int,bool>m_isAllOnline;   //判断所有设备上线下线
    QCustomPlot *m_customPlot;
    QCPAxis *m_keyAxis;
    QCPAxis *m_valueAxis;
    QCPBars *m_fossil;
    QVector<double> m_fossilData;
    QVector<double> m_ticks;
};

#endif // HOMEPAGE_H
