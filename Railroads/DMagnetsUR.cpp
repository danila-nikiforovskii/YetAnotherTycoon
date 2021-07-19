#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_UR()
{

DCornerNode * NNode = &(CornerNodes[RailStart.i][RailStart.j]);
    //principal ur
    if ( (NNode->ur==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {

            DMagnet* prevptr = nullptr;
            int i0 = RailStart.i+1;
            int j0 = RailStart.j-1;

            bool flag = true;
            do
                {

            DMagnet * newmagnet = new DMagnet();

            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;

            newmagnet->newelement = new class diagURDL();
            static_cast<class diagURDL*>(newmagnet->newelement)->dl=&(CornerNodes[i0-1][j0+1]);
            static_cast<class diagURDL*>(newmagnet->newelement)->ur=&(CornerNodes[i0][j0]);

            static_cast<class diagURDL*>(newmagnet->newelement)->i = i0-1;
            static_cast<class diagURDL*>(newmagnet->newelement)->j = j0;

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
            j0 = j0 - 1;

        }
    while (flag);
        }


    // upgrade straight urdl to junction ur_u

    if ( (NNode->ur!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) && (NNode->ur->type==diagURDL))
        {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+1;
            newmagnet->address.j=RailStart.j-3;
            newmagnet->address.type=NetworkNodeTypes::horiz;
            newmagnet->newelement = new class junctionUR_U();

            static_cast<class junctionUR_U*>(newmagnet->newelement)->dl=NNode;
            static_cast<class junctionUR_U*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i+1][RailStart.j-3]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionUR_U*>(newmagnet->newelement)->j = RailStart.j-3;

            QList<DNetworkListElement*> allowed;
            allowed.append(NNode->ur);

            if ((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }



    // upgrade straight urdl to junction ur_r

    if ( (NNode->ur!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) && (NNode->ur->type==diagURDL))
        {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j-2;
            newmagnet->address.type=NetworkNodeTypes::vert;
            newmagnet->newelement = new class junctionUR_R();

            static_cast<class junctionUR_R*>(newmagnet->newelement)->dl=NNode;
            static_cast<class junctionUR_R*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j-2]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionUR_R*>(newmagnet->newelement)->j = RailStart.j-2;

            QList<DNetworkListElement*> allowed;
            allowed.append(NNode->ur);

            if ((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }






    // =========  upgrade ur_u to junction UR U ==========

    if ( (NNode->ur!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) && (NNode->ur->type==tight_UR_U))
        {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+2;
            newmagnet->address.j=RailStart.j-2;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionUR_U();

            static_cast<class junctionUR_U*>(newmagnet->newelement)->dl=NNode;
            static_cast<class junctionUR_U*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i+1][RailStart.j-3]);
            static_cast<class junctionUR_U*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionUR_U*>(newmagnet->newelement)->j = RailStart.j-3;

            QList<DNetworkListElement*> allowed;
            allowed.append(NNode->ur);

            if ((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }


    // =========  upgrade ur_r to junction UR r ==========

    if ( (NNode->ur!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) && (NNode->ur->type==tight_UR_R))
        {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+2;
            newmagnet->address.j=RailStart.j-2;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionUR_R();

            static_cast<class junctionUR_R*>(newmagnet->newelement)->dl=NNode;
            static_cast<class junctionUR_R*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j-2]);
            static_cast<class junctionUR_R*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class junctionUR_R*>(newmagnet->newelement)->j = RailStart.j-2;

            QList<DNetworkListElement*> allowed;
            allowed.append(NNode->ur);

            if ((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }




 //============== TIGHT UR R + UPGRADE TO JUNCTION R DR ================
    if ( (NNode->ur==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {
            if (( (VerticalSideNodes[RailStart.i+3][RailStart.j-2].l!=nullptr)&& (VerticalSideNodes[RailStart.i+3][RailStart.j-2].l->type==RailTypes::straightHoriz) )||
                ((VerticalSideNodes[RailStart.i+2][RailStart.j-2].l!=nullptr)&& (VerticalSideNodes[RailStart.i+2][RailStart.j-2].l->type==RailTypes::straightHoriz) ) )
                {
                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+3;
                    newmagnet->address.j=RailStart.j-2;
                    newmagnet->address.type=NetworkNodeTypes::vert;
                    newmagnet->newelement = new class junctionL_DL();

                    static_cast<class junctionL_DL*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j-2]);;
                    static_cast<class junctionL_DL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i+1][RailStart.j-2]);
                    static_cast<class junctionL_DL*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i][RailStart.j]);

                    static_cast<class junctionL_DL*>(newmagnet->newelement)->i = RailStart.i;
                    static_cast<class junctionL_DL*>(newmagnet->newelement)->j = RailStart.j-2;

                    QList<DNetworkListElement*> allowed;
                    if ( (VerticalSideNodes[RailStart.i+3][RailStart.j-2].l!=nullptr)&&(VerticalSideNodes[RailStart.i+3][RailStart.j-2].l->type==straightHoriz) )
                            allowed.append(VerticalSideNodes[RailStart.i+3][RailStart.j-2].l);

                    if ( (VerticalSideNodes[RailStart.i+2][RailStart.j-2].l!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j-2].l->type==straightHoriz) )
                            allowed.append(VerticalSideNodes[RailStart.i+2][RailStart.j-2].l);

                    newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);

                }
            else {



            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j-2;
            newmagnet->address.type=NetworkNodeTypes::vert;
            newmagnet->newelement = new class tight_UR_R();
            static_cast<class tight_UR_R*>(newmagnet->newelement)->dl=NNode;
            static_cast<class tight_UR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j-2]);
            static_cast<class tight_UR_R*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class tight_UR_R*>(newmagnet->newelement)->j = RailStart.j-2;
            newmagnet->valid = check_obstruction(newmagnet->newelement);
            magnets.append(newmagnet);
                }
        }





//============== TIGHT UR U + UPGRADE TO JUNCTION D_DL ================
    if ( (NNode->ur==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {

            if ( (HorizontalSideNodes[RailStart.i+1][RailStart.j-3].d!=nullptr)&& (HorizontalSideNodes[RailStart.i+1][RailStart.j-3].d->type==RailTypes::straightVert) )

            {
                //upgrade to junction d _ dl
                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+1;
                    newmagnet->address.j=RailStart.j-3;
                    newmagnet->address.type=NetworkNodeTypes::horiz;
                    newmagnet->newelement = new class junctionD_DL();

                    static_cast<class junctionD_DL*>(newmagnet->newelement)->dl=NNode;
                    static_cast<class junctionD_DL*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i+1][RailStart.j-3]);;
                    static_cast<class junctionD_DL*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i+1][RailStart.j-1]);

                    static_cast<class junctionD_DL*>(newmagnet->newelement)->i = RailStart.i;
                    static_cast<class junctionD_DL*>(newmagnet->newelement)->j = RailStart.j-3;
                    QList<DNetworkListElement*> allowed;
                    allowed.append(HorizontalSideNodes[RailStart.i+1][RailStart.j-3].d);

                    if ((HorizontalSideNodes[RailStart.i+1][RailStart.j-1].u!=nullptr)&&(HorizontalSideNodes[RailStart.i+1][RailStart.j-1].u->type==straightVert))
                        allowed.append(HorizontalSideNodes[RailStart.i+1][RailStart.j-1].u);

                    if ( (HorizontalSideNodes[RailStart.i][RailStart.j-2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i][RailStart.j-2].d->type==straightVert)  )
                        allowed.append(HorizontalSideNodes[RailStart.i][RailStart.j-2].d);

                    newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

                    magnets.append(newmagnet);

            }
            else
            {
                //tight ur u

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+1;
            newmagnet->address.j=RailStart.j-3;
            newmagnet->address.type=NetworkNodeTypes::horiz;
            newmagnet->newelement = new class tight_UR_U();
            static_cast<class tight_UR_U*>(newmagnet->newelement)->dl=NNode;
            static_cast<class tight_UR_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i+1][RailStart.j-3]);
            static_cast<class tight_UR_U*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class tight_UR_U*>(newmagnet->newelement)->j = RailStart.j-3;
newmagnet->valid = check_obstruction(newmagnet->newelement);
            magnets.append(newmagnet);
        }
        }



}
