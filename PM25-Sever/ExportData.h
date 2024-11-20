#ifndef EXPORTDATA_H
#define EXPORTDATA_H

#include <QWidget>
#include "PublicStruct.h"
namespace Ui {
class ExportData;
}

class ExportData : public QWidget
{
    Q_OBJECT

public:
    explicit ExportData(QWidget *parent = nullptr);
    ~ExportData();

private:
    Ui::ExportData *ui;
};

#endif // EXPORTDATA_H
