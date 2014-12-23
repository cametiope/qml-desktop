#ifndef MPRISCONNECTION_H
#define MPRISCONNECTION_H

#include <QQuickItem>
#include <QDBusServiceWatcher>
#include <QDBusReply>
#include <QDBusConnectionInterface>
#include <QVariantList>
#include <mpris2player.h>
#include <QQmlListProperty>

class MprisConnection : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(MprisConnection)
    Q_PROPERTY(QQmlListProperty<Mpris2Player> playerList READ getPlayerList NOTIFY playerListChanged)

public:
    MprisConnection(QQuickItem *parent = 0);
    ~MprisConnection(){
        delete watcher;
        while (!playerList.isEmpty())
                    delete playerList.takeFirst();
    }

    QList<Mpris2Player*> playerList;
    QQmlListProperty<Mpris2Player> getPlayerList() {
        return QQmlListProperty<Mpris2Player>(this, playerList);
    }
private:
    QDBusServiceWatcher *watcher;
public slots:
    void serviceOwnerChanged(const QString &serviceName,
                                 const QString &oldOwner,
                                 const QString &newOwner);
signals:
    QQmlListProperty<Mpris2Player> playerListChanged(QQmlListProperty<Mpris2Player> playerList);
};

#endif // MPRISCONNECTION_H

