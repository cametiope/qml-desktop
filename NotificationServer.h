#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QDBus>

class NotificationServer : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString app READ, QString name READ, QString replaceId READ, QString notificationIcon READ, QString summary READ, QString body READ, QString hint READ, QString timeout READ)
/*public:
    explicit NotificationServer(QObject *parent = 0);*/
public signals:
    void received();
};

#endif // NOTIFICATION_H
