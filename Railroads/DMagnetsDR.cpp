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


                //===== check for connection with junctions ===========


                //junction UL_L



                if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].ul!=nullptr)&&(CornerNodes[i0][j0].ul->type==tight_UL_L))
                    {

                        DMagnet * newmagnet = new DMagnet();
                        newmagnet->address.i=i0;
                        newmagnet->address.j=j0;
                        newmagnet->address.type=NetworkNodeTypes::corner;
                        newmagnet->newelement = new class junctionUL_L();

                        static_cast<class junctionUL_L*>(newmagnet->newelement)->dr=&(CornerNodes[i0][j0]);
                        static_cast<class junctionUL_L*>(newmagnet->newelement)->ul=&(CornerNodes[i0-2][j0-2]);
                        static_cast<class junctionUL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0-3][j0-2]);
                        static_cast<class junctionUL_L*>(newmagnet->newelement)->i = i0-3;
                        static_cast<class junctionUL_L*>(newmagnet->newelement)->j = j0-2;

                        QList<DNetworkListElement*> allowed;
                        allowed.append(CornerNodes[i0][j0].ul);

                        /*if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
                            allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);*/
                        newmagnet->prev = prevptr;
                        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                        magnets.append(newmagnet);
                    }

                //junction UL_U

                if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].ul!=nullptr)&&(CornerNodes[i0][j0].ul->type==tight_UL_U))
                    {

                        DMagnet * newmagnet = new DMagnet();
                        newmagnet->address.i=i0;
                        newmagnet->address.j=j0;
                        newmagnet->address.type=NetworkNodeTypes::corner;
                        newmagnet->newelement = new class junctionUL_U();

                        static_cast<class junctionUL_U*>(newmagnet->newelement)->dr=&(CornerNodes[i0][j0]);
                        static_cast<class junctionUL_U*>(newmagnet->newelement)->ul=&(CornerNodes[i0-2][j0-2]);
                        static_cast<class junctionUL_U*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0-2][j0-3]);
                        static_cast<class junctionUL_U*>(newmagnet->newelement)->i = i0-2;
                        static_cast<class junctionUL_U*>(newmagnet->newelement)->j = j0-3;

                        QList<DNetworkListElement*> allowed;
                        allowed.append(CornerNodes[i0][j0].ul);

                        /*if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
                            allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);*/
                        newmagnet->prev = prevptr;
                        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                        magnets.append(newmagnet);
                    }

    }


// ==================== upgrade DRUL to junction DR_R
if ( (NNode->dr!=nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr)&&(NNode->dr->type==diagDRUL) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i+3;
        newmagnet->address.j=RailStart.j+1;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class junctionDR_R();

        static_cast<class junctionDR_R*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+2]);
        static_cast<class junctionDR_R*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j]);
        static_cast<class junctionDR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j+1]);
        static_cast<class junctionDR_R*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class junctionDR_R*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(CornerNodes[RailStart.i][RailStart.j].dr);

        if ((CornerNodes[RailStart.i+1][RailStart.j+1].dr!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j+1].dr->type==diagDRUL))
            allowed.append(CornerNodes[RailStart.i+1][RailStart.j+1].dr);

        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);

    }

// ==================== upgrade DRUL to junction DR_D
if ( (NNode->dr!=nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr)&&(NNode->dr->type==diagDRUL) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i+1;
        newmagnet->address.j=RailStart.j+3;
        newmagnet->address.type=NetworkNodeTypes::horiz;
        newmagnet->newelement = new class junctionDR_D();

        static_cast<class junctionDR_D*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+2]);
        static_cast<class junctionDR_D*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j]);
        static_cast<class junctionDR_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i+1][RailStart.j+3]);
        static_cast<class junctionDR_D*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class junctionDR_D*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(CornerNodes[RailStart.i][RailStart.j].dr);

        if ((CornerNodes[RailStart.i+1][RailStart.j+1].dr!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j+1].dr->type==diagDRUL))
            allowed.append(CornerNodes[RailStart.i+1][RailStart.j+1].dr);

        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);

    }

// ==================== upgrade DRUL to split DR_R
if ( (NNode->dr!=nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr)&&(NNode->dr->type==diagDRUL) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i+3;
        newmagnet->address.j=RailStart.j+2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class splitDR_R();

        static_cast<class splitDR_R*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+2]);
        static_cast<class splitDR_R*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j]);
        static_cast<class splitDR_R*>(newmagnet->newelement)->r=&(CornerNodes[RailStart.i+3][RailStart.j+2]);
        static_cast<class splitDR_R*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class splitDR_R*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(CornerNodes[RailStart.i][RailStart.j].dr);

        if ((CornerNodes[RailStart.i+1][RailStart.j+1].dr!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j+1].dr->type==diagDRUL))
            allowed.append(CornerNodes[RailStart.i+1][RailStart.j+1].dr);

        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);
}


// ==================== upgrade DRUL to split DR_D
if ( (NNode->dr!=nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr)&&(NNode->dr->type==diagDRUL) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i+2;
        newmagnet->address.j=RailStart.j+3;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class splitDR_D();

        static_cast<class splitDR_D*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+2]);
        static_cast<class splitDR_D*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j]);
        static_cast<class splitDR_D*>(newmagnet->newelement)->d=&(CornerNodes[RailStart.i+2][RailStart.j+3]);
        static_cast<class splitDR_D*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class splitDR_D*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(CornerNodes[RailStart.i][RailStart.j].dr);

        if ((CornerNodes[RailStart.i+1][RailStart.j+1].dr!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j+1].dr->type==diagDRUL))
            allowed.append(CornerNodes[RailStart.i+1][RailStart.j+1].dr);

        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);
}



// ==================== upgrade tight dr_D to junction DR_D
if ( (NNode->dr!=nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr)&&(NNode->dr->type==tight_DR_D) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i+2;
        newmagnet->address.j=RailStart.j+2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class junctionDR_D();

        static_cast<class junctionDR_D*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+2]);
        static_cast<class junctionDR_D*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j]);
        static_cast<class junctionDR_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i+1][RailStart.j+3]);
        static_cast<class junctionDR_D*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class junctionDR_D*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(CornerNodes[RailStart.i][RailStart.j].dr);

        if ((CornerNodes[RailStart.i+1][RailStart.j+1].dr!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j+1].dr->type==diagDRUL))
            allowed.append(CornerNodes[RailStart.i+1][RailStart.j+1].dr);

        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);

    }


// ==================== upgrade tight DR_R to junction DR_R
if ( (NNode->dr!=nullptr)&&(NNode->ur==nullptr)&&(NNode->dl==nullptr)&&(NNode->dr->type==tight_DR_R) )
    {
        DMagnet * newmagnet = new DMagnet();
        newmagnet->address.i=RailStart.i+2;
        newmagnet->address.j=RailStart.j+2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class junctionDR_R();

        static_cast<class junctionDR_R*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+2]);
        static_cast<class junctionDR_R*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j]);
        static_cast<class junctionDR_R*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+3][RailStart.j+1]);
        static_cast<class junctionDR_R*>(newmagnet->newelement)->i = RailStart.i;
        static_cast<class junctionDR_R*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(CornerNodes[RailStart.i][RailStart.j].dr);

        if ((CornerNodes[RailStart.i+1][RailStart.j+1].dr!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j+1].dr->type==diagDRUL))
            allowed.append(CornerNodes[RailStart.i+1][RailStart.j+1].dr);

        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
        magnets.append(newmagnet);

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

// ============= connections to splits
if  (NNode->dr==nullptr)
    {

        if  (  ((CornerNodes[RailStart.i+3][RailStart.j+2].ul!=nullptr) &&  (CornerNodes[RailStart.i+3][RailStart.j+2].ul->type==diagULDR))||
               ((CornerNodes[RailStart.i+2][RailStart.j+1].ul!=nullptr) &&  (CornerNodes[RailStart.i+2][RailStart.j+1].ul->type==diagULDR)) )
            {


                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i+3;
                newmagnet->address.j=RailStart.j+2;
                newmagnet->address.type=NetworkNodeTypes::corner;
                newmagnet->newelement = new class splitUL_L();
                static_cast<class splitUL_L*>(newmagnet->newelement)->l=NNode;
                static_cast<class splitUL_L*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i+1][RailStart.j]);
                static_cast<class splitUL_L*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+3][RailStart.j+2]);
                static_cast<class splitUL_L*>(newmagnet->newelement)->i = RailStart.i;
                static_cast<class splitUL_L*>(newmagnet->newelement)->j = RailStart.j;
                newmagnet->valid = check_obstruction(newmagnet->newelement);

                QList<DNetworkListElement*> allowed;

                if((CornerNodes[RailStart.i+3][RailStart.j+2].ul!=nullptr) &&  (CornerNodes[RailStart.i+3][RailStart.j+2].ul->type==diagULDR))
                    allowed.append(CornerNodes[RailStart.i+3][RailStart.j+2].ul);

                if((CornerNodes[RailStart.i+2][RailStart.j+1].ul!=nullptr) &&  (CornerNodes[RailStart.i+2][RailStart.j+1].ul->type==diagULDR))
                    allowed.append(CornerNodes[RailStart.i+2][RailStart.j+1].ul);

                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }


        if  (  ((CornerNodes[RailStart.i+2][RailStart.j+3].ul!=nullptr) &&  (CornerNodes[RailStart.i+2][RailStart.j+3].ul->type==diagULDR))||
               ((CornerNodes[RailStart.i+1][RailStart.j+2].ul!=nullptr) &&  (CornerNodes[RailStart.i+1][RailStart.j+2].ul->type==diagULDR)) )
            {


                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i+2;
                newmagnet->address.j=RailStart.j+3;
                newmagnet->address.type=NetworkNodeTypes::corner;
                newmagnet->newelement = new class splitUL_U();
                static_cast<class splitUL_U*>(newmagnet->newelement)->u=NNode;
                static_cast<class splitUL_U*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j+1]);
                static_cast<class splitUL_U*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+3]);
                static_cast<class splitUL_U*>(newmagnet->newelement)->i = RailStart.i;
                static_cast<class splitUL_U*>(newmagnet->newelement)->j = RailStart.j;
                newmagnet->valid = check_obstruction(newmagnet->newelement);

                QList<DNetworkListElement*> allowed;

                if((CornerNodes[RailStart.i+2][RailStart.j+3].ul!=nullptr) &&  (CornerNodes[RailStart.i+2][RailStart.j+3].ul->type==diagULDR))
                    allowed.append(CornerNodes[RailStart.i+2][RailStart.j+3].ul);

                if((CornerNodes[RailStart.i+1][RailStart.j+2].ul!=nullptr) &&  (CornerNodes[RailStart.i+1][RailStart.j+2].ul->type==diagULDR))
                    allowed.append(CornerNodes[RailStart.i+1][RailStart.j+2].ul);

                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }
}



}
