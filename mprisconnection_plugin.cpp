#include "mprisconnection_plugin.h"
#include "mprisconnection.h"
#include "mpris2player.h"

#include <qqml.h>

void MprisConnectionPlugin::registerTypes(const char *uri)
{
    // @uri Material.Desktop
    qmlRegisterType<MprisConnection>(uri, 1, 0, "MprisConnection");
    qmlRegisterUncreatableType<Mpris2Player>(uri, 1, 0, "Mpris2Player", "Player class");
}


