#include <QObject>

class QHttpRequest;
class QHttpResponse;

class Greeting : public QObject
{
    Q_OBJECT
public:
    Greeting();

private Q_SLOTS:
    void handle(QHttpRequest *req, QHttpResponse *resp);
};
