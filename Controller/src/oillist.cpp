#include "oillist.h"

Oillist::Oillist(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
   myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}

void Oil::adjustOil(int scrollValue)
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "Oil : " << scrollValue << std::endl;
    myProxy->updateOil(scrollValue, callStatus, result);
    std::cout << "Check error: '" << result << "'\n";
}
