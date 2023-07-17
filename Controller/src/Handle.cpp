#include "Handle.h"

Handle::Handle(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
   myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}

void Handle::adjustHandle(int scrollValue)
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "Handle : " << scrollValue << std::endl;
    myProxy->updateHandle(scrollValue, callStatus, result);
    std::cout << "Check error: '" << result << "'\n";
}
