#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_DL()
{//principal dl

    DCornerNode * NNode = &(CornerNodes[RailStart.i][RailStart.j]);


    if ( (NNode->dl==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {

            DMagnet* prevptr = nullptr;
            int i0 = RailStart.i-1;
            int j0 = RailStart.j+1;

            bool flag = true;
            do
                {


            DMagnet * newmagnet = new DMagnet();

            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;

            newmagnet->newelement = new class diagURDL();
            static_cast<class diagURDL*>(newmagnet->newelement)->ur=&(CornerNodes[i0+1][j0-1]);
            static_cast<class diagURDL*>(newmagnet->newelement)->dl=&(CornerNodes[i0][j0]);

            static_cast<class diagURDL*>(newmagnet->newelement)->i = i0;
            static_cast<class diagURDL*>(newmagnet->newelement)->j = j0-1;
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

            i0 = i0 - 1;
            j0 = j0 + 1;

        }
    while (flag);

     // check for connection with junctions....
    // JUNCTION UR_U
    if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].ur!=nullptr)&&(CornerNodes[i0][j0].ur->type==tight_UR_U))
        {

            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionUR_U();

            static_cast<class junctionUR_U*>(newmagnet->newelement)->dl=&(CornerNodes[i0][j0]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->ur=&(CornerNodes[i0+2][j0-2]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0+1][j0-3]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->i = i0;
            static_cast<class junctionUR_U*>(newmagnet->newelement)->j = j0-3;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].ur);

            /*if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
                allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);*/
            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }

    // JUNCTION UR_R
    if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].ur!=nullptr)&&(CornerNodes[i0][j0].ur->type==tight_UR_R))
        {

            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionUR_R();

            static_cast<class junctionUR_R*>(newmagnet->newelement)->dl=&(CornerNodes[i0][j0]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->ur=&(CornerNodes[i0+2][j0-2]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0+3][j0-2]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->i = i0;
            static_cast<class junctionUR_R*>(newmagnet->newelement)->j = j0-2;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].ur);

            /*if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
                allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);*/
            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }


        }


 // ===================== TIGHT DL_D + UPGRADE TO junction U_UR ================
    if ( (NNode->dl==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {

           if ( ((HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d!=nullptr) && (HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d->type==straightVert))||
               ((HorizontalSideNodes[RailStart.i-2][RailStart.j+2].u!=nullptr) && (HorizontalSideNodes[RailStart.i-2][RailStart.j+2].u->type==straightVert)))
            {

                   DMagnet * newmagnet = new DMagnet;
                   newmagnet->address.i=RailStart.i-2;
                   newmagnet->address.j=RailStart.j+3;
                   newmagnet->address.type=NetworkNodeTypes::horiz;
                   newmagnet->newelement = new class junctionU_UR();

                   static_cast<class junctionU_UR*>(newmagnet->newelement)->ur=NNode;
                   static_cast<class junctionU_UR*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+1]);;
                   static_cast<class junctionU_UR*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+3]);;

                   static_cast<class junctionU_UR*>(newmagnet->newelement)->i = RailStart.i-2;
                   static_cast<class junctionU_UR*>(newmagnet->newelement)->j = RailStart.j;
                   QList<DNetworkListElement*> allowed;
                   //allowed.append();

                   if ( (HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d->type==straightVert)  )
                       allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d);
                   if ( (HorizontalSideNodes[RailStart.i-2][RailStart.j+2].u!=nullptr)&&(HorizontalSideNodes[RailStart.i-2][RailStart.j+2].u->type==straightVert)  )
                       allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j+2].u);

                   newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
               }
           else
               {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i-2;
            newmagnet->address.j=RailStart.j+3;
            newmagnet->address.type=NetworkNodeTypes::horiz;
            newmagnet->newelement = new class tight_DL_D();
            static_cast<class tight_DL_D*>(newmagnet->newelement)->ur=NNode;
            static_cast<class tight_DL_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+3]);
            static_cast<class tight_DL_D*>(newmagnet->newelement)->i = RailStart.i-2;
            static_cast<class tight_DL_D*>(newmagnet->newelement)->j = RailStart.j;
newmagnet->valid = check_obstruction(newmagnet->newelement);
            magnets.append(newmagnet);
               }
        }



    // ======================= tight DL_L  + UPGRADE OT JUNCTION D_DR=================================
    if ( (NNode->dl==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {

            if ( ((VerticalSideNodes[RailStart.i-3][RailStart.j+1].r!=nullptr) && (VerticalSideNodes[RailStart.i-3][RailStart.j+1].r->type==straightHoriz))||
                 ((VerticalSideNodes[RailStart.i-2][RailStart.j+1].r!=nullptr) && (VerticalSideNodes[RailStart.i-2][RailStart.j+1].r->type==straightHoriz)) )
                {

                    int i0 = RailStart.i-3;
                    int j0 = RailStart.j+1;

                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=i0;
                    newmagnet->address.j=j0;
                    newmagnet->address.type=NetworkNodeTypes::vert;
                    newmagnet->newelement = new class junctionR_UR();

                    static_cast<class junctionR_UR*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0][j0]);;
                    static_cast<class junctionR_UR*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0+2][j0]);
                    static_cast<class junctionR_UR*>(newmagnet->newelement)->ur=&(CornerNodes[i0+2][j0-1]);

                    static_cast<class junctionR_UR*>(newmagnet->newelement)->i = i0;
                    static_cast<class junctionR_UR*>(newmagnet->newelement)->j = j0-1;

                    QList<DNetworkListElement*> allowed;

                    if ( (VerticalSideNodes[i0+1][j0].r!=nullptr)&&(VerticalSideNodes[i0+1][j0].r->type=straightHoriz))
                        allowed.append(VerticalSideNodes[i0+1][j0].r);
                    allowed.append(VerticalSideNodes[i0][j0].r);

                    newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                    //newmagnet->prev = prevptr;
                    magnets.append(newmagnet);

                }
            else
                {



            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i-3;
            newmagnet->address.j=RailStart.j+1;
            newmagnet->address.type=NetworkNodeTypes::vert;
            newmagnet->newelement = new class tight_DL_L();
            static_cast<class tight_DL_L*>(newmagnet->newelement)->ur=NNode;
            static_cast<class tight_DL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j+1]);
            static_cast<class tight_DL_L*>(newmagnet->newelement)->i = RailStart.i-3;
            static_cast<class tight_DL_L*>(newmagnet->newelement)->j = RailStart.j;
            newmagnet->valid = check_obstruction(newmagnet->newelement);
            magnets.append(newmagnet);
                }
        }



}
