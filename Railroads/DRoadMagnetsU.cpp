#include <dmainscreen.h>

void DMainScreen::PREPARE_ROAD_MAGNETS_U()
{
      DHorizontalSideNode * NNode = &(HorizontalSideNodes[RailStart.i][RailStart.j]);


// ============ straight up ===========
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
                      newmagnet->newelement = new class RoadVert();
                      static_cast<class RoadVert*>(newmagnet->newelement)->d=&(HorizontalSideNodes[i0][j0+1]);
                      static_cast<class RoadVert*>(newmagnet->newelement)->u=&(HorizontalSideNodes[i0][j0]);
                      static_cast<class RoadVert*>(newmagnet->newelement)->i=i0;
                      static_cast<class RoadVert*>(newmagnet->newelement)->j=j0;
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

        }

// ================ tight corners
      if (NNode->u==nullptr)
      {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i+1;
              newmagnet->address.j=RailStart.j-1;
              newmagnet->address.type=NetworkNodeTypes::vert;
              newmagnet->newelement = new class RoadTurnDR();
              static_cast<class RoadTurnDR*>(newmagnet->newelement)->d=NNode;
              static_cast<class RoadTurnDR*>(newmagnet->newelement)->r=&(VerticalSideNodes[RailStart.i+1][RailStart.j-1]);
              static_cast<class RoadTurnDR*>(newmagnet->newelement)->i=RailStart.i;
              static_cast<class RoadTurnDR*>(newmagnet->newelement)->j=RailStart.j-1;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
      }

      if (NNode->u==nullptr)
      {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i;
              newmagnet->address.j=RailStart.j-1;
              newmagnet->address.type=NetworkNodeTypes::vert;
              newmagnet->newelement = new class RoadTurnDL();
              static_cast<class RoadTurnDL*>(newmagnet->newelement)->d=NNode;
              static_cast<class RoadTurnDL*>(newmagnet->newelement)->l=&(VerticalSideNodes[RailStart.i][RailStart.j-1]);
              static_cast<class RoadTurnDL*>(newmagnet->newelement)->i=RailStart.i;
              static_cast<class RoadTurnDL*>(newmagnet->newelement)->j=RailStart.j-1;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
      }


// ======================== corners to diag
      if (NNode->u==nullptr)
      {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i;
              newmagnet->address.j=RailStart.j-1;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class RoadTurn_U_UL();
              static_cast<class RoadTurn_U_UL*>(newmagnet->newelement)->d=NNode;
              static_cast<class RoadTurn_U_UL*>(newmagnet->newelement)->ul=&(CornerNodes[RailStart.i][RailStart.j-1]);
              static_cast<class RoadTurn_U_UL*>(newmagnet->newelement)->i=RailStart.i;
              static_cast<class RoadTurn_U_UL*>(newmagnet->newelement)->j=RailStart.j-1;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
      }

      if (NNode->u==nullptr)
      {
              DMagnet * newmagnet = new DMagnet;
              newmagnet->address.i=RailStart.i+1;
              newmagnet->address.j=RailStart.j-1;
              newmagnet->address.type=NetworkNodeTypes::corner;
              newmagnet->newelement = new class RoadTurn_U_UR();
              static_cast<class RoadTurn_U_UR*>(newmagnet->newelement)->d=NNode;
              static_cast<class RoadTurn_U_UR*>(newmagnet->newelement)->ur=&(CornerNodes[RailStart.i+1][RailStart.j-1]);
              static_cast<class RoadTurn_U_UR*>(newmagnet->newelement)->i=RailStart.i;
              static_cast<class RoadTurn_U_UR*>(newmagnet->newelement)->j=RailStart.j-1;
              newmagnet->valid = check_obstruction(newmagnet->newelement);
              magnets.append(newmagnet);
      }

}
