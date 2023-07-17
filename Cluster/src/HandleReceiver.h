#ifndef HANDLERECEIVER_H
#define HANDLERECEIVER_H

#include <QObject>
#include <iostream>

class HandleReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int handleValue READ handleValue NOTIFY handleValueChanged)

public:
    explicit HandleReceiver(QObject *parent = nullptr);
    int handleValue() const { return qt_handleValue; }

signals:
    void handleValueChanged(int handle);

public slots:
    void receiveHandle(int signal);

private:
    int qt_handleValue = 0;
};

#endif // HANDLEOUTPUT_H
