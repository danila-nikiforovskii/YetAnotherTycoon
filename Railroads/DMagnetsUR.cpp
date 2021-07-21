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

//===== check for connections with junctions
    // JUNCTION DL_D
    if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].dl!=nullptr)&&(CornerNodes[i0][j0].dl->type==tight_DL_D))
        {

            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionDL_D();

            static_cast<class junctionDL_D*>(newmagnet->newelement)->ur=&(CornerNodes[i0][j0]);
            static_cast<class junctionDL_D*>(newmagnet->newelement)->dl=&(CornerNodes[i0-2][j0+2]);
            static_cast<class junctionDL_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0-2][j0+3]);
            static_cast<class junctionDL_D*>(newmagnet->newelement)->i = i0-2;
            static_cast<class junctionDL_D*>(newmagnet->newelement)->j = j0;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].dl);

            /*if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
                allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);*/
            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }



// JUNCTION DL_L
    if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].dl!=nullptr)&&(CornerNodes[i0][j0].dl->type==tight_DL_L))
        {

            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class junctionDL_L();

            static_cast<class junctionDL_L*>(newmagnet->newelement)->ur=&(CornerNodes[i0][j0]);
            static_cast<class junctionDL_L*>(newmagnet->newelement)->dl=&(CornerNodes[i0-2][j0+2]);
            static_cast<class junctionDL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0-3][j0+1]);
            static_cast<class junctionDL_L*>(newmagnet->newelement)->i = i0-3;
            static_cast<class junctionDL_L*>(newmagnet->newelement)->j = j0;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].dl);

            /*if ((CornerNodes[RailStart.i-2][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j-2].dr->type=diagULDR))
                allowed.append(CornerNodes[RailStart.i-2][RailStart.j-2].dr);*/
            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
        }



    // =========== check connections to split =================
   //  j0=j0-1;i0=i0+1;
    if (CornerLimits(i0,j0) && (CornerNodes[i0][j0].dl!=nullptr) && (CornerNodes[i0][j0].dl->type==split_UR_U))
        {
            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class NjunctionUR();

            static_cast<class NjunctionUR*>(newmagnet->newelement)->uru=&(CornerNodes[i0][j0]);
            static_cast<class NjunctionUR*>(newmagnet->newelement)->urd=&(CornerNodes[i0][j0+1]);

            static_cast<class NjunctionUR*>(newmagnet->newelement)->dlu=&(CornerNodes[i0-2][j0+2]);
            static_cast<class NjunctionUR*>(newmagnet->newelement)->dld=&(CornerNodes[i0-2][j0+3]);

            static_cast<class NjunctionUR*>(newmagnet->newelement)->i = i0-2;
            static_cast<class NjunctionUR*>(newmagnet->newelement)->j = j0;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].dl);

            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);


        }


    if (CornerLimits(i0,j0) && (CornerNodes[i0][j0].dl!=nullptr) && (CornerNodes[i0][j0].dl->type==split_UR_R))
        {
            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class NjunctionDL();

            static_cast<class NjunctionDL*>(newmagnet->newelement)->urr=&(CornerNodes[i0][j0]);
            static_cast<class NjunctionDL*>(newmagnet->newelement)->url=&(CornerNodes[i0-1][j0]);

            static_cast<class NjunctionDL*>(newmagnet->newelement)->dlr=&(CornerNodes[i0-2][j0+2]);
            static_cast<class NjunctionDL*>(newmagnet->newelement)->dll=&(CornerNodes[i0-1][j0+2]);

            static_cast<class NjunctionDL*>(newmagnet->newelement)->i = i0-3;
            static_cast<class NjunctionDL*>(newmagnet->newelement)->j = j0;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].dl);

            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);


        }


        }


    // =========== upgrade straight ur to splits UR_U + FURTHER TO NjunctionUR
    if ( (NNode->ur!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) && (NNode->ur->type==diagURDL))
        {


            if   (  ((CornerNodes[RailStart.i+2][RailStart.j-3].dl)&&(CornerNodes[RailStart.i+2][RailStart.j-3].dl->type==diagURDL))||
                    ((CornerNodes[RailStart.i+1][RailStart.j-2].dl)&&(CornerNodes[RailStart.i+1][RailStart.j-2].dl->type==diagURDL)))
                {

                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+2;
                    newmagnet->address.j=RailStart.j-3;
                    newmagnet->address.type=NetworkNodeTypes::corner;

                    newmagnet->newelement= new class NjunctionUR();

                    static_cast<class NjunctionUR*>(newmagnet->newelement)->uru=&(CornerNodes[RailStart.i+2][RailStart.j-3]);
                    static_cast<class NjunctionUR*>(newmagnet->newelement)->urd=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
                    static_cast<class NjunctionUR*>(newmagnet->newelement)->dlu=&(CornerNodes[RailStart.i][RailStart.j-1]);
                    static_cast<class NjunctionUR*>(newmagnet->newelement)->dld=NNode;
                        static_cast<class NjunctionUR*>(newmagnet->newelement)->i = RailStart.i;
                       static_cast<class NjunctionUR*>(newmagnet->newelement)->j = RailStart.j-3;

                    QList<DNetworkListElement*> allowed;
                    if((CornerNodes[RailStart.i+1][RailStart.j-1].ur!=nullptr) && (CornerNodes[RailStart.i+1][RailStart.j-1].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+1][RailStart.j-1].ur);
                    if((CornerNodes[RailStart.i][RailStart.j].ur!=nullptr) && (CornerNodes[RailStart.i][RailStart.j].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i][RailStart.j].ur);

                    if((CornerNodes[RailStart.i+2][RailStart.j-3].dl!=nullptr) && (CornerNodes[RailStart.i+2][RailStart.j-3].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+2][RailStart.j-3].dl);
                    if((CornerNodes[RailStart.i+1][RailStart.j-2].dl!=nullptr) && (CornerNodes[RailStart.i+1][RailStart.j-2].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+1][RailStart.j-2].dl);



                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);
                }
            else
                {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+2;
            newmagnet->address.j=RailStart.j-3;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class splitUR_U();

            static_cast<class splitUR_U*>(newmagnet->newelement)->dl=NNode;
            static_cast<class splitUR_U*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
            static_cast<class splitUR_U*>(newmagnet->newelement)->u=&(CornerNodes[RailStart.i+2][RailStart.j-3]);

            static_cast<class splitUR_U*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class splitUR_U*>(newmagnet->newelement)->j = RailStart.j-3;

            QList<DNetworkListElement*> allowed;
            allowed.append(NNode->ur);
            if ((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                            allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
                }
        }

    // =========== upgrade straight ur to splits UR_R + further to NjunctionDL
    if ( (NNode->ur!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) && (NNode->ur->type==diagURDL))
        {

            if   (  ((CornerNodes[RailStart.i+3][RailStart.j-2].dl)&&(CornerNodes[RailStart.i+3][RailStart.j-2].dl->type==diagURDL))||
                    ((CornerNodes[RailStart.i+2][RailStart.j-1].dl)&&(CornerNodes[RailStart.i+2][RailStart.j-1].dl->type==diagURDL)))
                {

                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+3;
                    newmagnet->address.j=RailStart.j-2;
                    newmagnet->address.type=NetworkNodeTypes::corner;

                    newmagnet->newelement= new class NjunctionDL();

                    static_cast<class NjunctionDL*>(newmagnet->newelement)->url=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->urr=&(CornerNodes[RailStart.i+3][RailStart.j-2]);
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->dlr=&(CornerNodes[RailStart.i+1][RailStart.j]);
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->dll=NNode;
                        static_cast<class NjunctionDL*>(newmagnet->newelement)->i = RailStart.i;
                       static_cast<class NjunctionDL*>(newmagnet->newelement)->j = RailStart.j-2;

                    QList<DNetworkListElement*> allowed;
                    if((CornerNodes[RailStart.i+1][RailStart.j-1].ur!=nullptr) && (CornerNodes[RailStart.i+1][RailStart.j-1].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+1][RailStart.j-1].ur);
                    if((CornerNodes[RailStart.i][RailStart.j].ur!=nullptr) && (CornerNodes[RailStart.i][RailStart.j].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i][RailStart.j].ur);

                    if((CornerNodes[RailStart.i+3][RailStart.j-2].dl!=nullptr) && (CornerNodes[RailStart.i+3][RailStart.j-2].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+3][RailStart.j-2].dl);
                    if((CornerNodes[RailStart.i+2][RailStart.j-1].dl!=nullptr) && (CornerNodes[RailStart.i+2][RailStart.j-1].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+2][RailStart.j-1].dl);



                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);
                }
            else
                {
            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i+3;
            newmagnet->address.j=RailStart.j-2;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class splitUR_R();

            static_cast<class splitUR_R*>(newmagnet->newelement)->dl=NNode;
            static_cast<class splitUR_R*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
            static_cast<class splitUR_R*>(newmagnet->newelement)->r=&(CornerNodes[RailStart.i+3][RailStart.j-2]);

            static_cast<class splitUR_U*>(newmagnet->newelement)->i = RailStart.i;
            static_cast<class splitUR_U*>(newmagnet->newelement)->j = RailStart.j-2;

            QList<DNetworkListElement*> allowed;
            allowed.append(NNode->ur);
            if ((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                            allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);

            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);
                }

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


    // ============= connections to splits
    if  (NNode->ur==nullptr)
        {

            if  (  ((CornerNodes[RailStart.i+2][RailStart.j-3].dl!=nullptr) &&  (CornerNodes[RailStart.i+2][RailStart.j-3].dl->type==diagURDL))||
                   ((CornerNodes[RailStart.i+1][RailStart.j-2].dl!=nullptr) &&  (CornerNodes[RailStart.i+1][RailStart.j-2].dl->type==diagURDL)) )
                {


                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+2;
                    newmagnet->address.j=RailStart.j-2-1;
                    newmagnet->address.type=NetworkNodeTypes::corner;
                    newmagnet->newelement = new class splitDL_D();
                    static_cast<class splitDL_D*>(newmagnet->newelement)->d=NNode;
                    static_cast<class splitDL_D*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i][RailStart.j-1]);
                    static_cast<class splitDL_D*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-3]);
                    static_cast<class splitDL_D*>(newmagnet->newelement)->i = RailStart.i;
                    static_cast<class splitDL_D*>(newmagnet->newelement)->j = RailStart.j-3;
                    newmagnet->valid = check_obstruction(newmagnet->newelement);

                    QList<DNetworkListElement*> allowed;

                    if((CornerNodes[RailStart.i+2][RailStart.j-3].dl!=nullptr) && (CornerNodes[RailStart.i+2][RailStart.j-3].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+2][RailStart.j-3].dl);

                    if((CornerNodes[RailStart.i+1][RailStart.j-2].dl!=nullptr) && (CornerNodes[RailStart.i+1][RailStart.j-2].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+1][RailStart.j-2].dl);

                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);
                }

            if  (  ((CornerNodes[RailStart.i+3][RailStart.j-2].dl!=nullptr) &&  (CornerNodes[RailStart.i+3][RailStart.j-2].dl->type==diagURDL))||
                   ((CornerNodes[RailStart.i+2][RailStart.j-1].dl!=nullptr) &&  (CornerNodes[RailStart.i+2][RailStart.j-1].dl->type==diagURDL)) )
                {


                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+3;
                    newmagnet->address.j=RailStart.j-2;
                    newmagnet->address.type=NetworkNodeTypes::corner;
                    newmagnet->newelement = new class splitDL_L();
                    static_cast<class splitDL_L*>(newmagnet->newelement)->l=NNode;
                    static_cast<class splitDL_L*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i+1][RailStart.j]);
                    static_cast<class splitDL_L*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+3][RailStart.j-2]);
                    static_cast<class splitDL_L*>(newmagnet->newelement)->i = RailStart.i;
                    static_cast<class splitDL_L*>(newmagnet->newelement)->j = RailStart.j-2;
                    newmagnet->valid = check_obstruction(newmagnet->newelement);

                    QList<DNetworkListElement*> allowed;

                    if((CornerNodes[RailStart.i+3][RailStart.j-2].dl!=nullptr) && (CornerNodes[RailStart.i+3][RailStart.j-2].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+3][RailStart.j-2].dl);

                    if((CornerNodes[RailStart.i+2][RailStart.j-1].dl!=nullptr) && (CornerNodes[RailStart.i+2][RailStart.j-1].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+2][RailStart.j-1].dl);

                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);
                }

    }


    // ========= upgrade split DL_D TO NjunctionUR

        if  ( (NNode->ur!=nullptr) && (NNode->ur->type==split_DL_D))
            {

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i+2;
                newmagnet->address.j=RailStart.j-2;
                newmagnet->address.type=NetworkNodeTypes::corner;

                newmagnet->newelement= new class NjunctionUR();

                static_cast<class NjunctionUR*>(newmagnet->newelement)->dlu=&(CornerNodes[RailStart.i][RailStart.j+1]);
                static_cast<class NjunctionUR*>(newmagnet->newelement)->dld=NNode;
                static_cast<class NjunctionUR*>(newmagnet->newelement)->uru=&(CornerNodes[RailStart.i+2][RailStart.j-3]);
                static_cast<class NjunctionUR*>(newmagnet->newelement)->urd=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
                    static_cast<class NjunctionUR*>(newmagnet->newelement)->i = RailStart.i;
                   static_cast<class NjunctionUR*>(newmagnet->newelement)->j = RailStart.j-3;

                QList<DNetworkListElement*> allowed;
                if((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr) && (CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                    allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);
                allowed.append(NNode->ur);
                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);

            }




        // ========= upgrade split DL_L TO NjunctionDL

            if  ( (NNode->ur!=nullptr) && (NNode->ur->type==split_DL_L))
                {

                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i+2;
                    newmagnet->address.j=RailStart.j-2;
                    newmagnet->address.type=NetworkNodeTypes::corner;

                    newmagnet->newelement= new class NjunctionDL();

                    static_cast<class NjunctionDL*>(newmagnet->newelement)->dlr=&(CornerNodes[RailStart.i+1][RailStart.j]);
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->dll=NNode;
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->urr=&(CornerNodes[RailStart.i+3][RailStart.j-2]);
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->url=&(CornerNodes[RailStart.i+2][RailStart.j-2]);
                        static_cast<class NjunctionDL*>(newmagnet->newelement)->i = RailStart.i;
                       static_cast<class NjunctionDL*>(newmagnet->newelement)->j = RailStart.j-2;

                    QList<DNetworkListElement*> allowed;
                    if((CornerNodes[RailStart.i+2][RailStart.j-2].dl!=nullptr) && (CornerNodes[RailStart.i+2][RailStart.j-2].dl->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i+2][RailStart.j-2].dl);
                    allowed.append(NNode->ur);
                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);

                }



}
