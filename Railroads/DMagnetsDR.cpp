#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_DR()
{//principal dr

    DCornerNode * NNode = &(CornerNodes[RailStart.i][RailStart.j]);

if ( (NNode->dr==nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr) )
    {

                DMagnet* prevptr = nullptr;
                int i0 = RailStart.i+1;
                int j0 = RailStart.j+1;

                bool flag = true;
                do
                    {

                        DMagnet * newmagnet = new DMagnet();
                        newmagnet->address.i=i0;
                        newmagnet->address.j=j0;
                        newmagnet->address.type=NetworkNodeTypes::corner;
                        newmagnet->newelement = new class diagULDR();
                        static_cast<class diagULDR*>(newmagnet->newelement)->ul=&(CornerNodes[i0-1][j0-1]);
                        static_cast<class diagULDR*>(newmagnet->newelement)->dr=&(CornerNodes[i0][j0]);
                        static_cast<class diagULDR*>(newmagnet->newelement)->i = i0-1;
                        static_cast<class diagULDR*>(newmagnet->newelement)->j = j0-1;
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
                        j0 = j0 + 1;

                    }
                while (flag);

    }


// ================== tight dr r + upgrade to junction l_ul =============


if ( (NNode->dr==nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr) )
    {

        if (
                (( VerticalSideNodes[RailStart.i+3][RailStart.j+1].l!=nullptr)&&(VerticalSideNodes[RailStart.i+3][RailStart.j+1].l->type==straightHoriz)) ||
                (( VerticalSideNodes[RailStart.i+2][RailStart.j+1].l!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j+1].l->type==straightHoriz))
                )
            {

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i+3;
                newmagnet->address.j=RailStart.j+1;
                newmagnet->address.type=NetworkNodeTypes::vert;
                newmagnet->newelement = new class junctionL_UL();
                static_cast<class junctionL_UL*>(newmagnet->newelement)->ul=NNode;
                static_cast<class junctionL_UL*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j+1]);
                static_cast<class junctionL_UL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i+1][RailStart.j+1]);
                static_cast<class junctionL_UL*>(newmagnet->newelement)->i = RailStart.i;
                static_cast<class junctionL_UL*>(newmagnet->newelement)->j = RailStart.j;

                QList<DNetworkListElement*> allowed;

                if  ( (VerticalSideNodes[RailStart.i+1][RailStart.j+1].r!=nullptr)&&(VerticalSideNodes[RailStart.i+1][RailStart.j+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i+1][RailStart.j+1].r);
                if  ( (VerticalSideNodes[RailStart.i+2][RailStart.j+1].r!=nullptr)&&(VerticalSideNodes[RailStart.i+2][RailStart.j+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i+2][RailStart.j+1].r);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

                magnets.append(newmagnet);
            }

        else
            {
        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i+3;
        newmagnet->address.j=RailStart.j+1;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class tight_DR_R();
        static_cast<class tight_DR_R*>(newmagnet->newelement)->ul=NNode;
        static_cast<class tight_DR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j+1]);
        static_cast<class tight_DR_R*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class tight_DR_R*>(newmagnet->newelement)->j = RailStart.j;
newmagnet->valid = check_obstruction(newmagnet->newelement);
        magnets.append(newmagnet);
            }
    }


//===============  tight dr_d + upgrade to junction u ul ==========
if ( (NNode->dr==nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr) )
    {
       // upgraded to junction
      if  (  ((HorizontalSideNodes[RailStart.i+1][RailStart.j+2].d!=nullptr) && (HorizontalSideNodes[RailStart.i+1][RailStart.j+2].d->type==straightVert))||
             ((HorizontalSideNodes[RailStart.i+1][RailStart.j+2].u!=nullptr) && (HorizontalSideNodes[RailStart.i+1][RailStart.j+2].u->type==straightVert)))

              { DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i+1;
                newmagnet->address.j=RailStart.j+3;
                newmagnet->address.type=NetworkNodeTypes::horiz;
                newmagnet->newelement = new class junctionU_UL;
                static_cast<class junctionU_UL*>(newmagnet->newelement)->ul=NNode;
                static_cast<class junctionU_UL*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i+1][RailStart.j+1]);
                static_cast<class junctionU_UL*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i+1][RailStart.j+3]);
                static_cast<class junctionU_UL*>(newmagnet->newelement)->i = RailStart.i;
                static_cast<class junctionU_UL*>(newmagnet->newelement)->j = RailStart.j;

                QList <DNetworkListElement*> allowed;
                if  ((HorizontalSideNodes[RailStart.i+1][RailStart.j+2].d!=nullptr) && (HorizontalSideNodes[RailStart.i+1][RailStart.j+2].d->type==straightVert))
                        allowed.append(HorizontalSideNodes[RailStart.i+1][RailStart.j+2].d);
                if  ((HorizontalSideNodes[RailStart.i+1][RailStart.j+2].u!=nullptr) && (HorizontalSideNodes[RailStart.i+1][RailStart.j+2].u->type==straightVert))
                        allowed.append(HorizontalSideNodes[RailStart.i+1][RailStart.j+2].u);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }


        else
        {
               // =========== tight dr_d ========
        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i+1;
        newmagnet->address.j=RailStart.j+3;
        newmagnet->address.type=NetworkNodeTypes::horiz;
        newmagnet->newelement = new class tight_DR_D();
        static_cast<class tight_DR_D*>(newmagnet->newelement)->ul=NNode;
        static_cast<class tight_DR_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i+1][RailStart.j+3]);
        static_cast<class tight_DR_D*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class tight_DR_D*>(newmagnet->newelement)->j = RailStart.j;
        newmagnet->valid = check_obstruction(newmagnet->newelement);
        magnets.append(newmagnet);
        }

}




}
