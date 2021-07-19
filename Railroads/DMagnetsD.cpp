#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_D()
{
      DHorizontalSideNode * NNode = &(HorizontalSideNodes[RailStart.i][RailStart.j]);
      // =================== principal down ================
      if (NNode->d==nullptr)
          {
              DMagnet* prevptr = nullptr;
              int i0 = RailStart.i;
              int j0 = RailStart.j+1;

              bool flag = true;
              do
                  {
                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=i0;
                      newmagnet->address.j=j0;
                      newmagnet->address.type=NetworkNodeTypes::horiz;
                      newmagnet->newelement = new class straightVert();
                      static_cast<class straightVert*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0-1]);
                      static_cast<class straightVert*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0]);
                      static_cast<class straightVert*>(newmagnet->newelement)->i=i0;
                      static_cast<class straightVert*>(newmagnet->newelement)->j=j0-1;
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

                      j0 = j0 + 1;

                  }
              while (flag);

                j0 = j0-1;
              //========================== CHECK FOR CONNECTION WITH JUNCTIONS =====================================

               // ========================       JUNCTION U UL =======================
              if ( (HorizontalSideNodes[i0][j0+1].u!=nullptr)&&(HorizontalSideNodes[i0][j0+1].u->type==RailTypes::tight_DR_D))
                  {

                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=i0;
                      newmagnet->address.j=j0+1;
                      newmagnet->address.type=NetworkNodeTypes::horiz;
                      newmagnet->newelement = new class junctionU_UL();

                      static_cast<class junctionU_UL*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0-1]);;
                      static_cast<class junctionU_UL*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0+1]);
                      static_cast<class junctionU_UL*>(newmagnet->newelement)->ul=&(CornerNodes[i0-1][j0-2]);

                      static_cast<class junctionU_UL*>(newmagnet->newelement)->i = i0-1;
                      static_cast<class junctionU_UL*>(newmagnet->newelement)->j = j0-2;

                      QList<DNetworkListElement*> allowed;
                      allowed.append(HorizontalSideNodes[i0][j0+1].u);

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

              // ========================       JUNCTION U UR =======================
              if ( (HorizontalSideNodes[i0][j0+1].u!=nullptr)&&(HorizontalSideNodes[i0][j0+1].u->type==RailTypes::tight_DL_D))
                  {

                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=i0;
                      newmagnet->address.j=j0+1;
                      newmagnet->address.type=NetworkNodeTypes::horiz;
                      newmagnet->newelement = new class junctionU_UR();

                      static_cast<class junctionU_UR*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0+1]);;
                      static_cast<class junctionU_UR*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0-1]);
                      static_cast<class junctionU_UR*>(newmagnet->newelement)->ur=&(CornerNodes[i0+2][j0-2]);

                      static_cast<class junctionU_UR*>(newmagnet->newelement)->i = i0;
                      static_cast<class junctionU_UR*>(newmagnet->newelement)->j = j0-2;

                      QList<DNetworkListElement*> allowed;
                      allowed.append(HorizontalSideNodes[i0][j0+1].u);

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



      // ================ tight D DL  =  tight UR U ===============
      if (NNode->d==nullptr)
          {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i-1;
              newmagnet->address.j=RailStart.j+3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class tight_UR_U();
              static_cast<class tight_UR_U*>(newmagnet->newelement)->u=NNode;
              static_cast<class tight_UR_U*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-1][RailStart.j+3]);
              static_cast<class tight_UR_U*>(newmagnet->newelement)->i = RailStart.i-1;
              static_cast<class tight_UR_U*>(newmagnet->newelement)->j = RailStart.j;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
          }

      // upgrade tight d dl to juntion d dl
      if ((NNode->d!=nullptr)&&(NNode->d->type==RailTypes::tight_UR_U))
          {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i;
              newmagnet->address.j=RailStart.j+2;
              newmagnet->address.type=NetworkNodeTypes::horiz;
              newmagnet->newelement = new class junctionD_DL();
              static_cast<class junctionD_DL*>(newmagnet->newelement)->u=NNode;
              static_cast<class junctionD_DL*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i][RailStart.j+2]);
              static_cast<class junctionD_DL*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-1][RailStart.j+3]);
              static_cast<class junctionD_DL*>(newmagnet->newelement)->i = RailStart.i-1;
              static_cast<class junctionD_DL*>(newmagnet->newelement)->j = RailStart.j;

              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->d);

              if ((HorizontalSideNodes[RailStart.i][RailStart.j+1].d!=nullptr) && (HorizontalSideNodes[RailStart.i][RailStart.j+1].d->type==RailTypes::straightVert))
                  allowed.append (HorizontalSideNodes[RailStart.i][RailStart.j+1].d);
              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
              magnets.append(newmagnet);
          }




      // ================ tight D DR  =  tight UL U ===============
      if (NNode->d==nullptr)
          {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i+2;
              newmagnet->address.j=RailStart.j+3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class tight_UL_U();
              static_cast<class tight_UL_U*>(newmagnet->newelement)->u=NNode;
              static_cast<class tight_UL_U*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+3]);
              static_cast<class tight_UL_U*>(newmagnet->newelement)->i = RailStart.i;
              static_cast<class tight_UL_U*>(newmagnet->newelement)->j = RailStart.j;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
          }


        // =================== UPGRADE TIGHT D_DR to JUNCTION D DR===========
      if ((NNode->d!=nullptr)&&(NNode->d->type==RailTypes::tight_U_UL))
          {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=NNode->i;
              newmagnet->address.j=NNode->j+2;
              newmagnet->address.type=NetworkNodeTypes::horiz;
              newmagnet->newelement = new class junctionD_DR();

              static_cast<class junctionD_DR*>(newmagnet->newelement)->u=NNode;;
              static_cast<class junctionD_DR*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i][RailStart.j+2]);
              static_cast<class junctionD_DR*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+3]);

              static_cast<class junctionD_DR*>(newmagnet->newelement)->i = RailStart.i;
              static_cast<class junctionD_DR*>(newmagnet->newelement)->j = RailStart.j;

              QList<DNetworkListElement*> allowed;
              if ((HorizontalSideNodes[RailStart.i][RailStart.j+1].d!=nullptr)&&(HorizontalSideNodes[RailStart.i][RailStart.j+1].d->type==RailTypes::straightVert))
                      allowed.append(HorizontalSideNodes[RailStart.i][RailStart.j+1].d);
              allowed.append(NNode->d);
            //  allowed.append(HorizontalSideNodes[i0][j0].d);

              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

              //if (newmagnet->valid)
              //magnets.append(newmagnet);
          }


     //============  UPGRADE STRAIGHT DOWN TO JUNCTION D_DR ===================
      if ((NNode->d!=nullptr)&&(NNode->d->type==RailTypes::straightVert))
      {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i+2;
              newmagnet->address.j=RailStart.j+3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class junctionD_DR();
              static_cast<class junctionD_DR*>(newmagnet->newelement)->u=NNode;
              static_cast<class junctionD_DR*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i][RailStart.j+2]);
              static_cast<class junctionD_DR*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+2][RailStart.j+3]);
              static_cast<class junctionD_DR*>(newmagnet->newelement)->i = RailStart.i;
              static_cast<class junctionD_DR*>(newmagnet->newelement)->j = RailStart.j;

              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->d);

              if ((HorizontalSideNodes[RailStart.i][RailStart.j+1].d!=nullptr) && (HorizontalSideNodes[RailStart.i][RailStart.j+1].d->type==RailTypes::straightVert))
                  allowed.append (HorizontalSideNodes[RailStart.i][RailStart.j+1].d);
              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
              magnets.append(newmagnet);
        }


      //============  UPGRADE STRAIGHT DOWN TO JUNCTION D_DL ===================
       if ((NNode->d!=nullptr)&&(NNode->d->type==RailTypes::straightVert))
       {
               DMagnet * newmagnet = new DMagnet;
               newmagnet->address.i=RailStart.i-1;
               newmagnet->address.j=RailStart.j+3;
               newmagnet->address.type=NetworkNodeTypes::corner;
               newmagnet->newelement = new class junctionD_DL();
               static_cast<class junctionD_DL*>(newmagnet->newelement)->u=NNode;
               static_cast<class junctionD_DL*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i][RailStart.j+2]);
               static_cast<class junctionD_DL*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i-1][RailStart.j+3]);
               static_cast<class junctionD_DL*>(newmagnet->newelement)->i = RailStart.i-1;
               static_cast<class junctionD_DL*>(newmagnet->newelement)->j = RailStart.j;

               QList<DNetworkListElement*> allowed;
               allowed.append(NNode->d);

               if ((HorizontalSideNodes[RailStart.i][RailStart.j+1].d!=nullptr) && (HorizontalSideNodes[RailStart.i][RailStart.j+1].d->type==RailTypes::straightVert))
                   allowed.append (HorizontalSideNodes[RailStart.i][RailStart.j+1].d);
               newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
               magnets.append(newmagnet);
         }




}
