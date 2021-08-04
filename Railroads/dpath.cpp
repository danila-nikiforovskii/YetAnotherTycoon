#include "dpath.h"

DPath::DPath(DNetworkListElement* owner,
                   DNetworkNode * start,
                   DNetworkNode * end)
    {
        this->owner = owner;
        this->start = start;
        this->end = end;
    }


void DPath::createPath_u(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_u;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1;
            newpoint->newdir = dir_u;
            target->append(*newpoint);
            delete newpoint;
    }

void DPath::createPath_d(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_d;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1;
            newpoint->newdir = dir_d;
            target->append(*newpoint);
            delete newpoint;
    }

void DPath::createPath_l(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_l;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1;
            newpoint->newdir = dir_l;
            target->append(*newpoint);
            delete newpoint;
    }

void DPath::createPath_r(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_r;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1;
            newpoint->newdir = dir_r;
            target->append(*newpoint);
            delete newpoint;
    }

void DPath::createPath_ul(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_ul;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1.41;
            newpoint->newdir = dir_ul;
            target->append(*newpoint);
            delete newpoint;
    }

void DPath::createPath_ur(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_ur;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1.41;
            newpoint->newdir = dir_ur;
            target->append(*newpoint);
            delete newpoint;
    }

void DPath::createPath_dr(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_dr;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1.41;
            newpoint->newdir = dir_dr;
            target->append(*newpoint);
            delete newpoint;
    }


void DPath::createPath_dl(QList<DPathPoint> * target)
    {
            DPathPoint * newpoint = new DPathPoint;
            newpoint->t = 0;
            newpoint->newdir = dir_dl;
            target->append(*newpoint);
            delete newpoint;

            newpoint = new DPathPoint;
            newpoint->t = 1.41;
            newpoint->newdir = dir_dl;
            target->append(*newpoint);
            delete newpoint;
    }

//========================= tights ===================


void createPath_tight(QList<DPathPoint> * target, int start_dir, bool ccw)
    {
        int dir = start_dir;
        DPathPoint * newpoint = new DPathPoint;
         newpoint->t = 0.0;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24; //move to adjanced direction, wrap over the 0-23 range
         newpoint = new DPathPoint;
         newpoint->t = 0.195; // +0.195
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24;
         newpoint = new DPathPoint;
         newpoint->t = 0.195 + 1.215;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24;
         newpoint = new DPathPoint;
         newpoint->t = 0.195+ 1.215 + 1.215;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24;
         newpoint = new DPathPoint;
         newpoint->t = 0.195 + 1.215 + 1.215 + 0.82;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;
    }

void createPath_tight_from_corner(QList<DPathPoint> * target, int start_dir, bool ccw)
    {
        int dir = start_dir;
        DPathPoint * newpoint = new DPathPoint;
         newpoint->t = 0.0;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24; //move to adjanced direction, wrap over the 0-23 range
         newpoint = new DPathPoint;
         newpoint->t = 0.82;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24;
         newpoint = new DPathPoint;
         newpoint->t = 0.82 + 1.215;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24;
         newpoint = new DPathPoint;
         newpoint->t = 0.82 + 1.215 +1.215;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;

         dir = ((ccw?dir+1:dir-1)+24)%24;
         newpoint = new DPathPoint;
         newpoint->t = 0.82 + 1.215 + 1.215 + 0.195;
         newpoint->newdir = dir;
         target->append(*newpoint);
         delete newpoint;
    }


void DPath::createPath_tight_u_ul(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_u,true);
 }

void DPath::createPath_tight_dr_d(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_dr,false);
 }


void DPath::createPath_tight_u_ur(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_u,false);
 }

void DPath::createPath_tight_dl_d(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_dl,true);
 }



void DPath::createPath_tight_l_dl(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_l,true);
 }

void DPath::createPath_tight_ur_r(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_ur,false);
 }



void DPath::createPath_tight_l_ul(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_l,false);
 }

void DPath::createPath_tight_dr_r(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_dr,true);
 }


void DPath::createPath_tight_d_dr(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_d,true);
 }

void DPath::createPath_tight_ul_u(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_ul,false);
 }


void DPath::createPath_tight_d_dl(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_d,false);
 }

void DPath::createPath_tight_ur_u(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_ur,true);
 }




void DPath::createPath_tight_r_ur(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_r,true);
 }

void DPath::createPath_tight_dl_l(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_dl,false);
 }



void DPath::createPath_tight_r_dr(QList<DPathPoint> * target)
 {
        createPath_tight(target,dir_r,false);
 }

void DPath::createPath_tight_ul_l(QList<DPathPoint> * target)
 {
        createPath_tight_from_corner(target,dir_ul,true);
 }


