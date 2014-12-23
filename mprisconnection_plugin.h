#ifndef MPRISCONNECTION_PLUGIN_H
#define MPRISCONNECTION_PLUGIN_H

#include <QQmlExtensionPlugin>

class MprisConnectionPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // MPRISCONNECTION_PLUGIN_H

