#include "oilreceiver.h"

OilReceiver::OilReceiver(QObject *parent) : QObject(parent)
{
}

void OilReceiver::receiveOil(int oil)
{
    qt_oilValue = oil;
    emit oilValueChanged(oil);
}

