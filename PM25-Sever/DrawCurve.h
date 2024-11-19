#ifndef DRAWCURVE_H
#define DRAWCURVE_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class DrawCurve;
}

class DrawCurve : public QWidget
{
    Q_OBJECT

public:
    explicit DrawCurve(QWidget *parent = nullptr);
    ~DrawCurve();

private:
    Ui::DrawCurve *ui;
    QCustomPlot *m_customPlot;
};

#endif // DRAWCURVE_H
