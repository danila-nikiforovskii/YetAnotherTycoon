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

      // check for connection with splits
      i0 = i0 - 1;
      if ( (VerticalSideNodes[i0][j0].r!=nullptr)&&(VerticalSideNodes[i0][j0].r->type==RailTypes::split_L_D))
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=i0;
              newmagnet->address.j=j0;
              newmagnet->address.type=NetworkNodeTypes::vert;
              newmagnet->newelement = new class NjunctionR();

              static_cast<class NjunctionR*>(newmagnet->newelement)->ld=&(VerticalSideNodes[i0][j0]);
              static_cast<class NjunctionR*>(newmagnet->newelement)->lu=&(VerticalSideNodes[i0][j0-1]);
              static_cast<class NjunctionR*>(newmagnet->newelement)->ru=&(VerticalSideNodes[i0+3][j0-1]);
              static_cast<class NjunctionR*>(newmagnet->newelement)->rd=&(VerticalSideNodes[i0+3][j0]);

              static_cast<class NjunctionR*>(newmagnet->newelement)->mid_r_u=&(VerticalSideNodes[i0+2][j0-1]);
              static_cast<class NjunctionR*>(newmagnet->newelement)->mid_r_d=&(VerticalSideNodes[i0+2][j0]);

              static_cast<class NjunctionR*>(newmagnet->newelement)->i = i0;
              static_cast<class NjunctionR*>(newmagnet->newelement)->j = j0-1;

              QList<DNetworkListElement*> allowed;
              allowed.append(VerticalSideNodes[i0][j0].r);

              if ((VerticalSideNodes[i0][j0-1].r!=nullptr)&&(VerticalSideNodes[i0][j0-1].r->type==straightHoriz))
                  allowed.append(VerticalSideNodes[i0][j0-1].r);

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

      if ( (VerticalSideNodes[i0][j0].r!=nullptr)&&(VerticalSideNodes[i0][j0].r->type==RailTypes::split_L_U))
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=i0;
              newmagnet->address.j=j0;
              newmagnet->address.type=NetworkNodeTypes::vert;
              newmagnet->newelement = new class NjunctionL();

              static_cast<class NjunctionL*>(newmagnet->newelement)->ld=&(VerticalSideNodes[i0][j0+1]);
              static_cast<class NjunctionL*>(newmagnet->newelement)->lu=&(VerticalSideNodes[i0][j0]);
              static_cast<class NjunctionL*>(newmagnet->newelement)->ru=&(VerticalSideNodes[i0+3][j0]);
              static_cast<class NjunctionL*>(newmagnet->newelement)->rd=&(VerticalSideNodes[i0+3][j0+1]);

              static_cast<class NjunctionL*>(newmagnet->newelement)->mid_r_u=&(VerticalSideNodes[i0+2][j0]);
              static_cast<class NjunctionL*>(newmagnet->newelement)->mid_r_d=&(VerticalSideNodes[i0+2][j0+1]);

              static_cast<class NjunctionL*>(newmagnet->newelement)->i = i0;
              static_cast<class NjunctionL*>(newmagnet->newelement)->j = j0;

              QList<DNetworkListElement*> allowed;
              allowed.append(VerticalSideNodes[i0][j0].r);

              if ((VerticalSideNodes[i0][j0+1].r!=nullptr)&&(VerticalSideNodes[i0][j0+1].r->type==straightHoriz))
                  allowed.append(VerticalSideNodes[i0][j0+1].r);

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



// upgrade straight to split L_U + further to NjunctionL
if ( (NNode->l!=nullptr)&& (NNode->l->type==straightHoriz))
    {

        if ( (( VerticalSideNodes[RailStart.i-3][RailStart.j-1].r!=nullptr)&&( VerticalSideNodes[RailStart.i-3][RailStart.j-1].r->type==straightHoriz))||
             (( VerticalSideNodes[RailStart.i-2][RailStart.j-1].r!=nullptr)&&( VerticalSideNodes[RailStart.i-2][RailStart.j-1].r->type==straightHoriz)) )
            {

                int i0 = RailStart.i-3;
                int j0 = RailStart.j-1;

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=i0;
                newmagnet->address.j=j0;
                newmagnet->address.type=NetworkNodeTypes::vert;
                newmagnet->newelement = new class NjunctionL();

                static_cast<class NjunctionL*>(newmagnet->newelement)->ld=&(VerticalSideNodes[i0][j0+1]);
                static_cast<class NjunctionL*>(newmagnet->newelement)->lu=&(VerticalSideNodes[i0][j0]);
                static_cast<class NjunctionL*>(newmagnet->newelement)->ru=&(VerticalSideNodes[i0+3][j0]);
                static_cast<class NjunctionL*>(newmagnet->newelement)->rd=&(VerticalSideNodes[i0+3][j0+1]);

                static_cast<class NjunctionL*>(newmagnet->newelement)->mid_r_u=&(VerticalSideNodes[i0+2][j0]);
                static_cast<class NjunctionL*>(newmagnet->newelement)->mid_r_d=&(VerticalSideNodes[i0+2][j0+1]);

                static_cast<class NjunctionL*>(newmagnet->newelement)->i = i0;
                static_cast<class NjunctionL*>(newmagnet->newelement)->j = j0;

                QList<DNetworkListElement*> allowed;




                if ((VerticalSideNodes[i0][j0].r!=nullptr)&&(VerticalSideNodes[i0][j0].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0][j0].r);

                if ((VerticalSideNodes[i0+1][j0].r!=nullptr)&&(VerticalSideNodes[i0+1][j0].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+1][j0].r);

                if ((VerticalSideNodes[i0+2][j0].r!=nullptr)&&(VerticalSideNodes[i0+2][j0].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+2][j0].r);

                if ((VerticalSideNodes[i0][j0+1].r!=nullptr)&&(VerticalSideNodes[i0][j0+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0][j0+1].r);

                if ((VerticalSideNodes[i0+1][j0+1].r!=nullptr)&&(VerticalSideNodes[i0+1][j0+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+1][j0+1].r);

                if ((VerticalSideNodes[i0+2][j0+1].r!=nullptr)&&(VerticalSideNodes[i0+2][j0+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+2][j0+1].r);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);



            }
        else
            {



        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j-1;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class splitL_U();
        static_cast<class splitL_U*>(newmagnet->newelement)->r=NNode;
        static_cast<class splitL_U*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-2][RailStart.j]);
        static_cast<class splitL_U*>(newmagnet->newelement)->u=&(VerticalSideNodes[RailStart.i-3][RailStart.j-1]);
        static_cast<class splitL_U*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class splitL_U*>(newmagnet->newelement)->j = RailStart.j-1;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->l);

        if  ( (VerticalSideNodes[RailStart.i-2][RailStart.j].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j].r->type==straightHoriz))
            allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j].r);
        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

        magnets.append(newmagnet);
            }
    }



// upgrade straight to split L_D + FURTHER TO N junction R
if ( (NNode->l!=nullptr)&& (NNode->l->type==straightHoriz))
    {

        if (( (VerticalSideNodes[RailStart.i-3][RailStart.j+1].r!=nullptr)&&(VerticalSideNodes[RailStart.i-3][RailStart.j+1].r->type==straightHoriz))||
            ( (VerticalSideNodes[RailStart.i-2][RailStart.j+1].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j+1].r->type==straightHoriz)))
            {

                int i0 = RailStart.i-3;
                int j0 = RailStart.j+1;

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=i0;
                newmagnet->address.j=j0;
                newmagnet->address.type=NetworkNodeTypes::vert;
                newmagnet->newelement = new class NjunctionR();

                static_cast<class NjunctionR*>(newmagnet->newelement)->ld=&(VerticalSideNodes[i0][j0]);
                static_cast<class NjunctionR*>(newmagnet->newelement)->lu=&(VerticalSideNodes[i0][j0-1]);
                static_cast<class NjunctionR*>(newmagnet->newelement)->ru=&(VerticalSideNodes[i0+3][j0-1]);
                static_cast<class NjunctionR*>(newmagnet->newelement)->rd=&(VerticalSideNodes[i0+3][j0]);

                static_cast<class NjunctionR*>(newmagnet->newelement)->mid_r_u=&(VerticalSideNodes[i0+2][j0-1]);
                static_cast<class NjunctionR*>(newmagnet->newelement)->mid_r_d=&(VerticalSideNodes[i0+2][j0]);

                static_cast<class NjunctionR*>(newmagnet->newelement)->i = i0;
                static_cast<class NjunctionR*>(newmagnet->newelement)->j = j0-1;

                QList<DNetworkListElement*> allowed;




                if ((VerticalSideNodes[i0][j0].r!=nullptr)&&(VerticalSideNodes[i0][j0].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0][j0].r);

                if ((VerticalSideNodes[i0+1][j0].r!=nullptr)&&(VerticalSideNodes[i0+1][j0].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+1][j0].r);

                if ((VerticalSideNodes[i0+2][j0].r!=nullptr)&&(VerticalSideNodes[i0+2][j0].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+2][j0].r);

                if ((VerticalSideNodes[i0][j0-1].r!=nullptr)&&(VerticalSideNodes[i0][j0-1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0][j0-1].r);

                if ((VerticalSideNodes[i0+1][j0-1].r!=nullptr)&&(VerticalSideNodes[i0+1][j0-1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+1][j0-1].r);

                if ((VerticalSideNodes[i0+2][j0-1].r!=nullptr)&&(VerticalSideNodes[i0+2][j0-1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[i0+2][j0-1].r);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }
        else
            {


        DMagnet * newmagnet = new DMagnet;
        newmagnet->address.i=RailStart.i-3;
        newmagnet->address.j=RailStart.j+1;
        newmagnet->address.type=NetworkNodeTypes::vert;
        newmagnet->newelement = new class splitL_D();
        static_cast<class splitL_D*>(newmagnet->newelement)->r=NNode;
        static_cast<class splitL_D*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-2][RailStart.j]);
        static_cast<class splitL_D*>(newmagnet->newelement)->d=&(VerticalSideNodes[RailStart.i-3][RailStart.j+1]);
        static_cast<class splitL_D*>(newmagnet->newelement)->i = RailStart.i-3;
        static_cast<class splitL_D*>(newmagnet->newelement)->j = RailStart.j;

        QList<DNetworkListElement*> allowed;
        allowed.append(NNode->l);

        if  ( (VerticalSideNodes[RailStart.i-2][RailStart.j].r!=nullptr)&&(VerticalSideNodes[RailStart.i-2][RailStart.j].r->type==straightHoriz))
            allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j].r);
        newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

        magnets.append(newmagnet);
            }
    }


// =================== tught L_UL = tight DR_R + UPGRADE TO junction DR_R===========
if (NNode->l==nullptr)
    {
        if  (  ((CornerNodes[RailStart.i-3][RailStart.j-1].dr!=nullptr)&&(CornerNodes[RailStart.i-3][RailStart.j-1].dr->type==diagULDR)) ||
               ((CornerNodes[RailStart.i-2][RailStart.j].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j].dr->type==diagULDR))
               )
            {

                DMagnet * newmagnet = new DMagnet();
                newmagnet->address.i=RailStart.i-3;
                newmagnet->address.j=RailStart.j-1;
                newmagnet->address.type=NetworkNodeTypes::corner;
                newmagnet->newelement = new class junctionDR_R();

                static_cast<class junctionDR_R*>(newmagnet->newelement)->r=NNode;
                static_cast<class junctionDR_R*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-3][RailStart.j-1]);
                static_cast<class junctionDR_R*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i-1][RailStart.j+1]);
                static_cast<class junctionDR_R*>(newmagnet->newelement)->i = RailStart.i-3;
                static_cast<class junctionDR_R*>(newmagnet->newelement)->j = RailStart.j-1;

                QList<DNetworkListElement*> allowed;

                if ((CornerNodes[RailStart.i-3][RailStart.j-1].dr!=nullptr)&&(CornerNodes[RailStart.i-3][RailStart.j-1].dr->type=diagULDR))
                    allowed.append(CornerNodes[RailStart.i-3][RailStart.j-1].dr);
                if ((CornerNodes[RailStart.i-2][RailStart.j].dr!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j].dr->type=diagULDR))
                    allowed.append(CornerNodes[RailStart.i-2][RailStart.j].dr);

                newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }

        else {



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



if  (NNode->l==nullptr)
    {

        if  (  ((VerticalSideNodes[RailStart.i-3][RailStart.j+1].r!=nullptr) &&  (VerticalSideNodes[RailStart.i-3][RailStart.j+1].r->type==straightHoriz))||
               ((VerticalSideNodes[RailStart.i-2][RailStart.j+1].r!=nullptr) &&  (VerticalSideNodes[RailStart.i-2][RailStart.j+1].r->type==straightHoriz)) )
            {


                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-3;
                newmagnet->address.j=RailStart.j+1;
                newmagnet->address.type=NetworkNodeTypes::vert;
                newmagnet->newelement = new class splitR_U();
                static_cast<class splitR_U*>(newmagnet->newelement)->u=NNode;
                static_cast<class splitR_U*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j+1]);
                static_cast<class splitR_U*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i-1][RailStart.j+1]);
                static_cast<class splitR_U*>(newmagnet->newelement)->i = RailStart.i-3;
                static_cast<class splitR_U*>(newmagnet->newelement)->j = RailStart.j;
                newmagnet->valid = check_obstruction(newmagnet->newelement);

                QList<DNetworkListElement*> allowed;

                if((VerticalSideNodes[RailStart.i-3][RailStart.j+1].r!=nullptr) && (VerticalSideNodes[RailStart.i-3][RailStart.j+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i-3][RailStart.j+1].r);

                if((VerticalSideNodes[RailStart.i-2][RailStart.j+1].r!=nullptr) && (VerticalSideNodes[RailStart.i-2][RailStart.j+1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j+1].r);


                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }

        if  (  ((VerticalSideNodes[RailStart.i-3][RailStart.j-1].r!=nullptr) &&  (VerticalSideNodes[RailStart.i-3][RailStart.j-1].r->type==straightHoriz))||
               ((VerticalSideNodes[RailStart.i-2][RailStart.j-1].r!=nullptr) &&  (VerticalSideNodes[RailStart.i-2][RailStart.j-1].r->type==straightHoriz)) )
            {


                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-3;
                newmagnet->address.j=RailStart.j-1;
                newmagnet->address.type=NetworkNodeTypes::vert;
                newmagnet->newelement = new class splitR_D();
                static_cast<class splitR_D*>(newmagnet->newelement)->d=NNode;
                static_cast<class splitR_D*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j-1]);
                static_cast<class splitR_D*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i-1][RailStart.j-1]);
                static_cast<class splitR_D*>(newmagnet->newelement)->i = RailStart.i-3;
                static_cast<class splitR_D*>(newmagnet->newelement)->j = RailStart.j-1;
                newmagnet->valid = check_obstruction(newmagnet->newelement);

                QList<DNetworkListElement*> allowed;

                if((VerticalSideNodes[RailStart.i-3][RailStart.j-1].r!=nullptr) && (VerticalSideNodes[RailStart.i-3][RailStart.j-1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i-3][RailStart.j-1].r);

                if((VerticalSideNodes[RailStart.i-2][RailStart.j-1].r!=nullptr) && (VerticalSideNodes[RailStart.i-2][RailStart.j-1].r->type==straightHoriz))
                    allowed.append(VerticalSideNodes[RailStart.i-2][RailStart.j-1].r);


                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
            }

}


if ( (NNode->l!=nullptr) && (NNode->l->type==split_R_U))
    {


         int i0 = RailStart.i-3;
         int j0 = RailStart.j;

         DMagnet * newmagnet = new DMagnet;
         newmagnet->address.i=i0;
         newmagnet->address.j=j0;
         newmagnet->address.type=NetworkNodeTypes::vert;
         newmagnet->newelement = new class NjunctionR();

         static_cast<class NjunctionR*>(newmagnet->newelement)->ld=&(VerticalSideNodes[i0][j0+1]);
         static_cast<class NjunctionR*>(newmagnet->newelement)->lu=&(VerticalSideNodes[i0][j0]);
         static_cast<class NjunctionR*>(newmagnet->newelement)->ru=&(VerticalSideNodes[i0+3][j0]);
         static_cast<class NjunctionR*>(newmagnet->newelement)->rd=&(VerticalSideNodes[i0+3][j0+1]);

         static_cast<class NjunctionR*>(newmagnet->newelement)->mid_r_u=&(VerticalSideNodes[i0+2][j0]);
         static_cast<class NjunctionR*>(newmagnet->newelement)->mid_r_d=&(VerticalSideNodes[i0+2][j0+1]);

         static_cast<class NjunctionR*>(newmagnet->newelement)->i = i0;
         static_cast<class NjunctionR*>(newmagnet->newelement)->j = j0;

         QList<DNetworkListElement*> allowed;

         allowed.append(NNode->l);


         if ((VerticalSideNodes[i0+3][j0].l!=nullptr)&&(VerticalSideNodes[i0+3][j0].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+3][j0].l);

         if ((VerticalSideNodes[i0+2][j0].l!=nullptr)&&(VerticalSideNodes[i0+2][j0].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+2][j0].l);

         if ((VerticalSideNodes[i0+1][j0].l!=nullptr)&&(VerticalSideNodes[i0+1][j0].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+1][j0].l);

         if ((VerticalSideNodes[i0+3][j0+1].l!=nullptr)&&(VerticalSideNodes[i0+3][j0+1].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+3][j0+1].l);

         if ((VerticalSideNodes[i0+2][j0+1].l!=nullptr)&&(VerticalSideNodes[i0+2][j0+1].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+2][j0+1].l);

         if ((VerticalSideNodes[i0+1][j0+1].l!=nullptr)&&(VerticalSideNodes[i0+1][j0+1].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+1][j0+1].l);

         newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
         magnets.append(newmagnet);


    }


if ( (NNode->l!=nullptr) && (NNode->l->type==split_R_D))
    {


         int i0 = RailStart.i-3;
         int j0 = RailStart.j;

         DMagnet * newmagnet = new DMagnet;
         newmagnet->address.i=i0;
         newmagnet->address.j=j0;
         newmagnet->address.type=NetworkNodeTypes::vert;
         newmagnet->newelement = new class NjunctionL();

         static_cast<class NjunctionL*>(newmagnet->newelement)->ld=&(VerticalSideNodes[i0][j0]);
         static_cast<class NjunctionL*>(newmagnet->newelement)->lu=&(VerticalSideNodes[i0][j0-1]);
         static_cast<class NjunctionL*>(newmagnet->newelement)->ru=&(VerticalSideNodes[i0+3][j0-1]);
         static_cast<class NjunctionL*>(newmagnet->newelement)->rd=&(VerticalSideNodes[i0+3][j0]);

         static_cast<class NjunctionL*>(newmagnet->newelement)->mid_r_u=&(VerticalSideNodes[i0+2][j0-1]);
         static_cast<class NjunctionL*>(newmagnet->newelement)->mid_r_d=&(VerticalSideNodes[i0+2][j0]);

         static_cast<class NjunctionL*>(newmagnet->newelement)->i = i0;
         static_cast<class NjunctionL*>(newmagnet->newelement)->j = j0-1;

         QList<DNetworkListElement*> allowed;

         allowed.append(NNode->l);


         if ((VerticalSideNodes[i0+3][j0].l!=nullptr)&&(VerticalSideNodes[i0+3][j0].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+3][j0].l);

         if ((VerticalSideNodes[i0+2][j0].l!=nullptr)&&(VerticalSideNodes[i0+2][j0].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+2][j0].l);

         if ((VerticalSideNodes[i0+1][j0].l!=nullptr)&&(VerticalSideNodes[i0+1][j0].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+1][j0].l);

         if ((VerticalSideNodes[i0+3][j0-1].l!=nullptr)&&(VerticalSideNodes[i0+3][j0-1].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+3][j0-1].l);

         if ((VerticalSideNodes[i0+2][j0-1].l!=nullptr)&&(VerticalSideNodes[i0+2][j0-1].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+2][j0-1].l);

         if ((VerticalSideNodes[i0+1][j0-1].l!=nullptr)&&(VerticalSideNodes[i0+1][j0-1].l->type==straightHoriz))
             allowed.append(VerticalSideNodes[i0+1][j0-1].l);

         newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
         magnets.append(newmagnet);


    }



}
