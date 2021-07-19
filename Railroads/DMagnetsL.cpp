#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_L()
{
    DVerticalSideNode * NNode = &(VerticalSideNodes[RailStart.i][RailStart.j]);



// principal direction to the left....
if (NNode->l==nullptr)
    {
        DMagnet* prevptr = nullptr;
        int i0 = RailStart.i-1;
        int j0 = RailStart.j;

        DMagnet * newmagnet;
        bool flag = true;
        do
            {

            newmagnet =  new DMagnet;
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::vert;
            newmagnet->newelement = new class straightHoriz();
            static_cast<class straightHoriz*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0+1][j0]);
            static_cast<class straightHoriz*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0][j0]);
            static_cast<class straightHoriz*>(newmagnet->newelement)->i=i0;
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

            i0 = i0 - 1;

            }
        while (flag);

        //=========check for the connections with the junctions

        //===========junction R_UR
       if ( (VerticalSideNodes[i0][j0].r!=nullptr)&&(VerticalSideNodes[i0][j0].r->type==RailTypes::tight_DL_L))
           {

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
               allowed.append(VerticalSideNodes[i0][j0].r);

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

       //===========junction R_DR
      if ( (VerticalSideNodes[i0][j0].r!=nullptr)&&(VerticalSideNodes[i0][j0].r->type==RailTypes::tight_UL_L))
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=i0;
              newmagnet->address.j=j0;
              newmagnet->address.type=NetworkNodeTypes::vert;
              newmagnet->newelement = new class junctionR_DR();

              static_cast<class junctionR_DR*>(newmagnet->newelement)->l=&(VerticalSideNodes[i0][j0]);;
              static_cast<class junctionR_DR*>(newmagnet->newelement)->r=&(VerticalSideNodes[i0+2][j0]);
              static_cast<class junctionR_DR*>(newmagnet->newelement)->dr=&(CornerNodes[i0+2][j0+2]);

              static_cast<class junctionR_DR*>(newmagnet->newelement)->i = i0;
              static_cast<class junctionR_DR*>(newmagnet->newelement)->j = j0;

              QList<DNetworkListElement*> allowed;
              allowed.append(VerticalSideNodes[i0][j0].r);

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


// upgrade straight to junction L_UL
if ( (NNode->l!=nullptr)&& (NNode->l->type==straightHoriz))
    {

        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j-1;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class junctionL_UL();
        static_cast<class junctionL_UL*>(newmagnet->newelement)->r=NNode;
        static_cast<class junctionL_UL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-2][RailStart.j]);
        static_cast<class junctionL_UL*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-3][RailStart.j-1]);
        static_cast<class junctionL_UL*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class junctionL_UL*>(newmagnet->newelement)->j = RailStart.j-1;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->l);

        if  ( (VerticalSideNodes[RailStart.i-2][RailStart.j].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j].r->type==straightHoriz))
            allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j].r);
        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

        magnets.append(newmagnet);
    }

// upgrade straight to junction L_DL
if ( (NNode->l!=nullptr)&& (NNode->l->type==straightHoriz))
    {

        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j+2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class junctionL_DL();
        static_cast<class junctionL_DL*>(newmagnet->newelement)->r=NNode;
        static_cast<class junctionL_DL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-2][RailStart.j]);
        static_cast<class junctionL_DL*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-3][RailStart.j+2]);
        static_cast<class junctionL_DL*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class junctionL_DL*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->l);

        if  ( (VerticalSideNodes[RailStart.i-2][RailStart.j].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j].r->type==straightHoriz))
            allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j].r);
        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

        magnets.append(newmagnet);
    }





// =================== tught L_UL = tight DR_R===========
if (NNode->l==nullptr)
    {
        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j-1;
        newmagnet->address.type=NetworkNodeTypes::corner;

        newmagnet->newelement = new class tight_DR_R();
        static_cast<class tight_DR_R*>(newmagnet->newelement)->r=NNode;
        static_cast<class tight_DR_R*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-3][RailStart.j-1]);
        static_cast<class tight_DR_R*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class tight_DR_R*>(newmagnet->newelement)->j = RailStart.j-1;
        newmagnet->valid = check_obstruction(newmagnet->newelement);
        magnets.append(newmagnet);
    }


// upgrade tight L_UL to junction L_UL
if ( (NNode->l!=nullptr)&& (NNode->l->type==tight_DR_R))
    {

        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-2;
        newmagnet->address.j=RailStart.j;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class junctionL_UL();
        static_cast<class junctionL_UL*>(newmagnet->newelement)->r=NNode;
        static_cast<class junctionL_UL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-2][RailStart.j]);
        static_cast<class junctionL_UL*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-3][RailStart.j-1]);
        static_cast<class junctionL_UL*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class junctionL_UL*>(newmagnet->newelement)->j = RailStart.j-1;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->l);

        if  ( (VerticalSideNodes[RailStart.i-2][RailStart.j].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j].r->type==straightHoriz))
            allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j].r);
        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

        magnets.append(newmagnet);
    }




// =================== tught L_DL = tight UR_R + UPGRADE TO JUNCTION UR_R===========
if (NNode->l==nullptr)
    {

        if ( ((CornerNodes[RailStart.i-3][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-3][RailStart.j+2].ur->type==diagURDL)) ||
            ((CornerNodes[RailStart.i-2][RailStart.j+1].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+1].ur->type==diagURDL))
            )
            {

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-3;
                newmagnet->address.j=RailStart.j+2;
                newmagnet->address.type=NetworkNodeTypes::corner;
                newmagnet->newelement = new class junctionUR_R();

                static_cast<class junctionUR_R*>(newmagnet->newelement)->r=NNode;
                static_cast<class junctionUR_R*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i-2][RailStart.j+1]);
                static_cast<class junctionUR_R*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-3][RailStart.j+2]);
                static_cast<class junctionUR_R*>(newmagnet->newelement)->i = RailStart.i-3;
                static_cast<class junctionUR_R*>(newmagnet->newelement)->j = RailStart.j;

                QList<DNetworkListElement*> allowed;


                if ((CornerNodes[RailStart.i-3][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-3][RailStart.j+2].ur->type==diagURDL))
                    allowed.append(CornerNodes[RailStart.i-3][RailStart.j+2].ur);

                if ((CornerNodes[RailStart.i-2][RailStart.j+1].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+1].ur->type==diagURDL))
                    allowed.append(CornerNodes[RailStart.i-2][RailStart.j+1].ur);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);

            }

        else {


        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j+2;
        newmagnet->address.type=NetworkNodeTypes::corner;
        newmagnet->newelement = new class tight_UR_R();
        static_cast<class tight_UR_R*>(newmagnet->newelement)->r=NNode;
        static_cast<class tight_UR_R*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-3][RailStart.j+2]);
        static_cast<class tight_UR_R*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class tight_UR_R*>(newmagnet->newelement)->j = RailStart.j;
        newmagnet->valid = check_obstruction(newmagnet->newelement);

        magnets.append(newmagnet);
            }
    }

// upgradet tight L_DL to junction L_DL
if ( (NNode->l!=nullptr)&& (NNode->l->type==tight_UR_R))
    {

        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-2;
        newmagnet->address.j=RailStart.j;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class junctionL_DL();
        static_cast<class junctionL_DL*>(newmagnet->newelement)->r=NNode;
        static_cast<class junctionL_DL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-2][RailStart.j]);
        static_cast<class junctionL_DL*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-3][RailStart.j+2]);
        static_cast<class junctionL_DL*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class junctionL_DL*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->l);

        if  ( (VerticalSideNodes[RailStart.i-2][RailStart.j].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j].r->type==straightHoriz))
            allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j].r);
        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

        magnets.append(newmagnet);
    }



}
