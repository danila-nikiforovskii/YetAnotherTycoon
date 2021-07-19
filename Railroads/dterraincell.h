#ifndef DTERRAINCELL_H
#define DTERRAINCELL_H

#include <QPoint>

class DTerrainCell
{
public:
    DTerrainCell();

    unsigned int type;
    unsigned int variety;

    QPoint ul();
    QPoint ur();
    QPoint dl();
    QPoint dr();

    void setX (unsigned int x);
    void setY (unsigned int y);

    unsigned int seavariety;
    unsigned int nextvariety;
    unsigned int seaphase;
private:
    unsigned int x;
    unsigned int y;
};

#endif // DTERRAINCELL_H
