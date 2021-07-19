#include <dmainscreen.h>

void DMainScreen::PREPARE_MAGNETS_U()
{
      DHorizontalSideNode * NNode = &(HorizontalSideNodes[RailStart.i][RailStart.j]);
      // ===================    principal up ================
      if (NNode->u==nullptr)
          {
              DMagnet* prevptr = nullptr;
              int i0 = RailStart.i;
              int j0 = RailStart.j-1;

              bool flag = true;
              do
                  {
                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=i0;
                      newmagnet->address.j=j0;
                      newmagnet->address.type=NetworkNodeTypes::horiz;
                      newmagnet->newelement = new class straightVert();
                      static_cast<class straightVert*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0+1]);
                      static_cast<class straightVert*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0]);
                      static_cast<class straightVert*>(newmagnet->newelement)->i=i0;
                      static_cast<class straightVert*>(newmagnet->newelement)->j=j0;
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

                      j0 = j0 - 1;

                  }
              while (flag);


              j0 = j0+1;
               // ===================  check for connections with junctions================

              // =================== junction D_DR ====================
              if ( (HorizontalSideNodes[i0][j0-1].d!=nullptr)&&(HorizontalSideNodes[i0][j0-1].d->type==RailTypes::tight_UL_U))
                  {

                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=i0;
                      newmagnet->address.j=j0-1;
                      newmagnet->address.type=NetworkNodeTypes::horiz;
                      newmagnet->newelement = new class junctionD_DR();

                      static_cast<class junctionD_DR*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0-1]);;
                      static_cast<class junctionD_DR*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0+1]);
                      static_cast<class junctionD_DR*>(newmagnet->newelement)->dr=&(CornerNodes[i0+2][j0+2]);

                      static_cast<class junctionD_DR*>(newmagnet->newelement)->i = i0;
                      static_cast<class junctionD_DR*>(newmagnet->newelement)->j = j0-1;

                      QList<DNetworkListElement*> allowed;
                      allowed.append(HorizontalSideNodes[i0][j0-1].d);
                    //  allowed.append(HorizontalSideNodes[i0][j0].d);

                      newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                      newmagnet->prev = prevptr;

                     // flag = newmagnet->valid;
                      flag = true;
                      if (flag)
                          {
                              magnets.append(newmagnet);
                              prevptr = (magnets.last());
                          }
                      //if (newmagnet->valid)
                      //magnets.append(newmagnet);
                  }

              // =================== junction D_DL ====================
              if ( (HorizontalSideNodes[i0][j0-1].d!=nullptr)&&(HorizontalSideNodes[i0][j0-1].d->type==RailTypes::tight_UR_U))
                  {

                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=i0;
                      newmagnet->address.j=j0-1;
                      newmagnet->address.type=NetworkNodeTypes::horiz;
                      newmagnet->newelement = new class junctionD_DL();

                      static_cast<class junctionD_DL*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0-1]);;
                      static_cast<class junctionD_DL*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0+1]);
                      static_cast<class junctionD_DL*>(newmagnet->newelement)->dl=&(CornerNodes[i0-1][j0+2]);

                      static_cast<class junctionD_DL*>(newmagnet->newelement)->i = i0-1;
                      static_cast<class junctionD_DL*>(newmagnet->newelement)->j = j0-1;

                      QList<DNetworkListElement*> allowed;
                      allowed.append(HorizontalSideNodes[i0][j0-1].d);
                    //  allowed.append(HorizontalSideNodes[i0][j0].d);

                      newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);
                      newmagnet->prev = prevptr;

                     // flag = newmagnet->valid;
                      flag = true;
                      if (flag)
                          {
                              magnets.append(newmagnet);
                              prevptr = (magnets.last());
                          }
                      //if (newmagnet->valid)
                      //magnets.append(newmagnet);
                  }

          }




    // =================== tight U UR = tight DL_D + UPGRADE TO junction DL _D====================
      if (NNode->u==nullptr)
          {
              if  ( ((CornerNodes[RailStart.i+2][RailStart.j-3].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-3].dl->type==diagDLUR))||
                     ((CornerNodes[RailStart.i+1][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j-2].dl->type==diagDLUR)) )
                                {


                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=RailStart.i+2;
                      newmagnet->address.j=RailStart.j-3;
                      newmagnet->address.type=NetworkNodeTypes::corner;
                      newmagnet->newelement = new class junctionDL_D();

                      static_cast<class junctionDL_D*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-3]);
                      static_cast<class junctionDL_D*>(newmagnet->newelement)->dl=&(CornerNodes[RailStart.i][RailStart.j-1]);
                      static_cast<class junctionDL_D*>(newmagnet->newelement)->d=&(HorizontalSideNodes[RailStart.i][RailStart.j]);

                      static_cast<class junctionDL_D*>(newmagnet->newelement)->i = RailStart.i;
                      static_cast<class junctionDL_D*>(newmagnet->newelement)->j = RailStart.j-3;

                      QList<DNetworkListElement*> allowed;


                      if ((CornerNodes[RailStart.i+2][RailStart.j-3].dl!=nullptr)&&(CornerNodes[RailStart.i+2][RailStart.j-3].dl->type==diagDLUR))
                          allowed.append(CornerNodes[RailStart.i+2][RailStart.j-3].dl);

                      if ((CornerNodes[RailStart.i+1][RailStart.j-2].dl!=nullptr)&&(CornerNodes[RailStart.i+1][RailStart.j-2].dl->type==diagDLUR))
                          allowed.append(CornerNodes[RailStart.i+1][RailStart.j-2].dl);

                      newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                      magnets.append(newmagnet);

                  }
              else {




              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i+2;
              newmagnet->address.j=RailStart.j-3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class tight_DL_D();
              static_cast<class tight_DL_D*>(newmagnet->newelement)->d=NNode;
              static_cast<class tight_DL_D*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-3]);
              static_cast<class tight_DL_D*>(newmagnet->newelement)->i = RailStart.i;
              static_cast<class tight_DL_D*>(newmagnet->newelement)->j = RailStart.j-3;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
                  }
          }

      // ================= tight U UL = tight DR D + UPGRADE TO JUNCTION DR_D==============
      if (NNode->u==nullptr)
          {
              if  ( ((CornerNodes[RailStart.i-1][RailStart.j-3].dr!=nullptr)&&(CornerNodes[RailStart.i-1][RailStart.j-3].dr->type==diagDRUL))||
                    ((CornerNodes[RailStart.i][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i][RailStart.j-2].dr->type==diagDRUL)) )
                  {

                      DMagnet * newmagnet = new DMagnet;
                      newmagnet->address.i=RailStart.i-1;
                      newmagnet->address.j=RailStart.j-3;
                      newmagnet->address.type=NetworkNodeTypes::corner;
                      newmagnet->newelement = new class junctionDR_D();
                      static_cast<class junctionDR_D*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-1][RailStart.j-3]);
                      static_cast<class junctionDR_D*>(newmagnet->newelement)->dr=&(CornerNodes[RailStart.i+1][RailStart.j-1]);
                      static_cast<class junctionDR_D*>(newmagnet->newelement)->d=NNode;

                      static_cast<class junctionDR_D*>(newmagnet->newelement)->i=RailStart.i-1;
                      static_cast<class junctionDR_D*>(newmagnet->newelement)->j=RailStart.j-3;

                      QList<DNetworkListElement*> allowed;

                      if((CornerNodes[RailStart.i-1][RailStart.j-3].dr!=nullptr)&&(CornerNodes[RailStart.i-1][RailStart.j-3].dr->type==diagDRUL))
                          allowed.append(CornerNodes[RailStart.i-1][RailStart.j-3].dr);

                      if((CornerNodes[RailStart.i][RailStart.j-2].dr!=nullptr)&&(CornerNodes[RailStart.i][RailStart.j-2].dr->type==diagDRUL))
                          allowed.append(CornerNodes[RailStart.i][RailStart.j-2].dr);

                     newmagnet->valid=check_obstruction_conditional(newmagnet->newelement,allowed);
                     magnets.append(newmagnet);

                  }

              else {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i-1;
              newmagnet->address.j=RailStart.j-3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class tight_DR_D();
              static_cast<class tight_DR_D*>(newmagnet->newelement)->d=NNode;
              static_cast<class tight_DR_D*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-1][RailStart.j-3]);
              static_cast<class tight_DR_D*>(newmagnet->newelement)->i = RailStart.i-1;
              static_cast<class tight_DR_D*>(newmagnet->newelement)->j = RailStart.j-3;
              newmagnet->valid = check_obstruction(newmagnet->newelement);

              magnets.append(newmagnet);
                  }
          }

      // ==== UP - UPGRADE VERT TO JUNCTIONS =============

      if ( (NNode->u!=nullptr) && (NNode->u->type==straightVert))
          // junction U_UL
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i-1;
              newmagnet->address.j=RailStart.j-3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class junctionU_UL();

              static_cast<class junctionU_UL*>(newmagnet->newelement)->d=NNode;
              static_cast<class junctionU_UL*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i][RailStart.j-2]);;
              static_cast<class junctionU_UL*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-1][RailStart.j-3]);

              static_cast<class junctionU_UL*>(newmagnet->newelement)->i = RailStart.i-1;
              static_cast<class junctionU_UL*>(newmagnet->newelement)->j = RailStart.j-3;
              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->u);

              if ( (HorizontalSideNodes[RailStart.i][RailStart.j-2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i][RailStart.j-2].d->type==straightVert)  )
                  allowed.append(HorizontalSideNodes[RailStart.i][RailStart.j-2].d);

              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

              magnets.append(newmagnet);
          }

      // junction U_UR
      if ( (NNode->u!=nullptr) && (NNode->u->type==straightVert))
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i+2;
              newmagnet->address.j=RailStart.j-3;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class junctionU_UR();

              static_cast<class junctionU_UR*>(newmagnet->newelement)->d=NNode;
              static_cast<class junctionU_UR*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i][RailStart.j-2]);;
              static_cast<class junctionU_UR*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-3]);

              static_cast<class junctionU_UR*>(newmagnet->newelement)->i = RailStart.i;
              static_cast<class junctionU_UR*>(newmagnet->newelement)->j = RailStart.j-3;
              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->u);

              if ( (HorizontalSideNodes[RailStart.i][RailStart.j-2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i][RailStart.j-2].d->type==straightVert)  )
                  allowed.append(HorizontalSideNodes[RailStart.i][RailStart.j-2].d);

              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

              magnets.append(newmagnet);
          }

      // ==== UP - UPGRADE  tight U UL TO JUNCTION =============
      if ( (NNode->u!=nullptr) && (NNode->u->type==tight_DR_D))
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i;
              newmagnet->address.j=RailStart.j-2;
              newmagnet->address.type=NetworkNodeTypes::horiz;
              newmagnet->newelement = new class junctionU_UL();

              static_cast<class junctionU_UL*>(newmagnet->newelement)->d=NNode;
              static_cast<class junctionU_UL*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i][RailStart.j-2]);;
              static_cast<class junctionU_UL*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i-1][RailStart.j-3]);

              static_cast<class junctionU_UL*>(newmagnet->newelement)->i = RailStart.i-1;
              static_cast<class junctionU_UL*>(newmagnet->newelement)->j = RailStart.j-3;
              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->u);

              if ( (HorizontalSideNodes[RailStart.i][RailStart.j-2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i][RailStart.j-2].d->type==straightVert)  )
                  allowed.append(HorizontalSideNodes[RailStart.i][RailStart.j-2].d);

              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

              magnets.append(newmagnet);
          }

      // ==== UP - UPGRADE  tight U UR TO JUNCTION =============
      if ( (NNode->u!=nullptr) && (NNode->u->type==tight_DL_D))
          {

              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i;
              newmagnet->address.j=RailStart.j-2;
              newmagnet->address.type=NetworkNodeTypes::horiz;
              newmagnet->newelement = new class junctionU_UR();

              static_cast<class junctionU_UR*>(newmagnet->newelement)->d=NNode;
              static_cast<class junctionU_UR*>(newmagnet->newelement)->u=&(HorizontalSideNodes[RailStart.i][RailStart.j-2]);;
              static_cast<class junctionU_UR*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+2][RailStart.j-3]);

              static_cast<class junctionU_UR*>(newmagnet->newelement)->i = RailStart.i;
              static_cast<class junctionU_UR*>(newmagnet->newelement)->j = RailStart.j-3;
              QList<DNetworkListElement*> allowed;
              allowed.append(NNode->u);

              if ( (HorizontalSideNodes[RailStart.i][RailStart.j-2].d!=nullptr)&&(HorizontalSideNodes[RailStart.i][RailStart.j-2].d->type==straightVert)  )
                  allowed.append(HorizontalSideNodes[RailStart.i][RailStart.j-2].d);

              newmagnet->valid = check_obstruction_conditional(newmagnet->newelement,allowed);

              magnets.append(newmagnet);
          }


}
