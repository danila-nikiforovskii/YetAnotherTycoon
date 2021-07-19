#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_UL()
{
// principal ul
DCornerNode * NNode = &(CornerNodes[RailStart.i][RailStart.j]);

if ( (NNode->ul==nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr) )
    {
        DMagnet* prevptr = nullptr;
        int i0 = RailStart.i-1;
        int j0 = RailStart.j-1;

        bool flag = true;
        do
            {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=i0;
        newmagnet->address.j=j0;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class diagULDR();
        static_cast<class diagULDR*>(newmagnet->newelement)->dr=&(CornerNodes[i0+1][j0+1]);
        static_cast<class diagULDR*>(newmagnet->newelement)->ul=&(CornerNodes[i0][j0]);
        static_cast<class diagULDR*>(newmagnet->newelement)->i = i0;
        static_cast<class diagULDR*>(newmagnet->newelement)->j = j0;
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
        j0 = j0 - 1;

    }
while (flag);
    }
//=================     TIGHT UL_L  + UPGRADE TO JUNCTION R DR  ====

if ( (NNode->ul==nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr) )
    {

        if ( ((VerticalSideNodes[RailStart.i-3][RailStart.j-2].r!=nullptr)&&(VerticalSideNodes[RailStart.i-3][RailStart.j-2].r->type==straightHoriz))||
             ((VerticalSideNodes[RailStart.i-2][RailStart.j-2].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j-2].r->type==straightHoriz)))
            {
                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-3;
                newmagnet->address.j=RailStart.j-2;
                newmagnet->address.type=NetworkNodeTypes::vert;
                newmagnet->newelement = new class junctionR_DR();
                static_cast<class junctionR_DR*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j-2]);
                static_cast<class junctionR_DR*>(newmagnet->newelement)->dr=NNode;
                static_cast<class junctionR_DR*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i-1][RailStart.j-2]);
                static_cast<class junctionR_DR*>(newmagnet->newelement)->i = RailStart.i-3;
                static_cast<class junctionR_DR*>(newmagnet->newelement)->j = RailStart.j-2;

                QList<DNetworkListElement*> allowed;
                if ((VerticalSideNodes[RailStart.i-2][RailStart.j-2].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j-2].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j-2].r);

                allowed.append(VerticalSideNodes[RailStart.i-3][RailStart.j-2].r);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }
        else{

        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j-2;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class tight_UL_L();
        static_cast<class tight_UL_L*>(newmagnet->newelement)->dr=NNode;
        static_cast<class tight_UL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j-2]);
        static_cast<class tight_UL_L*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class tight_UL_L*>(newmagnet->newelement)->j = RailStart.j-2;
        newmagnet->valid = check_obstruction(newmagnet->newelement);
        magnets.append(newmagnet);
            }
    }

//============ upgrade straight diag UL to junction UL_L

if ((NNode->ul!=nullptr) &&(NNode->ur==nullptr)&&(NNode->dl==nullptr) && (NNode->ul->type==diagULDR) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j-2;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class junctionUL_L();

        static_cast<class junctionUL_L*>(newmagnet->newelement)->dr=NNode;
        static_cast<class junctionUL_L*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-2][RailStart.j-2]);
        static_cast<class junctionUL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j-2]);
        static_cast<class junctionUL_L*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class junctionUL_L*>(newmagnet->newelement)->j = RailStart.j-2;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->ul);

        if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type==diagULDR))
            allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);

        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);
    }


//============ upgrade straight diag UL to junction UL_U

if ((NNode->ul!=nullptr) &&(NNode->ur==nullptr)&&(NNode->dl==nullptr) && (NNode->ul->type==diagULDR) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i-2;
        newmagnet->address.j=RailStart.j-3;
        newmagnet->address.type=NetworkNodeTypes::horiz;
        newmagnet->newelement = new class junctionUL_U();

        static_cast<class junctionUL_U*>(newmagnet->newelement)->dr=NNode;
        static_cast<class junctionUL_U*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-2][RailStart.j-2]);
        static_cast<class junctionUL_U*>(newmagnet->newelement)->u= &(HorizontalSideNodes[RailStart.i-2][RailStart.j-3]);
        static_cast<class junctionUL_U*>(newmagnet->newelement)->i = RailStart.i-2;
        static_cast<class junctionUL_U*>(newmagnet->newelement)->j = RailStart.j-3;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->ul);

        if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type==diagULDR))
            allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);

        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);
    }


// upgrade tight UL_L to junction UL_L
if ((NNode->ul!=nullptr) &&(NNode->ur==nullptr)&&(NNode->dl==nullptr) && (NNode->ul->type==tight_UL_L) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i-2;
        newmagnet->address.j=RailStart.j-2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class junctionUL_L();

        static_cast<class junctionUL_L*>(newmagnet->newelement)->dr=NNode;
        static_cast<class junctionUL_L*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-2][RailStart.j-2]);
        static_cast<class junctionUL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j-2]);
        static_cast<class junctionUL_L*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class junctionUL_L*>(newmagnet->newelement)->j = RailStart.j-2;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->ul);

        if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
            allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);

        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);
    }

// upgrade tight UL_U to junction UL_U
if ((NNode->ul!=nullptr) &&(NNode->ur==nullptr)&&(NNode->dl==nullptr) && (NNode->ul->type==tight_UL_U) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i-2;
        newmagnet->address.j=RailStart.j-2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class junctionUL_U();

        static_cast<class junctionUL_U*>(newmagnet->newelement)->dr=NNode;
        static_cast<class junctionUL_U*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-2][RailStart.j-2]);
        static_cast<class junctionUL_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i-2][RailStart.j-3]);
        static_cast<class junctionUL_U*>(newmagnet->newelement)->i = RailStart.i-2;
        static_cast<class junctionUL_U*>(newmagnet->newelement)->j = RailStart.j-3;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->ul);

        if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
            allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);

        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);
    }



// =================== TIGHT UL_U + UPGRADED TO JUNCTION D_DR ==========
if ( (NNode->ul==nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr) )
    {

        if  ( ((HorizontalSideNodes[RailStart.i-2][RailStart.j-3].d!=nullptr) && (HorizontalSideNodes[RailStart.i-2][RailStart.j-3].d->type==RailTypes::straightVert))||
              ((HorizontalSideNodes[RailStart.i-2][RailStart.j-2].d!=nullptr) && (HorizontalSideNodes[RailStart.i-2][RailStart.j-2].d->type==RailTypes::straightVert))
              )
            {

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-2;
                newmagnet->address.j=RailStart.j-3;
                newmagnet->address.type=NetworkNodeTypes::horiz;
                newmagnet->newelement = new class junctionD_DR();


                static_cast<class junctionD_DR*>(newmagnet->newelement)->dr=NNode;
                static_cast<class junctionD_DR*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i-2][RailStart.j-3]);
                static_cast<class junctionD_DR*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i-2][RailStart.j-1]);
                static_cast<class junctionD_DR*>(newmagnet->newelement)->i = RailStart.i-2;
                static_cast<class junctionD_DR*>(newmagnet->newelement)->j = RailStart.j-3;

                QList<DNetworkListElement*> allowed;
                if ((HorizontalSideNodes[RailStart.i-2][RailStart.j-3].d!=nullptr) && (HorizontalSideNodes[RailStart.i-2][RailStart.j-3].d->type==RailTypes::straightVert))
                    allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j-3].d);
                if ((HorizontalSideNodes[RailStart.i-2][RailStart.j-2].d!=nullptr) && (HorizontalSideNodes[RailStart.i-2][RailStart.j-2].d->type==RailTypes::straightVert))
                    allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j-2].d);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }
        else
            {
                // ============  tight UL_U ==========
        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-2;
        newmagnet->address.j=RailStart.j-3;
        newmagnet->address.type=NetworkNodeTypes::horiz;
        newmagnet->newelement = new class tight_UL_U();
        static_cast<class tight_UL_U*>(newmagnet->newelement)->dr=NNode;
        static_cast<class tight_UL_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i-2][RailStart.j-3]);
        static_cast<class tight_UL_U*>(newmagnet->newelement)->i = RailStart.i-2;
        static_cast<class tight_UL_U*>(newmagnet->newelement)->j = RailStart.j-3;
newmagnet->valid = check_obstruction(newmagnet->newelement);
        magnets.append(newmagnet);
        }

    }



}
