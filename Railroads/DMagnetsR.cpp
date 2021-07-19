#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_R()
{
    DVerticalSideNode * NNode = &(VerticalSideNodes[RailStart.i][RailStart.j]);

    // principal direction to the right....
    if (NNode->r==nullptr)
        {
            DMagnet* prevptr = nullptr;
            int i0 = RailStart.i+1;
            int j0 = RailStart.j;

            bool flag = true;
            do
                {
                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=i0;
                    newmagnet->address.j=j0;
                    newmagnet->address.type=NetworkNodeTypes::vert;
                    newmagnet->newelement = new class straightHoriz();
                    static_cast<class straightHoriz*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0-1][j0]);
                    static_cast<class straightHoriz*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0][j0]);
                    static_cast<class straightHoriz*>(newmagnet->newelement)->i=i0-1;
                    static_cast<class straightHoriz*>(newmagnet->newelement)->j=j0;
                    newmagnet->valid = check_obstruction(newmagnet->newelement);
                    newmagnet->prev = prevptr;

                    flag = newmagnet->valid;
                    if (flag)
                        {
                            magnets.append(newmagnet);
                            prevptr = (magnets.last());
                        }
                    else
                        {
                            delete newmagnet;
                        }

                    i0 = i0 + 1;

                }
            while (flag);

           // =======  check for connections with the junctions ============

            //===========junction L_UL
           if ( (VerticalSideNodes[i0][j0].l!=nullptr)&&(VerticalSideNodes[i0][j0].l->type==RailTypes::tight_DR_R))
               {

                   DMagnet * newmagnet = new DMagnet;
                   newmagnet->address.i=i0;
                   newmagnet->address.j=j0;
                   newmagnet->address.type=NetworkNodeTypes::vert;
                   newmagnet->newelement = new class junctionL_UL();

                   static_cast<class junctionL_UL*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0][j0]);;
                   static_cast<class junctionL_UL*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0-2][j0]);
                   static_cast<class junctionL_UL*>(newmagnet->newelement)->ul=&(CornerNodes[i0-3][j0-1]);

                   static_cast<class junctionL_UL*>(newmagnet->newelement)->i = i0-3;
                   static_cast<class junctionL_UL*>(newmagnet->newelement)->j = j0-1;

                   QList<DNetworkListElement*> allowed;
                   allowed.append(VerticalSideNodes[i0][j0].l);

                   newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                   newmagnet->prev = prevptr;

                   flag = newmagnet->valid;
                   if (flag)
                       {
                           magnets.append(newmagnet);
                           prevptr = (magnets.last());
                       }
                   //if (newmagnet->valid)
                   //magnets.append(newmagnet);
               }

           //===========junction L_DL
          if ( (VerticalSideNodes[i0][j0].l!=nullptr)&&(VerticalSideNodes[i0][j0].l->type==RailTypes::tight_UR_R))
              {

                  DMagnet * newmagnet = new DMagnet;
                  newmagnet->address.i=i0;
                  newmagnet->address.j=j0;
                  newmagnet->address.type=NetworkNodeTypes::vert;
                  newmagnet->newelement = new class junctionL_DL();

                  static_cast<class junctionL_DL*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0][j0]);;
                  static_cast<class junctionL_DL*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0-2][j0]);
                  static_cast<class junctionL_DL*>(newmagnet->newelement)->dl=&(CornerNodes[i0-3][j0+2]);

                  static_cast<class junctionL_DL*>(newmagnet->newelement)->i = i0-3;
                  static_cast<class junctionL_DL*>(newmagnet->newelement)->j = j0;

                  QList<DNetworkListElement*> allowed;
                  allowed.append(VerticalSideNodes[i0][j0].l);

                  newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                  newmagnet->prev = prevptr;

                  flag = newmagnet->valid;
                  if (flag)
                      {
                          magnets.append(newmagnet);
                          prevptr = (magnets.last());
                      }
                  //if (newmagnet->valid)
                  //magnets.append(newmagnet);
              }


        }


    // =================== upgrade straight to junction r_UR ==========

    if ((NNode->r!=nullptr)&&(NNode->r->type==straightHoriz))
        {
            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j-1;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionR_UR();
            static_cast<class junctionR_UR*>(newmagnet->newelement)->l=NNode;
            static_cast<class junctionR_UR*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+3][RailStart.j-1]);
            static_cast<class junctionR_UR*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+2][RailStart.j]);
            static_cast<class junctionR_UR*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionR_UR*>(newmagnet->newelement)->j = RailStart.j-1;



            QList<DNetworkListElement*> allowed;
            if ((VerticalSideNodes[RailStart.i+2][RailStart.j].l!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j].l->type==straightHoriz))
                allowed.append(VerticalSideNodes[RailStart.i+2][RailStart.j].l);
            allowed.append(VerticalSideNodes[RailStart.i][RailStart.j].r);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

            magnets.append(newmagnet);
        }

    // ================ upgrade STraight to junction R_DR
    if ((NNode->r!=nullptr)&&(NNode->r->type==straightHoriz))
        {
            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j+2;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionR_DR();
            static_cast<class junctionR_DR*>(newmagnet->newelement)->l=NNode;
            static_cast<class junctionR_DR*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+3][RailStart.j+2]);
            static_cast<class junctionR_DR*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+2][RailStart.j]);
            static_cast<class junctionR_DR*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionR_DR*>(newmagnet->newelement)->j = RailStart.j;


            QList<DNetworkListElement*> allowed;
            if ((VerticalSideNodes[RailStart.i+2][RailStart.j].l!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j].l->type==straightHoriz))
                allowed.append(VerticalSideNodes[RailStart.i+2][RailStart.j].l);
            allowed.append(VerticalSideNodes[RailStart.i][RailStart.j].r);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

            magnets.append(newmagnet);
        }

    // ================= tight R_UR = tight DL_L + upgrader to junction dl_l
    if (NNode->r==nullptr)
        { if  ( (( CornerNodes[RailStart.i+3][RailStart.j-1].dl!=nullptr)&&(CornerNodes[RailStart.i+3][RailStart.j-1].dl->type==diagDLUR))||
                (( CornerNodes[RailStart.i+2][RailStart.j].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j].dl->type==diagDLUR)) )
              {

                  DMagnet * newmagnet = new DMagnet;
                  newmagnet->address.i=RailStart.i+3;
                  newmagnet->address.j=RailStart.j-1;
                  newmagnet->address.type=NetworkNodeTypes::corner;
                  newmagnet->newelement = new class junctionDL_L();

                  static_cast<class junctionDL_L*>(newmagnet->newelement)->l=NNode;
                  static_cast<class junctionDL_L*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+3][RailStart.j-1]);
                  static_cast<class junctionDL_L*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i+1][RailStart.j+1]);
                  static_cast<class junctionDL_L*>(newmagnet->newelement)->i = RailStart.i;
                  static_cast<class junctionDL_L*>(newmagnet->newelement)->j = RailStart.j-1;

                  QList<DNetworkListElement*> allowed;

                  if ((CornerNodes[RailStart.i+3][RailStart.j-1].dl!=nullptr)&&(CornerNodes[RailStart.i+3][RailStart.j-1].dl->type==diagDLUR))
                      allowed.append(CornerNodes[RailStart.i+3][RailStart.j-1].dl);

                  if ((CornerNodes[RailStart.i+2][RailStart.j].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j].dl->type==diagDLUR))
                      allowed.append(CornerNodes[RailStart.i+2][RailStart.j].dl);

                  newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                  magnets.append(newmagnet);

              }
                      else {
            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j-1;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class tight_DL_L();
            static_cast<class tight_DL_L*>(newmagnet->newelement)->l=NNode;
            static_cast<class tight_DL_L*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+3][RailStart.j-1]);
            static_cast<class tight_DL_L*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class tight_DL_L*>(newmagnet->newelement)->j = RailStart.j-1;
            newmagnet->valid = check_obstruction(newmagnet->newelement);
            magnets.append(newmagnet);
                }
        }



    // =================== upgrade tight R UR to junction r_UR ==========

    if ((NNode->r!=nullptr)&&(NNode->r->type==tight_DL_L))
        {
            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+2;
            newmagnet->address.j=RailStart.j;
            newmagnet->address.type=NetworkNodeTypes::vert;
            newmagnet->newelement = new class junctionR_UR();
            static_cast<class junctionR_UR*>(newmagnet->newelement)->l=NNode;
            static_cast<class junctionR_UR*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+3][RailStart.j-1]);
            static_cast<class junctionR_UR*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+2][RailStart.j]);
            static_cast<class junctionR_UR*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionR_UR*>(newmagnet->newelement)->j = RailStart.j-1;

            QList<DNetworkListElement*> allowed;
            if ((VerticalSideNodes[RailStart.i+2][RailStart.j].l!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j].l->type==straightHoriz))
                allowed.append(VerticalSideNodes[RailStart.i+2][RailStart.j].l);
            allowed.append(VerticalSideNodes[RailStart.i][RailStart.j].r);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

            magnets.append(newmagnet);
        }


    // ================= tight R_DR = tight UL_L + upgrade to junction UL L
    if (NNode->r==nullptr)
        {
            if  ( (( CornerNodes[RailStart.i+3][RailStart.j+2].ul!=nullptr)&&(CornerNodes[RailStart.i+3][RailStart.j+2].ul->type==diagULDR))||
                  (( CornerNodes[RailStart.i+2][RailStart.j+1].ul!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j+1].ul->type==diagULDR)) )
                {

                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+3;
                    newmagnet->address.j=RailStart.j+2;
                    newmagnet->address.type=NetworkNodeTypes::corner;
                    newmagnet->newelement = new class junctionUL_L();

                    static_cast<class junctionUL_L*>(newmagnet->newelement)->l=NNode;
                    static_cast<class junctionUL_L*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i+1][RailStart.j]);
                    static_cast<class junctionUL_L*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+3][RailStart.j+2]);
                    static_cast<class junctionUL_L*>(newmagnet->newelement)->i = RailStart.i;
                    static_cast<class junctionUL_L*>(newmagnet->newelement)->j = RailStart.j;

                    QList<DNetworkListElement*> allowed;

                    if ((CornerNodes[RailStart.i+3][RailStart.j+2].ul!=nullptr)&&(CornerNodes[RailStart.i+3][RailStart.j+2].ul->type==diagULDR))
                        allowed.append(CornerNodes[RailStart.i+3][RailStart.j+2].ul);

                    if ((CornerNodes[RailStart.i+2][RailStart.j+1].ul!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j+1].ul->type==diagULDR))
                        allowed.append(CornerNodes[RailStart.i+2][RailStart.j+1].ul);

                    newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);

                }
                        else {





            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j+2;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class tight_UL_L();
            static_cast<class tight_UL_L*>(newmagnet->newelement)->l=NNode;
            static_cast<class tight_UL_L*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+3][RailStart.j+2]);
            static_cast<class tight_UL_L*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class tight_UL_L*>(newmagnet->newelement)->j = RailStart.j;
            newmagnet->valid = check_obstruction(newmagnet->newelement);
            magnets.append(newmagnet);
            }
        }

    // ================ upgrade tight R_DR to junction R_DR
    if ((NNode->r!=nullptr)&&(NNode->r->type==tight_UL_L))
        {
            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+2;
            newmagnet->address.j=RailStart.j;
            newmagnet->address.type=NetworkNodeTypes::vert;
            newmagnet->newelement = new class junctionR_DR();
            static_cast<class junctionR_DR*>(newmagnet->newelement)->l=NNode;
            static_cast<class junctionR_DR*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+3][RailStart.j+2]);
            static_cast<class junctionR_DR*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+2][RailStart.j]);
            static_cast<class junctionR_DR*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionR_DR*>(newmagnet->newelement)->j = RailStart.j;


            QList<DNetworkListElement*> allowed;
            if ((VerticalSideNodes[RailStart.i+2][RailStart.j].l!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j].l->type==straightHoriz))
                allowed.append(VerticalSideNodes[RailStart.i+2][RailStart.j].l);
            allowed.append(VerticalSideNodes[RailStart.i][RailStart.j].r);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

            magnets.append(newmagnet);
        }



}
