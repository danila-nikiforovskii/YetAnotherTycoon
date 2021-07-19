#ifndef DPLAYER_H
#define DPLAYER_H

#include <dnetworknode.h>
#include <QList>

class DPlayer
{
    public:
        DPlayer();

    int money;
    int loan;

    QList<DNetworkNode*> network;




};

#endif // DPLAYER_H
