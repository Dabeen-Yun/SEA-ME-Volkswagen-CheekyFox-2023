#include "HandleReceiver.h"

HandleReceiver::HandleReceiver(QObject *parent) : QObject(parent)
{
}

void HandleReceiver::receiveHandle(int handle)
{
    qt_handleValue = handle;
    emit handleValueChanged(qt_handleValue);
}
