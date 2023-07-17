#ifndef OILRECEIVER_H
#define OILRECEIVER_H

#include <QObject>
#include <iostream>

class OilReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int oilValue READ oilValue NOTIFY oilValueChanged)

public:
    explicit OilReceiver(QObject *parent = nullptr);
    int oilValue() const { return qt_oilValue; }

signals:
    void oilValueChanged(int oil);

public slots:
    void receiveOil(int signal);

private:
    int qt_oilValue = 100;
};


#endif // OILRECEIVER_H
