#include <dmainscreen.h>

void DMainScreen::mouseReleaseEvent(QMouseEvent *event)
{
    if (READY) {

            switch (event->button()){
                case Qt::RightButton: moving = false;

                    break;
                case Qt::LeftButton: zooming = false;

                    switch (CurrentTool)
                        {
                        case TOOL_RAILROAD_PLACE_END:

                            {
                                CurrentTool = TOOL_RAILROAD_PLACE_START;

                                if (HoverMagnet!=nullptr)
                                    {

                                        if (HoverMagnet->valid)
                                            {

                                                DMagnet * mag = HoverMagnet;

                                                do {
                                                        NetworkList->append(mag->newelement);

                                                        NetworkList->last->killUpgraded();
                                                        NetworkList->last->LinkNodes();

                                                        for ( QList<ObstructionElement>::iterator iter=NetworkList->last->imprint.begin(); iter!=NetworkList->last->imprint.end();iter++)
                                                            {
                                                                if (iter->tile.u==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].u=NetworkList->last;
                                                                if (iter->tile.d==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].d=NetworkList->last;
                                                                if (iter->tile.l==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].l=NetworkList->last;
                                                                if (iter->tile.r==1)
                                                                    obstructions[NetworkList->last->i+iter->adress.x()][NetworkList->last->j+iter->adress.y()].r=NetworkList->last;
                                                            }

                                                        mag = mag->prev;
                                                    } while(mag!=nullptr);
                                            }

                                        DESTROY_MAGNETS();
                                    }
                                break;

                            }

                        case TOOL_ROAD_PLACE_END:
                            {

                                 CurrentTool = TOOL_ROAD_PLACE_START;

                                 if (HoverMagnet!=nullptr)
                                     {

                                         if (HoverMagnet->valid)
                                             {

                                                 DMagnet * mag = HoverMagnet;

                                                 do {
                                                         RoadList->append(mag->newelement);

                                                         RoadList->last->killUpgraded();
                                                         RoadList->last->LinkNodes();

                                                         for ( QList<ObstructionElement>::iterator iter=RoadList->last->imprint.begin(); iter!=RoadList->last->imprint.end();iter++)
                                                             {
                                                                 if (iter->tile.u==1)
                                                                     obstructions[RoadList->last->i+iter->adress.x()][RoadList->last->j+iter->adress.y()].u=RoadList->last;
                                                                 if (iter->tile.d==1)
                                                                     obstructions[RoadList->last->i+iter->adress.x()][RoadList->last->j+iter->adress.y()].d=RoadList->last;
                                                                 if (iter->tile.l==1)
                                                                     obstructions[RoadList->last->i+iter->adress.x()][RoadList->last->j+iter->adress.y()].l=RoadList->last;
                                                                 if (iter->tile.r==1)
                                                                     obstructions[RoadList->last->i+iter->adress.x()][RoadList->last->j+iter->adress.y()].r=RoadList->last;
                                                             }

                                                         mag = mag->prev;
                                                     } while(mag!=nullptr);
                                             }

                                         DESTROY_MAGNETS();
                                     }
                                 break;

                            }

                        default: break;
                        }
                    break;
                default: QWidget::mouseReleaseEvent(event);
                }


            update();
        }
}
