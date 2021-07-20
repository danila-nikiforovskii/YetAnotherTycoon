#ifndef DNETWORKLIST_H
#define DNETWORKLIST_H

//the list of the fragments

#include <dnetworknode.h>
#include <QDebug>
enum RailTypes
{
    forgotten = -1,
    straightVert = 0,
    straightHoriz,
    diagULDR,
    diagDRUL = RailTypes::diagULDR,
    diagDLUR,
    diagURDL = RailTypes::diagDLUR,

    tight_U_UL,
    tight_DR_D = RailTypes::tight_U_UL,

    tight_U_UR,
    tight_DL_D = RailTypes::tight_U_UR,

    tight_D_DL,
    tight_UR_U = RailTypes::tight_D_DL,

    tight_D_DR,
    tight_UL_U = RailTypes::tight_D_DR,

    tight_UL_L,
    tight_R_DR = RailTypes::tight_UL_L,

    tight_DL_L,
    tight_R_UR = RailTypes::tight_DL_L,

    tight_UR_R,
    tight_L_DL = RailTypes::tight_UR_R,

    tight_DR_R,
    tight_L_UL = RailTypes::tight_DR_R,


    loose_U_UL,
    loose_DR_D = RailTypes::loose_U_UL,

    loose_U_UR,
    loose_DL_D = RailTypes::loose_U_UR,

    loose_D_DL,
    loose_UR_U = RailTypes::loose_D_DL,

    loose_D_DR,
    loose_UL_U = RailTypes::loose_D_DR,


    junction_U_UL,
    junction_U_UR,

    junction_UR_U,
    junction_UR_R,

    junction_R_UR,
    junction_R_DR,

    junction_DR_R,
    junction_DR_D,

    junction_D_DR,
    junction_D_DL,

    junction_DL_D,
    junction_DL_L,

    junction_L_DL,
    junction_L_UL,

    junction_UL_L,
    junction_UL_U,

    split_U_L,
    split_U_R,

    split_UR_R,
    split_UR_U,

    split_R_U,
    split_R_D,

    split_DR_R,
    split_DR_D,

    split_D_R,
    split_D_L,

    split_DL_D,
    split_DL_L,

    split_L_D,
    split_L_U,

    split_UL_L,
    split_UL_U,

    Njunction_U,
    Njunction_UR,
    Njunction_R,
    Njunction_DR,
    Njunction_D,
    Njunction_DL,
    Njunction_L,
    Njunction_UL,

    Xjunction_U,
    Xjunction_UR,
    Xjunction_R,
    xjunction_DR

    // PLACEHOLDERS for crossings, X-junctions et al.
};

class DNetworkList;

enum texture_rotation
{
    d0 = 0,
    d90,
    d180,
    d270,
    m0,
    m90,
    m180,
    m270
};


struct ObstructionTile
{
int u =0;
int l =0;
int r =0;
int d =0;
//   -----=
//  |\ u  /|
//  | \  / |
//  |l \/ r|
//  |  /\  |
//  | /  \ |
//  |/ d  \|
//  -------
};



struct ObstructionElement
{
        ObstructionTile tile;
        QPoint adress;
};

class DNetworkListElement
{
     public:
        DNetworkListElement();
        DNetworkList *list = nullptr;
        DNetworkListElement *prev =nullptr;
        DNetworkListElement *next =nullptr;
        virtual ~DNetworkListElement();
        virtual void kill() {erase();};
        virtual void killUpgraded() {};
        void erase();
        virtual void LinkNodes(){};
        RailTypes type = forgotten;
        int i,j;
        int ax,ay;
        int bx,by;
        texture_rotation rot;
        QList<ObstructionElement> imprint;

        void AppendObstructionElement(int u, int l, int r, int d,int i,int j)
        {
            ObstructionElement element;
            element.tile.u=u;
            element.tile.l=l;
            element.tile.d=d;
            element.tile.r=r;
            element.adress.setX(i);
            element.adress.setY(j);
            imprint.append(element);
        };

        void AppendFULL(int i,int j)
        {
            AppendObstructionElement(1,1,1,1,i,j);
        }
        void AppendUL(int i,int j)
        {
            AppendObstructionElement(1,1,0,0,i,j);
        }
        void AppendUR(int i,int j)
        {
            AppendObstructionElement(1,0,1,0,i,j);
        }

        void AppendDL(int i,int j)
        {
            AppendObstructionElement(0,1,0,1,i,j);
        }
        void AppendDR(int i,int j)
        {
            AppendObstructionElement(0,0,1,1,i,j);
        }


};





// =============== straights ==================
class straightVert:public DNetworkListElement
{
        public:
        straightVert() {     ax = 0;
                             ay = 12;
                             bx = 0;
                             by = 12;
                             rot = d0;
                            AppendFULL(0,0);
                             type = RailTypes::straightVert;
                       }
        void LinkNodes(){u->d=this;d->u=this;}
        void kill(){u->d = nullptr; d->u = nullptr;erase();}
    DHorizontalSideNode * u;
    DHorizontalSideNode * d;
};

class straightHoriz:public DNetworkListElement
{
        public:
        straightHoriz() {           ax = 0;
                                    ay = 12;
                                   bx = 0;
                                   by = 12;
                                    rot = d90;
                                   AppendFULL(0,0);
                               type = RailTypes::straightHoriz;
                        }
        void LinkNodes(){l->r=this;r->l=this;}
        void kill(){l->r = nullptr; r->l = nullptr;erase();}
        DVerticalSideNode *l;
        DVerticalSideNode *r;
};


// ================ diags =======================
class diagULDR: public DNetworkListElement
{
    public:
        diagULDR(){        ax =1 ;
                            ay = 12;
                           bx = 1;
                            by = 12;
                            rot = d90;

                            AppendFULL(0,0);
                             type = RailTypes::diagULDR;
                  }
        void LinkNodes(){ul->dr=this;dr->ul=this;}
        void kill(){ul->dr = nullptr; dr->ul = nullptr;erase();}
    DCornerNode * ul;
    DCornerNode * dr;
};

class diagURDL:public DNetworkListElement
{
        public:
        diagURDL(){        ax =1 ;
                           ay = 12;
                           bx = 1;
                           by = 12;
                           rot = d0;
                            AppendFULL(0,0);
                           type = RailTypes::diagURDL;
                  }
        void LinkNodes(){ur->dl=this;dl->ur=this;}
        void kill(){ur->dl = nullptr; dl->ur = nullptr;erase();}
    DCornerNode * ur;
    DCornerNode * dl;
};

// ================== tights ========================


class tight_UR_R:   public DNetworkListElement
{public:
    tight_UR_R(){                    ax =2 ;
                                     ay = 12;
                                     bx = 4;
                                     by = 13;
                                     rot = d180;
AppendFULL(0,1);AppendUL(1,1);AppendDR(1,0);AppendFULL(2,0);
                             type = RailTypes::tight_UR_R;
                }
     void LinkNodes(){dl->ur=this;r->l=this;}
     void kill(){dl->ur = nullptr; r->l = nullptr;erase();}
    DCornerNode * dl;
    DVerticalSideNode *r;
};

class tight_UR_U:   public DNetworkListElement
{public:
    tight_UR_U(){                ax =2 ;
                                ay = 12;
                                 bx = 4;
                                 by = 13;
                                rot = m270;
AppendFULL(0,2);AppendUL(1,1);AppendDR(0,1);AppendFULL(1,0);
                         type = RailTypes::tight_UR_U;
                }
    void LinkNodes(){dl->ur=this;u->d=this;}
    void kill(){dl->ur = nullptr; u->d = nullptr;erase();}
    DCornerNode * dl;
    DHorizontalSideNode *u;
};


class tight_DR_D:  public  DNetworkListElement
{ public:
        tight_DR_D(){         ax =2 ;
                              ay = 12;
                              bx = 4;
                              by = 13;
                              rot = d270;
AppendFULL(0,0);AppendDL(1,1);AppendUR(0,1);AppendFULL(1,2);
                  type = RailTypes::tight_DR_D;
                    }
         void LinkNodes(){ul->dr=this;d->u=this;}
         void kill(){ul->dr = nullptr; d->u = nullptr;erase();}
        DHorizontalSideNode *d;
        DCornerNode* ul;
};

class tight_DR_R:  public  DNetworkListElement
{ public:
        tight_DR_R(){                      ax =2 ;
                                            ay = 12;
                                            bx = 4;
                                            by = 13;
                                           rot = m0;
AppendFULL(0,0);AppendDL(1,0);AppendUR(1,1);AppendFULL(2,1);
                               type = RailTypes::tight_DR_R;
                    }
          void LinkNodes(){ul->dr=this;r->l=this;}
          void kill(){ul->dr = nullptr; r->l = nullptr;erase();}
        DVerticalSideNode *r;
        DCornerNode* ul;
};


class tight_DL_L:  public  DNetworkListElement
{ public:
        tight_DL_L(){                   ax =2 ;
                                         ay = 12;
                                        bx = 4;
                                        by = 13;
                                       rot = d0;
AppendFULL(0,1);AppendUL(1,1);AppendDR(1,0);AppendFULL(2,0);
                            type = RailTypes::tight_DL_L;
                    }
        void LinkNodes(){ur->dl=this;l->r=this;}
        void kill(){ur->dl = nullptr; l->r = nullptr;erase();}
        DCornerNode *ur;
        DVerticalSideNode *l;
};

class tight_DL_D:  public  DNetworkListElement
{ public:
        tight_DL_D(){            ax =2 ;
                                 ay = 12;
                                 bx = 4;
                                 by = 13;
                                 rot = m90;
AppendFULL(0,2);AppendDR(0,1);AppendUL(1,1);AppendFULL(1,0);
                     type = RailTypes::tight_DL_D;
                    }
        void LinkNodes(){ur->dl=this;d->u=this;}
        void kill(){ur->dl = nullptr; d->u = nullptr;erase();}
        DCornerNode *ur;
        DHorizontalSideNode *d;
};


class tight_UL_U:   public DNetworkListElement
{ public:
    tight_UL_U(){               ax =2 ;
                                ay = 12;
                                bx = 4;
                                 by = 13;
                                 rot = d90;
AppendFULL(0,0);AppendUR(0,1);AppendDL(1,1);AppendFULL(1,2);
                        type = RailTypes::tight_UL_U;
                }
     void LinkNodes(){dr->ul=this;u->d=this;}
     void kill(){dr->ul = nullptr; u->d = nullptr;erase();}
    DCornerNode *dr;
    DHorizontalSideNode *u;
};

class tight_UL_L:  public DNetworkListElement
{ public:
    tight_UL_L(){                    ax =2 ;
                                     ay = 12;
                                     bx = 4;
                                     by = 13;
                                     rot = m180;
  AppendFULL(0,0);AppendDL(1,0);AppendUR(1,1);AppendFULL(2,1);
                               type = RailTypes::tight_UL_L;

                }
    void LinkNodes(){dr->ul=this;l->r=this;}
    void kill(){dr->ul = nullptr; l->r = nullptr;qDebug()<<"bye cruel world";erase();}
    DCornerNode *dr;
    DVerticalSideNode *l;
};

//=========================== JUNCTIONS ===================================

class junctionU_UL: public DNetworkListElement

{ public:
        junctionU_UL(){         ax =2 ;
                              ay = 14;
                              bx = 4;
                              by = 15;
                              rot = d270;
                    AppendFULL(0,0);AppendFULL(1,1);AppendUR(0,1);AppendFULL(1,2);
                  type = RailTypes::junction_U_UL;
                    }
         void LinkNodes(){ul->dr=this; d->u=this; u->d=this;}

         void killUpgraded(){

             if (ul->dr!=nullptr) ul->dr->kill();
             if (d->u!=nullptr) d->u->kill();
             if (u->d!=nullptr) u->d->kill();

         }

         void kill(){ul->dr = nullptr; d->u = nullptr; u->d=nullptr; erase();}


        DHorizontalSideNode *d;
        DHorizontalSideNode *u;
        DCornerNode *ul;
};

class junctionU_UR: public DNetworkListElement
{
         public:
        junctionU_UR(){         ax =2 ;
                                ay = 14;
                                bx = 4;
                                by = 15;
                                rot = m90;
                      AppendFULL(1,0);AppendFULL(0,1);AppendUL(1,1);AppendFULL(0,2);
                    type = RailTypes::junction_U_UR;
                      }

        void LinkNodes(){ur->dl=this; d->u=this; u->d=this;}

        void killUpgraded(){

            if (ur->dl!=nullptr) ur->dl->kill();
            if (d->u!=nullptr) d->u->kill();
            if (u->d!=nullptr) u->d->kill();

        }

        void kill(){ur->dl = nullptr; d->u = nullptr; u->d=nullptr; erase();}

        DHorizontalSideNode *d;
        DHorizontalSideNode *u;
        DCornerNode *ur;
};

class junctionUR_U: public DNetworkListElement
{
public:
    junctionUR_U()     {   ax = 2 ;
                           ay = 16;
                           bx = 4;
                           by = 17;
                           rot = d90;
                           AppendFULL(1,0);AppendFULL(1,1);AppendDR(0,1);AppendFULL(0,2);
                         type = RailTypes::junction_UR_U;
                       }
                       void LinkNodes(){ dl->ur=this;ur->dl=this;u->d=this;}
                       void kill(){ ur->dl=nullptr;ur->dl=nullptr;u->d=nullptr;erase();}
                       void killUpgraded(){

                           if (ur->dl!=nullptr) ur->dl->kill();
                           if (dl->ur!=nullptr) dl->ur->kill();
                           if (u->d!=nullptr) u->d->kill();

                       }
      DCornerNode *dl;
      DCornerNode *ur;
      DHorizontalSideNode *u;
};

class junctionUR_R: public DNetworkListElement
{public:
    junctionUR_R()     {   ax = 2 ;
                           ay = 16;
                           bx = 4;
                           by = 17;
                           rot = m0;
                           AppendFULL(0,1);AppendFULL(1,0);AppendUL(1,1);AppendFULL(2,0);
                         type = RailTypes::junction_UR_R;
                       }
                       void LinkNodes(){ dl->ur=this;ur->dl=this;r->l=this;}
                       void kill(){ ur->dl=nullptr;ur->dl=nullptr;r->l=nullptr;erase();}
                       void killUpgraded(){

                           if (ur->dl!=nullptr) ur->dl->kill();
                           if (dl->ur!=nullptr) dl->ur->kill();
                           if (r->l!=nullptr) r->l->kill();

                       }

      DCornerNode *dl;
      DCornerNode *ur;
      DVerticalSideNode *r;
};

class junctionR_UR: public DNetworkListElement
{
    public:
        junctionR_UR()
        {   ax = 2 ;
            ay = 14;
            bx = 4;
            by = 15;
            rot = d0;
            AppendFULL(0,1);AppendFULL(1,1);AppendDR(0,1);AppendFULL(0,2);
          type = RailTypes::junction_R_UR;
        }
        void LinkNodes(){ l->r=this;r->l=this;ur->dl=this;}
        void kill(){ r->l=nullptr;l->r=nullptr;ur->dl=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (ur->dl!=nullptr) ur->dl->kill();

        }
DVerticalSideNode *l;
DVerticalSideNode *r;
DCornerNode *ur;
};

class junctionR_DR: public DNetworkListElement
{
       public:
                junctionR_DR()
                {   ax =2 ;
                    ay = 14;
                    bx = 4;
                    by = 15;
                    rot = m180;
                    AppendFULL(0,0);AppendFULL(1,0);AppendUR(0,1);AppendFULL(2,1);
                  type = RailTypes::junction_R_DR;
                }
                void LinkNodes(){ l->r=this;r->l=this;dr->ul=this;}
                void kill(){ r->l=nullptr;l->r=nullptr;dr->ul=nullptr;erase();}
                void killUpgraded(){

                    if (l->r!=nullptr) l->r->kill();
                    if (r->l!=nullptr) r->l->kill();
                    if (dr->ul!=nullptr) dr->ul->kill();

                }


DVerticalSideNode *l;
DVerticalSideNode *r;
DCornerNode *dr;
};

class junctionDR_R: public DNetworkListElement
{ public:
        junctionDR_R() {   ax = 2 ;
                           ay = 16;
                           bx = 4;
                           by = 17;
                           rot = d180;
                           AppendFULL(0,0);AppendFULL(1,1);AppendDR(1,0);AppendFULL(2,1);
                         type = RailTypes::junction_DR_D;
                       }
                       void LinkNodes(){ ul->dr=this;ul->dr=this;r->l=this;}
                       void kill(){ ul->dr=nullptr;ul->dr=nullptr;r->l=nullptr;erase();}
                       void killUpgraded(){

                           if (ul->dr!=nullptr) ul->dr->kill();
                           if (dr->ul!=nullptr) dr->ul->kill();
                           if (r->l!=nullptr) r->l->kill();

                       }
        DCornerNode *ul;
        DCornerNode *dr;
        DVerticalSideNode *r;
};

class junctionDR_D: public DNetworkListElement
{
public:
        junctionDR_D() {   ax = 2 ;
                           ay = 16;
                           bx = 4;
                           by = 17;
                           rot = m90;
                           AppendFULL(0,0);AppendFULL(1,1);AppendUR(0,1);AppendFULL(1,2);
                         type = RailTypes::junction_DR_D;
                       }
                       void LinkNodes(){ ul->dr=this;ul->dr=this;d->u=this;}
                       void kill(){ ul->dr=nullptr;ul->dr=nullptr;d->u=nullptr;erase();}
                       void killUpgraded(){

                           if (ul->dr!=nullptr) ul->dr->kill();
                           if (dr->ul!=nullptr) dr->ul->kill();
                           if (d->u!=nullptr) d->u->kill();

                       }
    DCornerNode *ul;
    DCornerNode *dr;
    DHorizontalSideNode *d;
};

class junctionD_DL:public DNetworkListElement
{
    public:
        junctionD_DL()
        {
                                        ax =2 ;
                                       ay = 14;
                                       bx = 4;
                                       by = 15;
                                       rot = m270;
                                       AppendFULL(1,0);AppendFULL(1,1);AppendDR(0,1);AppendFULL(0,2);
                                     type = RailTypes::junction_D_DL;
        }
        void LinkNodes(){ u->d=this;d->u=this;dl->ur=this;}
        void kill(){ u->d=nullptr;d->u=nullptr;dl->ur=nullptr;erase();}
        void killUpgraded(){

            if (dl->ur!=nullptr) dl->ur->kill();
            if (d->u!=nullptr) d->u->kill();
            if (u->d!=nullptr) u->d->kill();

        }
        DHorizontalSideNode *u;
        DHorizontalSideNode *d;
        DCornerNode * dl;
};

class junctionD_DR:public DNetworkListElement
{public:
        junctionD_DR(){         ax =2 ;
                              ay = 14;
                              bx = 4;
                              by = 15;
                              rot = d90;
                    AppendFULL(0,0);AppendFULL(0,1);AppendDL(1,1);AppendFULL(1,2);
                  type = RailTypes::junction_D_DR;
                    };
         void LinkNodes(){dr->ul=this; d->u=this; u->d=this;}

         void killUpgraded(){

             if (dr->ul!=nullptr) dr->ul->kill();
             if (d->u!=nullptr) d->u->kill();
             if (u->d!=nullptr) u->d->kill();

         }

         void kill(){dr->ul = nullptr; d->u = nullptr; u->d=nullptr; erase();}


        DHorizontalSideNode *u;
        DHorizontalSideNode *d;
        DCornerNode * dr;
};

class junctionDL_D: public DNetworkListElement
{
public:
        junctionDL_D() {   ax = 2 ;
                           ay = 16;
                           bx = 4;
                           by = 17;
                           rot = d270;
                           AppendFULL(1,0);AppendFULL(0,1);AppendUL(1,1);AppendFULL(0,2);
                         type = RailTypes::junction_DR_D;
                       }
                       void LinkNodes(){ ur->dl=this;dl->ur=this;d->u=this;}
                       void kill(){ ur->dl=nullptr;dl->ur=nullptr;d->u=nullptr;erase();}
                       void killUpgraded(){

                           if (ur->dl!=nullptr) ur->dl->kill();
                           if (dl->ur!=nullptr) dl->ur->kill();
                           if (d->u!=nullptr) d->u->kill();

                       }
        DCornerNode *ur;
        DCornerNode *dl;
        DHorizontalSideNode *d;
};

class junctionDL_L: public DNetworkListElement
{public:
    junctionDL_L(){   ax = 2 ;
                      ay = 16;
                                bx = 4;
                                          by = 17;
                                                    rot = m180;
                                                              AppendFULL(0,1);AppendFULL(1,1);AppendDR(1,0);AppendFULL(2,0);
                                                                        type = RailTypes::junction_DL_L;
                      }
    void LinkNodes(){ ur->dl=this;dl->ur=this;l->r=this;}
    void kill(){ ur->dl=nullptr;dl->ur=nullptr;l->r=nullptr;erase();}
    void killUpgraded(){

            if (ur->dl!=nullptr) ur->dl->kill();
            if (dl->ur!=nullptr) dl->ur->kill();
            if (l->r!=nullptr) l->r->kill();

        }
    DCornerNode *ur;
    DCornerNode *dl;
    DVerticalSideNode *l;
};

class junctionL_DL: public DNetworkListElement
{
public:
        junctionL_DL()
            {
                ax = 2 ;
                 ay = 14;
                  bx = 4;
                   by = 15;
                 rot = d180;
                  type = RailTypes::junction_L_DL;
 AppendFULL(0,1);AppendFULL(1,0);AppendUR(1,1);AppendFULL(2,0);
            }

        void LinkNodes(){ l->r=this;r->l=this;dl->ur=this;}
        void kill(){ r->l=nullptr;l->r=nullptr;dl->ur=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (dl->ur!=nullptr) dl->ur->kill();

        }

        DVerticalSideNode *r;
        DVerticalSideNode *l;
        DCornerNode *dl;
};

class junctionL_UL: public DNetworkListElement
{
    public:
        junctionL_UL()
        {   ax = 2 ;
            ay = 14;
            bx = 4;
            by = 15;
            rot = m0;
            AppendFULL(0,0);AppendFULL(1,1);AppendDL(1,0);AppendFULL(2,1);
          type = RailTypes::junction_L_UL;
        }
        void LinkNodes(){ l->r=this;r->l=this;ul->dr=this;}
        void kill(){ r->l=nullptr;l->r=nullptr;ul->dr=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (ul->dr!=nullptr) ul->dr->kill();

        }

        DVerticalSideNode *r;
        DVerticalSideNode *l;
        DCornerNode *ul;
};

class junctionUL_L: public DNetworkListElement
{
public:
    junctionUL_L()
            {   ax = 2 ;
                ay = 16;
                bx = 4;
                by = 17;
                rot = d0;
                AppendFULL(0,0);AppendFULL(1,0);AppendUR(1,1);AppendFULL(2,1);
              type = RailTypes::junction_UL_L;
            }
            void LinkNodes(){ ul->dr=this;dr->ul=this;l->r=this;}
            void kill(){ dr->ul=nullptr;ul->dr=nullptr;l->r=nullptr;erase();}
            void killUpgraded(){

                if (dr->ul!=nullptr) dr->ul->kill();
                if (ul->dr!=nullptr) ul->dr->kill();
                if (l->r!=nullptr) l->r->kill();

            }

    DCornerNode *dr;
    DCornerNode *ul;
    DVerticalSideNode*l;
};

class junctionUL_U: public DNetworkListElement
{
public:
    junctionUL_U()
        {ax = 2 ;
            ay = 16;
            bx = 4;
            by = 17;
            rot = m270;
            AppendFULL(0,0);AppendFULL(0,1);AppendDL(1,1);AppendFULL(1,2);
          type = RailTypes::junction_UL_U;
        }
    void LinkNodes(){ ul->dr=this;dr->ul=this;u->d=this;}
    void kill(){ dr->ul=nullptr;ul->dr=nullptr;u->d=nullptr;erase();}
    void killUpgraded(){

        if (dr->ul!=nullptr) dr->ul->kill();
        if (ul->dr!=nullptr) ul->dr->kill();
        if (u->d!=nullptr) u->d->kill();

    }
    DCornerNode *dr;
    DCornerNode *ul;
    DHorizontalSideNode *u;
};

// ====================== SPLITS =================
class splitU_L: public DNetworkListElement
{
    public:
        splitU_L() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = d0;
            AppendFULL(0,0);
            AppendFULL(0,1);AppendFULL(1,1);
            AppendUR(0,2);AppendFULL(1,2);

            type = RailTypes::split_U_L;
        }

        void LinkNodes(){ u->d=this;d->u=this;ul->d=this;}
        void kill(){ u->d=nullptr;d->u=nullptr;ul->d=nullptr;erase();}
        void killUpgraded(){

            if (u->d!=nullptr) u->d->kill();
            if (d->u!=nullptr) d->u->kill();
            if (ul->d!=nullptr) ul->d->kill();

        }



        DHorizontalSideNode *d;
        DHorizontalSideNode *u;

        DHorizontalSideNode *ul;
};

class splitU_R: public DNetworkListElement
{
    public:
        splitU_R() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = m0;
            AppendFULL(1,0);
            AppendFULL(0,1);AppendFULL(1,1);
            AppendUL(1,2);AppendFULL(0,2);

            type = RailTypes::split_U_R;
        }

        void LinkNodes(){ u->d=this;d->u=this;ur->d=this;}
        void kill(){ u->d=nullptr;d->u=nullptr;ur->d=nullptr;erase();}
        void killUpgraded(){

            if (u->d!=nullptr) u->d->kill();
            if (d->u!=nullptr) d->u->kill();
            if (ur->d!=nullptr) ur->d->kill();
        }

        DHorizontalSideNode *d;
        DHorizontalSideNode *u;
        DHorizontalSideNode *ur;
};

class splitUR_U: public DNetworkListElement
{

    public:
        splitUR_U(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = d0;
                      AppendFULL(1,0);
                      AppendDR(0,1);AppendFULL(1,1);
                      AppendFULL(0,2);
                       type = RailTypes::split_UR_U;
                  }

        void LinkNodes(){ ur->dl=this;dl->ur=this;u->dl=this;}
        void kill(){ ur->dl=nullptr;dl->ur=nullptr;u->dl=nullptr;erase();}
        void killUpgraded(){

            if (ur->dl!=nullptr) ur->dl->kill();
            if (dl->ur!=nullptr) dl->ur->kill();
            if (u->dl!=nullptr) u->dl->kill();
        }



        DCornerNode *dl;
        DCornerNode *ur;
        DCornerNode *u;

};

class splitUR_R: public DNetworkListElement
{
    public:
        splitUR_R(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = m90;
                      AppendFULL(0,1);
                      AppendUL(1,1);AppendFULL(1,0);
                      AppendFULL(2,0);
                       type = RailTypes::split_UR_R;
                  }
        void LinkNodes(){ ur->dl=this;dl->ur=this;r->dl=this;}
        void kill(){ ur->dl=nullptr;dl->ur=nullptr;r->dl=nullptr;erase();}
        void killUpgraded(){

            if (ur->dl!=nullptr) ur->dl->kill();
            if (dl->ur!=nullptr) dl->ur->kill();
            if (r->dl!=nullptr) r->dl->kill();
        }


        DCornerNode *dl;
        DCornerNode *ur;
        DCornerNode *r;
};


class splitR_U: public DNetworkListElement
{
    public:  splitR_U() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = d90;
            AppendFULL(0,1);AppendFULL(1,1);
            AppendUL(0,0);AppendFULL(1,0);AppendFULL(2,0);
            type = RailTypes::split_R_U;
        }

        void LinkNodes(){ l->r=this;r->l=this;u->l=this;}
        void kill(){ l->r=nullptr;r->l=nullptr;u->l=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (u->l!=nullptr) u->l->kill();
        }

        DVerticalSideNode * l;
        DVerticalSideNode * r;
        DVerticalSideNode * u;
};

class splitR_D: public DNetworkListElement
{
    public:  splitR_D() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = m90;
            AppendFULL(0,0);AppendFULL(1,0);
            AppendUR(0,1);AppendFULL(1,1);AppendFULL(2,1);
            type = RailTypes::split_R_D;
        }

        void LinkNodes(){ l->r=this;r->l=this;d->l=this;}
        void kill(){ l->r=nullptr;r->l=nullptr;d->l=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (d->l!=nullptr) d->l->kill();
        }

        DVerticalSideNode * l;
        DVerticalSideNode * r;
        DVerticalSideNode * d;
};

class splitDR_R: public DNetworkListElement
{
    public:
        splitDR_R(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = d90;
                      AppendFULL(0,0);AppendFULL(1,0);
                      AppendDL(2,0);AppendFULL(1,1);
                      AppendFULL(2,1);
                       type = RailTypes::split_DR_R;
                  }


        void LinkNodes(){ ul->dr=this;dr->ul=this;r->ul=this;}
        void kill(){ ul->dr=nullptr;dr->ul=nullptr;r->ul=nullptr;erase();}
        void killUpgraded(){

            if (ul->dr!=nullptr) ul->dr->kill();
            if (dr->ul!=nullptr) dr->ul->kill();
            if (r->ul!=nullptr) r->ul->kill();
        }
        DCornerNode *ul;
        DCornerNode *dr;
        DCornerNode *r;
};

class splitDR_D: public DNetworkListElement
{
    public:
        splitDR_D(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = m180;
                      AppendFULL(0,0);AppendFULL(0,1);
                      AppendUR(0,2);AppendFULL(1,1);
                      AppendFULL(1,2);
                       type = RailTypes::split_DR_D;
                  }


        void LinkNodes(){ ul->dr=this;dr->ul=this;d->ul=this;}
        void kill(){ ul->dr=nullptr;dr->ul=nullptr;d->ul=nullptr;erase();}
        void killUpgraded(){

            if (ul->dr!=nullptr) ul->dr->kill();
            if (dr->ul!=nullptr) dr->ul->kill();
            if (d->ul!=nullptr) d->ul->kill();
        }
        DCornerNode *ul;
        DCornerNode *dr;
        DCornerNode *d;
};


class splitD_R: public DNetworkListElement
{
    public:
        splitD_R() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = d180;
            AppendFULL(0,0);AppendDL(1,0);
            AppendFULL(0,1);AppendFULL(1,1);
           AppendFULL(1,2);

            type = RailTypes::split_D_R;
        }

        void LinkNodes(){ u->d=this;d->u=this;dr->u=this;}
        void kill(){ u->d=nullptr;d->u=nullptr;dr->u=nullptr;erase();}
        void killUpgraded(){
            if (u->d!=nullptr) u->d->kill();
            if (d->u!=nullptr) d->u->kill();
            if (dr->u!=nullptr) dr->u->kill();
        }


        DHorizontalSideNode *d;
        DHorizontalSideNode *u;
        DHorizontalSideNode *dr;
};

class splitD_L: public DNetworkListElement
{
    public:
        splitD_L() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = m180;
            AppendDR(0,0);AppendFULL(1,0);
            AppendFULL(0,1);AppendFULL(1,1);
            AppendFULL(0,2);

            type = RailTypes::split_D_L;
        }

        void LinkNodes(){ u->d=this;d->u=this;dl->u=this;}
        void kill(){ u->d=nullptr;d->u=nullptr;dl->u=nullptr;erase();}
        void killUpgraded(){

            if (u->d!=nullptr) u->d->kill();
            if (d->u!=nullptr) d->u->kill();
            if (dl->u!=nullptr) dl->u->kill();
        }

        DHorizontalSideNode *d;
        DHorizontalSideNode *u;
        DHorizontalSideNode *dl;
};


class splitDL_D: public DNetworkListElement
{

    public:
        splitDL_D(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = d180;
                      AppendFULL(1,0);
                      AppendUR(1,1);AppendFULL(0,1);
                      AppendFULL(0,2);
                       type = RailTypes::split_DL_L;
                  }

        void LinkNodes(){ ur->dl=this;dl->ur=this;d->ur=this;}
        void kill(){ ur->dl=nullptr;dl->ur=nullptr;d->ur=nullptr;erase();}
        void killUpgraded(){

            if (ur->dl!=nullptr) ur->dl->kill();
            if (dl->ur!=nullptr) dl->ur->kill();
            if (d->ur!=nullptr) d->ur->kill();
        }



        DCornerNode *dl;
        DCornerNode *ur;
        DCornerNode *d;

};

class splitDL_L: public DNetworkListElement
{
    public:
        splitDL_L(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = m270;
                      AppendFULL(0,1);
                      AppendDR(1,0);AppendFULL(1,01);
                      AppendFULL(2,0);
                       type = RailTypes::split_DL_D;
                  }
        void LinkNodes(){ ur->dl=this;dl->ur=this;l->ur=this;}
        void kill(){ ur->dl=nullptr;dl->ur=nullptr;l->ur=nullptr;erase();}
        void killUpgraded(){

            if (ur->dl!=nullptr) ur->dl->kill();
            if (dl->ur!=nullptr) dl->ur->kill();
            if (l->ur!=nullptr) l->ur->kill();
        }


        DCornerNode *dl;
        DCornerNode *ur;
        DCornerNode *l;
};


class splitL_D: public DNetworkListElement
{
    public:  splitL_D() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = d270;
            AppendFULL(1,0);AppendFULL(2,0);
            AppendDL(2,1);AppendFULL(1,1);AppendFULL(0,1);
            type = RailTypes::split_L_D;
        }

        void LinkNodes(){ l->r=this;r->l=this;d->r=this;}
        void kill(){ l->r=nullptr;r->l=nullptr;d->r=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (d->r!=nullptr) d->r->kill();
        }

        DVerticalSideNode * l;
        DVerticalSideNode * r;
        DVerticalSideNode * d;
};

class splitL_U: public DNetworkListElement
{
    public:  splitL_U() {
            ax = 0;
            ay = 14;
            bx=1;
            by=16;
            rot = m270;
            AppendFULL(0,0);AppendFULL(1,0);
            AppendDL(2,0);AppendFULL(1,1);AppendFULL(2,1);
            type = RailTypes::split_L_U;
        }

        void LinkNodes(){ l->r=this;r->l=this;u->r=this;}
        void kill(){ l->r=nullptr;r->l=nullptr;u->r=nullptr;erase();}
        void killUpgraded(){

            if (l->r!=nullptr) l->r->kill();
            if (r->l!=nullptr) r->l->kill();
            if (u->r!=nullptr) u->r->kill();
        }

        DVerticalSideNode * l;
        DVerticalSideNode * r;
        DVerticalSideNode * u;
};


class splitUL_L: public DNetworkListElement
{
    public:
        splitUL_L(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = d270;
                      AppendFULL(0,0);AppendFULL(1,0);
                      AppendUR(0,1);AppendFULL(1,1);
                      AppendFULL(2,1);
                       type = RailTypes::split_UL_L;
                  }


        void LinkNodes(){ ul->dr=this;dr->ul=this;l->dr=this;}
        void kill(){ ul->dr=nullptr;dr->ul=nullptr;l->dr=nullptr;erase();}
        void killUpgraded(){

            if (ul->dr!=nullptr) ul->dr->kill();
            if (dr->ul!=nullptr) dr->ul->kill();
            if (l->dr!=nullptr) l->dr->kill();
        }
        DCornerNode *ul;
        DCornerNode *dr;
        DCornerNode *l;
};

class splitUL_U: public DNetworkListElement
{
    public:
        splitUL_U(){
                      ax = 0;
                      ay = 17;
                      bx = 1;
                      by = 19;
                      rot = m0;
                      AppendFULL(0,0);AppendDL(1,0);
                      AppendFULL(0,1);AppendFULL(1,1);
                      AppendFULL(1,2);
                       type = RailTypes::split_UL_U;
                  }


        void LinkNodes(){ ul->dr=this;dr->ul=this;u->dr=this;}
        void kill(){ ul->dr=nullptr;dr->ul=nullptr;u->dr=nullptr;erase();}
        void killUpgraded(){

            if (ul->dr!=nullptr) ul->dr->kill();
            if (dr->ul!=nullptr) dr->ul->kill();
            if (u->ul!=nullptr) u->dr->kill();
        }
        DCornerNode *ul;
        DCornerNode *dr;
        DCornerNode *u;
};


// ====================== END =====================


class DNetworkList
{
    public:
        DNetworkList();

        DNetworkListElement *first = nullptr;
        DNetworkListElement *last = nullptr;

        ~DNetworkList();
        void append(DNetworkListElement* newbie);
};


#endif // DNETWORKLIST_H
