#ifndef MPRIS2PLAYER_H
#define MPRIS2PLAYER_H

#include <QDBusInterface>
#include <QMap>
#include <QVariantMap>
#include <QDBusArgument>

class Mpris2Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap metadata READ metadata NOTIFY metadataNotify)

public:

    explicit Mpris2Player(QString serviceName, QObject *parent = 0) : QObject(parent),
        iface(serviceName,
                         "/org/mpris/MediaPlayer2",
                         "org.mpris.MediaPlayer2.Player") {
        QDBusConnection::sessionBus().connect(serviceName, "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties", "PropertiesChanged", this, SLOT(metadataReceived(QDBusMessage)));
    }
    ~Mpris2Player(){}

    QVariantMap metadata() const {
        QDBusInterface iface(this->iface.service(), "/org/mpris/MediaPlayer2", "org.freedesktop.DBus.Properties");
        QDBusMessage result = iface.call("Get", "org.mpris.MediaPlayer2.Player", "Metadata");
        const QDBusArgument &arg = result.arguments().at(0).value<QDBusVariant>().variant().value<QDBusArgument>();
        arg.beginMap();
        QVariantMap map;
        while (!arg.atEnd()) {
            QVariant var;
            QString str;
            arg.beginMapEntry();
            arg >> str >> var;
            arg.endMapEntry();
            map.insert(str, var);
        }
        arg.endMap();
        return map;
    }

    Q_INVOKABLE void playPause() {
        iface.call("PlayPause");
    }

    Q_INVOKABLE void next() {
        iface.call("Next");
    }
    Q_INVOKABLE void previous() {
        iface.call("Previous");
    }

    Q_INVOKABLE void stop() {
        iface.call("Stop");
    }

    Q_INVOKABLE void seek(const QVariant &position) {
        iface.call("Seek", position.toLongLong());
    }

    Q_INVOKABLE void openUri(const QVariant &uri) {
        iface.call("OpenUri", uri.toString());
    }

    QDBusInterface iface;
signals:
    QVariantMap metadataNotify(QVariantMap map);
private slots:
    void metadataReceived(QDBusMessage msg) {
        const QDBusArgument &arg = msg.arguments().at(1).value<QDBusArgument>();
        arg.beginMap();
        while (!arg.atEnd()) {
            QString key;
            arg.beginMapEntry();
            arg >> key;
            if (key == "Metadata") {
                emit metadataNotify(metadata());
            }
            arg.endMapEntry();
        }
        arg.endMap();
    }
};

#endif // MPRIS2PLAYER_H
