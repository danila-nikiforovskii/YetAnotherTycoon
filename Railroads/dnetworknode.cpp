#include "dnetworknode.h"

DNetworkNode::DNetworkNode()
{

}


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



// ===================== HORIZONTAL SIDES ========================
DHorizontalSideNode::DHorizontalSideNode(int i, int j)

{
    this->i = i+(WIDTH+1);
    this->j = j;
}


QPoint DHorizontalSideNode::tileU()
{
    QPoint ret;
    ret.setX(i-(WIDTH+1));
    ret.setY(j-1);
    return ret;
}


QPoint DHorizontalSideNode::tileD()
{
    QPoint ret;
    ret.setX(i-(WIDTH+1));
    ret.setY(j);
    return ret;
}

int DHorizontalSideNode::getNodeID()
{
    return j*(WIDTH) + i + ( (HEIGHT+1)*(WIDTH+1) );
}

// ================== VERTICAL SIDES ================

DVerticalSideNode::DVerticalSideNode(int i, int j)

{
    this->i = i+(2*WIDTH+1);
    this->j = j;
}


QPoint DVerticalSideNode::tileL()
{
    QPoint ret;
    ret.setX(i-(2*WIDTH+1)-1);
    ret.setY(j);
    return ret;
}

QPoint DVerticalSideNode::tileR()
{
    QPoint ret;
    ret.setX(i-(2*WIDTH+1));
    ret.setY(j);
    return ret;
}

int DVerticalSideNode::getNodeID()
{
    return j*(WIDTH+1) + i + ( (HEIGHT+1)*(WIDTH+1) ) + ((HEIGHT+1)*(WIDTH));
}



// =================== CORNER NODES =================

DCornerNode::DCornerNode(int i, int j)
{
    this->i = i;
    this->j =j;

}


int DCornerNode::getNodeID()
{
    return j*(WIDTH+1) + i;
}


QPoint DCornerNode:: tileUL()
{
    QPoint ret;
    ret.setX(i-1);
    ret.setY(j-1);
    return ret;
}



QPoint DCornerNode:: tileUR()
{
    QPoint ret;
    ret.setX(i);
    ret.setY(j-1);
    return ret;
}



QPoint DCornerNode:: tileDL()
{
    QPoint ret;
    ret.setX(i-1);
    ret.setY(j);
    return ret;
}

QPoint DCornerNode::tileDR()
{
    QPoint ret;
    ret.setX(i);
    ret.setY(j);
    return ret;
}






// ================ static convinience functions =============
QPoint DNetworkNode::cornerUL(int i, int j)
{
    QPoint ret;
    ret.setX(i);
    ret.setY(j);
    return ret;
}


QPoint DNetworkNode::cornerUR(int i, int j)
{
    QPoint ret;
    ret.setX(i+1);
    ret.setY(j);
    return ret;
}

QPoint DNetworkNode::cornerDL(int i, int j)
{
    QPoint ret;
    ret.setX(i);
    ret.setY(j+1);
    return ret;
}

QPoint DNetworkNode::cornerDR(int i, int j)
{
    QPoint ret;
    ret.setX(i+1);
    ret.setY(j+1);
    return ret;
}


QPoint DNetworkNode::medianL(int i, int j)
{
    QPoint ret;
    ret.setX(i+(2*WIDTH+1));
    ret.setY(j);
    return ret;
}


QPoint DNetworkNode::medianR(int i, int j)
{
    QPoint ret;
    ret.setX(i+1+(2*WIDTH+1));
    ret.setY(j);
    return ret;
}

QPoint DNetworkNode::medianU(int i, int j)
{
    QPoint ret;
    ret.setX(i+(WIDTH+1));
    ret.setY(j);
    return ret;
}

QPoint DNetworkNode::medianD(int i, int j)
{
    QPoint ret;
    ret.setX(i+(WIDTH+1));
    ret.setY(j+1);
    return ret;
}

