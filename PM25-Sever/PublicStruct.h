#ifndef PUBLICSTRUCT_H
#define PUBLICSTRUCT_H
#include <QObject>

struct ClientData
{
    int deviceNum;              //设备编号
    bool isNowConcentration;    //传感器是否在采集
    int result;                 //浓度结果 微克
    int acquisitionInterval;    //采集间隔/s

    ClientData()
    {
        deviceNum = -1;
        isNowConcentration = -1;
        result = -1;
        acquisitionInterval = -1;
    }
};

struct SendToClient
{
    int deviceNum_send;              //设备编号
    int isNowConcentration_send;    //传感器是否在采集
    int acquisitionInterval_send;    //采集间隔/s

    SendToClient()
    {
        deviceNum_send = -1;
        isNowConcentration_send = -1;
        acquisitionInterval_send = -1;
    }
};

enum UCKeys
{
    HomePageKey = 1,
    DrawCurveKey,
};



#endif // PUBLICSTRUCT_H
