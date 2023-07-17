#ifndef OIL_H
#define OIL_H

#include <QObject>
#include <iostream>


#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterProxy.hpp>

using namespace v1_0::commonapi;

class Oil : public QObject
{
    Q_OBJECT

public:
    explicit Oil(QObject *parent = nullptr);
    std::shared_ptr < CommonAPI::Runtime > runtime;
    std::shared_ptr<ClusterProxy<>> myProxy;

public slots:
    void adjustOil(int scrollValue);
};

#endif // OIL_H
