#include "dnetworklist.h"
#include <QDebug>

DNetworkList::DNetworkList()
    {

    }

void DNetworkListElement::erase()
    {

        DNetworkListElement* prevnode = this->prev;

        if (prevnode!=nullptr)
            {
                //not the first element....
                if (this->next == nullptr)
                    {
                        prevnode->next = nullptr;

                        list->last = prevnode;
                    }
                else
                    {
                        prevnode->next = this->next;

                        next->prev = prevnode;
                    }

            }
        else
            {
                //the first element
                DNetworkListElement* nextnode = this->next;

                if (nextnode!=nullptr)
                    {

                        this->list->first = nextnode;
                        nextnode->prev = nullptr;
                    }
                else
                    {
                        //the only element...

                        this->list->first = nullptr;
                        this->list->last = nullptr;
                    }




            }

        delete this;

    }

DNetworkList::~DNetworkList()
    {
        //destruction

        DNetworkListElement * dead = last;
        DNetworkListElement * awaiting;

        while (dead!=nullptr)
            {
                awaiting = dead->prev;
                delete dead;
                dead = awaiting;
            }
    }

DNetworkListElement::~DNetworkListElement()
    {
        //destruction
    }

DNetworkListElement::DNetworkListElement()
    {
        //construction
    }




void DNetworkList::append(DNetworkListElement * newbie)
    {
        if (last!=nullptr)
            {
                last -> next = newbie;


                newbie->prev = last;
                newbie->next = nullptr;

                newbie->list = this;

                this->last = newbie;

            }
        if (first == nullptr)
            {
                first = newbie;
                newbie->prev = nullptr;
                newbie->next = nullptr;
                newbie->list = this;
                last = newbie;

            }


    }

// ======================================= ELEMENTS ===========================

straightVert::straightVert()
    {
        ax = 0;
        ay = 12;
        bx = 0;
        by = 12;
        rot = d0;
        AppendFULL(0,0);
        type = RailTypes::straightVert;
    }

void straightVert::LinkNodes()
    {
        u->d=this;
        d->u=this;
    }
void straightVert::kill()
    {
        u->d = nullptr; d->u = nullptr;

        delete d->path_u_main;
        delete u->path_d_main;

        d->path_u_main = nullptr;
        u->path_d_main = nullptr;
        erase();
    }

void straightVert::LinkPaths()
    {
        DPath * path = new DPath(this,d,u);
        DPath::createPath_u(&(path->points));
        d->path_u_main = path;

        path = new DPath(this,u,d);
        DPath::createPath_d(&(path->points));
        u->path_d_main = path;
    }


// =================
straightHoriz::straightHoriz()
    {
        ax = 0;
        ay = 12;
        bx = 0;
        by = 12;
        rot = d90;
        AppendFULL(0,0);
        type = RailTypes::straightHoriz;
    }

void straightHoriz::LinkNodes()
    {
        l->r=this;
        r->l=this;
    }

void straightHoriz::LinkPaths()
    {
        DPath * path = new DPath(this,l,r);
        DPath::createPath_r(&(path->points));
        l->path_r_main = path;

        path = new DPath(this,r,l);
        DPath::createPath_l(&(path->points));
        r->path_l_main = path;
    }

void straightHoriz::kill()
    {
        l->r = nullptr;
        r->l = nullptr;

        delete l->path_r_main;
        delete r->path_l_main;

        l->path_r_main = nullptr;
        r->path_l_main = nullptr;
        erase();
    }

// =================
diagULDR::diagULDR()
    {
        ax =1 ;
        ay = 12;
        bx = 1;
        by = 12;
        rot = d90;

        AppendFULL(0,0);
        type = RailTypes::diagULDR;
    }

void diagULDR::LinkNodes()
    {
        ul->dr=this;
        dr->ul=this;
    }

void diagULDR::LinkPaths()
    {
        DPath * path = new DPath(this,ul,dr);
        DPath::createPath_dr(&(path->points));
        ul->path_dr_main = path;

        path = new DPath(this,dr,ul);
        DPath::createPath_ul(&(path->points));
        dr->path_ul_main = path;
    }

void diagULDR::kill()
    {
        ul->dr = nullptr;
        dr->ul = nullptr;

        delete dr->path_ul_main;
        delete ul->path_dr_main;

        dr->path_ul_main = nullptr;
        ul->path_dr_main = nullptr;
        erase();
    }
// =================


diagURDL::diagURDL()
    {

        ax =1 ;
        ay = 12;
        bx = 1;
        by = 12;
        rot = d0;
        AppendFULL(0,0);
        type = RailTypes::diagURDL;
    }

void diagURDL::LinkNodes()
    {
        ur->dl=this;
        dl->ur=this;
    }

void diagURDL::LinkPaths()
    {
        DPath * path = new DPath(this,ur,dl);
        DPath::createPath_dl(&(path->points));
        ur->path_dl_main = path;

        path = new DPath(this,dl,ur);
        DPath::createPath_ur(&(path->points));
        dl->path_ur_main = path;
    }

void diagURDL::kill()
    {
        ur->dl = nullptr;
        dl->ur = nullptr;

        delete ur->path_dl_main;
        delete dl->path_ur_main;

        ur->path_dl_main = nullptr;
        dl->path_ur_main = nullptr;
        erase();
    }

//=================  tights =======================

tight_UR_R::tight_UR_R()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = d180;
        AppendFULL(0,1);AppendUL(1,1);AppendDR(1,0);AppendFULL(2,0);
        type = RailTypes::tight_UR_R;
    }

void tight_UR_R::LinkNodes()
    {
        dl->ur=this;
        r->l=this;
    }


void tight_UR_R::LinkPaths()
    {
        DPath * path = new DPath(this,dl,r);
        DPath::createPath_tight_ur_r(&(path->points));
        dl->path_ur_main = path;

        path = new DPath(this,r,dl);
        DPath::createPath_tight_l_dl(&(path->points));
        r->path_l_main = path;
    }


void tight_UR_R::kill()
    {
        dl->ur = nullptr;
        r->l = nullptr;

        delete dl->path_ur_main;
        delete r->path_l_main;

        dl->path_ur_main = nullptr;
        r->path_l_main = nullptr;
        erase();

    }
// ====================
tight_UR_U::tight_UR_U()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = m270;
        AppendFULL(0,2);AppendUL(1,1);AppendDR(0,1);AppendFULL(1,0);
        type = RailTypes::tight_UR_U;
    }

void tight_UR_U::LinkNodes()
    {
        dl->ur=this;
        u->d=this;
    }

void tight_UR_U::LinkPaths()
    {
        DPath * path = new DPath(this,dl,u);
        DPath::createPath_tight_ur_u(&(path->points));
        dl->path_ur_main = path;

        path = new DPath(this,u,dl);
        DPath::createPath_tight_d_dl(&(path->points));
        u->path_d_main = path;
    }

void tight_UR_U::kill()
    {
        dl->ur = nullptr;
        u->d = nullptr;

        delete  dl->path_ur_main;
        delete  u->path_d_main;

        dl->path_ur_main= nullptr;
        u->path_d_main = nullptr;
        erase();
    }
//=========================
tight_DR_D::tight_DR_D()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = d270;
        AppendFULL(0,0);AppendDL(1,1);AppendUR(0,1);AppendFULL(1,2);
        type = RailTypes::tight_DR_D;
    }

void tight_DR_D::LinkNodes()
    {
        ul->dr=this;
        d->u=this;

    }

void tight_DR_D::LinkPaths()
    {
        DPath * path = new DPath(this,ul,d);
        DPath::createPath_tight_dr_d(&(path->points));
        ul->path_dr_main = path;

        path = new DPath(this,d,ul);
        DPath::createPath_tight_u_ul(&(path->points));
        d->path_u_main = path;
    }

void tight_DR_D::kill()
    {
        ul->dr = nullptr;
        d->u = nullptr;

        delete ul->path_dr_main;
        delete d->path_u_main ;

        ul->path_dr_main = nullptr;
        d->path_u_main = nullptr;

        erase();
    }
// ==========================
tight_DR_R::tight_DR_R()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = m0;
        AppendFULL(0,0);AppendDL(1,0);AppendUR(1,1);AppendFULL(2,1);
        type = RailTypes::tight_DR_R;
    }

void tight_DR_R::LinkNodes()
    {
        ul->dr=this;
        r->l=this;
    }

void tight_DR_R::LinkPaths()
    {
        DPath * path = new DPath(this,ul,r);
        DPath::createPath_tight_dr_r(&(path->points));
        ul->path_dr_main = path;

        path = new DPath(this,r,ul);
        DPath::createPath_tight_l_ul(&(path->points));
        r->path_l_main = path;
    }

void tight_DR_R::kill()
    {
        ul->dr = nullptr;
        r->l = nullptr;

        delete ul->path_dr_main;
        delete r->path_l_main;
        ul->path_dr_main = nullptr;
        r->path_l_main = nullptr;
        erase();
    }
//===============

tight_DL_L::tight_DL_L()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = d0;
        AppendFULL(0,1);AppendUL(1,1);AppendDR(1,0);AppendFULL(2,0);
        type = RailTypes::tight_DL_L;
    }


void tight_DL_L::LinkPaths()
    {
        DPath * path = new DPath(this,ur,l);
        DPath::createPath_tight_dl_l(&(path->points));
        ur->path_dl_main = path;

        path = new DPath(this,l,ur);
        DPath::createPath_tight_r_ur(&(path->points));
        l->path_r_main = path;
    }

void tight_DL_L::LinkNodes()
    {
        ur->dl=this;
        l->r=this;
    }
void tight_DL_L::kill()
    {
        ur->dl = nullptr;
        l->r = nullptr;

        delete ur->path_dl_main;
        delete l->path_r_main ;

        ur->path_dl_main = nullptr;
        l->path_r_main = nullptr;

        erase();
    }
//=======================


tight_DL_D::tight_DL_D()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = m90;
        AppendFULL(0,2);AppendDR(0,1);AppendUL(1,1);AppendFULL(1,0);
        type = RailTypes::tight_DL_D;
    }

void tight_DL_D::LinkNodes()
    {
        ur->dl=this;d->u=this;
    }


void tight_DL_D::LinkPaths()
    {
        DPath * path = new DPath(this,ur,d);
        DPath::createPath_tight_dl_d(&(path->points));
        ur->path_dl_main = path;

        path = new DPath(this,d,ur);
        DPath::createPath_tight_u_ur(&(path->points));
        d->path_u_main = path;
    }

void tight_DL_D::kill()
    {
        ur->dl = nullptr; d->u = nullptr;
        delete  ur->path_dl_main;
        delete d->path_u_main;

        ur->path_dl_main = nullptr;
        d->path_u_main = nullptr;

        erase();
    }
//==========
tight_UL_U::tight_UL_U()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = d90;
        AppendFULL(0,0);AppendUR(0,1);AppendDL(1,1);AppendFULL(1,2);
        type = RailTypes::tight_UL_U;
    }

void tight_UL_U::LinkNodes()
    {dr->ul=this;u->d=this;

        }

void tight_UL_U::LinkPaths()
    {
        DPath * path = new DPath(this,dr,u);
        DPath::createPath_tight_ul_u(&(path->points));
        dr->path_ul_main = path;

        path = new DPath(this,u,dr);
        DPath::createPath_tight_d_dr(&(path->points));
        u->path_d_main = path;
    }

void tight_UL_U::kill()
    {
        dr->ul = nullptr; u->d = nullptr;
        delete dr->path_ul_main;
        delete u->path_d_main;

        dr->path_ul_main = nullptr;
        u->path_d_main = nullptr;

        erase();

    }

//===================

tight_UL_L::tight_UL_L()
    {
        ax =2 ;
        ay = 12;
        bx = 4;
        by = 13;
        rot = m180;
        AppendFULL(0,0);AppendDL(1,0);AppendUR(1,1);AppendFULL(2,1);
        type = RailTypes::tight_UL_L;

    }
void tight_UL_L::LinkNodes()
    {dr->ul=this;l->r=this;
        }

void tight_UL_L::LinkPaths()
    {
        DPath * path = new DPath(this,dr,l);
        DPath::createPath_tight_ul_l(&(path->points));
        dr->path_ul_main = path;

        path = new DPath(this,l,dr);
        DPath::createPath_tight_r_dr(&(path->points));
        l->path_r_main = path;
    }

void tight_UL_L::kill()
    {
        dr->ul = nullptr;
        l->r = nullptr;

        delete dr->path_ul_main;
        delete l->path_r_main;

        dr->path_ul_main = nullptr;
        l->path_r_main = nullptr;

        erase();
    }
