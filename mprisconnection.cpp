#include "mprisconnection.h"

MprisConnection::MprisConnection(QQuickItem *parent):
    QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
    QDBusConnection bus = QDBusConnection::sessionBus();
        const QStringList services = bus.interface()->registeredServiceNames();

        foreach(QString name, services.filter("org.mpris.MediaPlayer2")) {
            playerList.append(new Mpris2Player(name));
        }
        watcher = new QDBusServiceWatcher(QString(), bus);

        connect(watcher, SIGNAL(serviceOwnerChanged(QString, QString, QString)),
                this, SLOT(serviceOwnerChanged(QString,QString,QString)));
}
void MprisConnection::serviceOwnerChanged(const QString &serviceName, const QString &oldOwner, const QString &newOwner) {
    if (oldOwner.isEmpty() && serviceName.startsWith("org.mpris.MediaPlayer2.")) {
                playerList.append(new Mpris2Player(serviceName));
                emit playerListChanged(QQmlListProperty<Mpris2Player>(this, playerList));
    } else if (newOwner.isEmpty() && serviceName.startsWith("org.mpris.MediaPlayer2.")) {
        for (int i = 0; i < playerList.size(); ++i) {
            if (playerList.at(i)->iface.service() == serviceName) {
                delete playerList.at(i);
                playerList.removeAt(i);
                emit playerListChanged(QQmlListProperty<Mpris2Player>(this, playerList));
            }
         }
    }
}
