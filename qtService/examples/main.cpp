#include <QCoreApplication>
#include "qtservice.h"

class ExampleService : public QtService<QCoreApplication>
{
public:
    ExampleService(int argc, char **argv);

protected:
    void start() override;
    void stop() override;
    void pause() override;
    void resume() override;
};

ExampleService::ExampleService(int argc, char **argv)
    : QtService<QCoreApplication>(argc, argv, "ExampleService")
{
    setServiceDescription("Qt Example Service");
    setServiceFlags(QtServiceBase::CanBeSuspended);
}

void ExampleService::start()
{
    qDebug() << __FUNCTION__;
    logMessage("service start", MessageType::Information);
}

void ExampleService::stop()
{
    qDebug() << __FUNCTION__;
    logMessage("service stop", MessageType::Information);
}

void ExampleService::pause()
{
    qDebug() << __FUNCTION__;
    logMessage("service pause", MessageType::Information);
}

void ExampleService::resume()
{
    qDebug() << __FUNCTION__;
    logMessage("service resume", MessageType::Information);
}

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv);

    // return a.exec();
    ExampleService service(argc, argv);
    return service.exec();
}
