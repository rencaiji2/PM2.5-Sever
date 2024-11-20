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
};

#endif // DRAWCURVE_H
