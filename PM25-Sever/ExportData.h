#ifndef EXPORTDATA_H
#define EXPORTDATA_H

#include <QWidget>
#include "PublicStruct.h"
#include <QtConcurrent/QtConcurrent>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
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
    void exportData(int devNum,QList<QVector<QString>> data);

    void createDirectoryIfNotExists(const QString &path);

private slots:
    void clientDataRcevice(ClientData data);

    void on_btn_export_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ExportData *ui;

    QHash<int,QList<QVector<QString>>> m_exportData;

    int m_deviceNum;
};

#endif // EXPORTDATA_H
