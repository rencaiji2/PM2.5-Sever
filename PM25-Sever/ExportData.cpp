#include "ExportData.h"
#include "ui_ExportData.h"
#include <WindowsManager.h>

ExportData::ExportData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExportData)
{
    ui->setupUi(this);
}

ExportData::~ExportData()
{
    delete ui;
}
