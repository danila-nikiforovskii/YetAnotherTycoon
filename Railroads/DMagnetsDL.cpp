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


        // check for connections with splits

    if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].ur!=nullptr)&&(CornerNodes[i0][j0].ur->type==split_DL_D))
        {
            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class NjunctionUR();

            static_cast<class NjunctionUR*>(newmagnet->newelement)->uru=&(CornerNodes[i0+2][j0-3]);
            static_cast<class NjunctionUR*>(newmagnet->newelement)->urd=&(CornerNodes[i0+2][j0-2]);

            static_cast<class NjunctionUR*>(newmagnet->newelement)->dlu=&(CornerNodes[i0][j0-1]);
            static_cast<class NjunctionUR*>(newmagnet->newelement)->dld=&(CornerNodes[i0][j0]);

            static_cast<class NjunctionUR*>(newmagnet->newelement)->i = i0;
            static_cast<class NjunctionUR*>(newmagnet->newelement)->j = j0-3;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].ur);

            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);

        }

    if ( CornerLimits(i0,j0) && (CornerNodes[i0][j0].ur!=nullptr)&&(CornerNodes[i0][j0].ur->type==split_DL_L))
        {
            DMagnet * newmagnet = new DMagnet();
            newmagnet->address.i=i0;
            newmagnet->address.j=j0;
            newmagnet->address.type=NetworkNodeTypes::corner;
            newmagnet->newelement = new class NjunctionDL();

            static_cast<class NjunctionDL*>(newmagnet->newelement)->url=&(CornerNodes[i0+2][j0-2]);
            static_cast<class NjunctionDL*>(newmagnet->newelement)->urr=&(CornerNodes[i0+3][j0-2]);

            static_cast<class NjunctionDL*>(newmagnet->newelement)->dll=&(CornerNodes[i0][j0]);
            static_cast<class NjunctionDL*>(newmagnet->newelement)->dlr=&(CornerNodes[i0+1][j0]);

            static_cast<class NjunctionDL*>(newmagnet->newelement)->i = i0;
            static_cast<class NjunctionDL*>(newmagnet->newelement)->j = j0-2;

            QList<DNetworkListElement*> allowed;
            allowed.append(CornerNodes[i0][j0].ur);

            newmagnet->prev = prevptr;
            newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);

        }

        }
    // UPGRADE STRAIGHT DLUR to JUNCTION_DL_D

     if ( (NNode->dl!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr)&&(NNode->dl->type==diagDLUR) )
         {



             DMagnet * newmagnet = new DMagnet;
             newmagnet->address.i=RailStart.i-2;
             newmagnet->address.j=RailStart.j+3;
             newmagnet->address.type=NetworkNodeTypes::horiz;
             newmagnet->newelement = new class junctionDL_D();

             static_cast<class junctionDL_D*>(newmagnet->newelement)->ur=NNode;
             static_cast<class junctionDL_D*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
             static_cast<class junctionDL_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+3]);

             static_cast<class junctionDL_D*>(newmagnet->newelement)->i = RailStart.i-2;
             static_cast<class junctionDL_D*>(newmagnet->newelement)->j = RailStart.j;

             QList<DNetworkListElement*> allowed;
             allowed.append(NNode->dl);

             if ((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagDLUR))
                 allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);

             newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
             magnets.append(newmagnet);

         }

     // UPGRADE STRAIGHT DLUR to JUNCTION_DL_L

      if ( (NNode->dl!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr)&&(NNode->dl->type==diagDLUR) )
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i-3;
              newmagnet->address.j=RailStart.j+1;
              newmagnet->address.type=NetworkNodeTypes::vert;
              newmagnet->newelement = new class junctionDL_L();

              static_cast<class junctionDL_L*>(newmagnet->newelement)->ur=NNode;
              static_cast<class junctionDL_L*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
              static_cast<class junctionDL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j+1]);

              static_cast<class junctionDL_L*>(newmagnet->newelement)->i = RailStart.i-3;
              static_cast<class junctionDL_L*>(newmagnet->newelement)->j = RailStart.j;

              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->dl);

              if ((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagDLUR))
                  allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);

              newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
              magnets.append(newmagnet);

          }



      // UPGRADE STRAIGHT DLUR to SPLIT_DL_D + FURTHER TO NJunctionUR

       if ( (NNode->dl!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr)&&(NNode->dl->type==diagDLUR) )
           {


               if   (  ((CornerNodes[RailStart.i-2][RailStart.j+3].ur)&&(CornerNodes[RailStart.i-2][RailStart.j+3].ur->type==diagURDL))||
                       ((CornerNodes[RailStart.i-1][RailStart.j+2].ur)&&(CornerNodes[RailStart.i-1][RailStart.j+2].ur->type==diagURDL)))
                   {

                       DMagnet * newmagnet = new DMagnet;
                       newmagnet->address.i=RailStart.i-2;
                       newmagnet->address.j=RailStart.j+3;
                       newmagnet->address.type=NetworkNodeTypes::corner;

                       newmagnet->newelement= new class NjunctionUR();

                       static_cast<class NjunctionUR*>(newmagnet->newelement)->uru=NNode;
                       static_cast<class NjunctionUR*>(newmagnet->newelement)->urd=&(CornerNodes[RailStart.i][RailStart.j+1]);
                       static_cast<class NjunctionUR*>(newmagnet->newelement)->dlu=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
                       static_cast<class NjunctionUR*>(newmagnet->newelement)->dld=&(CornerNodes[RailStart.i-2][RailStart.j+3]);
                           static_cast<class NjunctionUR*>(newmagnet->newelement)->i = RailStart.i-2;
                          static_cast<class NjunctionUR*>(newmagnet->newelement)->j = RailStart.j;

                       QList<DNetworkListElement*> allowed;
                       if((CornerNodes[RailStart.i-2][RailStart.j+3].ur!=nullptr) && (CornerNodes[RailStart.i-2][RailStart.j+3].ur->type==diagURDL))
                           allowed.append(CornerNodes[RailStart.i-2][RailStart.j+3].ur);
                       if((CornerNodes[RailStart.i-1][RailStart.j+2].ur!=nullptr) && (CornerNodes[RailStart.i-1][RailStart.j+2].ur->type==diagURDL))
                           allowed.append(CornerNodes[RailStart.i-1][RailStart.j+2].ur);

                       if((CornerNodes[RailStart.i][RailStart.j].dl!=nullptr) && (CornerNodes[RailStart.i][RailStart.j].dl->type==diagURDL))
                           allowed.append(CornerNodes[RailStart.i][RailStart.j].dl);
                       if((CornerNodes[RailStart.i-1][RailStart.j+1].dl!=nullptr) && (CornerNodes[RailStart.i-1][RailStart.j+1].dl->type==diagURDL))
                           allowed.append(CornerNodes[RailStart.i-1][RailStart.j+1].dl);



                       newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                       magnets.append(newmagnet);
                   }

  else
                   {
               DMagnet * newmagnet = new DMagnet;
               newmagnet->address.i=RailStart.i-2;
               newmagnet->address.j=RailStart.j+3;
               newmagnet->address.type=NetworkNodeTypes::corner;
               newmagnet->newelement = new class splitDL_D();

               static_cast<class splitDL_D*>(newmagnet->newelement)->ur=NNode;
               static_cast<class splitDL_D*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
               static_cast<class splitDL_D*>(newmagnet->newelement)->d=&(CornerNodes[RailStart.i-2][RailStart.j+3]);

               static_cast<class splitDL_D*>(newmagnet->newelement)->i = RailStart.i-2;
               static_cast<class splitDL_D*>(newmagnet->newelement)->j = RailStart.j;

               QList<DNetworkListElement*> allowed;
               allowed.append(NNode->dl);

               if ((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagDLUR))
                   allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);

               newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
               magnets.append(newmagnet);
                   }
           }


       // UPGRADE STRAIGHT DLUR to SPLIT_DL_L+ FURTHER TO NJunctionDL

        if ( (NNode->dl!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr)&&(NNode->dl->type==diagDLUR) )
            {

                if   (  ((CornerNodes[RailStart.i-3][RailStart.j+2].ur)&&(CornerNodes[RailStart.i-3][RailStart.j+2].ur->type==diagURDL))||
                        ((CornerNodes[RailStart.i-2][RailStart.j+1].ur)&&(CornerNodes[RailStart.i-2][RailStart.j+1].ur->type==diagURDL)))
                    {

                        DMagnet * newmagnet = new DMagnet;
                        newmagnet->address.i=RailStart.i-3;
                        newmagnet->address.j=RailStart.j+2;
                        newmagnet->address.type=NetworkNodeTypes::corner;

                        newmagnet->newelement= new class NjunctionDL();

                        static_cast<class NjunctionDL*>(newmagnet->newelement)->urr=NNode;
                        static_cast<class NjunctionDL*>(newmagnet->newelement)->url=&(CornerNodes[RailStart.i+1][RailStart.j]);
                        static_cast<class NjunctionDL*>(newmagnet->newelement)->dll=&(CornerNodes[RailStart.i-3][RailStart.j+2]);
                        static_cast<class NjunctionDL*>(newmagnet->newelement)->dlr=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
                            static_cast<class NjunctionDL*>(newmagnet->newelement)->i = RailStart.i-3;
                           static_cast<class NjunctionDL*>(newmagnet->newelement)->j = RailStart.j;

                        QList<DNetworkListElement*> allowed;
                        if((CornerNodes[RailStart.i-3][RailStart.j+2].ur!=nullptr) && (CornerNodes[RailStart.i-3][RailStart.j+2].ur->type==diagURDL))
                            allowed.append(CornerNodes[RailStart.i-3][RailStart.j+2].ur);
                        if((CornerNodes[RailStart.i-2][RailStart.j+1].ur!=nullptr) && (CornerNodes[RailStart.i-2][RailStart.j+1].ur->type==diagURDL))
                            allowed.append(CornerNodes[RailStart.i-2][RailStart.j+1].ur);

                        if((CornerNodes[RailStart.i][RailStart.j].dl!=nullptr) && (CornerNodes[RailStart.i][RailStart.j].dl->type==diagURDL))
                            allowed.append(CornerNodes[RailStart.i][RailStart.j].dl);
                        if((CornerNodes[RailStart.i-1][RailStart.j+1].dl!=nullptr) && (CornerNodes[RailStart.i-1][RailStart.j+1].dl->type==diagURDL))
                            allowed.append(CornerNodes[RailStart.i-1][RailStart.j+1].dl);



                        newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                        magnets.append(newmagnet);
                    }

   else
                    {
                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-3;
                newmagnet->address.j=RailStart.j+2;
                newmagnet->address.type=NetworkNodeTypes::corner;
                newmagnet->newelement = new class splitDL_L();

                static_cast<class splitDL_L*>(newmagnet->newelement)->ur=NNode;
                static_cast<class splitDL_L*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
                static_cast<class splitDL_L*>(newmagnet->newelement)->l=&(CornerNodes[RailStart.i-3][RailStart.j+2]);

                static_cast<class splitDL_L*>(newmagnet->newelement)->i = RailStart.i-3;
                static_cast<class splitDL_L*>(newmagnet->newelement)->j = RailStart.j;

                QList<DNetworkListElement*> allowed;
                allowed.append(NNode->dl);

                if ((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagDLUR))
                    allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);

                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);
                    }
            }



      // UPGRADE  tight DL L to JUNCTION_DL_L

       if ( (NNode->dl!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr)&&(NNode->dl->type==tight_DL_L) )
           {

               DMagnet * newmagnet = new DMagnet;
               newmagnet->address.i=RailStart.i-2;
               newmagnet->address.j=RailStart.j+2;
               newmagnet->address.type=NetworkNodeTypes::corner;
               newmagnet->newelement = new class junctionDL_L();

               static_cast<class junctionDL_L*>(newmagnet->newelement)->ur=NNode;
               static_cast<class junctionDL_L*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
               static_cast<class junctionDL_L*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i-3][RailStart.j+1]);

               static_cast<class junctionDL_L*>(newmagnet->newelement)->i = RailStart.i-3;
               static_cast<class junctionDL_L*>(newmagnet->newelement)->j = RailStart.j;

               QList<DNetworkListElement*> allowed;
               allowed.append(NNode->dl);

               if ((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagDLUR))
                   allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);

               newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
               magnets.append(newmagnet);

           }


     // UPGRADE  tight DL D to JUNCTION_DL_D

      if ( (NNode->dl!=nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr)&&(NNode->dl->type==tight_DL_D) )
          {



              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i-2;
              newmagnet->address.j=RailStart.j+2;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class junctionDL_D();

              static_cast<class junctionDL_D*>(newmagnet->newelement)->ur=NNode;
              static_cast<class junctionDL_D*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
              static_cast<class junctionDL_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+3]);

              static_cast<class junctionDL_D*>(newmagnet->newelement)->i = RailStart.i-2;
              static_cast<class junctionDL_D*>(newmagnet->newelement)->j = RailStart.j;

              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->dl);

              if ((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr)&&(CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagDLUR))
                  allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);

              newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
              magnets.append(newmagnet);

          }



 // ===================== TIGHT DL_D + UPGRADE TO junction U_UR ================
    if ( (NNode->dl==nullptr)&&(NNode->ul==nullptr)&&(NNode->dr==nullptr) )
        {

            // check for junction aside...

             if ((CornerNodes[RailStart.i+1][RailStart.j].dl!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j].dl->type==junction_U_UR))
                 {

             DMagnet * newmagnet = new DMagnet;
             newmagnet->address.i=RailStart.i-2;
             newmagnet->address.j=RailStart.j+3;
             newmagnet->address.type=NetworkNodeTypes::horiz;
             newmagnet->newelement = new class TwoTrackJunctionU_UR();

             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->dl=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+3]);;
             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->ur=&(HorizontalSideNodes[RailStart.i-1][RailStart.j]);;
             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->ul=&(HorizontalSideNodes[RailStart.i-2][RailStart.j]);;
             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->dr=&(HorizontalSideNodes[RailStart.i-1][RailStart.j+3]);;

             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->urr=&(CornerNodes[RailStart.i+1][RailStart.j]);
             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->url=&(CornerNodes[RailStart.i][RailStart.j]);

             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->ml=&(HorizontalSideNodes[RailStart.i-2][RailStart.j+1]);
             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->mr=&(HorizontalSideNodes[RailStart.i-1][RailStart.j+1]);

             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->i = RailStart.i-2;
             static_cast<class TwoTrackJunctionU_UR*>(newmagnet->newelement)->j = RailStart.j;


             QList<DNetworkListElement*> allowed;

             allowed.append (CornerNodes[RailStart.i+1][RailStart.j].dl );


             if ( (HorizontalSideNodes[RailStart.i-1][RailStart.j].d!=nullptr)&&(HorizontalSideNodes[RailStart.i-1][RailStart.j].d->type==straightVert)  )
                 allowed.append(HorizontalSideNodes[RailStart.i-1][RailStart.j].d);

             if ( (HorizontalSideNodes[RailStart.i-2][RailStart.j].d!=nullptr)&&(HorizontalSideNodes[RailStart.i-2][RailStart.j].d->type==straightVert)  )
                 allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j].d);

             if ( (HorizontalSideNodes[RailStart.i-2][RailStart.j+1].d!=nullptr)&&(HorizontalSideNodes[RailStart.i-2][RailStart.j+1].d->type==straightVert)  )
                 allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j+1].d);

             if ( (HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d->type==straightVert)  )
                 allowed.append(HorizontalSideNodes[RailStart.i-2][RailStart.j+2].d);

             newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

             magnets.append(newmagnet);

                 }
             else
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
                   magnets.append(newmagnet);
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
               }}
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




    // ============= connections to splits
    if  (NNode->dl==nullptr)
        {

            if  (  ((CornerNodes[RailStart.i-3][RailStart.j+2].ur!=nullptr) &&  (CornerNodes[RailStart.i-3][RailStart.j+2].ur->type==diagURDL))||
                   ((CornerNodes[RailStart.i-2][RailStart.j+1].ur!=nullptr) &&  (CornerNodes[RailStart.i-2][RailStart.j+1].ur->type==diagURDL)) )
                {


                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i-3;
                    newmagnet->address.j=RailStart.j+2;
                    newmagnet->address.type=NetworkNodeTypes::corner;
                    newmagnet->newelement = new class splitUR_R();
                    static_cast<class splitUR_R*>(newmagnet->newelement)->r=NNode;
                    static_cast<class splitUR_R*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-3][RailStart.j+2]);
                    static_cast<class splitUR_R*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i-1][RailStart.j]);
                    static_cast<class splitUR_R*>(newmagnet->newelement)->i = RailStart.i-3;
                    static_cast<class splitUR_R*>(newmagnet->newelement)->j = RailStart.j;
                    newmagnet->valid = check_obstruction(newmagnet->newelement);

                    QList<DNetworkListElement*> allowed;

                    if((CornerNodes[RailStart.i-3][RailStart.j+2].ur!=nullptr) && (CornerNodes[RailStart.i-3][RailStart.j+2].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i-3][RailStart.j+2].ur);

                    if((CornerNodes[RailStart.i-2][RailStart.j+1].ur!=nullptr) && (CornerNodes[RailStart.i-2][RailStart.j+1].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i-2][RailStart.j+1].ur);

                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);
                }


            if  (  ((CornerNodes[RailStart.i-2][RailStart.j+3].ur!=nullptr) &&  (CornerNodes[RailStart.i-2][RailStart.j+3].ur->type==diagURDL))||
                   ((CornerNodes[RailStart.i-1][RailStart.j+2].ur!=nullptr) &&  (CornerNodes[RailStart.i-1][RailStart.j+2].ur->type==diagURDL)) )
                {


                    DMagnet * newmagnet = new DMagnet;
                    newmagnet->address.i=RailStart.i-2;
                    newmagnet->address.j=RailStart.j+3;
                    newmagnet->address.type=NetworkNodeTypes::corner;
                    newmagnet->newelement = new class splitUR_U();
                    static_cast<class splitUR_U*>(newmagnet->newelement)->u=NNode;
                    static_cast<class splitUR_U*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-2][RailStart.j+3]);
                    static_cast<class splitUR_U*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i][RailStart.j+1]);
                    static_cast<class splitUR_U*>(newmagnet->newelement)->i = RailStart.i-2;
                    static_cast<class splitUR_U*>(newmagnet->newelement)->j = RailStart.j;

                    QList<DNetworkListElement*> allowed;

                    if((CornerNodes[RailStart.i-2][RailStart.j+3].ur!=nullptr) && (CornerNodes[RailStart.i-2][RailStart.j+3].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i-2][RailStart.j+3].ur);

                    if((CornerNodes[RailStart.i-1][RailStart.j+2].ur!=nullptr) && (CornerNodes[RailStart.i-1][RailStart.j+2].ur->type==diagURDL))
                        allowed.append(CornerNodes[RailStart.i-1][RailStart.j+2].ur);

                    newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                    magnets.append(newmagnet);
                }

    }

// ========= upgrade split UR_U TO NjunctionUR

    if  ( (NNode->dl!=nullptr) && (NNode->dl->type==split_UR_U))
        {

            DMagnet * newmagnet = new DMagnet;
            newmagnet->address.i=RailStart.i-2;
            newmagnet->address.j=RailStart.j+2;
            newmagnet->address.type=NetworkNodeTypes::corner;

            newmagnet->newelement= new class NjunctionUR();

            static_cast<class NjunctionUR*>(newmagnet->newelement)->uru=NNode;
            static_cast<class NjunctionUR*>(newmagnet->newelement)->urd=&(CornerNodes[RailStart.i][RailStart.j+1]);
            static_cast<class NjunctionUR*>(newmagnet->newelement)->dlu=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
            static_cast<class NjunctionUR*>(newmagnet->newelement)->dld=&(CornerNodes[RailStart.i-2][RailStart.j+3]);
                static_cast<class NjunctionUR*>(newmagnet->newelement)->i = RailStart.i-2;
               static_cast<class NjunctionUR*>(newmagnet->newelement)->j = RailStart.j;

            QList<DNetworkListElement*> allowed;
            if((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr) && (CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagURDL))
                allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);
            allowed.append(NNode->dl);
            newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
            magnets.append(newmagnet);

        }



    // ========= upgrade split UR_R TO NjunctionDL

        if  ( (NNode->dl!=nullptr) && (NNode->dl->type==split_UR_R))
            {

                DMagnet * newmagnet = new DMagnet;
                newmagnet->address.i=RailStart.i-2;
                newmagnet->address.j=RailStart.j+2;
                newmagnet->address.type=NetworkNodeTypes::corner;

                newmagnet->newelement= new class NjunctionDL();

                static_cast<class NjunctionDL*>(newmagnet->newelement)->urr=NNode;
                static_cast<class NjunctionDL*>(newmagnet->newelement)->url=&(CornerNodes[RailStart.i-1][RailStart.j]);
                static_cast<class NjunctionDL*>(newmagnet->newelement)->dlr=&(CornerNodes[RailStart.i-2][RailStart.j+2]);
                static_cast<class NjunctionDL*>(newmagnet->newelement)->dll=&(CornerNodes[RailStart.i-1][RailStart.j+2]);
                    static_cast<class NjunctionDL*>(newmagnet->newelement)->i = RailStart.i-3;
                   static_cast<class NjunctionDL*>(newmagnet->newelement)->j = RailStart.j;

                QList<DNetworkListElement*> allowed;
                if((CornerNodes[RailStart.i-2][RailStart.j+2].ur!=nullptr) && (CornerNodes[RailStart.i-2][RailStart.j+2].ur->type==diagURDL))
                    allowed.append(CornerNodes[RailStart.i-2][RailStart.j+2].ur);
                allowed.append(NNode->dl);
                newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                magnets.append(newmagnet);

            }


}
