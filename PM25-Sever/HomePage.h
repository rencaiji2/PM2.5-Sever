#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "PublicStruct.h"

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

private:
    void clientDataRcevice(ClientData data);

private:
    Ui::HomePage *ui;

    bool m_isCheckSet;
    QHash <int,QString>m_numToString_hash;
    QHash <QString,int>m_stringToInt_hash;
    std::vector<uint8_t> m_uint8Vector;
};

#endif // HOMEPAGE_H
