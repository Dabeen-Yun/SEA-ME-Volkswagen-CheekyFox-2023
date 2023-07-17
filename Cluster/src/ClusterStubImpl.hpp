#ifndef CLUSTERSTUBIMPL_H_
#define CLUSTERSTUBIMPL_H_
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterStubDefault.hpp>
#include <QObject>

class ClusterStubImpl: public QObject, public v1_0::commonapi::ClusterStubDefault {
    Q_OBJECT
public:
    ClusterStubImpl();
    virtual ~ClusterStubImpl();
    virtual void updateSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, int _speed, updateSpeedReply_t _reply);
    virtual void updateRPM(const std::shared_ptr<CommonAPI::ClientId> _client, int _rpm, updateRPMReply_t _reply);
    virtual void updateOil(const std::shared_ptr<CommonAPI::ClientId> _client, int _oil, updateOilReply_t _reply);
    virtual void clickButtons(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _command, clickButtonsReply_t _reply);
    virtual void updateHandle(const std::shared_ptr<CommonAPI::ClientId> _client, int _handle, updateHandleReply_t _reply);

signals:
    void signalSpeed(int);
    void signalRPM(int);
    void signalOil(int);
    void signalButtons(std::string);
    void signalHandle(int);
};
#endif /* CLUSTERSTUBIMPL_H_ */
