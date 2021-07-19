#ifndef DNETWORKLIST_H
#define DNETWORKLIST_H

//the list of the fragments

#include <dnetworknode.h>
#include <QDebug>
enum RailTypes
{
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
        RailTypes type;
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
                       };
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
                        };
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
                  };
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
                  };
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
                };
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
                };
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
                    };
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
                    };
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
                    };
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
                    };
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
                };
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

                };
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
                    };
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
                      };

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

class junctionUR_U: DNetworkListElement
{
       junctionUR_U();
      DCornerNode *dl;
      DCornerNode *ur;
      DHorizontalSideNode *u;
};

class junctionUR_R: DNetworkListElement
{
       junctionUR_R();
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

class junctionDR_R:DNetworkListElement
{
        junctionDR_R();
        DCornerNode *ul;
        DCornerNode *dr;
        DVerticalSideNode *r;
};

class junctionDR_D:DNetworkListElement
{
    junctionDR_D();
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

class junctionDL_D:DNetworkListElement
{
        junctionDL_D();
        DCornerNode *ur;
        DCornerNode *dl;
        DHorizontalSideNode *d;
};

class junctionDL_L:DNetworkListElement
{
        junctionDL_L();
        DCornerNode *ur;
        DCornerNode *dl;
        DVerticalSideNode *l;
};

class junctionL_DL:DNetworkListElement
{
        junctionL_DL();
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

class junctionUL_L:DNetworkListElement
{
    junctionUL_L();
    DCornerNode *dr;
    DCornerNode *ul;
    DVerticalSideNode*l;
};

class junctionUL_U:DNetworkListElement
{
    junctionUL_U();
    DCornerNode *dr;
    DCornerNode *ul;
    DHorizontalSideNode *u;
};

// ====================== SPLITS =================


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
