#ifndef DNETWORKNODE_H
#define DNETWORKNODE_H

#include <QPoint>
#include <defines.h>
#include <QList>


enum NetworkNodeTypes
{
    corner =0,
    horiz,
    vert
};


enum RailConfig
    // see drawing for details
{
    unavalaible = -1,
    empty = 0,
    single,
    tightL,
    tightR,
    looseL,
    looseR,
    junctionL,
    junctionR,
    confluxL,
    confluxR,
    joinR,
    joinL,
    branchR,
    branchL,
    HswitchR,
    HswitchL,
    NswitchL,
    NswitchR,
    XswitchL,
    XswitchR,
    LconnectL,
    LconnectR,
    RconnectL,
    RconnectR,
};

class DNetworkListElement;

class DNetworkNode
{
    public:
        DNetworkNode() ;

    int i,j;

    virtual int getNodeID() {return -1;};
    // i: [0..width] is a corner. (total width corners)
    // [(width+1) + 0 .. (width+1)+(width-1)] is a horizonthal median (total width-1 medians)
    // [(2*width+1) + 0 .. (2*width+1)+(width)] is a vertical median (total width medians)

    // for corners: j is a trivial coordinate
    // for horizonthal medians. j is a obvious coordinate as well
    // for vertical medians j is a coordinate of the corner ABOVE

    //    * ==o== * ==o== * ==o==
    //    |       |       |
    //    o       o       o
    //    |       |       |

    // all this nodes have the same j's

    static QPoint cornerUL(int i, int j);
    static QPoint cornerUR(int i, int j);
    static QPoint cornerDL(int i, int j);
    static QPoint cornerDR(int i, int j);

    static QPoint medianL(int i, int j);
    static QPoint medianR(int i, int j);
    static QPoint medianU(int i, int j);
    static QPoint medianD(int i, int j);


};

class DHorizontalSideNode : public DNetworkNode
{
    public:
        DHorizontalSideNode(int i=0, int j=0);

    QPoint tileU();
    QPoint tileD();
    int getNodeID();

    DNetworkListElement * u = nullptr;
    DNetworkListElement * d = nullptr;

};

class DVerticalSideNode : public DNetworkNode
{
    public:
        DVerticalSideNode(int i=0, int j=0);

   QPoint tileL();
   QPoint tileR();
   int getNodeID();

   DNetworkListElement * l = nullptr;
   DNetworkListElement * r  = nullptr;

};

class DCornerNode: public DNetworkNode
{
    public:
        DCornerNode(int i=0, int j=0);

   QPoint tileUL();
   QPoint tileUR();
   QPoint tileDL();
   QPoint tileDR();

   int getNodeID();

   DNetworkListElement *ul = nullptr;
   DNetworkListElement *ur = nullptr;
   DNetworkListElement *dl  = nullptr;
   DNetworkListElement *dr = nullptr;


};

#endif // DNETWORKNODE_H
