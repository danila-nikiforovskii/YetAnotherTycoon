#ifndef DPATH_H
#define DPATH_H


#include <QList>

const double cos15 = 0.965;
const double cos30 = 0.866;
const double cos45 = 0.707;
const double cos60 = 0.5;
const double cos75 = 0.258;





const double sina[24] = {
                         0,-cos75,-cos60,-cos45,-cos30,-cos15,-1,-cos15,-cos30,-cos45,-cos60,-cos75,
                          0,cos75,cos60,cos45,cos30,cos15,1,cos15,cos30,cos45,cos60,cos75};//inverse y axis


const double cosa[24] = {1,cos15,cos30,cos45,cos60,cos75,0,-cos75,-cos60,-cos45,-cos30,-cos15,
                         -1,-cos15,-cos30,-cos45,-cos60,-cos75,0,cos75,cos60,cos45,cos30,cos15};






#define dir_r 0
#define dir_ur 3
#define dir_u 6
#define dir_ul 9
#define dir_l 12
#define dir_dl 15
#define dir_d 18
#define dir_dr 21


struct DPathPoint
{
    double t;
    int newdir;
};


class DNetworkNode;
class DNetworkListElement;

class DPath
{
public:
    QList<DPathPoint> points;

    DNetworkListElement* owner;
    DNetworkNode * start;
    DNetworkNode * end;

    DPath * forward;
    DPath * forward_junction;
    DPath * back;
    DPath * back_junction;

    static void createPath_u(QList<DPathPoint> * target);
    static void createPath_d(QList<DPathPoint> * target);

    static void createPath_l(QList<DPathPoint> * target);
    static void createPath_r(QList<DPathPoint> * target);

    static void createPath_ur(QList<DPathPoint> * target);
    static void createPath_dl(QList<DPathPoint> * target);

    static void createPath_ul(QList<DPathPoint> * target);
    static void createPath_dr(QList<DPathPoint> * target);


    static void createPath_tight_u_ul(QList<DPathPoint> * target);
    static void createPath_tight_dr_d(QList<DPathPoint> * target);

    static void createPath_tight_u_ur(QList<DPathPoint> * target);
    static void createPath_tight_dl_d(QList<DPathPoint> * target);

    static void createPath_tight_l_ul(QList<DPathPoint> * target);
    static void createPath_tight_dr_r(QList<DPathPoint> * target);

    static void createPath_tight_l_dl(QList<DPathPoint> * target);
    static void createPath_tight_ur_r(QList<DPathPoint> * target);

    static void createPath_tight_d_dl(QList<DPathPoint> * target);
    static void createPath_tight_ur_u(QList<DPathPoint> * target);

    static void createPath_tight_d_dr(QList<DPathPoint> * target);
    static void createPath_tight_ul_u(QList<DPathPoint> * target);

    static void createPath_tight_r_ur(QList<DPathPoint> * target);
    static void createPath_tight_dl_l(QList<DPathPoint> * target);

    static void createPath_tight_r_dr(QList<DPathPoint> * target);
    static void createPath_tight_ul_l(QList<DPathPoint> * target);

    static void createPath_split_u_l(QList<DPathPoint> * target);
    static void createPath_split_u_r(QList<DPathPoint> * target);

    static void createPath_split_ul_u(QList<DPathPoint> * target);
    static void createPath_split_ul_d(QList<DPathPoint> * target);

    static void createPath_split_l_u(QList<DPathPoint> * target);
    static void createPath_split_l_d(QList<DPathPoint> * target);

    static void createPath_split_dl_u(QList<DPathPoint> * target);
    static void createPath_split_dl_d(QList<DPathPoint> * target);

    static void createPath_split_d_l(QList<DPathPoint> * target);
    static void createPath_split_d_r(QList<DPathPoint> * target);

    static void createPath_split_dr_u(QList<DPathPoint> * target);
    static void createPath_split_dr_d(QList<DPathPoint> * target);

    static void createPath_split_r_u(QList<DPathPoint> * target);
    static void createPath_split_r_d(QList<DPathPoint> * target);

    static void createPath_split_ur_u(QList<DPathPoint> * target);
    static void createPath_split_ur_d(QList<DPathPoint> * target);

    DPath(DNetworkListElement* owner,
    DNetworkNode * start,
    DNetworkNode * end);
};

#endif // DPATH_H
