#include "dterraincell.h"

DTerrainCell::DTerrainCell()
{

}

QPoint DTerrainCell::ul()
{
    QPoint point;
    point.setX(x);
    point.setY(y);
    return point;
}

QPoint DTerrainCell::ur()
{
    QPoint point;
    point.setX(x+1);
    point.setY(y);
    return point;
}


QPoint DTerrainCell::dl()
{
    QPoint point;
    point.setX(x);
    point.setY(y+1);
    return point;
}


QPoint DTerrainCell::dr()
{
    QPoint point;
    point.setX(x+1);
    point.setY(y+1);
    return point;
}

void DTerrainCell::setX(unsigned int x)
{
    this->x = x;
}

void DTerrainCell::setY(unsigned int y)
{
    this->y = y;
}
