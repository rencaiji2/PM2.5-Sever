#ifndef DRAWCURVE_H
#define DRAWCURVE_H

#include <QWidget>
#include "qcustomplot.h"
#include "PublicStruct.h"

namespace Ui {
class DrawCurve;
}

class DrawCurve : public QWidget
{
    Q_OBJECT

public:
    explicit DrawCurve(QWidget *parent = nullptr);
    ~DrawCurve();

private slots:
    void clientDataRcevice(ClientData data);
    void on_timer_slot();

    void on_checkBox_1_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_checkBox_3_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_devNumSelect_currentIndexChanged(int index);

    void on_comboBox_timeSelect_currentIndexChanged(int index);

private:
    void Replot();
    void CalculateMaximumMeanMinimum(ClientData data);

private:
    Ui::DrawCurve *ui;
    QCustomPlot *m_customPlot;
    QCPGraph *m_qCPGraph_1;
    QCPGraph *m_qCPGraph_2;
    QCPGraph *m_qCPGraph_3;
    QCPGraph *m_qCPGraph_4;
    QHash<int,QCPGraph *> m_intToQCPGraph;
    QHash<int,QList<QVector<double>>> m_drawData;
    QTimer m_timer;
    bool m_isCanRefensh;  //是否可以刷新曲线
    int m_devNum;
    int m_timeSection;
};

#endif // DRAWCURVE_H
