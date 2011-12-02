#include <QObject>

class QHttpRequest;
class QHttpResponse;

class BodyData : public QObject
{
    Q_OBJECT
public:
    BodyData();

private Q_SLOTS:
    void handle(QHttpRequest *req, QHttpResponse *resp);
};

class Responder : public QObject
{
    Q_OBJECT
public:
    Responder(QHttpRequest *req, QHttpResponse *resp);
    ~Responder();
Q_SIGNALS:
    void done();
private Q_SLOTS:
    void accumulate(const QByteArray&);
    void reply();
private:
    QHttpRequest *m_req;
    QHttpResponse *m_resp;
};
